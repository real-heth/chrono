发动机演示 {#tutorial_chrono_solidworks_demo_engine}
==========================

这是一个关于如何使用 SolidWorks CAD 作为预处理工具的重要入门教程，感谢 [Chrono::SolidWorks](@ref chrono_solidworks_installation) 插件的支持。

你将学习如何使用 SolidWorks 建模 3D 装配体，如何将其导出为包含 Chrono 系统描述的 .py 文件，如何使用 [PyChrono](@ref pychrono_introduction) 运行导出系统的 Python 仿真，以及如何使用 POVray 渲染仿真。

请按照教程的所有步骤操作，一旦你理解了所有这些步骤，你将能够创建许多可以从 SolidWorks 导出到 Chrono 的复杂机制。

# 前提条件:

+ 你必须拥有一个 [SolidWorks](http://www.solidworks.com) CAD 许可证。
+ [Chrono::SolidWorks](@ref chrono_solidworks_installation) 插件必须安装在 SolidWorks 中。
可选地，对于教程的最后步骤（渲染动画），这些工具必须安装：
+ [PyChrono](@ref pychrono_introduction) Python 模块必须安装在你的 Python 环境中，
+ [POVray](http://www.povray.org) 渲染软件必须安装；如果你想使用 Irrlicht 实时可视化，则不是必需的；
+ [VirtualDub](http://www.virtualdub.org) 视频编辑工具必须安装；如果你想使用 Irrlicht 实时可视化，则不是必需的。

<div class=well>
该演示的文件可以在目录 ```C:/[install path]/chrono_solidworks/examples/engine``` 中找到。该目录包含此装配所需的所有零件。
</div>

# 创建子装配体

+ 首先，启动 SolidWorks。

+ 使用菜单：**文件/新建...** 并选择 *装配体*。

+ 如果 SolidWorks 提示你创建 *布局*，只需关闭它；在本教程中我们不需要布局。

+ 使用菜单：**插入/组件/现有零件...** 并从上面列出的演示文件目录中选择 ```Piston.sldprt``` 文件。活塞可以放置在你喜欢的位置，在 3D 视图中：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_01.jpg)

+ 使用菜单：**插入/组件/现有零件...** 并从演示文件目录中选择 ```Conrod.sldprt``` 文件。活塞可以放置在你喜欢的位置，在 3D 视图中： 

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_02.jpg)

+ 特征管理器视图，在左侧，应如下所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_03.jpg)

+ 使用 **配合** 工具在活塞和连杆之间创建约束。可以通过按下此按钮轻松访问此工具：

 ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_034.jpg) 

+ 配合工具对于所有 SolidWorks 用户来说应该是熟悉的，它包括选择一对表面并设置应在它们之间强制执行的约束类型；完成后按下绿色的对勾按钮：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_035.jpg)

+ 具体来说，你必须在连杆和活塞之间创建一个 **同心** 配合，如下图所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_04.jpg)

+ ...以及在连杆和活塞之间创建一个 **重合** 配合，如下图所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_05.jpg)

+ 创建的约束现在可以在左侧的特征管理器视图中看到：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_06.jpg)

+ 使用菜单：**文件/另存为...** 并将此装配体保存为 ```piston_rod.sldasm```，在你喜欢的目录中。这个子装配体（活塞 + 连杆）将在稍后用作构建整个发动机更大装配体的构建块。

# 创建根装配体

+ 使用菜单：**文件/新建...** 并选择 *装配体*。现在我们将创建根装配体，它包含整个发动机。一个装配体可以包含零件或子装配体。

+ 再次，如果提示创建布局，只需关闭布局对话框即可。

+ 选择前视平面，在特征管理器中选择它，然后在弹出菜单中点击 *草图*，以便我们可以在其上创建一些参考轴。

+ 在草图中，创建以下方案，包括一条水平轴和四条垂直轴，并添加尺寸，以确保它们之间的间距为 89.3 mm：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_07.jpg)

+ 使用菜单：**插入/组件/零件...** 并从演示文件目录中选择 ```Crankshaft.sldprt``` 文件。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_08.jpg)

+ 注意，在特征管理器视图的左侧，名称显示为```(f) Crankshaft <1>``` 其中 ```(f)``` 标签表示该零件是固定的。默认情况下，SolidWorks 中插入的第一个零件是固定的；但在我们的情况下，我们希望它是自由的，因为我们将负责将其约束到一个旋转关节，所以在特征管理器中使用弹出菜单，将 *固定* 改为 *浮动*，你将看到 ```(-) Crankshaft <1>``` 带有 ```(-)``` 标签。

+ 使用 **配合** 工具在曲轴和水平轴之间创建约束。可以通过按下此按钮轻松访问此工具：
  
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_034.jpg)

+ 约束类型应为 **同心**：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_09.jpg)

+ 使用菜单：**插入/组件/装配体...** 并选择你之前保存的 ```piston_rod.sldprt``` 文件（或使用演示目录中提供的文件）。将子装配体放置在 3D 视图中。

+ 注意！默认情况下，子装配体将被视为刚性装配体（即活塞和连杆不能活动），这不是我们想要的行为。可以通过查看其图标来判断子装配体是否为刚性：
  
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_10.jpg)

+ 现在，使用弹出菜单并点击 **属性** 按钮，如下图所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_11.jpg)

+ 在打开的窗口中，将 *Solve as.. Rigid* 切换为 *Solve as.. Flexible*：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_12.jpg)

+ 按 **确定** 并关闭。你将看到图标已更改为：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_13.jpg)

+ 使用 **配合** 工具在曲轴和连杆之间创建约束。可以通过按下此按钮轻松访问此工具：
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_034.jpg) 

+ 你必须创建一个 **同心** 配合和一个 **重合** 配合：
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_14.jpg)
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_15.jpg)

+ 使用 **配合** 工具在活塞和你在草图中创建的垂直轴之间创建约束。使用按钮：
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_034.jpg)

+ 你必须创建一个 **同心** 配合：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_16.jpg)

+ 注意，最终，你的装配体层次结构应如下所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_165.jpg)

+ 使用菜单：**文件/另存为...** 并将此装配体保存为 ```engine.sldasm```，在你喜欢的目录中。（注意，如果你想跳过教程的前面步骤，已经提供了一个可用的同名装配体供你使用）。

# 导出装配体为 Chrono 系统

+ **打开** Chrono 导出器的选项卡，在视图窗口的右侧：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_17.jpg)

+ 勾选 **保存 test.py** 按钮（这将生成一个示例 Python 脚本，用于计算简单的动画并输出可用于渲染的后处理数据）。

+ 点击 **另存为 Python...** 按钮，并将其保存为 ```engine.py``` 在一个空目录中。

此操作将整个根装配体保存为一个 Python 文件，称为 ```engine.py```，其中包含大量语句，一旦作为 Python 模块执行，将为 SolidWorks 中的所有移动部件创建许多 ChBody 对象，并为每个 SolidWorks 配合约束创建许多 ChLink 对象。使用编辑器检查 engine.py 文件，以便了解发生了什么。

除了导出的 ```engine.py``` 文件外，还会有一个名为 ```engine_shapes``` 的目录。查看该目录：你会发现三个 .obj 文件，每个文件对应一个移动部件的可视化形状的 3D 网格。如果你想对模拟进行渲染，这些形状将在后处理系统中使用。

你还可以使用 3D 工具（如 [Blender](http://www.blender.org)）修改、编辑或简化这些 .obj 网格。

# 在交互式 3D 视图中运行 Chrono 仿真

由于你启用了 *保存 test.py* 选项，一个自动生成的 ```test.py``` 程序将加载并模拟引擎。你可以直接从 SolidWorks 运行它以进行快速测试，操作如下：

- 勾选 **Visualization Irrlicht** 选项，以使用 3D 实时视图

- 点击 **Run test** 按钮。

此时，test.py 将加载 engine.py 模型并显示此交互式视图，你可以在模拟运行时使用鼠标进行平移和缩放：

![](http://www.projectchrono.org/assets/manual/Tutorial_engine_17_irrlicht.jpg)

就是这样！

请注意，不要指望在这个动画中看到太多运动：唯一的运动会是由活塞的重量引起的，这会使曲轴稍微摆动一下。如果你想施加一个持续的旋转，你需要遵循下面的教程《Demo_engine advanced》（发动机演示进阶）。

# 这是如何工作的？ 

当你按下 **Run test** 按钮时，发生了什么？

1. SolidWorks 调用 Python 解释器来运行 ```test.py``` 文件，该文件基于 [PyChrono](@ref pychrono_introduction);

2. 接着，test.py 文件将：

3. 加载你从 SolidWorks 导出的 engine.py 文件

4. 将 engine.py 中的所有对象放入一个 ChSystem 对象中

5. 设置一个基于 Irrlicht 的简单可视化系统

6. 运行仿真循环

注意，在某些系统上，如果 Python 解释器未在全局路径中可用，步骤 1 可能会失败。如果是这样，你可以手动启动 ```test.py```，例如，打开一个 Anaconda shell 并使用以下命令启动：

```run_test.py -f engine.py```

实际上，test.py 程序使用了必需的 -f 参数来指定要加载的模型。

其他标志也可以使用，命令行语法为

```run_test.py (-f|--filename)<model_file> [-d|--timestep]<dt>  [-T|--Tlength]<max_simulated_time> [-v|--visualization]<irrlicht|pov> [-p|--datapath]<path_to_data_folder>```

无论如何，```test.py``` 文件只是一个简单的存根。你可以将其作为参考，并修改它以创建更复杂的 Python 程序。我们强烈建议你在 Python 集成开发环境（IDE）编辑器中打开它，查看其工作原理。

# 使用 POVray 运行 Chrono 仿真

- 勾选 **Visualization pov** 选项，以使用 POVray 作为后处理渲染工具

- 点击 **Run test** 按钮。

仿真将以无交互视图的方式计算：请等待几秒钟。在仿真结束时，你会发现 engine.py 的目录中已经生成了额外的文件；其中一些是由 Chrono 的后处理系统生成的。操作如下：

- 打开 POVray。

- 将 ```rendering_frames.pov.ini``` 文件拖放到 POVray 窗口中。

- 点击 POVray 中的 **Run** 按钮。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_18.jpg)

- 一系列 .bmp 图像将通过光线追踪生成，并保存在 *anim* 目录中：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_19.jpg)

- 要从一系列 .bmp 文件生成动画：
  只需启动 *VirtualDub* 工具并 **加载** 序列中的第一张图像，其他图像将自动添加：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_20.jpg)

- 建议在 VirtualDub 中选择合适的压缩编解码器。为此，请使用菜单 **视频/压缩...** 并配置编解码器。我们建议使用 Mpeg4 / DivX 编解码器。如果系统中尚未安装 Mpeg4，可能需要安装编解码器包。

- 另外，请记住，您可能需要设置帧速率，通常为每秒 25 或 30 帧。只需使用菜单 **视频/帧速率...**

- 最后 **另存为 AVI**。

# 继续更复杂的系统

可选地，您可以通过添加更多气缸来重复此练习，以创建完整的四缸发动机：

+ 添加另外三个 ```piston_rod.sldasm``` 子装配体并创建适当的约束（避免创建冗余约束）；你应该得到这个：

  ![](http://www.projectchrono.org/assets/manual/SWaddin.jpg)

+ 将整个装配体保存为 ```Engine4c.sldasm```

+ 将 Chrono 系统导出为 ```Engine4c.py```

完成此操作后，现在可以继续以下内容 [Demo_engine advanced](@ref tutorial_chrono_solidworks_demo_engine_advanced)
在这里，您将学习如何添加额外的约束（例如，施加曲轴旋转的电机约束）、如何更改形状的渲染外观等高级主题。
