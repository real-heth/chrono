链轮模型 {#tracked_sprocket}
===================================

\tableofcontents

链轮子系统将履带车辆的传动系统连接到履带组件，并负责与履带板主体的碰撞检测和接触处理。链轮子系统模板实现了针对一致的链轮齿轮轮廓和相关履带板的自定义碰撞检测算法。Chrono::Vehicle 提供了两种链轮子系统模板，分别对应支持的履带板类型，即单销、双销和带状履带。链轮齿轮轮廓定义为由线段和圆弧组成的二维路径，并针对每种轮廓类型进行参数化。碰撞检测在二维平面中进行，工作在链轮齿轮的平面内，但接触力在三维中计算，然后应用于链轮和相互作用的履带板主体。

除了齿轮轮廓外，链轮模板还通过链轮本体的质量和惯性、链轮轴的转动惯量以及两个齿轮之间的间距进行参数化。

## 单销链轮 {#tracked_sprocket_single_pin}

此链轮模板使用由圆弧组成的齿轮轮廓。此类型的链轮适用于与单销履带板的交互。

请参见 [ChSprocketSinglePin](@ref chrono::vehicle::ChSprocketSinglePin) 和 [SprocketSinglePin](@ref chrono::vehicle::SprocketSinglePin)。


## 双销链轮 {#tracked_sprocket_double_pin}

此链轮模板使用由圆弧和扁平座组成的齿轮轮廓。此类型的链轮适用于与双销履带板的交互。

请参见 [ChSprocketDoublePin](@ref chrono::vehicle::ChSprocketDoublePin) 和 [SprocketDoublePin](@ref chrono::vehicle::SprocketDoublePin)。


## 带状链轮 {#tracked_sprocket_band}

此链轮模板使用由圆弧和扁平座组成的齿轮轮廓。此类型的链轮适用于与连续带履带的交互。

请参见 [ChSprocketBand](@ref chrono::vehicle::ChSprocketBand) 和 [SprocketBand](@ref chrono::vehicle::SprocketBand)。
