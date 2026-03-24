
FEA 节点  {#manual_fea_nodes}
=======================

\tableofcontents

不同类型的节点可以在 [FEA 模块](@ref manual_fea) 中使用。
在本页中，您可以找到它们属性的描述。

- 节点是具有自由度（xyz，旋转等）的对象。
- 存在不同类型的节点，一些单元需要特定类型的节点。
- 节点通过 std::shared_ptr 共享指针进行管理：您无需担心删除它们。
- 使用 ChMesh::AddNode() 将节点添加到网格中。

# ChNodeFEAxyz  {#manual_ChNodeFEAxyz}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyz.png)

- 3 个坐标（p，即 3D 空间中的 x y z 平移）
- 例如，用于实体单元：
  - ChElementTetraCorot_4
  - ChElementTetraCorot_10
  - ChElementHexaCorot_8
  - ChElementHexaCorot_20 等

# ChNodeFEAxyzrot  {#manual_ChNodeFEAxyzrot}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyzrot.png)

- 6个坐标（平移 p 和三维旋转）
- 注意：旋转由四元数 q 表示
- 例如，用于这些单元：
  - ChElementBeamEuler
  - ChElementShellReissner

# ChNodeFEAxyzD  {#manual_ChNodeFEAxyzD}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyzD.png)

- 6 个坐标（平移 p 和 Dx Dy Dz 方向）
- 用于定义简单的电缆类型梁，其中扭转信息不重要
- 例如，用于这些单元：
  - ChElementCableANCF
  - ChElementShellANCF_3423

 
# ChNodeFEAxyzDD {#manual_ChNodeFEAxyzDD}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyzDD.png)

- 9 个坐标（x y z 平移和两个方向）
- 例如，用于这些单元：
  - ChElementBeamANCF_3333
  - ChElementShellANCF_3833

# ChNodeFEAxyzDDD {#manual_ChNodeFEAxyzDDD}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyzDDD.png)

- 12 个坐标（x y z 平移和三个方向）
- 例如，用于这些单元：
  - ChElementBeamANCF_3243
  - ChElementShellANCF_3443
  - ChElementHexaANCF_3843

# ChNodeFEAxyzP   {#manual_ChNodeFEAxyzP}

![](http://www.projectchrono.org/assets/manual/fea_ChNodeFEAxyzP.png)

- 1 个坐标（一个标量 P，在 3D 空间中）
- 用于热分析和静电分析
- 例如，用于这些单元：
  - ChElementTetraCorot_4_P

# ChNodeFEAcurv   {#manual_ChNodeFEAcurv}

- 9 个坐标（位置向量的 3 个二阶偏导数，表示曲率）
  - 位置关于 x 的二阶偏导数
  - 位置关于 y 的二阶偏导数
  - 位置关于 z 的二阶偏导数
- 例如，用于这些单元：
  - ChElementHexaANCF_3813_9

# 理论

关于在 Chrono 中实现有限元的更多信息，可参阅[白皮书页面](http://projectchrono.org/whitepapers/)。

# 示例

请参阅 [教程](@ref tutorial_table_of_content_chrono_fea) 页面中的演示和示例。
