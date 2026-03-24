Irrlicht 可视化（运行时） {#irrlicht_visualization}
==================================

[Irrlicht](https://irrlicht.sourceforge.io/) 渲染引擎长期以来一直是 Chrono 实时应用程序的主要渲染系统。因此，Irrlicht 引擎的 \ref chrono::irrlicht::ChVisualSystemIrrlicht "irrlicht::ChVisualSystemIrrlicht" 包装器目前在所有渲染引擎中提供了最广泛的功能集，包括关于底层问题规模、仿真选项和时间的实时信息，各种标志以启用链接框架和力、接触反应等的渲染。

此外，MODAL 模块依赖 Irrlicht 来渲染模态形状。

\ref chrono::irrlicht::ChVisualSystemIrrlicht "irrlicht::ChVisualSystemIrrlicht" 负责创建可视化窗口，包括信息面板（按钮 `i`）。

一个典型的 \ref chrono::irrlicht::ChVisualSystemIrrlicht "irrlicht::ChVisualSystemIrrlicht" 使用示例，包括最小的照明、摄像机和背景设置，如下所示：

~~~{.cpp}
    auto vis = chrono_types::make_shared<ChVisualSystemIrrlicht>();
    vis->AttachSystem(&sys);
    vis->SetWindowSize(1024, 768);
    vis->SetWindowTitle("Irrlicht Demo");
    vis->Initialize();
    vis->AddLogo();
    vis->AddSkyBox();
    vis->AddCamera(ChVector3d(0, 8, 6));
    vis->AddTypicalLights();
~~~

有关更多信息，请参阅 @ref chrono::irrlicht::ChVisualSystemIrrlicht "irrlicht::ChVisualSystemIrrlicht" 文档。

[Chrono::Irrlicht 参考](group__irrlicht__module.html)

[Chrono::Irrlicht 安装指南](module_irrlicht_installation.html) 

<img src="http://www.projectchrono.org/assets/manual/irrlicht_visualization.png" class="img-responsive">
