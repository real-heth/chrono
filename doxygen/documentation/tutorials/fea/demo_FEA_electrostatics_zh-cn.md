执行静电分析   (demo_FEA_electrostatics.cpp)  {#tutorial_demo_FEA_electrostatics}
===============================================================

本教程介绍如何使用[FEA 模块](group__chrono__fea.html)在给定边界条件下，计算某一区域的静电场解（泊松问题）。四面体网格从 Abaqus 文件中导入。有两个节点集合（边界）施加了高电压，其余区域视为空气。

\include demo_FEA_electrostatics.cpp
