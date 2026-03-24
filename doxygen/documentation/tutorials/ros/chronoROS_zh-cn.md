Chrono ROS 模块教程 {#tutorial_table_of_content_chrono_ros}
===============================

Chrono 分发版包含多个用于将自主堆栈与机器人操作系统 (ROS) 集成的演示，使用 [ROS 模块](@ref ros)。除了 C++ API 外，Chrono::ROS 还可以通过模块 `pychrono.ros` 在 PyChrono 中使用。

Chrono::ROS 提供了直接集成到 ROS 生态系统的功能，使用 rclcpp 中的内置 ROS 实体。Chrono::ROS 仅用于在内置 ROS 数据类型和 Chrono 数据类型之间交换信息。可以扩展基础 `ChROSHandler` 来开发具有 ROS 发布者/订阅者等自定义逻辑的功能。

选择 ROS C++ 演示：

* demo_ROS_sensor - 演示 Chrono::Sensor 与 ROS 的集成
* demo_ROS_two_managers - 演示使用多个 `ChROSManager` 实例
* demo_ROS_urdf - 演示与 URDF 模型的 ROS 集成
* demo_ROS_vehicle - 演示与 Chrono::Vehicle 的 ROS 集成，可选择支持传感器
* demo_ROS_viper - ROS 与 Viper 月球车模型集成演示

选择 ROS Python 演示：

* demo_ROS_sensor.py - 演示 Chrono::Sensor 与 ROS 的集成
* demo_ROS_two_managers.py - 演示使用多个 `ChROSManager` 实例
* demo_ROS_urdf.py - 演示与 URDF 模型的 ROS 集成
* demo_ROS_vehicle.py - 演示与 Chrono::Vehicle 的 ROS 集成，可选择支持传感器
* demo_ROS_viper.py - 演示与 Viper 月球车模型的 ROS 集成

除了上述演示外，对于更复杂的示例，请参见 [Autonomy Research Testbed](https://github.com/uwsbel/autonomy-research-testbed)。在该存储库中，威斯康星大学麦迪逊分校的 [Simulation Based Engineering Lab](https://sbel.wisc.edu) 开展了一项工作，旨在为规模车辆开发自主堆栈。Chrono（以及 Chrono::ROS）被用作该工作的开发平台。
