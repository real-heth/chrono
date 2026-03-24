
可视化系统 {#visualization_system}
====================

Chrono 对象——无论是刚体、网格，还是没有底层物理的抽象形状——都可以通过不同的渲染引擎进行渲染和可视化。同时，Chrono 并不绑定于任何特定的渲染引擎，从而允许轻松扩展到其他渲染系统。实际上，提供了各种 [可视化系统](@ref manual_visualization)。

任何可视化系统都继承自一个公共基类——即 @ref chrono::ChVisualSystem "ChVisualSystem"，定义在 **core** 模块中——该基类始终包含指向给定 @ref chrono::ChSystem "ChSystem" 的指针。此绑定允许可视化系统在仿真更新时获得通知，从而能够根据新的刚体位置更新任何可视化资产。可视化系统可能允许同时渲染多个 Chrono 系统。

除了 @ref chrono::ChVisualSystem "ChVisualSystem" 外，Chrono 还提供了广泛的与渲染器无关的 _可视化资产_：每个可视化系统负责将它们转换为特定渲染器的资产。这些 _可视化资产_ 主要由 @ref chrono::ChVisualShape "ChVisualShape" 类表示。

## 视觉形状与模型 {#visual_model_shapes}

向物理对象添加视觉形状（@ref chrono::ChVisualShape "ChVisualShape"）的最简单方法可能只需几行代码：

~~~{.cpp}
    auto visshape = chrono_types::make_shared<ChVisualShapeBox>(20, 1, 20);
    visshape->SetColor(ChColor(0.2f, 0.3f, 1.0f));

    body->AddVisualShape(visshape, ChFramed(ChVector3d(0, -1, 0), QUNIT));
~~~

在这里，我们假设 `body` 是继承自 @ref chrono::ChPhysicsItem "ChPhysicsItem" 的类型，例如 @ref chrono::ChBody "ChBody"。

虽然这种方法非常直接，但它隐藏了 Chrono 中可视化资产的大部分内部结构。实际上，@ref chrono::ChVisualShape "ChVisualShape" 只是整体结构的一部分。

<h4>ChVisualModel</h4>

类型为 @ref chrono::ChVisualModel "ChVisualModel" 的对象负责持有（通过指针）给定对象的所有可视化资产。

一个 @ref chrono::ChVisualModel "ChVisualModel" 对象可以附加到：

+ @ref chrono::ChPhysicsItem "ChPhysicsItem" 或其继承类（最常见的是 \ref chrono::ChBody "ChBody" 或 \ref chrono::fea::ChMesh "fea::ChMesh"），在这种情况下：
  + @ref chrono::ChVisualModel "ChVisualModel" 中包含的可视化资产将自动随对象一起移动；
  + 每当调用 @ref chrono::ChPhysicsItem::AddVisualShape "AddVisualShape()" 时，@ref chrono::ChVisualModel "ChVisualModel" 会在后台自动添加。
+ 直接附加到 @ref chrono::ChVisualSystem "ChVisualSystem":
  + 资产被视为固定在地面上，在仿真过程中不会移动；
  + 必须显式创建一个 @ref chrono::ChVisualModel "ChVisualModel" 并通过调用 @ref chrono::ChVisualSystem::AddVisualModel() "ChVisualSystem::AddVisualModel()" 将其添加到系统中。
  
任何 @ref chrono::ChVisualModel "ChVisualModel" 都包含以下成员以及其他成员：

+ 一组 @ref chrono::ChVisualShape "ChVisualShape" 与其相对 @ref chrono::ChFrame "ChFrame" 的配对，表示形状相对于父对象框架的相对位置；
+ 一组 @ref chrono::ChVisualShapeFEA "ChVisualShapeFEA" 用于表示网格。

尽管始终可以通过 @ref chrono::ChVisualModel::AddShape "ChVisualModel::AddShape()" 方法将视觉形状显式地附加到视觉模型上，但对于大多数普通用户而言，更便捷的方式是直接调用 @ref chrono::ChPhysicsItem::AddVisualShape "ChPhysicsItem::AddVisualShape()" 方法，一键将 ChVisualShape 附加到任意 @ref chrono::ChPhysicsItem "ChPhysicsItem"（例如 \ref chrono::ChBody "ChBody"）上。该方法同样适用于 @ref chrono::ChPhysicsItem::AddVisualShapeFEA "ChPhysicsItem::AddVisualShapeFEA()"。即使在这些情况下，上述命令本质上也是在隐式地将形状添加到底层的 @ref chrono::ChVisualModel "ChVisualModel" 中。

请注意，当附加到 \ref chrono::ChBodyAuxRef "ChBodyAuxRef" 时，参考框架被视为 `REF` 框架，而不是如图所示的 `COG` 框架。

![](http://www.projectchrono.org/assets/manual/pic_ChAsset.png)

<h4>ChVisualShape 和 ChVisualMaterial</h4>

视觉形状继承自 @ref chrono::ChVisualShape "ChVisualShape" 或 @ref chrono::ChVisualShapeFEA "ChVisualShapeFEA"，其类名通常以 ```ChVisualShape____``` 开头。它们通常还包含一个 @ref chrono::ChGeometry "ChGeometry" 对象来描述其几何形状，以及一个或多个 @ref chrono::ChVisualMaterial "ChVisualMaterial"，用于定义该视觉资产的外观属性。

如果用户未向 @ref chrono::ChVisualShape "ChVisualShape" 显式添加 @ref chrono::ChVisualMaterial "ChVisualMaterial"，那么当用户为该形状的任何属性设置非默认值时，系统将自动为其添加一个。当视觉形状与网格（例如 @ref chrono::ChVisualShapeModelFile "ChVisualShapeModelFile"）结合使用时，通常会用到多个材质，因为输入的 OBJ 文件中可能列出了多种不同的材质。

请参阅 @ref chrono::ChVisualShape "ChVisualShape" 参考页面，以全面了解所有可能的派生类。

总之，实现上述示例效果的更严格方法可能是：

~~~{.cpp}
    auto body = chrono_types::make_shared<ChBody>();

    auto vismat = chrono_types::make_shared<ChVisualMaterial>(20, 1, 20);
    vismat->SetDiffuseColor(ChColor(0.2f, 0.3f, 1.0f));

    auto visshape = chrono_types::make_shared<ChVisualShapeBox>(20, 1, 20);
    visshape->SetMaterial(0, vismat);

    auto vismodel = chrono_types::make_shared<ChVisualModel>(20, 1, 20);
    vismodel->AddShape(visshape, ChFramed(ChVector3d(0, -1, 0), QUNIT));

    body->AddVisualModel(vismodel);
~~~

### 教程

请参阅 [demo_IRR_assets](@ref tutorial_demo_irr_assets) 以了解如何将资产应用于刚体。
