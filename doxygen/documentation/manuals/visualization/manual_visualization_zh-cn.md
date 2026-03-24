Chrono 可视化 {#manual_visualization}
=================================

Chrono 对象——无论是刚体、网格、粒子，还是没有底层物理的抽象形状——都可以通过不同的渲染引擎进行渲染和可视化。同时，Chrono 并不绑定于任何一个渲染引擎，从而允许轻松扩展到其他渲染系统。

根据系统的复杂性和渲染需求，我们区分两种类型的 _可视化系统_：

+ **Run-Time**: 用于快速和实时渲染场景，通常包括用户界面和关于正在进行的仿真的附加信息：
  * @subpage irrlicht_visualization "Irrlicht 模块"
  * @subpage vsg_visualization "VSG 模块"
+ **Offline/Postprocess**: 用于不适合实时限制的高质量渲染：
  * @subpage blender_visualization "Blender 模块"
  * @subpage povray_visualization "POVRay 模块"

**附加文档**

* [教程](@ref tutorial_root)
