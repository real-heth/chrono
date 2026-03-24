为 WASM 构建 Chrono {#tutorial_install_chrono_emscripten}
==========================

以下说明详细介绍了如何在 Linux 主机上使用 [Emscripten](https://emscripten.org/) 构建 Chrono 的 WebAssembly 版本。

这些说明也可能适用于 Windows 或 macOS 主机，只需进行最小的修改即可。

请参阅 [安装 Chrono](@ref tutorial_install_chrono) 获取本地构建说明。 

#### 1) 安装 Emscripten

使用 [文档中描述的方法](https://emscripten.org/docs/getting_started/downloads.html) 下载并安装 Emscripten。

#### 2) 下载并安装 Eigen 库

Chrono 使用 [Eigen3](http://eigen.tuxfamily.org/) 进行所有内部密集线性代数操作。Chrono 需要 Eigen 版本 3.3.0 或更高版本，但我们强烈建议使用 **最新稳定版本系列，Eigen 3.4.0（或更高版本）**。Eigen 是一个头文件库，因此通过系统包管理器安装的版本或从上游源下载的版本都可以与 emscripten 一起使用。

#### 3) 下载并安装 GLM（可选）

如果您打算使用 Chrono 内置的 WebGL 可视化功能，则在构建过程中需要 [OpenGL Mathematics](https://github.com/g-truc/glm) 库。由于它是一个头文件库，因此可以通过系统包管理器获取，或者从 [GitHub](https://github.com/g-truc/glm/releases) 下载源代码并按原样使用。

#### 4) 下载并安装 CMake

[CMake](https://cmake.org/) 是编译 Chrono 之前配置构建过程所必需的工具。它在 Linux 社区中也被广泛用于构建许多其他软件单元。如果尚未安装，请使用您系统的包管理器进行安装。在大多数系统上，该软件包的名称就简单地叫做 `cmake`。

<div class="ce-warning">
基于 Debian 的发行版可能需要安装 `cmake-curses-gui` 软件包，连同 `cmake` 一起安装，以便使用下文中提到的基于终端的图形用户界面。

> 注意: CMake 的 Qt GUI（在某些系统上为 `cmake-gui`）与 emscripten 配合使用效果不佳。请使用命令行或 curses 终端 GUI。
</div>

#### 5) 下载并安装 Ninja

推荐使用 [Ninja](https://ninja-build.org/) 以促进更快、更便携的构建过程。它通常可以通过系统的包管理器作为 `ninja-build` 或仅作为 `ninja` 获取。

#### 6) 下载 Project Chrono 源代码并使用 Git 

通过在您的计算机上执行 **clone** Git 仓库来下载 Chrono SDK。`git clone -b master git@github.com:projectchrono/chrono.git` 将在当前目录中创建一个 Github 仓库的副本。

<div class="ce-info">
强烈建议检出 [最新的发布标签](https://github.com/projectchrono/chrono/tags)。发布版本表示 Chrono 的最稳定和经过充分测试的版本。要检出 9.0.0 版本，请使用：`git switch --detach 9.0.0`。

如果您有兴趣在下一个官方发布之前使用最新开发的功能，可以使用 `git switch develop` 切换到 `develop` 分支。
</div>

#### 6) 使用 Emscripten Wrapper 运行 CMake

在 Chrono SDK 源代码目录中创建一个新的 _空_ 目录。这将用于构建 Chrono：`mkdir build`。接下来，将当前目录更改为该目录：`cd build`。

> 我们建议使用基于终端的 CMake GUI 来配置 Chrono 构建，但以下过程也可以通过命令行复制。

-  从构建目录运行 `emcmake ccmake -G Ninja ..`。包装器 `emcmake` 将为 CMake 设置 emscripten 工具链，然后在终端中出现基于文本的 GUI。

-  输入 `c` 以 **Configure** 并继续。界面将重新加载到一个包含更多选项的新屏幕。
  
-  指定 Eigen 安装的位置。
   如果未自动检测到，您可能需要手动设置 CMake 变量 `EIGEN3_INCLUDE_DIR`。<br>

<img src="http://www.projectchrono.org/assets/Images/install_ccmake_1.png" class="img-responsive" width="400">

<div class="ce-warning">
如果 Eigen 库是通过包管理器安装的，其位置可能会自动检测到。如果是这样，请在继续之前验证库的路径是否正确。
</div>

  - 以下说明是可选的，但强烈 **推荐**，因为它们在浏览器中运行时提供对 WebGL 可视化的支持。

    - 输入 `c` 以 **Configure** 并继续到下一个屏幕。

    - 启用推荐的可选模块。<br>
     其他模块可能需要额外的设置和依赖项。

    - 输入 `c` 以 **Configure** 并继续到下一个屏幕。

	- Emscripten 包含 GLEW 和 GLFW 的嵌入式头文件，这两个是 Chrono 的依赖项，位于其 sysroot 文件夹中。如果您使用 emsdk 安装了 emscripten 环境，则在您的主目录下应该有一个文件夹 `~/.emscripten_cache/sysroot`，其中包含所需的头文件。

<div class="ce-warning">
类似于之前设置的 Eigen 目录字段，GLM 包含目录可能会自动检测到。如果它被自动检测到，请在继续之前验证库的位置是否正确。
</div>
 
- 输入 `c` 以 **Configure** 并继续，直到到达最后一个屏幕。此屏幕将显示 `g` 选项以 **Generate**。按 `g` 并允许配置完成；ccmake 完成后将关闭。

<img src="http://www.projectchrono.org/assets/Images/install_ccmake_3.png" class="img-responsive" width="400">

#### 7) 编译项目

在与新创建的 Makefile 相同的构建目录中运行命令 `ninja`。请准备等待 15 - 25 分钟以完成构建。在拥有大量 CPU 核心的系统上，可以使用 `ninja -j N` 同时运行多达 _N_ 个构建步骤以加快过程。这是 Chrono 构建过程的最后一步。恭喜！

<div class="ce-info">
`ninja install` 通常会将 Chrono 库、数据文件和演示可执行文件复制到 CMake 配置期间指定的安装目录中，但在针对 WebAssembly 时，这并不实用，因为生成的文件通常会嵌入到网页中。
</div>
</div>

#### 8) 测试演示

导航到之前用于构建 Chrono 的目录。将当前目录更改为子目录 `bin`。演示示例文件存储在此处，它们是展示 Project Chrono 功能的绝佳资源。

对于每个演示，将生成两个文件，一个以 `.wasm` 结尾的二进制文件和一个以 `.js` 结尾的 JavaScript 包装器。

- 对于命令行演示，可以使用诸如 [Node.js](https://nodejs.org/en/) 之类的 JavaScript 引擎在终端中直接执行演示。 

- 对于更复杂的演示，包括那些使用可视化的演示，必须将 JavaScript 文件加载到网页中。这个过程稍微复杂一些，但在 [Emscripten 的文档](https://emscripten.org/docs/compiling/Deploying-Pages.html) 中有详细说明。
