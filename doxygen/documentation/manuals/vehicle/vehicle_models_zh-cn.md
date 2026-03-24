车辆模型 {#vehicle_models}
================================

\tableofcontents

## 轮式车辆模型 {#vehicle_models_wheeled}

### HMMWV {#vehicle_models_hmmwv}

HMMWV 是“高机动性多用途轮式车辆”系列的缩写。这个 Chrono 案例展示的是 M966 运兵车型。就像真车一样，它的前后轴都采用了双叉臂式悬架 ，并且具备全轮驱动能力。它搭载了一套带有液力变矩器 的三速自动变速箱，以及一个高度拟真的发动机子系统。转向系统采用的是循环球式转向 （Pitman-arm steering）。此外，该模型可以适配 Chrono 提供的各种轮胎类型。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/HMMWV.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/HMMWV_suspension.png" width="600" />

### FEDA {#vehicle_models_feda}

FED ALPHA 是由工程公司 Ricardo 与美国军方合作开发的概念车辆。

Chrono::Vehicle FEDA 是一款四轮驱动车型，前后悬架均为双叉臂式，配有防倾杆和 Pitman-arm 转向机构。目前，仅实现了 Pacejka 2002 和刚性轮胎模型。

### Sedan {#vehicle_models_sedan}

Sedan 示例展示了一款通用的平均乘用车。它在前轴采用双叉臂悬架，后轴采用多连杆悬架。转向系统为齿轮齿条式。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/Sedan.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/Sedan_suspension.png" width="600" />

### Citybus {#vehicle_models_citybus}

顾名思义，Citybus 是一种典型的城市公交车。像所有重型车辆一样，它使用叶片弹簧实心车轴。Chrono 的叶片弹簧车轴基于功能性方法，因此看不到叶片。前轮由旋转臂转向，在这种组合中也称为趾杆转向。该模型还展示了双轮的使用。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/CityBus.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/CityBus_suspension.png" width="600" />

### FMTV {#vehicle_models_fmtv}

中型战术车辆系列（FMTV）是由 Oshkosh 公司制造的一系列卡车。

Chrono 车辆模型库提供了这类车辆的两种变体模型：

- LMTV（轻型中型战术车辆），2.5 吨，4x4 卡车
- MTV（中型战术车辆），5 吨，6x4 卡车

两种车辆模型都使用叶片弹簧后轴和带趾杆可转向前轴的叶片弹簧，并包括驾驶室与货舱之间扭转柔度的模型。MTV 模型具有平衡梁后悬架。

### MAN {#vehicle_models_man}

MAN（Maschinenfabrik Augsburg Nürnberg）Kat 1 卡车系列专为战术越野使用而设计。所有系列成员都配备了由连杆引导的螺旋弹簧实心车轴系统。这种设计允许非常高的车轮行程。车辆框架为箱形，因此模型可以使用刚性底盘方法，因为在真实车辆中几乎没有车架扭转。所有转向车轴都具有摇臂/旋转臂机构。所有车轮都可以驱动。

最初为德国联邦国防军设计，如今可以在世界上多个军队中找到，例如在美军中作为 M1001 牵引车或 M1002 救援车。

5 吨（载重能力）卡车是该系列中最小的成员。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_5t.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_5t_suspension.png" width="600" />

7 吨卡车是该系列中配置最为多样的车型，可用于携带特殊设备或作为翻斗车。在 Chrono 中，它仅具有一个货斗。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_7t.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_7t_suspension.png" width="600" />

10 吨卡车是该系列中最早投入使用的车型，最早在 70 年代末投入使用。大多数用于运输，有些配备了起重机。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_10t.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/MAN_10t_suspension.png" width="600" />

### UAZ {#vehicle_models_uaz}

UAZ 是乌里扬诺夫斯克汽车厂（Ulyanovski Avtomobilny Zavod）的缩写。UAZ 452 巴士/面包车/卡车自 1965 年以来在俄罗斯广受欢迎。它具有全轮驱动和两个叶片弹簧车轴。前轴采用趾杆转向机构。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/UAZBUS.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/UAZBUS_suspension.png" width="600" />

UAZ 469 类似吉普车的车辆自 1965 年以来在苏联军队中使用。它与 UAZ 452 共享许多组件（车轴、发动机）。转向系统也是趾杆/旋转臂类型，但配置略有不同。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/UAZ469.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/UAZ469_suspension.png" width="600" />

### Gator {#vehicle_models_gator}

Gator 是一款 John Deere 电动多功能车辆模型，配备了用于自动驾驶的仪器。Gator 模型在前部使用单叉臂悬架，后部使用刚性车轴。它具有齿轮齿条转向机构，仅在后轮上配备制动器。电动机通过差速器连接到后轮。

### KRAZ {#vehicle_models_kraz}

该模型基于乌克兰 Kraz 64431，是一款半挂卡车。牵引车具有趾杆叶片弹簧前悬架，通过旋转臂机构转向，后悬架为两个叶片弹簧。牵引车为 6x4 配置，两个后轴驱动。挂车通过铰链连接到牵引车，具有三个全为叶片弹簧类型的车轴。

### RC-car {#vehicle_models_rccar}

这是一个小型遥控四轮驱动车辆的模型。

### Generic wheeld vehicle {#vehicle_models_generic}

通用轮式车辆模型是用于测试各种模板和设置的沙箱。它不代表任何特定车辆，并且为该模型提供的所有具体子系统不一定彼此一致。

## Tracked vehicle models {#vehicle_models_tracked}

### M113 {#vehicle_models_m113}

M113 是一种轻型坦克，具有铝合金车体和 Christie 型行走装置。第一辆 M113 于 1960 年服役。它被世界上许多军队使用，并且从基本车辆派生出了许多配置。Chrono M113 模型显示了一辆部队运输车（2+11 名乘员）。

行走装置由十个路轮、两个驱动轮和两个惰轮组成。该模型可以配置为单销履带或双销履带。第三种选择——橡胶带履带——正在开发中。履带张紧可以通过惰轮的特殊张紧悬架来设置。路轮通过转向/扭杆系统悬挂。传动系统建模为三速自动变速箱与液力变矩器结合的内燃机。

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/M113.png" width="600" />

<img src="http://www.projectchrono.org/assets/manual/vehicle/models/M113_suspension.png" width="600" />

### Marder {#vehicle_models_marder}

Marder（德语中的“貂”）是一种履带式步兵战车，自 1969 年以来被德国联邦国防军使用。它的行走装置包括 12 个路轮、一个驱动轮、一个惰轮和 3 个支撑滚轮。每侧的前两个和后两个路轮由伸缩减震器减震。它由一台 444 kW 柴油发动机驱动，配备带锁止功能的液力变矩器和四速自动变速箱。它最多可搭载九名士兵（指挥官、炮手、驾驶员和六名步兵）。

我们的模型仅基于公开的在线数据和文献资料。尽管原始车辆采用双销履带，但当前的 Chrono 模型仅实现了单销履带。
