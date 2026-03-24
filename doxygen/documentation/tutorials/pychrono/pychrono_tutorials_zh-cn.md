PyChrono 教程  {#tutorial_table_of_content_pychrono}
==========================

\tableofcontents

这是面向 [PyChrono](@ref pychrono_introduction) 用户的一组教程集。建议按示例中由浅入深的顺序学习。

下面的示例展示如何从 Python 侧使用 Chrono API。如需查看如何从 C++ 侧使用 `Chrono::Python` 解析并执行 Python 程序，请参见 [Chrono C++ Python 模块教程](@ref tutorial_table_of_content_chrono_python)。

<span style="color:red;font-weight:bold">注意！</span> 与您当前安装的 Chrono 库版本兼容的示例源码，可在以下位置找到：

- 如果您克隆了 Chrono 源码并从源码构建了 PyChrono，示例代码位于源码树的 `src/demos/python/`；
- 如果您通过 conda 安装了 PyChrono 包，示例代码位于本地 anaconda 的 site-packages 下的 `pychrono/demos/`。

## 入门教程

- **core/demo_CH_coords.py**

    学习 Python 与 Chrono 互操作的基础：
    - 导入 PyChrono 模块
    - 使用基本类：向量、矩阵等
    - 继承类

<br>

- **core/demo_CH_buildsystem.py**

    基本的物理系统与刚体创建：
    - 创建 `ChSystem`
    - 创建并添加刚体
    - 遍历已创建的接触
    - 使用 Python 语法遍历已添加的刚体

<br>

- **postprocess/demo_POST_povray1.py**

    基于 POVray 的后处理系统：
    - 创建包含两个刚体的基本系统
    - 创建后处理器对象
    - 为刚体添加用于可视化的资产（assets）对象
    - 生成 POVray 脚本以作为后处理渲染 3D 动画

<br>

- **irrlicht/demo_IRR_revolute.py**

    创建简单摆并在交互式 3D 视图中显示：
    - 使用 `pychrono.irrlicht`（PyChrono 的 Irrlicht 实时 3D 可视化）
    - 将纹理作为可视化资产附加
    - 创建刚体与约束

<br>

- **irrlicht/demo_IRR_earthquake.py**

    创建一小堆砖块，模拟地面震动并观察砖块坠落：
    - 为对象（震动平台）施加位移规律
    - 在 Irrlicht 实时仿真中添加软阴影

<br>

- **irrlicht/demo_IRR_crank_plot.py**

    创建曲柄滑块机构：
    - 添加带指定角速度的电机
    - 使用 Python 的 `matplotlib` 绘图展示结果

<br>

- **irrlicht/demo_IRR_paths.py**

    创建两个沿参数化曲线运动的摆。学习如何：
    - 创建由子线段构成的分段路径并进行可视化
    - 添加“curvilinear glyph”（曲线滑动）类型的约束（刚体可自由移动，但其一点评限于沿路径滑动）
    - 添加“imposed trajectory”（规定轨迹）类型的约束（刚体的一点被约束为按给定运动函数沿参数化路径运动）

<br>

- **irrlicht/demo_IRR_collision_trimesh.py**

    创建基于网格的复杂刚体形状。学习如何：
    - 加载 .obj 网格文件并用于形状的可视化
    - 加载 .obj 网格文件并用于碰撞
    - 调整 `ChBodyAuxRef` 中参考系相对于质心的位置
    - 更改惯性属性

    注意：
    - 使用通用凹网格进行碰撞检测比使用其它碰撞形状更慢且不够稳健，只有在无法用球、盒、圆柱或它们的组合等基本原语定义碰撞形状时才使用。（通常的折衷是：用精细网格作可视化，用若干简单原语作碰撞。）
    - 网格为 Wavefront .obj 文件，可由 Blender、Maya 等建模软件或部分 CAD 导出。
    - 用于碰撞时，.obj 网格必须是“封闭”的，即无边缝、无重复顶点等。若不确定，可使用 MeshLab 等工具检查网格的拓扑正确性。
    - 若仅用于可视化（不用于碰撞），网格无需封闭。（若可视化效果不佳，请检查 .obj 文件中的法线是否正确。）

## FEA tutorials

- **fea/demo_FEA_beams.py**

    使用 `pychrono.fea` 模块模拟柔性梁：
    - 使用 `python.fea` 模块
    - 创建带约束的梁单元

<br>

- **fea/demo_FEA_beamsIGA.py**

    使用 `pychrono.fea` 模拟 Jeffcott 转子：
    - 使用 `python.fea` 模块
    - 创建通过不稳定区的柔性转子
    - 调整积分器与求解器设置以提高精度
    - 通过 Python 侧从 `ChFunction` 继承创建定制运动函数

<br>

## Chrono::Vehicle 教程

使用完整预置的轮式车辆模型，在 Python 中模拟车辆动力学。

- **vehicle/demo_VEH_HMMWV.py**

    使用预置模型的 HMMWV 演示

<br>

- **vehicle/demo_VEH_WheeledJSON.py**

    使用 JSON 文件完全定义的车辆仿真（本例为与 demo_VEH_HMMWV.py 相同的 HMMWV）

<br>

- **vehicle/demo_VEH_HMMWV9_YUP.py**

    演示如何设置竖直 Y 轴的世界坐标系，使用 HMMWV 的降阶模型

<br>

- **vehicle/demo_VEH_CityBus.py**

    城市公交示例，展示后轴双胎车辆

<br>

- **vehicle/demo_VEH_UAZBUS.py**

    货车（UAZ）示例

<br>

- **vehicle/demo_VEH_MAN_10t.py** 

    卡车示例，展示具有两个可转向车轴的车辆

<br>

## OpenCascade 教程
    
- **cascade/demo_CAS_cascade.py**

    使用 `pychrono.cascade` 模块借助 OpenCascade 内核创建几何体并让其落地：
    - 使用 `python.cascade` 模块
    - 在凹网格上创建碰撞
    - 控制碰撞容差（包络、边距）

<br>

- **cascade/demo_CAS_stepfile.py**

    使用 `pychrono.cascade` 加载由 CAD 保存的 STEP 文件：
    - 加载来自 3D CAD 的 STEP 文件
    - 从 STEP 文档中获取部件并转换为 Chrono 刚体

<br>

- **cascade/demo_CAS_robot.py**

    使用 `pychrono.cascade` 加载 STEP 文件并在刚体之间创建约束：
    - 加载 STEP 文件
    - 从 STEP 文档获取部件与参考并创建关节
    - 为部件分配 `ChLinkTrajectory`


## 机器学习教程

- 使用 PyChrono 与 TensorFlow

    在仿真中训练神经网络以控制执行器：
    - 使用 TensorFlow 构建学习模型
    - 使用 PyChrono 构建训练环境
    - 使用仿真训练神经网络
    - [更多细节](@ref tutorial_pychrono_demo_tensorflow)

<br>
<br>

- **cascade/demo_CAS_robot.py**

    使用 `pychrono.cascade` 加载 STEP 文件并在刚体之间创建约束：
    - 加载由 3D CAD 保存的 STEP 文件
    - 从 STEP 文档中获取部件与参考并在它们之间创建关节
    - 为部件分配 `ChLinkTrajectory`

## Machine Learning Tutorials

- 使用 PyChrono 与 TensorFlow

    在仿真中训练神经网络以控制执行器：
    - 使用 TensorFlow 构建学习模型
    - 使用 PyChrono 构建训练环境
    - 使用仿真训练神经网络
    - [更多细节](@ref tutorial_pychrono_demo_tensorflow)

<br>
