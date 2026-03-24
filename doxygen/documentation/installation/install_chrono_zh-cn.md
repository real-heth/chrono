安装 Chrono {#tutorial_install_chrono}
==========================

\tableofcontents

Chrono 源代码可以从 Chrono GitHub [仓库](https://github.com/projectchrono/chrono) 获取，作为 zip 文件（用于当前开发分支或官方 [发布版本](https://github.com/projectchrono/chrono/releases) 之一）。或者，您也可以使用 [git](https://git-scm.com/) 克隆 Chrono 仓库。

------------------------------------------------------------
## 前提条件 {#prerequisites}

从源代码构建 Chrono 需要 C++ 编译器和 [CMake](https://cmake.org/) 构建系统。

#### 推荐的编译器 {#compilers}

- Windows: **MSVC** Visual Studio 2022 或更高版本。
  ([VS 2022 Community Edition](https://visualstudio.microsoft.com/downloads/) 免费下载)<br>
  注意: 默认情况下未安装 C++ 编译器；请确保在安装 VS 时安装 C++ 工具链。
- Linux: **GNU** C++ 编译器（适用于基于 Linux 的平台，版本 11 或更高）
- Linux: **LLVM Clang** C 和 C++ 编译器（版本 14 或更高）
- MacOS: **Clang** 通过 Xcode 包安装。
  ([Xcode](https://apps.apple.com/us/app/xcode/id497799835?mt=12/) 免费下载)

其他编译器也经过测试（例如 Intel C++、PGI），但它们并未得到官方支持和维护。尽管使用其他工具链构建 Chrono 可能是可行的，但这可能需要对 CMake 脚本进行修改。

#### 安装 CMake {#install_cmake}

[CMake](https://cmake.org/) 是在编译 Chrono 之前配置构建工具链所必需的工具。

CMake 将配置并创建必要的解决方案文件（Windows）或 make 文件（Linux），以便从源代码编译和构建 Chrono。

对于 Windows 用户：确保将 CMake 可执行文件放入您的 `Path` 环境变量中（安装程序可以为您完成此操作）。

在 Linux 上，如果尚未安装，请使用包管理器安装 `cmake`。某些发行版可能需要与 `cmake` 一起安装其他软件包（例如，用于基于窗口的 CMake GUI 界面的 `cmake-gui` 或用于使用 `ccmake` 终端 GUI 的 `cmake-curses-gui`）。

对于 Xcode 用户：虽然 CMake.app 包也包含命令行工具，但必须设置适当的链接以便从终端使用它。最好通过 homebrew 安装纯命令行版本：在终端中运行 <tt>brew install cmake</tt>。

#### 安装 GUI git 客户端 {#install_git}

虽然可以通过命令行使用 `git`，但我们建议使用 [GUI git 客户端](https://git-scm.com/downloads/guis)。

在 Windows 和 MacOS 上，我们建议使用 [SourceTree](http://www.sourcetreeapp.com/)，下面的示例也使用了它。

请注意，大多数现代 IDE 都集成了 git（例如，免费提供的 [Visual Studio Code](https://code.visualstudio.com/) 可在 Windows、Linux 和 Mac 上使用）。

------------------------------------------------------------
## 可选支持 {#optional}

在 CMake 配置期间，Chrono 还会检查编译器功能（例如 SIMD 级别支持、OpenMP 可用性）和环境（例如 MPI 和 CUDA 可用性）的额外支持。如果未找到这些支持，构建 Chrono 和某些模块的特定优化将被禁用（例如，如果 C++ 编译器不支持 OpenMP，则 FEA、Bullet 碰撞和 Eigen 不支持多线程），某些功能将被禁用（例如，如果没有 OpenMP 或 Thrust，则不支持多核碰撞检测算法），或者整个模块将被禁用（例如，没有 CUDA 就无法构建 Chrono::FSI、Chrono::GPU 和 Chrono::Sensor，没有 OpenMP 和 Thrust 就无法构建 Chrono::Multicore，没有 MPI 就无法构建 Chrono::Synchrono 和 Chrono::Vehicle 协同仿真模块）。

如果启用特定的 Chrono 模块，还会检查额外的支持。例如，启用 Chrono::MUMPS 模块需要 Fortran 编译器。

#### CUDA 支持 {#cuda}

Chrono 可以配置并构建支持 CUDA 版本高于 12.3 的版本。使用 CUDA，因此使用基于 CUDA 的 Chrono 模块（Chrono::FSI、Chrono::GPU 和 Chrono::Sensor）需要 NVIDIA GPU。请参阅 [NVIDIA 网站](https://developer.nvidia.com/cuda-downloads) 获取有关在您的计算机和操作系统上安装 CUDA 及必要的 NVIDIA 驱动程序的说明。

如果使用的 CMake 版本高于 3.23，Chrono 配置会将 CUDA 架构设置为 `all-major`（可以更改为 `native` 或任何其他特定架构）。对于较旧的 CMake 版本，用户有责任将 `CHRONO_CUDA_ARCHITECTURES` 正确设置为适合其 GPU 卡的值（请注意，计算能力为 "8.9" 必须输入为 `89`）。

对于具有多个并行 CUDA 安装的用户，可以通过在 CMake 中指定适当的工具链来选择所需的版本（例如，`-T cuda=C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8`）。在 Linux 上，也可以使用环境模块管理多个 CUDA 环境（例如，请参阅此 [GitHub Gist](https://gist.github.com/garg-aayush/156ec6ddda3d62e2c0ddad00b7e66956)）。

#### Thrust 支持 {#thrust}

Thrust 库在各种 Chrono 功能和模块中使用不同的后端。例如，多核碰撞检测库（替代默认的基于 Bullet 的碰撞检测）以及 Chrono::Multicore 模块需要使用 OpenMP 后端的 Thrust。Chrono::FSI 模块需要使用 CUDA 后端的 Thrust。

获取 Thrust（仅头文件）库的最简单方法是作为最近 CUDA 发行版的一部分。这允许使用最新的 Thrust 版本（CUDA 12.3 中为 2.2.0；CUDA 12.8 中为 2.7.0）。

也可以单独使用 Thrust（例如，在没有 NVIDIA GPU 的机器上启用 Chrono::Multicore 模块）。但是，这需要使用 Thrust 的较旧版本，从其 [GitHub 仓库](https://github.com/NVIDIA/thrust) 获取。请注意，那里可用的最新版本是 2.1.0。

#### MPI 支持 {#mpi}

安装 MPI 是 Chrono::Synchrono 和 Chrono::Vehicle 中可用的协同仿真框架（用于车辆-地形交互）所必需的。Chrono 已成功与 Intel MPI（也包含在 [Intel oneAPI HPC Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/hpc-toolkit.html) 中）、[Microsoft MPI](https://learn.microsoft.com/en-us/message-passing-interface/microsoft-mpi)、[OpenMPI](https://www.open-mpi.org/) 和 [MPICH](https://www.mpich.org/) 一起构建。

#### OpenMP 支持 {#openmp}

所有常见编译器的最新版本都支持 OpenMP，因此在 Chrono 配置期间很可能会自动检测到 OpenMP 支持。即便如此，用户仍然可以选择禁用 OpenMP（取消选择 `CH_ENABLE_OPENMP` CMake 选项）。

对于 Windows 用户的注意事项：MSVC 仅支持 OpenMP 2.0 标准（详细信息请参阅 [Microsoft 网站](https://learn.microsoft.com/en-us/cpp/build/reference/openmp-enable-openmp-2-0-support?view=msvc-170)）。这对于在 Chrono 中使用并不是问题，因为只使用了 OpenMP 2.0 中已经可用的功能。

------------------------------------------------------------
## 第三方依赖 {#dependencies}

Chrono 核心模块仅依赖于 [Eigen3](http://eigen.tuxfamily.org/) 模板库用于线性代数。

由于可选的 Chrono 模块可能会引入额外的依赖项，我们建议仅启用项目所需的模块，至少在第一次安装时如此；有关它们的安装，请参阅 [安装指南](@ref install_guides)。

#### 安装 Eigen {#install_eigen}

Eigen 是一个仅包含头文件的库，因此可以在下载后立即使用。然而，它也可以通过 `cmake` 配置和安装（见下文）。

在 Linux 上，Eigen 也可以通过系统包管理器安装（例如 <tt>sudo apt install eigen3-dev</tt>）。

在 Mac 上，Eigen 可以通过 homebrew 安装：<tt>brew install eigen</tt>。从 MacOS 12 Monterey 开始，homebrew 安装在 `/opt/homebrew`。

Chrono 支持最新的 Eigen3 版本 5.0.0，以及之前的 3.* 版本（例如 3.3.9 和 3.4.1）。
为了与其他第三方软件包的新版本（尤其是 Intel oneAPI）保持最佳兼容性，我们建议使用最新的 Eigen3 5.0.0。

#### 安装第三方 Chrono 依赖项的实用脚本 {#scripts}

Chrono 分发包在目录 `contrib/build-scripts` 中包含了一组脚本，这些脚本提供了一种简单的机制来安装各种 Chrono 模块的依赖项。脚本按操作系统组织在子目录中：Bash shell 脚本位于 `contrib/build-scripts/linux/`，Windows 批处理脚本位于 `contrib/build-scripts/windows/`。目录 `contrib/build-scripts/macOS/` 包含针对 MacOS 特性的 Bash shell 脚本；如果该目录中没有脚本，只需使用 Linux 脚本即可。

**注意事项**<br>
- 脚本假定已安装 git、cmake 和 C++ 编译器
- 其他要求（如果有）在每个脚本顶部的注释中指出
- 使用说明列在每个脚本顶部的注释中

目前，脚本提供了以下软件包的安装：
- Eigen3 -- Chrono 核心模块的唯一外部依赖
- Blaze -- Chrono::Multicore 所需的线性代数包
- GL 和 GLEW -- Chrono::Sensor 可选使用的 OpenGL 包
- MUMPS -- Chrono::Mumps 所需的直接稀疏线性求解器
- OpenCRG -- Chrono::Vehicle 可选使用的道路描述文件格式
- Spectra -- Chrono::Modal 所需的代数包
- URDF -- Chrono::Parsers 可选使用的 URDF 文件解析工具
- VDB -- Chrono::Sensor 可选使用的 OpenVDB 包
- VSG -- Chrono::VSG 所需的 VulkanSceneGraph 包

此外，每个子目录都包含一个示例脚本，用于配置和构建启用各种模块的 Chrono，并满足相应的依赖项。

**使用方法**<br>
请参阅每个脚本顶部注释中的说明。
一般使用方法如下：
- 将所需的脚本复制到工作目录中（每个脚本将创建临时目录以下载必要的源代码并配置和构建各种软件包）
- 编辑脚本以适应您的特定机器（至少设置所需的安装目录）
- 运行脚本
- 验证软件包文件是否已正确安装在指定的安装目录中

除了 OpenCRG，所有由这些脚本构建和安装的软件包都提供 CMake 配置脚本，这些脚本在 CMake 配置 Chrono 时用于查找相应的依赖项。为了简化 Chrono 的 CMake 配置过程，并避免每次手动指定软件包的特定信息，我们建议设置 `CMAKE_PREFIX_PATH` 环境变量，将每个已安装软件包的 CMake 项目配置脚本所在的目录添加到该变量中。
在 Windows 机器上的 `CMAKE_PREFIX_PATH` 示例是：

```cpp
E:\Packages\eigen\share\eigen3\cmake;
E:\Packages\blaze\share\blaze\cmake;
E:\Packages\vsg\lib\cmake;
E:\Packages\urdf\lib\urdfdom\cmake;
E:\Packages\urdf\CMake;
E:\Packages\spectra\share\spectra\cmake;
E:\Packages\gl\lib\cmake;
E:\Packages\mumps\cmake;
C:\occt-7.9.2\occt-vc14-64\cmake;
C:\Program Files (x86)\Intel\oneAPI\mkl\latest\lib\cmake\mkl;
```

#### 关于第三方 Chrono 依赖项的注意事项 {#notes}

- 切勿混合使用 64 位和 32 位的二进制文件和库。<br>
例如，您必须链接 64 位的 Irrlicht 库。
- 由于许多第三方依赖包会创建和安装共享库，因此可能需要执行以下步骤：
  - 在 Linux 上，运行 `ldconfig`（您可能需要 root 权限）以缓存对新创建的共享库的必要链接，或设置 `LD_LIBRARY_PATH` 环境变量
  - 在 Windows 上，将包含包 DLL 的目录添加到 `PATH` 环境变量中（否则，这些 DLL 必须手动复制到二进制文件旁边，以便在运行时找到）

------------------------------------------------------------
## 使用 CMake 配置 Chrono {#configure_chrono}

CMake 可以通过 GUI 界面 `cmake-gui`（注意在 Linux 上，这需要安装一个单独的 CMake 包）、Curses 界面 (`ccmake`) 或直接从命令提示符 (`cmake`) 使用。请注意，后者需要将所有必要的 CMake 变量作为参数传递给 `cmake`，或者编写一个脚本（示例脚本随 Chrono 分发包提供，位于 `contrib/build-scripts/` 目录下）。

下面，我们将更详细地描述如何使用 `cmake-gui` 和 `ccmake` 配置 Chrono。

#### 使用 GUI 界面配置 CMake {#configure_chrono_cmake_gui}

启动 `cmake-gui` 以配置构建。
-  在 "Where is the source code" 字段中设置 Chrono 目录的路径。<br>
   这是您创建 Git 仓库的目录，在我们的示例中是 <tt>C:/workspace/chrono</tt>。

-  在 "Where to build the binaries" 字段中设置一个 **不同于** Chrono 源代码位置的目录路径，因为 Chrono 禁止 "in-source" 构建。这个构建目录可以事先手动创建；否则，CMake 会提示创建它。在我们的示例中，使用 <tt>C:/workspace/chrono_build</tt>  
   <img src="http://www.projectchrono.org/assets/manual/Install_cmake_destinations.png" class="img-responsive">

-  点击 **Configure** 按钮。
  
-  设置适当的生成器（例如 Visual Studio、Makefile 等）和适当的平台（Win32、x64 等） 
   <img src="http://www.projectchrono.org/assets/manual/Install_cmake_platform.png" class="img-responsive">

-  指定 Eigen 安装的位置。
   如果 Eigen 本身是通过 CMake 配置和安装的，请将 CMake 变量 `Eigen3_DIR` 设置为指向包含项目配置脚本的 Eigen 安装目录（例如 `C:/Packages/eigen/share/eigen3/cmake/`）。否则，将 CMake 变量 `EIGEN3_INCLUDE_DIR` 设置为指向包含子目录 `Eigen` 的头文件目录（例如 `C:/Packages/eigen-3.4.0/`）。

-  启用任何其他模块。在继续之前，请参考它们的 [安装指南](@ref install_guides)。

-  请记住，在更改某些设置后，您可能需要多次按 **Configure**，直到所有变量依赖关系都得到解决。

-  最后，按 **Generate**。

<div class="ce-warning">
如果使用多配置生成器（例如 Visual Studio 或 ninja 多配置），CMake 会将变量 `CMAKE_CONFIGURATION_TYPES` 设置为包含所有可用配置（Debug、Release、MinSizeRel、RelWithDebInfo）。请保持不变。
<br><br>
如果使用单配置生成器（例如 makefiles 或 ninja），请将 `CMAKE_CONFIGURATION_TYPES` 设置为所需的构建类型（例如 Release 或 Debug）。不要将其留空（默认值），因为这将导致构建没有优化和调试信息。
<br><br>
CMake 使用斜杠 `/` 作为路径分隔符。Unix 用户已经习惯了这种约定。<br>
Windows 用户应注意将默认分隔符 `\` 转换为 `/`！
</div>

此时，您刚刚创建了一个项目，该项目将用于稍后构建 Chrono。您可以关闭 CMake。

#### 使用 Curses 界面配置 CMake {#configure_chrono_ccmake}

- 创建一个 **不同于** Chrono 源代码目录的构建目录（因为 Chrono 禁止 "in-source" 构建），并将当前目录更改为该目录。
  
- 在构建目录中运行 `ccmake <path-to-chrono-sources>`。终端中将出现基于 Curses 的 GUI。

<img src="http://www.projectchrono.org/assets/manual/install_ccmake_1.png" class="img-responsive" width="600">

- 按 `c` 进行 **Configure** 并继续。界面将重新加载到一个包含更多选项的新屏幕。
  
<img src="http://www.projectchrono.org/assets/manual/install_ccmake_2.png" class="img-responsive" width="600">

- 指定构建类型（除非使用多配置生成器，见上文）。

- 指定 Eigen 安装的位置（见上文）。

<img src="http://www.projectchrono.org/assets/manual/install_ccmake_3.png" class="img-responsive" width="600">

- 按 `c` 进行 **Configure** 并继续，直到到达最终屏幕。此时按 `g` 进行 **Generate**，CCMake 将在完成后关闭。

<img src="http://www.projectchrono.org/assets/manual/install_ccmake_4.png" class="img-responsive" width="600">

构建文件现在可在构建目录中使用（在此示例中为 `Makefile`）。

------------------------------------------------------------
## 构建 Chrono {#build_chrono}

#### Visual Studio {#build_chrono_windows}

1. 双击构建目录中的 `Chrono.sln` 文件以打开 Visual Studio 解决方案文件。或者，如果使用 `cmake-gui`，点击 _Open Project_ 按钮。

2. 在 VS 工具栏中，从 _Solution Configurations_ 下拉菜单中选择所需的构建模式（例如 **Release**）。  
  <img src="http://www.projectchrono.org/assets/manual/Install_vs_buildtype.png" class="img-responsive">

3. 在工具栏中，点击 **Build > Build solution** 或 **Build > Build ALL_BUILD**。
   这将构建所有 Chrono 项目（每个 Chrono 模块一个），以及演示和测试（如果在配置期间启用）。
   默认情况下，Chrono 模块生成共享库（DLL），除非在配置期间将 `BUILD_SHARED` 设置为 `off`。所有 DLL 和可执行文件将放置在构建树的 `bin\Release` 目录中。

4. 可选地，重复步骤 2 和 3，选择 **Debug** 作为配置类型，以构建包含调试符号的调试二进制文件。所有 DLL 和可执行文件将放置在构建树的 `bin\Debug` 目录中。

#### Linux/make {#build_chrono_linux}

根据 CMake 配置期间使用的生成器，调用相应的构建命令。例如：

- `make -j 10`<br>
  使用 Make 构建，使用 10 个并行构建线程。
- `ninja -j 10`<br>
  使用 ninja 构建，使用 10 个并行构建线程。
- `ninja -f build.Release.ninja -j 10`<br>
  使用 `ninja` 多配置构建进行 Release 构建，使用 10 个并行构建线程。

#### MacOS/clang {#build_chrono_mac}

- CMake 在 "Where to build the binaries" 指定的目录中生成一系列 Makefile。

- 要构建 Chrono 库和演示可执行文件，只需在该目录的命令行中调用 <tt>make</tt>。

- 可选地，输入 <tt>make install</tt> 将 Chrono 库、数据文件和演示可执行文件安装到 CMake 配置期间指定的目录中。

- CMake 可以配置为生成 Xcode (<tt>cmake -G Xcode ....</tt>) 配置。通常情况下，您会使用 Xcode IDE。其优点是可以调试代码。与 MS Visual Studio 类似，您可以从 IDE 中选择构建类型。

<div class="ce-warning"> 
**MacOS 问题:** clang++ 默认不支持 OpenMP。
您将无法成功构建 <tt>libChrono_multicore</tt>。<br> 
但是，可以使用 homebrew 添加 OpenMP 支持: <tt>brew install libomp</tt>。 
完成后，您可以配置 Chrono 以支持 OpenMP。为此，必须定义正确的编译器标志:
<tt>-Xpreprocessor -fopenmp</tt> 用于编译器，<tt>-lomp</tt> 用于链接器。请为 C 编译器和 C++ 编译器都提供 OpenMP 选项，否则 OpenMP 配置将失败。
</div> 

------------------------------------------------------------
## 测试 Chrono 构建 {#test_chrono}

Chrono 分发版包含大量演示、单元测试和基准测试。如果在 CMake 配置期间将相应的 CMake 变量设置为 `on`，这些内容将包含在构建中：`BUILD_DEMOS`、`BUILD_TESTING` 和 `BUILD_BENCHAMRKING`。默认情况下，仅启用生成演示可执行文件。

每个 Chrono 模块都添加了自己的演示和测试集，只有在启用相应的 Chrono 模块时才会构建这些内容。请注意，一些演示程序依赖于多个 Chrono 模块。例如，大多数 MBD 和 FEA 演示需要运行时可视化模块（VSG 或 Irrlicht）。类似地，Chrono::Vehicle 演示需要运行时可视化模块，而其他一些车辆演示还需要额外的模块（例如 Chrono::FSI、Chrono::Multicore 等）。

可执行文件位于子目录 `bin/<config>/` 下（例如，`bin/Release/` 或 `bin/Debug/`），对于多配置生成器，或者直接位于 `bin/` 下，否则。

单元测试不使用运行时可视化，并基于 googletest。运行任何 Chrono 单元测试将生成标准报告，指示测试是否成功或失败。您可以使用 `ctest` 一次运行所有单元测试。例如，要运行 Release 构建（多配置生成器）的所有单元测试，请从顶级构建目录执行以下命令：<br>
`ctest -C Release`

-----------------------------------------------------------
## 安装 Chrono {#install_chrono}

在成功构建后，可以安装 Chrono（到 CMake 配置期间通过 `CMAKE_INSTALL_PREFIX` 指定的目录）。这将把 Chrono 库、头文件、数据文件和演示可执行文件复制到安装目录。

在 Visual Studio 中，安装过程是通过构建 Chrono.sln 解决方案的 "INSTALL" 项目完成的。

如果使用 make 或 ninja，安装过程如下：

- `make install`
- `ninja install`
