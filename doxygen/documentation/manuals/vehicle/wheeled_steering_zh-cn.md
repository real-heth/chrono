转向机构模型 {#wheeled_steering}
=============================================

\tableofcontents

基类 [ChSteering](@ref chrono::vehicle::ChSteering) 要求任何派生的转向机构类（转向机构模板）提供一个转向连杆体，以便可以连接可转向悬挂（通常通过悬挂的拉杆）。

派生的转向机构类型定义了特定类型转向机构的刚体、关节、力元件和拓扑结构。所有位置都假定是相对于机构参考系提供的（派生的转向机构类型可以自由选择该参考系的位置和方向）。

转向机构组件通过指定机构组件参考系相对于底盘参考系的位置和方向附加到底盘上（参见 [ISO 参考系](@ref vehicle_ISO_frame) 的定义）。

一个轮式车辆可以有多个转向机构，每个转向机构与不同的可转向车轴相关联。同样，一个转向机构也可以连接到多个可转向车轴。

## Pitman arm {#wheeled_steering_pitman}

该转向机构是一个四杆连杆机构，转向连杆体通过 Pitman 臂和从动臂连接到底盘。Pitman 臂体通过万向节连接到转向连杆，通过旋转关节连接到底盘。驾驶员的转向输入用于控制旋转关节的角度。在 Chrono::Vehicle Pitman 臂模板中，从动臂使用复合旋转-球形关节建模。

参见 [ChPitmanArm](@ref chrono::vehicle::ChPitmanArm) 和 [PitmanArm](@ref chrono::vehicle::PitmanArm)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/PitmanArm_bodies.png" width="600" />

该转向机构模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/PitmanArm_topology.png" width="800" />

关键点为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/PitmanArm_points.png" width="600" />

一个 PitmanArm 转向机构的示例 JSON 文件为：
\include "data/vehicle/hmmwv/steering/HMMWV_PitmanArm.json"

## 齿轮齿条 {#wheeled_steering_rack_pinion}

Chrono::Vehicle 齿轮齿条转向模板是齿轮齿条转向机构的运动学模型。转向连杆体通过棱柱关节连接到底盘。齿条位移计算如下：
\f[
d = r (\alpha_{max} s)
\f]
其中 \f$ r \f$ 是小齿轮半径，\f$ \alpha_{max} \f$ 是小齿轮最大角度，\f$ s \in [-1,1] \f$ 是驾驶员转向输入。该位移用于控制转向连杆的平移。

参见 [ChRackPinion](@ref chrono::vehicle::ChRackPinion) 和 [RackPinion](@ref chrono::vehicle::RackPinion)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RackPinion_bodies.png" width="600" />

该转向机构模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RackPinion_topology.png" width="800" />

关键点为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RackPinion_points.png" width="600" />

一个齿轮齿条转向机构的示例 JSON 文件为：
\include "data/vehicle/hmmwv/steering/HMMWV_RackPinion.json"

## 旋转臂 {#wheeled_steering_rotary_arm}

旋转臂转向是一种简单的杠杆臂，围绕一个轴旋转。它适用于实心摇臂车轴和实心前束杆车轴。它通常用作卡车、农用拖拉机和联合收割机的转向系统。

参见 [ChRotaryArm](@ref chrono::vehicle::ChRotaryArm) 和 [RotaryArm](@ref chrono::vehicle::RotaryArm)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RotaryArm_bodies.png" width="600" />

该转向机构模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RotaryArm_topology.png" width="800" />

关键点为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RotaryArm_points.png" width="600" />

一个旋转臂转向机构的示例 JSON 文件为：
\include "data/vehicle/uaz/steering/UAZBUS_RotaryArm.json"
