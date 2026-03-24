Chrono SYNCHRONO 模块教程 {#tutorial_table_of_content_chrono_synchrono}
===============================

Chrono 分发版包含多个用于建模和仿真自主车辆和机器人的演示，使用 [SYNCHRONO 模块](@ref manual_synchrono)。

SynChrono 支持在单一时空连贯的 Chrono 环境中，对多辆车辆或机器人的分布式仿真进行同步。SynChrono 还提供了开箱即用的功能，包括 Chrono::Vehicle 模型的封装、Chrono::Irrlicht 和 Chrono::Sensor 的可视化、智能交叉口系统的建模，以及可变形（SCM）地形的同步。

SynChrono 演示：

* 基本 SynChrono 演示 (demo_vehicles/)
    * demo_SYN_wheeled - 演示可驱动的轮式车辆，在平坦、刚性地形上，使用 MPI 进行同步。
    * demo_SYN_tracked - 演示可驱动的履带车辆，在平坦、刚性地形上，使用 MPI 进行同步。

* 面向功能的 SynChrono 演示
    * demo_SYN_scm(_tracked) - 演示对可同步变形（SCM）地形的支持
    * demo_highway - 演示简单的车道变换模型和高速公路网格

* FastDDS SynChrono 演示
    * demo_SYN_DDS_wheeled - 演示可驱动的轮式车辆，在平坦、刚性地形上，使用 DDS 进行同步。
    * demo_SYN_DDS_tracked - 演示可驱动的履带车辆，在平坦、刚性地形上，使用 DDS 进行同步。
    * demo_SYN_DDS_distributed - 演示可驱动的轮式车辆。设置允许 DDS 节点通过 IP 分布在多个物理计算节点上。

所有 SynChrono 演示都使用命令行参数在运行时控制各种选项，而无需重新编译。您可以通过运行 `./path/to/demo_SYN_somedemo --help` 查看特定演示的选项。要运行基于 MPI 的演示并使用 `n` 个节点，请运行以下命令：

````
mpirun -n <num nodes> path/to/demo_SYN_MPI_demo
````

对于更复杂的 MPI 设置，请查阅您所使用的 MPI 发行版的文档。

虽然 `mpirun` 命令可以处理每个节点的初始化，但要运行基于 DDS 的演示程序，你需要在独立的进程中手动启动每个节点，这可以通过脚本实现，或者简单地打开多个终端窗口。要启动一个包含 n 个节点的基于 DDS 的演示程序，请运行以下命令：

````
./path/to/demo_SYN_DDS_demo -n <num nodes> -d <this node num>
````

其中 `-d` 参数的值对于每个启动的 DDS 节点都是不同的数字。
