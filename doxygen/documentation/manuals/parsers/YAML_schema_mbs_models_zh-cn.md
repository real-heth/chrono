用于 Chrono 多体系统（MBS）模型定义的 YAML 模式 {#YAML_schema_mbs_models}
=======================================

Chrono YAML MBS 模型文件定义了一个机械系统，并包含两个主要对象：

- 与 YAML 模型规范兼容的 Chrono 版本 (`chrono-version`)。
  这是一个形式为 `M.m`（主版本.次版本）或 `M.m.p`（主版本-次版本-补丁）的字符串，尽管仅验证前两个字段的兼容性。
- `model` 对象，列出 Chrono 模型中的所有物理项。

## 模型规范

Chrono YAML 模型规范文件中的 `model` 对象定义了：
    1. **Bodies**: (必需) 刚体，具有质量和惯性，并可选地具有碰撞和可视化几何体
    2. **Joints**: 连接一对刚体的关节，可以指定为运动学（理想）关节或衬套
    3. **Passive force elements**: 作用在两刚体之间的平移和旋转线性或非线性弹簧-阻尼力元件
    4. **Motors and actuators**: 
        - 平移和旋转电机作用于两刚体之间的位置（位移或角度）、速度（线性或角速度）或力（力或力矩）水平。电机通过控制输入（位置、速度或力）的时间函数来指定。
        - 外部执行器
    5. **Constraints**: 刚体之间的附加约束方程
    6. **External loads**: 施加在刚体上的外部载荷

<div class="ce-info">
可以使用任意大小写为模型描述 YAML 文件中的各种对象类型提供枚举值。
例如，一个 "point-line" 关节可以使用 `point_line`、`POINT_LINE`、`Point_Line`、`POinT_liNE` 等任意形式指定。
</div>

下面的表格列出了 `model` 对象的主要字段：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|-------|-------------|------|----------|---------|---------|
| `name` | 可选的模型名称，用于识别 | string | -- | 否 | 'YAML model' |
| `angle_degrees` | 角度是以度（true）还是弧度（false）表示 | boolean | -- | 否 | true |
| `data_path` | 数据文件位置的配置 | object, see below | -- | 否 | 使用绝对路径 |
| `bodies` | 刚体对象数组 | array[`body`] | -- | 是 | -- |
| `joints` | 关节对象数组 | array[`joint`] | -- | 否 | -- |
| `constraints` | 约束对象数组 | array[`constraint`] | -- | 否 | -- |
| `tsdas` | TSDA（平移弹簧-阻尼器）对象数组 | array[`tsda`] | -- | 否 | -- |
| `rsdas` | RSDA（旋转弹簧-阻尼器）对象数组 | array[`rsda`] | -- | 否 | -- |
| `motors` | 电机对象数组 | array[`motor`] | -- | 否 | -- |
| `body_loads` | 施加在刚体上的外部载荷数组 | array[`body_load`] | -- | 否 | -- |

`data_path` 对象可以包含以下字段（如果指定）：

| 字段 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|-------|-------------|------|----------|---------|---------|
| `type` | 数据路径类型 | string | `RELATIVE` 或 `ABSOLUTE` | 是 | -- |
| `root` | 数据文件位置的根目录 | string | -- | 否 | `.`（当前目录） |

### 刚体

每个刚体表示仿真中的一个物理对象，具有以下属性：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 |
|----------|-------------|------|------------------|----------|---------|
| `name` | 刚体的唯一标识符 | string | -- | 是 | -- |
| `fixed` | 指示刚体是否相对于全局坐标系固定 | boolean | -- | 否 | false |
| `mass` | 质量，单位为 kg | double | -- | 是（如果刚体未固定） | -- |
| `com`->`location` | 刚体参考系相对于质心参考系的原点 | array[3] | -- | 否 | [0, 0, 0] |
| `com`->`orientation` | 刚体参考系相对于质心参考系的方向 | array[3] 或 array[4] | -- | 否 | 单位旋转 |
| `inertia`->`moments` | 相对于质心参考系的惯性矩 [Ixx, Iyy, Izz] | array[3] | -- | 是（如果刚体未固定） | -- |
| `inertia`->`products` | 相对于质心参考系的惯性积 [Ixy, Iyz, Izx] | array[3] | -- | 否 | [0, 0, 0] |
| `location` | 刚体参考系的原点，相对于模型参考系 | array[3] | -- | 是 | -- |
| `orientation` | 刚体参考系相对于模型参考系的方向 | array[3] 或 array[4] | -- | 否 | 单位旋转 |
| `initial_linear_velocity` | 刚体参考系的初始线速度 | array[3] | -- | 否 | [0, 0, 0] |
| `initial_angular_velocity` | 刚体参考系的初始角速度，以局部刚体参考系表示 | array[3] | -- | 否 | [0, 0, 0] |
| `contact` | 接触材料列表 `materials` 和碰撞形状列表 `shapes` | object, 见下文 | -- | 否 | 无接触 |
| `visualization` | 可视化形状列表 `shapes` | object, 见下文 | -- | 否 | 无可视化 |

**注意:** `orientation` 可以指定为欧拉卡丹角 [yaw, pitch, roll] 或四元数 [e0, e1, e2, e3]

#### 刚体接触属性

刚体的碰撞通过接触材料列表 `materials` 和碰撞形状列表 `shapes` 指定。
模型可以有比 `materials` 更多的 `shapes`，用户需要指定哪个 `shape` 与哪个 `material` 关联。
根据接触方法，平滑接触公式 (SMC) 或非平滑接触公式 (NSC)，相同的接触参数，如 `coefficient_of_friction` 和 `coefficient_of_restitution`，可能导致不同的物理效果。使用 SMC 公式时，用户可以指定基于材料的属性，如 `Youngs_modulus` 和 `Poisson_ratio`，或用于建模接触的弹簧-阻尼系数，如 `normal_stiffness` 和 `normal_damping`。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `materials` | 接触材料属性 | array[`material`], 见下文 | -- | 是 | -- |
| `shapes` | 碰撞形状用于接触检测 | array[`shape`], 见下文 | -- | 是 | -- |

##### 接触材料

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `name` | 材料的唯一标识符 | string | -- | 是 | -- |
| `coefficient_of_friction`    | 摩擦系数 | double | -- | 否 | 0.8 |
| `coefficient_of_restitution` | 恢复系数 | double | -- | 否 | 0.01|
| `physical__properties` | (仅 SMC) 基于材料的接触属性，如杨氏模量和泊松比 | object | -- | 否 | 见下文 |
| `coefficients`         | (仅 SMC) 接触弹簧-阻尼系数，如法向刚度和阻尼 | object | -- | 否 | 见下文 |
<br>
`material`->`physical__properties` 的属性:
| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `Youngs_modulus` | 材料的杨氏模量 | double | -- | 是 | 2e7 |
| `Poisson_ratio`  | 材料的泊松比 | double | -- | 是 | 0.3 |
<br>
`material`->`coefficients` 的属性:
| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `normal_stiffness`     | 法向刚度系数     | double | -- | 是 | 2e5 |
| `normal_damping`       | 法向阻尼系数       | double | -- | 是 | 40 |
| `tangential_stiffness` | 切向刚度系数 | double | -- | 是 | 2e5 |
| `tangential_damping`   | 切向阻尼系数   | double | -- | 是 | 20 |

##### 碰撞形状

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 碰撞形状类型 | string | `SPHERE`, `BOX`, <br> `CYLINDER`, `MESH`, <br> `HULL` | 是 | -- |
| `material` | 用于形状的接触材料名称，见上文 | string | -- | 是 | -- |
| `location` | 形状相对于刚体参考系的位置 | array[3] | -- | 是 , 除了 `MESH` | [0, 0, 0] 对于 `MESH` |
| `orientation` | 形状相对于刚体参考系的方向 | array[3] 或 array[4] | -- | 是 , 除了 `MESH` | 单位旋转 对于 `MESH` |
| `radius` | `SPHERE` 和 `CYLINDER` 形状的半径 | double | -- | 是 |-- |
| `dimensions` | `BOX` 形状的尺寸 [长度, 宽度, 高度] | array[3] | -- | 是 | -- |
| `axis` | `CYLINDER` 形状的轴方向 | array[3] | -- | 是 | -- |
| `length` | `CYLINDER` 形状的长度 | double | -- | 是 | -- |
| `filename` | `HULL` 和 `MESH` 形状的文件名 | string | -- | 是 | -- |
| `contact_radius` | `MESH` 形状的接触半径 | double | -- | 否 | 0 |
| `scale` | `MESH` 形状的缩放因子 | double | -- | 否 | 1.0 |

#### 刚体可视化属性

刚体的可视化可以是单个 `model_file` 和/或一个 `shapes` 列表（类型为 `SPHERE`、`BOX`、`CYLINDER` 或 `MESH`）。
如果提供了 `model_file`，它将直接传递给运行时可视化系统。
另一方面，`MESH` 形状假定仅通过 OBJ Wavefront 文件提供，并且还支持平移、旋转和缩放。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `model_file` | 可视化模型文件的路径 | string | -- | 否 | -- |
| `shapes` | 可视化形状列表 | array, 见下文 | -- | 否 | -- |

##### 可视化形状

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 可视化形状类型 | string | `SPHERE`, `BOX`, <br> `CYLINDER`, `MESH` | 是 | -- |
| `location` | 形状相对于刚体参考系的位置 | array[3] | -- | 是 , 除了 `MESH` | [0, 0, 0] 对于 `MESH` |
| `orientation` | 形状相对于刚体参考系的方向 | array[3] 或 array[4] | -- | 是 , 除了 `MESH` | 单位旋转 对于 `MESH` |
| `radius` | `SPHERE` 和 `CYLINDER` 形状的半径 | double | -- | 是 | -- |
| `dimensions` | `BOX` 形状的尺寸 [长度, 宽度, 高度] | array[3] | -- | 是 | -- |
| `axis` | `CYLINDER` 形状的轴方向 | array[3] | -- | 是 | -- |
| `length` | `CYLINDER` 形状的长度 | double | -- | 是 | -- |
| `filename` | `MESH` 形状的文件名 | string | -- | 是 | -- |
| `scale` | `MESH` 形状的缩放因子 | double | -- | 否 | 1.0 |
| `color` | 形状的颜色，RGB 格式 [r, g, b] | array[3] | -- | 否 | [-1, -1, -1] |

### 关节

关节是连接两个刚体并约束它们相对运动的装置。
它们可以通过约束（理想运动学关节）或通过刚性顺应性（衬套）来表示。
当前支持的关节 `type` 有：`LOCK`、`REVOLUTE`、`SPHERICAL`、`PRISMATIC`、`UNIVERSAL`、`POINT_LINE`、`POINT_PLANE`。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 关节类型 | string | `LOCK`,<br> `REVOLUTE`,<br>`SPHERICAL`,<br>`PRISMATIC`,<br>`UNIVERSAL`,<br>`POINT_LINE`,<br>`POINT_PLANE` | 是 | -- |
| `name` | 关节的唯一标识符 | string | -- | 是 | -- |
| `body1` | 要连接的第一个刚体的名称 | string | -- | 是 | -- |
| `body2` | 要连接的第二个刚体的名称 | string | -- | 是 | -- |
| `location` | 关节位置 | array[3] | -- | 是 | -- |
| `axis` | 转动/平移关节的运动轴 | array[3] | -- | 是 | -- |
| `axis1` | 万向节的第一个轴 | array[3] | -- | 是 | -- |
| `axis2` | 万向节的第二个轴 | array[3] | -- | 是 | -- |
| `bushing_data` | 衬套顺应性数据；如果不存在，关节为运动学关节 | object | -- | 否 | 无衬套 |

`bushing_data` 模型沿关节受约束的自由度的顺应性行为（即理想运动学关节的刚性约束的放松）。
请注意，类型为 `PRISMATIC`、`POINT_LINE` 或 `POINT_PLANE` 的关节是禁止的。

对于受约束的自由度，可以指定刚度和阻尼系数。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `stiffness_linear` | 受约束平移自由度的线性刚度系数 | double | -- | 是 | -- |
| `damping_linear` | 受约束平移自由度的线性阻尼系数 | double | -- | 是 | -- |
| `stiffness_rotational` | 受约束旋转自由度的旋转刚度系数 | double | -- | 是 | -- |
| `damping_rotational` | 受约束旋转自由度的旋转阻尼系数 | double | -- | 是 | -- |
| `DOF` | 自由度特定属性 | object | -- | 否 | 全部为 0.0 |

可以选择使用嵌套的 `DOF` 对象对未约束的自由度应用顺应性，例如：

```yaml
bushing_data:
  stiffness_linear: 7e7
  damping_linear: 0.35e5
  stiffness_rotational: 1e5
  damping_rotational: 5e3
  DOF:
    stiffness_linear: 5000
    damping_linear: 50
    stiffness_rotational: 500
    damping_rotational: 25
```

如果 `DOF` 对象不存在，衬套在未约束自由度方向上的线性和旋转刚度及阻尼都设置为 0.0。

### 约束
约束连接两个刚体并约束它们的相对运动。支持的约束 `type` 有：`DISTANCE`、`REVOLUTE-SPHERICAL`、`REVOLUTE-TRANSLATIONAL`。 

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 约束类型 | string | `DISTANCE`,<br>`REVOLUTE-SPHERICAL`,<br>`REVOLUTE-TRANSLATIONAL` | 是 | -- |
| `name` | 约束的唯一标识符 | string | -- | 是 | -- |
| `body1` | 要连接的第一个刚体的名称 | string | -- | 是 | -- |
| `body2` | 要连接的第二个刚体的名称 | string | -- | 是 | -- |
| `point1` | 在全局坐标系中表示的 body1 上的点 | array[3] | -- | 是 | -- |
| `point2` | 在全局坐标系中表示的 body2 上的点 | array[3] | -- | 是 | -- |

### 被动弹簧-阻尼力元件

有两种类型的弹簧-阻尼元件，平移型 (TSDA) 和旋转型 (RSDA)。

#### 平移弹簧-阻尼器

TSDA 元件对连接的刚体施加力。
在 YAML 规范文件中，它们列在一个数组 `tsdas` 中，包含具有以下属性的对象：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `name` | 力元件的唯一标识符 | string | -- | 是 | -- |
| `body1` | 要连接的第一个刚体的名称 | string | -- | 是 | -- |
| `body2` | 要连接的第二个刚体的名称 | string | -- | 是 | -- |
| `point1` | 在全局坐标系中表示的 body1 上的点 [x,y,z] | array[3] | -- | 是 | -- |
| `point2` | 在全局坐标系中表示的 body2 上的点 [x,y,z] | array[3] | -- | 是 | -- |
| `free_length` | TSDA 自由长度 | double | -- | 是 | -- |
| `preload` | 预加载力 | double | -- | 否 | 0 |
| `minimum_length` | TSDA 最小长度 | double | -- | 否 | -- |
| `maximum_length` | TSDA 最大长度 | double | -- | 否 | -- |
| `visualization` | TSDA 元件的可视化属性 | object | -- | 否 | 无可视化 |

对于线性弹簧-阻尼器，使用 `spring_coefficient` 和 `damping_coefficient` 属性。
例如：

```yaml
tsdas:
  - name: linear_spring_damper
    body1: first_body
    body2: second_body
    point1: [6.5, 0, 0]
    point2: [5.5, 0, 0]
    spring_coefficient: 50.0
    damping_coefficient: 5.0
    free_length: 1.0
    visualization:
      type: SPRING
      radius: 0.05
      resolution: 80
      turns: 15
```

对于非线性行为，使用 `spring_curve_data` 和/或 `damping_curve_data` 和/或 `deformation`/`map_data` 对。这些属性允许以表格数据的形式指定弹簧-阻尼器特性（Chrono 在运行时将进行线性插值）。例如：

```yaml
tsdas:
  - name: nonlinear_spring_damper
    body1: first_body
    body2: second_body
    point1: [6.5, 0, 0]
    point2: [5.5, 0, 0]
    deformation: [ 0.273304, 0.278384, 0.283464, 0.288544, 0.293624, 0.324104, 0.343002, 0.361899, 0.380797, 0.399694, 0.418592, 0.423672, 0.428752, 0.433832, 0.438912 ],
    map_data: [
      [ -0.666667, -5691.62, -5691.62, -5691.62, -5691.62, -5691.62, -9690.35, -9690.35, -9690.35, -9690.35, -9690.35, -9690.35, -5691.62, -5691.62, -5691.62, -5691.62 ],
      [ -0.333333, -2845.81, -2845.81, -2845.81, -2845.81, -2845.81, -4845.17, -4845.17, -4845.17, -4845.17, -4845.17, -4845.17, -2845.81, -2845.81, -2845.81, -2845.81 ],
      [ 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ],
      [ 0.333333, 21307.1, 21307.1, 21307.1, 21307.1, 21307.1, 11675.1, 11675.1, 11675.1, 11675.1, 11675.1, 11675.1, 21307.1, 21307.1, 21307.1, 21307.1 ],
      [ 0.666667, 42614.2, 42614.2, 42614.2, 42614.2, 42614.2, 23350.2, 23350.2, 23350.2, 23350.2, 23350.2, 23350.2, 42614.2, 42614.2, 42614.2, 42614.2 ]
    ]
```

可选地，`visualization` 对象指定 TSDA 元件的渲染方式：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `type` | 可视化几何类型 | string | `SEGMENT`,`SPRING` | 是 | -- |
| `color` | 元件的 RGB 颜色 `[r, g, b]` | array[3] | -- | 否 | [0, 0, 0] |
| `radius` | 可视化 TSDA 几何的半径（如果为 `SPRING`） | double | -- | 否 | 0.05 |
| `resolution` | 每个线圈转数的细分数（如果为 `SPRING`） | integer | -- | 否 | 65 |
| `turns` | 线圈的圈数（如果为 `SPRING`） | integer | -- | 否 | 5 |

#### 旋转弹簧-阻尼器

旋转弹簧-阻尼器元件（RSDA）在两个连接的刚体之间施加力矩。在 YAML 配置文件中，它们列在一个名为 `rsdas` 的数组中，包含具有以下属性的对象：

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `name` | 元件的唯一标识符 | string | -- | 是 | -- |
| `body1` | 要连接的第一个刚体的名称 | string | -- | 是 | -- |
| `body2` | 要连接的第二个刚体的名称 | string | -- | 是 | -- |
| `location` | RSDA 位置，以全局坐标系表示 [x,y,z] | array[3] | -- | 否 | [0, 0, 0] |
| `axis` | RSDA 轴，以全局坐标系表示 [x,y,z] | array[3] | -- | 是 | -- |
| `free_angle` | RSDA 自由角度 | double | -- | 是 | -- |
| `preload` | 预加载力矩 | double | -- | 否 | 0 |
| `spring_coefficient`  | 线性弹簧系数 | double | -- | 线性弹簧必需 | -- |
| `damping_coefficient` | 线性阻尼系数 | double | -- | 线性阻尼器必需 | -- |
| `spring_curve_data`   | 非线性弹簧曲线数据 [[角度, 力矩], ...] | array, see above | -- | 非线性弹簧必需 | -- |
| `damping_curve_data`  | 非线性阻尼曲线数据 [[角速度, 力矩], ...] | array, see above | -- | 非线性阻尼器必需 | -- |

线性或非线性 RSDA 力矩的指定方式与 TSDA 的相应线性或非线性力类似。

### 体力

体力（Body loads）代表施加于仿真中特定物体上的外力或力矩。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `name` | 元件的唯一标识符 | string | -- | 是 | -- |
| `type` | 体力类型 | string | `FORCE`, `TORQUE` | 是 | -- |
| `body` | 施加体力的刚体名称 | string | -- | 是 | -- |
| `load` | 力或力矩的向量 | array[3] | -- | 是 | -- |
| `local_load` | `load` 是否在局部刚体坐标系（true）或全局坐标系（false）下施加 | boolean | -- | 是 | -- |
| `point` | （仅限 `FORCE`）施加 `load` 的位置 | array[3] | -- | `FORCE` 必需 | -- |
| `local_point` | （仅限 `FORCE`）`point` 是否在局部刚体坐标系（true）或全局坐标系（false）下指定 | boolean | -- | `FORCE` 必需 | -- |

### 电机

电机（Motors）用于对刚体施加力或力矩。支持的电机类型（`type`）包括：`LINEAR` 和 `ROTATION`。`LINEAR` 电机沿指定轴施加力，而 `ROTATION` 电机施加力矩。

| 属性 | 描述 | 类型 | 可用值 | 必需 | 默认值 | 
|----------|-------------|------|------------------|----------|---------|
| `name` | 电机的唯一标识符 | string | -- | 是 | -- |
| `type` | 电机类型 | string | `LINEAR`,<br>`ROTATION` | 是 | -- |
| `body1` | 要连接的第一个刚体的名称 | string | -- | 是 | -- |
| `body2` | 要连接的第二个刚体的名称 | string | -- | 是 | -- |
| `location` | 电机位置，以全局坐标系表示 [x,y,z] | array[3] | -- | 是 | -- |
| `axis` | 电机轴，以全局坐标系表示 [x,y,z] | array[3] | -- | 是 | -- |
| `actuation_type` | 驱动类型 | string | `POSITION`,<br>`SPEED`,<br>`FORCE` | 是 | -- |
| `actuation_function` | 定义驱动的时间函数 | object | -- | 是 | -- |
| `guide` | 线性电机的导向约束 | string | `FREE`,<br>`PRISMATIC`,<br>`SPHERICAL` | 否 | `PRISMATIC` |
| `spindle` | 旋转电机的主轴约束 | string | `FREE`,<br>`REVOLUTE`,<br>`CYLINDRICAL` | 否 | `REVOLUTE` |

### 函数

函数（Functions）对象用于指定驱动输入。唯一必需的字段是 `type`，它决定了哪些附加字段是有效的。支持的函数类型包括：

- `CONSTANT` 定义一个具有固定 `value` 的函数；
- `POLYNOMIAL` 定义一个多项式函数，形式为 `f(x) = a₀ + a₁x + a₂x² + ...`，使用 `coefficients` 字段：[a₀, a₁, a₂, ...]；
- `SINE` 定义一个正弦函数，具有 `amplitude`、`frequency` 和 `phase`；
- `RAMP` 定义一个斜坡函数，具有 `slope` 和 `intercept`；
- `DATA` 插值一系列数据点（见下文）；
- `CONTROLLER` 表示将提供一个外部控制器来提供函数值。

`DATA` 类型的函数使用指定数据点之间的线性插值：

```yaml
type: DATA
data:
  - [0.0, 0.0]
  - [1.0, 5.0]
  - [2.0, 2.5]
```

所有函数类型（除了 `CONTROLLER`）都可以包含一个可选的 `repeat` 字段，以周期性地重复函数。
例如：

```yaml
repeat:
  start: 1.0
  width: 2.0
  shift: 3.0
```

## YAML 模式

YAML 模型规范文件必须遵循 Chrono 数据目录中提供的 ``data/yaml/schema/mbs_model.schema.yaml`` 文件：

\include data/yaml/schema/mbs_model.schema.yaml
