高级发动机演示 {#tutorial_chrono_solidworks_demo_engine_advanced}
==========================

\tableofcontents

在继续本教程之前，请先阅读 [发动机演示](@ref tutorial_chrono_solidworks_demo_engine) 教程。

因此，我们假设您已经为四缸发动机创建了 ```run_test.py```，使用 [Chrono::SolidWorks](@ref chrono_solidworks_installation) 插件导出器生成了这样的 [PyChrono](@ref pychrono_introduction) 文件。

在接下来的内容中，您将学习如何修改由导出器自动生成的 ```run_test.py``` 程序，以自定义仿真并添加高级功能。

现在，您可以编写一个更复杂的 Python 程序来进行更高级的仿真；例如，您可以添加弹簧、阻尼器、电机、粒子等。此外，您还可以修改由插件导出器保存的对象的属性，例如，您可能希望覆盖某些零件的质量属性。

- 为了节省时间，只需从 [发动机演示](@ref tutorial_chrono_solidworks_demo_engine) 教程中复制 ```run_test.py``` 并将其重命名为 ```run_test_modified.py```。我们将以此文件作为模板。

- 在您的 Python IDE 中（例如，Spyder）打开 ```run_test_modified.py```。如果您是 Chrono 的 Python 编程新手，请阅读 [PyChrono 介绍](@ref pychrono_introduction)。

现在我们准备对 Python 程序进行各种修改；以下是一些想法。

<div class=well>
这个示例的文件可以在目录 ```C:/[install path]/chrono_solidworks/examples/engine``` 中找到。该目录包含了组装所需的所有零件。
</div>


# 场景加载代码 {#manual_sw_importscene}

未修改的 ```run_test_modified.py``` 程序可以从命令行运行，命令为 ```run_test_modified.py -f engine4c.py```，但是如果您删除参数解析部分并在上方添加导入语句，您可以直接从 IDE 运行，或者通过双击运行，而无需指定 -f 参数。

例如：假设您将发动机机构导出为 engine4c.py。为了在您的 Python 代码中导入该 Chrono 机构，请编写：

~~~{.py}
exported_items = chrono.ImportSolidWorksSystem('./engine4c')
~~~

<div class = "ce-warning">
注意，您应该写 ```engine4c```，而不是 ```engine4c.py```。也就是说，这里不能使用 .py 后缀。还要注意，即使文件在当前目录中，也必须指定 ```./``` 路径。
</div>

注意所有导出的项目都被添加到一个 ChSystem 中：

~~~{.py}
my_system = chrono.ChSystemNSC()
for my_item in exported_items:
	my_system.Add(my_item)
~~~

<div class = "ce-info">
本教程面向 PyChrono，使用 Python 语言，但这里描述的所有技巧也可以在 C++ 中实现。主要区别在于，在 C++ 中，您不能直接加载导出的 .py 文件：您需要链接 [PYTHON 模块](@ref module_python_installation) 并使用以下 C++ 代码，以实现与上面 Python 代码相同的效果：

~~~{.c}
ChPythonEngine my_python;
my_python.ImportSolidWorksSystem("engine4c", mphysicalSystem);
~~~
</div>


# 添加额外的坐标系  {#manual_sw_addcoords}

如果您想通过编程添加额外的物体/约束/弹簧等，使用 xyz 坐标系作为参考会很有帮助。您可以使用 SolidWorks 添加这些坐标系，然后将它们导出为 .py 文件，稍后获取它们的位置和旋转。例如，这里我们看到如何使用坐标系来定义 ChLinkEngine 电机的 Z 轴，该电机稍后将添加在曲轴和地面之间。

- 首先，添加一个 SolidWorks 特征，类型为 *CoordinateSystem*，使用菜单 **插入/参考几何体/坐标系**。

- 在装配体中选择草图轴的起点作为原点，并选择该轴的方向作为坐标系特征的 Z 方向。您应该得到类似这样的结果：

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_06.jpg)

- 如果一切正常，坐标系将被添加到装配体中（不要将其添加到子装配体或零件中，在本例中不需要）。 

- 将其名称更改为易记的名称，在我们的示例中，我们将其更改为 ```Marker_shaft```。 

  ![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_07.jpg)

- 使用 **另存为 Python** 按钮保存装配体，再次将其导出为 Chrono 的 ```engine4c.py```。 

- 现在在您的 ```run_test_modified.py``` 中，您可以将该坐标系作为 *ChMarker* 对象获取！只需使用 ```SearchMarker``` 语句:

~~~{.py}
my_marker = my_system.SearchMarker('Marker_shaft')
if not my_marker :
	sys.exit('Error: cannot find marker from its name in the C::E system!')
~~~

一旦您将标记作为 Python 对象获取，例如，您可以使用 ```my_marker.GetAbsCoord().pos.x``` 获取其绝对位置，等等。例如，在下一段中，我们将使用它在特定位置创建约束。

如果您对导出对象的名称有疑问，只需打开导出的 .py 文件（在我们的例子中是 engine4c.py），查看类似这样的行：```....SetName("blabla")```;

# 添加更多约束（一个发动机）  {#manual_sw_addconstr}

engine4c.py 文件，由 SolidWorks 导出，不包含任何强制曲轴旋转的约束；导出的唯一约束是
“配合”约束，例如曲轴与连杆之间的旋转关节等。

engine4c.py 文件，由 SolidWorks 导出，不包含任何强制曲轴旋转的约束；导出的唯一约束是
“配合”约束，例如曲轴与连杆之间的旋转关节等。

以下是一个创建额外约束的示例，即在曲轴和地面之间创建一个旋转发动机。掌握此方法后，您便能将此概念扩展到其他类型的约束上。

- 获取地面和曲轴作为 Python 对象。您可以利用它们具有唯一的助记名称：ground（装配体根的默认名称）和 Crankshaft-1（曲轴零件的名称）。因此，执行以下操作：

~~~{.py}
my_shaft = my_system.SearchBody('Crankshaft-1')
if not my_shaft :
    sys.exit('Error: cannot find shaft  from its name in the C::E system!')

my_ground = my_system.SearchBody('ground')
if not my_ground :
    sys.exit('Error: cannot find ground from its name in the C::E system!')
~~~

- 最后，添加这段代码以创建 ChLinkMotorRotationSpeed 类型的约束，即一个约束两个部件旋转的链接；这两个部件就是您刚刚获取的两个刚体，my_shaft 和 my_ground：

~~~{.py}
revolute_frame = my_marker.GetAbsFrame()
link_motor = chrono.ChLinkMotorRotationSpeed()
link_motor.Initialize(my_shaft, my_ground, revolute_frame)
link_motor.SetSpindleConstraint(chrono.ChLinkMotorRotationSpeed.SpindleConstraint_CYLINDRICAL)
link_motor.SetMotorFunction(chrono.ChFunctionConst(1.0*chrono.CH_2PI))  # 1.0 Hz to rad/s
my_system.Add(link_motor)
~~~

```Initialize()``` 函数需要两个物体和一个代表约束位置与旋转的 ```ChFramed``` 对象；我们将使用 my_marker 的坐标系。在这种情况下，ChLinkMotorRotationSpeed 约束假设坐标系的 Z 轴用作旋转轴。

尽管您可以从头创建一个 ```ChFramed``` 对象，通过输入旋转和 xyz 位置值，但在这里更聪明的方法是使用在 SolidWorks 中创建并在前一段中获取的 my_marker 对象的坐标系。

```SetSpindleConstraint()``` 是 ChLinkMotorRotation 类的一个自定义函数：可用于选择两个部件之间使用的连接类型。在这里，我们希望设置一个恒定的角速度，例如每秒一圈，然后我们需要 ```SetMotorFunction()``` 来传递一个 ChFunction 对象，在本例中即为 ChFunctionConst。

根据以上建议修改 ```run_test_modified.py``` 后，即可运行它（通过你的 IDE 或直接双击）。你应该能在 3D Irrlicht 交互式视图中看到四缸发动机在旋转，效果如图所示：

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_00.jpg)

# 改进 POVray 渲染  {#manual_sw_pov}

作为 Irrlicht 交互视图的替代方案，您可以使用 POVray 批处理渲染模拟。如果您查看 run_test_modified.py，您会发现默认行为是使用 Irrlicht，但您可以通过更改列表顶部的一行轻松切换到 POVray，从

~~~{.py}
m_visualization = "irrlicht"
~~~

到

~~~{.py}
m_visualization = "pov"
~~~

其余代码将使用 POV 后处理器，并包含一段占位代码，你可以随意修改或从中获取灵感。

## 更改相机视角  {#manual_sw_camera}

如果您想更改 POVray 后处理系统的相机视角，请在 ```run_test_modified.py``` 中查找以下语句，并根据需要修改视点的 x、y、z 坐标。```SetCamera()``` 的参数是观察者视点的位置向量、目标点的位置向量，以及镜头角度的度数（例如，远摄镜头为 30°，广角镜头为 50°）：

~~~{.py}
pov_exporter.SetCamera(chrono.ChVector3d(0.4,0.6,0.9), chrono.ChVector3d(0.2,0,0), 30)
~~~

## 更改形状可视化材质  {#manual_sw_material}

或许你的 3D 渲染看起来太暗淡，因为默认情况下，所有表面看起来都像白色粉笔。然而，你可以选择一个对象并通过调整 POVray 材质来改变其外观。其思路是，你可以在每个运动部件中添加额外的 ```ChAsset``` 类型对象；这些 ChAsset 对象中的一个可以属于 ```ChPovRayAssetCustom``` 类，它允许你向为特定形状生成的渲染脚本中添加可选的 POVray 语句。看看下面的代码是如何实现的：

~~~{.py}
shaft_povmat = postprocess.ChPovRayAssetCustomShared()
shaft_povmat.SetCommands('''
       pigment { color rgbt <0.5,0.5,0.52,0> }
       finish  {    reflection {0.35}
                    ambient 0
                    diffuse 1
                    phong 0.9
                    phong_size 60
                    metallic } ''')
my_shaft.GetAssets().push_back(shaft_povmat)
~~~

在这种情况下，我们创建了一段 POVray 语句片段，即颜料的定义和光泽金属的表面处理，并将其分配给 my_shaft 对象（我们已经获取了该对象，使用前面段落中描述的方法）。

现在再次运行 run_test_modified.py：它将再次创建 .pov 和 .ini 脚本，因此您可以再次将 .ini 文件加载到 POVray 中并渲染动画；您应该能够看到曲轴看起来像金属一样：

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_01.jpg)

请注意，我们还生成了一个水平平面和一个网格：这可以通过添加作用于全局的额外 POVray 语句来完成；以下是代码片段：

~~~{.py}
pov_exporter.SetCustomPOVcommandsScript('''
    light_source{ <1,3,1.5> color rgb<1.1,1.1,1.1> }
    object{ Grid(0.1,0.04, rgb<0.5,0.5,0.5>, rgbt<1,1,1,1>) translate -0.3*y }
    plane{<0,1,0>, 0 pigment{color rgb<0.8,0.8,0.8>} translate -0.301*y }
    ''')
~~~

## 设置所有对象为透明  {#manual_sw_transparent}

假设你想设置场景中所有对象的材质：这可以通过迭代所有对象来完成，如下代码所示，我们希望将所有部件设置为 80% 透明：

~~~{.py}
transp_povmat = postprocess.ChPovRayAssetCustomShared()
transp_povmat.SetCommands('''
        pigment { color rgbt <1,1,1,0.8> }
        ''')

for aitem in chrono.IterOtherPhysicsItems(my_system):
    aitem.GetAssets().push_back(transp_povmat)
~~~

## 显示约束坐标系    {#manual_sw_showdoords}
 
在前一段中，我们将所有对象设置为透明；如果你想渲染约束的参考坐标系的位置，这可能会很有用——这可以被视为模拟的“可视化调试”...

在 POVray 后处理系统中启用约束坐标系渲染的代码如下：

~~~{.py}
pov_exporter.SetShowLinks(1, 0.03)
~~~

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_02.jpg)


## 显示质心    {#manual_sw_showcog}

假设你想可视化每个 ChBodyAuxRef 物体的重心（COGs，也称为质心）：这是你需要的代码：

~~~{.py}
pov_exporter.SetShowCOGs(1, 0.05)
~~~

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_03.jpg)

质心是由 SolidWorks 在将机构导出为 Chrono.py 文件时自动计算的，并且取决于你在 SolidWorks 界面中分配给零件的材料密度。

## 显示坐标系     {#manual_sw_showframes}

假设你想可视化每个 ChBodyAuxRef 物体的参考坐标系：这是你需要的代码：

~~~{.py}
pov_exporter.SetShowFrames(1, 0.05)
~~~

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_04.jpg)

请注意，从 SolidWorks 插件导出的物体并不是简单的 ChBody 类，而是属于高级的 ChBodyAuxRef 类。实际上，ChBody 对象假设它们的质心与物体的参考坐标系重合，而在 ChBodyAuxRef 物体中，物体的参考坐标系通常与质心不同。


重要提示：移动物体的参考坐标在 SolidWorks 界面中显示为原点（x、y、z 平面交点）。SolidWorks 中的每个零件都有一个原点。如果多个零件在 SolidWorks 子装配中合并并作为刚体求解（参见前一教程），则移动物体的参考坐标是子装配的原点。

## 将相机附加到移动物体    {#manual_sw_attachcamera}

假设你想制作一个动画，其中相机与模拟部件一起移动，例如你可能想显示坐在车辆上的驾驶员的视角。这可以通过以下代码实现：

- 首先，通过查看对象的名称来获取对象；例如，这里我们选择四根连杆中的一根，因为我们希望渲染一个动画，其中视角与连杆一起移动：

~~~{.py}
my_rod = my_system.SearchBody('piston_rod-2/ConRod-1')
if not my_rod :
    sys.exit('Error: cannot find conrod from its name in the C::E system!')
~~~

- 现在，创建一个 ```ChCamera``` 资产，在连杆的坐标系中设置其位置和目标点，并将其添加到连杆的其他资产中：

~~~{.py}
my_movingcamera = chrono.ChCamera()
my_movingcamera.SetPosition(chrono.ChVector3d(0,-0.1,-0.700))
my_movingcamera.SetAimPoint(chrono.ChVector3d(0,-0.1,0))
my_rod.GetAssets().push_back(my_movingcamera)
~~~

当你渲染动画时，你应该会看到类似这样的效果：

![](http://www.projectchrono.org/assets/manual/Tutorial_engine2_05.jpg)
