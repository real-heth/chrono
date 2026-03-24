安装 PyChrono {#pychrono_installation}
==========================

在您的计算机上安装 PyChrono 有两种选择。第一种使用预编译的 conda 包，这是推荐的方式。第二种适用于需要从 C++ 源代码构建完整库的用户。

## A) 安装预编译的 Python 模块

我们提供了可以在 Python 中一步安装的预编译 PyChrono 模块。PyChrono 模块既可用于最新发布的代码，也可用于 git *main* 分支中的最新代码。Conda 包可用于 Linux、Windows 和 MacOS，并支持不同版本的 Python3。

![Anaconda-Server Badge](https://anaconda.org/projectchrono/pychrono/badges/latest_release_date.svg)
![Anaconda-Server Badge](https://anaconda.org/projectchrono/pychrono/badges/platforms.svg)
![Anaconda-Server Badge](https://anaconda.org/projectchrono/pychrono/badges/license.svg)
![Anaconda-Server Badge](https://anaconda.org/projectchrono/pychrono/badges/downloads.svg)

要安装 PyChrono conda 模块，请执行以下操作：

1. 安装 [Anaconda](https://www.anaconda.com/download/) Python 发行版。 <br>

2. 我们强烈建议使用专用的 conda 环境，并在该环境下安装所需的 Python 发行版、必要的依赖项和 PyChrono 包。

   要创建一个带有 Python 3.12 的 `chrono` 环境，请使用：

   ```shell
   conda create -n chrono python=3.12
   ```

   然后激活该环境：

   ```shell
   conda activate chrono
   ```

   这样所有后续的 conda 命令都会在该环境中执行。

3. 决定您想要的 Chrono 代码版本（最新发布版或最新代码）以及对应的 Python 版本。请查阅 [PyChrono Anaconda 仓库](https://anaconda.org/projectchrono/pychrono/files) 上可用模块的列表。

   从 Chrono 发布版本构建的 PyChrono 包标记为 'release'；从最新的 Chrono 开发代码构建的 PyChrono 包标记为 'main'。

4. 安装 PyChrono conda 包。如果您想安装最新的开发分支，请运行

   ```shell
   conda install projectchrono::pychrono -c conda-forge
   ```

   否则，请使用您想要安装的特定版本代码，例如：

   ```shell
   conda install projectchrono::pychrono=9.0.1=py312hf1de3a3_6463 -c conda-forge
   ```

<div class="ce-warning">
vsg3d 模块和 ROS 模块尚未在 PyChrono 的 conda 版本中提供。要使用它们，您可能需要“从 C++ API 构建 Python 模块”
</div>

## B) 从 C++ API 构建 Python 模块

使用整个 Chrono C++ API 的高级用户可以从头构建 PyChrono。 
这是获得最新 PyChrono 的首选方式，但它更复杂。
操作如下：

1. 安装 [Chrono API](@ref tutorial_install_chrono) 的 C++ 源代码并构建它，
2. 安装 [Python](http://www.python.org)（仅支持 Python 3.2 或更高版本）。
   或者，如果您有足够的硬盘空间，最好安装完整的堆栈，如 [Anaconda](https://www.anaconda.com/download/)
3. 构建 PyChrono 模块，按照 [这些说明](@ref module_python_installation)

<div class="ce-warning">
从 C++ 源代码构建 PyChrono 时，必须编辑 PYTHONPATH 环境变量以包含 Chrono 构建树中 bin/ 目录的路径。
例如：

```shell
export PYTHONPATH=$HOME/chrono_build/bin
```

</div>

## 技巧

<div class="ce-info">
我们建议您使用专门的 IDE 编辑器，它可以很好地处理 Python 语言（语法高亮、智能感知等）。
大多数 Python 发行版默认安装的 IDE 是 IDLE，它仅适用于较简单的任务。我们最推荐的是 **Spyder**，它随 [Anaconda](https://www.anaconda.com/download/) Python 发行版一起提供。其他免费选项包括 [Visual Studio Code](https://code.visualstudio.com/) 或 [Visual Studio 的 Python 插件](https://marketplace.visualstudio.com/items?itemName=ms-python.python)。
</div>
