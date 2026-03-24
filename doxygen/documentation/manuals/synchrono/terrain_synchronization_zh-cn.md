可变形地形同步 {#terrain_synchronization}
=================================

SynChrono 通过 Chrono::Vehicle 的 [土壤接触模型 (SCM) 实现](@ref vehicle_terrain_scm) 提供可变形地形的状态同步。这允许多辆车辆在越野驾驶时相互作用，并与彼此造成的车辙和地形变形进行交互。

<img src="http://www.projectchrono.org/assets/manual/vehicle/terrain/SCM_mesh_refinement.png" width="600" />

## SCM 地形背景 {#terrain_sync_background}

更多关于 SCM 地形物理的细节可以在 Chrono::Vehicle 的 [地形参考指南](@ref vehicle_terrain_scm) 中找到。对于同步的目的，SCM 地形的关键特性如下：

- 土壤由整数网格表示，只有被变形的节点会保存在哈希表中
- 土壤节点仅在垂直方向上发生位移
- 没有土壤历史记录 - 垂直位移捕捉了完整的土壤状态

## 同步地形状态 {#terrain_sync_mechanics}

为了在两个系统之间同步状态，需要传递的只是一个 `(int x, int y)` 的列表，表示被变形的节点，以及一个 `double z` 的列表，表示相应节点的当前高度。在地形物理更新的时间步过程中，哪些节点被变形以及它们的高度的列表是地形系统已经计算出的一个容易获得的副产品。由于这个列表将在每个物理时间步重置，但 SynChrono 只会在每个心跳发送消息，因此每个时间步变形的节点会合并到 `SynSCMTerrainAgent` 类拥有的地图中，该地图只在每个心跳重置一次。通过 FlatBuffer 消息发送的消息是一个 `int x, int y, double z` 的向量，每个元素表示在前一个心跳期间被变形的节点。

当在同步节点上接收到地形状态信息时，通过 [vehicle::SCMTerrrain::SetModifiedNodes](@ref chrono::vehicle::SCMTerrain::SetModifiedNodes) 函数立即应用更新，地形类在内部处理应用这些外部节点更新。

## 注意事项 {#terrain_sync_caveats}

关于实现的一些附加说明：

- 代码中没有任何机制可以防止用户在不同的计算节点上错误地设置不同的土壤属性或尺寸。
- 车辆不应在同一心跳期间修改相同的节点——实际应用到地形的更新将是随机的。这不应比车辆不碰撞的正常要求更严格，因为唯一被修改的节点是在车辆车轮下方的节点。
