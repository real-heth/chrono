安装 SENSOR 模块   {#module_sensor_installation}
===============================

[TOC]

Chrono::Sensor 是一个可选模块，允许对传感器进行建模和仿真，以便在 Chrono 中模拟机器人和自主代理。

## 功能

**SENSOR 模块**允许用户为机器人和自主代理建模和仿真传感器。

有关更多详细信息，请参阅参考手册中的 [Chrono::Sensor](@ref manual_sensor) 部分。

## 要求的依赖项

- 要 **运行** 基于此模块的应用程序，需要以下条件：
  * NVIDIA GPU，Maxwell 或更高版本 - 能够运行 OptiX
  * NVIDIA 图形驱动程序 530.41 或更高版本

- 要 **构建** 基于此模块的应用程序，需要以下条件：
  * [CUDA](https://developer.nvidia.com/cuda-downloads)
  * [OptiX](https://developer.nvidia.com/designworks/optix/download) - 仅支持版本 7.7（不支持 6.X 或其他 7.X 版本）
  * [GLFW](https://www.glfw.org/) - 版本 3.0 或更高
  * [GLEW](http://glew.sourceforge.net/) - 版本 1.0 或更高
  * OpenGL
  * [TensoRT](https://developer.nvidia.com/tensorrt) (可选) - 版本 7.0.0

## 构建说明

1. 重复[完整安装](@ref tutorial_install_chrono)的说明，但当您看到 CMake 窗口时，必须添加以下步骤：

2. 将 `CH_ENABLE_MODULE_SENSOR` 设置为 'on'，然后按 'Configure'（刷新变量列表）

3. 将 `OptiX_INSTALL_DIR` 和 `OptiX_ROOT_DIR` 变量设置为系统上安装的 OptiX 目录的根目录（包含 `include/` 的目录），然后按 'Configure' 刷新变量列表。如果刷新未正确设置以下变量：`OptiX_Include`，请手动设置它（例如 `OptiX_INSTALL_DIR/include`）。

4. 将所有 `GLEW_...`、`GLFW_...` 的值设置为适当的目录或文件值，如果 cmake 未自动找到。

5. 可选地，将 `CH_USE_CUDA_NVRTC` 设置为 'on' 以启用 Optix RT 内核的运行时编译。按 'Configure' 刷新变量列表。如果设置为 'off'，RT 内核将在运行时编译。根据系统的不同，您可能需要将 `CMAKE_CUDA_ARCHITECTURES` 设置为特定的目标架构，因为这将导致 RT 内核被编译为 PTX。

6. 可选地，将 `CH_USE_TENSOR_RT` 设置为 'on' 以启用使用 TensorRT 增强传感器数据。按 'Configure' 刷新变量列表。
    * 将 `TENSOR_RT_INSTALL_DIR` 变量设置为系统上安装的 TensorRT 目录的根目录（包含 `lib/`、`bin/`、`include/` 的目录），然后按 'Configure' 刷新变量列表。
    * 如果刷新未正确设置以下变量：`TENSOR_RT_INCLUDE_PATH`、`TENSOR_RT_NVINFER`、`TENSOR_RT_ONNXPARSER` 和 `TENSOR_RT_PARSER`，请手动设置它们，最后三个变量直接指向相应的库文件。

7. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

8. **注意** 如果从外部项目链接到 Chrono::Sensor 安装，请确保设置安装位置的目录，其中包含着色器代码（编译的 ptx 代码或 shaders/*.cu 文件）。这应在任何将使用 chrono::sensor 的外部代码的顶部设置。
  
  ```cpp
    // 设置着色器位置的函数（包含 ChOptixUtils.h）
    chrono::sensor::SetSensorShaderDir("path/to/sensor/shaders");

    // 如果启用了 USE_CUDA_NVRTC，使用
    chrono::sensor::SetSensorShaderDir("path/to/install/include/chrono_sensor/optix/shaders/");

    // 如果禁用了 USE_CUDA_NVRTC，使用
    chrono::sensor::SetSensorShaderDir("path/to/install/lib/sensor_ptx/");
  ```

## 使用

- 请参阅 [参考手册](@ref manual_sensor)。

- 查看本模块的 [API 部分](@ref sensor) 以获取有关类和函数的文档。

- 查看 [演示](@ref tutorial_table_of_content_chrono_sensor) 的 C++ 和 Python 源代码，以了解如何使用此模块的功能。

## MacOS 支持

此模块不支持 Mac。
