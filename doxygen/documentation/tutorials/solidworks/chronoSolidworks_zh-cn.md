Chrono::SolidWorks&copy;教程 {#tutorial_table_of_content_chrono_solidworks}
==========================

Chrono::SolidWorks 教程适用于已安装 [Chrono::Solidworks](@ref manual_chrono_solidworks) SolidWorks 插件的用户。

其他示例可以直接在 Chrono::SolidWorks 仓库的 [examples](https://github.com/projectchrono/chrono-solidworks/tree/master/to_put_in_app_dir/examples) 中找到。

<br>
-   @subpage tutorial_chrono_solidworks_demo_engine

    学习 Chrono::SolidWorks 插件的基础知识：

    - 使用 SolidWorks 建模 3D 装配体，
    - 将其导出为包含 Chrono 系统描述的 .py 文件。
    - 运行导出系统的 Python 仿真
    - 使用 POVray 渲染仿真

<br>
-   @subpage tutorial_chrono_solidworks_demo_engine_advanced

    关于 Chrono::SolidWorks 插件的高级使用技巧，以及一些 Python 使用窍门：

    - 通过创建自定义约束，修改导出的场景
    - 分配 POVray 材料
    - 创建自定义 POVray 对象
    - 将相机附加到移动部件上

<br>
-   @subpage tutorial_chrono_solidworks_demo_shapes
 
    学习如何在使用 Chrono::SolidWorks 插件时定义碰撞形状。

    - 在 SolidWorks 中为零件分配碰撞形状
    - 使用 Python 创建并分配表面材料
    - 自定义高级 POVray 颜料和纹理
    - 移动地面以模拟地震

<br>
-   @subpage tutorial_chrono_solidworks_demo_spider_robot

    将爬行机器人的 SolidWorks 模型导入到 PyChrono 程序中，并进行仿真。

    - 使用 Chrono::SolidWorks 插件导出机械系统
    - 在 PyChrono 中加载系统
    - 添加在 CAD 中未建模的执行器和其他项目
    - 在 Irrlicht 3D 视图中显示仿真

## 使用预导出模型的教程

这些教程附带预导出的模型，允许用户在不立即安装插件的情况下测试导入功能。
	
- [demo_PARSER_Python_SolidWorks.py](https://github.com/projectchrono/chrono/blob/main/src/demos/python/parsers/demo_PARSER_Python_SolidWorks.py)

    - 使用 PyChrono 进行仿真
    - 使用 Irrlicht 或 POVRAy 渲染

<br>

- [demo_PARSER_Python_SolidWorks.cpp](https://github.com/projectchrono/chrono/blob/main/src/demos/parsers/demo_PARSER_Python_SolidWorks.cpp)

    - 使用 Chrono (C++) 通过加载 Python 导出的模型进行仿真（需要 PARSERS 模块）
