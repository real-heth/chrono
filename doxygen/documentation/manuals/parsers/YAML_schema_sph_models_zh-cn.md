用于 Chrono::SPH 模型定义的 YAML 模式 {#YAML_schema_sph_models}
=======================================

一个 Chrono YAML SPH 模型文件定义了一个用于 Chrono::SPH 的流体系统，并包含两个主要对象：

- 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。
  这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- `model` 对象，列出了 Chrono 模型中的所有物理项。

## 模型规范

## YAML 模式

YAML 模型规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/sph_model.schema.yaml`` 文件：

\include data/yaml/schema/sph_model.schema.yaml
