SynChrono {#module_synchrono_overview}
==============

<div style="text-align:center">
<img src="http://www.projectchrono.org/assets/manual/synchrono/synchrono-convoy.png" width="450" />
<img src="http://www.projectchrono.org/assets/manual/synchrono/synchrono-highway.png" width="534" />
</div>

## 项目概览

SynChrono 是由威斯康星大学麦迪逊分校的基于仿真的工程实验室（[SBEL](https://sbel.wisc.edu/)）开发的自主车辆仿真项目。该仿真框架基于能够在统一框架中模拟一个或多个机器人、自主车辆或其他自主代理的能力。我们当前的动机来自自主车辆测试，因此我们的许多演示和示例将借鉴自主车辆，但由于仿真由 Chrono 支持，我们可以支持任何虚拟环境。

我们的目标是将 Project Chrono 的物理仿真扩展到多代理领域，特别是代理动力学不强耦合的多代理领域。对于例如两个水下机器人仿真，其中一个机器人产生的水流会影响另一个机器人的动力学，最好使用 Chrono，在 Chrono 中，机器人和流体将包含在单个 Chrono 模型中，并且动力学将联合仿真。

SynChrono 适用于每个代理的动力学单独重要，但它们之间的相互作用不重要的场景。对于自主车辆来说，除非发生碰撞，否则一辆车的动力学不会影响其他车辆。SynChrono 同步所有代理的运动，但允许它们的动力学分布在计算节点上，而不是将所有动力学包含在一个单一的仿真中。

_图片_: 左侧是一队自主车辆在越野地形上使用通过机器学习开发的策略导航障碍物。右侧是一辆自主车辆在高速公路环境中进行变道操作。

## 代理同步 {#syn_agent_sync}

一个“典型”的 Chrono 系统（例如使用 `Chrono::Vehicle` 的系统）的动力学是通过按某个时间步长 `Δt` 向前推进仿真来处理的，在每个时间步长中，为 `ChSystem` 中的每个实体计算新的状态。在 SynChrono 中情况仍然如此，只是每个仿真节点处理自己的 `ChSystem`，并且这些独立的系统必须定期同步。情况如下面的图所示：

<img src="http://www.projectchrono.org/assets/manual/synchrono/syn-timestep-heartbeat.png" width="600" />

每个节点以相同的恒定时间步长向前推进时间。一些节点可能比其他节点在更少的实际时间内完成它们的时间步长，这可能是因为它们有更多的处理能力、更简单的系统，或其他各种原因。然而，在仿真中经过一定数量的时间步长后，称为心跳，所有节点将同步它们的当前状态。在心跳之间，节点的 `ChSystem` 中的僵尸代理不会更新，并且将保持静止，直到达到心跳并将更新的状态信息应用于 `ChSystem`。

接下来我们解释在每个心跳中具体传递了什么（[状态信息](#syn_state_info)），这些数据是如何格式化的（[FlatBuffers](#syn_flatbuffers)），以及数据是如何在节点之间传递的（[通信类型](#syn_communication)）。

### 状态信息 {#syn_state_info}

在每个心跳中传递的状态信息是特定于每种类型的代理的，它应该是构建另一个节点世界中的僵尸代理所需的最小信息。对于车辆代理，我们需要知道两件事：

- 僵尸代理的外观
- 僵尸代理的位置

“僵尸” _长什么样_，是通过指定车轮数量以及用于车身和车轮的网格文件来确定的，这仅在仿真开始时进行一次。而“僵尸” _在哪里_，则会在每个心跳周期进行通信，内容包括车辆质心的位置和朝向（位姿），以及每个车轮各自的位姿。

<img src="http://www.projectchrono.org/assets/manual/synchrono/synchrono_vehicle_synchronization.png" width="600" />

### FlatBuffers {#syn_flatbuffers}

为了在节点之间传递状态信息，我们需要将每个代理的数据从 C++ 对象转换为一系列字节，这些字节将在节点之间传输。[FlatBuffers](https://google.github.io/flatbuffers/) 是一个处理数据序列化和反序列化的库。

任何将被同步的代理都必须有一个 flatbuffers 模式（见下例），该模式定义了它们的状态数据的格式，以及一个使用该模式将数据打包和解包到 C++ 类中的相应类。

````protobuf
// 示例 flatbuffers 模式（见 Agent.fbs 和 Utils.fbs）

table Pose {
  pos:Vector;
  rot:Quaternion;

  // more details omitted...
}

table State {
  time:double;

  chassis:Pose;

  wheels:[Pose];
}
````

## 通信类型 {#syn_communication}

在节点达到心跳并使用 FlatBuffers 打包数据后，`SynCommunicator` 负责将这些二进制数据发送到仿真中的所有其他节点以供使用。目前有两种类型的通信器，一种基于消息传递接口 (MPI)，另一种基于数据分发服务 (DDS)，但只要它们能够处理在仿真中所有节点之间交换数据的任务，就可以定义其他类型的通信器。

### 消息传递接口 (MPI) {#syn_mpi}

使用 MPI 进行同步是通过两个 MPI 调用来完成的。虽然许多类型的代理将发送固定大小的消息（例如车辆），但其他类型（如可变形地形）则不会。因此，节点不会立即知道它们需要多少空间来接收传入的状态数据。MPI 同步使用第一次调用来确定每个节点需要多少空间来存储其状态数据，然后在节点分配好接收空间后，使用第二次调用来收集这些数据。更多细节请参见手册中的 [MPI 同步部分](@ref state_sync_MPI)。

### 数据分发服务 (DDS) {#syn_dds}

同步也可以通过 DDS 来实现。与 MPI 的集体通信不同，DDS 通信是通过一组“主题”进行点对点的，每个节点的状态数据都有一个主题。为了同步状态，每个节点订阅所有其他节点的主题。DDS 利用多线程来处理同时从多个节点发送和接收数据。通常在集群环境之外，DDS 比 MPI 更受欢迎，因为 MPI 可用性较低，而 DDS 提供了更多的通信灵活性，可以使用 UDP 进行通信。更多细节请参见手册中的 [DDS 同步部分](@ref state_sync_DDS)。

## 对其他 Chrono 模块的支持 {#syn_modules}

在 SynChrono 的开发过程中，重点是自主车辆仿真，因此 SynChrono 目前依赖于 Chrono::Vehicle 才能正常运行。虽然这不是一个根本性的限制，但构建 Chrono::Vehicle 不需要额外的依赖，因此这个依赖不应成为负担。

SynChrono 支持通过 Chrono::Irrlicht 和 Chrono::Sensor 模块进行可视化。
