VSG 可视化（实时） {#vsg_visualization}
==================================

基于 [VulkanSceneGraph (VSG)](https://vsg-dev.github.io/vsg-dev.io/)，该实时引擎目前正在积极开发中，旨在为 Chrono 可视化提供更先进和现代的可视化选项。

有关更多信息，请参阅 @ref chrono::vsg3d::ChVisualSystemVSG "vsg3d::ChVisualSystemVSG" 类。

一个典型的使用 \ref chrono::vsg3d::ChVisualSystemVSG "vsg3d::ChVisualSystemVSG" 的示例，包括灯光、摄像机和背景，如下所示：

~~~{.cpp}
    auto vis = chrono_types::make_shared<ChVisualSystemVSG>();
    vis->AttachSystem(&sys);
    vis->SetWindowSize(ChVector2i(1200, 800));
    vis->SetWindowPosition(ChVector2i(100, 300));
    vis->SetWindowTitle("VSG Demo");
    vis->SetUseSkyBox(true);
    vis->AddCamera(ChVector3d(-8, 8, -16));
    vis->SetCameraAngleDeg(40);
    vis->SetLightIntensity(1.0f);
    vis->SetLightDirection(1.5 * CH_PI_2, CH_PI_4);
    vis_vsg->SetShadows(true);
~~~

[Chrono::VSG 参考](group__vsg__module.html)

[Chrono::VSG 安装指南](module_vsg_installation.html) 

<img src="http://www.projectchrono.org/assets/manual/vsg_visualization.png" class="img-responsive">
