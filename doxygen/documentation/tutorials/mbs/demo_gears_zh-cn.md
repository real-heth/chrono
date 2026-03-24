齿轮约束示例 (demo_MBS_gears.cpp)  {#tutorial_demo_gears}
==========================

创建由皮带轮、直齿轮、锥齿轮组成的传动装置。

提供了自定义简化约束，以避免模拟齿轮齿之间的接触。

本教程展示了如何：

- 使用 ChLinkLockGear 约束在 3D 空间中表示简化的齿轮交互
- 使用 ChLinkLockPulley 约束在 3D 空间中建模简化的皮带轮
- 使用 ChCoordsys 和 ChFrame 类管理参考系的旋转
- 在两个部件之间创建电机  

\include demo_MBS_gears.cpp
