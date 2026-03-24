
坐标系 {#coordinate_systems}
==============================

平移和旋转以及它们的变换是 Chrono 库中的关键元素。

虽然三维空间中的平移 _仅_ 以 [向量](#manual_ChVector3) 表示，但用户可能会遇到 [四元数](#manual_ChQuaternion) 或更少见的 [旋转矩阵](#manual_ChMatrix33) 来表示旋转（通常出于性能原因）。  
建议尽可能 **依赖四元数**，并在需要时利用适当的转换为旋转矩阵。

Chrono 依赖不同的对象来表示坐标系（[ChCoordsys](#manual_ChCoordsys)、[ChFrame](#manual_ChFrame)、[ChFrameMoving](#manual_ChFrameMoving)、@ref chrono::ChMarker "ChMarker" 等），以利用不同的功能和优化。  
然而，用户通常只需要处理 [ChCoordsys](#manual_ChCoordsys) 或 [ChFrame](#manual_ChFrame)，我们建议初学者专注于这两者。

一些关于整体结构的基本知识可能有助于更好地处理这些对象：

- [ChCoordsys](#manual_ChCoordsys) 和 [ChFrame](#manual_ChFrame) 是最重要的基类；
- [ChCoordsys](#manual_ChCoordsys) 是最基本的对象，仅由一对 `ChVector3` 和一个 `ChQuaternion` 组成；
- [ChFrame](#manual_ChFrame) 是 Chrono 中最常用的类；它嵌入了一个 `ChCoordsys` 并仅添加了一个旋转矩阵以提高性能；
- [ChCoordsys](#manual_ChCoordsys) 和 [ChFrame](#manual_ChFrame) 都可以轻松地进行各种变换和坐标变换（平移和旋转）；
- [ChFrameMoving](#manual_ChFrameMoving) 在速度和加速度层面上添加了变换；
- @ref chrono::ChMarker "ChMarker" 提供了类似于 `ChFrameMoving` 的功能，但它附着在刚体上并在运动过程中跟随它；

所有在本页讨论的类都是模板化的，以便可以容纳不同的标量类型。然而，为了使代码更简洁，提供了一些针对 `double`、`float` 和有时 `int` 类型的特化。它们的名称遵循模式 `ClassName[d|f|i]`。

\tableofcontents

# 向量  {#manual_ChVector3}

表示三维空间中点的向量由 @ref chrono::ChVector3<> "ChVector3" 类定义。

在数学符号中：

\f[
\mathbf{p}=\{p_x, p_y, p_z\}
\f]

### 构造方法

@ref chrono::ChVector3<> "ChVector3" 的一般构造方法是通过其构造函数

~~~{.cpp}
ChVector3d vect1(1, 2, 3); // 等同于： ChVector3<double> vect1(1, 2, 3);
ChVector3d vect1(VECT_X); // 等同于： ChVector3<double> vect1 = VECT_X;
~~~

不过，Chrono 还提供了一组非常实用的常量（双精度）向量——`VNULL`, `VECT_X`, `VECT_Y`, `VECT_Z`，它们分别代表零向量和坐标轴单位向量。

### 使用方法

用于存储三个系数，可通过 @ref chrono::ChVector3<>::x()、`y()` 或 `z()` 方法进行访问。

由于 `ChVector3` 并未继承自 Eigen 向量，因此需要通过 @ref chrono::ChVector3<>::eigen() ".eigen()" 方法进行转换，才能使用 Eigen 的各项功能。

`ChVector` 可以通过以下方式进行修改和使用：

- 它们的方法，如类接口中定义的，包括所有重载的运算符 `+`、`-`、`*` 等。
- 自由函数，以大写字母 `V` 开头，如 `Vcross`

# 四元数  {#manual_ChQuaternion}

Chrono 中的旋转主要由四元数描述，如 @ref chrono::ChQuaternion<> "ChQuaternion" 类所实现，根据轴-角对表示法：

\mathbf{q}=\left\{
\begin{array}{c}
q_0\\
q_1\\
q_2\\
q_3
\end{array}
\right\}=\left\{
\begin{array}{c}
\cos(\theta / 2)\\
{u}_x \sin(\theta / 2)\\
{u}_y \sin(\theta / 2)\\
{u}_z \sin(\theta / 2)
\end{array}
\right\}
\f]

需要注意的是，标量部分位于第一个位置。

由于类的模板性质，需要指定标量类型；然而，提供了一些有用的预定义特化，例如 `ChQuaterniond` 用于双精度类型。

![](http://www.projectchrono.org/assets/manual/coord_quaternions.png)

请记住：

- 只有单位范数的四元数表示有效的旋转；
- 中性四元数 @ref chrono::QUNIT "QUNIT"，表示没有旋转，由四元组 `(1, 0, 0, 0)` 定义。

### 构造

四元数可以通过在构造函数中显式提供其分量来构建，例如：
  
~~~{.cpp}
ChQuaterniond q(1, 0, 0, 0);
~~~

但在许多情况下，从以下方式构建更为方便：

- `QuatFrom___` 自由函数，定义在 [ChRotation.h](https://github.com/projectchrono/chrono/blob/main/src/chrono/core/ChRotation.h) 中。  
  例如 @ref chrono::QuatFromAngleAxis "QuatFromAngleAxis" 或 @ref chrono::QuatFromAngleY "QuatFromAngleY"
- 预定义的四元数，定义在 [ChQuaternion.h](https://github.com/projectchrono/chrono/blob/main/src/chrono/core/ChQuaternion.h) 中。  
  例如 `Q_ROTATE_Z_TO_X` 或 @ref chrono::QUNIT "QUNIT"

### 使用方法

`ChQuaternion` 类允许对其他对象应用旋转，无论是 @ref chrono::ChVector3<> "ChVector3"、@ref chrono::ChFrame "ChFrame" 还是其他 `ChQuaternion`。

可以通过使用 `.Rotate()` 成员函数轻松地对点进行四元数旋转。下面的示例展示了如何绕 Y 轴旋转一个点 20 度：

~~~{.cpp}
ChVector3d vA(1, 2, 3);
ChQuaterniond q = QuatFromAngleY(20 * CH_DEG_TO_RAD);
ChVector3d vB = q.Rotate(vA);
~~~

`*` 运算符用于执行四元数（Hamilton）乘法。从运动学的角度来看，这表示旋转的连接。例如，旋转 **qA** 后跟旋转 **qB** 可以通过预乘法合并为单个旋转 **qC**，如下所示：

~~~{.cpp}
qC = qB * qA; // 连接两个旋转，先 qA 后 qB
~~~

或者，为了方便，可以使用 `>>` 运算符来实现相同的结果，但按从左到右的顺序书写：

~~~{.cpp}
qC = qA >> qB; // 连接两个旋转，先 qA 后 qB（与之前的结果相同）
~~~

# 旋转矩阵  {#manual_ChMatrix33}

作为四元数的替代方案，Chrono 提供了使用 3x3 旋转矩阵 \f$ \mathbf{R} \in \mathsf{SO}(3) \f$ 来描述一个参考系相对于另一个参考系的方向（具体信息请参见 @ref chrono::ChMatrix33）。请注意，旋转矩阵是正交归一的，因此 \f$ \mathbf{R}^{-1} = \mathbf{R}^{T} \f$。

有多种方法可以创建旋转矩阵并将其转换为其他表示形式。下面的示例说明了一些构造选项：

~~~{.cpp}
ChMatrix33d rotmA(1); // 从对角线上的值构建（例如单位矩阵）
ChMatrix33d rotmB(quat); // 从四元数构建
ChMatrix33d rotmC(angle, axis); // 从角度和轴构建
ChMatrix33d rotmD(vecX, vecY, vecZ); // 从列向量构建
~~~

`*` 运算符可用于相乘两个旋转矩阵。例如，旋转 **rotmA** 后跟旋转 **rotmB** 可以表示为：

~~~{.cpp}
ChMatrix33d rotmC = rotmB * rotmA; // 连接两个旋转，先 rotmA 后 rotmB
~~~

`*` 运算符也可用于与 ChVector3d 相乘；这对应于旋转向量：

~~~{.cpp}
ChVector3d vB = rotm * vA;
~~~

# ChCoordsys   {#manual_ChCoordsys}

A @ref chrono::ChCoordsys represents a coordinate system in 3D space. It embeds both a vector (coordinate translation \f$ \mathbf{d} \f$ ) and a quaternion (coordinate rotation \f$ \mathbf{q} \f$ ):
一个 @ref chrono::ChCoordsys 表示三维空间中的一个坐标系。它同时包含一个向量（坐标平移 \f$ \mathbf{d} \f$ ）和一个四元数（坐标旋转 \f$ \mathbf{q} \f$ ）：

\f[
\mathbf{c}=\{\mathbf{d},\mathbf{q}\}
\f]

ChCoordsys 是 ChFrame 的轻量级版本，后者将在下一节中讨论。

# ChFrame   {#manual_ChFrame}

@ref chrono::ChFrame 与 ChCoordsys 一样，用于表示三维空间中的一个坐标系，但它包含了更高级的功能。

![](http://www.projectchrono.org/assets/manual/coord_frame.png)

如上图所示，ChFrame 对象表示坐标系 **b** 相对于另一个坐标系 **a** 的“旋转”和“位移”。通常 **a** 是绝对参考系。

<div class="ce-info">
下文中的符号表示
\f[
\mathbf{d}_{a,b(c)}
\f]
用于定义一个向量 \f$ \mathbf{d} \f$，其终点在点 \f$ a \f$，起点在点 \f$ b \f$，
并以基 \f$ c \f$ 表示（即沿坐标系 \f$ c \f$ 的 x,y,z 轴测量）。
如果省略 \f$ b \f$，则假定其为绝对参考系的原点。
</div>

坐标系 \f$ c \f$ ).
如果省略 \f$ b \f$，则假定其为绝对参考系的原点。
</div>

作为 ChCoordsys，ChFrame 对象具有一个用于平移的向量和一个用于旋转的四元数：

\f[
\mathbf{c}=\{\mathbf{d},\mathbf{q}\}
\f]

然而，ChFrame 类还存储了一个辅助的 3x3 旋转矩阵，可以在四元数效率较低的情况下加速计算。从这个意义上说，ChCoordsys 可以被视为 ChFrame 的轻量级版本，如果不需要高级功能，可以节省内存。

## 构造

有多种方法可以构建 ChFrame；例如：

~~~{.cpp}
ChFramed Xa; // 构建默认坐标系：零平移，无旋转
ChFramed Xb(vec, quat); // 从给定的平移向量和旋转四元数构建
ChFramed Xc(csys); // 从给定的 ChCoordysd 构建
ChFramed Xd(vec, theta, u); // 从平移向量和绕轴旋转构建
~~~

## 使用方法

ChFrame 类的一个重要特性是能够对坐标变换进行应用：

- *方向*：变换应用于描述 _方向_ 的向量：
  向量仅旋转，但由于新参考系原点的位置不同，不会应用偏移；
  \f[
    \mathbf{d}_{P,a(a)}=\mathbf{R}_{ba} \mathbf{d}_{P,b(b)}
  \f]
  相关方法为 @ref chrono::ChFrame<>::TransformDirectionLocalToParent() "ChFrame<>::TransformDirectionLocalToParent()" 和 @ref chrono::ChFrame<>::TransformDirectionParentToLocal() "ChFrame<>::TransformDirectionParentToLocal()";
- *位置*：变换应用于描述 _位置_ 的向量：
  当变换时，向量会旋转，并考虑新参考系的不同位置
  \f[
    \mathbf{d}_{P,a(a)}=\mathbf{d}_{b,a(a)} + \mathbf{R}_{ba} \mathbf{d}_{P,b(b)}
  \f]
  相关方法为 @ref chrono::ChFrame<>::TransformPointLocalToParent() "ChFrame<>::TransformPointLocalToParent()" 和 @ref chrono::ChFrame<>::TransformPointParentToLocal() "ChFrame<>::TransformPointParentToLocal()";
- *力矩* 变换：变换应用于力矩，即力和力矩的组合：
  在不同参考系中表示的力会导致额外的力矩分量，仅仅是由于参考系的变化。
  相关方法为 @ref chrono::ChFrame<>::TransformWrenchLocalToParent() "ChFrame<>::TransformWrenchLocalToParent()" 和 @ref chrono::ChFrame<>::TransformWrenchParentToLocal() "ChFrame<>::TransformWrenchParentToLocal()"。

方向和位置变换是最常用的功能，因此值得进一步详细说明。例如，我们可以考虑将一个点从局部坐标系 **b** 转换到另一个（例如绝对）坐标系 **a**：

![](http://www.projectchrono.org/assets/manual/coord_trasf1_point.png)

这个 _仿射_ 变换可以表示为：

\f[
\mathbf{d}_{P,a(a)}=\mathbf{d}_{b,a(a)} + \mathbf{R}_{ba} \mathbf{d}_{P,b(b)}
\f]

在 Chrono 中，这个过程可以表示为，不使用 `ChFrame<>`：

~~~{.cpp}
ChVector3d d_Pa_a; // 从点 a 出发、终点为 P 的向量，用坐标系 (a) 表示
ChVector3d d_ba_a; // 从点 a 出发、终点为 b 的向量，用坐标系 (a) 表示
ChVector3d d_Pb_b; // 从点 b 出发、终点为 P 的向量，用坐标系 (b) 表示
ChMatrix33d R_ba; // 坐标系 (b) 相对于坐标系 (a) 的旋转矩阵
...
d_Pa_a = d_ba_a + R_ba * d_Pb_b;
~~~

另一方面，通过使用 `ChFrame<>` 方法，可以简化符号表示，利用以下三种类似的方法之一：

- 使用 `Transform[Direction|Point]ParentToLocal`|`Transform[Direction|Point]LocalToParent`；
  更冗长的标准方法
- 使用 `*` 运算符；

  ~~~{.cpp}
  ChVector3d d_Pa_a; // vector with endpoint P, starting from point a, expressed in frame (a)
  ChVector3d d_Pb_b; // vector with endpoint P, starting from point b, expressed in frame (b)
  ChFramed X_ba; // frame (b) (i.e. position and rotation) expressed with respect to frame (a)
  ...
  d_Pa_a = X_ba * d_Pb_b;
  ~~~

- 使用 `>>` 运算符；

~~~{.cpp}
ChVector3d d_Pa_a; // 从点 a 出发、终点为 P 的向量，用坐标系 (a) 表示
ChVector3d d_Pb_b; // 从点 b 出发、终点为 P 的向量，用坐标系 (b) 表示
ChFramed X_ba; // 坐标系 (b) (即位置和旋转) 相对于坐标系 (a) 表示
...
d_Pa_a = X_ba * d_Pb_b;
~~~

同样的概念可以用于链式坐标变换。例如，如果已知从坐标系 **c** 到 **b** 的变换以及从 **b** 到 **a** 的变换，则可以获得整体的坐标系旋转和位移

![](http://www.projectchrono.org/assets/manual/coord_trasf3_frame.png)

~~~{.cpp}
ChFramed X_ba, X_cb, X_ca;
...
X_ca = X_ba * X_cb;
~~~

或者，等效地，使用 `>>` 运算符：

~~~{.cpp}
X_ca = X_cb >> X_ba;
~~~

在 Chrono 中，大多数 ChCoordsys<>, ChFrame<> 和 ChFrameMoving<>（如下所定义）之间的变换可以用两种等效方式表示： <br>
  - 使用 * 运算符 _从右到左_ 变换，如：
    ```X_ca = X_ba * X_cb``` <br>
  - 使用 >> 运算符 _从左到右_ 变换，如：
    ```X_ca = X_cb >> X_ba```  <br>

后者有一些优势： <br>
- 它更“直观”（参见下标 cb-ba 如何遵循“链”） <br>
- 它利用默认的编译器操作优先级规则（从左到右）来提高计算性能 <br>
例如，如果第一个操作数是一个向量，如 ```vnew = v >> X_dc >> X_cb >> X_ba```，
编译器的默认行为会导致一系列矩阵与 ChFrame 的操作返回临时向量。相反，* 运算符会创建多个 `ChFrame<>` 临时对象，这会更慢。

同样可以将 * 或 >> 运算符用于其他对象，
例如在 ChFrame Xa 和 ChVector3 vb 之间使用 >>。该操作的结果是通过向量 vb 平移旧的 ChFrame 对象得到的新 ChFrame 对象：

~~~{.cpp}
ChVector3d vb;
ChFramed Xa, Xt; ...
Xt = Xa >> vb;    // also  Xt = vb * Xa;
~~~

同样适用于就地操作符 *= 或 >>=，它们可以用于平移或旋转 ChFrame，或者完全变换，具体取决于它们的使用方式：与 ChVector3、ChQuaternion 或另一个 ChFrame 一起使用。例如，要将 Xa 平移向量 vb，可以这样写：

~~~{.cpp}
Xa >>= vb;    
~~~

注意，虽然 * 和 >> 运算符会创建临时对象，但 *= 或 >>= 并不会，这会提高效率。在这种情况下，一个经验法则是避免：

 - 使用 * 和 >> 运算符
 - 使用低级函数，如 TransformLocalToParent、TransformParentToLocal 等。

“*”和“>>”运算均支持逆变换。

例如，在关系式 X_ca = X_cb >> X_ba 中，假设已知 X_ca 和 X_cb，并且希望计算 X_ba。将方程两边同时左乘 X_cb 的逆矩阵得到

~~~{.cpp}
X_ba = X_cb.GetInverse() >> X_ca;    
~~~

注意，GetInverse 操作可能不如低级方法高效，在这种情况下，可以使用不太直观但更高效的低级方法 TransformParentToLocal()，即：

~~~{.cpp}
X_ba = X_cb.TransformParentToLocal(X_ca);    
~~~

API的细节请参见 @ref chrono::ChFrame。

# ChFrameMoving    {#manual_ChFrameMoving}

@ref chrono::ChFrameMoving 对象用于表示三维空间中的一个坐标系，与 ChFrame 类似，但它还额外存储了该坐标系的速度和加速度信息：

\f[
\mathbf{c}=\{\mathbf{p},\mathbf{q},\dot{\mathbf{p}}, \dot{\mathbf{q}}, \ddot{\mathbf{p}}, \ddot{\mathbf{q}} \}
\f]

注意，使用四元数导数来表示角速度和角加速度可能比较繁琐。因此，该类还可以通过角速度  \f$ \mathbf{\omega} \f$ 和角加速度 \f$ \mathbf{\alpha} \f$ 来设置和获取这些数据：

\f[
\mathbf{c}=\{\mathbf{p},\mathbf{q},\dot{\mathbf{p}}, \mathbf{\omega}, \ddot{\mathbf{p}}, \mathbf{\alpha}\}
\f]

以下图示可以直观地说明这一点：

![](http://www.projectchrono.org/assets/manual/coord_framemoving.png)

注意，角速度和角加速度可以在移动坐标系的基底或绝对坐标系中设置/获取。

示例：创建一个 ChFrameMoving 对象并分配非零的角速度和线速度，同时分配线性和角加速度。

~~~{.cpp}
ChFrameMoving<> X_ba;
X_ba.SetPos(ChVector3d(2,3,5));
X_ba.SetRot(myquaternion);

// set velocity 
X_ba.SetPos_dt(ChVector3d(100,20,53)); 
X_ba.SetWvel_loc(ChVector3d(0,40,0)); // W 在局部坐标系中，或者……
X_ba.SetWvel_par(ChVector3d(0,40,0)); // W 在父坐标系中

// set acceleration
X_ba.SetPos_dtdt(ChVector3d(13,16,22)); 
X_ba.SetWacc_loc(ChVector3d(80,50,0)); // a 在局部坐标系中，或者……
X_ba.SetWacc_par(ChVector3d(80,50,0)); // a 在父坐标系中
~~~

@ref chrono::ChFrameMoving 对象可以用于变换 ChVector3（空间中的点）、ChFrame 或 ChFrameMoving 对象。速度也会被计算和变换。

示例：如果已知从 **b** 到 **a** 的变换以及从 **c** 到 **b** 的变换，可以计算 **c** 相对于 **a** 的绝对速度和角速度：

![](http://www.projectchrono.org/assets/manual/coord_trasf5_framemoving.png)

上述情况可以用以下等效表达式表示，
使用两种替代形式（基于 >> 运算符的从左到右，或基于 * 运算符的从右到左）：

~~~{.cpp}
X_ca = X_cb >> X_ba;
X_ca = X_ba * X_cb;
~~~

这与 ChFrame 和 ChCoordsys 中使用的代数运算_完全相同_，唯一的区别是，这次同时也会对速度和加速度进行变换。

注意，变换会自动考虑复杂项的贡献，例如向心加速度、相对加速度、科里奥利加速度等。

以下是另一个具有更长变换串联的示例：

![](http://www.projectchrono.org/assets/manual/coord_trasf6_framemoving.png)

注意，也可以使用帧变换的逆变换，使用 GetInverse()，如 ChFrame 所示。

示例：计算移动目标 8 相对于夹持器 6 的位置、速度和加速度，并以帧 6 的基底表示。

![](http://www.projectchrono.org/assets/manual/coord_robotexample.png)

如何在已知其他所有变换的情况下计算 X_86？从 X_80 的两个等效表达式开始：

    X_86>>X_65>>X_54>>X_43>>X_32>>X_21>>X_10 = X_87>>X_70; 

另外：

    X_86>>(X_65>>X_54>>X_43>>X_32>>X_21>>X_10) = X_87>>X_70;

将两边同时右乘 (...) 的逆矩阵，记住一般情况下

- X >> X.GetInverse() = I
- X.GetInverse() >> X = I,

其中 I 是可以去掉的单位变换，最终得到：

~~~{.cpp}
X_86 = X_87 >> X_70 >> (X_65 >> X_54 >> X_43 >> X_32 >> X_21 >> X_10).GetInverse();
~~~

示例：基于相同的图示，计算夹持器相对于移动目标 8 的速度和加速度，并以参考帧 8 的基底表示。

~~~{.cpp}
X_68 = X_12 >> X_23 >> X_34 >> X_45 >> X_56 >> (X_87 >> X_70).GetInverse();
~~~

API的详细信息请参见 @ref chrono::ChFrameMoving。

# ChMarker    {#manual_ChMarker}

ChMarker 对象是辅助坐标系，其特定功能是跟随所附的 [刚体](@ref rigid_bodies)，同时可能相对于刚体移动。

![](http://www.projectchrono.org/assets/manual/pic_ChMarker.png)

ChMarker 通常用于 @ref chrono::ChLinkLock "ChLinkLock" 链接系列。

# 理论

关于 Chrono 中坐标变换的理论方面的更多细节：
- [旋转的 PDF 白皮书](http://projectchrono.org/assets/white_papers/rotations.pdf)
- [坐标的 PDF 白皮书](http://projectchrono.org/assets/white_papers/frame_kinematics.pdf)
