
碰撞 {#collisions}
================

Chrono 可以计算和模拟可碰撞对象之间的碰撞——无论是刚体还是有限元网格——允许它们通过接触进行交互。

接触问题包括两个不同的方面：

- **碰撞检测**: 找到当前或未来可能接触的点对；
- **接触公式**: 定义接触形状之间的反作用力。

<h4> 接触公式 </h4>
如 [ChSystem 手册](@ref manual_ChSystem) 所述，Chrono 可以根据接触方法设置两种不同类型的系统：

- \ref chrono::ChSystemNSC "ChSystemNSC" 实现 **非光滑接触** (NSC):
  + 接触被视为硬/刚性约束；
  + 由于没有引入人工刚化项，因此允许使用更长的时间步长；
  + 需要特定的 [VI 求解器](simulation_system.html#solvers)；
  + 只有较新的 \ref chrono::ChSolverADMM "ChSolverADMM" 可以同时处理非光滑接触和有限元；

- \ref chrono::ChSystemSMC "ChSystemSMC" 实现 **光滑接触** (SMC):
  + 接触反作用力是基于物体的相互穿透计算的，并乘以一个顺应性/刚度项（惩罚方法）；
  + 接触刚度是一个人工项，通常与材料刚度经验相关；
  + 需要较短的时间步长，尤其是对于较硬的接触刚度；
  + 不需要 VI 求解器

用户应仔细考虑哪种系统更适合他们的需求，因为时间步长可能相差两到三个数量级。相反，如果没有碰撞发生，这两种系统类型是完全等效的。

<h4> 碰撞检测 </h4>

在 Chrono 中，有两种不同的碰撞系统可用：

+ \ref chrono::ChCollisionSystemBullet "ChCollisionSystemBullet": 一个定制版本的 [Bullet](https://github.com/bulletphysics/bullet3);
+ \ref chrono::ChCollisionSystemMulticore "ChCollisionSystemMulticore": 一个内部多核碰撞引擎（仅在机器上可用 Thrust 时启用）。

在 \ref chrono::ChSystem "ChSystem" 上调用 \ref chrono::ChSystem::SetCollisionSystemType "ChSystem::SetCollisionSystemType" 可以在这两者之间进行选择。例如：

~~~{.cpp}
sys.SetCollisionSystemType(ChCollisionSystem::Type::BULLET);
~~~

每个可碰撞对象都携带一组碰撞形状和材料：

+  \ref chrono::ChBody "ChBody" 通过 \ref chrono::ChCollisionModel "ChCollisionModel" 对象持有其碰撞形状；
+  \ref chrono::fea::ChMesh "ChMesh" 通过 \ref chrono::fea::ChContactSurface "ChContactSurface" 对象持有其碰撞形状；

对于有限元，碰撞对象和属性是通过 \ref chrono::fea::ChContactSurface "ChContactSurface" 及其继承类（例如 \ref chrono::fea::ChContactSurfaceMesh "ChContactSurfaceMesh" 和 \ref chrono::fea::ChContactSurfaceNodeCloud "ChContactSurfaceNodeCloud"）定义的，可以通过以下方式设置：

~~~{.cpp}
auto mcontactsurf = chrono_types::make_shared<ChContactSurfaceMesh>(mysurfmaterial);
my_mesh->AddContactSurface(mcontactsurf);
mcontactsurf->AddFacesFromBoundary(sphere_swept_thickness);  // do this after my_mesh->AddContactSurface
~~~

关于 \ref chrono::ChBody "ChBody" 类的碰撞对象，将在以下章节中进行更详细的讨论。

# 碰撞模型和形状 {#collision_models_shapes}

每个 \ref chrono::ChBody "ChBody"（以及任何其他从 \ref chrono::ChContactable "ChContactable" 派生的对象）都通过一个 \ref chrono::ChCollisionModel "ChCollisionModel" 对象携带其碰撞属性信息。_ChCollisionModel_ 对象可以包含多个 \ref chrono::ChCollisionShape "ChCollisionShape"，每个形状对象都携带一个几何形状对象以及其 [碰撞表面材料](#collision_materials)。

每个 \ref chrono::ChBody "ChBody" 可能包含一个：

+ \ref chrono::ChCollisionModel "ChCollisionModel", 该模型包含（多个）:
 + \ref chrono::ChCollisionShape "ChCollisionShape", 每个形状对象包含:
   + \ref chrono::ChGeometry "ChGeometry"
   + \ref chrono::ChContactMaterial "ChContactMaterial"

类似的结构也可以在 [可视化系统](@ref visualization_system) 中找到。

实际上，正如 Chrono 中的许多其他对象一样，_ChCollisionModel_ 中的项目是通过指针存储的，以便可以轻松地在不同的刚体之间共享它们。这对于 *ChContactMaterial* 对象尤其有用。

为了向 _ChBody_ 对象提供碰撞形状：

~~~{.cpp}
auto body = chrono_types::make_shared<ChBody>();

auto collmat = chrono_types::make_shared<ChContactMaterialNSC>();

auto collshape = chrono_types::make_shared<ChCollisionShapeBox>(collmat, 0.1, 0.2, 0.3);

body->AddCollisionShape(collshape);
body->EnableCollision(true);
~~~

始终记住在 \ref chrono::ChSystem "ChSystem" 中设置给定的碰撞系统类型，例如：

~~~{.cpp}
ChSystemNSC sys;
sys.SetCollisionSystemType(ChCollisionSystem::Type::BULLET);
~~~

可以在碰撞系统上调整其他设置（参见 [碰撞公差](#collision_tolerances)）。

对于最常见的原始对象，提供了一些名为 _ChBodyEasyXXXX_ 的辅助类：\ref chrono::ChBodyEasyBox "ChBodyEasyBox", \ref chrono::ChBodyEasyCylinder "ChBodyEasyCylinder", \ref chrono::ChBodyEasySphere "ChBodyEasySphere", ...  
这些类允许在单个命令中创建带有可视化和碰撞对象的刚体。然而，请注意，虽然可视化对象默认已添加，但碰撞形状并未添加。要启用它，应将适当的参数传递给构造函数，例如：

~~~{.cpp}
auto sphereBody = chrono_types::make_shared<ChBodyEasySphere>(0.05,      // radius size
                                                              1000,      // density
                                                              true,      // visualization?
                                                              true,      // collision?
                                                              collmat);  // contact material
~~~

![](http://www.projectchrono.org/assets/manual/pic_ChCollisionModel.png)

请注意：

- 碰撞形状是相对于 [刚体](@ref rigid_bodies) 的参考框架定义的

- 碰撞形状可以从继承自 \ref chrono::ChCollisionShape "ChCollisionShape" 的众多类中选择：
  - \ref chrono::ChCollisionShapeBox "ChCollisionShapeBox"
  - \ref chrono::ChCollisionShapeSphere "ChCollisionShapeSphere"
  - ...

- 可以向刚体添加多个碰撞形状。然而，复合形状会减慢仿真的碰撞检测阶段。在这种情况下，没有比位于刚体质心的球体更容易处理的几何形状。

- 凹形状的处理依赖于将几何形状分解为凸形状的联合

- 碰撞形状和可视化资产不需要匹配；例如，可以有一个用于渲染的详细可视化形状，而碰撞形状则更简单，以避免仿真减速。

- 避免使用过薄、过扁或总体上导致极端尺寸比的形状

- 要获取作用在刚体上的接触力：\ref chrono::ChBody::GetContactForce() "ChBody::GetContactForce()"，扭矩同理。

# 碰撞族 {#collision_families}

可以定义 _碰撞族_ 以实现选择性碰撞。
例如，你可能不希望 family=2 的对象与 family=4 的对象发生碰撞：

~~~{.cpp}
// default collision family is 0. Change it:
body_b->GetCollisionModel()->SetFamily(2);
body_b->GetCollisionModel()->DisallowCollisionsWith(4);
~~~

目前，Chrono 允许在仿真中使用最多 15 个不同的碰撞族。

# 碰撞表面材料 {#collision_materials}

形状之间的接触受材料的各种属性影响（摩擦、阻尼、内聚、恢复等）。这些属性是为每个形状指定的，通过向 *ChCollisionShape* 提供 \ref chrono::ChContactMaterialNSC "ChContactMaterialNSC" 或 \ref chrono::ChContactMaterialSMC "ChContactMaterialSMC" 对象。

Chrono 可以处理两种不同的接触公式 - 非光滑接触 (**NSC**) 和 光滑接触 (**SMC**) - 每种公式都需要不同的 _表面材料_ 类型以及不同的 \ref chrono::ChSystem "ChSystem" 类型（参见 [ChSystem 手册](@ref manual_ChSystem)）。

<div class="ce-warning"> 
当一个刚体被复制（拷贝构造）或克隆时，ChContactMaterial 被复制的是指针，而不是对象本身。这意味着两个复制的刚体将共享同一个 ChContactMaterial 实例，这意味着对一个对象的材料的任何更改也会反映到所有复制的对象上。
</div>

# 碰撞容差 {#collision_tolerances}

碰撞形状有两个（全局）容差，用于碰撞引擎创建和删除接触，即 **envelope** 和 **margin**：

- 外部 **envelope**（其厚度通过 \ref chrono::ChCollisionModel::SetDefaultSuggestedEnvelope "ChCollisionModel::SetDefaultSuggestedEnvelope" 修改）：当两个碰撞形状 *接近* 接触时，应立即向 *ChSystem* 添加约束方程。*envelope* 参数告诉我们这些形状（或接触对）应该多接近才能触发约束方程的创建。请注意，添加碰撞约束方程 **并不** 意味着反作用力 *已经* 存在，而只是意味着在不久的将来可能发生 **潜在** 碰撞。这允许系统提前捕捉潜在接触，从而降低穿透或不稳定接触的风险。
  + 如果 **太大**：可能会过早添加过多接触，从而增加问题规模（浪费内存和计算时间）；
  + 如果 **太小**：穿透风险增加，如果速度很高或物体厚度很小，物体甚至可能穿过其他物体（隧穿效应）。

- 内部 **margin**（其厚度通过 \ref chrono::ChCollisionModel::SetDefaultSuggestedMargin "ChCollisionModel::SetDefaultSuggestedMargin" 修改）：形状的相互穿透通常是数值问题的来源（积分误差、近似、条件不良的初始条件等）。虽然通常允许少量穿透，但当穿透过大时，碰撞检测算法需要回退到较慢的碰撞检测算法。这个 margin 表示这个阈值。
  + 如果 **太大**：形状看起来过于“圆润”；
  + 如果 **太小**：较慢的算法会过早启动，从而导致性能下降。

仅对 Bullet 引擎可用的附加设置：

- **接触断开阈值**（其值通过 \ref chrono::ChCollisionSystemBullet::SetContactBreakingThreshold "ChCollisionSystemBullet::SetContactBreakingThreshold" 修改）：Bullet 会跟踪前几帧仿真中发生的碰撞。为了清除列表，设置了一个阈值：当形状移动超过该阈值时，它们会从列表中移除。

为了提高碰撞检测的稳定性和性能，碰撞形状最初会按 margin 的量缩小；然后再按相同的量扩展，从而引入一种“圆角效果”。在下图中，两个蓝色形状最初是尖角的盒子，但经过处理后，它们的角变得圆润，圆角半径就是碰撞 margin。

![](http://www.projectchrono.org/assets/manual/pic_margins.png)

一个使用示例：

~~~{.cpp}
ChCollisionModel::SetDefaultSuggestedEnvelope(0.001);
ChCollisionModel::SetDefaultSuggestedMargin(0.0005);
ChCollisionSystemBullet::SetContactBreakingThreshold(0.001); // only for Bullet collision systems
~~~

<div class="ce-info">
包络（Envelope）和边距（margin）的设置将影响在调用相关函数**之后**创建的碰撞形状。

*SetDefaultSuggestedEnvelope* 和 *SetDefaultSuggestedMargin* 可以被多次调用，但一旦碰撞模型被填充了碰撞形状，包络和边距就无法更改。
</div>

# 碰撞回调 {#collision_callbacks}

虽然接触仿真由 Chrono 完全自主处理，但用户仍然可以通过适当的回调与接触仿真进行交互，每当发现接触时，Chrono 会自动调用这些回调。用户需要通过继承 \ref chrono::ChCollisionSystem::BroadphaseCallback "BroadphaseCallback" 或 \ref chrono::ChCollisionSystem::NarrowphaseCallback "NarrowphaseCallback" 类来创建自己的特定实现，然后通过 \ref chrono::ChCollisionSystem::RegisterBroadphaseCallback "RegisterBroadphaseCallback" 和 \ref chrono::ChCollisionSystem::RegisterNarrowphaseCallback "RegisterNarrowphaseCallback" 方法注册该新类的实例。

请参阅 [demo_MBS_callbackNSC.cpp](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_callbackNSC.cpp) 和 [demo_MBS_callbackSMC.cpp](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_callbackSMC.cpp) 以获取更多详细信息。

# 示例

有关进一步的指导，请参见：
- [demo_MBS_bricks](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_bricks.cpp)
- [demo_MBS_collisionNSC](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_collisionNSC.cpp)
- [demo_MBS_friction](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_friction.cpp)