加载一个 STEP 文件并模拟一个机器人 (demo_CAS_robot.cpp)  {#tutorial_demo_robot}
==========================

<div class="ce-warning">
此演示已过时，需要进行深度修改才能适配最新的 Chrono 版本。
</div>

本教程将介绍如何使用 [CASCADE 模块](group__cascade__module.html) 来加载一个从 CAD 模型导出的、以装配体形式保存在 STEP 文件中的 6 自由度机器人。

这是一个高级教程，展示了如何加载从专业 3D CAD 软件中保存为 [STEP 文件格式](http://en.wikipedia.org/wiki/ISO_10303) 的复杂 3D 模型。

大多数高端 3D CAD 软件都可以将装配体和零件保存为 STEP 格式。在最常用的 CAD 软件中，我们引用 [CATIA](http://www.3ds.com/products/catia/welcome/)、[SolidEdge](http://www.solidedge.com)、[SolidWorks](http://www.solidworks.com/)、[PTC Pro/E](http://www.ptc.com) 等。以下教程基于 **SolidEdge**，但可以通过少量修改适配其他 CAD 软件。

# 准备一个STEP文件

CASCADE 模块能够直接解析已保存为单个 STEP 文件的子装配体和子零件。然而，在保存之前，最好按照某些指南准备装配体：显著地，我们将在装配体中放置一些“辅助”对象（标记），我们将在 C++ 编程端使用它们，以便检索用于构建零件之间约束的有用坐标。这个过程在以下示例中进行了说明。

<div class="ce-info">
创建一个演示机制（汽车、机器人等）可能需要数小时。为了简化操作，我们加载一个现成的模型，该模型可以从工业机器人制造商的网站下载，见 [下载页面](http://www.abb.com/product/seitp327/5356453900282c5cc1256efc0028d55d.aspx?productLanguage=us&country=00&tabKey=7 ) 来自 [ABB](www.abb.com) 网站。我们下载了 IRB 7600 机器人的 3D 模型：顺便说一下，它已经是 STEP 格式，因此可以直接由 CASCADE 单元加载，但我们更愿意在 SolidEdge 中修改它并再次保存。
</div>

- 启动 SolidEdge（在本例中我们使用 v18 版本）

- 菜单 文件 / 打开...

- 选择从 ABB 网站下载的机器人的 STEP (.stp 或 .step) 文件。

- 在“新建”窗口的“常规”选项卡中，选择“Normal.asm”，以让 SolidEdge 从 STEP 文件创建一个装配体。

- 按下确定。转换完成后，SolidEdge 创建了装配体。查看 STEP 文件所在的目录：SolidEdge 创建了 .asm 文件和许多 .part 文件。右侧的 Assembly PathFinder 面板显示了装配体中的所有零件：

![](http://projectchrono.org/assets/manual/Tutorial_robot_01.jpg)

- 注意，装配体由许多零件组成。可能在我们的仿真中，刚体与 CAD 零件之间并不是一一对应的，因此我们希望组织 N 个子装配体，代表仿真中的 N 个刚体。也就是说，如果每个零件保持在一个单独的子装配体中，代表一个“刚体”，并且这些子装配体可以选择性地包含一些辅助对象（我们称之为“标记”），这些标记可以在 C++ 端用于查找关节的位置，那将是很好的。

- 创建子装配体：
	- 选择“零件库”面板，
	- 按下“Create in Place”按钮以打开创建窗口，
	- 将“Normal.asm”设置为模板
	- 在“新文件名”中设置“Base”（或“Forearm”，或其他有意义的名称），
	- 在“新文件位置”中浏览到包含所有其他装配文件的目录，
	- 菜单 文件 / 关闭并返回，以返回到一般装配。
	- 重复上述步骤以创建其他子装配体，例如命名为 'Bicep'、'Forearm'、'Wrist' 等。

- 创建的子装配体仍然是空的。因此我们必须将导入的零件移动到它们中。在 SolidEdge v.18 中，从父装配体拖放零件到子装配体不起作用，但一个简单的方法是：
	- 在父装配体中选择零件，
	- 按下 Ctrl+C 复制，
	- 然后在 Assembly PathFinder 中选择子级，
	- 使用弹出菜单中的“编辑”，
	- 按下 Ctrl+V 粘贴，
	- 然后使用菜单“文件 / 关闭并返回”返回到父装配体。

- 重复上述步骤，直到所有零件都在各自的子装配体中。有些子装配体可能包含多个零件。查看我们的示例：

  ![](http://projectchrono.org/assets/manual/Tutorial_robot_02.jpg)

- 现在我们在所有子装配体中添加一个辅助零件，以表示希望使用 C++ 函数创建约束（链接、马达等）的位置坐标。这些就像“占位符”。为此，我们创建一个 'marker.par' 零件，如下图所示：

  ![](http://projectchrono.org/assets/manual/Tutorial_robot_03.jpg)
  [marker.par](http://projectchrono.org/assets/manual/marker.par)

- 我们将这个标记零件插入到所有子装配体中，并正确对齐到所有关节：

  ![](http://projectchrono.org/assets/manual/Tutorial_robot_04.jpg)

- 最后，Assembly PathFinder 面板应显示如下内容：

  ![](http://projectchrono.org/assets/manual/Tutorial_robot_05.jpg)

- 选择基础装配体，使用菜单 文件 / 另存为.. 并选择 STEP 作为文件格式，然后保存整个装配体。

- 退出 SolidEdge 软件。


# 编写 C++ 代码以加载模型

剩下过程的关键是 ChCascadeDoc 类的功能。该类具有从 STEP 文件加载子装配体的功能，通过使用函数 `mydoc.GetNamedShape(...)`，该函数以子装配体（或子零件）的 ASCII 名称作为参数。

这里有一个小的不便：由于 SolidEdge 特有的问题，STEP 文件中子装配体的名称并不总是与您在 Assembly PPathFinder 窗口中看到的名称相同。具体来说，所有装配体的名称都会自动转换为 `Assem1`、`Assem2` 等，而您可能期望的是您创建的装配体名称，例如 `Base`、`Turret` 等。

解决这个不便的方法如下：使用 `mydoc.Dump(std::cout)` 函数在控制台上打印层次结构，并将 STEP 名称记录在纸上（或者使用 demo_converter.exe 显示该层次结构），您将看到类似如下内容：

~~~{.txt}
 -Name :Assem10 (root)
      pos at: 0 0 0 (absolute)
      pos at: 0 0 0 (.Location)
  -Name :Assem8
        pos at: 0 0 0 (absolute)
        pos at: 0 0 0 (.Location)
    -Name :IRB7600_23_500_m2000_rev1_01-1
          pos at: 0 0 0 (absolute)
          pos at: 0 0 0 (.Location)
    -Name :marker
          pos at: 2.29901e-035 -2.99071e-036 0.2185 (absol
          pos at: 2.29901e-035 -2.99071e-036 0.2185 (.Loca
  -Name :Assem4
        pos at: 0 0 0 (absolute)
        pos at: 0 0 0 (.Location)
    -Name :IRB7600_23_500_m2000_rev1_01-2
          pos at: 0 0 0 (absolute)
          pos at: 0 0 0 (.Location)
    -Name :marker
          pos at: 3.88578e-015 -2.66454e-015 0.2135 (absol
          pos at: 3.88578e-015 -2.66454e-015 0.2135 (.Loca
    -Name :marker
          pos at: 0.41 -0.049 0.78 (absolute)
          pos at: 0.41 -0.049 0.78 (.Location)
    -Name :marker
          pos at: -0.38 -0.03 0.6545 (absolute)
          pos at: -0.38 -0.03 0.6545 (.Location)
  -Name :Assem1
          .... etc. etc. .... ........
~~~

从上面的示例中，您可以看到 `Base` 已经变成了 `Assem8`，`Turret` 已经变成了 `Assem4`，依此类推。（幸运的是，SolidEdge 并没有更改零件的名称，只是更改了装配体的名称）。请在纸上记录这些信息。

现在，让我们开发一个 C++ 程序来加载机器人模型并进行仿真。

首先，包含所需的库（注意 unit_CASCADE/... 头文件）并使用适当的命名空间：

~~~{.cpp}
#include "physics/CHapidll.h" 
#include "core/CHrealtimeStep.h"
#include "irrlicht_interface/CHirrAppInterface.h"
#include "irrlicht_interface/CHbodySceneNodeTools.h" 
#include "unit_CASCADE/CHcascadeDoc.h"
#include "unit_CASCADE/CHCascadeMeshTools.h"
#include "unit_CASCADE/CHirrCascadeMeshTools.h"
#include "unit_CASCADE/CHirrCascade.h"
#include "irrlicht_interface/CHbodySceneNode.h" 
#include <irrlicht.h>


// Use the namespace of Chrono
using namespace chrono;

// Use the main namespaces of Irlicht
using namespace irr; 
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Use the namespace with OpenCascade stuff
using namespace cascade; 
~~~

以下是该程序（一个简单的演示，其中机器人由 STEP 文件创建，添加了约束，并在沿简单轨迹移动时显示机器人仿真）。

~~~{.cpp}
int main(int argc, char* argv[])
{

	ChGlobals* GLOBAL_Vars = DLL_CreateGlobals();

	// 1- Create a Chrono physical system: all bodies and constraints
	//    will be handled by this ChSystem object.
	ChSystem my_system;

	// Create the Irrlicht visualization (open the Irrlicht device, 
	// bind a simple user interface, etc. etc.)
	ChIrrAppInterface application(&my_system, L"Load a robot model from STEP file",core::dimension2d<u32>(800,600),false, true, video::EDT_OPENGL); 

	// Easy shortcuts to add logo, camera, lights and sky in Irrlicht scene:
	//ChIrrWizard::add_typical_Logo(application.GetDevice());
	ChIrrWizard::add_typical_Sky(application.GetDevice());
	ChIrrWizard::add_typical_Lights(application.GetDevice(), core::vector3df(30,100,30), core::vector3df(30,-80,-30),200,130);
	ChIrrWizard::add_typical_Camera(application.GetDevice(), core::vector3df(0.2,1.6,-3.5));

~~~

创建 ChCascadeDoc，这是一个加载 STEP 模型并管理其子装配体的容器。同时，为将要创建的刚体准备一些指针。

~~~{.cpp}
	ChCascadeDoc mydoc;
~~~

同时，为将要创建的刚体准备一些指针。

~~~{.cpp}
	ChBodySceneNodeAuxRef* mrigidBody_base	= 0;
	ChBodySceneNodeAuxRef* mrigidBody_turret = 0;
	ChBodySceneNodeAuxRef* mrigidBody_bicep = 0;
	ChBodySceneNodeAuxRef* mrigidBody_elbow = 0;
	ChBodySceneNodeAuxRef* mrigidBody_forearm = 0;
	ChBodySceneNodeAuxRef* mrigidBody_wrist = 0;
	ChBodySceneNodeAuxRef* mrigidBody_hand = 0;
	ChBodySceneNodeAuxRef* mrigidBody_cylinder = 0;
	ChBodySceneNodeAuxRef* mrigidBody_rod = 0;
~~~

加载 STEP 模型，使用以下命令：（确保 STEP 文件在硬盘上）

~~~{.cpp}
	bool load_ok = mydoc.Load_STEP("..\\data\\cascade\\IRB7600_23_500_m2000_rev1_01_decorated.stp");
~~~

打印包含的形状，显示装配体层次结构：

~~~{.cpp}
	mydoc.Dump(std::cout);

	ChCollisionModel::SetDefaultSuggestedEnvelope(0.002);
	ChCollisionModel::SetDefaultSuggestedMargin(0.001);

	// In most CADs the Y axis is horizontal, but we want it vertical.
	// So define a root transformation for rotating all the imported objects.
	ChQuaterniond rotation1;
	rotation1.QuatFromAngleAxis(-CH_PI/2, VECT_X); // 1: rotate 90° on X axis 
	ChQuaterniond rotation2;
	rotation2.QuatFromAngleAxis(CH_PI, VECT_Y);	 // 2: rotate 180° on vertical Y axis
	ChQuaterniond tot_rotation = rotation2 % rotation1;  // rotate on 1 then on 2, using quaternion product
	ChFrameMoving<> root_frame( ChVector3d(0,0,0), tot_rotation); 
~~~

检索已加载模型中的一些子形状，使用 GetNamedShape() 函数，该函数可以使用 path/subpath/subsubpath/part 语法以及 * 或 ? 通配符等。
使用 / 斜杠就像在访问 Unix 目录（实际上 STEP 文件的组织方式就像一个目录，每个子目录表示一个子装配体）。

~~~{.cpp}
	if (load_ok)
	{

		TopoDS_Shape shape_base;
		if (mydoc.GetNamedShape(shape_base, "Assem10/Assem8" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_base = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_base);

				// The base is fixed to the ground
			mrigidBody_base->GetBody()->SetFixed(true);

				// Move the body as for global displacement/rotation by pre-transform its coords.
				// Note, it could be written also as   mrigidBody_base->GetBody() %= root_frame; 
			mrigidBody_base->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_turret;
		if (mydoc.GetNamedShape(shape_turret, "Assem10/Assem4" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_turret = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_turret);

				// Move the body as for global displacement/rotation
			mrigidBody_turret->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_bicep;
		if (mydoc.GetNamedShape(shape_bicep, "Assem10/Assem1" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_bicep = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_bicep);

				// Move the body as for global displacement/rotation
			mrigidBody_bicep->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_elbow;
		if (mydoc.GetNamedShape(shape_elbow, "Assem10/Assem5" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_elbow = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_elbow);

				// Move the body as for global displacement/rotation
			mrigidBody_elbow->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";

		
		TopoDS_Shape shape_forearm;
		if (mydoc.GetNamedShape(shape_forearm, "Assem10/Assem7" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_forearm = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_forearm);

				// Move the body as for global displacement/rotation
			mrigidBody_forearm->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";

		
		TopoDS_Shape shape_wrist;
		if (mydoc.GetNamedShape(shape_wrist, "Assem10/Assem6" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_wrist = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_wrist);

				// Move the body as for global displacement/rotation
			mrigidBody_wrist->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_hand;
		if (mydoc.GetNamedShape(shape_hand, "Assem10/Assem9" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_hand = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_hand);

			//mrigidBody_hand->GetBody()->SetFixed(true);

				// Move the body as for global displacement/rotation
			mrigidBody_hand->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_cylinder;
		if (mydoc.GetNamedShape(shape_cylinder, "Assem10/Assem3" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_cylinder = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_cylinder);

				// Move the body as for global displacement/rotation
			mrigidBody_cylinder->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


		TopoDS_Shape shape_rod;
		if (mydoc.GetNamedShape(shape_rod, "Assem10/Assem2" ))
		{
				// Add the shape to the Irrlicht system, to get also visualization.
			mrigidBody_rod = (ChBodySceneNodeAuxRef*)addChBodySceneNode_Cascade_C(
									&my_system, application.GetSceneManager(), 
									shape_rod);

				// Move the body as for global displacement/rotation
			mrigidBody_rod->GetBody()->ConcatenatePreTransformation(root_frame);
		}
		else std::cout << "Warning. Desired object not found in document \n";


	}
	else std::cout << "Warning. Desired STEP file could not be opened/parsed \n";



	if (!mrigidBody_base ||
		!mrigidBody_turret ||
		!mrigidBody_bicep ||
		!mrigidBody_elbow ||
		!mrigidBody_forearm ||
		!mrigidBody_wrist ||
		!mrigidBody_hand )
	{
		DLL_DeleteGlobals();
		return 0;
	}
~~~

在两个零件之间创建关节。为了确定关节的轴线位置，我们可以利用一个事实：在此演示所用的 STEP 文件中，我们预先插入了一些名为“marker”（标记）的对象，并将它们与轴对齐；因此，现在我们可以获取这些标记并读取其位置和旋转信息。

重要提示！在 STEP 文件中，某些子装配体包含多个标记实例，因此可能存在两个或更多同名为 **marker** 的几何体……如何选择目标实例呢？GetNamedShape() 函数具备处理此问题的功能：您可以使用井号“#”后接数字来指定，例如 Assem10/Assem8/marker#2 表示：从装配体 Assem10 的子装配体 Assem8 中，获取名称为 "marker" 的几何体的第 2 个实例。

~~~{.cpp}
	TopoDS_Shape shape_marker;

	ChFramed frame_marker_base_turret;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem8/marker#1" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_base_turret);
	else std::cout << "Warning. Desired marker not found in document \n";
		// Transform the abs coordinates of the marker because everything was rotated/moved by 'root_frame' :
	frame_marker_base_turret %= root_frame;

	auto my_link1 = chrono_types::make_shared<ChLinkLockRevolute>();
	ChSharedBodyPtr mb1 = mrigidBody_base->GetBody();
	ChSharedBodyPtr mb2 = mrigidBody_turret->GetBody();
	my_link1->Initialize(mb1, mb2, frame_marker_base_turret);
	my_system.AddLink(my_link1);


	ChFramed frame_marker_turret_bicep;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem4/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_turret_bicep);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_turret_bicep %= root_frame;

	auto my_link2 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_turret->GetBody();
	mb2 = mrigidBody_bicep->GetBody();
	my_link2->Initialize(mb1, mb2, frame_marker_turret_bicep);
	my_system.AddLink(my_link2);

	ChFramed frame_marker_bicep_elbow;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem1/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_bicep_elbow);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_bicep_elbow %= root_frame;

	auto my_link3 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_bicep->GetBody();
	mb2 = mrigidBody_elbow->GetBody();
	my_link3->Initialize(mb1, mb2, frame_marker_bicep_elbow);
	my_system.AddLink(my_link3);
	

	ChFramed frame_marker_elbow_forearm;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem5/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_elbow_forearm);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_elbow_forearm %= root_frame;
	
	auto my_link4 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_elbow->GetBody();
	mb2 = mrigidBody_forearm->GetBody();
	my_link4->Initialize(mb1, mb2, frame_marker_elbow_forearm);
	my_system.AddLink(my_link4);


	ChFramed frame_marker_forearm_wrist;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem7/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_forearm_wrist);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_forearm_wrist %= root_frame;

	auto my_link5 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_forearm->GetBody();
	mb2 = mrigidBody_wrist->GetBody();
	my_link5->Initialize(mb1, mb2, frame_marker_forearm_wrist);
	my_system.AddLink(my_link5);


	ChFramed frame_marker_wrist_hand;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem6/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_wrist_hand);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_wrist_hand %= root_frame;

	auto my_link6 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_wrist->GetBody();
	mb2 = mrigidBody_hand->GetBody();
	my_link6->Initialize(mb1, mb2, frame_marker_wrist_hand);
	my_system.AddLink(my_link6);


	ChFramed frame_marker_turret_cylinder;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem4/marker#3" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_turret_cylinder);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_turret_cylinder %= root_frame;

	auto my_link7 = chrono_types::make_shared<ChLinkLockRevolute>();
	mb1 = mrigidBody_turret->GetBody();
	mb2 = mrigidBody_cylinder->GetBody();
	my_link7->Initialize(mb1, mb2, frame_marker_turret_cylinder);
	my_system.AddLink(my_link7);


	ChFramed frame_marker_cylinder_rod;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem3/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_cylinder_rod);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_cylinder_rod %= root_frame;

	ChSharedPtr<ChLinkLockCylindrical>  my_link8(new ChLinkLockCylindrical);
	mb1 = mrigidBody_cylinder->GetBody();
	mb2 = mrigidBody_rod->GetBody();
	my_link8->Initialize(mb1, mb2, frame_marker_cylinder_rod);
	my_system.AddLink(my_link8);


	ChFramed frame_marker_rod_bicep;
	if (mydoc.GetNamedShape(shape_marker, "Assem10/Assem2/marker#2" ))
		ChCascadeDoc::FromCascadeToChrono(shape_marker.Location(), frame_marker_rod_bicep);
	else std::cout << "Warning. Desired marker not found in document \n";
	frame_marker_rod_bicep %= root_frame;

	ChSharedPtr<ChLinkLockCylindrical>  my_link9(new ChLinkLockCylindrical);
	mb1 = mrigidBody_rod->GetBody();
	mb2 = mrigidBody_bicep->GetBody();
	my_link9->Initialize(mb1, mb2, frame_marker_rod_bicep);
	my_system.AddLink(my_link9);
~~~

为手部与绝对参考坐标系之间的“锁定”约束添加两个标记：当我们移动绝对参考坐标系中的标记时，手部将随之运动。

这是一种非常简单的实现机器人逆运动学（IK）的方法，适用于任何类型的机器人，即使是并联机械臂或复杂的运动链也无需了解其逆运动学的解析表达式。

~~~{.cpp}
	ChSharedMarkerPtr  my_marker_hand(new ChMarker);
	ChSharedMarkerPtr  my_marker_move(new ChMarker);

	mrigidBody_hand->GetBody()->AddMarker(my_marker_hand);
	mrigidBody_base->GetBody()->AddMarker(my_marker_move);

	ChQuaterniond rot_on_x; rot_on_x.QuatFromAngleAxis(CH_PI/2, VECT_X);
	ChFramed frame_marker_move = ChFramed(VNULL, rot_on_x) >> frame_marker_wrist_hand ;

	my_marker_hand->ImposeAbsoluteTransform( frame_marker_wrist_hand);
	my_marker_move->ImposeAbsoluteTransform( frame_marker_move);

	ChSharedPtr<ChLinkLockLock>  my_link_teacher(new ChLinkLockLock);
	my_link_teacher->Initialize(my_marker_hand, my_marker_move);
	my_system.AddLink(my_link_teacher);
~~~

为 'my_link_teacher' 标记设置 Z 和 Y 坐标的运动，使手部能够跟随它。为此，我们为 Z 坐标创建四个运动段，为 Y 坐标创建四个运动段，然后使用 ChFunctionSequence 将它们连接起来，并通过 ChFunctionRepeat 重复序列。

~~~{.cpp}
    ChFunctionConstAcc* motlaw_z1 = new ChFunctionConstAcc();
	motlaw_z1->SetDisplacement(-0.7);
	motlaw_z1->SetDuration(1);
	ChFunctionConst*	 motlaw_z2 = new ChFunctionConst();
	ChFunctionConstAcc* motlaw_z3 = new ChFunctionConstAcc();
	motlaw_z3->SetDisplacement( 0.7);
	motlaw_z3->SetDuration(1);
	ChFunctionConst*	 motlaw_z4 = new ChFunctionConst();
	ChFunctionSequence* motlaw_z_seq = new ChFunctionSequence();
	motlaw_z_seq->InsertFunct(motlaw_z1, 1,  1, true); 
	motlaw_z_seq->InsertFunct(motlaw_z2, 1,  1, true);  // true = force c0 continuity, translating fx
	motlaw_z_seq->InsertFunct(motlaw_z3, 1,  1, true);
	motlaw_z_seq->InsertFunct(motlaw_z4, 1,  1, true);
	ChFunctionRepeat* motlaw_z = new ChFunctionRepeat();
	motlaw_z->SetRepeatedFunction(motlaw_z_seq);
	motlaw_z->SetSliceWidth(4);

	ChFunctionConst*	 motlaw_y1 = new ChFunctionConst();
	ChFunctionConstAcc* motlaw_y2 = new ChFunctionConstAcc();
	motlaw_y2->SetDisplacement(-0.6);
	motlaw_y2->SetDuration(1);
	ChFunctionConst*	 motlaw_y3 = new ChFunctionConst();
	ChFunctionConstAcc* motlaw_y4 = new ChFunctionConstAcc();
	motlaw_y4->SetDisplacement(0.6);
	motlaw_y4->SetDuration(1);
	ChFunctionSequence* motlaw_y_seq = new ChFunctionSequence();
	motlaw_y_seq->InsertFunct(motlaw_y1, 1,  1, true);
	motlaw_y_seq->InsertFunct(motlaw_y2, 1,  1, true);  // true = force c0 continuity, translating fx
	motlaw_y_seq->InsertFunct(motlaw_y3, 1,  1, true);
	motlaw_y_seq->InsertFunct(motlaw_y4, 1,  1, true);
	ChFunctionRepeat* motlaw_y = new ChFunctionRepeat();
	motlaw_y->SetRepeatedFunction(motlaw_y_seq);
	motlaw_y->SetSliceWidth(4);

	my_marker_move->SetMotionZ(motlaw_z);
	my_marker_move->SetMotionY(motlaw_y);


	// Create a large cube as a floor.

	ChBodySceneNode* mfloor = (ChBodySceneNode*)addChBodySceneNode_easyBox(
											&my_system, application.GetSceneManager(),
											1000.0,
											ChVector3d(0,-0.6,0),
											ChQuaternion<>(1,0,0,0), 
											ChVector3d(20,1,20) );
	mfloor->GetBody()->SetFixed(true);
	mfloor->GetBody()->EnableCollision(true);
	video::ITexture* cubeMap = application.GetVideoDriver()->getTexture("../data/blu.png");
	mfloor->setMaterialTexture(0,	cubeMap);
~~~

修改求解器的设置。默认情况下，求解器的精度可能不足以保持机器人关节的“连接”状态。特别是，SOR、SSOR 和其他定点迭代法无法很好地模拟此机器人问题，因为在运动链中最后一个部件（即手部）的质量与其他部件相比非常小，因此在本例这种“示教模式”的逆运动学（IK）中“拉动手指”时，求解器的收敛性会很差。所以需要切换到一个更精确的求解器；SOLVER_ITERATIVE_MINRES 求解器既快速又精确（尽管它不适用于含摩擦的碰撞问题）。

~~~{.cpp}
	my_system.SetLcpSolverType(ChSystem::SOLVER_MINRES);
~~~

现在，终于可以运行模拟器的循环了：以下是实时模拟器的运行截图：

![](http://projectchrono.org/assets/manual/Tutorial_robot_06.jpg)

# Here is the full source code:

\include demo_CAS_robot.cpp
