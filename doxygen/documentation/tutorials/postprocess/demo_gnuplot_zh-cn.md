GNUplot 示例（demo_POST_gnuplot.cpp）  {#tutorial_demo_gnuplot}
==========================

本教程演示如何使用 [POSTPROCESS 模块](group__postprocess__module.html) 与 [GNUPLOT](http://www.gnuplot.info) 创建图表。

类 `@ref chrono::postprocess::ChGnuPlot` 可以帮助您直接从 C++ 程序生成 `.gpl` gnuplot 脚本。

当然您也可以手动生成 `.gpl` 脚本：从程序保存 `.dat` 数据文件，然后手动运行 gnuplot，但该类会为您自动生成脚本并简化图表创建流程，同时会自动调用 gnuplot。

使用前的两个先决条件：

- 在计算机上安装 [GNUPLOT](http://www.gnuplot.info)。我们支持从 v4.6 起的版本，可从其官网安装 32 或 64 位版本。

- `gnuplot` 命令需能从 shell 中访问。在 Linux/Unix 上默认通常可用；在 Windows 上需要将 `gnuplot.exe` 所在的 `bin/` 目录加入到 PATH 环境变量。验证方法：在命令行窗口中输入 `gnuplot`，应能启动 gnuplot。

下面给出若干使用 `ChGnuPlot` 类的示例。

# 示例 1

使用 `ChGnuPlot` 的最底层方式：使用 `SetCommand()` 或者 `<<` 运算符构建 `.gpl` 脚本。

该脚本会按指定的 `.gpl` 名称保存到磁盘。

~~~{.cpp}
ChGnuPlot mplot("__tmp_gnuplot_1.gpl");
mplot << "set contour";
mplot << "set title 'Demo of specifying discrete contour levels'";
mplot << "splot x*y";
~~~

当 `mplot` 对象在示例结束时超出作用域并被销毁时，脚本会保存到磁盘并自动启动 GNUplot。

您应能看到如下窗口：

![](http://projectchrono.org/assets/manual/Tutorial_gnuplot1.png)

<div class="ce-info">
疑难排查：如果未看到窗口，请检查：
<br>
… 在命令行（Windows 的 DOS cmd）中输入 `gnuplot` 能否启动 gnuplot；如果找不到程序，请安装 gnuplot。
<br>
… 确保在 shell 中能访问 gnuplot（在 Windows 中将其添加到 PATH）。
<br>
… 若 `.gpl` 脚本包含错误，可在 shell 中切换到 `demo_POST_gnuplot` 可执行文件的工作目录，运行 `gnuplot __tmp_gnuplot_1.gpl`（将 `__tmp_gnuplot_1.gpl` 替换为实际文件名），gpl 会提示脚本错误信息（若有）。
</div>


# 示例 2

学习如何使用 `Open...` 系列函数定义输出终端。gnuplot 可在窗口中显示图形，也可以保存为 EPS、JPG、PNG 等格式。

本示例在两个窗口中打开两个图，并将第二个图保存为 EPS 文件。

注意我们使用 `SetGrid()`、`SetLabelX()`、`SetLabelY()` 等函数，这些是便捷函数，免去了手动输入复杂的 gnuplot 命令。例如 `mplot.SetLabelX("x");` 等价于 `mplot << "set xlabel \"x\"";`。

~~~{.cpp}
ChGnuPlot mplot("__tmp_gnuplot_2.gpl");
mplot.SetGrid();
~~~

将第一个绘图重定向到窗口 0：

~~~{.cpp}
mplot.OutputWindow(0);
mplot.SetLabelX("x");
mplot.SetLabelY("y");
mplot << "plot [-30:20] besj0(x)*0.12e1 with impulses, (x**besj0(x))-2.5 with points";
~~~

将下一个绘图重定向到窗口 1：

~~~{.cpp}
mplot.OutputWindow(1);
mplot.SetLabelX("v");
mplot.SetLabelY("w");
mplot << "plot [-10:10] real(sin(x)**besj0(x))";
~~~

最后将绘图输出到 EPS（Postscript）文件，可用于 LaTeX 文档。此处使用 `Replot()` 重复窗口 1 的最后一条绘图命令来保存为 EPS：

~~~{.cpp}
mplot.OutputEPS("test_eps.eps");
mplot.Replot(); // repeat last plot
~~~

您应能在两个独立窗口中看到如下图形：

![](http://projectchrono.org/assets/manual/Tutorial_gnuplot2.png)

![](http://projectchrono.org/assets/manual/Tutorial_gnuplot3.png)


# 示例 3

学习如何使用 `Plot()` 便捷函数，直接从 `.dat` 文件（按列排列的 ASCII 数据）生成绘图。

当然也可以直接写 gnuplot 命令，例如：

~~~{.cpp}
	mplot << "plot \"test_gnuplot_data.dat\" 1:2 
~~~

但 `Plot()` 函数使此过程更简单。

步骤 1：创建一个包含三列示例数据的 `.dat` 文件：

~~~{.cpp}
std::ofstream mdatafile("test_gnuplot_data.dat");
for (double x = 0; x<10; x+=0.1)
	 mdatafile << x << ", " << sin(x) << ", "  << cos(x) << std::endl;
~~~

步骤 2：创建绘图。

`Plot()` 便捷函数接受 `.dat` 文件名、列索引、标题及自定义设置（定义线型、线宽等），详见 gnuplot 文档。

~~~{.cpp}
ChGnuPlot mplot("__tmp_gnuplot_3.gpl");
mplot.SetGrid();
mplot.SetLabelX("x");
mplot.SetLabelY("y");
mplot.Plot("test_gnuplot_data.dat", 1,2, "sine",   " with lines lt -1 lw 2");
~~~

可以对同一输出多次调用 `Plot()`，它们会叠加（等价于 gnuplot 中的 `plot ..., ..., ...`）。例如：

~~~{.cpp}
mplot.Plot("test_gnuplot_data.dat", 1,3, "cosine", " with lines lt 2 lw 2");
~~~

您应能看到如下绘图：

![](http://projectchrono.org/assets/manual/Tutorial_gnuplot4.png)


# 示例 4

为了更方便，`Plot()` 也可直接用于内嵌数据，而无需先保存 `.dat` 文件。可以使用：

- 一对 x,y 向量（使用 `@ref chrono::ChVectorDynamic` 列向量）
- `@ref chrono::ChFunction` 表示的 y(x)
- `@ref chrono::ChFunctionInterp`
- `@ref chrono::ChMatrixDynamic` 的列等

数据值将以内嵌方式保存到 `.gpl` 文件中。

注意：`Replot()` 不适用于内嵌数据。

下面创建一些示例数据：

~~~{.cpp}
// create demo data in a pair of x,y vectors
ChVectorDynamic<> mx(100);
ChVectorDynamic<> my(100);
for (int i=0; i<100; ++i)
{
		double x = ((double)i/100.0)*12;
		double y = sin(x)*exp(-x*0.2);
		mx(i)=x;
		my(i)=y;
}
// ..or create demo data in a ChFunctionInterp
ChFunctionInterp mfun;
for (int i=0; i<100; ++i)
{
		double x = ((double)i/100.0)*12;
		double y = cos(x)*exp(-x*0.4);
		mfun.AddPoint(x,y);
}
// ..or create demo data in two columns of a ChMatrix
ChMatrixDynamic<> matr(100,10);
for (int i=0; i<100; ++i)
{
		double x = ((double)i/100.0)*12;
		double y = cos(x)*exp(-x*0.4);
		matr(i,2)=x;
		matr(i,6)=y*0.4;
}
~~~

现在创建绘图：

~~~{.cpp}
ChGnuPlot mplot("__tmp_gnuplot_4.gpl");
mplot.SetGrid();
mplot.Plot(mx,my, "from x,y ChVectorDynamic",  " every 5 pt 1 ps 0.5");
mplot.Plot(mfun,  "from ChFunctionInterp",  " with lines lt -1 lc rgb'#00AAEE' ");
mplot.Plot(matr,   2,6, "from ChMatrix", " with lines lt 5");
~~~

您应能看到如下绘图：

![](http://projectchrono.org/assets/manual/Tutorial_gnuplot5.png)

\include demo_POST_gnuplot.cpp
