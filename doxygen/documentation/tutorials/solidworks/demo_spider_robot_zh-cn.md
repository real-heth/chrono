在 SolidWorks 中制作一个蜘蛛机器人并进行仿真 {#tutorial_chrono_solidworks_demo_spider_robot}
==========================

本演示涉及六条腿的爬行蜘蛛机器人的仿真，我们使用 18 个执行器控制腿的运动。

![](http://projectchrono.org/assets/manual/Tutorial_spider_robot.jpg)

具体步骤如下：

- 使用 SolidWorks 制作爬行机器人的 3D CAD 模型，
- 使用 Chrono::SolidWorks 插件将其导出为 .py 文件；例如，使用名称 **spider\_robot.py**
- 创建一个 Python 程序，例如，使用名称 **demo_SW\_spider_robot.py**，使用 [PyChrono](@ref pychrono_introduction) 的函数加载并模拟 spider\_robot.py。

CAD 模型和 **demo_SW\_spider_robot.py** 程序随 Chrono SolidWorks 插件安装提供，但也可以直接从 [这里](https://github.com/projectchrono/chrono-solidworks/tree/master/to_put_in_app_dir/examples/spider_robot) 获取

请注意，在 SolidWorks GUI 中显示为 *M-410iB-300 -1/ArmBase\<1\>* 的零件，在 Python 端变为 *M-410iB-300 -1/ArmBase-1*；即 \<N\> 后缀变为 -N。
