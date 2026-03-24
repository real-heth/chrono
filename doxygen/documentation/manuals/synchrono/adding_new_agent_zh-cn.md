如何向 SynChrono 添加新实体（agent）
=============================================

SynChrono 允许你分布式地仿真多辆车，并且还可以扩展其功能以模拟不同的 _实体_。在本示例中，我们将演示如何添加一个直升机实体。

## 设置 FlatBuffer 编译器

所有 SynChrono 消息的消息格式都由 FlatBuffers 模式控制。当更改消息格式时，必须重新编译模式。此重新编译会导致 FlatBuffers 重新生成 C++ 包装代码，从而允许我们解包 FlatBuffer 消息。

因此，虽然在运行 SynChrono 代码时只需要 FlatBuffers 头文件，但在编辑消息模式时需要构建 FlatBuffers 编译器（并且为新实体添加新的消息模式时也是如此）。

#### 选项 1：从源代码构建

由于 FlatBuffers 被包含为 Chrono 的子模块，获取 flatc 编译器的一个简单方法是从源代码构建它。

1. 确保你已安装 C++ 编译器和 CMake。
2. 进入 **_chrono_root_** \\src\\chrono_thirdparty\\flatbuffers 
3. 运行 CMake 和 make 命令，具体请参见 [FlatBuffers 指南](https://google.github.io/flatbuffers/flatbuffers_guide_building.html)。例如在 Windows 上：

~~~~~~~~~~~~~~~{.bat}
cmake -G "Visual Studio 15" -DCMAKE_BUILD_TYPE=Release  .
cmake --build . --config RELEASE 
~~~~~~~~~~~~~~~

#### 选项 2：下载预编译版本

在 Windows 上，你可以直接下载 [预编译的二进制文件](https://github.com/google/flatbuffers/releases/)。许多 Linux 发行版（例如 Arch Linux、Ubuntu）也可以通过其包管理器获取预编译版本。

## 生成 flatbuffer 头文件

_flatc_ flatbuffer 编译器解析 .fbs 文件以创建一个头文件，该头文件负责序列化和反序列化对象，提供对缓冲区通信的高级访问。

### 编辑 fbs 文件

打开文件 **chrono_root**\\src\\src\\chrono_synchrono\\agent\\Agent.fbs

1. 添加一个新实体：在 _State_ 表中指定每次更新时必须传递的信息，在 _Description_ 表中指定初始化所需的信息。

~~~~~~~~~~~~~~~{.fbs}
// Derived "class" of Agent
// Creates a copter agent message
namespace SynFlatBuffers.Agent.Copter;
table State {
  time:double;
  chassis:Pose;
  propellers:[Pose];
}
table Description {
  chassis_vis_file:string;
  propeller_vis_file:string;
  num_props:int;
}
root_type State;
~~~~~~~~~~~~~~~

1. 为新实体添加消息（以下代码片段的最后两行）：

~~~~~~~~~~~~~~~{.fbs}
union Type { 
  WheeledVehicle.State, 
  WheeledVehicle.Description, 
  TrackedVehicle.State, 
  TrackedVehicle.Description, 
  Environment.State,
  Environment.Description,
  Copter.State,             <--
  Copter.DescriptioN        <--
}
~~~~~~~~~~~~~~~

1. 编译 fbs:

    1. 进入 flatbuffer 目录: **_chrono_root_**\\ src\\chrono_synchrono\\flatbuffer\\message

    2. 启动 flatc 编译器: 如下所示:
```..\..\..\chrono_thirdparty\flatbuffers\RELEASE\flatc.exe -c  ..\fbs\SynFlatBuffers.fbs --no-includes --gen-all```

现在，文件 ```*_chrono_root_**\ src\chrono_synchrono\flatbuffer\message\SynFlatBuffers_generated.h ``` 应该已经更改（以反映 .fbs 文件中的修改）

## 对 C++ 代码的更改

### 在 SynCopterMessage.h/cpp 中定义新消息

在此示例中，我们创建一个 State 和 Description 消息（在此示例中为 SynCopterDescriptionMessage 和 SynCopterStateMessage）。

两个子类都必须实现 SynMessage 的纯虚函数（ConvertFromFlatBuffers 和 ConvertToFlatBuffers）。

### 创建一个新的 SynAgent 派生类

新的 SynCopterAgent 继承自 SynAgent，必须重写其纯虚成员函数。有关详细信息，请参见 ```chrono_synchrono/agent/SynCopterAgent.h/cpp```。车辆代理还提供 json 文件初始化，这对于一般的新代理不可用。

1. 构造函数
    1. 初始化状态和描述消息成员变量
    2. 通过重载或 if 语句为新代理添加一个默认（无参数）构造函数。它将用于从描述消息构建代理。
2. InitializeZombie
    此函数创建固定的刚体，其在空间中的位置和方向将由来自其他进程的消息决定。
3. SynchronizeZombie
    此函数根据来自其他进程的消息更新僵尸刚体的位置和方向。
4. Update
    更新代理的状态消息。此状态将发送给其他进程（其他进程将其视为僵尸）。更新僵尸的状态是没有意义的，因此在函数开始时进行检查，如在 SynCopterAgent.cpp 中：

```cpp
if (!m_copter)
        return;
```

5. GatherMessages
6. GatherDescriptionMessages

### 向“工厂”动态转换中添加新类

1. 向 ```SynMessageFactory.cpp``` 添加新的消息类型：SynMessageFactory 使用动态转换来推断消息的类型。因此，每当我们添加一个新的消息类型时，我们必须在状态和描述的 elseif 语句中添加另一个条件：

```cpp
else if (agent_state->message_type() == SynFlatBuffers::Agent::Type_Copter_State) {
            message = chrono_types::make_shared<SynCopterStateMessage>(source_key, destination_key);
        }
```

2. 向 ```AgentFactory.cpp``` 添加新的代理

AgentFactory 使用动态转换从来自其他进程的描述中创建僵尸代理。由于我们添加了新的消息和代理类，因此必须相应地修改此函数：

```cpp
else if (auto copter_description = std::dynamic_pointer_cast<SynCopterDescriptionMessage>(description)) {
        auto copter_agent = chrono_types::make_shared<SynCopterAgent>();
        copter_agent->SetKey(source_key);
        copter_agent->SetZombieVisualizationFiles(copter_description->chassis_vis_file,  //
                                                  copter_description->propeller_vis_file);  //

        copter_agent->SetNumProps(copter_description->GetNumProps());
		agent = copter_agent;
    }
```

请确保完全定义代理描述（在此示例中，我们分配了网格文件和螺旋桨的数量）。
