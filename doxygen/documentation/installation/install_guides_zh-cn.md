安装指南 {#install_guides}
==========================

### 安装 Chrono (C++)

-   [核心 Chrono 模块](@ref tutorial_install_chrono)

其他 Chrono 功能通过可选模块提供，这些模块在 CMake 配置期间启用。

-   [CASCADE 模块](@ref module_cascade_installation)

-   [CSHARP 模块](@ref module_csharp_installation)

-   [FMI 模块](@ref module_fmi_installation)

-   [FSI 模块](@ref module_fsi_installation)

-   [DEM 模块](@ref module_dem_installation)

-   [IRRLICHT 模块](@ref module_irrlicht_installation)

-   [MATLAB 模块](@ref module_matlab_installation)

-   [MODAL 模块](@ref module_modal_installation)

-   [MULTICORE 模块](@ref module_multicore_installation)

-   [MUMPS 模块](@ref module_mumps_installation)

-   [Pardiso MKL 模块](@ref module_mkl_installation)

-   [PARSERS 模块](@ref module_parsers_installation)

-   [POSTPROCESS 模块](@ref module_postprocess_installation)

-   [PYTHON 模块](@ref module_python_installation)

-   [ROS 模块](@ref module_ros_installation)

-   [SENSOR 模块](@ref module_sensor_installation)	

-   [SYNCHRONO 模块](@ref module_synchrono_installation)

-   [VEHICLE 模块](@ref module_vehicle_installation)

-   [VSG 模块](@ref module_vsg_installation)

#### 提供第三方依赖

核心 Chrono 模块（因此所有 Chrono 模块）需要 Eigen3 线性代数（仅头文件）库。

Chrono 可选模块通常依赖于可能需要额外安装步骤的第三方库，如每个模块安装页面所述。

对于其中一些依赖项，我们提供了实用程序脚本，这些脚本将下载、配置、构建和安装已知与当前 Chrono 发行版兼容的版本。在每种情况下，我们都提供了批处理脚本（适用于 Windows 用户）和 bash 脚本（适用于 Linux/Mac 用户）。目前，以下依赖项的实用程序脚本可用（在 Chrono 源代码树的 `contrib/build-scripts` 子目录下，按操作系统组织）：

- Eigen3，核心 Chrono 模块所需
- Blaze，Chrono::Multicore 模块所需
- Spectra，Chrono::Modal 模块所需
- VSG 库，Chrono::VSG 模块所需
- URDF 库，Chrono::Parsers 模块中的 URDF 解析器所需
- GL 实用库，Chrono::Sensor 模块可选所需
- MUMPS 库，Chrono::Mumps 模块可选直接稀疏线性求解器所需
- OpenCRG 库，Chrono::Vehicle 模块可选 OpenCRG 支持所需

`contrib/build-scripts` 子目录中还包括用于使用 CMake 配置 Chrono 的示例脚本（`buildChrono.bat`、`buildChrono.sh` 和 `buildChronoMac.sh`），可用作满足各种可选 Chrono 模块依赖项的示例（假设这些依赖项已使用上述实用程序脚本安装）。

有关更多详细信息，请参阅 Chrono 核心模块安装指南中的相关[部分](@ref scripts)。

### 构建使用 Chrono 的项目

- [配置并构建外部 Chrono 项目](@ref tutorial_install_project)

### 为 WebAssembly 构建 Chrono

-   [为 WASM 构建 Chrono](@ref tutorial_install_chrono_emscripten)


### 安装 PyChrono

- @subpage pychrono_installation


### Chrono::Solidworks 插件

用于使用 Chrono 库模拟 Solidworks 模型的插件

- @subpage chrono_solidworks_installation

### 使用 Chrono 构建 Docker 镜像

- @subpage docker_installation
