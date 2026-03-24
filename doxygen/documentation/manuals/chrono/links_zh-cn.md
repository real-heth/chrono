
连接件 {#links}
========

在 Chrono 中，一个物体的运动可以相对于另一个物体或地面进行约束。这是通过使用 ChLink 类来实现的。从 @ref chrono::ChLink "ChLink" 类派生出了多种类型的连接件，其中最显著的是以下几类的派生类：

- @ref chrono::ChLinkMate "ChLinkMate": 更高效，但不实现限制，只有少数可以施加运动；
- @ref chrono::ChLinkLock "ChLinkLock": 更通用，相对运动可以在边界内受限，力和相对位移可以轻松获取；可以指定对相对于刚体参考系 _移动_ 的点的约束；
- @ref chrono::ChLinkMotor "ChLinkMotor": ChLinkMate 派生的关节，包含驱动功能。

因此，一些 ChLinkMate 和 ChLinkLock 派生类可能会重叠。后者更灵活，前者更高效。因此，一般应优先使用 ChLinkMate 版本。

![](http://www.projectchrono.org/assets/manual/pic_ChLink.png)

一些关于整体结构的基本知识可能有助于更好地使用这些类：

- 连接件通常引用一对 @ref chrono::ChMarker "ChMarker"，但在连接件初始化期间，这些标记可以自动添加到刚体上；见下文；
- 每个连接件都有一个参考/主框架；反作用力和轴方向是相对于该参考标记计算的；
- 设置标记/刚体的初始位置为可行位置是值得的；
- 当存在约束时，通常有必要将求解器参数设置为更精细的值；见 [求解器](@ref solvers)。

# ChLink 快速参考

| 自由度 | 任务 | 描述 | 类 |
| :-: | :--- | :-- | :-- |
| 6 | 固定 | 固定位置和旋转 | @ref chrono::ChLinkMateFix "ChLinkMateFix" <br> @ref chrono::ChLinkLockLock "ChLinkLockLock" |
| 6\|3 | 衬套 | 线性顺应 + 可选球形关节 | @ref chrono::ChLinkBushing "ChLinkBushing" |
| 5 | 转动 | 允许绕 Z 轴旋转 | @ref chrono::ChLinkMateRevolute "ChLinkMateRevolute" <br> @ref chrono::ChLinkLockRevolute "ChLinkLockRevolute" <br> @ref chrono::ChLinkRevolute "ChLinkRevolute" |
| 5 | 平移 | 允许沿 Z 轴平移  | @ref chrono::ChLinkMatePrismatic "ChLinkMatePrismatic" <br> @ref chrono::ChLinkLockPrismatic "ChLinkLockPrismatic" |
| 4 | 万向节 | 万向节（沿 X 和 Y 轴） | @ref chrono::ChLinkUniversal "ChLinkUniversal" |
| 4 | 转动+平移 | 允许沿 X 轴平移和绕 Z 轴旋转 | @ref chrono::ChLinkLockRevolutePrismatic "ChLinkLockRevolutePrismatic" |
| 4 | Oldham | Oldham 关节；不固定轴位置 | @ref chrono::ChLinkLockOldham "ChLinkLockOldham" |
| 4 | Cylindrical | Z 轴共线  | @ref chrono::ChLinkMateCylindrical "ChLinkMateCylindrical" <br> @ref chrono::ChLinkLockCylindrical "ChLinkLockCylindrical" |
| 3 | Spherical | 固定平移 | @ref chrono::ChLinkMateSpherical "ChLinkMateSpherical" <br> @ref chrono::ChLinkLockSpherical "ChLinkLockSpherical" |
| 3 | Planar | XY 平面共面 | @ref chrono::ChLinkLockPlanar "ChLinkLockPlanar" <br> @ref chrono::ChLinkMatePlanar "ChLinkMatePlanar" |
| 3 | Aligned | 固定旋转 | @ref chrono::ChLinkLockAlign "ChLinkLockAlign" |
| 2 | Revolute+Spherical | 固定相对于旋转轴的距离（旋转轴的 Z 轴） | @ref chrono::ChLinkRevoluteSpherical "ChLinkRevoluteSpherical"|
| 2 | Revolute+Align | 允许相对于旋转框架的平移 | @ref chrono::ChLinkRevoluteTranslational "ChLinkRevoluteTranslational" |
| 2 | Point on a Plane | 阻止 Z 方向的平移 | @ref chrono::ChLinkMateDistanceZ "ChLinkMateDistanceZ" <br> @ref chrono::ChLinkLockPointPlane "ChLinkLockPointPlane" |
| 2 | Point on a Line | 点属于给定的直线；可以自由旋转 | @ref chrono::ChLinkLockPointLine "ChLinkLockPointLine" <br> @ref chrono::ChLinkLockPointSpline "ChLinkLockPointSpline" |
| 2 | Parallel | Z 轴平行 | @ref chrono::ChLinkMateParallel "ChLinkMateParallel" <br> @ref chrono::ChLinkLockParallel "ChLinkLockParallel" |
| 2 | Orthogonal | X 和 Y 轴保持正交；Z 轴对齐 | @ref chrono::ChLinkMateOrthogonal "ChLinkMateOrthogonal" <br> @ref chrono::ChLinkLockPerpend "ChLinkLockPerpend" |
| 1 | Distance | 极坐标距离固定 | @ref chrono::ChLinkDistance "ChLinkDistance" |
| 1 | Rack-Pinion | 将小齿轮 Z 轴的旋转与齿条 X 轴耦合 | @ref chrono::ChLinkMateRackPinion "ChLinkMateRackPinion" |
| 1 | Pulley | Z 轴旋转耦合；滑轮特定功能 | @ref chrono::ChLinkLockPulley "ChLinkLockPulley" |
| 1 | Gear | Z 轴旋转耦合；齿轮特定功能 | @ref chrono::ChLinkLockGear "ChLinkLockGear" |
| 0 | Free | 无约束 | @ref chrono::ChLinkLockFree "ChLinkLockFree" |

此外，如果一个刚体需要固定在全局参考系中，并且不关心反作用力，可以使用 @ref chrono::ChBody "SetFixed()" 方法；这也将从系统中消除状态。

## 执行器

| ConDOF | MotDOF | 任务 | 描述 | 类 |
| :-: | :-: | :--- | :-- | :-- |
| 0\|3\|5 | 1 | 线性执行器 | 在框架之间施加线性力\|速度\|位置；<br>可选地在其端点添加无\|棱柱\|球形关节<br>可以与一维 @ref chrono::ChShaft "ChShaft" 配对 | @ref chrono::ChLinkMotorLinear "ChLinkMotorLinear" 及其派生类 |
| 0\|3\|5 | 1 | 旋转执行器 | 在框架之间施加扭矩\|速度\|位置；<br>可选地在其端点添加无\|旋转\|圆柱\|Oldham 关节<br>可以与一维 @ref chrono::ChShaft "ChShaft" 配对 | @ref chrono::ChLinkMotorRotation "ChLinkMotorRotation" 及其派生类 |
| 0 | 1 | 线性弹簧+阻尼器 | 弹簧+阻尼器，取决于框架距离；也可以使用自定义力 | @ref chrono::ChLinkTSDA "ChLinkTSDA" |
| 0 | 1 | 旋转弹簧+阻尼器 | 弹簧+阻尼器，取决于沿 Z 轴的框架旋转；也可以使用自定义力 | @ref chrono::ChLinkRSDA "ChLinkRSDA" |

此外，@ref chrono::ChLinkLockLock "ChLinkLockLock" 也可以用于在刚体之间施加运动约束。

## 使用方法

在许多情况下，无需显式创建两个标记。可以在调用 ChLink::Initialize() 函数时传递两个刚体和约束的位置。该函数将自动创建两个标记并将其添加到刚体中。

或者，可以显式创建两个标记，将它们添加到两个刚体中，然后通过传递这两个标记来调用 ```Initialize()```。

通常，该过程包括以下步骤：

1. 创建一个 @ref chrono::ChLink "ChLink" 派生类的链接（例如 @ref chrono::ChLinkLockSpherical "ChLinkLockSpherical"）

   ~~~{.cpp}
   auto mylink =  chrono_types::make_shared<ChLinkLockSpherical>();
   ~~~

2. 使用 ```mylink->Initialize(…)``` 连接两个刚体；不同的链接可能接受不同的参数。有关详细信息，请参阅特定链接的文档。

   ~~~{.cpp}
   mylink->Initialize(pendulumBody,   // the 1st body to connect
                      floorBody,      // the 2nd body to connect
                      ChFramed(ChVector3d(1, 0, 0),
                               QuatFromAngleAxis(-CH_PI / 2, VECT_X)
                               )
                      );
   ~~~

3. 将链接添加到 ChSystem

   ~~~{.cpp}
   my_system.Add(mylink);
   ~~~

4. 可选：设置链接属性

# 示例

另请参见：

- [demo_MBS_fourbar](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_fourbar.cpp)
- [demo_MBS_suspension](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_suspension.cpp)
