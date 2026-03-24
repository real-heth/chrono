安装 Chrono Solidworks {#chrono_solidworks_installation}
==========================

Chrono::SolidWorks 是 [SolidWorks](http://www.solidworks.com) 的一个插件，允许通过利用 Chrono 库来模拟和导出 SolidWorks 模型。

请参阅 [Chrono::SolidWorks 用户手册](@ref manual_chrono_solidworks) 获取完整文档。

安装
------------

- 必须在计算机上安装一份 [SolidWorks](http://www.solidworks.com)。支持的版本为 2011 或更高，64 位。
- 下载 [Chrono::SolidWorks 安装程序](http://projectchrono.org/download/#chronosolidworks) 并安装；
- 这允许 *直接从 SolidWorks 界面模拟模型*；
- 导出到 Python、C++ 或 JSON 格式不是必需的，但 *始终可能*。
  在这种情况下，需要有 PyChrono 或 Chrono (C++) 来导入它们。  
  特别是，导出的模型可以：
  - Python 可以被加载：
    - Chrono (C++)，如果 [PARSERS 模块](@ref manual_parsers) 和至少 `CH_ENABLE_MODULE_PYTHON` 已启用，或者系统中可用 PyChrono；
    - PyChrono，如果系统中可用；
  - C++ 需要 Chrono (C++) 可用，此选项需要编译 C++ 代码；
  - JSON 需要 Chrono (C++)；目前从 JSON 导入在其他语言中不受支持；

使用方法
-------------

请参阅 [Chrono::SolidWorks 用户手册](@ref manual_chrono_solidworks) 获取完整文档。  
通过示例学习，请参阅 [Chrono::SolidWorks 教程](@ref tutorial_table_of_content_chrono_solidworks)。
