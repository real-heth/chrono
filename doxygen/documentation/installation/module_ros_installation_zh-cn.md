# 安装 ROS 模块 {#module_ros_installation}

[TOC]

Chrono::ROS 是一个可选模块，允许将 Chrono 与 [机器人操作系统 (ROS)](https://ros.org/) 直接集成。

## 功能

**ROS 模块**允许用户将基于 ROS 2 的自主堆栈与 Chrono 中的自主代理进行接口。

有关更多详细信息，请参阅参考手册中的 [Chrono::ROS](@ref manual_ros) 部分。

## 要求

- 要构建和运行基于此模块的应用程序，需要以下条件：
  - Linux 操作系统（Windows 操作系统支持将很快验证）。
  - 可用的共享内存 (`/dev/shm`) 至少为 1 GB（默认）。
    - Chrono::ROS 接口尝试保留（不一定使用）至少 1 GB 的 `/dev/shm` 以支持 4K Chrono::Sensor 相机图像。
    - 如果您在内存受限的系统上运行，并且不需要高带宽的传感器数据（如 4K 相机），可以通过修改 `src/chrono_ros/ipc/ChROSIPCChannel.h` 来减少共享内存需求。将 `CreateMainChannel` 中的默认 `buffer_size` 从 `512 * 1024 * 1024`（512 MB）更改为较小的值（例如，16 MB 的 `16 * 1024 * 1024`）。对于大多数非视觉传感器，16 MB 已足够。Chrono::ROS 创建了一个双向共享内存通道；因此，无论您在上面设置的值是多少，最大共享内存使用量都是该值的两倍。
  - 所有 ROS 2 发行版和中间件变体均受支持。然而，由于 Humble 是 LTS 版本，它已在 Chrono::ROS 中进行了最彻底的测试，因此我们建议在项目中使用 Humble。ROS 1 不受支持。
  - ROS 2 Humble（有关详细安装说明，请参阅 [docs.ros.org](https://docs.ros.org/en/humble/Installation.html)）。建议使用 Docker。带有 Chrono::ROS 构建的 Docker 镜像可在 [此处](https://hub.docker.com/r/uwsbel/projectchrono) 获取。
    - 使用 Docker 时，请确保覆盖默认的 `shm_size` 为 64 MB；默认情况下需要 `shm_size` 大于 1 GB。
  - 注意：Chrono::ROS 所需的所有 ROS 2 软件包都包含在基础 ROS 2 安装中。

## 可选依赖项

  - 某些功能（在 [参考手册](@ref manual_ros) 中有详细说明）是基于一些可选依赖项有条件构建的。这些依赖项包括：
    - [chrono_ros_interfaces](https://github.com/projectchrono/chrono_ros_interfaces)
  - 要为 Chrono::ROS 构建 URDF 支持，还需要启用 [Chrono::Parsers](@ref module_parsers_installation) 模块。

<div class="ce-info">
注意：如果您启用了带有 URDF 支持的 Chrono::Parsers，并且使用的是比 Iron 更新的 ROS 2 发行版，请确保 `urdfdom_DIR` **不** 设置为 ROS 2 安装路径。`ChParserURDF` 类使用的是更新版本的 urdfdom。
</div>

## 构建说明

1. 要构建 Chrono::ROS，在安装上述依赖项后，确保已源化您的 ROS 2 安装（例如 `source /opt/ros/humble/setup.bash`）。
2. 重复[完整安装](@ref tutorial_install_chrono)的说明。
3. 在 CMake 配置参数或 GUI 中将 `CH_ENABLE_MODULE_ROS` 设置为 'on'。
4. 如上所述，要启用 URDF 支持，还必须启用 [Chrono::Parsers](@ref module_parsers_installation) 模块。
5. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

## 使用

- 请参阅 [参考手册](@ref manual_ros)。

- 查看本模块的 [API 部分](@ref ros) 以获取有关类和函数的文档。

- 查看 [demos](@ref tutorial_table_of_content_chrono_ros) 的 C++ 和 Python 源代码，以了解如何使用本模块的函数。
