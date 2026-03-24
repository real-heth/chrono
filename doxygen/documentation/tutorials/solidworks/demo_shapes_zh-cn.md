碰撞形状演示 {#tutorial_chrono_solidworks_demo_shapes}
==========================


本教程演示如何使用 [Chrono::SolidWorks](@ref chrono_solidworks_installation) 插件为 SolidWorks 零件分配碰撞形状。这些碰撞形状在导出 .py 场景文件时将被转换为 Chrono 碰撞形状。

请注意，默认情况下，您在 SolidWorks 中建模的所有零件都不会生成任何碰撞形状：如果您想模拟具有碰撞的现象，必须使用本教程中概述的程序为零件分配碰撞形状。这有几个原因：

+ 您可以选择仅为真正需要的零件添加碰撞形状，从而减少计算开销；
+ 目前没有自动方法将通用的详细凹形状转换为一组 Chrono 碰撞形状（实际上，正在开发自动凸分解工具，但在许多情况下，当用户手动添加凸形状时，效果最好）

目前，支持以下凸形状：

+ 球体
+ 圆柱体
+ 盒子
+ 凸包。

也支持它们的组合。

# 前提条件:

+ 您必须拥有一个 [SolidWorks](http://www.solidworks.com) CAD 许可证。
+ 必须在 SolidWorks 中安装 [Chrono::SolidWorks](@ref chrono_solidworks_installation) 插件。
可选地，对于本教程的最后步骤（渲染动画），必须安装以下工具：
+ 必须在您的 Python 环境中安装 [PyChrono](@ref pychrono_introduction) Python 模块，
+ 必须安装 [POVray](http://www.povray.org) 渲染软件；如果您想使用 Irrlicht 实时可视化，则不是必需的；
+ 必须安装 [VirtualDub](http://www.virtualdub.org) 视频编辑工具；如果您想使用 Irrlicht 实时可视化，则不是必需的。

<div class=well>
本演示的文件可以在目录 ```C:/[install path]/chrono_solidworks/examples/collisions``` 中找到。该目录包含此装配所需的所有零件。
</div>

我们将建模一小组带柱头的柱子，这些柱子将被地震摇动。

# 创建柱子

+ 首先，启动 SolidWorks。

+ 使用菜单 **文件/新建...** 创建一个新的 *零件*。

+ 在零件编辑器中，使用工具栏中的 ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_01.jpg)  **旋转凸台/基体** 工具创建一个多立克柱（类似于希腊神庙中的柱子）。(只需创建一个类似矩形的轮廓，其中一条垂直边几乎是平的弧线，另一条边是旋转轴)。

+ 您应该得到这个结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_02.jpg)

此形状将用于计算质量、惯性张量、零件的坐标，以及如果使用 POVray 或其他类型的后处理进行可视化网格，但它尚未产生任何碰撞！
因此，现在我们为该零件分配碰撞形状。

可以转换为 Chrono .py 文件的碰撞形状是简单类型：球体、圆柱体、盒子等（或它们的组合）。因此，现在我们将用单个圆柱体近似柱子，假设在这个近似水平上足以进行我们想要的模拟。

要添加碰撞形状，我们利用 SolidWorks 的一个功能：每个零件可以包含多个“形状”——这些形状在 SolidWorks 中称为 *实体体*（不要与 Chrono 中的 *刚体* 概念混淆）。

+ 因此，我们将创建一个额外的圆柱体：使用工具

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_03.jpg)

**拉伸凸台/基体** 并从柱子的顶部拉伸一个圆盘到柱子的顶部。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_08.jpg)

+ 重要！在接受拉伸结果之前，取消选中 **合并结果** 选项！

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_04.jpg)

+ 由于取消选中 *合并结果* 选项，现在您可以在左侧面板中看到 *两个* 实体体（如果您忘记了，默认情况下 SolidWorks 会将圆柱体与柱子合并，您仍然会得到一个实体体，因为它们是重叠的）。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_05.jpg)

+ 选择第二个实体体（圆柱体），并在屏幕右侧的 Chrono 插件选项卡中使用工具 **将实体体设置为碰撞形状**。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_06.jpg)

+ 该工具会检测到您选择的实体体是一个圆柱体，因此将其标记为碰撞形状；请注意，实体体的名称会发生变化，您会得到类似这样的结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_07.jpg)

<br>
<div class = "ce-info">
请注意，该工具还会自动为碰撞形状添加一个零密度材料（即 **空气**）。这是必要的，否则当 SolidWorks 计算柱子的质量时，重量将加倍，而我们希望碰撞形状不影响质量计算。无论如何，您仍然可以为柱子分配具有所需密度的 SolidWorks 材料，例如钢、混凝土等。
</div>

<div class = "ce-info">
该工具还会改变碰撞形状的可视化，使其变为半透明的粉红色。这更为直观，因为碰撞形状通常与完整形状重叠。一旦您确定碰撞形状在正确的位置，您也可以将其隐藏。
</div>

<div class = "ce-warning">
在使用工具创建碰撞形状后，**不要修改**其实体体（例如，不要在圆柱体上打孔），否则在将来导出 .py 场景时，它将无法被识别为原始碰撞形状。
</div>

+ 将其保存为 ```column.sldprt```。

# 创建一个柱头

+ 首先，启动 SolidWorks。

+ 使用菜单 **文件/新建...** 创建一个新的 *零件*。

+ 在零件编辑器中，使用工具栏中的
  
  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_03.jpg)  

  **拉伸凸台/基体** 工具创建一个带方形底座的盒子。（这是我们稍后将雕刻以制作详细柱头的基本形状）。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_10.jpg)

+ 现在我们展示另一种定义碰撞形状的方法：选择盒子实体体并使用菜单 **插入/特征.../复制...**，确保选择了 **复制**，然后在不移动任何内容的情况下接受工具。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_11.jpg)

+ 现在您有两个初始盒子的副本：其中一个将用于表示碰撞形状。选择第二个实体体，并在屏幕右侧的 Chrono 插件选项卡中使用工具 **将实体体设置为碰撞形状**。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_06.jpg)

+ 您应该得到这个结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_12.jpg)

+ 现在继续为另一个实体体添加细节（不是碰撞形状，可以将其隐藏以便操作更方便）。例如，使用 ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_01.jpg) **旋转凸台/基体** 工具添加一个环形形状，如下所示：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_13.jpg)

+ 我们希望添加一个表示环形的碰撞形状：一个圆柱体就足够了。创建一个圆柱体（不要忘记取消选中 *合并结果* 选项！），选择它，在 Chrono 插件选项卡中使用 **将实体体设置为碰撞形状** 工具，如前面的步骤所示。

+ 您可能还想添加一些可选的细节，例如倒角等，这样您将得到以下结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_17.jpg)

  这是
  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_14.jpg) = 
  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_15.jpg) +
  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_16.jpg)

请注意，在这种情况下，您使用一组不同的碰撞原语定义了碰撞形状，即一个立方体和一个圆柱体。您可以在单个零件中添加任意数量的碰撞形状。

# 创建地板

+ 使用菜单 **文件/新建...** 创建一个新的 *零件*。

+ 按照之前创建柱头的说明，您应该能够创建一个大的平板盒子，为其分配一个盒子碰撞形状，并将其保存为 ```floor.sldprt```（在我们的示例文件中，我们将 ```floor``` 直接保存到装配体 portal.sldasm 中）。


# 装配建筑

+ 使用菜单 **文件/新建...** 创建一个新的 *装配体*。

+ 如果 SolidWorks 提示您创建一个 *布局* 对话框，只需关闭它；在本教程中我们不需要布局。

+ 使用菜单：**插入/组件/零件...** 并选择地板零件，将其作为 *固定* 零件添加到装配体中。

+ 确保在特征管理器中显示为 ```(f)floor```，而不是浮动的 ```(-)floor``` 零件。如果不是，请使用弹出菜单，如前面的教程中所学。

+ 使用菜单：**插入/组件/零件...** 并选择 capital.sldprt 零件。

+ 使用 
  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_034.jpg) 
  **配合** 工具将柱头完美地放置在地板上。

+ 重复最后两个步骤，将 column.sldprt 零件添加到柱头顶部，再次重复将 capital.sldprt 添加到柱子顶部。添加配合约束以使它们完美对齐：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_18.jpg)

+ 现在停用配合约束，因为我们不希望它们被导出到 .py Chrono 文件中（如果保持激活，地震期间建筑将无法倒塌）。要停用它们，只需选择它们并使用弹出菜单 ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_22.jpg)；它们将变为“幽灵”状态：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_19.jpg)

+ 如果需要，您可以通过选择下部柱头 *column* 上部柱头并使用圆形阵列工具 ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_21.jpg) 创建一组柱子。这将产生以下结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_20.jpg)

# 导出装配体为 Chrono 系统

+ 按照之前的教程学习的方法导出系统：打开 Chrono 导出器选项卡，勾选 **保存 test.py** 按钮，点击 **另存为 Python...** 按钮，并将其保存为 ```collisions.py``` 在一个空目录中。

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine_17.jpg)

+ 如果按下 **运行测试** 按钮，测试 Python 脚本将计算模拟。只是一个静态场景。

然而，有三个需要改进的点：柱子将保持固定，因为还没有地震，摄像机视锥可能未正确对齐以显示所有柱子，表面材料可能看起来过于暗淡和无趣。在接下来的步骤中，我们将通过编写自定义的 Python 脚本来修改模拟。

# 自定义 Python 模拟，引入地震

+ 复制 run_test.py 文件并将其重命名为 ```run_test_modified.py```。我们将以此文件作为模板。

+ 在您的 Python IDE（例如 Spyder）中打开 run_test_modified.py。

+ 虽然不是强制性的，但建议设置碰撞检测算法的内外碰撞包络。这对于非常大或非常小的物体尤其重要。
请注意，这必须在导入模型和/或创建 ChSystem 之前进行。

~~~{.py}
chrono.ChCollisionModel.SetDefaultSuggestedEnvelope(0.005)
chrono.ChCollisionModel.SetDefaultSuggestedMargin(0.005)
~~~

+ 修改加载 .py 系统文件的部分为：

~~~{.py}
exported_items = chrono.ImportSolidWorksSystem('./collisions')
~~~

+ 创建一个 *接触表面材料*（用于碰撞检测的表面数据，以了解摩擦系数和接触点的其他属性）。在此示例中，有一个单一的接触表面材料在所有对象之间共享。

~~~{.py}
brick_material = chrono.ChContactMaterialNSC()
brick_material.SetFriction(0.6)
~~~

<div class = "ce-info">
可选地，可以定义具有 *顺应性* 的表面材料。在这种情况下，应编写一个材料，例如具有一定摩擦力、阻尼系数（Raleygh 类型）、正交顺应性和切向顺应性：

~~~{.py}
brick_material = chrono.ChContactMaterialNSC()
brick_material.SetFriction(0.6)
brick_material.SetDampingF(0.05)
brick_material.SetCompliance (0.000000003)
brick_material.SetComplianceT(0.000000001)
~~~

请注意，对于具有顺应性的材料，应使用较小的时间步长。

<br>
另请注意，对于具有柔量（compliance）的材料，不应设置碰撞安全包络（collision safe envelope），即：```chrono.ChCollisionModel.SetDefaultSuggestedEnvelope(0)```
</div>

<div class = "ce-info">
没有柔量的材料是完全非弹性的。若要在不使用柔量的情况下实现弹性行为，可以设置一个非零的恢复系数，例如：

~~~{.py}
brick_material.SetRestitution(0.6)
~~~

请注意，如果启用了顺应性，恢复系数没有意义。

<br>
请注意，非零的恢复系数在物理上并不准确，除非在非常简单的场景中，因为它基于非常简单的牛顿恢复假设。
</div>

+ 将 brick_material 分配给所有刚体对象，通过迭代 ChSystem 中的所有项目：

~~~{.py}
for my_body in my_system.GetBodies(): 
        my_body.SetMaterialSurface(brick_material) 
~~~

+ 为了在动画中获得更好的效果，将大理石程序纹理分配给所有对象。这是通过创建一个 ChPovRayAssetCustom 对象来完成的，该对象包含 POVray 语法的自定义语句，当 POV 后处理器生成 POV 脚本时将使用该语句。在此示例中，我们使用 POVray 的 ```T_Stone8``` 程序纹理：

~~~{.py}
marble_povmat = postprocess.ChPovRayAssetCustom()
marble_povmat.SetCommands('''
       texture{T_Stone8}
        ''')

for my_body in my_system.GetBodies(): 
        my_body.AddAsset(marble_povmat)
~~~

+ 如果您想将特定纹理分配给特定对象，只需通过名称获取对象，如下例所示：

~~~{.py}
floor_povmat = postprocess.ChPovRayAssetCustom()
floor_povmat.SetCommands('''
       texture{T_Stone9}
        ''')
my_floor = my_system.SearchBody('floor^portal-1')
if not my_floor :
    sys.exit('Error: cannot find floor  from its name in the C::E system!')
my_floor.AddAsset(floor_povmat)
~~~

+ 现在我们想要摇动地板盒以模拟地震。为此，我们在 ```floor``` 对象和默认的 ```ground``` 对象之间创建一个约束，该对象始终存在于 .py 导出的场景中；然后我们将 'floor' 设置为自由（不像在 SolidWorks 中创建时那样固定），并通过将运动规律应用于约束来施加地面和地板之间的运动。

~~~{.py}
my_ground = my_system.SearchBody('ground')
if not my_ground :
    sys.exit('Error: cannot find ground  from its name in the C::E system!')

my_floor.SetFixed(False)
link_shaker = chrono.ChLinkLockLock()
link_shaker.Initialize(my_floor, my_ground, chrono.ChFramed)
my_system.Add(link_shaker)
~~~

+ 到这里，link_shaker 对象还没有分配自定义运动规律，因此它将简单地保持地板与地面静态连接。现在我们创建一个类型为 x=(Ca*sin(t*A+phaseA))*(Cb*sin(t*B+phaseB)) 的运动规律，作为两个谐波规律的乘积：

~~~{.py}
my_functA = chrono.ChFunctionSine(0.06,1.4)
my_functA.thisown = 0
my_functB = chrono.ChFunctionSine(1.0,0.1)
my_functB.thisown = 0
my_funct = chrono.ChFunctionOperator()
my_funct.SetFirstOperandFunction(my_functA)
my_funct.SetSecondOperandFunction(my_functB)
my_funct.SetOperationType(chrono.ChFunctionOperator.MUL)
my_funct.thisown = 0
link_shaker.SetMotionX(my_funct)
~~~

+ 明智的做法是为相机和视点定义一个更好的位置，例如我们将默认位置更改为：

~~~{.py}
pov_exporter.SetCamera(chrono.ChVector3d(3.2,1.3,3.5), chrono.ChVector3d(0.6,0.5,0), 32)
~~~

+ 由于我们想使用 ```T_Stone8``` 程序纹理，其定义在 POVray 头文件 ```stones.inc``` 中，因此我们必须将该包含添加到 POVray 脚本中。方法如下：

~~~{.py}
pov_exporter.SetCustomPOVcommandsScript(
...
#include "stones.inc"
light_source{ <1,3,1.5> color rgb<1,1,1> }
...)
~~~

+ 在我们使用上述代码片段和其他小修改自定义了 ```run-test-modified.py``` 文件后，我们可以 **运行** 它以在几秒钟内计算模拟。

+ 使用 POVray 渲染动画，并使用 VirtualDub 将 .bmp 帧组装成 .avi 文件，如前面的教程中所述；您应该会看到地震的动画：

![](http://www.projectchrono.org/assets/manual/Tutorial_collshapes_23.jpg)
