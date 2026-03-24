用于 Chrono::FSI 问题定义的 YAML 模式 {#YAML_schema_fsi_problems}
========================================

Chrono YAML FSI 问题规范文件定义了运行 Chrono::FSI 协同仿真所需的多体和流体问题以及协同仿真参数。
它由以下对象组成：

- [必需] 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- [必需] `model` 对象，定义多体和流体模型及求解器的 YAML 规范文件。
- [必需] `simulation` 对象，定义协同仿真元步长和仿真持续时间。
- [可选] `visualization` 对象，启用运行时可视化并定义渲染频率。
- [可选] `output` 对象，启用仿真输出并定义输出频率。

## 模型规范

FSI 问题将 Chrono MBS 模型和仿真与流体求解器耦合。可以使用任何实现了 Chrono::FSI API 的流体求解器。

多体和流体模型及仿真是通过引用相应的 YAML 规范文件来指定的。这些文件名必须包括文件的路径，相对于此 Chrono::FSI YAML 规范的位置。

## 仿真规范

## 可视化规范

## 输出规范

## YAML 模式

YAML FSI 问题规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/fsi.schema.yaml`` 文件：

\include data/yaml/schema/fsi.schema.yaml
