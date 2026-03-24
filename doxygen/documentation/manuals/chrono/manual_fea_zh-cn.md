
有限元      {#manual_fea}
===============

本部分讨论 Chrono 的 [FEA 模块](group__chrono__fea.html)。

有限元可以用于在 Chrono 中建模柔性部件。

支持不同类型的有限元：

- **实体体积**（例如四面体）：可用于建模具有任意几何形状的部件，例如金属形状、塑料模具、生物力学组织如肌肉等。

- **表面体积** 即壳体：可用于建模薄部件，如轮胎、气囊等。

- **梁** 单元：可用于建模电缆、导线、细轴、风力涡轮机叶片等。

大位移支持大多数有限元。这允许，例如，模拟橡胶结构在大挠度下的行为、飞机在空间中进行复杂机动、风力涡轮机叶片的大旋转以及其他几何非线性。当然，线性化的小位移分析也作为一个子情况得到支持。

详细的节点和单元文档可以在以下页面找到：

* @subpage manual_fea_nodes
* @subpage manual_fea_elements

# 有限元数据结构

有限元模型的数据结构组织如下：

![](http://www.projectchrono.org/assets/manual/fea_data_1a.png) ![](http://www.projectchrono.org/assets/manual/fea_data_1b.png)

任何 Chrono \ref chrono::ChSystem "ChSystem" 都包含在物体、连接、载荷和其他物理项的列表中，还包含一个 @ref chrono::fea::ChMesh "fea::ChMesh" 对象的列表。这些对象本身是有限元（派生自 @ref chrono::fea::ChElementBase "ChElementBase"）和节点（派生自 @ref chrono::fea::ChNodeFEAbase "ChNodeFEAbase"）的容器。

单个 @ref chrono::fea::ChMesh "fea::ChMesh" 实际上可以包含多个单元。

提供了一整套 [载荷](@ref loads) 和 [连接](@ref links) 用于施加载荷和连接节点（无论是连接到其他节点还是连接到 \ref chrono::ChBody "ChBody"）。

# 如何创建有限元模型

在下面的示例中，我们展示了一个包含两个单元、一个约束和一个载荷的情况的数据结构：

![](http://www.projectchrono.org/assets/manual/fea_data_2a.png) ![](http://www.projectchrono.org/assets/manual/fea_data_2b.png)

一般来说：

- **网格** 是节点和单元的容器
  - 使用 \ref chrono::ChSystem::Add() "ChSystem::Add()" 将 ChMesh 添加到系统中
  - 单个系统中允许存在多个网格

- **节点** 拥有自由度（xyz，旋转等）。
  - 使用 \ref chrono::fea::ChMesh::AddNode() "ChMesh::AddNode()" 将节点添加到网格中
  - 查看 [节点列表](@ref manual_fea_nodes)。

- **单元** 连接 N 个节点。
  - 使用 \ref chrono::fea::ChMesh::AddElement() "ChMesh::AddElement()" 将单元添加到网格中
  - 使用 `SetNodes()` 初始化单元，指定连接的节点
  - 使用 `SetMaterial()` 为单元设置材料属性
  - 查看 [单元列表](@ref manual_fea_elements)

下面的示例说明了这一点。

## 1) 创建一个 ChMesh 

- 创建网格（使用 `chrono_types::make_shared`，这样它将由共享指针管理，您无需担心删除它）
- 将网格添加到物理系统中：

~~~{.cpp}
    // 物理系统：它包含所有物理对象。
    ChSystem my_system;

    // 创建一个网格，它是元素组及其引用节点的容器。
    auto my_mesh = chrono_types::make_shared<ChMesh>();

    // 记得将网格添加到系统中！
    my_system.Add(my_mesh);
~~~

## 2) 创建一些节点

- 创建节点
- 注意：通常节点位置在其构造函数中作为参数提供
- 将节点添加到网格中

~~~{.cpp}
    // 创建一些具有 x,y,z 自由度的点状节点
    // 在创建它们时，还设置 X0 未变形位置。
    auto mnode1 = chrono_types::make_shared<ChNodeFEAxyz>(ChVector3d(0, 0, 0));
    auto mnode2 = chrono_types::make_shared<ChNodeFEAxyz>(ChVector3d(0, 0, 1));
    auto mnode3 = chrono_types::make_shared<ChNodeFEAxyz>(ChVector3d(0, 1, 0));
    auto mnode4 = chrono_types::make_shared<ChNodeFEAxyz>(ChVector3d(1, 0, 0));
    
    // 记得将节点和单元添加到网格中！
    my_mesh->AddNode(mnode1);
    my_mesh->AddNode(mnode2);
    my_mesh->AddNode(mnode3);
    my_mesh->AddNode(mnode4);
~~~

- 设置节点属性（如果需要）：
  - 例如，大多数节点类提供了一种方法，通过使用 `SetForce()` 来施加局部力（如果节点具有旋转自由度，还可以施加力矩），这是使用 ChLoad 类的更简单的替代方法，如果力是恒定的。有关更多信息，请参见 [载荷](@ref loads)。
  - 可以使用 `SetMass()` 为节点附加可选的局部质点质量；否则，FEA 节点的默认质量为零，因为质量主要由有限元单元添加。

~~~{.cpp}
    // 例如，为节点设置一些非零质量
    mnode1->SetMass(0.01); 
    mnode2->SetMass(0.01); 

    // 例如，为节点设置一个施加的力：
    mnode2->SetForce(ChVector3d(0, 5, 0));
~~~

## 3) 创建材料

- 创建材料
- 注意，并非所有单元都需要材料，例如 ChElementSpring 没有材料。
- 单个材料可以在多个单元之间共享。

~~~{.cpp}
	// 创建一个材料，它将分配给每个单元
    auto mmaterial = chrono_types::make_shared<ChContinuumElastic>();

    // …并设置其参数
    mmaterial->SetYoungModulus(0.01e9);  // 橡胶 0.01e9，钢 200e9
    mmaterial->SetPoissonRatio(0.3);
~~~

## 4) 创建有限元单元

- 创建单元
- 将单元添加到网格中
- 将节点（之前创建的）分配给单元
- 将材料分配给单元

~~~{.cpp}
	// 创建四面体单元
    auto melement1 = chrono_types::make_shared<ChElementTetraCorot_4>();
    
    // 记得将单元添加到网格中！
    my_mesh->AddElement(melement1);

    // 分配节点
    melement1->SetNodes(mnode1, mnode2, mnode3, mnode4);

    // 分配材料
    melement1->SetMaterial(mmaterial);
~~~

# 另请参阅

- [白皮书页面](http://projectchrono.org/whitepapers/)
  关于 Chrono 中有限元实现的理论和附加信息

- [教程](@ref tutorial_table_of_content_chrono_fea)
  演示和示例
  
- [API 文档](group__chrono__fea.html)
  本模块的 C++ 类和函数。
