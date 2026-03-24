Chrono::ROS 参考手册 {#manual_ros}
=================================

* [安装和构建 Chrono::ROS](@ref module_ros_installation)
* [Chrono::ROS 概述](@ref module_ros_overview)
* [Chrono::ROS 教程](@ref tutorial_table_of_content_chrono_ros)

更多内容即将推出...

## Chrono 9.0 的更新日志

Chrono::ROS 模块已被重构，以解决并防止 ROS 2 和 Chrono 进程空间之间的任何未来符号冲突。新版本将 ROS 2 节点移到单独的进程中，并通过共享内存 (SHM) 将数据从 Chrono 序列化到 ROS。这增强了 Chrono 和 ROS 之间的分离，进一步避免了 ROS 引起的仿真减速。

### 这对我有什么影响？

如果您在项目中没有通过实现和重写 `custom_handler` 类来使用任何自定义处理程序，则此更改不会影响您的项目。任何仅使用内置于 Chrono::ROS 的传感器/车辆/主体处理程序的项目将继续正常运行，而无需进行任何 API 更改。

如果您确实实现了自定义处理程序，则必须将您的处理程序移植到新的设计中。请按照此处的逐步指南操作：[Chrono::ROS 自定义处理程序页面](@ref custom_handlers)。
