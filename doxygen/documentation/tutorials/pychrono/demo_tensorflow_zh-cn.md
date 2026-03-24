深度强化学习（PyChrono + TensorFlow） {#tutorial_pychrono_demo_tensorflow}
==========================

# 简介

深度强化学习（DRL）是使用强化学习训练深度神经网络的方法。近年来，DRL 已成功应用于多种机器人控制任务。该方法的主要优点在于能够应对非结构化且动态变化的环境，而传统机器人控制在这些场景下往往表现欠佳。

训练神经网络需要与环境进行大量交互，因此物理引擎可以提供很大帮助：在虚拟环境中训练智能体可以替代直接在现实世界中训练，从而节省时间并降低风险。

使用 PyChrono，您可以方便地构建物理模型，并在仿真与首选的机器学习框架之间交换数据。

我们建议使用下面两种方式之一入门 PyChrono 的 DRL：

# 1- [gym-chrono](https://github.com/projectchrono/gym-chrono)

如果您需要更复杂、更逼真的环境，并希望利用 OpenAI Gym 的生态（例如使用 [OpenAI Baselines](https://github.com/openai/baselines)），推荐使用 `gym-chrono`，它是一组基于 PyChrono 的 OpenAI Gym 环境。这些环境为 MuJoCo 环境提供了开源替代方案。

# 2- TensorFlow 示例

我们还提供了两个即插即用的示例，帮助您快速使用 DRL 进行机器人控制。这些示例仅需要 TensorFlow 与 PyChrono 即可运行，并内置一个独立的 Proximal Policy Optimization（PPO）算法实现。

[示例代码（PYTHON）](https://github.com/projectchrono/chrono/tree/main/src/demos/python/chrono-tensorflow)

### 依赖项：

运行这些示例需要安装：

- Numpy
- Scikit-Learn
- TensorFlow 1.x

我们推荐使用 [Anaconda](https://www.anaconda.com/)。准备环境的步骤如下：

- 下载并安装 Anaconda（建议选择用户安装并将 Anaconda 设置为默认 Python）。
- 创建一个新的 Python 环境。如果您是从源码构建 PyChrono，请将该环境的 Python 版本设置为在 CMake 中指定的 Python 可执行文件版本；也可以使用该虚拟环境的可执行文件、头文件和库来构建 PyChrono。
- 激活新环境。
- 如果您尚未从源码构建 PyChrono，可通过 Anaconda 安装 pychrono：

~~~~~~~~~~~~~{.sh}
conda install -c projectchrono pychrono
~~~~~~~~~~~~~

- 安装 Numpy：

~~~~~~~~~~~~~{.sh}
conda install numpy
~~~~~~~~~~~~~

- 安装 Scikit-Learn：

~~~~~~~~~~~~~{.sh}
conda install scikit-learn
~~~~~~~~~~~~~

- 安装 TensorFlow（示例使用 GPU 版 1.14）：

~~~~~~~~~~~~~{.sh}
conda install tensorflow-gpu=1.14
~~~~~~~~~~~~~

### 目标：

我们将训练一个神经网络来解决使用 [PyChrono](@ref pychrono_introduction) 创建的虚拟训练环境中的机器人控制任务。示例包含虚拟环境和基于 TensorFlow 的学习模型。

### 环境概览

我们提供两个示例环境用于机器人控制：

**ChronoPendulum**

![](http://projectchrono.org/assets/manual/Tutorial_tensorflow_pendulum.jpg)

倒立摆任务，目标是在小车上保持杆的平衡。动作为 1 维（沿 z 轴的力），观测为 4 维（小车与杆的位置与速度）。

**ChronoAnt**

![](http://projectchrono.org/assets/manual/Tutorial_tensorflow_ant.jpg)

四足行走器，目标是以尽可能快且直的速度行走。动作为 8 维（电机扭矩），观测为 30 维。

### 使用的强化学习算法

为训练神经网络，我们采用了称为 Proximal Policy Optimization（PPO）的强化学习算法（参见 https://arxiv.org/abs/1707.06347）。PPO 是一种 on-policy 的 actor-critic 算法，因此包含两个神经网络：策略网络（Policy），用于在给定状态下输出动作；价值网络（VF），用于评估给定状态下的价值函数。

策略与价值函数的代码分别位于 `Policy.py` 与 `VF.py`。

## 如何运行示例

确保使用的 Python 解释器已安装 PyChrono 与 TensorFlow，然后用所需的命令行参数运行脚本。

### 串行与并行训练

可选择 `train_serial.py`（串行）或 `train_parallel.py`（并行）。并行版本使用 Python 的 `multiprocessing` 模块从多个仿真中收集数据；在训练后期（单个 episode 更长）并行训练可显著加速学习过程。

**示例**：

在 1000 个 episode 上训练倒立摆：

~~~~~~~~~~~~~{.sh}

python ./train_serial.py ChronoPendulum -n 1000

~~~~~~~~~~~~~

在 20000 个 episode 上训练四足机器人：

~~~~~~~~~~~~~{.sh}

python ./train_parallel.py ChronoAnt -n 20000

~~~~~~~~~~~~~

也可以在您喜欢的 IDE 中启动示例，但请记得提供必要的命令行参数。

### 命令行参数说明

除环境名与 episode 数量外，还有若干用于微调学习参数的参数。
`--renderON/--renderOFF` 控制是否打开渲染。注意：可视化渲染会降低仿真速度并影响训练效率。

- **环境名**：`env_name`
- **episode 数量**：`-n`, `--num_episodes`，默认=1000
- **运行时渲染**：`--renderON` / `--renderOFF`
- **折扣因子**：`-g`, `--gamma`，默认=0.995
- **GAE 的 lambda**：`-l`, `--lam`，默认=0.98
- **Kullback–Leibler 散度目标值**：`-k`, `--kl_targ`，默认=0.003
- **批次大小**：`-b`, `--batch_size`，默认=20

### 保存与恢复

神经网络参数与其他 TensorFlow 变量存储在 `Policy` 与 `VF` 目录中，缩放器（scaler）的均值与方差存储在 `scaler.dat`（numpy 文件）中。可使用这些文件/目录恢复之前的检查点。

由于并行与串行版本使用相同的网络架构，因此恢复检查点时两者没有区别。

### 测试器

要在不进一步训练策略的情况下测试策略，请运行 `tester.py`。使用 `--VideoSave` 可保存渲染截图。
