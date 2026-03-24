安装 PYTHON 模块 {#module_python_installation}
==========================

[TOC]

这是一个可选模块，为 Chrono 添加 Python 支持。

## 特性

**PYTHON 模块**允许用户使用 [Python](http://www.python.org) 来使用 Chrono 的建模、仿真和可视化功能。

该模块由 *两个* 构建目标组成：

- [PyChrono](@ref pychrono_introduction) 的 Python 模块。<br>
  如果在 CMake 配置期间启用了以下 Chrono 模块，将为其生成 Python 包装器：
    - *pychrono*，包装大多数 Chrono 类，相当于 chrono 命名空间
    - *pychrono.fea*，包装 FEA 类，相当于 chrono::fea 命名空间
    - *pychrono.fsi*，包装 FSI 类，相当于 chrono::fsi 命名空间（在 Mac Apple Silicon 上不可用）
    - *pychrono.vehicle*，包装 Chrono::Vehicle 类和地面车辆模型，相当于 chrono::vehicle 命名空间
    - *pychrono.robot*，包装 Chrono 机器人模型库中的各种模型
    - *pychrono.ros*，包装 Chrono::ROS 类
    - *pychrono.sensor*，包装 Chrono::Sensor 类（在 Mac Apple Silicon 上不可用）
    - *pychrono.postprocess*，包装 Chrono::Postprocess 模块
    - *pychrono.irrlicht*，包装 Chrono::Irrlicht 模块以进行运行时可视化
    - *pychrono.vsg3d*，包装 Chrono::VSG 模块以进行运行时可视化，相当于 chrono::vsg3d 命名空间（在 conda 版本中尚不可用）
    - *pychrono.pardisomkl*，包装 Chrono::PardisoMKL 模块（在 Mac Apple Silicon 上不可用）
    - *pychrono.cascade*，包装 Chrono::Cascade 模块
<br><br>
- 一个 *PYPARSER 模块*，这是一个 C++ 模块，用于从 C++ 程序解析/执行/解释 Python 指令。

<div class="ce-info">
**注意**：如果您只对使用 PyChrono 感兴趣，构建 Chrono Python 模块的替代方法是安装预编译的 [PyChrono conda 包](@ref pychrono_installation)。
</div>

## 依赖项

- 要**运行**基于此模块的应用程序：
    - 必须安装 [Python3](http://www.python.org)。在 Mac 上，请从 https://www.python.org 下载并安装实际的 Python 发行版。设置适当的环境变量。不要使用通过 homebrew 安装的 Python。
    - 要使用 *pychrono.cascade* 模块，还必须构建并安装 [pythonocc-core](https://github.com/tpaviot/pythonocc-core) 包。为了与 OpenCASCADE 7.9.2（构建 Chrono::Cascade 所需）保持一致，请确保使用 **pythonocc-core 版本 7.9.0**。

- 要**构建**此模块：
    - 必须安装 [Python3](http://www.python.org)。
    - 必须安装 [SWIG](http://www.swig.org/) 包装生成器。

<div class="ce-warning">
构建 PyChrono 需要 SWIG 版本 **4.0.0** 或更高。
<ul>
  <li>在 Windows 上，使用包含预构建可执行文件的 [SWIGWIN](https://sourceforge.net/projects/swig/files/swigwin) 发行版。已测试的 SWIG 版本为 4.0.2、4.1.0 和 4.2.1。</li>
  <li>在 Linux 上，许多发行版包含 SWIG 的软件包。请查阅您的包管理应用程序。</li>
  <li>在 MacOS 上，不要使用 homebrew 安装 SWIG。您将得到 SWIG 4.3.1，它会生成带有语法错误的源文件。请从源代码构建 SWIG 4.1.1 或 4.2.1。</li>
</ul>
</div>

## 构建说明

1. 在系统上安装 SWIG。需要版本 4.0.0 或更高。（在 Windows 上，只需解压到所需位置）。

2. 重复[完整安装](@ref tutorial_install_chrono)的说明，但当您看到 CMake 窗口时，必须添加以下步骤：

3. 将 `CH_ENABLE_MODULE_PYTHON` 设置为 'on'，然后按下 'Configure'（以刷新变量列表）

4. Python 包应由 CMake 自动检测。
如果提示，请将 `CH_PYTHONDIR` 变量设置为您安装的 Python 目录。
例如，它可能是 <tt>C:/Python33</tt>

5. 如果提示，请设置 CMake 变量 <tt>SWIG_EXECUTABLE</tt> 以指定 SWIG 可执行文件的位置。
   在 Linux 上，这应该会自动检测。在 Windows 上，根据 SWIG 的安装方式，您可能需要手动设置此变量。

6. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

如果在同一台机器上有多个 Python 安装，您可能需要在调用 CMake 时显式指定要使用的 Python。例如，在 Linux 上（Mac 类似于 Linux）：

<pre>
% ccmake -DPYTHON_EXECUTABLE:FILEPATH=/usr/local/python/3.6.0/bin/python3
  -DPYTHON_LIBRARY=/usr/local/python/3.6.0/lib/libpython3.so
  -DPYTHON_INCLUDE_DIR=/usr/local/python/3.6.0/include
  ../../chrono
On the Mac:
% ccmake -DPYTHON_EXECUTABLE:FILEPATH=$(which python3) ../../chrono
</pre>

成功编译后，[PyChrono](@ref pychrono_introduction) 模块可以从 *BUILD* 目录或安装后从 *INSTALL* 目录使用。为了使生成的 Python 模块可访问，必须设置/追加 <tt>PYTHONPATH</tt> 环境变量。在配置过程中，Chrono CMake 脚本将输出用于设置 PYTHONPATH 环境变量的正确路径；例如：

- Windows:<br>
<img src="http://www.projectchrono.org/assets/manual/ChronoPython_config.png" width="500">

- Linux:<br>
<img src="http://www.projectchrono.org/assets/manual/ChronoPython_config_linux.png" width="600">

设置/更改环境变量是特定于平台的。

- 在 Windows 上，您可以在 '控制面板 -> 系统 -> 高级系统设置' 中（全局）设置环境变量：<br>
  <img src="http://www.projectchrono.org/assets/manual/Windows_env.png" width="500"><br>

- 在 Linux 上，使用 bash shell：<br>
  <img src="http://www.projectchrono.org/assets/manual/Linux_env.png" width="600"><br>
  要永久设置 <tt>PYTHONPATH</tt>，可以将上述内容添加到您的 .bashrc 文件（或适用于您的 shell 的初始化文件）中。

## 使用

在运行时，所有系统都需要一些 Python 模块：<tt>numpy</tt> 和 <tt>six</tt>。运行此命令：<br>
<tt>pip3 list</tt><br>
您应该会看到类似如下的输出：<br>
<tt>Package    Version<br>
---------- -------<br>
numpy      1.22.3<br>
pip        22.0.4<br>
setuptools 58.1.0<br>
six        1.16.0</tt><br>
您可以使用以下命令安装缺失的模块：<br>
<tt>pip3 install numpy six</tt><br>

有关如何使用生成的模块的更多详细信息，请参阅以下内容：

- C++ 函数（作为 Python 解析器）
    - 请参阅本模块的 [API 部分](group__python__module.html) 以获取有关 C++ 函数的文档。
    - 查看 [demos](@ref tutorial_root) 的 C++ 源代码，以了解如何使用本模块的 C++ 函数。

- Python 函数 (作为 [PyChrono](@ref pychrono_introduction) )
    - 请参阅 PyChrono 的 [参考文档](@ref pychrono_reference)，了解如何从 Python 端使用 Chrono。
    - 查看 [demos](@ref tutorial_table_of_content_pychrono) 的 Python 源代码。

## 备注

Python 模块的构建过程，由 CMake 生成，包括以下自动步骤：

- SWIG 预处理 C++ 源代码文件，以生成一个 .cxx 包装文件，其中包含通过 API 访问 C++ 函数的代码，以及一些 .py 文件，

- C++ 编译器编译 .cxx 文件并生成一个或多个库文件，

- SWIG 生成的文件 (*.py) 和生成的库文件 (*.pyd 在 Windows 上，*.so 在 Linux/Mac 上) 被收集到 *BUILD* 目录中的一个位置，以便可以直接从那里使用。同样，在安装后，所有 Chrono::Python 模块都会被复制到 *INSTALL* 目录中的一个位置。有关这些确切位置的说明，请参阅上文关于您的特定配置的注释，以及关于设置 <tt>PYTHONPATH</tt> 环境变量的说明。

<div class="ce-info">
该模块已针对 Python 3（包括 Python 3.12 及更早版本）进行了测试。不再支持 Python 2.7。
</div>

<div class="ce-warning">
在某些 Python 发行版中，调试库 'python33_d.lib'（python33.lib 库的调试版本）默认情况下未包含。
如果您需要它，因为您在调试模式下重新编译 Python 模块，要么重新编译整个 Python 源码，要么修改 pyconfig.h 强制使用 python33.lib，按照以下步骤操作：

1. 注释掉以下行：

   ~~~{.py}
   //#define Py_DEBUG
   ~~~

2. 修改

   ~~~{.py}
   #if defined(_DEBUG)
   #pragma comment(lib,"python33_d.lib")
   ~~~

   为

   ~~~{.py}
   #if defined(_DEBUG)
   #pragma comment(lib,"python33.lib")
   ~~~

3. 在 CMake 中按下 'Advanced'，将 PYTHON_DEBUG_LIBRARY 设置为与 PYTHON_LIBRARY 相同的库，然后按下 'Generate'，以便您的项目将链接 'python33.lib' 而不是 'python33_d.lib'。
</div>
