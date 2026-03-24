Chrono SENSOR 模块教程 {#tutorial_table_of_content_chrono_sensor}
===============================

Chrono 发行版中包含多个演示，用于通过[SENSOR 模块](@ref sensor)对机器人和自动驾驶车辆的传感器进行建模与仿真。

Chrono::Sensor 提供对以下传感器的支持：
 - RGB 单目相机
 - 激光雷达
 - 雷达
 - GPS
 - 惯性测量单元IMU（加速度计、陀螺仪、磁力计）
 - 转速计 (Tachometer)  

这些是常用于机器人和自动驾驶车辆系统的传感器的参数化模型。

除了主库之外，SENSOR 模块还创建了一个预定义的 [SENSOR 模型](@ref sensor_overview) 库，目前包含：

- 通用相机
- 激光雷达
  - 通用激光雷达
  - Velodyne VLP-16 (Puck)
  - Velodyne HDL-32E
- 通用 GPS
- 通用 IMU

选择传感器演示：

* 基本传感器演示
  * demo_SEN_Camera - 带有自定义滤波器的相机传感器示例
  * demo_SEN_Lidar - 带有自定义滤波器的激光雷达传感器示例
  * demo_SEN_GPSIMU - 在摆上使用 GPS 和 IMU 的示例
  * demo_SEN_tachometer - 使用转速计测量物体旋转速度的示例
  * demo_SEN_JSON - 通过 JSON 接口使用传感器的示例

* 车辆与传感器 (需要 Chrono::Vehicle 和 Chrono::Irrlicht)
  * demo_SEN_Gator - 配备传感器的示例车辆
  * demo_SEN_HMMWV - 配备传感器的 HMMWV 示例
  * demo_SEN_deformableSoil - 在可变形地形上进行传感器示例

* 配备 TensorRT 的传感器 (需要在 cmake 中启用 CH_USE_TENSOR_RT=ON)
  * demo_SEN_NNCamera - 使用基于神经网络的滤波器通过 TensorRT 进行推理的相机示例
  * demo_SRN_rl_infer - 使用传感器和神经网络进行强化学习驾驶的示例
