GPS 传感器模型 {#GPS_sensor}
=================================

\tableofcontents

Chrono 中的 GPS 使用球面坐标系和 GPS 参考位置来计算纬度、经度和高度，该参考位置指定了仿真中的原点。GPS 假设 Chrono 系统为 Z 向上，X 向东，Y 向北。

#### GPS 创建

~~~cpp
// 创建噪声模型
auto gps_noise_model=chrono_types::make_shared<ChNoiseNormal>(
    ChVector<float>(1.f, 1.f, 1.f),  // 均值
    ChVector<float>(2.f, 3.f, 1.f)   // 标准差
);
auto gps = chrono_types::make_shared<ChGPSSensor>(
                parent_body,      // GPS 附加的刚体
                gps_update_rate,  // 更新频率
                gps_offset_pose,  // 相对于刚体的偏移位姿
                gps_reference,    // GPS 参考位置（仿真原点的 GPS 坐标）
                gps_noise_model   // 用于添加 GPS 噪声的噪声模型
);

gps->SetName("GPS");
gps->SetLag(gps_lag);
gps->SetCollectionWindow(gps_collection_time);

// GPS 数据访问滤波器
gps->PushFilter(chrono_types::make_shared<ChFilterGPSAccess>());

// 将传感器添加到管理器
manager->AddSensor(gps);
~~~

<br>

#### GPS 数据访问

~~~cpp
utils::CSV_writergps_csv(" ");
UserGPSBufferPtr bufferGPS;
while () {
    bufferGPS=gps->GetMostRecentBuffer<UserGPSBufferPtr>();
    if(bufferGPS->Buffer) {
        // 将 GPS 数据保存到文件
        GPSDatagps_data= bufferGPS->Buffer[0];
        gps_csv<<std::fixed <<std::setprecision(6);
        gps_csv<<gps_data.Latitude;   // 纬度
        gps_csv<<gps_data.Longitude;  // 经度
        gps_csv<<gps_data.Altitude;   // 高度
        gps_csv<<gps_data.Time;       // 时间
        gps_csv<<std::endl;
    }
}

gps_csv.write_to_file(gps_file);
~~~
