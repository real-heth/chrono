施加载荷   (demo_FEA_loads_static.cpp)  {#tutorial_demo_FEA_loads}
==================================

本教程介绍如何使用 [FEA 模块](group__chrono__fea.html) 为有限元模型施加载荷。

载荷通过ChLoad对象添加。

系统提供了多种即用型的 ChLoad 对象，而本教程也将指导您如何为自定义载荷定义新的 ChLoad 类。

可选地，可以使用 ChLoader 类来自动化执行某些任务，其中最显著的是对分布载荷进行高斯积分。

\include demo_FEA_loads_statics.cpp
