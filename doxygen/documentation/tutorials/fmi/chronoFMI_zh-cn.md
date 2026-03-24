Chrono FMI 模块教程 {#tutorial_table_of_content_chrono_fmi}
===========================

- 液压起重机协同仿真

  该 [demo](https://github.com/projectchrono/chrono/tree/main/fmu/src/demos/fmi) 生成两个 Chrono FMU 并在协同仿真中使用。

  第一个 FMU，`demo_FMI_craneFMU`，封装一个简单的多体系统：一个倒立摆（通过转动副与地面连接）表示起重机主桅，另一个摆表示载荷。起重机主体接受外部提供的作用力（施加在机体某一点，作为其主要连续输入 FMI 变量），并将执行器长度与长度变化率作为主要连续输出提供。

  第二个 FMU，`demo_FMI_actuatorFMU`，封装一个液压执行器，包括液压活塞、方向阀、软管、泵和油箱。作为主要 FMI 变量，该 FMU 接受执行器长度和长度变化率作为连续输入，并将执行器力作为连续输出提供。

  `demo_FMI_hydraulic_crane_cosim` 演示在显式力—位移协同仿真循环中如何使用这两个 FMU。

- Chrono::Vehicle 相关 FMU

  如果同时启用了 `Chrono::FMI` 和 [Chrono::Vehicle](@ref vehicle) 模块，将生成多个封装车辆系统的 FMU：
  
  - `FMU_WheeledVehicle`：封装带 4 个车轮的车辆系统的协同仿真 FMU。该车辆包含动力传动系统和变速器，但不包含轮胎。
  
    封装的 `Chrono::Vehicle` 模型通过车辆、发动机和变速器的 JSON 规格文件定义。该车辆 FMU 必须与提供车辆指令的驾驶系统以及为 4 个车轮提供轮胎载荷（类型为 `TerrainForce`）的 4 个轮胎系统一起协同仿真。
  
    该车辆 FMU 定义如下连续输出变量：

    - 车辆参考系（类型 `ChFrameMoving`）
    - 车轮状态（类型 `WheelState`）

    <br>
  - `FMU_ForceElementTire`：封装“力元”轮胎系统的协同仿真 FMU。

    封装的 `Chrono::Vehicle` 轮胎模型通过一个 JSON 规格文件定义，假定其定义了类型为 `ChForceElementTire` 的轮胎。

    该轮胎 FMU 必须与提供当前车轮状态（类型 `WheelState`）的车辆系统以及在单点查询处提供局部地形信息（高度、法向量和摩擦系数）的地形系统一起协同仿真。

    该轮胎 FMU 定义如下连续输出变量：
    - 车轮—轮胎/地形载荷（类型 `TerrainForce`）
    - 地形查询点的位置（类型 `ChVector3`）
    <br>

  - `FMU_PathFollowerDriver`：封装车辆路径跟踪驾驶器系统的协同仿真 FMU。驾驶器模型包含横向路径跟踪 PID 控制器和纵向巡航 PID 控制器。

    封装的驾驶器模型通过指定横向控制器路径的数据文件定义。

    该驾驶器 FMU 必须与提供当前车辆参考系（类型 `ChFrameMoving`）的车辆系统一起协同仿真。

    该驾驶器 FMU 定义如下连续输出变量：
    - 转向命令（范围 [-1, 1]）
    - 油门命令（范围 [0, 1]）
    - 刹车命令（范围 [0, 1]）

要查看这些 FMU 在协同仿真循环中如何协同工作，我们提供两个示例程序：

- `demo_VEH_FMI_WheeledVehicle_a`

  该程序使用 `WheeledVehicle` 与 `PathFollowerDriver`，并结合 4 个 `Chrono::Vehicle` 轮胎与一个 `Chrono::Vehicle` 地形系统，共同协同仿真一辆以恒定速度沿预定路径行驶的车辆。

- `demo_VEH_FMI_WheeledVehicle_b`

  该程序使用 `WheeledVehicle`、4 个 `ForceElementTire` 实例与 `PathFollowerDriver`，并结合 `Chrono::Vehicle` 地形系统，共同协同仿真一辆以恒定速度沿预定路径行驶的车辆。
