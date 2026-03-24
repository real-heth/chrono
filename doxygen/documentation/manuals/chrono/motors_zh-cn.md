
电动机   {#motors}
========

电机是用于施加运动的对象，可以是 _直线_ 运动（@ref chrono::ChLinkMotorLinear "ChLinkMotorLinear"）或 _旋转_ 运动（@ref chrono::ChLinkMotorRotation "ChLinkMotorRotation"），适用于 1D 对象（即 @ref chrono::ChShaft "ChShaft"）或 3D 对象（即 @ref chrono::ChBody "ChBody"）。

由于 @ref chrono::ChLinkMotorRotation "ChLinkMotorRotation" 和 @ref chrono::ChLinkMotorLinear "ChLinkMotorLinear" 继承自 @ref chrono::ChLinkMate "ChLinkMate"，因此对后者的所有考虑也适用于这些电机。

在某些情况下，运动是通过 @ref chrono::ChFunction "ChFunction" 对象控制的，详见 [这里](@ref ChFunction_objects)。

| -                        | 3D 旋转                 | 3D 线性                       | 1D 线性/旋转                                        |   
| :----------------------- | :---------------------------------------------------------------------:  | :------------------------------------------------------------------: | :--------------------------------------------------------:  |
| 强制位移      | @ref chrono::ChLinkMotorRotationAngle "ChLinkMotorRotationAngle"         | @ref chrono::ChLinkMotorLinearPosition "ChLinkMotorLinearPosition"   | @ref chrono::ChShaftsMotorPosition "ChShaftsMotorPosition"  |   
| 强制速度             | @ref chrono::ChLinkMotorRotationSpeed "ChLinkMotorRotationSpeed"         | @ref chrono::ChLinkMotorLinearSpeed "ChLinkMotorLinearSpeed"         | @ref chrono::ChShaftsMotorSpeed "ChShaftsMotorSpeed"        |
| 施加负载               | @ref chrono::ChLinkMotorRotationTorque "ChLinkMotorRotationTorque"       | @ref chrono::ChLinkMotorLinearForce "ChLinkMotorLinearForce"         | @ref chrono::ChShaftsMotorLoad "ChShaftsMotorLoad"      |
| 连接到 1D 传动系统  | @ref chrono::ChLinkMotorRotationDriveline "ChLinkMotorRotationDriveline" | @ref chrono::ChLinkMotorLinearDriveline "ChLinkMotorLinearDriveline" | -                                                           |

<div class="ce-warning"> 
旧的 chrono::ChLinkLockLinActuator 类已过时：建议用户使用本页中描述的新 ChLinkMotor 类。
</div>

\tableofcontents

# 3D 旋转电机   {#rotational_motors}

这些电机连接两个 @ref chrono::ChBodyFrame "ChBodyFrame" 类的部件，即在空间中具有平移+旋转的对象，例如 @ref chrono::ChBody "ChBody" 或 @ref chrono::fea::ChNodeFEAxyzrot "ChNodeFEAxyzrot"。
所有旋转电机都继承自 @ref chrono::ChLinkMotorRotation "ChLinkMotorRotation"，并考虑约束框架的 Z 轴周围的旋转，以弧度为基本单位。

![](http://www.projectchrono.org/assets/manual/pic_ChLinkMotorRotation.png)

旋转电机允许多圈旋转，并提供包装的 @ref chrono::ChLinkMotorRotation::GetMotorAngleWrapped() "GetMotorAngleWrapped()" 或未包装的 @ref chrono::ChLinkMotorRotation::GetMotorAngle() "GetMotorAngle()" 电机角度。

相对位移|速度|加速度通过 @ref chrono::ChLinkMotorRotation::GetMotorAngle() "GetMotorAngle()" | @ref chrono::ChLinkMotorRotation::GetMotorAngleDt() "GetMotorAngleDt()" | @ref chrono::ChLinkMotorRotation::GetMotorAngleDt2() "GetMotorAngleDt2()" 获取

默认情况下，所有旋转电机还在 Z 轴上嵌入一个旋转约束，除非通过 @ref chrono::ChLinkMotorRotation::SetSpindleConstraint() "SetSpindleConstraint()" 方法另行指定，该方法可以接受以下选项：

- FREE : 不对主轴方向/对齐施加约束
- REVOLUTE: 对 **X**,**Y**,**Z**, **RX**, **RY** 施加约束（默认）
- CYLINDRICAL: 对 **X**,**Y**, **RX**, **RY** 施加约束
- OLDHAM: 对 **RX**, **RY** 施加约束

一般来说，添加电机的过程包括以下步骤：

- 从所需的 ChLinkMotorXxxyyy 类创建电机
- 使用类中可用的 ```Initialize()``` 方法之一
- 将电机添加到 ChSystem 中
- 关联一个描述运动函数的 @ref chrono::ChFunction "ChFunction" 对象；
  方法名称取决于具体的派生类。

示例：

~~~{.cpp}
// 创建电机
auto rotmotor = chrono_types::make_shared<ChLinkMotorRotationSpeed>();

// 连接转子和定子并将电机添加到系统中：
rotmotor->Initialize(rotor,                // 物体 A
                     stator,               // 物体 B
                     ChFramed(ChVector3d(1,0,0)) // 电机框架，绝对坐标
                     );
                      
// 将电机添加到系统中
mphysicalSystem.Add(rotmotor);

// 创建一个 ChFunction 用于电机：例如一个恒定的角速度，单位为 [rad/s]，例如 1 PI/s =180°/s
auto mwspeed = chrono_types::make_shared<ChFunctionConst>(CH_PI); 

// 让电机使用我们的运动函数：
rotmotor->SetSpeedFunction(mwspeed);

~~~

# 3D 线性电机 {#linear_motors}

这些电机连接两个 @ref chrono::ChBodyFrame "ChBodyFrame" 类的部件，即在空间中具有平移+旋转的对象，例如 @ref chrono::ChBody "ChBody" 或 @ref chrono::fea::ChNodeFEAxyzrot "ChNodeFEAxyzrot"。

所有线性电机都继承自 @ref chrono::ChLinkMotorLinear "ChLinkMotorLinear"，并假设 Z 轴为允许的方向。

![](http://www.projectchrono.org/assets/manual/pic_ChLinkMotorLinear.png)

默认情况下，所有线性电机还为其他相对自由度（关于 **Y**、**Z** 的平移和关于 **RX**、**RY**、**RZ** 的旋转，除了由电机控制的 Z 方向的旋转平移）提供棱柱约束，因此您无需创建额外的关节，例如 ChLinkLockPrismatic，以保持两个部件在一起。无论如何，如果您愿意，可以使用 ChLinkMotorLinear::SetGuideConstraint() 函数更改此行为，该函数可以接受以下选项：

相对位移|速度|加速度通过 @ref chrono::ChLinkMotorLinear::GetMotorPos() "GetMotorPos()" | @ref chrono::ChLinkMotorLinear::GetMotorPosDt() "GetMotorPosDt()" | @ref chrono::ChLinkMotorLinear::GetMotorPosDt2() "GetMotorPosDt2()"

默认情况下，所有线性电机还在 Z 轴上嵌入一个棱柱约束，除非通过 @ref chrono::ChLinkMotorLinear::SetGuideConstraint() "SetGuideConstraint()" 方法另行指定，该方法可以接受以下选项：

- FREE : 不对滚子方向/对齐施加约束
- PRISMATIC: 对 **X**, **Y**, **RX**, **RY**, **RZ** 施加约束（默认）
- SPHERICAL: 对 **X** 和 **Y** 施加约束

初始化过程类似于 `ChLinkMotorRotation` 的情况。

## 3D 传动系统电机  {#driveline_motors}

@ref chrono::ChLinkMotorLinearDriveline "ChLinkMotorLinearDriveline" 和 @ref chrono::ChLinkMotorRotationDriveline "ChLinkMotorRotationDriveline" 允许通过将其与 @ref chrono::ChShaft "ChShaft" 的平移/旋转耦合，在两个 3D 物体之间施加相对运动（分别为平移和旋转）。受约束的方向始终沿 Z 轴。

由于这种耦合，施加在轴上的任何运动都会导致受约束框架（线性或旋转，取决于电机类型）产生相应的运动，但特别是受约束物体感受到的任何反作用力/力矩都会反映回轴。

这意味着，与其他通过 @ref chrono::ChFunction "ChFunction" 提供的“信号”直接驱动的 @ref chrono::ChLinkMotor "ChLinkMotor" 不同，该类保持功率平衡，并在位移和力的层面上描述完整的耦合。

在设置 @ref chrono::ChShaft "ChShaft" 对象的惯性值时应特别注意，以避免不稳定性，尤其是在低惯性和高速情况下。

## 1D 电机  {#shaft_motors}

@ref chrono::ChShaftsMotor "ChShaftsMotor" 类型的电机作用于一对 1D 空间的对象。

其使用方法类似于 @ref chrono::ChLinkMotor "ChLinkMotor" 类型的电机，不同之处在于受约束的对象是 @ref chrono::ChShaft "ChShaft" 类型。

# 示例

另请参见：

- [demo_MBS_motors](https://github.com/projectchrono/chrono/blob/main/src/demos/mbs/demo_MBS_motors.cpp)
