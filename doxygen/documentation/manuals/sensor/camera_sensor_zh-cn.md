摄像头传感器模型 {#camera_sensor}
=================================

\tableofcontents

在 Chrono:Sensor:ChCameraSensor 中，合成数据是通过基于 GPU 的光线追踪生成的。通过利用硬件加速支持和 NVIDIA Optix 库提供的无头渲染功能。

## 摄像头传感器设置

~~~cpp
chrono::ChFrame<double> offset_pose({10, 2, .5},                           // 位置
                                     QuatFromAngleAxis(CH_PI, {0, 0, 1}));  // 旋转

auto Camera = chrono_types::make_shared<ChCameraSensor>(
                    parent_body,                // 摄像头附加的刚体
                    update_rate,                // 更新频率（Hz）
                    offset_pose,                // 偏移位姿
                    image_width,                // 图像宽度
                    image_height,               // 图像高度
                    fov,                        // 摄像头的水平视场角
                    alias_factor,               // 抗锯齿的超采样因子
                    lens_model,                 // 可选的镜头畸变模型
                    use_global_illumination,    // 可选，启用全局光照
                    gamma,                      // 可选，设置伽马校正指数（默认为2.2）
                    use_fog                     // 可选，为摄像头启用雾效
                    );

Camera->SetName("摄像机传感器");
Camera->SetLag(lag);
Camera->SetCollectionWindow(exposure_time);

// 传感器数据访问滤波器
Camera->PushFilter(chrono_types::make_shared<ChFilterRGBA8Access>());

// 将传感器添加到管理器
manager->AddSensor(Camera);
~~~

有关更多详情，请参阅 [ChCameraSensor](@ref chrono::sensor::ChCameraSensor)。

摄像头设置过程将自动将 [Optix 渲染滤波器](@ref chrono::sensor::ChFilterOptixRender) 添加到滤波器列表中。

如果摄像头的 supersample_factor 大于 1，设置过程将调整分辨率并将 [图像别名滤波器](@ref chrono::sensor::ChFilterImgAlias) 添加到滤波器列表中。

## 渲染步骤

Chrono::sensor 中的摄像头传感器使用 Optix 作为渲染引擎。对于每个像素，引擎将沿该方向发射一条光线，并找到与光线相交的第一个对象。默认情况下，引擎使用基于物理的 BRDF 着色器渲染对象。它将以递归方式生成用于阴影、反射和折射的附加光线。

摄像头的更新频率远低于物理模拟。因此，[ChOptixEngine](@ref chrono::sensor::ChOptixEngine) 会生成一个线程来执行渲染，而不会阻塞主线程。

### 每次更新（主线程）

1. 检查是否有需要更新的摄像头。如果有这样的摄像头
    - 更新场景信息
    - 将其推入渲染队列
2. 检查是否有摄像头的数据准备好发送，或者等待它们完成。
3. 继续到下一个时间步

### 渲染线程

1. 等待渲染队列中有摄像头
2. 更新这些摄像头，清空渲染队列，返回步骤 1

## 滤波器图

可以将任意数量的滤波器附加到列表中并修改最终结果。滤波器按列表中的顺序执行。以下是一些示例。

* [摄像头噪声](@ref chrono::sensor::ChFilterCameraNoiseConstNormal)
* [图像别名滤波器](@ref chrono::sensor::ChFilterImgAlias)
* [灰度转换](@ref chrono::sensor::ChFilterGrayscale)
* [保存结果](@ref chrono::sensor::ChFilterSave)
* [可视化结果](@ref chrono::sensor::ChFilterVisualize)

## 摄像头动画

在仿真过程中，可以使用 `SetOffsetPose` 轻松更改摄像头的位置和旋转

~~~cpp
Camera->SetOffsetPose(chrono::ChFrame<double>({8, 2, .5},    // 位置
                      QuatFromAngleAxis(CH_PI, {0, 0, 1})));  // 旋转
~~~

## 数据访问

数据将在延迟时间后准备好。要访问

~~~cpp
RGBA_ptr = Camera->GetMostRecentBuffer<UserRGBA8BufferPtr>();
if (RGBA_ptr->Buffer) {
    unsigned int height = RGBA_ptr->Height;
    unsigned int width = RGBA_ptr->Width;
    PixelRGBA8 pixel_at_100_100 = RGBA_ptr->Buffer[100 * width + 100];
    uint8_t red_channel_at_100_100 = unsigned(pixel_at_100_100.R);
}
~~~
