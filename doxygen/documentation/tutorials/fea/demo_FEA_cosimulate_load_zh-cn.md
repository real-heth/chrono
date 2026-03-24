对网格施加协同仿真载荷  (demo_FEA_cosimulate_load.cpp)     {#tutorial_demo_FEA_cosimulate_load}
================================

本教程介绍如何使用[FEA 模块](group__chrono__fea.html)导入带有 3D 四面体网格的 .INP Abaqus 网格，并对来自外部进程的表面施加载荷。

此处的外部进程仅通过同一 .cpp 文件中的一个函数进行模拟；但在协同仿真环境中，它可能是一个外部进程或程序（例如 CFD 软件），该程序接收来自 Chrono 的 3D 网格，并将流体作用力反馈给 Chrono。

\include demo_FEA_cosimulate_load.cpp
