轮式与履带式车辆同步 {#vehicle_synchronization}
=================================

\tableofcontents

SynChrono 提供了对 [Chrono::Vehicle](@ref manual_vehicle) 模型模板的状态同步支持。目前支持轮式和履带式车辆的同步。

## 基本概念 {#veh_sync_general_concepts}

为了实现 SynChrono 将 Project Chrono 的物理扩展到多代理领域的目标，第一步是实现大规模车辆场景。单车仿真已经通过 [Chrono::Vehicle](@ref manual_vehicle) 模块得到支持，但需要一个可扩展的解决方案来支持几十到上百辆额外的车辆。通过 SynChrono 的同步骨干，这成为可能。SynChrono 内的同步在 [这里](state_synchronization.html) 有详细说明。

为了在代理之间实现时间和空间的一致性，状态传递在预定的心跳时进行，以有效地假装所有车辆都在同一个世界中进行仿真。[SynAgent](group__synchrono__agent.html) 管理这些假想代理（或 _僵尸_）的构建和同步，并处理生成要在代理之间分发的状态消息。[SynWheeledVehicleAgent](@ref chrono::synchrono::SynWheeledVehicleAgent) 和 [SynTrackedVehicleAgent](@ref chrono::synchrono::SynTrackedVehicleAgent) 类是用于 [ChWheeledVehicle](@ref chrono::vehicle::ChWheeledVehicle) 和 [ChTrackedVehicle](@ref chrono::vehicle::ChTrackedVehicle) 的薄包装器。在仿真过程中，VehicleAgent 将为其他节点上初始化的每个 VehicleAgent 初始化一个僵尸，将其自身的状态分发到其他节点，并同步每个僵尸以匹配其对应的代理。这个循环可以在下图中看到。

<img src="http://www.projectchrono.org/assets/manual/synchrono_vehicle_synchronization.png" alt="DDS System" width=60%>

轮式和履带式车辆将通过 SynChrono 分发各自的状态和描述信息。状态数据描述了车辆特定组件的当前位置和方向。在 SynChrono 的初始握手过程中，会发送描述消息，描述如何将车辆重建为僵尸。有关确切数据类型的详细说明，请参见 [轮式车辆同步](#veh_sync_wheeled) 或 [履带式车辆同步](#veh_sync_tracked) 部分。

### 限制 {#veh_sync_limitations}

目前，仅在代理之间共享各种车辆组件的位置和方向。接触力未共享，因此代理仅在空间上保持一致（即具有知识），而不是在空间上交互。

## 轮式车辆同步 {#veh_sync_wheeled}

[SynWheeledVehicleAgent](@ref chrono::synchrono::SynWheeledVehicleAgent) 仅仅是对 [ChWheeledVehicle](@ref chrono::vehicle::ChWheeledVehicle) 指针的一个封装。

### 描述消息 {#veh_sync_wheeled_description}

为了重建一个 [ChWheeledVehicle](@ref chrono::vehicle::ChWheeledVehicle)，必须知道其底盘、轮辋和轮胎的视觉表示。为了增强通用性并允许多种车辆配置（即超过四个轮子），还会发送轮子的数量。每个视觉文件表示为一个字符串，然后相对于 Chrono 数据目录进行读取。

在仿真初始化时，底盘、轮子和轮胎被放置在原点。随着状态消息的接收，位置会被更新。

```protobuf
table Description {
  chassis_vis_file:string;
  wheel_vis_file:string;
  tire_vis_file:string;

  num_wheels:int;
}
```

### 状态消息 {#veh_sync_wheeled_state}

轮式车辆的状态信息相对简单。底盘和模型轮子的姿态（位置和方向）会发送给其他代理。轮子和轮胎共享相同的姿态信息。

在接收时，通过描述消息初始化创建的物体会更新其位置。

在发送时，会查询附加的车辆指针以获取传递组件的位置和方向。

```protobuf
table State {
  time:double;

  chassis:Pose;

  wheels:[Pose];
}
```

## 履带式车辆同步 {#veh_sync_tracked}

[SynTrackedVehicleAgent](@ref chrono::synchrono::SynTrackedVehicleAgent) 仅仅是对 [ChTrackedVehicle](@ref chrono::vehicle::ChTrackedVehicle) 指针的一个封装。

### 描述消息 {#veh_sync_tracked_description}

为了重建一个 [ChTrackedVehicle](@ref chrono::vehicle::ChTrackedVehicle)，必须知道其底盘、履带鞋、链轮、惰轮和路轮的视觉表示。除了底盘和履带鞋，不同的网格可以用于不同的侧面，因此左右文件分别发送。为了增强通用性并允许多种车辆配置（即更多或更少的链轮/惰轮等），还会发送履带鞋、链轮、惰轮和路轮的数量。每个视觉文件表示为一个字符串，然后相对于 Chrono 数据目录进行读取。

```protobuf
table Description {
  chassis_vis_file:string;
  track_shoe_vis_file:string;
  left_sprocket_vis_file:string;
  right_sprocket_vis_file:string;
  left_idler_vis_file:string;
  right_idler_vis_file:string;
  left_road_wheel_vis_file:string;
  right_road_wheel_vis_file:string;

  num_track_shoes:int;
  num_sprockets:int;
  num_idlers:int;
  num_road_wheels:int;
}
```

### 状态消息 {#veh_sync_tracked_state}

履带式车辆的状态信息只是由代理处理的每个组件的姿态（位置和方向）组成的长列表。在接收时，每个组件的位置会被更新；在发送时，会查询附加的车辆指针以获取每个组件的位置和方向。

```protobuf
table State {
  time:double;

  chassis:Pose;

  track_shoes:[Pose];
  sprockets:[Pose];
  idlers:[Pose];
  road_wheels:[Pose];
}
```