PyChrono 技术参考 {#pychrono_reference}
==========================

PyChrono 是 Chrono 的 Python 封装。它是一组Python 模块，对应于 Chrono 的各个单元，如下图所示：

![](http://www.projectchrono.org/assets/manual/Units_python.png)

Python 与 C++ 的区别
----------------------------------

并非所有 C++ API 的功能都可以 1:1 映射到 Python API。当然，Python 是一种解释型语言，与 C++ 在许多方面有所不同，因此存在一些差异和限制，但也有优势。如果您已经使用过 Chrono 的 C++ API，您会发现本指南对于快速入门 PyChrono 开发非常有用。

### 对象创建

在 C++ 中，您可以通过两种方式创建对象：在栈上和在堆上（后者用于*动态分配*）。例如，分别如下所示，这是 **C++ 语言中的对象创建**

~~~~cpp
chrono::ChSystem  my_system;  // 在栈上，或者..
chrono::ChSystem* my_system_pointer = new chrono::ChSystem();  // 在堆上 
~~~~

在第二种情况下，在 C++ 中您必须记得在某个时候使用 *delete (my\_system\_pointer)* 来释放对象。而在 Python 中，对象的创建总是以一种方式完成：*objectname = namespace.classname()*，并且不需要记得删除对象，因为对象的生命周期由 Python 自动管理。因此，**在 Python 中创建对象** 非常简单：

~~~~~~~~~~~~~~~python
my_vect = chrono.ChSystem()
~~~~~~~~~~~~~~~

请注意，Python 中的 = 运算符并不意味着*复制*（对于整数、浮点数等简单类型除外），而是意味着*赋值*，所以例如

~~~~~~~~~~~~~~~python
my_systemA = chrono.ChSystem()
my_systemB = my_systemA      # 为同一个系统分配另一个句柄
my_systemA.SetTol(2)
print (my_systemB.GetTol())
~~~~~~~~~~~~~~~

将输出 2，因为您创建了一个单一的 ChSystem 对象，并且有两个句柄指向它。

### 模板类

目前 Python 不支持模板类。因此，所有依赖模板的 C++ 类都需要在 Python 中进行封装，以提供最相关的特化。由于最基本的模板类为最常见的特化提供了别名，这些名称也反映在 Python 封装中。

~~~~~~~~~~~~~~~python
chrono.ChVector3d         # 就像 C++ 里的 ChVector3d 一样
chrono.ChQuaterniond      # 就像 C++ 里的 ChQuaterniond 一样
chrono.ChMatrix33d        # 就像 C++ 里的 ChMatrix33d 一样
chrono.ChMatrixDynamicd   # 就像 C++ 里的 ChMatrixDynamic<double> 一样
chrono.ChFramed           # 就像 C++ 里的 ChFramed 一样
chrono.ChFrameMovingd     # 就像 C++ 里的 ChFrameMoving<double> 一样
chrono.ChCoordsysd        # 就像 C++ 里的 ChCoordsysd 一样
~~~~~~~~~~~~~~~

目前对模板的模板（尤其是 std::vector<> 容器）有（相当有限的）支持。概念是相同的：C++ 模板在 Python 中被翻译为一个特殊的名称。对于 std::vector，我们在前面加上 vector_ 前缀：

~~~~~~~~~~~~~~~python
chrono.vector_ChVector3d   # 就像 C++ 里的 std::vector<ChVector<double>> 一样
~~~~~~~~~~~~~~~

### ChVector x y z 分量

在 C++ 中，您可以使用函数 ```x() y() z()``` 访问 3D 向量的 x y z 分量，这些函数返回对分量的引用。为了避免一些问题，我们去掉了 () 括号，并将这些函数映射为 Python 中对 ```x y z``` 类成员的直接访问，因此：

~~~~cpp
chrono::ChVector<double>  my_vector;
my_vector.x() = 123;
double sum = my_vector.y() + my_vector.z();
~~~~

变为

~~~~~~~~~~~~~~~python
chrono.ChVector3d  my_vector
my_vector.x = 123
sum = my_vector.y + my_vector.z
~~~~~~~~~~~~~~~

类似的概念也适用于四元数的分量 e0 e1 e2 e3，例如，在 Python 中使用 myquaternion.e0，而不是在 C++ 中使用 myquaternion.e0()。

### 共享指针

除了向量、矩阵等，大多数使用 Chrono API 创建的复杂对象都是通过 C++ 共享指针管理的。这是 ChBody 部件、ChLink 约束等的情况。共享指针是一种 C++ 技术，允许用户创建对象而不必担心删除，因为删除是自动管理的。在 Chrono C++ API 中，这些共享指针是基于模板的；正如我们之前所说，Python 不支持模板，但这不是问题，因为 PyChrono **会在必要时自动处理共享指针对象**。

这是一个 **C++ 中共享指针的示例** :

~~~~cpp
std::shared_ptr<ChLinkLockRevolute>  my_link_BC(new ChLinkLockRevolute);
~~~~

这是 **Python** 中的等效语法：

~~~~~~~~~~~~~~~{.py}
my_link_BC = chrono.ChLinkLockRevolute()
~~~~~~~~~~~~~~~

<div class="ce-info">
在 PyChrono 中创建共享指针对象时，被引用的对象也会同时被创建。例如，在上一个示例中，旋转副（revolute joint）就是在同一行代码中创建的。如果你需要指向同一对象的其他共享指针，只需输入 ```my_link_other = my_link_BC``` 等即可。
</div>

向下转型和向上转型
-------------------------

#### 向上转型

向派生类到基类的向上转型在 Python 中是**自动**进行的，不需要干预。我们也为共享指针实现了这一点。例如，*ChSystem.Add()* 需要一个指向 *ChPhysicsItem* 对象的（共享）指针，这是一个基类，但你可以传递一个 *ChBody*、*ChLinkLockGear* 等派生类。在 Python 中也是一样。

#### 向下转型

一个更大的问题是将基类向派生类的向下转型。也就是说，如果一个函数 *返回* 一个指向基类的指针，如何理解特定返回对象属于派生类？在撰写本文时，自动向下转型仅对继承自 ChFunction 和 ChAsset 的类执行。否则，必须使用 `CastToXXX()` 辅助函数进行手动向下转型；这有点类似于 C++ 中的 ```dynamic_cast<derived>(base)``` 方法。目前，这些转换函数为许多共享指针提供。在 Python 中使用如下示例：

~~~~~~~~~~~~~~~python
mybody = chrono.CastToChBody(ptr_to_contactable)
~~~~~~~~~~~~~~~

### 嵌套类

SWIG 目前不支持 Python 中的嵌套类（参见 http://www.swig.org/Doc4.0/SWIGPlus.html#SWIGPlus_nested_classes）。嵌套类可以被忽略，或者像在 PyChrono 中一样，被“展平”处理。Chrono 会自动对每一个嵌套类执行此操作。这意味着 C++ 嵌套类在 PyChrono 中的对应版本将位于上层的命名空间级别中，你可以从以下示例中看到这一点：

~~~~~~~~~~~~~~~cpp
// 在 C++ 中继承 ReportContactCallback 的类
class ContactReporter : public ChContactContainer::ReportContactCallback { ... etc ...
// 枚举类:
vehicle.SetChassisVisualizationType(chrono::vehicle::VisualizationType::MESH);
~~~~~~~~~~~~~~~

在 Python 中我们有:

~~~~~~~~~~~~~~~py
# 在 Python 中继承 ReportContactCallback 的类
class ContactReporter(chrono.ReportContactCallback): ...etc...
# 同样的原则适用于枚举类:
vehicle.SetChassisVisualizationType(pychrono.vehicle.VisualizationType_MESH)
~~~~~~~~~~~~~~~

### 不支持的类

我们设法在 Python 中映射了大多数常用的 C++ 类，但可能仍有一些类或函数尚未映射到 Python。这可以通过以下方式理解。正确映射的函数将返回对象，其类型在解释器窗口中显示为:

~~~~~~~~~~~~~~~python
my_system.GetGravitationalAcceleration()
<pychrono.ChVector3d; 
proxy of <Swig Object of type 'chrono::ChVector< double > *' at 0x03EDCEA8> >
~~~~~~~~~~~~~~~

尚未映射的函数，例如 ChSystem.GetSystemDescriptor()，将给出较短的回显，表示指向在 Python 中不可用的对象的指针的类型信息：

~~~~~~~~~~~~~~~python
my_system.GetSystemDescriptor()
<Swig Object of type 'chrono::ChSystemDescriptor *' at 0x03EDD800>
~~~~~~~~~~~~~~~

<div class="ce-info">
随着 PyChrono 的发展，后一种情况将越来越少发生。如果你在某些函数中遇到此类问题，请告诉我们，以便我们修复它。
</div>

演示与示例
------------------

你可以在 [这些教程](@ref tutorial_table_of_content_pychrono) 中找到使用示例。
