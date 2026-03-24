基于 DDS 和 MPI 的状态同步 {#state_synchronization}
=============================================

\tableofcontents

## 消息传递接口 (MPI) {#state_sync_MPI}

MPI 是一种用于并行计算的标准化消息传递标准。经过 25 年以上的积极开发，MPI 是一个稳健的标准，具有多种实现和广泛的使用，特别是在超级计算集群中。此外，MPI 运行时处理程序设置的许多方面，例如在每个计算资源上启动任务以及选择通信类型，无论是共享内存、InfiniBand、TCP 还是其他。这种广泛的可访问性和在集群环境中的易用性使其成为 SynChrono 的默认选择。

在 MPI 术语中，每个计算资源称为 _rank_，在 SynChrono 中，每个 rank 通常处理一个 `ChSystem`。这个 `ChSystem` 可能有一个或多个车辆代理、可变形地形或其他参与者，MPI rank 负责与所有其他 rank 共享其 `ChSystem` 的状态数据，并接收来自其他 rank 的状态数据。

### SynChrono 实现 {#state_sync_MPI_synchrono}

在 SynChrono 中，基于 MPI 的同步在每个心跳时通过两个 MPI 调用进行。首先，所有 rank 使用 `MPI_Allgather` 通信其消息的长度。在许多情况下，rank 每个心跳发送的消息长度总是相同（对于刚性地形上的车辆就是这种情况），而在其他情况下（例如可变形地形），无法预知消息的长度，因此必须将此信息传达给每个 rank。在 `MPI_Allgather` 之后，每个 rank 执行可变长度的收集操作 `MPI_Allgatherv`，以从所有其他 rank 获取消息数据。

## 数据分发服务 (DDS) {#state_sync_DDS}

DDS 是一种较新的消息传递标准，基于实时发布-订阅 (RTPS) 模式构建。与 MPI 中的 rank-to-rank 通信不同，DDS 中的通信通过发布和订阅的 _topics_ 进行。

有许多 DDS 实现，最流行的是由 [Real-Time Innovations (RTI)](https://www.rti.com/products) 发布的。为了保持 Project Chrono 的开源理念，选择了 [FastDDS](https://github.com/eProsima/Fast-DDS) 作为该接口的首个版本的供应商。

### SynChrono 实现 {#state_sync_DDS_synchrono}

下图说明了通用的 DDS 通信场景。对于 SynChrono，每个参与者对应一个节点，具有单个 ChSystem。数据同步通过发布者和订阅者进行，这些发布者和订阅者在 SynChrono 级别进行了封装，以提供用于传递 FlatBuffer 消息的 SynChrono 特定 API。每个仿真中的代理都有一个唯一的 topic，每个代理管理一个用于共享其数据的发布者以及一个用于接收来自其他 rank 数据的订阅者。在下一层，数据读取器和数据写入器管理每对代理之间的通信。如果仿真中有五个节点，每个代理将有四个数据读取器以接收来自其他节点的数据。

请参见 [这里](https://community.rti.com/static/documentation/connext-dds/5.2.0/doc/manuals/connext_dds/html_files/RTI_ConnextDDS_CoreLibraries_GettingStarted/Content/GettingStarted/An_Introduction_to_.htm) 了解有关 DDS 的更多详细信息。

<img src="http://www.projectchrono.org/assets/manual/synchrono/synchrono_complicated_dds_system.png" alt="DDS System" width=70%>

SynChrono 对 DDS 的使用尽可能保持最小化。[SynChronoManager](@ref chrono::synchrono::SynChronoManager) 拥有对单个 [SynCommunicator](@ref chrono::synchrono::SynCommunicator) 的句柄。类似于 MPI，必须使用上述类创建 [SynDDSCommunicator](@ref chrono::synchrono::SynDDSCommunicator) 以促进消息传递。SynChrono 级别的类封装了 DDS 的概念，并提供访问器或设置器来操作其配置或创建新实体。[SynDDSPublisher](@ref chrono::synchrono::SynDDSPublisher)、[SynDDSSubscriber](@ref chrono::synchrono::SynDDSSubscriber)、[SynDDSTopic](@ref chrono::synchrono::SynDDSTopic) 以及 [更多](group__synchrono__communication__dds.html) 封装了 DDS 的概念，以提供简单的 SynChrono API。
