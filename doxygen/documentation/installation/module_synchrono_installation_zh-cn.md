安装 SYNCHRONO 模块   {#module_synchrono_installation}
===============================

Chrono::Synchrono 是一个可选模块，允许在不同计算实体之间并行化 Chrono::Vehicle 仿真。

## 功能

**SynChrono 模块**允许用户在 MPI 或 DDS 实体之间并行化 Chrono::Vehicle 的动力学计算。

## 要求的依赖项

- 要构建基于此模块的应用程序，需要以下条件：
  * MPI
    - Linux: 测试过 [OpenMPI](https://www.open-mpi.org/) 和 [MPICH](https://www.mpich.org/)。
    - Windows: 测试过 [Intel MPI](https://software.intel.com/en-us/mpi-library/choose-download/windows) 和 [MS-MPI](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi)。您必须确保 MPI dll（`impi.dll` 或 `msmpi.dll`）在系统路径中。
  * [FlatBuffers](http://google.github.io/flatbuffers/) 
    - 一个版本包含在 chrono_thirdparty 作为子模块，对于一般开发，可以使用该版本或外部构建的版本。
- 以下是可选的：
  * [FastDDS](https://fast-dds.docs.eprosima.com/en/latest/)
    - 请使用 [最新的二进制文件](https://www.eprosima.com/component/ars/releases/eprosima-fast-dds?Itemid=0) 进行安装。
    - 如果包管理器提供的版本相对较新，也可能可以正常工作。

## 构建说明

1. 使用 `git submodule init` 和 `git submodule update` 初始化 `chrono_thirdparty` 中的 FlatBuffers 子模块。
    - 要运行带有 SynChrono 的程序，只需从初始化子模块中获取 FlatBuffers 头文件。
    - 如果对 FlatBuffers 消息模式进行了修改，则需要使用外部版本的 FlatBuffers 二进制文件（例如从包管理器获取）或[构建子模块版本](https://google.github.io/flatbuffers/flatbuffers_guide_building.html)（包含在 `chrono_thirdparty` 中）。

2. 重复[完整安装](@ref tutorial_install_chrono)的说明。Chrono::Vehicle 是必需的，至少需要 Chrono::Irrlicht 或 Chrono::Sensor 中的一个用于可视化。当您看到 CMake 窗口时，必须进行以下额外更改：

3. 将 `CH_ENABLE_MODULE_SYNCHRONO` 设置为 'on'，然后按 'Configure'（刷新变量列表）。

4. （可选）如果使用 Fast_DDS，将 `CH_USE_FAST_DDS` 设置为 'on'，然后按 'Configure'。
    - 如果使用已安装的二进制文件，CMake 应该会自动识别它们。
    - 如果从源代码构建或安装在非标准位置，则必须手动指定 `FastDDS_ROOT`。

5. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

## 使用

- 请参阅 [SynChrono API](@ref synchrono)。
- 阅读 [概述](@ref module_synchrono_overview)。
