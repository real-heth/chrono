动力系统模型 {#vehicle_powertrain}
=======================================

\tableofcontents

动力系统连接到驾驶员系统（接收油门输入）和车辆系统的传动系统子系统（接收驱动轴角速度并发送驱动轴扭矩）。

<img src="http://www.projectchrono.org/assets/manual/vehicle/powertrain_data_flow.png" width="600" />

Chrono::Vehicle 设计允许链接到第三方动力系统模型。与这样的外部动力系统模型接口需要两个薄接口类，分别派生自 [ChEngine](@ref chrono::vehicle::ChEngine) 和 [ChTransmission](@ref chrono::vehicle::ChTransmission)。

Chrono::Vehicle 提供了几种动力系统模板，下面将进行描述。

## 基于轴的动力系统模型 {#vehicle_powertrain_shafts}

该动力系统模型基于各种 Chrono 一维轴元素 ([ChShaft](@ref chrono::ChShaft)) 和专用轴连接元素。这些元素用于建模：

- 发动机 ([ChShaftsThermalEngine](@ref chrono::ChShaftsThermalEngine))，通过速度-扭矩曲线指定
- 扭矩转换器 ([ChShaftsTorqueConverter](@ref chrono::ChShaftsTorqueConverter))，通过容量因子随速度比变化的曲线和扭矩比随速度比变化的曲线指定
- 变速箱（手动或自动，具有任意数量的前进档和一个倒档）

电机块通过一个特殊的 Chrono 约束 ([ChShaftBodyRotation](@ref chrono::ChShaftBodyRotation)) 连接到底盘，从而允许模拟电机扭矩对底盘的影响。

参见 [ChEngineShafts](@ref chrono::vehicle::ChEngineShafts),  [ChAutomaticTransmissionShafts](@ref chrono::vehicle::ChAutomaticTransmissionShafts), 和 [ChManualTransmissionShafts](@ref chrono::vehicle::ChManualTransmissionShafts)

下图显示了基于轴的动力系统模型连接到基于轴的轮式车辆模型。

<img src="http://www.projectchrono.org/assets/manual/vehicle/shafts_powertrain.png" width="800" />

下面提供了基于轴的动力系统的示例 JSON 文件，说明了各种模板参数：
\include "data/vehicle/hmmwv/powertrain/HMMWV_EngineShafts.json"
\include "data/vehicle/hmmwv/powertrain/HMMWV_AutomaticTransmissionShafts.json"

上面 JSON 文件中编码的曲线如下所示。

<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/ShaftsPowertrain_engine_curves.png" width="500" />
<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/ShaftsPowertrain_TC_curves.png" width="500" />

## 基于发动机映射的动力系统模型 {#vehicle_powertrain_map}

该模板用于基于速度-扭矩发动机映射的简单动力系统模型。该模型没有扭矩转换器，可以具有手动或自动变速箱。它接受一个倒档和任意数量的前进档。在自动模式下，换档是基于指定的理想换档点进行的。

参见 [ChEngineSimpleMap](@ref chrono::vehicle::ChEngineSimpleMap) 和 [ChAutomaticTransmissionSimpleMap](@ref chrono::vehicle::ChAutomaticTransmissionSimpleMap)。

下面提供了基于发动机映射的动力系统的示例 JSON 文件，说明了各种模板参数：
\include "data/vehicle/uaz/powertrain/UAZBUS_EngineSimpleMap.json"
\include "data/vehicle/uaz/powertrain/UAZBUS_AutomaticTransmissionSimpleMap.json"

上面 JSON 文件中编码的曲线如下所示。

<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/SimpleMapPowertrain_engine_curves.png" width="500" />
<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/SimpleMapPowertrain_shift_bands.png" width="500" />

## 简单动力系统模型 {#vehicle_powertrain_simple}

该模型使用简单的速度-扭矩依赖关系，没有扭矩转换器，也没有变速箱。

参见 [ChEngineSimple](@ref chrono::vehicle::ChEngineSimple) 和 [EngineSimple](@ref chrono::vehicle::EngineSimple)。

下面提供了一个类似 CVT 的简单动力系统的示例 JSON 文件，说明了各种模板参数：
\include "data/vehicle/hmmwv/powertrain/HMMWV_EngineSimple.json"
