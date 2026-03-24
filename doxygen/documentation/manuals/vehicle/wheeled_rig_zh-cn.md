试验台 {#wheeled_rig}
=========================

\tableofcontents

## 悬挂试验台 {#wheeled_rig_suspension}

[ChSuspensionTestRig](@ref chrono::vehicle::ChSuspensionTestRig) 是一种用于测试整个车辆悬挂组件的机制。被测试的悬挂可以通过以下方式指定：

- 通过独立的 JSON 文件（可能包含或不包含转向子系统）
- 作为车辆 JSON 规范文件中指定的车轴
- 作为现有车辆中指定的车轴（必须已初始化）

提供了两种悬挂试验台的变体：

- [ChSuspensionTestRigPlatform](@ref chrono::vehicle::ChSuspensionTestRigPlatform) 使用两个独立的刚性平台通过与轮胎的相互作用来驱动悬挂机构。参见 demo_VEH_SuspensionTestRigPlatform。
- [ChSuspensionTestRigPushrod](@ref chrono::vehicle::ChSuspensionTestRigPushrod) 对车轮主轴施加直接驱动。参见 demo_VEH_SuspensionTestRigPushrod。

下面的图像显示了使用 ChSuspensionTestRigPlatform（使用前双叉臂悬挂和 TMeasy 轮胎）进行仿真的快照以及示例输出图。

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/susp_test_rig_platform.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/suspe_test_rig_plot1.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/suspe_test_rig_plot2.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/suspe_test_rig_plot3.png" width="600" />

下面的图像显示了使用 ChSuspensionTestRigPushrod（使用前双叉臂悬挂）进行仿真的快照。

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/susp_test_rig_pushrod.png" width="600" />

## 轮胎试验台 {#wheeled_rig_tire}

[ChTireTestRig](@ref chrono::vehicle::ChTireTestRig) 是一种用于测试单个轮胎与 [刚性](@ref vehicle_terrain_rigid)、[SCM 可变形](@ref vehicle_terrain_scm) 或 [颗粒](@ref vehicle_terrain_granular) 地形相互作用的机制。所有可用的 Chrono::Vehicle [轮胎模型](@ref wheeled_tire) 都可以与该试验台一起使用，但仅在与一致的地形模型结合时。

轮胎试验台允许随时间变化的纵向速度、车轮角速度和车轮侧滑角，支持自动选择纵向和角速度以强制执行指定的纵向滑移值，并允许指定倾角（在仿真过程中保持固定）。

参见 demo_VEH_TireTestRig 和 demo_VEH_TireTestRig_Multicore。

下面的图像显示了单个轮胎测试的快照，分别使用 Pac02 轮胎在刚性地形上进行测试，以及在 SCM 可变形地形上使用刚性轮胎进行测试。

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/tire_test_rig_rigid.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/test_rigs/tire_test_rig_SCM.png" width="600" />
