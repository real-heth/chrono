车辆底盘 {#vehicle_chassis}
==================================

任何车辆系统都必须包含一个底盘子系统。车辆的位置、方向、速度和加速度被定义为底盘参考系的状态。所有其他车辆子系统都是相对于车辆底盘初始化的。

目前，仅提供一个底盘模板：[ChRigidChassis](@ref chrono::vehicle::ChRigidChassis)，它由一个刚体组成。

对于建模具有不同拓扑结构的车辆（例如，铰接底盘）、具有扭转顺应性的底盘以及拖车系统，Chrono::Vehicle 还包括所谓的“后底盘”（基类 [ChChassisRear](@ref chrono::vehicle::ChChassisRear)，刚体模板 [ChRigidChassisRear](@ref chrono::vehicle::ChRigidChassisRear)），可以使用专门的“底盘连接器”连接到前底盘。

提供了以下三种类型的底盘连接器模板：

* [ChChassisConnectorArticulated](@ref chrono::vehicle::ChChassisConnectorArticulated) 允许通过一个由转向驱动输入控制的驱动铰链关节连接前后底盘
* [ChChassisConnectorTorsion](@ref chrono::vehicle::ChChassisConnectorTorsion) 允许通过一个具有指定扭转刚度的纵向铰链关节连接前后底盘
* [ChChassisConnectorHitch](@ref chrono::vehicle::ChChassisConnectorHitch) 模拟拖车挂钩连接（使用球形关节）
