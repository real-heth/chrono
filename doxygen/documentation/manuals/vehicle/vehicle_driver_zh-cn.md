驾驶员子系统 {#vehicle_driver}
==================================

\tableofcontents

驾驶员输入（转向、油门和制动）由驾驶员子系统提供，Chrono::Vehicle 中可用的选项包括交互式、数据驱动和闭环（例如基于 PID 控制器的路径跟随）。

驾驶员系统的基类 [ChDriver](@ref chrono::vehicle::ChDriver) 对驾驶员系统模板施加了最小要求，特别是能够返回油门输入（在 \f$[0,1]\f$ 范围内归一化）、转向输入（在 \f$[-1, +1]\f$ 范围内归一化，负值表示向左转向）和制动输入（在 \f$[0,1]\f$ 范围内归一化）。此外，驾驶员系统可以通过其 `Synchronize` 方法从任何其他系统（例如车辆状态）接收信息，并且可以具有内部动力学（在其 `Advance` 方法中实现）。特定的驾驶员系统模板可以扩展生成的车辆输入集，例如包括手动变速器的当前选定档位、启用/禁用履带车辆的交叉驱动功能等。

Chrono::Vehicle 包含多个驾驶员系统模板。对于以软实时运行的交互式仿真，它提供了一个驾驶员系统模板，该模板基于用户控制（键盘和鼠标或游戏控制器）生成车辆输入。

对于实验设计仿真，它提供了一个基于通过文本数据文件提供的输入的驾驶员系统模板，车辆输入通过线性插值获得。这些数据文件也可以通过在交互式运行期间收集的数据自动生成。

最后，Chrono::Vehicle 包含几个基于 PID 控制器的闭环驾驶员系统模型。这些模型包括速度控制器（同时调整油门和制动输入以保持恒定车速）和路径跟随控制器。后者调整转向输入，使车辆沿用户定义的路径（以贝塞尔曲线指定）行驶。

## 交互式驾驶员 {#vehicle_driver_interactive}

交互式驾驶员 [ChInteractiveDriver](@ref chrono::vehicle::ChInteractiveDriver)（适用于 VSG 和 Irrlicht 的运行时可视化系统）可以通过用户输入控制（转向/加速/制动）模拟车辆。这些交互式驾驶员依赖于各自运行时可视化系统的键盘和控制器事件处理程序。

该驾驶员子系统模型的其他功能包括：

- 实验性控制器支持
- 能够锁定/解锁驾驶员输入到当前值（通过键 `J` 控制）
- 能够记录和回放用户输入（使用嵌入的数据驱动驾驶员；见下文）

### 键盘驾驶员

- 按下 `A` 键会增加向左转向的角度
- 按下 `D` 键会增加向右转向的角度
- 按下 `W` 键会加速
- 按下 `S` 键会减速

油门和制动控制是耦合的，这意味着加速首先将制动输入降至零，然后再增加油门输入（减速时反之亦然）。

### 控制器驾驶员

现代模拟器通常为汽车中的所有不同控制元件提供多个（USB）设备。它们配备了踏板、方向盘、H型换挡器、顺序换挡器、手刹和按钮盒（带有大量按钮用于更改车内系统）。Chrono 支持通过将控制器轴和按钮分配给多个附加设备来实现这一点。轴还可以进行校准，设置该轴的最小和最大（原始）值以及预期的（缩放）输出值。

映射和校准是使用 `data/vehicles` 文件夹中的 "controller.json" 文件完成的，该文件允许您将控制分配给这些“控制器”的轴和按钮。我们提供了一些此类文件的示例，但通常您需要根据自己的设置自定义此文件：

* `controller_XboxOneForWindows.json` 是一个相当标准的控制器设置，应该很容易适应大多数用户，它映射了所有轴并包括顺序换挡器设置以及在自动和手动变速箱之间切换的方法。
* `controller_WheelPedalsAndShifters.json` 是一个更复杂的多控制器设置示例，具有方向盘、三个踏板，以及顺序和 H 型换挡器设置。如果您想使用它，可能需要进行大量修改，但它展示了如何使用不同的控制器。

#### 控制器文件示例

```json
{
    "steering": {
        "name": "Steering Wheel", "axis": 0,
        "min": -32768, "max": 32767, "scaled_min": 1, "scaled_max": -1
    },
    "throttle": {
        "name": "Pedal Box", "axis": 2,
        "min": -1, "max": -32767, "scaled_min": 0, "scaled_max": 1
    },
    "brake": {
        "name": "Pedal Box", "axis": 2,
        "min": 0, "max": 32767, "scaled_min": 0, "scaled_max": 1
    },
    "clutch": {
        "name": "Pedal Box", "axis": 4,
        "min": 0, "max": 32767, "scaled_min": 0, "scaled_max": 1
    },
    "gearReverse": { "name": "H-Shifter", "button": 0 },
    "gear1": { "name": "H-Shifter", "button": 1 },
    "gear2": { "name": "H-Shifter", "button": 2 },
    "gear3": { "name": "H-Shifter", "button": 3 },
    "gear4": { "name": "H-Shifter", "button": 4 },
    "gear5": { "name": "H-Shifter", "button": 5 },
    "gear6": { "name": "H-Shifter", "button": 6 },
    "gear7": { "name": "H-Shifter", "button": 7 },
    "gear8": { "name": "H-Shifter", "button": 8 },
    "gear9": { "name": "H-Shifter", "button": 9 },
    "shiftUp": { "name": "Steering Wheel", "button": 4 },
    "shiftDown": { "name": "Steering Wheel", "button": 5 },
    "toggleManualGearbox": { "name": "Button Box", "button": 2 }
}
```

在文件的顶层，我们有一个控制器功能的集合（`steering`、`throttle`、`shiftUp` 等），对于每个功能，我们可以指定轴或按钮定义以及所有映射细节：

* 轴：`steering`、`throttle`、`brake`、`clutch` 具有以下属性：
  * `name` 是系统上控制器的名称；
  * `axis` 是要映射到的轴的编号；
  * `min` 和 `max` 是该轴的原始最小值和最大值；
  * `scaled_min` 和 `scaled_max` 是该轴的输出最小值和最大值；
* 按钮：`shiftUp`、`shiftDown`、`gearReverse`、`gear1`、`gear2`、...、`gear9`、`toggleManualGearbox` 具有以下属性：
    * `name` 是系统上控制器的名称；
    * `button` 是要映射到的按钮编号；

关于控制变速箱的一点说明：

 * 如果您有手动变速箱，支持顺序换挡器。您可以使用另一个按钮在自动和手动变速箱之间切换。
 * 还支持 H 型换挡器。代码支持最多 9 个前进档，并支持换挡（只要离合器完全踩下）。

还有一个调试模式，每秒两次打印所有连接控制器的轴和按钮的值。这在定义文件时非常有用，否则应该禁用。

#### 当前实现的限制

* 所有控制器处理都与 IrrLicht 相关，这意味着您需要使用它进行可视化。这也意味着我们继承了 IrrLicht 处理控制器的所有限制。这主要体现在每个控制器支持的按钮数量上，但可能还存在其他限制。

## 基于数据的（开环）驱动模型 {#vehicle_driver_data}

一些重要的车辆测试操作基于时间依赖的转向/油门/制动信号。没有考虑任何形式的反馈。该驱动模型在 [ChDataDriver](@ref chrono::vehicle::ChDataDriver) 中实现。

一个包含驱动输入的 ASCII 数据文件包含四列，分别为时间（秒）、转向输入（无量纲量，范围在 \f$[-1,1]\f$，其中 \f$-1\f$ 表示完全向左转向）、油门输入（无量纲量，范围在 \f$[0,1]\f$，其中 \f$1\f$ 表示全油门）和制动（无量纲量，范围在 \f$[0,1]\f$，其中 \f$1\f$ 表示全制动力）。

下面列出了一个示例驱动数据文件
\include "data/vehicle/generic/driver/Sample_Maneuver.txt"

<img src="http://www.projectchrono.org/assets/manual/vehicle/curves/DataDriver.png" width="500" />

在任何给定时间，当前的驱动输入（转向、油门和制动）都是通过对提供的数据进行分段线性插值获得的。超出最后一个时间条目后，驱动输入将保持在其最后的值。

## 闭环驱动模型 {#vehicle_driver_closed_loop}

闭环驱动模型需要一个控制策略并考虑反馈。反馈可能导致不稳定的行为，因此控制器参数必须谨慎选择。示例参数在广泛的使用范围内有效。用户应从给定的示例参数集之一开始，仅在必要时进行修改。

### 路径跟随控制器

为了使车辆沿给定路径行驶，有必要测量横向路径偏差并生成一个最小化偏差的方向盘角度。一个众所周知的解决方案是 PID 控制器（P=比例，I=积分，D=微分）。采用纯 P 变体时，只需设置 P 增益。这在许多情况下都有效，但纯 P 控制器永远无法将横向偏差降至零。残余偏差随着 P 增益的增加而减小。如果 P 增益过大，车辆会在要求的车辆路径周围振荡。通过将 I 增益设置为 P 增益的约 5% 到 10%，可以消除残余路径偏差。通过设置 D 增益，如果发生路径振荡，可以施加阻尼。如果使用 I 增益，模拟操作不应超过约 2 分钟。如果需要更长时间，应每 2 分钟重置控制器状态以避免不稳定。

下图（Wikipedia）显示了 Chrono 如何实现 PID 控制器：

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/PID_en.svg/2880px-PID_en.svg.png" width="500"/>

- r(t) = 期望路径信号
- e(t) = 横向路径偏差
- y(t) = 实际路径信号
- u(t) = 转向信号

下图（Wikipedia）显示了增益因子的影响：

<img src="https://upload.wikimedia.org/wikipedia/commons/3/33/PID_Compensation_Animated.gif" width="500"/>

人类驾驶员不仅对偏差变化做出反应，还能够进行预判。在 Chrono 中，这种能力通过在车辆前方设置一个参考点来测量偏差来模拟。参考点与车辆参考系的距离称为前视距离，这是一个重要的控制器输入参数。

期望路径由贝塞尔曲线指定（参见 [ChBezierCurve](@ref chrono::ChBezierCurve)）。误差定义为“哨兵点”（位于车辆前进方向的前视距离处的点）与“目标点”（哨兵点在期望路径上的投影）之间的偏差。

### 恒速控制器

为了保持给定的车辆速度，可以使用 PID 控制器。与路径控制器的区别在于，它使用速度偏差而不是横向路径偏差。

- r(t) = 期望速度信号
- e(t) = 速度偏差
- y(t) = 实际速度信号
- u(t) = 油门/制动信号

[ChPathFollowerDriver](@ref chrono::vehicle::ChPathFollowerDriver) 类实现了 PID 横向控制器与 PID 速度控制器的组合。在极端操作（如双车道变换）中表现良好。

对于标准道路驾驶操作，一个有趣的替代方案是 [ChPathFollowerDriverSR](@ref chrono::vehicle::ChPathFollowerDriverSR)。它具有 PID 速度控制器，但采用考虑人类和车辆特性的横向控制策略。预判使用前视时间而不是前视距离，这意味着有效的前视距离随速度变化。

### 最优速度控制器

恒速控制器适用于许多标准驾驶操作。在长而弯曲的道路上驾驶时，了解车辆能够以多快的速度完成整个路线是很有趣的。为此，开发了 [ChHumanDriver](@ref chrono::vehicle::ChHumanDriver) 类。横向和速度控制器都使用人类行为、车辆特性和预判以及驾驶员的视野。横向控制器与 [ChPathFollowerDriverSR](@ref chrono::vehicle::ChPathFollowerDriverSR) 中实现的控制器相同。
