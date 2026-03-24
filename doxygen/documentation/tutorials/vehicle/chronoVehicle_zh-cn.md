Chrono VEHICLE 模块教程 {#tutorial_table_of_content_chrono_vehicle}
===============================

Chrono 发行版中包含了多个使用 [VEHICLE 模块](@ref vehicle) 对地面车辆系统进行建模和仿真的示例程序。

Chrono::Vehicle 在一个基于模板的框架中，为轮式和履带式车辆提供了支持。这些模板是各种车辆及车辆子系统的参数化模型。

除了主库之外，VEHICLE 模块还创建了一个预定义的 [VEHICLE 模型](@ref vehicle_models) 库，目前包含以下内容：

- 轮式车辆模型
  - [HMMWV](@ref vehicle_models_hmmwv): 越野四轮车
  - [Sedan](@ref vehicle_models_sedan): 普通乘用车
  - [Citybus](@ref vehicle_models_citybus): 城市公交车
  - [UAZ](@ref vehicle_models_uaz): UAZ-452 小型客车模型
  - [M-role](@ref vehicle_models_mrole): 多用途轮式车辆模型
  - [MAN](@ref vehicle_models_man): 卡车模型（3 种不同变体：5t、7t 和 10t）
  - [Kraz](@ref vehicle_models_kraz): 半挂卡车模型
  - [FMTV](@ref vehicle_models_fmtv): 中型战术车辆系列卡车模型
  - [Gator](@ref vehicle_models_gator): 小型多用途车辆模型
  - [RC](@ref vehicle_models_rccar): 遥控车辆模型
- 履带式车辆模型
  - [M113](@ref vehicle_models_m113): M113 履带车辆
  - [Marder](@ref vehicle_models_marder): Marder 履带车辆

选择车辆示例：

- demo_VEH_HMMWV - 越野四驱轮式车辆（源自车辆模型库）
- demo_VEH_HMMWV_DefSoil - 轮式车辆在 [SCM 可变形地形](@ref vehicle_terrain_scm) 上的演示（Bekker-Wong 型）
- demo_VEH_HMMWV_Multicore - 轮式车辆在 [颗粒地形](@ref vehicle_terrain_granular) 上的多核模拟演示，使用 [MULTICORE 模块](@ref multicore_module)
- demo_VEH_M113 - 履带车辆（源自车辆模型库）
- demo_VEH_M113_DefSoil - 履带车辆在 [SCM 可变形地形](@ref vehicle_terrain_scm) 上的演示（Bekker-Wong 型）
- demo_VEH_M113_Multicore - 履带车辆在 [颗粒地形](@ref vehicle_terrain_granular) 上的多核模拟演示，使用 [MULTICORE 模块](@ref multicore_module)
- demo_VEH_SteeringController - 使用横向转向控制器进行双车道变换操作
- demo_VEH_CRGTerrain - OpenCRG 可选接口的演示
- demo_VEH_ArticulatedVehicle - 演示如何扩展 Chrono::Vehicle（铰接底盘）
- demo_VEH_TactorTrailer - 演示如何扩展 Chrono::Vehicle（牵引车-挂车车辆）
- demo_VEH_TwoCars - 演示如何在单个仿真中使用多个车辆
- demo_VEH_WheeledJSON - 通过 JSON 规范文件定义的轮式车辆
- demo_VEH_TrackedJSON - 通过 JSON 规范文件定义的履带车辆
- demo_VEH_DeformableSoil - 演示在 [SCM 可变形地形](@ref vehicle_terrain_scm) 中使用位置依赖的土壤参数
- demo_VEH_MovingPatch - 演示 [颗粒地形](@ref vehicle_terrain_granular) 的移动补丁功能
- demo_VEH_RigidTerrain - 演示如何为 [刚性地形](@ref vehicle_terrain_rigid) 模型使用多个补丁
- demo_VEH_SuspensionTestRig - 演示带轮胎驱动的轮式车辆 [悬挂测试台](@ref wheeled_rig_suspension)
- demo_VEH_TireTestRig - 演示单个 [轮胎测试台](@ref wheeled_rig_tire)
- demo_VEH_TrackTestRig - 演示履带车辆履带组件测试台
