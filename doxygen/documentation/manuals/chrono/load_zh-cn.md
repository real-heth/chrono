
载荷 {#loads}
========

Chrono 提供了多种将载荷施加到对象的选项。

顾名思义，可以承载载荷的对象是那些继承自 @ref chrono::ChLoadable "ChLoadable" 类的对象；例如 @ref chrono::ChBody "ChBody"、有限元和节点或 @ref chrono::ChShaft "ChShaft"。

载荷可以通过不同的方法施加到这些对象上：

+ @ref chrono::ChForce "ChForce":
  - 仅适用于 @ref chrono::ChBody "ChBody"
  - 相对于某个预定义的参考系（刚体或世界）施加力或力矩；
+ @ref chrono::ChLoad "ChLoad" + @ref chrono::ChLoader "ChLoader":
  - 适用于任何继承自 @ref chrono::ChLoadable "ChLoadable" 的对象；
  - 具体实现必须通过 @ref chrono::ChLoader "ChLoader" 对象提供；
  - 与 Chrono 系统耦合更紧密；
  - 需要计算广义载荷；
+ 继承自 @ref chrono::ChLoadCustom "ChLoadCustom"|@ref chrono::ChLoadCustomMultiple "ChLoadCustomMultiple" 的载荷：
  - 可以施加到一个或多个 @ref chrono::ChLoadable "ChLoadable" 对象上；
  - 是施加到对象对上的首选选择；
  - 提供了多个预定义类，简化了广义载荷的编写。

虽然在前面的列表中没有明确提到，但 @ref chrono::ChLinkTSDA "ChLinkTSDA"|@ref chrono::ChLinkRSDA "ChLinkRSDA" 也可以执行类似的工作，包括为广义力提供雅可比矩阵，或者通过提供自定义函数对象（@ref chrono::ChLinkTSDA::ForceFunctor "ChLinkTSDA::ForceFunctor"|@ref chrono::ChLinkRSDA::TorqueFunctor "ChLinkRSDA::TorqueFunctor"）甚至适当的常微分方程（仅 @ref chrono::ChLinkTSDA::ODE "ChLinkTSDA::ODE"）来实现一些高级内部动力学。

其他简化的方法，仅限于 _ChBody_，允许通过使用 @ref chrono::ChBody::AccumulateForce() "AccumulateForce()" 和 @ref chrono::ChBody::AccumulateTorque() "AccumulateTorque()" 来累积力。

可以通过 @ref chrono::ChBody::GetAppliedForce() "GetAppliedForce()" 获取给定 _ChBody_ 的总力贡献，扭矩同理。

对于有限元节点，类似于 @ref chrono::ChForce "ChForce" 对 @ref chrono::ChBody "ChBody" 的作用，可以通过 @ref chrono::fea::ChNodeFEAxyz::SetForce() "ChNodeFEAxyz::SetForce()" 直接向节点施加力。然而，在这种情况下，选项更加有限，因为力被表示为一个简单的 @ref chrono::ChVector3 "ChVector3"，因此总是假定为常数并以绝对参考系表示。@ref chrono::fea::ChNodeFEAxyzrot "ChNodeFEAxyzrot" 类还实现了 @ref chrono::fea::ChNodeFEAxyzrot::SetTorque() "ChNodeFEAxyzrot::SetTorque()"。

一些更特殊的类已被排除在此列表之外：请查看 @ref chrono::ChLoadBase "ChLoadBase" 以全面了解 Chrono 中的载荷类。

### ChForce

@ref chrono::ChForce "ChForce" 可以直接施加到 @ref chrono::ChBody "ChBody" 上，方法如下：

~~~{.cpp}
  auto force = chrono_types::make_shared<ChForce>();
  body->AddForce(force)

  // 在调用 AddForce 之后
  force->SetMforce(10);
~~~

请注意：

- 使用 `body->AddForce(force)` 而不是 `force->SetBody(body)`：后者是不够的，因为 _ChForce_ 不会被 _ChSystem_ 考虑；
- 始终在调用 `body->AddForce(force)` 之后调用 `ChForce` 方法

施加点、方向、位置和模量可以通过常数值或通过 [ChFunctions](@ref ChFunction_objects) 设置。参考系可以是相对于刚体的，也可以是绝对的，但不能设置为通用框架。

### ChLoad 及其继承类

这些载荷集合允许最大程度的自由度和与 Chrono 系统的耦合。

与 @ref chrono::ChForce "ChForce" 相反，这些其他 _ChLoad_ 需要引入一个 @ref chrono::ChLoadContainer "ChLoadContainer" 才能添加到系统中。例如：

~~~{.cpp}
  auto load_container = chrono_types::make_shared<ChLoadContainer>();
  sys.Add(load_container);

  auto load_bb = chrono_types::make_shared<ChLoadBodyBodyTorque>(bodyA, bodyB, ChVector3d(0,10.0,0), false);
  load_container->Add(load_bb);
~~~

对于 @ref chrono::ChLoad "ChLoad" 的情况，用户需要提供一个预定义的 @ref chrono::ChLoader "ChLoader" 对象，或者编写自己的。请参考每个单独的 _ChLoader_ 的文档以了解其用法。此方法考虑施加到单个对象的载荷。

类似的载荷集包括那些继承自 @ref chrono::ChLoadCustom "ChLoadCustom" 和 @ref chrono::ChLoadCustomMultiple "ChLoadCustomMultiple" 的载荷。尽管它们的特性与 @ref chrono::ChLoad "ChLoad" 类型相似，且使用场景可能存在大量重叠，但它们通常提供了一组更广泛的预定义类，可能更符合用户的需求。

这些更高级的方法允许与 Chrono 系统进行更紧密的耦合，还可以引入整个刚度矩阵块（参见 @ref chrono::ChLoadBodyBodyBushingGeneric "ChLoadBodyBodyBushingGeneric" 等），提供雅可比矩阵等。这需要实现一些额外的代码。
