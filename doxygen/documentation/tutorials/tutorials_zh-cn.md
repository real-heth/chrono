教程 {#tutorial_root}
==========================

<div class="ce-info">
**包含固定大小可向量化 Eigen 对象成员的类的动态对象**<br>
<ul>

<li>许多 Chrono 类现在具有固定大小可向量化的 Eigen 类型成员。这些类重载了它们的 `operator new` 以生成 16 字节对齐的指针（使用 Eigen 提供的宏）。</li>

<li>这处理了必须动态创建此类对象的情况；有关更多详细信息，请参阅 [Eigen 文档](https://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html)。</li>

<li>如果需要创建此类的 STL 容器，应使用始终分配对齐内存的自定义分配器（例如 Eigen 提供的 `Eigen:aligned_allocator`）；有关更多详细信息，请参阅 [Eigen 文档](https://eigen.tuxfamily.org/dox/group__TopicStlContainers.html)。</li>

<li>最后，这种对齐内存分配的要求对创建共享指针有影响。实际上，`std::make_shared` 使用 `placement new` 而不是 `operator new`。为了解决这个问题并尽可能保持封装性，Chrono 提供了 `make_shared` 的自定义替代函数，可在 `chrono_types` 命名空间中使用。这些函数会自动推断是否可以安全地回退到 `std::make_shared`，否则会使用确保使用对齐内存的替代机制创建共享指针。<br>
因此，用户代码应**始终**使用 `chrono_types::make_shared`，例如

~~~{.cpp}
auto my_body = chrono_types::make_shared<ChBody>();
~~~

</li>
</ul>
</div>

## Chrono 模块

-   @subpage tutorial_table_of_content_chrono

    Chrono 库核心功能和能力的示例。

-   @subpage tutorial_table_of_content_chrono_irrlicht

    使用 Irrlicht 模块进行实时可视化的示例。

-   @subpage tutorial_table_of_content_chrono_mbs

    Chrono 中多体系统动力学的示例。

-   @subpage tutorial_table_of_content_chrono_fea

    Chrono 中有限元分析的示例。

-   @subpage tutorial_table_of_content_chrono_vehicle

    Chrono 中地面车辆建模和仿真的示例。

-   @subpage tutorial_table_of_content_chrono_fsi

    使用 FSI 模块进行流固耦合问题的示例。

-   @subpage tutorial_table_of_content_chrono_postprocess

    生成后处理数据的示例（例如 POVray 或 GNUplot 输出）。

-   @subpage tutorial_table_of_content_chrono_multicore

    使用多核模块的示例。

-   @subpage tutorial_table_of_content_chrono_dem

    使用 DEM 模块进行颗粒动力学问题的示例。

-   @subpage tutorial_table_of_content_chrono_python

    使用 Python 程序的示例。

-   @subpage tutorial_table_of_content_chrono_matlab

    使用 Matlab 进行交互操作的示例。

-   @subpage tutorial_table_of_content_chrono_cosimulation

    使用 Simulink 进行联合仿真的示例。

-   @subpage tutorial_table_of_content_chrono_cascade

    加载 CAD 模型的示例。

-   @subpage tutorial_table_of_content_chrono_sensor

    Chrono 中用于机器人和自主车辆的传感器建模和仿真的示例。

-   @subpage tutorial_table_of_content_chrono_synchrono

    Chrono 中自主车辆和机器人的分布式仿真示例。

-   @subpage tutorial_table_of_content_chrono_fmi

    Chrono 中生成（导出）和使用（导入）FMU 的示例。

-   @subpage tutorial_table_of_content_chrono_ros

    Chrono 中集成基于 ROS 的外部自主系统的示例。


## 其他工具


-   @subpage tutorial_table_of_content_pychrono

    学习如何使用 [PyChrono](@ref pychrono_introduction)

-   @subpage tutorial_table_of_content_chrono_solidworks

    学习如何使用 [Chrono::SolidWorks](@ref manual_chrono_solidworks)


## Chrono 培训材料

-   [Tutorial slides](@ref tutorial_slides_300)

    Chrono 3.0.0 版本的教程幻灯片集


## 文档指南

-    @subpage tutorial_table_of_content_documentation

     编写 Chrono 技术文档的指南（针对新模块/功能的开发者）。
