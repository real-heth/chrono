履带总成 {#tracked_assembly}
==================================

Chrono::Vehicle 的履带总成是一个包含车辆子系统的容器，包括链轮、带张紧器的惰轮，可选的一组滚轮、若干悬挂机构，以及任意数量的履带板机构。

为了消除履带板体一致初始化的负担，履带总成子系统提供了自动将履带组装到链轮、惰轮、车轮和任何现有滚轮周围的算法支持。针对不同的链轮轮廓和相关履带板模型，提供了专门的履带总成及相应的组装例程。

Chrono::Vehicle 中的各种履带总成模板在所使用的履带板类型上有所不同：

- [ChTrackAssemblySinglePin](@ref chrono::vehicle::ChTrackAssemblySinglePin)
- [ChTrackAssemblyDoublePin](@ref chrono::vehicle::ChTrackAssemblyDoublePin)
- [ChTrackAssemblyBandBushing](@ref chrono::vehicle::ChTrackAssemblyBandBushing)
- [ChTrackAssemblyBandANCF](@ref chrono::vehicle::ChTrackAssemblyBandANCF)
