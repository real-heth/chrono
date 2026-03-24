概述车辆建模与仿真 {#vehicle_overview}
===============================================================

Chrono::Vehicle 模块提供了一系列模板，用于各种轮式和履带式车辆子系统的拓扑结构，支持刚性、柔性和颗粒地形的建模，支持闭环和交互式驾驶员模型，以及仿真结果的运行时和离线可视化。

车辆系统的建模是以模块化方式进行的，车辆被定义为各种子系统实例的组合（悬架、转向、传动系统等）。通过采用基于模板的设计提供建模的灵活性。在 Chrono::Vehicle 中，模板是参数化模型，定义了车辆子系统的特定实现。因此，模板定义了基本的建模元素（刚体、关节、力元件），规定了子系统的拓扑结构，指定了设计参数，并实现了特定模板（例如双叉臂悬架）的子系统（例如悬架）的通用功能。最后，通过为具体车辆（例如 HMMWV 前悬架）指定模板参数（硬点、关节方向、惯性属性、接触材料属性等）来实例化该模板。

Chrono::Vehicle 的核心模板是车辆子系统的参数化模型。然而，完整的车辆机动性仿真还需要车辆本身之外的辅助系统，例如提供输入控制（如转向、油门、制动）的驾驶员系统、封装发动机和变速箱并连接到车辆传动系统的动力系统，以及地形系统。

对于轮式车辆系统，提供了以下子系统模板：

- 悬架（双叉臂、使用距离约束的简化双叉臂、多连杆、实心车轴、麦克弗森支柱、半拖臂等）
- 转向（Pitman 臂、齿轮齿条）
- 传动系统（基于轴的 2WD 和 4WD，使用专用的 Chrono 建模元素，简化的运动学传动系统）
- 车轮（仅作为附加质量和惯性载体，附加到悬架的主轴体）
- 制动器（使用恒定扭矩并由驾驶员制动输入调节的简单模型）

Chrono::Vehicle 提供了多种轮胎模型及其相关模板，从刚性轮胎到半经验模型（如 Pacejka 和 Fiala），再到使用有限元建模的完全可变形轮胎（使用绝对节点坐标法或共旋转法）。

对于履带式车辆，提供了以下子系统模板：

- 履带板（单销和双销）
- 相关的链轮模板（带相应的齿轮轮廓）
- 悬架（扭转弹簧，带线性或旋转阻尼器，液压）
- 惰轮（带张紧机构）
- 滚轮

作为一个中间件库，Chrono::Vehicle 需要用户提供 C++ 类来具体实例化特定的模板。一个可选的 Chrono 库提供了一些地面车辆的完整 C++ 类集合，包括轮式和履带式车辆，这些类可以作为其他特定车辆模型的示例。虽然这些类通常非常轻量，但这仍然需要一定的编程经验。为了解决这个问题，我们提供了一种基于 JSON 格式输入规范文件的替代机制，用于定义车辆系统和子系统模板的具体实例化。

按照其给定类型（轮式或履带式）的子系统模板层次结构，车辆可以通过相应的 JSON 文件层次结构完全定义，这些文件指定具体的模板参数，或者进一步引用子组件的 JSON 规范文件。以下是一个轮式车辆的顶层 JSON 规范文件示例。结合它引用的所有其他输入文件，这个 JSON 文件完全描述了一个具体的双轴轮式车辆，前后都使用双叉臂悬架，前轴配有 Pitman 臂转向机构，后轮驱动传动系统。

~~~~{.json}
{
  "Name":      "Test vehicle - Double Wishbone",
  "Type":      "Vehicle",
  "Template":  "WheeledVehicle",

  "Chassis": {
    "Input File":  "generic/chassis/Chassis.json"
  },
  
  "Axles": [
  {
    "Suspension Input File":   "generic/suspension/DoubleWishbone.json",
    "Suspension Location":     [1.25, 0, -0.21],
    "Steering Index":          0,
    "Left Wheel Input File":   "generic/wheel/WheelSimple.json",
    "Right Wheel Input File":  "generic/wheel/WheelSimple.json",
    "Left Brake Input File":   "generic/brake/BrakeSimple.json",
    "Right Brake Input File":  "generic/brake/BrakeSimple.json"
  },
  {
    "Suspension Input File":   "generic/suspension/DoubleWishbone.json",
    "Suspension Location":     [-1.25, 0, -0.21],
    "Left Wheel Input File":   "generic/wheel/WheelSimple.json",
    "Right Wheel Input File":  "generic/wheel/WheelSimple.json",
    "Left Brake Input File":   "generic/brake/BrakeSimple.json",
    "Right Brake Input File":  "generic/brake/BrakeSimple.json"
  }
  ],
  
  "Steering Subsystems": [
  {
    "Input File":   "generic/steering/PitmanArm.json",
    "Location":     [1.1, 0, -0.4],
    "Orientation":  [0.98699637, 0, 0.16074256, 0]
  }
  ],
  
  "Driveline": {
    "Input File":          "generic/driveline/Driveline2WD.json",
    "Suspension Indexes":  [1]
  }
}
~~~~

## 参考系 {#vehicle_ISO_frame}

每个车辆子系统都是相对于其自身的参考系定义的；换句话说，车辆子系统模板中的所有硬点位置必须相对于子系统的参考系提供。然后，车辆系统（无论是轮式还是履带式）通过指定其相对于车辆参考系的位置和方向，并提供连接信息（如将特定转向机构连接到轮式车辆的特定车轴/悬架）来构建其组成组件模板的具体实例集合。

在建模中，Chrono::Vehicle 完全使用 ISO 车辆轴约定，即右手坐标系，X 向前，Z 向上，Y 指向车辆左侧（参见 ISO 8855:2011）。下图说明了车辆参考系 O<sub>1</sub>（按惯例与底盘子系统对齐），以及子系统参考系（前后悬架的 O'<sub>2</sub> 和 O''<sub>2</sub>，以及转向机构的 O<sub>3</sub>）对于具有两个车轴的轮式车辆。

<img src="http://www.projectchrono.org/assets/manual/vehicle/ISO_frame.png" width="600" />

### 仿真世界坐标系

虽然 Chrono::Vehicle 仿真的默认世界坐标系也是 ISO（Z 向上）坐标系，但也提供了在不同参考系（例如 Y 向上坐标系）中模拟车辆的支持。

世界坐标系通过旋转矩阵唯一定义（将 ISO 坐标系与所需世界坐标系对齐所需的旋转）。要将世界坐标系定义从默认的 ISO 约定更改为其他坐标系，必须在任何 Chrono::Vehicle 库调用之前设置所需的世界坐标系：

~~~cpp
ChWorldFrame::Set(world_rotation);
~~~

提供了一个快捷方式来指定 Y 向上（X 向前，Z 向右）的世界坐标系：

~~~cpp
ChWorldFrame::SetYUP();
~~~

[ChWorldFrame](@ref chrono::vehicle::ChWorldFrame) 类提供了查询世界法线、前进方向、给定 3D 点的高度（沿世界垂直方向的分量）、将点投影到世界水平面，以及在基准 ISO 坐标系和世界坐标系之间表达 3D 向量的工具。

请参见 `demo_VEH_HMMWV9_YUP`，了解在 Y 向上世界坐标系中进行 Chrono::Vehicle 仿真的示例。

## 仿真循环 {#vehicle_simulation_loop}

Chrono::Vehicle 仿真循环采用力-位移协同仿真方案，其数据交换如下面的两幅图所示，分别针对轮式和履带式车辆。

<img src="http://www.projectchrono.org/assets/manual/vehicle/data_flow_wheeled.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/data_flow_tracked.png" width="600" />

这种软件架构的采用是为了

- 提供模块化和灵活性；
- 允许使用第三方辅助系统模型并将 Chrono::Vehicle 模型集成到更大的仿真框架中；
- 支持与外部工具或其他 Chrono 模块的协同仿真。

这种仿真流程通过 Chrono::Vehicle API 强制执行，该 API 要求所有系统提供一个 <tt>Synchronize</tt> 方法，用于实现数据交换，以及一个 <tt>Advance</tt> 方法，用于实现系统动力学（即将系统状态推进到下一个数据交换时间点）。然而，需要注意的是，使用 Chrono::Vehicle 提供的辅助系统的车辆机动仿真实际上将是一个整体的、一次性耦合的仿真。

<img src="http://www.projectchrono.org/assets/manual/vehicle/simulation_loop.png" width="300" />
