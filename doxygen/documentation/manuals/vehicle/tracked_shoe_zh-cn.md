履带板模型 {#tracked_shoe}
=========================

\tableofcontents

Chrono::Vehicle 提供了单销和双销履带板的模板，每种模板都可以具有中央或侧向导向销。单销履带板由一个具有非平凡接触几何形状的主体组成，通过旋转关节与相邻履带板连接。双销履带板模板除了主履带板主体外，还包含两个附加的连接体，这些连接体通过旋转关节与相邻履带板连接，并携带与履带链轮齿轮碰撞的接触几何形状。

此外，还提供了两种不同的连续带履带模型。

所有履带板模板在尺寸、质量和组成部分的惯性以及接触几何形状方面都是完全参数化的。

## 单销履带板 {#tracked_shoe_single_pin}

请参见 [ChTrackShoeSinglePin](@ref chrono::vehicle::ChTrackShoeSinglePin) 和 [TrackShoeSinglePin](@ref chrono::vehicle::TrackShoeSinglePin)。

## 双销履带板 {#tracked_shoe_double_pin}

请参见 [ChTrackShoeDoublePin](@ref chrono::vehicle::ChTrackShoeDoublePin) 和 [TrackShoeDoublePin](@ref chrono::vehicle::TrackShoeDoublePin)。

## 带衬套履带板 {#tracked_shoe_band_bushing}

请参见 [ChTrackShoeBandBushing](@ref chrono::vehicle::ChTrackShoeBandBushing) 和 [TrackShoeBandBushing](@ref chrono::vehicle::TrackShoeBandBushing)。  另请参见基类 [ChTrackShoeBand](@ref chrono::vehicle::ChTrackShoeBand)。

## 带 ANCF 履带板 {#tracked_shoe_band_ancf}

请参见 [ChTrackShoeBandANCF](@ref chrono::vehicle::ChTrackShoeBandANCF) 和 [ChTrackShoeBandANCF](@ref chrono::vehicle::TrackShoeBandANCF)。  另请参见基类 [ChTrackShoeBand](@ref chrono::vehicle::ChTrackShoeBand)。
