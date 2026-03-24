用于 Chrono::Vehicle 车辆模型定义的 YAML 模式 {#YAML_schema_vehicle_models}
========================================

一个 Chrono::Vehicle YAML FSI 问题规范文件定义了车辆模型，并由两个主要对象组成：

- [必需] 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。
  这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- [必需] `model` 对象，定义车辆子系统的 JSON 规范文件。

## 模型规范

## YAML 模式

YAML 车辆模型规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/vehicle_model.schema.yaml`` 文件：

\include data/yaml/schema/vehicle_model.schema.yaml
