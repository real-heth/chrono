惰轮模型 {#tracked_idler}
=============================

Chrono::Vehicle 的惰轮机构由惰轮和将惰轮连接到底盘的机构组成。惰轮可以是假定有中央导向销的 [ChDoubleTrackWheel](@ref chrono::vehicle::ChDoubleTrackWheel)，也可以是假定有侧向导向销的 [ChSingleTrackWheel](@ref chrono::vehicle::ChSingleTrackWheel)。

惰轮子系统是相对于以惰轮原点为中心的参考系定义的，该参考系可以相对于底盘参考系倾斜。平移关节与该参考系的 X 轴对齐，而旋转关节的旋转轴与其 Y 轴对齐。

针对不同的惰轮机构拓扑，提供了不同的模板。

## 平移惰轮 {#tracked_idler_translational}

惰轮通过旋转关节连接到连接体，连接体又通过平移关节连接到底盘。线性执行器作为张紧器，其模型为带有可选预载的通用弹簧-阻尼器。

请参见 [ChTranslationalIdler](@ref chrono::vehicle::ChTranslationalIdler) 和 [TranslationalIdler](@ref chrono::vehicle::TranslationalIdler)。

## 距离惰轮 {#tracked_idler_distance}

惰轮通过销轴连接到底盘上的臂。固定距离约束将臂相对于底盘定位。

请参见 [ChDistanceIdler](@ref chrono::vehicle::ChDistanceIdler) 和 [DistanceIdler](@ref chrono::vehicle::DistanceIdler)。
