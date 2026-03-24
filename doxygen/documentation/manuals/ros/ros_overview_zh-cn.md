Chrono::ROS {#module_ros_overview}
==============

## 项目概述

Chrono::ROS 是由威斯康星大学麦迪逊分校的基于仿真的工程实验室 ([SBEL](https://sbel.wisc.edu)) 开发的一个模块。该项目的目标是提供一个简单且可扩展的接口，将 Project Chrono 与机器人操作系统 ([ROS 2](https://docs.ros.org/)) 连接起来。Chrono::ROS 允许个人将 Chrono 直接集成到 ROS 自主堆栈的开发中。基于 ROS 2 现有的网络功能，Chrono::ROS 使用现有的 ROS 概念（发布者、订阅者等）并直接与 ROS 主题进行交互。

## 对其他 Chrono 模块的支持 {#ch_modules}

Chrono::ROS 并不一定绑定到任何一个特定的 Chrono 模块；然而，目前仅为现有的 Chrono 功能实现了有限数量的处理程序。例如，[Chrono::Vehicle](@ref manual_vehicle) 和 [Chrono::Sensor](@ref manual_sensor) 已经实现了通用处理程序，用于快速原型开发。

如果使用其他模块，可以实现自定义处理程序来处理这些功能。有关如何实现自定义处理程序的更多信息，请参阅 [Chrono::ROS 自定义处理程序页面](@ref custom_handlers)。

支持 PyChrono/Chrono:Python 封装。
