Chrono::Sensor 概览 {#sensor_overview}
=================================

\tableofcontents

Chrono::Sensor 模块提供了在 Chrono 仿真中模拟 RGB 相机、激光雷达、雷达、GPS 以及加速度计、陀螺仪和磁力计的支持。传感器是附加到 Chrono 刚体（ChBody）上的对象。Chrono::Sensor 目前与 Chrono 的核心刚体仿真兼容，包括 Chrono::Vehicle。

## Chrono::Sensor 详细概览

 ##### 传感器系统的设置方式（更多示例可以在传感器演示中找到）

~~~cpp
import ..

// Chrono
ChSystemNSC mphysicalSystem

// ...

// 设置和初始化传感器及传感器系统（管理器和环境）
auto manager = chrono_types::make_shared<ChSensor>();

// 设置和自定义场景
manager->scene->AddPointLight({x,y,z}, {intensity, intensity, intensity}, distance);
manager->scene->SetAmbientLight({0.1, 0.1, 0.1});

// 设置天空渐变
Background b;
b.mode = BackgroundMode::GRADIENT;
b.color_horizon = {.6, .7, .8};
b.color_zenith = {.4, .5, .6};
manager->scene->SetBackground(b);

// 添加一些传感器
// 请参阅传感器特定页面以将传感器添加到管理器

// 仿真循环
while(){

  // 更新传感器管理器
  manager->Update();

  // 执行动力学步骤
  mphysicalSystem.DoStepDynamics(step_size);
}
~~~

<br>

##### Chrono::Sensor 设计考虑

由于动态 Chrono 仿真通常具有比传感器更高的更新频率（动力学：约 1kHz；传感器：10-100Hz），传感器框架使用单独的线程来管理数据整理。

  - <img src="http://www.projectchrono.org/assets/manual/sensor/processing.png" width="600" />

<br>

Chrono::Sensor 可以利用多个渲染线程，每个线程管理一个独立的 GPU，用于模拟一组传感器。这在具有多个代理和众多传感器的场景中尤为有用，这些传感器以不同的更新频率运行。

  - <img src = "http://www.projectchrono.org/assets/manual/sensor/multigpu.png" width ="600"/>

<br>

每个传感器都有一个滤波器图，用户可以扩展该图以自定义计算管道，用于模拟特定传感器属性或配置特定数据格式。
   - <img src="http://www.projectchrono.org/assets/manual/sensor/filter_graph_general.png" width="300" />

<br>

##### 从 JSON 文件加载传感器模型

~~~cpp
auto cam = Sensor::CreateFromJSON(
  GetChronoDataFile("sensor/json/generic/Camera.json"),   // JSON 文件路径
  my_body,                                                // 传感器附加的刚体
  ChFramed(ChVector3d(-5, 0, 0), QUNIT));                 // 传感器的附加位姿

  // 将相机添加到管理器
  manager->AddSensor(cam);
~~~

## 参考坐标系和相对附加位置

每个 Chrono 传感器默认使用 Z 向上，X 向前，Y 向左的坐标系，以匹配车辆 ISO 参考坐标系。对于 RGB 相机，这意味着 z 轴在图像平面中垂直，y 轴在图像平面中向左，x 轴指向图像平面内部。对于激光雷达，x 轴沿零垂直角和零水平角的光线方向。
