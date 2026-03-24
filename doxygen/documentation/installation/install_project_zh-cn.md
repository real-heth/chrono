构建使用 Chrono 的项目 {#tutorial_install_project}
==========================

外部 C++ 项目使用 Chrono 需要：
- 在编译时访问 Chrono 头文件
- 在链接时访问 Chrono 库
- 在运行时访问共享库，Windows 上为 `.dll`，Linux 上为 `.so`  

<img src="http://www.projectchrono.org/assets/manual/Pic_build.png" class="img-responsive">

<br>
此过程通过在 Chrono 配置期间生成的 Chrono CMake 配置脚本自动化，并可在 Chrono 构建树（此处命名为 \<__chrono_build__\>）或 Chrono 安装（此处命名为 \<__chrono_install__\>）中使用。<br>
`chrono-config.cmake` 脚本（\<chrono_build\>/cmake/chrono-config.cmake 或 \<chrono_install\>/cmake/chrono-config.cmake）允许查找 Chrono 组件以及有关给定 Chrono 构建或 Chrono 安装的所有必要信息，以便链接和使用 Chrono 库。

`chrono-config.cmake` 在项目的 CMakeLists.txt 配置脚本中通过调用 `find_package` 使用：
\code{.c}
find_package(Chrono
             [COMPONENTS required_components...]
             [OPTIONAL_COMPONENTS optional_components>
             CONFIG)
\endcode
以查找提供 `required_components` 模块的 Chrono 构建或安装，并可选择性地查找 `optional_components` 模块。请注意，如果不需要可选组件，则可以省略 `OPTIONAL_COMPONENTS`。

在调用 `find_package()` 时，可以请求以下 Chrono 组件（不区分大小写）： 
Cascade, CSharp, DEM, FMI, FSI, FSI_SPH, FSI_TDPF, Irrlicht, VSG, Matlab, Modal, Multicore, PardisoMKL, Parsers, Postprocess, Sensor, Synchrono, Vehicle, VehicleCosim.<br>
__注意__:

- 核心 Chrono 模块会自动作为必需组件包含。
- 只有在目标 Chrono 包构建时启用了相应模块时，特定组件才可用。

`chrono-config.cmake` 会递归处理所有请求的组件，以便启用作为请求模块（或其依赖项）依赖项构建的任何其他 Chrono 模块。

此外，`chrono-config.cmake` 默认使用与配置和构建 Chrono 包时相同的配置和构建设置（例如，C++ 编译器、CUDA SDK、MPI），以及任何第三方依赖项的相同设置（例如，VSG 运行时可视化库）。但是，调用者可以选择重定向其中的任何设置。

在从 `find_package` 返回时，将设置以下变量：

- Chrono_FOUND
       如果找到 Chrono 及所有必需组件，则设置为 true
- CHRONO_TARGETS
       导出的 Chrono 目标列表
- CHRONO_STATIC
       如果构建了 Chrono 静态库，则设置为 ON，如果构建了共享库，则设置为 OFF
- CHRONO_MSVC_RUNTIME_LIBRARY
       构建 Chrono 时使用的 MSVC 运行时库
- CHRONO_DLL_NAMES
       （Windows）Chrono DLL 列表（不含路径）
- CHRONO_CSHARP_SOURCES
       所有与请求的组件对应的 SWIG 生成的 C# 脚本列表
       （目前，仅包装了核心、后处理、Irrlicht 和 Vehicle Chrono）
- CHRONO_DATA_DIR
       Chrono 数据目录的路径
- CHRONO_VEHICLE_DATA_DIR
       Chrono::Vehicle 数据目录的路径
- SYNCHRONO_DATA_DIR
       Chrono::Synchrono 数据目录的路径

此外，对于每个请求的组件 'COMPONENT'，会设置一个变量 `CHRONO_<COMPONENT_UPPER>_FOUND` 为 `TRUE` 或 `FALSE`（其中 'COMPONENT_UPPER' 是组件名称的大写形式）。这些变量仅对在调用 `find_package` 时请求为“可选”的 Chrono 模块有意义，因为缺少必需组件会自动将 `Chrono_FOUND` 设置为 `FALSE`。
<br>

---------------------------------------------------------------------
## 配置和构建外部项目

Chrono 分发包包含用于不同类型的基于 Chrono 的外部项目的模板项目。这些模板项目位于 Chrono 源代码树（或 Chrono 安装树）的顶层目录中：
- [template_project](https://github.com/projectchrono/chrono/tree/main/template_project) - 一个简单的 C++ 项目，构建一个使用 Irrlicht 可视化的简单摆机制
- [template_project_csharp](https://github.com/projectchrono/chrono/tree/main/template_project_csharp) - 一个简单的 C# 项目，构建一个使用 Irrlicht 可视化的弹跳球
- [template_project_fmi](https://github.com/projectchrono/chrono/tree/main/template_project_fmi2) - 一个简单的 C++ 项目，构建一个 FMU（请参阅 [特殊说明](@ref module_fmi_installation) 以了解如何构建支持 FMU 生成的 Chrono）
- [template_project_ros](https://github.com/projectchrono/chrono/tree/main/template_project_ros) - 一个简单的 C++ 项目，演示如何从外部项目使用 Chrono::ROS
- [template_project_vehicle_cosim](https://github.com/projectchrono/chrono/tree/main/template_project_vehicle_cosim) - 一个简单的 MPI 项目，构建一个在刚性地形上单轮的 Chrono::Vehicle 协同仿真

#### 1. 检查先决条件

至少需要以下软件包：

- 必须提供 C++ 编译器和 [CMake](http://www.cmake.org)。
- 必须提供可用的 Chrono 构建或安装（请参阅 [Chrono 安装说明](@ref tutorial_install_chrono)）。

__注意__：使用其他 Chrono 模块可能需要 CUDA SDK、MPI 编译器或第三方库，如 Irrlicht、VSG、OptiX、OpenGL、Thrust、Blaze 等。

#### 2. 创建项目目录

- 从 Chrono 源代码（或安装）中复制所需的“模板”项目目录到其他位置，并根据需要重命名。在下文中，我们以 **template_project** 为例，\<__my_project__\> 为外部项目源代码的名称。
- 目录 \<my_project\> 将包含新项目的所有源代码。

#### 3. 编辑 CMakeLists.txt 脚本

- 使用模板项目目录中的示例 **CMakeLists.txt** 作为起点。
  在为自己的项目自定义之前，建议先尝试构建预定义的示例，以确保所有必要的 Chrono 模块和依赖项都已到位。

- CMakeLists.txt 中的以下元素应进行自定义：
  - 在调用 `project()` 时指定项目的名称。

  - 在调用 `find_package(Chrono...)` 时请求项目所需的必需（`COMPONENTS`）和可选（`OPTIONAL_COMPONENTS`）Chrono 模块。在我们的例子中：
    \code{.c}
    find_package(Chrono
                 COMPONENTS Irrlicht
                 OPTIONAL_COMPONENTS Postprocess
                 CONFIG)
    \endcode
    请求 Chrono::Irrlicht 模块，如果可用，还请求 Chrono::Postprocess 模块。<br>

  - 在调用 `add_executable` 时设置源文件列表和目标名称：  
    \code{.c}
    set(MY_FILES my_example.cpp)
    add_executable(my_demo ${MY_FILES})
    \endcode

#### 4. 使用 CMake 配置项目

- 启动 `cmake-gui`

- 使用 **Browse source...** 设置源目录的位置（在我们的例子中为 \<my_project\>）
	
- 使用 **Browse build...** 设置生成二进制文件的位置。虽然不是必需的，但最好使用与源目录不同的构建目录。在这里，我们假设二进制文件将生成在 \<__my_project_build__\>。

- 点击 **Configure** 按钮

- 设置 `Chrono_DIR` 变量。该变量指向包含 `chrono-config.cmake` 脚本的目录路径，因此可以是 \<chrono_build\>/cmake 或 \<chrono_install\>/cmake。

- 点击 **Configure** 按钮再次配置项目

- 配置成功后，`chrono-config.cmake` 会提供所请求的 Chrono 组件（必需或可选）的列表以及 Chrono 配置的详细信息。

- 点击 **Generate** 按钮生成构建文件（根据选择的生成器，构建文件将创建在项目构建目录 \<my_project_build\> 中）。

#### 5. 编译项目

如果在 CMake 中使用了 Visual Studio 生成器
- **打开** CMake 生成的 Visual Studio 解决方案文件（在我们的例子中为 \<my_project_build\>/my_project.sln）
- 选择所需的构建模式（例如 **Release**，使用 Visual Studio 工具栏中的下拉列表）
- **构建** 项目（使用 Visual Studio 菜单 "Build>Build solution..." 或快捷键 Ctrl-Shft-B）

在 Linux 上，假设使用 Makefile 生成器，在构建目录中调用 make 命令：

\code{.c}
$ cd \<my_project_build\>
$ make
\endcode

__注意__：项目应使用与 Chrono 相同的构建配置进行编译（例如，Release 或 Debug）。使用多配置生成器时，Chrono 构建树中可以同时存在不同的构建。

#### 6. 运行你的程序

在 \<my_project_build\> 中运行可执行文件 `my_demo`（如果使用多配置生成器，如 Visual Studio，则在特定配置的子目录中）以启动简单摆示例的仿真。
<img src="http://projectchrono.org/assets/manual/Install_my_project_2.jpg" class="img-responsive">
<br>
---------------------------------------------------------------------

### Windows 用户的重要信息

默认情况下，所有 Chrono 模块都构建为共享库（Windows 上为 **DLL**）。此外，大多数第三方依赖项也以共享库的形式提供。操作系统必须能够在运行时找到所有必要的 DLL。

为了简化操作，`chrono-config.cmake` 提供了一个函数，将必要的 Chrono DLL 从它们的位置（在 Chrono 构建树中或在 Chrono 安装中）复制到项目的构建目录（在我们的例子中为 \<my_project_build\>）。
这是通过在 Visual Studio 解决方案中引入一个新的构建目标（`COPY_DLLS`）来完成的，该目标在 **POST_BUILD** 时执行。

为了启用此便利目标，项目的 CMakeLists.txt 脚本应在末尾调用 `add_CHRONO_DLLS_copy_command()`。请注意，此函数在 Windows 以外的平台上无效。

### 使用 Chrono::CSharp 的重要信息

一些 Chrono 模块已通过 SWIG 封装，可用于 C# 程序。这些可以是独立的 C# 程序（请参阅 Chrono 分发中的 [C# 示例](https://github.com/projectchrono/chrono/tree/main/src/demos/csharp)）或用于配套的 [ChronoUnity](https://github.com/projectchrono/chrono-unity) 包。

在配置 C# 项目时，除了启用 CSharp 语言外，您可能还希望启用 C++：

```cpp
   project(my_csharp_project CSharp CXX)
```

这是为了允许某些需要 C++ 的 Chrono 功能：

- Chrono::Multicore 需要 C++ 的 OpenMP
- Chrono::Vehicle 联合仿真需要 C++ 的 MPI
- Chrono::VSG 调用 FindThreads

如果未启用 C++，`chono-config.cmake` 将禁用这些功能以及依赖它们的任何 Chrono 模块。

### 使用 Chrono::Sensor 的重要信息

如果从外部项目链接到 Chrono::Sensor 模块，请确保设置安装位置的目录，其中包含着色器代码（编译的 ptx 代码或 shaders cu 文件）。这应在任何将从安装位置使用 Chrono::Sensor 的外部代码的顶部设置。

```cpp
  //function to set the shader location (include ChOptixUtils.h)
  chrono::sensor::SetSensorShaderDir("path/to/sensor/shaders");

  //if USE_CUDA_NVRTC is enabled, use
  chrono::sensor::SetSensorShaderDir("path/to/install/include/chrono_sensor/optix/shaders/");

  //if USE_CUDA_NVRTC is disabled, use
  chrono::sensor::SetSensorShaderDir("path/to/install/lib/sensor_ptx/");
```
