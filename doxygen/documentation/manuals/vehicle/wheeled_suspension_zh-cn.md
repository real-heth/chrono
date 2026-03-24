悬挂模型 {#wheeled_suspension}
=======================================

\tableofcontents

悬挂子系统是车轮车辆一个车轴的模型。基类 [ChSuspension](@ref chrono::vehicle::ChSuspension) 要求任何派生的悬挂类（悬挂模板）提供两个车轮主轴（左和右），每个通过旋转关节连接到该类型悬挂的某个部件，以及两个主轴轴（[ChShaft](@ref chrono::ChShaft) 类型的元素），如果该车轴是驱动的，则可以连接到车辆传动系统。

派生的悬挂类型定义了特定类型悬挂的车体、关节、力元件和拓扑结构。所有位置都假定是相对于悬挂参考框架提供的（派生悬挂类型可以自由选择该框架的位置，但不能改变其方向，假定其与底盘 ISO 参考框架平行）。

悬挂组件通过指定悬挂组件参考框架相对于底盘参考框架的位置来连接到底盘（参见 [ISO 参考框架](@ref vehicle_ISO_frame) 的定义）。

## 双叉臂悬挂 {#wheeled_suspension_ChDoubleWishbone}

独立可转向悬挂，使用两个叉臂控制臂（也称为 A 臂）连接转向节和底盘。用于 [HMMWV](@ref chrono::vehicle::hmmwv::HMMWV) 车辆模型的前后悬挂。

参见 [ChDoubleWishbone](@ref chrono::vehicle::ChDoubleWishbone) 和 [DoubleWishbone](@ref chrono::vehicle::DoubleWishbone)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishbone_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishbone_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishbone_points.png" width="600" />

## 双叉臂悬挂（简化） {#wheeled_suspension_ChDoubleWishboneReduced}

该简化双叉臂悬挂模板使用两个距离约束来模拟上下控制臂。当控制臂的质量和惯性相对于系统中的其他车体较小时，可以忽略不计。

参见 [ChDoubleWishboneReduced](@ref chrono::vehicle::ChDoubleWishboneReduced) 和 [DoubleWishboneReduced](@ref chrono::vehicle::DoubleWishboneReduced)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishboneReduced_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishboneReduced_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/DoubleWishboneReduced_points.png" width="600" />

## 麦弗逊支柱悬挂 {#wheeled_suspension_ChMacPhersonStrut}

独立可转向悬挂系统，适用于前轮驱动和横置发动机/变速箱的小型到中型乘用车。

参见 [ChMacPhersonStrut](@ref chrono::vehicle::ChMacPhersonStrut) 和 [MacPhersonStrut](@ref chrono::vehicle::MacPhersonStrut)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MacPhersonStrut_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MacPhersonStrut_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MacPhersonStrut_points.png" width="600" />

## 多连杆悬挂 {#wheeled_suspension_ChMultiLink}

该悬挂系统类似于双叉臂车轴。拖臂可以承受较高的纵向力。

参见 [ChMultiLink](@ref chrono::vehicle::ChMultiLink) 和 [MultiLink](@ref chrono::vehicle::MultiLink)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MultiLink_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MultiLink_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/MultiLink_points.png" width="600" />

## 半拖臂悬挂 {#wheeled_suspension_ChSemiTrailingArm}

小型乘用车后悬挂使用的简单独立车轴系统。

参见 [ChSemiTrailingArm](@ref chrono::vehicle::ChSemiTrailingArm) 和 [SemiTrailingArm](@ref chrono::vehicle::SemiTrailingArm)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SemiTrailingArm_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SemiTrailingArm_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SemiTrailingArm_points.png" width="600" />

## 实心车轴悬挂 {#wheeled_suspension_ChSolidAxle}

实心车轴系统由四个连杆引导。它通常使用螺旋弹簧或空气弹簧，可以在较老的乘用车中找到。

参见 [ChSolidAxle](@ref chrono::vehicle::ChSolidAxle) 和 [SolidAxle](@ref chrono::vehicle::SolidAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidAxle_points.png" width="600" />

## 实心三连杆车轴悬挂 {#wheeled_suspension_ChSolidThreeLinkAxle}

用于 [MAN 5t](@ref chrono::vehicle::man::MAN_5t)、[MAN 7t](@ref chrono::vehicle::man::MAN_7t) 和 [MAN 10t](@ref chrono::vehicle::man::MAN_10t) 卡车模型的后悬挂。该悬挂允许非常高的车轮行程，这是叶片弹簧无法实现的。它也用于配备空气弹簧的公路卡车。空气弹簧和螺旋弹簧需要由连杆引导的悬挂。

参见 [ChSolidThreeLinkAxle](@ref chrono::vehicle::ChSolidThreeLinkAxle) 和 [SolidThreeLinkAxle](@ref chrono::vehicle::SolidThreeLinkAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidThreeLinkAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidThreeLinkAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidThreeLinkAxle_points.png" width="600" />

## 实心三连杆车轴悬挂（带摇臂） {#wheeled_suspension_ChSolidBellcrankThreeLinkAxle}

用于 [MAN 5t](@ref chrono::vehicle::man::MAN_5t)、[MAN 7t](@ref chrono::vehicle::man::MAN_7t) 和 [MAN 10t](@ref chrono::vehicle::man::MAN_10t) 卡车模型的前悬挂。

参见 [ChSolidBellcrankThreeLinkAxle](@ref chrono::vehicle::ChSolidBellcrankThreeLinkAxle) 和 [SolidBellcrankThreeLinkAxle](@ref chrono::vehicle::SolidBellcrankThreeLinkAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidBellcrankThreeLinkAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidBellcrankThreeLinkAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SolidBellcrankThreeLinkAxle_points.png" width="600" />

## 叶片弹簧实心车轴悬挂 {#wheeled_suspension_ChLeafspringAxle}

用于 [UAZ](@ref chrono::vehicle::uaz::UAZBUS) 车辆模型的后悬挂。叶片弹簧车轴具有复杂的导向行为。这是一种仿真解决方案，其中叶片弹簧的导向效果通过车轴管中心的特殊关节来模拟。悬挂效果由螺旋弹簧建模。滚动行为接近真实的叶片弹簧车轴。

参见 [ChLeafspringAxle](@ref chrono::vehicle::ChLeafspringAxle) 和 [LeafspringAxle](@ref chrono::vehicle::LeafspringAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/LeafspringAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/LeafspringAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/LeafspringAxle_points.png" width="600" />

## 带摇臂的叶片弹簧实心车轴悬挂 {#wheeled_suspension_ChToeBarLeafspringAxle}

用于 [UAZ](@ref chrono::vehicle::uaz::UAZBUS) 车辆模型的前悬挂。

参见 [ChToeBarLeafspringAxle](@ref chrono::vehicle::ChToeBarLeafspringAxle) 和 [ToeBarLeafspringAxle](@ref chrono::vehicle::ToeBarLeafspringAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ToeBarLeafspringAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ToeBarLeafspringAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ToeBarLeafspringAxle_points.png" width="600" />

## SAE 叶片弹簧实心车轴悬挂 {#wheeled_suspension_ChSAELeafspringAxle}

SAE 弹簧设计手册展示了一种在负载条件下模拟叶片弹簧的真实变形行为的方法。叶片弹簧的运动学可以通过 5 个点来定义。这些点可以用来定义由 6 个刚体（前叶片、前夹具、后夹具、后叶片和吊架）组成的叶片弹簧。各个刚体通过关节连接。前后叶片以及前后夹具的旋转弹簧具有可由用户设置的旋转刚度，以定义正确的行为。该悬挂用于 [UAZ](@ref chrono::vehicle::uaz::UAZBUS) 车辆 SAE 类型模型的后悬挂。通过该叶片弹簧模型，可以正确模拟车轴由于车轮行程引起的运动以及纵向力引起的捆绑效应。

参见 [ChSAELeafspringAxle](@ref chrono::vehicle::ChLeafspringAxle) 和 [SAELeafspringAxle](@ref chrono::vehicle::LeafspringAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAELeafspringAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAELeafspringAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAELeafspringAxle_points.png" width="600" />

## 带摇臂的 SAE 叶片弹簧实心车轴悬挂 {#wheeled_suspension_ChSAEToeBarLeafspringAxle}

用于 [UAZ](@ref chrono::vehicle::uaz::UAZBUS) SAE 类型车辆模型的前悬挂。叶片弹簧的定义与 SAE 叶片弹簧车轴相同。

参见 [ChSAEToeBarLeafspringAxle](@ref chrono::vehicle::ChToeBarLeafspringAxle) 和 [SAEToeBarLeafspringAxle](@ref chrono::vehicle::SAEToeBarLeafspringAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAEToeBarLeafspringAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAEToeBarLeafspringAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/SAEToeBarLeafspringAxle_points.png" width="600" />

## 三连杆独立后悬挂 {#wheeled_suspension_ChThreeLinkIRS}

三连杆独立后悬挂 (IRS)，如 Polaris RZR 车辆所示。

参见 [ChThreeLinkIRS](@ref chrono::vehicle::ChThreeLinkIRS) 和 [ThreeLinkIRS](@ref chrono::vehicle::ThreeLinkIRS)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ThreeLinkIRS_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ThreeLinkIRS_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/ThreeLinkIRS_points.png" width="600" />

## 刚性悬挂 {#wheeled_suspension_ChRigidSuspension}

简单的组件，主销直接连接到固定在底盘上的车轴管。典型用于农用拖拉机和联合收割机。

参见 [ChRigidSuspension](@ref chrono::vehicle::ChRigidSuspension) 和 [RigidSuspension](@ref chrono::vehicle::RigidSuspension)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidSuspension_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidSuspension_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidSuspension_points.png" width="600" />

## 刚性铰接车轴悬挂 {#wheeled_suspension_ChRigidPinnedAxle}

简单的组件，主销直接连接到车轴管，可以绕枢轴点相对于底盘摆动。如果需要一个非弹簧车轴系统，但必须在起伏地形上运行以避免车轮抬起，可以使用此悬挂。

参见 [ChRigidPinnedAxle](@ref chrono::vehicle::ChRigidPinnedAxle) 和 [RigidPinnedAxle](@ref chrono::vehicle::RigidPinnedAxle)。

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidPinnedAxle_bodies.png" width="600" />

该悬挂模板的拓扑结构为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidPinnedAxle_topology.png" width="800" />

硬点（仅为左侧定义，并镜像以构建右侧）为：

<img src="http://www.projectchrono.org/assets/manual/vehicle/wheeled/RigidPinnedAxle_points.png" width="600" />

## 通用轮式车辆悬挂模板 {#wheeled_suspension_ChGenericWheeledSuspension}

该模板允许指定用户定义的、自定义的悬挂子系统，具有任意拓扑结构。
具体的悬挂通过添加车身、关节、距离约束和 TSDA 来构建。每个建模组件都可以标记为“镜像”。用户负责定义所有非镜像组件和左侧镜像组件（相应的右侧组件会自动生成）。

参见 [ChGenericWheeledSuspension](@ref chrono::vehicle::ChGenericWheeledSuspension) 和 [GenericWheeledSuspension](@ref chrono::vehicle::GenericWheeledSuspension)。
