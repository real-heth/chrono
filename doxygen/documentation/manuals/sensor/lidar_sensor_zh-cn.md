激光雷达传感器模型 {#lidar_sensor}
=================================

\tableofcontents

在 chrono::sensor::ChLidarSensor 中，合成数据是通过基于 GPU 的光线追踪生成的。通过利用硬件加速支持和 NVIDIA Optix 库提供的无头渲染功能。对于每个激光雷达光束，会追踪一组光线来采样该光束。样本数量以及光束发散角由用户设置。激光雷达的整个帧/扫描在单个渲染步骤中处理。为了考虑扫描中光线的时间差，使用关键帧和运动模糊技术。通过这些关键帧，扫描中的每个光束在特定时间追踪场景，重现物体和激光雷达的运动。激光雷达光束返回的强度基于漫反射模型。

#### 创建激光雷达

~~~cpp
auto lidar = chrono_types::make_shared<ChLidarSensor>(
	               parent_body,             // 激光雷达附加的刚体
                   update_rate,             // 扫描频率（Hz）
                   offset_pose,             // 偏移位姿
                   horizontal_samples,      // 水平采样点数
                   vertical_channels,       // 垂直通道数
                   horizontal_fov,          // 水平视场
                   max_vert_angle,          // 垂直最大角度
                   min_vert_angle,          // 垂直最小角度
                   max_distance,            // 最大测距
                   beam_shape,              // 设置光束形状为矩形或椭圆
                   sample_radius,           // 配置每个光束使用的样本数量
                   vert_divergence_angle,   // 垂直光束发散角
                   hori_divergence_angle,   // 水平光束发散角
                   return_mode,             // 当使用多个样本时，激光雷达的返回模式
                   clip_near                // 近裁剪距离，以确保不看到外壳几何
                   );               
lidar->SetName("Lidar Sensor");
lidar->SetLag(lag);
lidar->SetCollectionWindow(collection_time); // 通常为旋转360度的时间
~~~

<br>

#### 激光雷达滤波图

~~~cpp
// 以原始格式访问激光雷达数据（距离和强度）
lidar->PushFilter(chrono_types::make_shared<ChFilterDIAccess>());

// 从原始数据生成点云
lidar->PushFilter(chrono_types::make_shared<ChFilterPCfromDepth>());

// 根据角度、角度、距离、强度添加噪声
lidar->PushFilter(chrono_types::make_shared<ChFilterLidarNoiseXYZI>(0.01f, 0.001f, 0.001f, 0.01f));

// 以点云格式访问激光雷达数据
lidar->PushFilter(chrono_types::make_shared<ChFilterXYZIAccess>());

// 可视化点云（<高度, 宽度, 缩放, 可视化窗口名称>）
lidar->PushFilter(chrono_types::make_shared<ChFilterVisualizePointCloud>(640, 480, 2, "Lidar Point Cloud"));

// 将传感器添加到管理器
manager->AddSensor(lidar);
~~~

<br>

#### 激光雷达数据访问

~~~cpp
UserXYZIBufferPtr xyzi_ptr;
while () {
    xyzi_ptr=lidar->GetMostRecentBuffer<UserXYZIBufferPtr>();
    if(xyzi_ptr->Buffer) {
        // 获取并打印点云中的第一个点
        PixelXYZI first_point= xyzi_ptr->Buffer[0];
        std::cout<<"First Point: [ "<<unsigned(first_point.x) <<", "<<
        unsigned(first_point.y) <<", “ <<unsigned(first_point.z) <<", "<<
        unsigned(first_point.intensity) <<" ]"<<std::endl;
    }
}
~~~
