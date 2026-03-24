用于 Chrono 多体系统（MBS）仿真设置的 YAML 模式 {#YAML_schema_mbs_simulations}
=======================================

一个 Chrono YAML MBS 仿真文件定义了运行 Chrono 仿真所需的参数。它由两个主要的对象组成：

- 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。
  这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- `simulation` 对象，包含仿真方法、求解器和积分器设置，以及可视化选项。

## 仿真规范

Chrono YAML 仿真规范文件中的 `simulation` 对象定义了：
    1. **时间设置**: 仿真运行的时间长度和分辨率
    2. **接触设置**: 如何处理碰撞和接触
    3. **求解器设置**: 如何求解运动方程
    4. **可视化设置**: 如何显示仿真

<div class="ce-info">
可以使用任意大小写为仿真描述 YAML 文件中的各种对象类型提供枚举值。
例如，一个 "Euler implicit" 积分器可以使用 `euler_implicit`、`EULER_IMPLICIT`、`Euler_implicit`、`EUler_imPLICIt` 等任意形式指定。
</div>

### 必需参数

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `time_step` | 积分时间步长（秒） | double | -- | 是 | -- |
| `contact_method` | 碰撞检测和响应的接触方法 | string | `SMC`,`NSC` | 是 | -- |

### 可选参数

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `enforce_realtime` | 是否强制实时仿真 | boolean | -- | 否 | false |
| `end_time` | 仿真总时间（秒） | double | -- | 否 | -1 表示无限仿真 |
| `gravity` | 重力加速度向量 [x, y, z] | array[3] | -- | 否 | [0, 0, -9.8] |

### 积分器、求解器和可视化设置

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `integrator` | 积分器类型和参数 | object | `EULER_IMPLICIT_LINEARIZED`,<br>`EULER_IMPLICIT_PROJECTED`,<br>`EULER_IMPLICIT`,<br>`HHT` | 否 | `EULER_IMPLICIT_LINEARIZED`  |
| `solver` | (DVI 或线性) 求解器类型和参数 | object |  `BARZILAI_BORWEIN`,<br>`PSOR`,<br>`APGD`,<br>`MINRES`,<br>`GMRES`,<br>`BICGSTAB`,<br>`PARDISO`,<br>`MUMPS`,<br>`SPARSE_LU`,<br>`SPARSE_QR` | 否 | `BARZILAI_BORWEIN` |
| `visualization` | 运行时可视化设置 | object | -- | 否 | `false` |

### 积分器类型和参数

每个积分器可以根据积分器类型支持以下设置：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|----------|-------------|------|------------------|----------|---------|
| `rel_tolerance` | 相对容差 (HHT 和隐式欧拉) | double | -- | 否 | 1e-4 |
| `abs_tolerance_states` | 状态变量的绝对容差 (HHT 和隐式欧拉) | double | -- | 否 | 1e-4 |
| `abs_tolerance_multipliers` | 拉格朗日乘子的绝对容差 (HHT 和隐式欧拉) | double | -- | 否 | 1e2 |
| `max_iterations` | 隐式积分器的非线性迭代最大次数 | integer | -- | 否 | 50 |
| `use_stepsize_control` | 是否使用内部步长控制 (HHT) | boolean | -- | 否 | false |
| `use_modified_newton` | 是否使用修改的牛顿迭代 (HHT) | boolean | -- | 否 | false |

### 求解器类型和参数

每个求解器可以根据求解器类型支持不同的配置参数：

#### 迭代 DVI 求解器 (BARZILAI_BORWEIN, APGD, PSOR)

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `max_iterations`| 最大迭代次数 | integer | -- | 否 | 100 |
| `overrelaxation_factor` | 用于提高收敛性的超松弛因子 | double | -- | 否 | 1.0 |
| `sharpness_factor` | 用于求解器响应调节的锐度因子 | double | -- | 否 | 1.0 |

#### 迭代 Krylov 线性求解器 (BICGSTAB, MINRES, GMRES)

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|----------|-------------|------|------------------|----------|---------|
| `max_iterations` | 最大迭代次数 | integer | -- | 否 | 100 |
| `tolerance` | 收敛的残差容差 | double | -- | 否 | 0.0 |
| `enable_diagonal_preconditioner` | 是否启用对角预处理器以加速收敛 | boolean | -- | 否 | false |

#### 直接稀疏线性求解器 (SPARSE_LU, SPARSE_QR, PARDISO_MKL, MUMPS)

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `lock_sparsity_pattern`| 保持矩阵稀疏模式不变 | boolean | -- | 否 | false |
| `use_sparsity_pattern_learner` | 在预处理阶段评估矩阵稀疏模式（仅适用于 `SPARSE_LU` 和 `SPARSE_QR`） | boolean | -- | 否 | true |

### 运行时可视化参数

如果存在键为 `visualization` 的条目，将启用运行时可视化。
可以设置以下可选参数：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 可视化类型 | string | `MODEL_FILE`,`PRIMITIVES`,<br>`COLLISION`,`NONE` | 否 | `MODEL_FILE` |
| `render_fps` | 可视化的目标帧率 | integer | -- | 否 | 120 |
| `enable_shadows` | 是否在可视化系统中启用阴影 | boolean | -- | 否 | true |
| `camera` | 相机的垂直方向、位置和观察点 | object | -- | 否 | 见下方 `camera` 对象 |

#### 相机设置

`camera` 对象指定了运行时可视化的初始视图配置。所有字段都是可选的；如果省略，将使用默认值。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|----------|-------------|------|------------------|----------|---------|
| `vertical` | 相机方向的垂直轴 | string | `Y`,`Z` | 否 | `Z` |
| `location` | 初始相机位置 [x, y, z] | array[3] | -- | 否 | [0, -1, 0] |
| `target` | 初始相机观察点 [x, y, z] | array[3] | -- | 否 | [0, 0, 0] |

## 示例

下面是一个仿真配置示例：

```yaml
# 基本 MBS 仿真

contact_method: SMC

time_step: 1e-4
end_time: 100
enforce_realtime: true

integrator:
    type: Euler_implicit_linearized

solver:
    type: Barzilai_Borwein
    max_iterations: 100
    overrelaxation_factor: 1.0
    sharpness_factor: 1.0

visualization:
    render_fps: 120
    enable_shadows: true
    camera:
        vertical: Z
        location: [9, -4, 1]
        target: [2, 0, 0]
```

## YAML 模式

YAML 模型规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/mbs_simulation.schema.yaml`` 文件：

\include data/yaml/schema/mbs_simulation.schema.yaml
