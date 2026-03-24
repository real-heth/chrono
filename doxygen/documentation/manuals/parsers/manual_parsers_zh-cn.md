Chrono::Parsers {#manual_parsers}
=================================

该模块能够实现以下功能：

- 使用 YAML 指定 Chrono 模型和仿真
- 从第三方规范文件导入模型
  + URDF（需要外部库）
  + OpenSim
  + Adams
- 与 Python 语言交互（需要 Python 解释器）

请注意，有限元模型（网格）的导入可以使用主 Chrono 模块中的 @ref chrono::fea::ChMeshFileLoader "ChMeshFileLoader" 类完成（因此无需 PARSERS 模块）。该类支持导入 Abaqus、TetGen、GMF（LS-DYNA）或通用 OBJ 文件，但仅适用于非常特定的元素，并不是一个完整的有限元导入工具。

[Chrono::Parsers 安装指南](@ref module_parsers_installation)

## YAML 解析器

各种 YAML 解析器类允许解析 Chrono 模型和仿真的 YAML 规范文件。解析器从相应的 YAML 输入文件中缓存模型信息和仿真设置，然后允许填充 Chrono 或 Chrono::FSI 系统并设置求解器和仿真参数。

**多体模型和仿真的 YAML 规范**

* @subpage YAML_parser_overview
* @subpage YAML_schema_mbs_models
* @subpage YAML_schema_mbs_simulations

**车辆模型的 YAML 规范**

* @subpage YAML_schema_vehicle_models

**流体-结构相互作用问题的 YAML 规范**

* @subpage YAML_schema_fsi_problems
* @subpage YAML_schema_sph_models
* @subpage YAML_schema_sph_simulations


## Python 引擎（不是 PyChrono）
@ref chrono::parsers::ChPythonEngine "ChPythonEngine" 类允许直接从 C++ 运行 Python 代码并与之交互，同时可以在变量之间交换数据。它不应与 [PyChrono](@ref pychrono_introduction) 混淆，后者是一个完全独立的 Python 库，封装了 Chrono C++ 代码。

+ @ref chrono::parsers::ChPythonEngine "ChPythonEngine" 允许从 C++ 运行通用的 Python 代码
+ [PyChrono](@ref pychrono_introduction) 允许从 Python 使用 Chrono

通过此类，用户还可以通过方法 @ref chrono::parsers::ChPythonEngine::ImportSolidWorksSystem() "ChPythonEngine::ImportSolidWorksSystem()" 将从 SolidWorks 导出的模型导入到 Python 中。有关更多信息，请参阅 [Chrono::SolidWorks 参考手册](@ref manual_chrono_solidworks)。请注意，这 **不是导入 SolidWorks 模型的唯一方法**。

关于通用 Python 交互的示例：[demo_PARSER_Python.cpp](https://github.com/projectchrono/chrono/blob/main/src/demos/parsers/demo_PARSER_Python.cpp)

[安装指南](@ref module_parsers_installation)
