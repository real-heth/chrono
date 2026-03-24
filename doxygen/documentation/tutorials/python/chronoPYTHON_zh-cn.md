Chrono PYTHON 模块教程   {#tutorial_table_of_content_chrono_python}
================================

使用 [PYTHON module](group__python__module.html) 的教程。

下面的示例展示如何使用 `Chrono::Python` 模块从 C++ 端解析 Python 程序（即**从 C++ 侧**）。要查看从 Python 侧使用 `Chrono::Python` 的示例，请参见 [PyChrono 教程](@ref tutorial_table_of_content_pychrono)。

<span style="color:red;font-weight:bold">注意！</span> 与您所安装的 Chrono 库版本兼容的这些示例源码，可在 Chrono 源码树的 `src/demos/pyparser` 下找到。

- demo_PY_parser.cpp

	如何从 C++ 端加载并执行 Python 命令或程序。

<br>

- demo_PY_import_solidworks.cpp

	加载您从 SolidWorks 导出的机构：

  - 将 SolidWorks 导出的机构载入 Chrono
  - 根据名称检索 SolidWorks 导出部件的指针
  - 使用 Irrlicht 展示实时仿真

<br>
