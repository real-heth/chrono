曲柄滑块机构示例 (demo_MBS_crank.cpp)  {#tutorial_demo_crank}
==========================

将 Chrono 集成到 Irrlicht 3D 可视化库中的最简单方法：实际上，关节的坐标只是用作简单多边形线的端点，这些线在每一帧重绘时绘制在 3D 空间中，以显示滑块-曲柄机构的非常简化的“骨架”。该示例还演示了如何：

- 创建约束和“引擎”对象

- 创建一个实时应用程序，其中 Chrono 根据 CPU 的速度调整积分步长。

\include demo_MBS_crank.cpp
