惯性测量单元传感器模型 {#IMU_sensor}
=================================

\tableofcontents

Chrono::Sensor 支持三种通常作为 IMU 集合使用的传感器。这些传感器是加速度计、陀螺仪和磁力计。

#### 加速度计创建

~~~cpp
// 创建噪声模型
auto
noise_model=chrono_types::make_shared<ChNoiseNormalDrift>(
    100.f,                  // 更新频率
    {0,0,0},                // 均值
    {0.001,0.001,0.001},    // 标准差
    .01f,                   // 偏置漂移
    .1f                     // 漂移时间常数
);

auto acc= chrono_types::make_shared<ChAccelerometerSensor>(
    parent_body,        // IMU 附加的刚体
    imu_update_rate,    // 更新频率
    imu_offset_pose,    // 相对于刚体的偏移位姿
    noise_model         // 噪声模型
);

acc->SetName("加速度计");

acc->SetLag(.001); //1 毫秒的延迟
acc->SetCollectionWindow(.001);  //1 毫秒的采集时间

// 加速度计数据访问滤波器
acc->PushFilter(chrono_types::make_shared<ChFilterAccelAccess>());

// 将传感器添加到管理器
manager->AddSensor(acc);
~~~

#### 陀螺仪创建

~~~cpp
// 创建噪声模型
auto
noise_model=chrono_types::make_shared<ChNoiseNormalDrift>(
    100.f,                  // 更新频率
    {0,0,0},                // 均值
    {0.001,0.001,0.001},    // 标准差
    .01f,                   // 偏置漂移
    .1f                     // 漂移时间常数
);

auto gyro= chrono_types::make_shared<ChGyroscopeSensor>(
    my_body,            // IMU 附加的刚体
    imu_update_rate,    // 更新频率
    imu_offset_pose,    // 相对于刚体的偏移位姿
    noise_model         // 噪声模型
);

gyro->SetName("陀螺仪");

gyro->SetLag(.001);                 // 1 毫秒的延迟
gyro->SetCollectionWindow(.001);    // 1 毫秒的采集时间

// 陀螺仪数据访问滤波器
gyro->PushFilter(chrono_types::make_shared<ChFilterGyroAccess>());

// 将传感器添加到管理器
manager->AddSensor(gyro);
~~~

#### 磁力计创建

~~~cpp
// 创建噪声模型
auto
noise_model=chrono_types::make_shared<ChNoiseNormal>(
    {0,0,0},                // 均值
    {0.001,0.001,0.001},    // 标准差
);

auto mag= chrono_types::make_shared<ChMagnetometerSensor>(
    my_body,            // IMU 附加的刚体
    100.f,              // 更新频率
    imu_offset_pose,    // 相对于刚体的偏移位姿
    noise_model         // 噪声模型
);

mag->SetName("磁力计");

mag->SetLag(.001);                  // 1 毫秒的延迟
mag->SetCollectionWindow(.001);     // 1 毫秒的采集时间

// 磁力计数据访问滤波器
mag->PushFilter(chrono_types::make_shared<ChFilterMagnetAccess>());

// 将传感器添加到管理器
manager->AddSensor(mag);
~~~

<br>

#### IMU 数据访问

~~~cpp
utils::CSV_writer imu_csv(" ");
UserAccelBufferPtr bufferAcc;
UserGyroBufferPtr bufferGyro;
UserMagnetBufferPtr bufferMag;
int imu_last_launch = 0;
while () {
  bufferAcc = acc->GetMostRecentBuffer<UserAccelBufferPtr>();
  bufferGyro = gyro->GetMostRecentBuffer<UserGyroBufferPtr>();
  bufferMag = mag->GetMostRecentBuffer<UserMagnetBufferPtr>();
  if (bufferAcc->Buffer && bufferGyro->Buffer && bufferMag->Buffer &&
      bufferMag->LaunchedCount > imu_last_launch) {
      // 将 IMU 数据保存到文件
      AccelData acc_data = bufferAcc->Buffer[0];
      GyroData gyro_data = bufferGyro->Buffer[0];
      MagnetData mag_data = bufferMag->Buffer[0];
      imu_csv << std::fixed << std::setprecision(6);
      imu_csv << acc_data.X;
      imu_csv << acc_data.Y;
      imu_csv << acc_data.Z;
      imu_csv << gyro_data.Roll;
      imu_csv << gyro_data.Pitch;
      imu_csv << gyro_data.Yaw;
      imu_csv << mag_data.H;
      imu_csv << mag_data.X;
      imu_csv << mag_data.Y;
      imu_csv << mag_data.Z;
      imu_csv << std::endl;
      imu_last_launch = bufferMag->LaunchedCount;
  }
}
imu_csv.write_to_file(imu_file);
~~~
