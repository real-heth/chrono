悬挂模型 {#tracked_suspension}
=======================================

\tableofcontents

不同的悬挂配置可用，包括带线性或旋转阻尼器的扭转弹簧和液气悬挂模板。履带组件可以包含任意数量的悬挂子系统，对于使用扭转弹簧的模板，可能包含也可能不包含阻尼器。Chrono::Vehicle 悬挂子系统还包含一个车轮本体，根据使用的履带板类型（中央或侧向导向销）进行模板化。

类似于轮式车辆的情况，履带车辆悬挂模板允许在指定弹簧和阻尼器力时具有完全的自由度，这些力可以是线性或非线性的，通过查表定义或在用户提供的 C++ 函数中实现。

## 履带悬挂模型 {#suspension_models}

### 线性阻尼器悬挂 {#tracked_suspension_translational_damper}

请参见 [ChTranslationalDamperSuspension](@ref chrono::vehicle::ChTranslationalDamperSuspension) 和 [TranslationalDamperSuspension](@ref chrono::vehicle::TranslationalDamperSuspension)。

### 旋转阻尼器悬挂 {#tracked_suspension_rotational_damper}

请参见 [ChRotationalDamperSuspension](@ref chrono::vehicle::ChRotationalDamperSuspension) 和 [RotationalDamperSuspension](@ref chrono::vehicle::RotationalDamperSuspension)。

## 车轮模型 {#roadwheel_models}

### 中央销车轮 {#tracked_susepension_roadwheel_central}

请参见 [ChDoubleTrackWheel](@ref chrono::vehicle::ChDoubleTrackWheel) 和 [DoubleTrackWheel](@ref chrono::vehicle::DoubleTrackWheel)。

### 侧向销车轮 {#tracked_suspension_roadwheel_lateral}

请参见 [ChSingleTrackWheel](@ref chrono::vehicle::ChSingleTrackWheel) 和 [SingleTrackWheel](@ref chrono::vehicle::SingleTrackWheel)。
