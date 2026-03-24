与 Simulink 的协同仿真（demo_COSIM_hydraulics.cpp）  {#tutorial_demo_cosim_hydraulics}
==========================

本教程说明如何使用协同仿真来模拟由液压系统驱动的简单机械机构。
液压系统由 Simulink 管理，而具有活动零件和铰链的机械机构由 Chrono 模拟。

所述方法可作为复杂场景的模板，例如多个液压缸驱动活动部件的机构。通常，Simulink 用于液压子系统的模拟与控制，而 Chrono 则用于机械系统的其余部分：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_01.png)

# 前提条件

本教程的前提条件包括：

- 已正确安装并能运行 Chrono 核心模块。
- 已安装 [Simulink](http://www.mathworks.com/products/simulink)。
- 已安装 Matlab 的 [Instrument Control Toolbox](http://www.mathworks.com/products/instrument)。
- 已安装 Matlab 的 [SimHydraulics Toolbox](http://www.mathworks.com/products/simhydraulics)。

<div class="ce-info">
SimHydraulics 是 Simulink 的一个可选 Matlab 工具箱。本 Chrono 示例需要它，但其他协同仿真示例并不一定需要。
</div>

# 背景

双向协同仿真利用两个仿真工具同时（时间上并行）推进被划分的两个子系统的仿真。两者会在某些时刻同步以交换数据，随后各自独立运行直到下一次同步时间。由于子系统彼此耦合，这种周期性的数据同步是必要的；对于强耦合的子系统，同步会更频繁。

协同仿真的方法有很多。此教程描述的方法比较简单——基于 Chrono 与 Simulink 之间如下的交互模式：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_02.png)

在上图中，假设系统由变量 $ \mathbf{X} = \{ \mathbf{X}_{CE}, \mathbf{X}_{S}\} $ 定义，并将其划分为 Chrono 处理 $ \mathbf{X}_{CE} $，Simulink 处理 $ \mathbf{X}_{S} $。

操作序列为：

- A) Chrono 仿真器以步长 $ dt $ 推进，直到同步点；
- B) Chrono 将 $ \mathbf{X}_{CE} $ 变量通过 TCP/IP 套接字发送到 Simulink；
- C) Simulink 将 $ \mathbf{X}_{S} $ 变量通过 TCP/IP 套接字发送到 Chrono；
- D) Simulink 仿真推进到同步点。注意 Simulink 可能采用变步长积分，因此到达同步点可能需要多个内部步长，详见图示。

该模式将重复直至仿真结束。

在本实现中，Simulink 接收到的 $ \mathbf{X}_{CE} $ 值在达到同步时间的步进过程中采用线性插值；而 Chrono 接收到的 $ \mathbf{X}_{S} $ 值则保持常量（零阶保持，ZOH）。

在此类协同仿真中，“慢”的积分器（Chrono）先于高频积分器（Simulink）。当然也可以反过来。还可以设计更复杂的插值/外推策略——例如使用外推代替 ZOH，或对 Simulink 中接收的 $ \mathbf{X}_{CE} $ 采用高阶插值。

当 Chrono 先于 Simulink 并对 $ \mathbf{X}_{S} $ 采用外推时，这相当于在 Chrono 与 Simulink 之间引入了一个因果延迟 $ dt $。当两个子系统耦合紧密时，过大的 $ dt $ 会导致数值不稳定问题。不幸的是，将 $ dt $ 设得非常小以解决稳定性问题往往会增加仿真时间。

# 系统描述

本教程考虑以下机构：在点 A 处有一铰接的杆，在点 B 与 D 之间有一线性执行器 L：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_03.png)

尽管 Chrono 已经提供了定义线性执行器的方法，但此处使用 Simulink 及其 SimHydraulics 工具箱来建立包含阀门、管路、泵和反馈控制等的高级液压缸模型。黄色的执行器将在 Simulink 中仿真，其余部分由 Chrono 仿真。

# Simulink 模型

首先，打开 Simulink 并创建一个包含泵和阀门的液压缸模型。为简便起见，可加载 SimHydraulics 的“动力助力转向机构（Power assisted steering mechanism）”示例（sh_hydraulic_power_assisted_steering.mdl）。该示例提供了一个现成系统，其中活塞根据方向盘旋转的反馈控制来往复移动：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_04.png)

注意，原始示例使用 SimScape/Simulink 模块建模了一个质量-弹簧-阻尼系统；双击 _Load_ 模块可以展开查看：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_05.png)

将 _Load_ 模块替换为 Chrono 机械载荷，需执行以下步骤：

- 删除 _Load_ 模块。

- 打开 `data/cosimulation/CEcosimulation.mdl`，复制 _CoSimulate_ 模块并将其粘贴到模型中，靠近活塞的位置。

- 选中 _CoSimulate_，使用菜单 Edit/Link Options../Break link 以便修改它。

- 在活塞与 _CoSimulate_ 模块之间建立如下连接：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_06.png)

_CoSimulate_ 模块是一个接口，它以固定时间间隔将输入变量向量发送到 Chrono，并接收返回的输出向量。具体来说：

- Simulink 将活塞的力发送给 Chrono。Chrono 会将该力施加到 B 与 D 之间的机械系统，并计算速度和位移。
- 反之：Chrono 将活塞的速度与位移发送给 Simulink。Simulink 会将该速度和位移施加到活塞，以便计算所需的力。

这也解释了需要两块黄色模块的原因：其中一块是用于获取反作用力的 SimScape 模块（在本例中为活塞杆），另一块用于施加运动（在本例中也作用于活塞杆）。灰色的 PS S 与 S PS 模块用于在 SimScape/SimHydraulics 信号与 Simulink 信号之间进行转换。

<div class="ce-info">
注意，本例也可以采用其他协同仿真方法。例如，可以在 Simulink 中施加力并向 Chrono 发送位移信息，然后 Chrono 使用约束式（rheonomic）线性执行器强制位移并将反作用力发送回 Simulink。
</div>

双击 _CoSimulate_ 模块并设置其参数：

![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_07.png)

参数含义：

- _Communication step size_：控制 Chrono 与 Simulink 交换信息的频率。由于液压问题通常较为刚性，本例需要非常小的步长，否则较大步长会导致数值不稳定。

- _N. of scalars received from Chrono_ 必须与从 Chrono 端通过 C++ 发送的变量数量匹配。本例中发送的是：1) 活塞杆速度；2) 活塞杆位移。

- _TCP host name_：如果在同一台计算机上运行两个仿真器，保持为 'localhost'；若 Chrono 在另一台机器上，请在此处填写该机器的 IP 地址。

- _TCP port_：任一未被防火墙阻塞且未占用的端口均可，例如使用 50009。

- _TCP timeout_：若 Chrono 在此超时时间内没有响应，仿真将被停止。

接着，将整个模型另存为合适的名称。本示例已提供可直接使用的模型：`data/cosimulation/test_cosim_hydraulics.mdl`。

# Chrono 模型

在 `src/demos/cosimulation/demo_COSIM_hydraulics.cpp` 中可以找到一个可直接运行的示例。该程序实现的步骤如下：

- 在socket通信操作周围使用 `try...catch`，因为套接字错误可能抛出异常。

- 创建一个 `ChSystem`，并添加桁架、移动体和一个铰链关节。

- 使用刚度与阻尼为零的 `ChLinkTSDA` 在两点之间创建一个“死”的线性执行器（dead linear actuator）。该连接将作为具有球形端部的圆柱体用于在两个刚体间施力。

- 创建一个弹簧-阻尼器以在运动时提供一定载荷，并配置系统求解器的精度。

- 添加一个socket框架对象（整个程序中使用的唯一实例）和一个协同仿真接口。


- 准备两个列向量，用于在 Chrono 与 Simulink 之间来回交换数据：
  - 从 Simulink 接收一个变量（液压缸的力）；
  - 向 Simulink 发送两个变量（液压缸的速度与位移）。

- 等待客户端（Simulink）连接。在本实现中 Chrono 为服务器，Simulink 为客户端。

- 建立连接后即可开始仿真。注意仿真步长 `dt` 必须与 CEcosimulation 模块中设置的值一致。

- 最后在socket连接出现任何问题时做好异常捕获处理。

# 运行协同仿真

到此，所有工具均已准备就绪。下一步：

- 编译 Chrono 程序；

- 运行 Chrono 程序；程序将进入等待状态，等待 Simulink 连接；

- 在 Simulink 中打开橙色的 “Input/Output” 示波器模块，以便绘制结果；

- 在 Simulink 界面中按下 '>' 按钮运行 Simulink 模型；

两个程序将并行运行，并定期交换数据，直到仿真结束或按下停止或终止 Chrono 程序为止。


![](http://projectchrono.org/assets/manual/Tutorial_cosim_hydraulics_08.png)


# 备注

<div class="ce-info">
当通信步长很小时，协同仿真可能会很慢。在某些情况下小步长不可避免——如本例所示，系统较为刚性，较大步长会导致变量剧烈振荡的数值不稳定。
</div>

<div class="ce-info">
可以为 _CoSimulate_ 模块配置多个输入和输出。例如，若用 Simulink 模拟一个 6 自由度机器人的六个 PID 控制器，可能需要从 Chrono 接收六个转动量作为输出，并向 Chrono 发送六个控制信号（例如力矩）作为输入。
</div>

<div class="ce-warning">
一次只能使用单个 _CoSimulate_ 模块。如果需要发送/接收更多变量，只需将模块配置为具有更长的向量输入/输出。
</div>

<div class="ce-info">
`CoSimulate` 模块的输入输出信号接受向量。要从单个信号构建向量，请使用 Simulink 的 `Mux` 模块；要将向量拆分为单个信号，请使用 `De-Mux` 模块，如示例所示。
</div>

<div class="ce-info">
如果在将系统划分为两个子系统以进行协同仿真时有多个选择，请遵循经验法则：尽量在连接变量（力、位移等）频率较低的位置进行分割，因为接口中流动的频率越高，所需的通信步长就越小。
</div>

<div class="ce-info">
将 Simulink 积分器从变步长改为定步长可能会弹出关于不同采样率块的警告或错误。可在菜单 Simulation/Configuration parameters... 的 Solver 选项卡中，将
“Tasking mode for periodic sample times” 设置为 `SingleTasking`（默认是 `Auto`）。
</div>

# 完整代码

\include demo_COSIM_hydraulics.cpp
