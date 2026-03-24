Chrono::Blender {#introduction_chrono_blender}
==========================

Chrono::Blender 是一款针对广泛使用的 [Blender](http://www.blender.org) 建模与渲染软件的插件工具。得益于该插件，你可以生成高质量、照片级逼真的 Chrono 仿真动画。

![](http://projectchrono.org/assets/manual/blender_addin.jpg)

这要求你先构建 [后处理模块](@ref module_postprocess_installation)，以便在运行仿真时，能够使用 ChBlender 类将所有 Chrono 视觉资源导出到一个目录下的 .py 文件中。每个时间步都会生成一个 .py 文件。

然后你可以打开 Blender，从 **File/Import../Chrono** 菜单中导入这些文件，你会发现所有的 Chrono 资源都被导入到 Blender 的 GUI 中。此时，你可以修改对象，添加灯光、摄像机、效果，进行高质量渲染、制作视频等，就像在 Blender GUI 中常规操作一样。

## 概览

这是对该插件主要功能的简要概述。如果你想在你的电脑上测试以下功能，首先必须执行以下步骤：

- 在 Blender 中安装插件

- 如果尚未启用，请在 CMake 中打开 *CH_ENABLE_MODULE_POSTPROCESSING* 并重新构建 Chrono

- 构建 *demo_POST_*（同时，可以查看源代码 *demo_POST_blender.cpp* 中的注释以了解更多信息）

- 运行 **demo_POST_blender.exe**

执行可执行文件后，你将在可执行文件目录下的子目录 '/DEMO_OUTPUT/BLENDER' 中找到新文件。
这些文件包括：

- **exported.assets.py**, 该文件包含所有全局设置，如渲染尺寸等，以及在仿真过程中保持不变的所有资源的定义，即从时间步到时间步不变化的形状，并且为了性能原因只保存一次。
  
- **output**, 一个目录，包含 *state00001.py*, *state00002.py* 等文件，这些文件包含每个时间步资产位置的信息，以及非持久性资产的定义，即从时间步到时间步变化的形状。
  
- **anim**, 一个目录，可选地用于在 Blender 中渲染动画后存储 .png 或 .jpg 文件。

你也可以在自己的项目中启用这种类型的后处理：如果你查看 *demo_POST_blender.cpp*，你可以学习如何操作。这非常简单。Blender 后处理能够将许多 Chrono 可视化资产转换为 Blender 对象，存储在 .py 文件中，而无需大量编程工作。

### 在 Blender 中加载仿真

- 打开 Blender

- 使用菜单 **File/Import../Chrono_import**

- 选择你使用 Chrono 可执行文件生成的 *exported.assets.py* 文件
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_10.jpg)
  
- 你会立即在 Blender 3D 视图中看到对象：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_20.jpg)

- 现在移动时间滑块，你会看到对象在 3D 视图中移动（在这个演示中，一些小球会落到地面上）。
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_30.jpg)

  背后发生了什么？基本上，每当 Blender 更改帧编号时，都会加载相应的文件 stateNNNNNN.py。
  这意味着你可以在 Blender 中渲染动画。
  
- 在 3D 视图的右上角，有一组图标用于更改 *Viewport shading*：默认的 *Solid* 模式不适合显示复杂的颜色和纹理，因此我们将其切换到 *Rendered* 模式，点击相应的图标：

  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_40.jpg)
  
- 有用的提示：Blender 中的默认渲染器是 *Evee*，它非常快速但不具备照片级真实感，即你可以用于大规模仿真，就像使用 Paraview 等工具一样，但如果你追求最高的照片级真实感，我们建议启用 *Cycles* 渲染器，如下图所示：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_50.jpg)

- 此时，你应该能够看到类似这样的效果：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_60.jpg)
  
  注意，你可以像处理常规 Blender 场景一样添加额外的摄像机、对象等。例如，在这个演示中，我们从顶部添加了一个区域光源，就像一个大型柔光箱，功率为 1800W。

### 编辑 Chrono 对象

是否可以向从 Chrono 保存的网格添加细节？是否可以更改它们的颜色或纹理？在许多情况下，这可以直接从 Blender GUI 中完成。

- 首先，让我们研究 Chrono 仿真是如何转换为 Blender 对象的：查看 *Outliner* 面板，其视图层列表将显示如下内容：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_70.jpg)

你会注意到四个集合：
  
  - **chrono_cameras** 包含由 Chrono 导出器生成的视频摄像机，如果你使用了此功能，否则为空。*此集合中的摄像机不能被编辑*

  - **chrono_assets** 包含在仿真过程中不会变化的资产，如网格。*这些对象可以被编辑、纹理化等，随你喜欢!!!*
  
  - **chrono_frame_assets** 包含在仿真过程中会变化的资产，如网格。*这些对象不能被编辑*

  - **chrono_frame_objects** 包含要渲染并在 3D 视图中可见的对象：这些对象是 *chrono_assets* 或 *chrono_frame_assets* 中资产的实例。其理念是，你可能有一个包含 100 个相同部件的仿真（即 100 个 ChBody 对象共享相同的 ChVisualShape，在 .cpp 源文件中），因此在 Blender 中创建一个网格并在 100 个实例中共享它是明智的，这些实例具有不同的位置和旋转。这个概念由 Chrono 的后处理模块和 Blender 插件自动管理。*这些对象不能被编辑*。

- 假设我们想要更改地板的纹理，这是从 Chrono 保存的，而不是通过 Blender 建模器 GUI 添加的。首先点击它：一个对象将在 *chrono_frame_objects* 中被选中。在我们的例子中，它是名为 "Object" 的对象。点击展开其子树：你会看到这个对象是名为 **shape_xxxxxxxxx** 的资产的实例，其中 xxxxxxxxxxx 是一个唯一标识符。现在，在 *chrono_assets* 集合中找到 shape_xxxxxxxxx 并点击其图标。
  
- 此时你可以编辑该资产，例如在这里我们删除了从 Chrono 导出的蓝色材质，并附加了一个新材质以生成网格效果：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_80.jpg)

  (注意：在撰写本文时，如果你编辑了一个从 Chrono 端分配了材质/颜色的资产，这种更改在时间步之间不会保持不变。一个解决方法是禁用 Chrono 材质 - 见后文 -，或者干脆不要从 Chrono 端分配材质)

### Chrono 视图设置

- 打开 3D 视图的侧边标签，通过点击视图右边界的小箭头：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_90.jpg)
  
- 现在你可以点击 *Chrono* 垂直标签，你将看到用于更改 Chrono 对象视图设置的面板：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_100.jpg)
  
- 在上图中，我们启用了 *Show assets coordsys* 选项，例如，这样我们可以看到所有资产的 x、y、z 轴的位置。
  我们还可以更改 *Assets coordsys size* 以找到这些轴的合适大小。
  
- 我们可以通过启用链接和项目的坐标系显示来实现相同的效果（其中项目是：一个 ChBody，或者 ChParticleCluster 中的一个粒子（体实例）等）。
  
- 我们可以通过启用 *Show contacts* 来显示接触。请注意，我们可以更改表示接触力的箭头的外观：
  
  - 在 Chrono 视图设置中向下滚动，在 *Glyphs* 框中选择 *contacts*
  
  - 你会看到可以更改箭头符号的许多属性： 
    
    ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_110.jpg)

例如，我们将 *width* 设置为常量 0.04，将 *length* 设置为 *Property*，其中属性是向量集 *F*，即接触力（带有一些缩放因子）。这样，我们得到的箭头厚度相同，但长度取决于接触力的强度。请注意，我们也可以选择另一种方式，即将所有接触箭头设置为相同长度，但宽度取决于 *F* 属性。或者两者兼顾。

  - 一个有趣的可能性是根据某些属性控制箭头符号的颜色。有一组预定义的伪彩色映射，使用 *Min*、*Max* 和 *colormap* 设置来查看效果。
	
  - 顺便说一下：也许你想通过点而不是箭头来显示接触。如果你将 *type* 设置从 *Vector local* 改为 *Point*，就可以实现这一点。对于点，你可以控制宽度和颜色：对于两者，你可以使用常量值或依赖于某个属性（在本例中为 *F* 向量）的值。

### 其他功能和注意事项

- 通过 C++ 从 Chrono 端分配的 PBR 材质在 Blender 中被转换为 principled BSDF 材质。如果有纹理分配给颜色、凹凸、粗糙度等，这些也会被管理。
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_120.jpg)
  
- OBJ 文件也能正确导入，即使分配了多个材质。
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_130.jpg)
  
- ChLineShape 对象（弧线、样条等）也受支持，并将渲染为细管：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_140.jpg)
  
- ChGlyphs 对象完全支持，子类型包括：点、坐标系、向量、张量。
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_150.jpg)
  
- ChTriangleMeshConnected 对象如果附加了一些向量/标量/张量属性，可以选择性地使用伪彩色映射渲染所需属性：
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_160.jpg)

- ChParticleCloud 对象受到支持，特别关注性能。这是渲染大量相同对象的仿真的首选方式。我们可以在短时间内渲染包含数十万个形状实例的粒子云（无论样本形状的复杂性如何）。
  
  ![](http://projectchrono.org/assets/manual/blender_addin_tutorial_170.jpg)

**注意！！！** 关于性能：在撰写本文时，如果你导出包含超过 100 个 ChBody 类型对象的场景，插件会变得很慢，也就是说，删除 Blender 对象以进入下一个时间步，以及分配新的 Blender 对象，会花费大量时间。这不是插件的问题：瓶颈是 Blender 中的已知问题，当分配/释放大量对象时会花费很多时间。目前的解决方法是尽可能使用 ChParticleCloud 对象（非常快），即当你有相同对象的副本时。我们希望在未来解决这个不便。
