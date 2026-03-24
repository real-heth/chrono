Chrono FSI 模块教程 {#tutorial_table_of_content_chrono_fsi}
===========================

Chrono 分发版包含多个用于模拟流体-固体相互作用问题的演示，使用 [FSI 模块](group__fsi.html)。

- 可压缩性 (demo_FSI_Compressibility.cpp)：此演示展示了如何使用静态水箱模型测量 SPH 求解器的可压缩性（密度误差）。

- 冲击破坏 (demo_FSI_DamBreak.cpp)：经典的冲击破坏问题，使用 SPH 方法建模。

- 基于ANCF梁的缆索模型 (demo_FSI_Flexible_Cable.cpp)：此演示展示了流体与通过 ANCF 梁单元建模的柔性板的相互作用。流体模型类似于冲击破坏问题。

- 基于ANCF壳体的板 (demo_FSI_Flexible_Plate.cpp)：此演示展示了流体与通过 ANCF 壳单元建模的柔性板的相互作用。流体模型类似于冲击破坏问题。

- 静止角 (demo_FSI_AngleRepose.cpp)：此演示展示了使用 WCSPH 方法将颗粒材料建模为连续体的静止角测试。

- 球体撞击成坑模拟（demo_FSI_Cratering.cpp）：本演示展示了球体坠落并与颗粒材料床相互作用的过程。该演示可用于与现有[文献](https://www.sciencedirect.com/science/article/pii/S0045782521003534?ref=pdf_download&fr=RR-2&rr=8c4472d7d99222ff)中的实验或解析结果进行验证对比。

- 波浪水槽 (demo_FSI_WaveTank.cpp)：此演示展示了使用 FSI 模块在波浪水槽中生成波浪。

一些刚体系统的演示，如漫游车、车辆等，也可用：

- VIPER在GRC1地形床环境中的模拟 (demo_FSI_Viper_SPH.cpp)：此演示展示了 VIPER 漫游车与使用 FSI 模块建模的 GRC1 地形床的相互作用。

- 基于颗粒材料地形的轮式车辆 (demo_VEH_CRMTerrain_WheeledVehicle.cpp)：此演示展示了轮式车辆与使用 FSI 模块建模的地形的相互作用。
