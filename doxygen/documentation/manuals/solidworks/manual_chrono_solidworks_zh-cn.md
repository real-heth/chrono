Chrono::Solidworks {#manual_chrono_solidworks}
==========================

![](http://projectchrono.org/assets/manual/carousel_chronosolidworks.jpg)

Chrono::SolidWorks 是 [SolidWorks](http://www.solidworks.com) 的一个插件，允许将 SolidWorks 模型直接导出到 Chrono 中。

该工具允许：

- 导出整个 *Assemblies*、嵌套的 *SubAssemblies* 和 *Parts*，以及它们的材料和外观属性；
- 导出 *Standard* 类型的 *Mates* 以及 *Mechanical>Hinge*；
- 指定 *collision shapes*，可以通过原始形状或自动生成对象的接触网格形状；
- 添加 [Chrono motors](@ref motors) 及其控制功能；

SolidWorks 模型可以导出为：

- **Python**: 可以通过 PyChrono 运行或通过 [Chrono::Parsers](@ref manual_parsers) 模块在 C++ 中解析（在这种情况下，需要安装 PyChrono）；
- **C++**: 生成的文件需要与用户项目一起编译；这可能有限制，但对于测试非常有用；
- **JSON**: 这允许通过 Chrono 序列化功能反序列化模型；

使用 SolidWorks 插件输出的最快方法是使用 [专用模板项目](https://github.com/projectchrono/chrono-solidworks/tree/master/to_put_in_app_dir/ChronoSolidworksImportTemplate)，可以在插件存储库中找到。它也是加载导出模型的各种情况下的良好信息来源。

![chrono_solidworks_overview](http://projectchrono.org/assets/manual/chrono_solidworks_overview.png)

# 使用方法

安装完成后（请参见 [专用安装指南](@ref chrono_solidworks_installation)），SolidWorks 的 *任务窗格*（也就是显示界面右侧那一竖排图标的地方）里应该会出现一个带有 Chrono 标志的新图标。接下来的所有操作都要通过这个面板来进行。

![chrono_solidworks_panel_1](http://projectchrono.org/assets/manual/chrono_solidworks_panel_1.png) ![chrono_solidworks_panel_2](http://projectchrono.org/assets/manual/chrono_solidworks_panel_2.png)

在成功导出模型之前，需要了解一些先决信息：

+ 仅从 *Assemblies* 导出，而不是从单个 *Parts* 导出；
+ 每个 *SubAssembly* 被视为一个单一的刚体，除非它被设置为 *Flexible*；
+ Chrono 电机是通过 *Coordinate Systems* 对象指定的，这些对象必须放置在 **顶层**（而不是在 *Parts* 内）；
+ **对象默认不发生碰撞**；
+ 碰撞设置在 **Solid Bodies** 上，而不是 *Parts* 上；
+ 创建 **Primitive** 碰撞形状将把所选物体的材料转换为 **Air**。

## 添加碰撞形状

碰撞检测和接触模拟通常是模拟中最耗费资源的操作之一。因此，只有那些被明确标记为“可碰撞”的物体才会被碰撞算法考虑。

出于同样的原因，最好在可能的情况下，通过在对象周围创建一个额外的简单物体，将复杂的物体 **包裹成原始形状**。这个包裹物体的材料将自动设置为 **Air**。

要在物体上启用碰撞：

1. 选择一个 *Solid Body*（而不是整个 *Part*）：展开 *Part* 树，查找 *Solid Bodies*，选择其中一个；
2. 点击 Chrono::SolidWorks 插件以展开它；
3. 在不同的碰撞形状类型之间进行选择，顺序如下：
   1. **Primitive Shape**（计算最轻量）：如果物体类似于原始形状（盒子、球体、圆柱等），将自动识别并附加到物体上；此外，所选物体将被设置为空气材料，其外观将变为半透明；
   2. **Mesh**：大多数物体属于此类别，其形状不像原始形状那么简单；将自动生成网格；然而，通过在后处理中替换为手工定制的网格，可以获得更好的性能；不如原始形状稳健；将在物体上进行球体扫描（半径为 *Mesh Sphere Sweep Radius*），从而“膨胀”原始形状以进行碰撞检测；半径越大，越稳健，但碰撞检测的精度越低；
   3. **Convex Decomposition**：待实现...

将物体标记为碰撞形状后，自定义标签将被添加到实体名称前缀。请勿修改此前缀。此外，请注意 *Part* 本身也会受到影响。因此，所有实例都将启用碰撞。

一些碰撞设置可在面板底部找到。

请注意，仅点击 *Undo* 无法撤销此操作。

## 添加电机

Chrono 电机可以直接添加到 SolidWorks 模型中，通过放置一个 *Coordinate System*（在 *Assembly* 选项卡 > *Reference Geometry* 中）。这将作为一个占位符，在导出阶段将放置一个适当的 @ref chrono::ChLinkMotor "ChLinkMotor"。

要添加 Chrono 电机：

1. 点击 Chrono::SolidWorks 插件以展开它；
2. 点击 **Motors**；
3. 面板将提供各种选择：选择适当的电机及其控制函数（请参见 [相关手册](motors.html#how_to_control_motors) 了解如何在 Chrono 中使用它们）；
4. 从树视图中选择一个 *Coordinate System* 并点击 **Add marker**；*Coordinate System* 必须位于 **顶层**
5. 从树视图中选择一个 *Part* 并点击 **Add slave body**；对主体执行相同操作；
6. 点击 **Create motor**。

自定义属性将作为所选 *Coordinate System* 的子项出现。通过选择它，然后点击 *Motors > Select Marker* 按钮，可以检索、编辑或删除电机属性。注意：对于未安装 Chrono::Solidworks 插件的 Solidworks 版本，此自定义电机属性是透明的。

## 自定义设置

一些设置是不言自明的。对于所有设置，工具提示将提供一些基本信息。这里是对那些更复杂设置的描述：

- **为每个子部件生成单独的 .obj 文件**：由多个实体组成的 *Parts* 或 *SubAssemblies* 可以为每个单独对象生成一个网格文件，或者生成一个包含所有对象的唯一网格；
- **导出比例**：模型可以在导出前通过适当的设置进行缩放：请注意，插件会自动识别 SolidWorks 中使用的单位，并负责将其转换为 SI 单位，而无需进一步更改。此缩放选项仅用于在典型缩放基础上提供额外的缩放。
- **运行模拟**：可以直接在 Solidworks 环境中运行装配体的 Chrono 模拟，而无需额外编码；在将模型导出到文件之前进行测试非常有用。

# 其它链接

* @subpage chrono_solidworks_installation
* [教程](@ref tutorial_table_of_content_chrono_solidworks)
* [Github 仓库](https://github.com/projectchrono/chrono-solidworks)
