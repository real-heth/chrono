可视化 {#vehicle_visualization}
======================================

\tableofcontents

Chrono::Vehicle 提供了对运行时交互式仿真以及高质量后处理渲染以生成动画的可视化支持。运行时仿真支持基于底层的 [Chrono::VSG](@ref vsg_module) 和 [Chrono::Irrlicht](@ref irrlicht_module) 模块。前者是推荐的运行时可视化系统，特别适用于 CRM 可变形地形上的车辆仿真（Irrlicht 基于的可视化系统不支持）。通过实用函数提供对单个仿真帧的光线追踪渲染的支持，这些函数可以在仿真循环中调用，以导出包含当前可视化资产信息的数据文件和一个 POV-Ray 脚本，该脚本可以批处理这些文件以生成帧图像。或者，可以使用 [ChronoBlender](@ref introduction_chrono_blender) 插件在 Blender 中进行后处理。

## 基于VSG的运行时可视化 {#vehicle_visualization_vsg}

基于 VSG 的车辆运行时可视化使用了对基础 Chrono::VSG 运行时可视化系统的自定义插件，以提供车辆特定的功能，例如：

- 以车辆为中心的摄像机（"追踪摄像机"）
- 显示车辆特定的信息
- 控制各个车辆子系统的可见性
- 等等

下面的图像是 Chrono::Vehicle 仿真的快照。

<img src="http://www.projectchrono.org/assets/manual/vis_vsg_wheeled.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vis_vsg_tracked.png" width="600" />

## 基于Irrlicht的运行时可视化 {#vehicle_visualization_irrlicht}

基于 Irrlicht 的车辆运行时可视化使用了针对轮式和履带式车辆的自定义 Irrlicht 应用程序 [ChWheeledVehicleIrrApp](@ref chrono::vehicle::ChWheeledVehicleVisualSystemIrrlicht) 和 [ChTrackedVehicleIrrApp](@ref chrono::vehicle::ChTrackedVehicleVisualSystemIrrlicht)。

这些是对基础 [ChIrrApp](@ref chrono::irrlicht::ChVisualSystemIrrlicht) 应用程序的扩展，以允许：

- 使用以车辆为中心的摄像机位置（视点）
- 显示额外的（车辆特定的）统计信息，例如车辆速度、当前驾驶员输入、动力传动系统扭矩、车轮和链轮扭矩等
- 渲染指定的接触力（履带车辆）

下面的图像是 Chrono::Vehicle 仿真的快照。

<img src="http://www.projectchrono.org/assets/manual/vehicle/visualization/vis_irrlicht_wheeled.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/visualization/vis_irrlicht_tracked.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/visualization/vis_irrlicht_tracked_2.png" width="600" />

## 基于 POV-Ray 的离线渲染 {#vehicle_visualization_povray}

离线渲染需要以下步骤：

- 收集每个需要渲染的帧的系统数据
- 可选地，准备特定于所需渲染引擎格式的网格数据文件
- 后处理数据文件以渲染每个帧的场景
- 可选地，将多个帧图像组合成动画

Chrono::Vehicle 提供了对这种工作流程模型的有限支持，以及对 [POV-Ray](http://www.povray.org/) 光线追踪程序的支持。

**准备输出数据文件**

- 在每个需要后处理的仿真帧上，调用函数 [WriteVisualizationAssets](@ref chrono::utils::WriteVisualizationAssets)。
- 该函数将输出一个以用户提供的名称命名的逗号分隔值（CSV）文件。
- 输出文件包含 Chrono 系统中所有刚体的信息（位置和方向）、所有相关的可视化资产（位置、方向、类型和资产特定参数）以及选定类型的关节。请注意，网格可视化资产是通过其各自的网格名称来标识的。

**准备网格数据文件**

对于使用 POV-Ray 渲染，必须将与网格可视化资产对应的 Wavefront OBJ 文件转换为 POV-Ray 输入文件中的宏。这可以通过以下方式完成

- 使用函数 [WriteMeshPovray](@ref chrono::utils::WriteMeshPovray)
- 使用专用工具，例如 [PoseRay](https://sites.google.com/view/poseray)

如果使用下面描述的渲染脚本，这些网格宏 POV-Ray 输入文件的名称应与相应的网格名称相同。此外，这样的网格 POV-Ray 输入文件必须定义一个单一的宏（与网格名称相同）；因此，由 PoseRay 生成的文件需要手动编辑（请参见 Chrono 分发版中提供的示例，例如 `data/vehicle/hmmwv/POV-Ray/hmmwv_chassis.inp`）。

**使用 POV-Ray 后处理文件**

Chrono 分发版中包含（在目录 `src/demos/vehicle/` 中）一个示例 POV-Ray 脚本（`renderZ.pov`），可用于（批量）处理以 WriteVisualizationAssets 生成的格式输出的数据文件。该脚本假设所有数据都以右手坐标系提供，Z 向上（ISO 参考系），并执行所有必要的转换以适应 POV-Ray 的 Y 向上左手坐标系。

该脚本提供以下用户控制：

- 渲染单帧或一系列帧（批处理）
- 打开/关闭刚体参考系的渲染
- 打开/关闭全局参考系的渲染
- 打开/关闭可视化资产的渲染
- 打开/关闭固定在地面的可视化资产的渲染
- 打开/关闭支撑关节的渲染
- 打开/关闭弹簧和阻尼器的渲染
- 指定表示关节的几何形状的尺寸
- 摄像机位置和观察点
- 启用/禁用阴影
- 可选地渲染环境（地面和天空）

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_10t.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/M113.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/visualization/vis_povray_frames.png" width="600" />

请注意，`renderZ.pov` 脚本仅作为起点提供。可以使用更复杂的材料和环境，通过 POV-Ray 生成更复杂和逼真的图像。

最后，可以使用类似的工作流程使用不同的渲染引擎，而不仅仅是 POV-Ray。例如，下面的图像是使用由 WriteVisualizationAssets 生成的数据文件，但使用 Mitsuba 引擎生成的。

<img src="http://www.projectchrono.org/assets/manual/vehicle/visualization/vis_mitsuba_wheeled.png" width="600" />
