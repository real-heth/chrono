安装 DEM-引擎 {#deme_installation}
=================================

### 从源代码安装

在 Linux 机器上，如果尚未安装 CUDA，请先安装 CUDA。可以在 [这里](https://developer.nvidia.com/cuda-downloads) 找到有用的安装说明。

一些关于准备 CUDA 的额外故障排除提示：

- 在 WSL 上，这段代码可能可以构建（并且 [这里](https://docs.nvidia.com/cuda/wsl-user-guide/index.html) 是在 WSL 上安装 CUDA 的指南），但可能无法运行。这是由于 WSL 上对统一内存和固定内存支持的诸多限制。建议使用原生 Linux 机器或集群。

一旦 CUDA 准备就绪，克隆此项目，然后：

```shell
git submodule init
git submodule update
```

这将拉取子模块 NVIDIA/jitify，以便我们能够进行运行时编译。

然后，通常的做法是在其中创建一个构建目录。然后在构建目录中，使用 `cmake` 配置编译。一个示例：

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

如果需要将 cmake 更新到最新版本，可以参考 [此信息](https://askubuntu.com/questions/1203635/installing-latest-cmake-on-ubuntu-18-04-3-lts-run-via-wsl-openssl-error)。

我们建议安装一个 `cmake` GUI，例如 `ccmake`，以及 `ninja_build` 生成器，以更好地帮助您配置项目。在这种情况下，上述示例可以替代地这样完成：

```shell
mkdir build
cd build
ccmake -G Ninja ..
```

通常情况下，您无需在图形界面中更改构建选项，但建议将 `CMAKE_BUILD_TYPE` 修改为 `Release`。此外，如果您需要将此软件包作为库进行安装，则可以指定一个 `CMAKE_INSTALL_PREFIX`。

一些关于生成项目的额外故障排除提示：

- 如果找不到某些依赖项，例如 CUB，则可能需要手动设置 `$PATH` 和 `$LD_LIBRARY_PATH`。下面给出了一个针对特定版本 CUDA 的示例，请注意在您的机器或集群上可能会有所不同。您还应检查 `nvidia-smi` 和 `nvcc --version` 是否返回正确。

- 如果找不到某些依赖项，例如 CUB，则可能需要手动设置 `$PATH` 和 `$LD_LIBRARY_PATH`。下面给出了一个针对特定版本 CUDA 的示例，请注意在您的机器或集群上可能会有所不同。您还应检查 `nvidia-smi` 和 `nvcc --version` 是否返回正确。

```shell
export CPATH=/usr/local/cuda-12.0/targets/x86_64-linux/include${CPATH:+:${CPATH}}
export PATH=/usr/local/cuda-12.0/bin${PATH:+:${PATH}}
export PATH=/usr/local/cuda-12.0/lib64/cmake${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-12.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
export CUDA_HOME=/usr/local/cuda-12.0
```

最后，构建项目。

```shell
ninja
```

一些关于构建项目的附加故障排除技巧：

- 如果在编译过程中看到一些语法错误，例如 `filesystem` 不是 `std` 的成员或参数未使用 `...` 展开，则手动将标志 `TargetCXXStandard` 设置为 `STD_CXX17` 可能会有所帮助。

### 安装为 C++ 库

在 `cmake` GUI 中将 `CMAKE_INSTALL_PREFIX` 标志设置为您希望的安装路径，然后

```shell
ninja install
```

我们提供了在 [chrono-projects](https://github.com/projectchrono/chrono-projects/tree/feature/DEME) 中链接 [Chrono](https://github.com/projectchrono/chrono) 和 _DEME_ 进行协同仿真的示例。

假设您知道如何构建链接到 Chrono 安装的 `chrono-projects`，那么链接到 _DEME_ 时需要做的额外操作是

- 将 `ENABLE_DEME_TESTS` 设置为 `ON`;
- 在提示时设置 `ChPF_DIR`。它应该位于 `<your_install_dir>/lib64/cmake/ChPF`;
- 在提示时设置 `DEME_DIR`。它应该位于 `<your_install_dir>/lib64/cmake/DEME`.

然后构建项目，您应该能够运行演示脚本，这些脚本展示了 _DEME_ 和 Chrono 之间的协同仿真。
