PyChrono {#pychrono_introduction}
==========================

![](http://projectchrono.org/assets/manual/logo_pychrono_h90.png)

<br>
<br>

* @subpage pychrono_installation
* @subpage pychrono_reference
* [Tutorials](@ref tutorial_table_of_content_pychrono)
* [gym-chrono](https://github.com/projectchrono/gym-chrono): 基于 PyChrono 的 OpenAI Gym 机器人仿真环境

这是一个关于如何使用 PyChrono（即 Chrono 的 Python 版本）的介绍。

PyChrono 是一个 Python 模块，是基于 Chrono 创建应用程序的另一种方式，不需要任何 C++ 编程。实际上，一旦你在 Python 环境中安装了 PyChrono，你就可以使用简单的 Python 脚本语言来调用 Chrono API 的大部分函数、类、方法等。

**Python 编程相对于 C++ 编程的优势**：

* Python 简单易用，
* Python 可以即时解释执行，
* Python 有大量第三方模块，例如用于绘图的 Matplotlib，用于代数运算的 Numpy 等，
* 安装要求低。

**Python 编程相对于 C++ 编程的劣势**：

* Python 比 C++ 慢，
* Chrono 的 Python 模块并不涵盖 C++ API 的所有功能。

其思路是，一旦安装完成，您就可以打开 Python 集成开发环境，导入 Chrono Python 模块，然后开始创建 Chrono 对象，如下所示：

~~~~~~~~~~~~~~~python
import pychrono as chrono

my_systemA = chrono.ChSystem()
my_vect1   = chrono.ChVector3d()
...
~~~~~~~~~~~~~~~

Python 入门
-----------------------

在完成 [安装](@ref pychrono_installation) 后，您就可以在 Python 中使用 PyChrono。首先：

- 启动您的编辑器，例如 Spyder。
- 创建一个新的空白 Python 脚本文件，例如 'test.py'

现在，您可以在这个新的 Python 文件中编写 Python 程序，执行它，将其保存到磁盘等。

让我们来看第一个程序。

- 首先，您应该使用 **import** 关键字来指定程序中必须加载和使用的 Python 模块。Chrono 的大部分核心功能都在一个名为 **pychrono** 的模块中，因此写入：

~~~~~~~~~~~~~~~python
import pychrono as chrono
~~~~~~~~~~~~~~~

注意，*as chrono* 是可选的：如果不使用它，您必须使用语法 pychrono.ChClassFoo... 来调用所有 Chrono 函数，而如果使用 *as chrono*，您只需像 C++ 等效命名空间一样重命名命名空间：chrono.ChClassFoo...

- 让我们创建一个 3D 向量对象：

~~~~~~~~~~~~~~~python
my_vect1 = chrono.ChVector3d()
~~~~~~~~~~~~~~~

(请注意，通过这种方式，所有 PyChrono 类都以 *chrono* 作为前缀。)

- 修改该向量对象的属性；这是使用 **.** 点操作符完成的：

~~~~~~~~~~~~~~~python
my_vect1.x=5
my_vect1.y=2
my_vect1.z=3
~~~~~~~~~~~~~~~

- 一些类有构建参数，例如可以通过传递 3 个坐标来快速初始化另一个向量：

~~~~~~~~~~~~~python
my_vect2 = chrono.ChVector3d(3,4,5)
~~~~~~~~~~~~~

- C++ 中 Chrono 向量和矩阵所具备的大多数运算符重载功能，在 Python 中同样可用，例如：

~~~~~~~~~~~~~~~python
my_vect4 = my_vect1*10 + my_vect2
~~~~~~~~~~~~~~~

-   对象的成员函数可以简单地使用 **.** 点操作符调用，就像在 C++ 中一样：

~~~~~~~~~~~~~~~python
my_len = my_vect4.Length()
print ('vector length =', my_len)
~~~~~~~~~~~~~~~

-   您可以使用大多数在 C++ 中使用的类，例如让我们玩转四元数和向量：

~~~~~~~~~~~~~python
my_quat = chrono.ChQuaterniond(1,2,3,4)
my_qconjugate = ~my_quat
print ('quat. conjugate  =', my_qconjugate)
print ('quat. dot product=', my_qconjugate ^ my_quat)
print ('quat. product=',     my_qconjugate % my_quat)
my_vec = chrono.ChVector3d(1,2,3)
my_vec_rot = my_quat.Rotate(my_vec)
~~~~~~~~~~~~~

PyChrono 的线性代数类（如 ChMatrixDynamicd 和 ChVectorDynamicd）已与 Python 列表进行了接口对接，这使得您可以使用任何第三方包来执行线性代数运算。在下面的示例中，我们将使用 NumPy：

~~~~~~~~~~~~~python
mlist = [[1,2,3,4], [5,6,7,8], [9,10,11,12], [13,14,15,16]]
ma = chrono.ChMatrixDynamicd() 
ma.SetMatr(mlist)   # Create a Matrix from a list. Size is adjusted automatically.
npmat = np.asarray(ma.GetMatr()) # Create a 2D npy array from the list extracted from ChMatrixDynamic
w, v = LA.eig(npmat)  # get eigenvalues and eigenvectors using numpy
mb = chrono.ChMatrixDynamicd(4,4)
prod = v * npmat  
mb.SetMatr(v.tolist())    
~~~~~~~~~~~~~

-  如果您想知道一个类中有哪些方法和/或属性可用，您可以简单地使用 IDE（如 Spyder 或 VisualStudio Code）的代码完成特性：例如，一旦你输入 *chrono.*，你就会看到一个弹出窗口，里面列出了可用的类、常量等。

<div class="ce-info">
大多数类的行为与其 C++ 对应类相似，因此建议您查阅 [C++ API 文档](http://api.chrono.projectchrono.org) 以了解其功能。目前尚未通过 Sphinx 自动生成 Python API 文档，因此您应参考 C++ API 文档。

</div>

进一步阅读
---------------

- 前往 [教程](@ref tutorial_table_of_content_pychrono) 获取示例。

- 您可以在 [参考](@ref pychrono_reference) 页面找到有关 PyChrono 与 C++ Chrono 区别的更多信息。
