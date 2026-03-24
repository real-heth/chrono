如何创建一个自定义的 ROS handler {#custom_handlers}
===================================

本手册页面旨在向读者介绍如何为 Chrono::ROS 创建自定义 ROS handler 的过程。

ROS 是一个用于编写机器人软件的灵活框架。它是一个工具、库和约定的集合，旨在简化在各种机器人平台上创建复杂且稳健的机器人行为的任务。本手册页面不会详细介绍 ROS，因此请参阅 [ROS 网站](http://www.ros.org/) 获取更详细的信息。假设读者在继续之前已经熟悉 ROS 的基本概念。

## 什么是 handler？

handler 是一个负责在 ROS 和 Chrono 之间转换消息的类。它是 ROS 世界和 Chrono 世界之间的接口。handler 本质上是一个高级抽象，封装了所有 ROS 实体，如发布者、订阅者和服务，并提供一个简单的接口与它们交互。任何与 ROS 交互的逻辑都应封装在 handler 中。

## Chrono::ROS Handler 实现指南

本指南将介绍如何为 Chrono::ROS 接口实现新的 handler。

## 架构概述

Chrono::ROS 使用 **双进程架构** 来确保分离并避免符号冲突（特别是在 Chrono 9.0 中 VSG 可视化和 ROS 2 库之间的冲突）。

1.  **主进程（Chrono 仿真）**：运行物理仿真。从 Chrono 对象中提取数据并将其序列化为原始字节。它 **不包含** ROS 符号。
2.  **子进程（ROS 节点）**：运行 ROS 节点。通过 IPC（进程间通信）接收原始字节，反序列化它们，并发布标准 ROS 消息。它 **不包含** Chrono 物理符号。

### "Handler" 概念

"Handler" 是这两个世界之间的桥梁。要添加新功能（例如发布新的传感器类型），必须实现一个跨越两个进程的 Handler。

一个完整的 Handler 包含 4 个文件：
1.  `ChROS<Name>Handler.h`：类定义（主进程）。
2.  `ChROS<Name>Handler.cpp`：数据提取和序列化逻辑（主进程）。
3.  `ChROS<Name>Handler_ipc.h`：**共享**数据结构定义（两个进程）。
4.  `ChROS<Name>Handler_ros.cpp`：ROS 发布/订阅逻辑（子进程）。

---

## 共享 IPC 头文件 (`*_ipc.h`)

这是最关键的文件。它定义了 Chrono 进程和 ROS 进程之间的“契约”。

*   **位置**：通常与您的 handler 文件放在一起（例如，`src/chrono_ros/handlers/sensor/`）。
*   **内容**：普通的 C++ 结构体（POD - Plain Old Data）。
*   **限制**：
    *   **不允许** 指针。
    *   **不允许** `std::string`、`std::vector` 或其他动态容器。
    *   **不允许** ROS 或 Chrono 头文件（请使用原始类型，如 `double`、`float`、`char[]`）。

**示例 (`ChROSCameraHandler_ipc.h`):**

```cpp
namespace chrono {
namespace ros {
namespace ipc {

struct CameraData {
    char topic_name[128]; // 固定大小字符串
    char frame_id[64];    // 固定大小字符串
    uint32_t width;
    uint32_t height;
    uint32_t step;
    // 数据紧跟在此结构体之后的字节流中
};

} // namespace ipc
} // namespace ros
} // namespace chrono
```

---

## 实现模式：发布者（Chrono → ROS）

使用此模式用于传感器或状态报告（例如，摄像头、GPS、物体状态）。

### 1. 主进程（`.h` / `.cpp`）

继承自 `ChROSHandler`。您的任务是实现 `GetSerializedData`。

**头文件 (`ChROSMyHandler.h`):**

```cpp
class CH_ROS_API ChROSMyHandler : public ChROSHandler {
public:
    // ... 构造函数 ...
    
    // 1. 初始化：验证输入（例如，检查主题名称）
    virtual bool Initialize(std::shared_ptr<ChROSInterface> interface) override;
    
    // 2. 消息类型：返回您的消息的枚举值
    virtual ipc::MessageType GetMessageType() const override { return ipc::MessageType::MY_DATA_TYPE; }
    
    // 3. 序列化：将数据打包为字节
    virtual std::vector<uint8_t> GetSerializedData(double time) override;
};
```

**实现 (`ChROSMyHandler.cpp`):**

```cpp
#include "ChROSMyHandler_ipc.h" // 包含共享结构体
#include <cstring> // 用于 std::memcpy

std::vector<uint8_t> ChROSMyHandler::GetSerializedData(double time) {
    // 可选：如果需要，可以在此处实现节流逻辑
    // if (time - m_last_time < 1.0 / m_update_rate) return {};

    // 1. 从 Chrono 对象中提取数据
    auto data = m_my_object->GetData();

    // 2. 打包到 IPC 结构体中
    ipc::MyDataStruct msg;
    strncpy(msg.topic_name, m_topic_name.c_str(), sizeof(msg.topic_name) - 1);
    msg.value = data;

    // 3. 序列化为向量
    // 注意：在生产代码中，使用成员变量 m_buffer 以避免重新分配
    std::vector<uint8_t> buffer(sizeof(ipc::MyDataStruct));
    std::memcpy(buffer.data(), &msg, sizeof(ipc::MyDataStruct));
    return buffer;
}
```

### 2. 子进程 (`_ros.cpp`)

此文件 **仅** 编译到 ROS 节点可执行文件中。它使用 `rclcpp` 发布数据。

**实现 (`ChROSMyHandler_ros.cpp`):**

```cpp
#include "chrono_ros/ChROSHandlerRegistry.h"
#include "ChROSMyHandler_ipc.h"
#include "std_msgs/msg/float64.hpp" // ROS 消息头文件

namespace chrono {
namespace ros {

// 回调函数
void PublishMyDataToROS(const uint8_t* data, size_t data_size, 
                        rclcpp::Node::SharedPtr node, 
                        ipc::IPCChannel* channel) {
    
    // 1. 反序列化
    if (data_size < sizeof(ipc::MyDataStruct)) return;
    const auto* msg_ipc = reinterpret_cast<const ipc::MyDataStruct*>(data);

    // 2. 创建/获取发布者（使用静态映射以保持持久性）
    static std::unordered_map<std::string, rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr> publishers;
    std::string topic = msg_ipc->topic_name;
    
    if (publishers.find(topic) == publishers.end()) {
        publishers[topic] = node->create_publisher<std_msgs::msg::Float64>(topic, 10);
    }

    // 3. 发布 ROS 消息
    std_msgs::msg::Float64 msg_ros;
    msg_ros.data = msg_ipc->value;
    publishers[topic]->publish(msg_ros);
}

// 4. 注册处理程序
CHRONO_ROS_REGISTER_HANDLER(MY_DATA_TYPE, PublishMyDataToROS)

} // namespace ros
} // namespace chrono
```

---

## 实现模式：订阅者（ROS → Chrono）

使用此模式用于控制输入（例如，驾驶员输入、机器人控制）。这是一个 **双向** 流。
2.  **运行时阶段**: 子进程接收 ROS 消息 → 发送 IPC 消息到主进程 → 主进程应用到 Chrono 对象。

### 1. 主进程（`.h` / `.cpp`）

**头文件 (`ChROSMySubscriber.h`):**

```cpp
class CH_ROS_API ChROSMySubscriber : public ChROSHandler {
public:
    // ...
    
    // 1. 处理传入消息：将 ROS 数据应用到 Chrono
    virtual void HandleIncomingMessage(const ipc::Message& msg) override;
    
    // 2. 启用双向支持
    virtual bool SupportsIncomingMessages() const override { return true; }
    
    // 3. 序列化：仅发送一次 SETUP 消息（主题名称）
    virtual std::vector<uint8_t> GetSerializedData(double time) override;
};
```

**实现 (`ChROSMySubscriber.cpp`):**

```cpp
std::vector<uint8_t> ChROSMySubscriber::GetSerializedData(double time) {
    // 仅发送一次主题名称以触发子进程中的订阅者创建
    if (!m_setup_sent) {
        m_setup_sent = true;
        return std::vector<uint8_t>(m_topic_name.begin(), m_topic_name.end());
    }
    return {}; // 设置完成后不再发送数据
}

void ChROSMySubscriber::HandleIncomingMessage(const ipc::Message& msg) {
    // 解包从子进程发送回的数据
    const auto* data = msg.GetPayload<ipc::MyControlStruct>();
    
    // 应用到 Chrono 物理对象
    m_my_object->SetControl(data->control_value);
}
```

### 2. 子进程 (`_ros.cpp`)

**实现 (`ChROSMySubscriber_ros.cpp`):**

```cpp
static rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr g_sub;
static ipc::IPCChannel* g_ipc_channel = nullptr; // 用于发送数据回主进程

// ROS 回调函数
void OnMessageReceived(const std_msgs::msg::Float64::SharedPtr msg) {
    if (!g_ipc_channel) return;

    // 1. 打包 IPC 结构体
    ipc::MyControlStruct data;
    data.control_value = msg->data;

    // 2. 发送回主进程
    ipc::Message ipc_msg(ipc::MessageType::MY_DATA_TYPE, 0, sizeof(data), 
                         reinterpret_cast<const uint8_t*>(&data), sizeof(data));
    g_ipc_channel->SendMessage(ipc_msg);
}

// 设置函数（当主进程发送主题名称时调用一次）
void SetupMySubscriber(const uint8_t* data, size_t size, 
                       rclcpp::Node::SharedPtr node, 
                       ipc::IPCChannel* channel) {
    g_ipc_channel = channel; // 存储回调通道
    
    std::string topic(reinterpret_cast<const char*>(data), size);
    g_sub = node->create_subscription<std_msgs::msg::Float64>(
        topic, 10, OnMessageReceived);
}

CHRONO_ROS_REGISTER_HANDLER(MY_DATA_TYPE, SetupMySubscriber)
```

---

## 注册步骤

要将新的处理程序集成到构建系统和 IPC 框架中，请按照以下 2 个步骤操作。

### 1. 添加消息类型枚举

**文件**: `src/chrono_ros/ipc/ChROSIPCMessage.h`

向 `enum class MessageType` 添加一个新值。

**为什么？** 这个唯一的 ID 允许子进程在接收到消息时知道要执行哪个回调函数。

```cpp
enum class MessageType : uint32_t {
    // ...
    MY_DATA_TYPE = 15, // 添加此项
    // ...
};
```

### 2. 更新 CMakeLists.txt

**文件**: `src/chrono_ros/CMakeLists.txt`

将你的 `_ros.cpp` 文件添加到 `chrono_ros_node` 目标源中。

**为什么？** ROS 端的逻辑（发布/订阅）必须编译到单独的 `chrono_ros_node` 可执行文件中，而不是主 Chrono 库。

**关键**: 如果你忘记这一步，你的处理程序将会编译，但在运行时会看到 "No handler registered for message type" 警告，因为你的 `_ros.cpp` 文件中的注册宏从未在子进程中执行。

```cmake
target_sources(chrono_ros_node PRIVATE
    # ...
    handlers/sensor/ChROSMyHandler_ros.cpp
)
```

### 3. 更新 SWIG 接口（可选）

**文件**: `src/chrono_swig/interface/ros/ChModuleROS.i`

如果你想在 Python（PyChrono）中使用你的处理程序，你必须在 SWIG 接口文件中注册它。

**为什么？** SWIG 需要知道你的 C++ 类，以生成 Python 包装器。

1.  **包含头文件**: 在 C++ 块中添加 `#include "chrono_ros/handlers/sensor/ChROSMyHandler.h"`（在 `%{ ... %}` 内）。
2.  **启用共享指针**: 在共享指针部分添加 `%shared_ptr(chrono::ros::ChROSMyHandler)`。
3.  **包含 SWIG 定义**: 在包含部分添加 `%include "../../../chrono_ros/handlers/sensor/ChROSMyHandler.h"`。

> **注意**: 你不需要修改 `ChROSManager.cpp`。只要你的新类继承自 `ChROSHandler`，管理器将自动处理它。

---

## 使用方法（在你的应用程序中）

最后，要在仿真中使用你的新处理程序：

```cpp
// 1. 创建处理程序
auto my_handler = chrono_types::make_shared<ChROSMyHandler>(...);

// 2. 注册到管理器
// 为什么？这告诉管理器在每次更新时调用你的处理程序的 GetSerializedData()。
ros_manager->RegisterHandler(my_handler);
```

## 最佳实践

*   **节流**: 在 `GetSerializedData` 中使用 `m_update_rate` 实现速率限制。如果不是发布的时间，返回一个空向量。这可以减轻 ROS（其 DDS 中间件）的压力，因为仿真在某些情况下可以比实时运行快很多。
*   **内存**: 避免在循环中重新分配向量。使用成员变量 `std::vector<uint8_t> m_buffer` 并使用 `resize()`。
*   **线程安全**: 在双向处理程序中，`HandleIncomingMessage` 从主线程调用，但如果你使用多线程步进，请确保你的 Chrono 对象修改是安全的。
*   **示例**:
    *   查看 `ChROSCameraHandler` 了解复杂数据（图像）。
    *   查看 `ChROSDriverInputsHandler` 了解双向控制。
