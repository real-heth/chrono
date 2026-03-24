导出 POVray 动画（demo_POST_povray.cpp）  {#tutorial_demo_povray}
==========================

本教程演示如何使用 [POSTPROCESS 模块](group__postprocess__module.html) 配合 [POVray](http://www.povray.org) 创建动画。

运行仿真后，程序会在磁盘上保存一组 `.pov` 和 `.ini` 文件，之后可以使用 POVray 进行高质量渲染。

- 学习如何将 @ref chrono::ChVisualShape 附加到刚体上。
- 学习如何输出用于 POVray 的数据。

注意：与 `demo_IRR_assets.cpp` 中用于 Irrlicht 实时显示的资产相同的资产也可用于 POVray 后处理渲染。


# 示例 1

创建一个 @ref chrono::ChBody，并附加一些定义 3D 形状的“资产”。
这些形状可由 VSG、Irrlicht 或 POV 后处理显示。
注意：这些资产与碰撞形状相互独立。

\snippet demo_POST_povray1.cpp Example 1


# 示例 2

纹理、颜色、带变换的资产层次。
本节展示如何添加更高级类型的资产。

\snippet demo_POST_povray1.cpp Example 2


# 示例 3

创建一个 @ref chrono::ChParticleCloud 集群，并附加定义单个“样本”3D 形状的资产。
该样本将在 POV 或 Irrlicht 中重复显示 N 次。

\snippet demo_POST_povray1.cpp Example 3


# POV 导出器

下面的部分非常重要，这也是本示例与使用 Irrlicht 的 `demo_IRR_assets` 的不同之处。
我们需要创建一个类型为 @ref chrono::postprocess::ChPovRay 的后处理器，并告知它我们将要导出哪些可视化资产：

\snippet demo_POST_povray1.cpp POV exporter

# 仿真循环

接下来需要编写常见的 while() 循环来执行仿真。
注意：在运行循环之前需调用 `pov_exporter.ExportScript();`，
并且在每个时间步都要调用 `pov_exporter.ExportData();`——
正是该调用在输出目录中生成了大量的 `.dat` 和 `.pov` 文件。

\snippet demo_POST_povray1.cpp POV simulation

# 使用 POVray 执行与渲染

在创建并编译程序后，按如下步骤操作：

- 运行可执行文件 `demo_POST_povray1.exe`
- 运行时控制台会显示时间计数器，表明系统正在加载并被仿真
- 程序结束后，打开 POVray，使用“Open”菜单或拖放方式打开 `rendering_frames.pov.ini` 文件（该 `.ini` 文件与其他 POVray 输出文件保存在可执行文件相同的目录中）

![](http://projectchrono.org/assets/manual/Povray.jpg)

- 在 POVray 中按下 Run 按钮执行 `.ini` 文件，POVray 会生成大量帧并保存到 `anim` 目录中。

![](http://projectchrono.org/assets/manual/Tutorial_pov.jpg)

# 可选：将渲染帧编码为 AVI 或 MPEG

如果希望将渲染得到的 `.bmp` 图像编码为 `.mpeg` 或 `.avi`，建议使用 VirtualDub 工具：

![](http://projectchrono.org/assets/manual/Tutorial_pov2.jpg)

- 将第一帧（.jpg）拖放到 VirtualDub 界面，它会自动加载时间轴上的其他帧
- 通过菜单 Video/Compression... 选择合适的视频编码器（建议：Xvid、DivX、mpeg4 等）
- 通过菜单 File/Save As Avi... 对视频进行编码并保存到磁盘


# 源代码完整列出

以下为参考用途的完整源代码：

\include demo_POST_povray1.cpp
