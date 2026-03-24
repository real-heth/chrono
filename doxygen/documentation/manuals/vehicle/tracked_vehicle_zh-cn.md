履带式车辆 {#tracked_vehicle}
===================================

类似于轮式车辆，Chrono::Vehicle 中的履带式车辆是通用车辆系统的一个特化，并定义为子系统的层次结构，如下图所示。

<img src="http://www.projectchrono.org/assets/manual/vehicle/tracked_subsystems.png" width="800" />

目前，仅支持一种履带车辆的拓扑结构，该结构在顶层包括一个底盘子系统、车辆传动系统、转向机构和两个履带组件子系统。后者是进一步子系统的容器，每个子系统包括一个链轮机构、一个惰轮张紧器子系统、任意数量的悬挂组件和任意数量的履带板组件。

请参见 [ChTrackedVehicle](@ref chrono::vehicle::ChTrackedVehicle)。

各个子系统模板在以下部分中进行了描述：

* @subpage tracked_assembly
* @subpage tracked_suspension
* @subpage tracked_sprocket
* @subpage tracked_idler
* @subpage tracked_shoe
