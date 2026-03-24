传动系统模型 {#wheeled_driveline}
=====================================

\tableofcontents

驱动系统子系统（也称为传动系统）是一组将动力传递到车辆驱动轮的组件。目前，Chrono::Vehicle 提供了用于传统传动系统的模板，这些传动系统连接到单个电机（在动力系统子系统中）并将动力传递到车辆的一个、两个或多个车轴。

传动系统与动力系统之间以及传动系统与驱动轮之间的接口是力-位移连接。特别是，动力系统向传动系统的传动轴提供扭矩，传动系统设置传动轴的角速度。同样，传动系统将扭矩传递并施加到驱动轮的车轴上，并接收车轮车轴的当前角速度。根据传动系统和动力系统的类型，传动系统-动力系统和传动系统-车轮的连接可以通过约束或纯运动学方式强制执行。

## 四轮轴传动系统 {#wheeled_driveline_4WD_shafts}

该传动系统模板使用各种 Chrono 一维轴元件 ([ChShaft](@ref chrono::ChShaft)) 和专用轴连接元件建模。这些元件用于建模差速器 ([ChShaftsPlanetary](@ref chrono::ChShaftsPlanetary))、锥齿轮 ([ChShaftsGearboxAngled](@ref chrono::ChShaftsGearboxAngled)) 和离合器 ([ChShaftsClutch](@ref chrono::ChShaftsClutch)) 以实现差速锁定。

请参见 [ChShaftsDriveline4WD](@ref chrono::vehicle::ChShaftsDriveline4WD) 和 [ShaftsDriveline4WD](@ref chrono::vehicle::ShaftsDriveline4WD)。

下面的图像显示了连接到基于轴的动力系统模型的四轮驱动轴传动系统。

<img src="http://www.projectchrono.org/assets/manual/vehicle/shafts_powertrain.png" width="800" />

四轮驱动轴传动系统的各种模板参数在以下示例 JSON 规范文件中进行了说明：
\include "data/vehicle/hmmwv/driveline/HMMWV_Driveline4WD.json"

## 两轮轴传动系统 {#wheeled_driveline_2WD_shafts}

该传动系统模板类似于四轮驱动轴传动系统模型，但只能驱动与单个车辆车轴相关的车轮。该车轴是任意的，因此该传动系统模型可用于建模前轮驱动和后轮驱动的车辆。

请参见 [ChShaftsDriveline2WD](@ref chrono::vehicle::ChShaftsDriveline2WD) 和 [ShaftsDriveline2WD](@ref chrono::vehicle::ShaftsDriveline2WD)。

以下是一个两轮驱动轴传动系统的示例 JSON 文件：
\include "data/vehicle/hmmwv/driveline/HMMWV_Driveline2WD.json"

## 四轮运动学传动系统 {#wheeled_driveline_4WD_simple}

该模板可用于建模四轮驱动传动系统。它使用恒定的前/后扭矩分配（值在 0 和 1 之间）以及 Torsen 限滑差速器的简单模型。

请参见 [ChSimpleDriveline](@ref chrono::vehicle::ChSimpleDriveline) 和 [SimpleDriveline](@ref chrono::vehicle::SimpleDriveline)。

以下是一个四轮运动学传动系统的示例 JSON 文件：
\include "data/vehicle/hmmwv/driveline/HMMWV_DrivelineSimple.json"

## X 轮运动学传动系统 {#wheeled_driveline_XWD_simple}

该简单传动系统模板可用于建模 XWD 传动系统，能够驱动一个或多个车辆车轴。它使用恒定的扭矩分配，具体取决于驱动车轴的数量，并使用 Torsen 限滑差速器的简单模型。

请参见 [ChSimpleDrivelineXWD](@ref chrono::vehicle::ChSimpleDrivelineXWD) 和 [SimpleDrivelineXWD](@ref chrono::vehicle::SimpleDrivelineXWD)。

以下是一个 XWD 传动系统的示例 JSON 文件：
\include "data/vehicle/MAN_Kat1/driveline/MAN_5t_DrivelineSimpleXWD.json"
