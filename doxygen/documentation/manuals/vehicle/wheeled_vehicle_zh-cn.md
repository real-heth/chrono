轮式车辆 {#wheeled_vehicle}
===================================

Chrono::Vehicle 中的轮式车辆是抽象通用车辆系统 ([ChVehicle](@ref chrono::vehicle::ChVehicle)) 的一种特化，定义为一组子系统的集合（如下图所示）。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled_subsystems.png" width="800" />

轮式车辆包含一个底盘子系统、一个传动系统子系统，以及任意数量的车轴，按照惯例，从车辆前部开始编号。通过允许任意数量的转向机构（连接到不同的车轴）或允许多个可转向车轴连接到同一转向机构，可以支持多转向车辆。每个车轴可以接受每侧一个或两个轮胎。

参见 [ChWheeledVehicle](@ref chrono::vehicle::ChWheeledVehicle)。

各种子系统模板在以下部分中进行了描述：

* @subpage wheeled_suspension
* @subpage wheeled_steering
* @subpage wheeled_driveline
* @subpage wheeled_tire
