基础悬架示例 (demo_MBS_suspension.cpp)  {#tutorial_demo_suspension}
==========================

模拟一个带有双叉臂悬架的简化车辆，并使用界面上的滑块通过鼠标驱动它。

本教程将介绍如何：

- 使用 ChLinkDistance 表示无质量杆，从而节省计算资源。
- 根据接触区域改变摩擦系数（在此示例中，地面的一半摩擦较低）。
- 使用 Irrlicht 界面系统与模型进行交互。
- 使用 ChLinkSpring 创建弹簧-阻尼器。

\include demo_MBS_suspension.cpp
