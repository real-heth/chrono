
Chrono 中的数学对象   {#mathematical_objects}
==============================

该文档部分主要介绍 Chrono 的数学函数和类。这些概念在 Chrono API 的其他部分非常普遍，同时也将在 @ref chrono_linalg API 文档中进行讨论。

\tableofcontents

# 线性代数  {#linear_algebra}

处理向量和矩阵是 Chrono API 中的一个反复出现的主题。Chrono 使用 [Eigen3](https://eigen.tuxfamily.org/dox/index.html) 来表示所有矩阵（稠密和稀疏）和向量。

Chrono 中的稠密矩阵通过标量类型进行模板化，并采用行优先的存储顺序。下面列出的所有 Chrono 矩阵和向量类型都只是 Eigen 矩阵类型的别名；详见 @ref chrono_linalg 和 ChMatrix.h 头文件。

<div class="ce-info">
[ChVector3](@ref chrono::ChVector3) 和 [ChVector2](@ref chrono::ChVector2) 类分别用于表示空间中的 3D 向量和平面中的 2D 向量，它们不是 Eigen 类型，也不是从 Eigen 矩阵派生的。
</div>

矩阵的索引从 0 开始，使用 (行,列) 索引：

\f[
\mathbf{A}=\left[
\begin{array}{cccc}
a_{0,0} & a_{0,1} & a_{0,2} & ... \\
a_{1,0} & a_{1,1} & a_{1,2} & ... \\
a_{2,0} & ... & ... & ... \\
a_{n_{rows}-1,0} & ... & ... & a_{n_{rows}-1,n_{cols}-1} 
\end{array}
\right]
\f]

Chrono 中有许多矩阵和向量的特化类型，下面将介绍它们的一些基本特性。

<br>
**动态大小矩阵。**
使用 [ChMatrixDynamic](@ref chrono::ChMatrixDynamic) 创建具有通用大小的矩阵，例如 12 行 x 4 列。ChMatrixDynamic 是按标量类型进行模板化的，默认类型为 `double`。

~~~{.cpp}
chrono::ChMatrixDynamic<double> A(12,4);
~~~

<br>
**固定大小矩阵。**
使用 [ChMatrixNM](@ref chrono::ChMatrixNM) 创建不需要调整大小且在编译时已知大小的矩阵。

~~~{.cpp}
chrono::ChMatrixNM<double,4,4> B;
~~~

<div class="ce-info">
**来自 Eigen 文档:**
<br><br>
什么时候应该使用固定大小，什么时候应该使用动态大小？简单的答案是：对于非常小的尺寸，尽可能使用固定大小，而对于较大的尺寸或必须使用的情况，使用动态大小。对于小尺寸，特别是小于（大约）16 的尺寸，使用固定大小对性能有很大好处，因为它允许 Eigen 避免动态内存分配并展开循环。
<br><br>
使用固定大小的限制当然是，这只有在编译时知道尺寸时才可能。此外，对于足够大的尺寸，例如大于（大约）32 的尺寸，使用固定大小的性能优势变得可以忽略不计。更糟的是，尝试在函数内部使用固定大小创建非常大的矩阵可能会导致堆栈溢出，因为 Eigen 会尝试将数组自动分配为局部变量，而这通常是在堆栈上完成的。最后，根据情况，当使用动态大小时，Eigen 也可能更积极地尝试向量化（使用 SIMD 指令）。
</div>

<br>
**3x3 固定大小矩阵。**
使用 @ref chrono::ChMatrix33 "ChMatrix33" 创建 3x3 矩阵，这些矩阵主要用于表示旋转矩阵和 3D 惯性张量。  
ChMatrix33 是按标量类型进行模板化的（默认类型为 `double`）。该矩阵类型派生自具有行优先存储的 3x3 固定大小 Eigen 矩阵，并提供了多个专用构造函数和用于坐标和旋转操作的方法。

~~~{.cpp}
	chrono::ChMatrix33d R;
~~~

<br>
**动态大小列向量。**
使用 [ChVectorDynamic](@ref chrono::ChVectorDynamic) 创建具有通用行数的列向量（单列矩阵）。

~~~{.cpp}
chrono::ChVectorDynamic<double> v(12);
~~~

<br>
**固定大小列向量。**
使用 @ref chrono::ChVectorN "ChVectorN" 创建具有固定长度（在编译时已知）的列向量。

~~~{.cpp}
chrono::ChVectorN<double,6> w;
~~~

<br>
**行向量。**
使用 @ref chrono::ChRowVectorDynamic "ChRowVectorDynamic" 和 @ref chrono::ChRowVectorN "ChRowVectorN" 创建行向量（单行矩阵），分别具有动态大小和固定大小。

<br>
此外，用于多体系统形式的专用 3x4、4x3 和 4x4 矩阵在 [ChMatrixMBD.h](https://github.com/projectchrono/chrono/blob/main/src/chrono/core/ChMatrixMBD.h) 中定义。

##矩阵的基本操作##

请参考 Eigen API 获取所有矩阵和向量的 [算术操作](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html)、[块操作](https://eigen.tuxfamily.org/dox/group__TutorialBlockOperations.html) 和 [线性系统求解](https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html) 的详细信息。

[demo_CH_linalg.cpp](https://github.com/projectchrono/chrono/blob/main/src/demos/core/demo_CH_linalg.cpp) 演示了矩阵的基本操作。

# 函数对象  {#ChFunction_objects}

这些 ChFunction 对象在 Chrono 的许多地方使用，用于表示 y=f(x) 函数，例如在引入线性执行器的预设位移时。

这些函数是标量函数，

\f[
 x \in \mathbb{R} \rightarrow y \in \mathbb{R}
\f]

并且有预定义好的一系列函数可供直接使用，例如正弦、余弦、常数等。如果预定义的函数不够用，用户可以通过继承基类 ChFunction 来实现自定义函数。

请参阅 @ref chrono::ChFunction "ChFunction" 获取 API 详细信息和子类列表。

### 示例 1

~~~{.cpp}
	ChFunctionRamp f_ramp;

	f_ramp.SetAngularCoeff(0.1);	// 设置角系数
	f_ramp.SetStartVal(0.4);		// 设置 x=0 时的 y 值

	// 在给定的 x 值处评估 y=f(x) 函数，使用 GetVal() :
	double y	= f_ramp.GetVal(10);
	// 在给定的 x 值处评估导数 df(x)/dx，使用 GetDer() :
	double ydx	= f_ramp.GetDer(10);

	std::cout << "   ChFunctionRamp at x=0: y=" << y << "  dy/dx=" << ydx << std::endl;
~~~

### 示例 2

将正弦 ChFunction 的值保存到文件中。

~~~{.cpp}
	ChFunctionSine f_sine;

	f_sine.SetAmplitude(2);		// 设置振幅
	f_sine.SetFrequency(1.5);	// 设置频率

	std::ofstream file_f_sine ("f_sine_out.dat");

	// 在 100 个 x 点上评估 y=f(x) 函数及其导数，并保存到文件中（稍后可以在 Matlab 中加载）
	for (int i=0; i<100; i++)
	{
		double x = (double)i/50.0;
		double y = f_sine.GetVal(x);
		double ydx = f_sine.GetDer(x);
		double ydxdx = f_sine.GetDer2(x);
		file_f_sine << x << " " << y << " " << ydx << " " << ydxdx << std::endl;
	}
~~~

### 示例 3

定义一个自定义函数。

下面的类将作为示例，展示如何基于 ChFunction 接口创建自定义函数。

至少有一个必须实现的成员函数：
__GetVal__.

注意，基类实现了默认的导数计算方法 GetDer() 和 GetDer2()，使用数值微分。然而，如果你知道导数的解析表达式，也可以重写基类的 GetDer() 和 GetDer2()，以获得更高的精度。

~~~{.cpp}
// 首先，定义一个继承自 ChFunction 的自定义类

class ChFunctionMyTest : public ChFunction
{
public:
	ChFunction* new_Duplicate() {return new ChFunctionMyTest;} 
	double GetVal(double x) {return cos(x);} // 仅用于测试：简单的余弦函数
};

ChFunctionMyTest f_test;

std::ofstream file_f_test ("f_test_out.dat");

// 在 100 个 x 点上评估 y=f(x) 函数及其导数，并保存到文件中（稍后可以在 Matlab 中加载）
for (int i=0; i<100; i++)
{
	double x = (double)i/50.0;
	double y = f_test.GetVal(x);
	double ydx = f_test.GetDer(x);
	double ydxdx = f_test.GetDer2(x);
	file_f_test << x << " " << y << " " << ydx << " " << ydxdx << std::endl;
}
~~~

# Quadrature    {#quadrature}

Quadrature 是一种计算积分的操作，就像计算面积和体积一样。

下面的代码展示了如何使用 Gauss-Legendre 求积法来计算函数的积分  \f$ \mathbb{R} \mapsto \mathbb{R} \f$ 在一维区间上的积分，或者 \f$ f: \mathbb{R}^2 \mapsto \mathbb{R}\f$  在二维区间上的积分，或者 \f$ f: \mathbb{R}^3 \mapsto \mathbb{R}\f$  在三维区间上的积分:

\f[
	F_{1D}=\int^a_b f(x) dx
\f]

\f[
	F_{2D}=\int^{a_y}_{b_y}\int^{a_x}_{b_x} f(x,y) dx dy
\f]

\f[
	F_{3D}=\int^{a_z}_{b_z}\int^{a_y}_{b_y}\int^{a_x}_{b_x} f(x,y,z) dx dy dz
\f]

如果函数是 N 次多项式，且求积阶数也为 N，则结果是精确的；否则结果是近似的（增大 N 可以提高精度，但请注意，这种方法通常在 N 取值范围为 1 到 10 时已足够，否则可能需要考虑其他积分方法）。

对于 N 小于 10 的情况，求积使用预先计算的系数以获得最大性能。

~~~{.cpp}
	// 定义一个 y=f(x) 函数，通过继承 ChIntegrable1D:
	class MySine1d : public ChIntegrable1D<double>
	{
	public: 
		void Evaluate (double& result, const double x)  {
			result = sin(x);
		}
	};

	// 从函数类创建一个对象
	MySine1d mfx;

    // 在 0..PI 区间上调用 6 阶 Gauss-Legendre 求积:
	double qresult;	
	ChQuadrature::Integrate1D<double>(qresult, mfx,  0, CH_PI,  6);
	
	std::cout << "Quadrature 1d result:" << qresult << " (analytic solution: 2.0)" << std::endl;

	
	// 其他求积测试，这次是在 2D

	class MySine2d : public ChIntegrable2D<double>
	{
	public: 
		void Evaluate (double& result, const double x, const double y) { result = sin(x); }
	};

	MySine2d mfx2d;
	ChQuadrature::Integrate2D<double>(qresult, mfx2d, 0, CH_PI, -1,1, 6);
	std::cout << "Quadrature 2d result:" << qresult << " (analytic solution: 4.0)" << std::endl;
~~~

注意，由于模板的使用，也可以对 m 维（向量、张量）函数进行积分 \f$ \mathbf{f}: \mathbb{R}^n \mapsto \mathbb{R}^m \f$ ，例如：

\f[
  \mathbf{F}=\int^{a_y}_{b_y}\int^{a_x}_{b_x} \mathbf{f}(x,y) dx dy \quad \mathbf{F} \in \mathbb{R}^2
\f]

~~~{.cpp}
	class MySine2dM : public ChIntegrable2D< ChMatrixNM<double,2,1> >
	{
	public: 
		void Evaluate (ChMatrixNM<double,2,1>& result, const double x, const double y) 
		{ 
			result(0) = x*y;
			result(1) = 0.5*y*y;
		}
	};

	MySine2dM mfx2dM;
	ChMatrixNM<double,2,1> resultM;
	ChQuadrature::Integrate2D< ChMatrixNM<double,2,1> >(resultM, mfx2dM, 0, 1, 0,3, 6);
	std::cout << "Quadrature 2d matrix result:" << resultM << " (analytic solution: 2.25, 4.5)" << std::endl;
~~~

<br><br><br>
