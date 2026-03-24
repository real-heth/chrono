转速传感器模型 {#tachometer_sensor}
=================================

\tableofcontents

在 Chrono::Sensor::ChTachometerSensor 中，合成数据是通过查询父体的角速度生成的。

### 创建转速传感器

~~~cpp
auto tachometer = chrono_types::make_shared<ChTachometerSensor>(
                        parent_body,        // 传感器所依附的刚体
                        update_rate,        // 测量频率（Hz）
                        offset_pose,        // 传感器的偏移位姿
                        axis,               // 测量的旋转轴
)

tachometer->SetName("转速传感器");
tachometer->SetLag(lag);
tachometer->SetCollectionWindow(collection_time); 
~~~

<br>

### 转速传感器滤波器图

~~~cpp
// 以原始格式访问转速传感器数据（角速度）
tachometer->PushFilter(chrono_types::make_shared<ChFitlerTachometerAccess>());

// 将传感器添加到管理器
manager->AddSensor(tachometer);
~~~

### 转速传感器数据访问

~~~cpp
UserTachometerBufferPtr data_ptr;
while(){
    data_ptr = tachometer->GetMostRecentBuffer<UserTachometerBufferPtr>();
    if (data_ptr->Buffer){
        // 获取并打印角速度
        angular_vel = data_ptr->Buffer[0];
        std::cout<<"角速度: "<<angular_vel<<std::endl;
    }
}
~~~
