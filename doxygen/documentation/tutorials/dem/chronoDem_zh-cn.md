Chrono DEM 模块教程 {#tutorial_table_of_content_chrono_dem}
===============================

Chrono 发行版包含若干使用 [DEM 模块](group__dem__module.html) 的颗粒动力学演示。

Chrono::Dem 通过基于罚函数的离散元方法（即 SMC）提供对 GPU 加速颗粒动力学的支持。

颗粒动力学演示：

- `demo_DEM_ballCosim`

    一个简单的协同仿真示例：一个由三角网格表示的大球与颗粒材料相互作用。球体的动力学由 `ChSystem` 计算，接触力由 `Chrono::DEM` 系统生成。

- `demo_DEM_fixedTerrain`

    一个地形初始化工具，在地形的表面网格上生成固定颗粒，并可从上述加载额外的颗粒。

- `demo_DEM_movingBoundary`

    一个已沉降的颗粒容器被一个移动的边界平面推向一侧。

- `demo_DEM_mixer`

    一个带旋转叶片的圆柱容器，用于搅拌颗粒材料。

- `demo_DEM_repose`

    颗粒材料通过料斗流出并形成稳定堆，展示了安息角/静止角（angle of repose）。
