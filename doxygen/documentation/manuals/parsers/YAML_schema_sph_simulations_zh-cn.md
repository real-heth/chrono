用于 Chrono::SPH 流体仿真设置的 YAML 模式 {#YAML_schema_sph_simulations}
=======================================

一个 Chrono YAML SPH 仿真文件定义了运行 Chrono::SPH 仿真所需的参数。它由三个主要对象组成：

- 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。
  这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- 流体求解器类型，一个字符串，用于标识支持的 CFD 求解器。
- `simulation` 对象，包含仿真方法、求解器和积分器设置，以及可视化选项。

## 仿真规范

## YAML 模式

YAML 模型规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/sph_simulation.schema.yaml`` 文件：

\include data/yaml/schema/sph_simulation.schema.yaml
