
刚体  {#rigid_bodies}
============

@ref chrono::ChBody "ChBody" 是 Chrono 中所有刚体的基类，因此它具有质量和转动惯量，并且能够在 3D 空间中移动。

![](http://www.projectchrono.org/assets/manual/pic_ChBody.png)

其位置和旋转，以及它们的导数，**始终参考质心 (COM)**，而视觉和碰撞形状则附加到一个 **辅助参考框架** (`Ref`)。  
请注意，在 @ref chrono::ChBody "ChBody" 基类中，COM 和 `Ref` 总是重合的，而只有在 @ref chrono::ChBodyAuxRef "ChBodyAuxRef" 及其派生类中，`Ref` 框架可能放置在其他位置。

类似 @ref chrono::ChBody::GetPos() "GetPos()" / @ref chrono::ChBody::SetPos() "SetPos()"、@ref chrono::ChBody::GetRot() "GetRot()" / @ref chrono::ChBody::SetRot() "SetRot()" 的方法及其导数始终参考 COM 框架。  
辅助框架通过专用方法处理，例如 `[Get|Set]FrameRefTo____` | `[Get|Set]Frame____ToRef`，在适当的情况下使用。

![](http://www.projectchrono.org/assets/manual/pic_ChBodyAuxRef.png)

刚体还可以：

- 如果提供了碰撞模型并且在刚体上启用了碰撞，则参与碰撞（参见 [碰撞](@ref collisions)）；
- 如果提供了可视化模型并且有合适的可视化系统，则进行可视化（参见 [可视化](@ref visualization_system)）；
- 通过 ChLink 对象进行约束（参见 [关节](@ref links)）；
- 通过 ChLoad 对象施加载荷（参见 [载荷](@ref loads)）；
- 用于坐标变换，因为它们本身继承自 ChFrameMoving；

@ref chrono::ChBody "ChBody" 和 @ref chrono::ChBodyAuxRef "ChBodyAuxRef" 类型的刚体 **不自带任何可视化或碰撞模型**，因此用户需要自行指定这些模型，并提供有效的质量和惯性参数。  
然而，如果刚体可以通过 **基本形状** 描述，一组 `ChBodyEasy` 类型的类可以简化此任务，通过计算质量、惯性，并可选择性地创建可视化和碰撞形状：

- @ref chrono::ChBodyEasySphere "ChBodyEasySphere"
- @ref chrono::ChBodyEasyCylinder "ChBodyEasyCylinder"
- @ref chrono::ChBodyEasyBox "ChBodyEasyBox"
- @ref chrono::ChBodyEasyConvexHull "ChBodyEasyConvexHull"
- @ref chrono::ChBodyEasyClusterOfSpheres "ChBodyEasyClusterOfSpheres"

刚体并不是唯一的选择。Chrono 还可以模拟柔性有限元体。请参阅 [FEA 手册](@ref manual_fea) 了解 FEA 功能的描述。

## 使用方法

创建/设置 ChBody 对象通常涉及以下步骤：

1. 创建刚体；
 
   ~~~{.cpp}
      auto mybody = chrono_types::make_shared<ChBody>();
      mybody->SetMass(10);
      mybody->SetInertiaXX( ChVector3d(4,4,4) );
      mybody->SetPos( ChVector3d(0.2,0.4,2) );
      mybody->SetPosDt( ChVector3d(0.1,0,0) );
      my_system.Add(mybody);
   ~~~

2. 可选：添加 [可视化形状](@ref visualization_system)

   ~~~{.cpp}
      auto visshape = chrono_types::make_shared<ChVisualShapeBox>(20, 1, 20);
      visshape->SetColor(ChColor(0.2f, 0.3f, 1.0f));
      mybody->AddVisualShape(visshape, ChFramed(ChVector3d(0, -1, 0), QUNIT));
   ~~~

3. 可选：添加 [碰撞形状和材料](@ref collisions)

   ~~~{.cpp}
      auto collmat = chrono_types::make_shared<ChContactMaterialNSC>();
      auto collshape = chrono_types::make_shared<ChCollisionShapeBox>(collmat, 0.1, 0.2, 0.3);
      mybody->AddCollisionShape(collshape);
      mybody->EnableCollision(true);
   ~~~

请参阅专门的页面了解 [碰撞](@ref collisions) 和 [可视化](@ref visualization_system) 以完成系统的配置。

对于 `ChBodyEasy` 类的刚体，构造函数更丰富：

~~~{.cpp}
auto mySphere = chrono_types::make_shared<ChBodyEasySphere>(4,      // radius
                                                            8000,   // density
                                                            true,   // visualization enabled
                                                            true,   // collision enabled
                                                            collmat // collision material
                                                         );  
my_system.Add(mySphere);
~~~

# 演示示例

参见:
- [demo_CH_buildsystem](https://github.com/projectchrono/chrono/blob/main/src/demos/core/demo_CH_buildsystem.cpp)
- [demo_MBS_crank](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_crank.cpp)
- [demo_MBS_conveyor](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_conveyor.cpp)
