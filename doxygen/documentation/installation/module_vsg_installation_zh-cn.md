安装 VSG 模块 {#module_vsg_installation}
==========================

[TOC]

Chrono::VSG 是一个运行时可视化系统，用于交互式 3D 查看 Chrono 仿真。

## 功能

**VSG 模块**用于在交互式 3D 视图中显示 Chrono 仿真。
主要功能如下：

- 支持大多数在 Chrono 物理对象（刚体、连接等）上指定为 _assets_ 的可视化形状
- 支持以下默认鼠标和键盘控制：
    - 鼠标左键用于相机旋转
    - 鼠标右键用于相机 x z 平移
    - 鼠标滚轮用于相机前后移动
    - 按箭头键进行 x z 平移，按 Page Up 和 Page Down 键进行 y 方向垂直移动

## 构建和安装前提条件

构建 Chrono VSG 模块有两个前提条件：

- [Vulkan](https://www.vulkan.org/) 是一个跨平台的 3D 图形 API。可以从 [https://vulkan.lunarg.com/](https://vulkan.lunarg.com/) 下载 [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)。请按照特定于您平台的安装说明进行操作。

- [VulkanScenegraph](https://vsg-dev.github.io/VulkanSceneGraph) 是一个基于 Vulkan 图形 API 构建的图形库。目前，VSG 库及其依赖项和其他相关实用程序库必须从源代码构建。

  构建和安装所有 VSG 依赖项的官方机制是使用 VSG 开发人员提供的 [vsgFramework](https://github.com/vsg-dev/vsgFramework)。但是请注意，这种方法将使用最新的 VSG 开发代码，因此可能与当前的 Chrono::VSG 模块不兼容。

  为了解决这个问题，我们在 Chrono 源代码树的 `contrib/build-scripts/vsg` 目录中提供了一组脚本（适用于 Windows 和 Linux）。这些脚本允许我们针对 VSG 依赖项的特定版本（即各自 GitHub 仓库中的标签）进行构建，并确保与当前的 Chrono::VSG 代码兼容。

  当前的 Chrono::VSG 模块需要以下版本的 VSG 及其依赖库：
  - [vsg](github.com/vsg-dev/VulkanSceneGraph.git) 1.1.11
  - [vsgXchange](github.com/vsg-dev/vsgXchange.git) 1.1.7
  - [vsgExamples](github.com/vsg-dev/vsgExamples.git) 1.1.9
  - [vsgImGui](github.com/vsg-dev/vsgImGui.git) 0.7.0
  - [assimp](github.com/assimp/assimp) 5.4.3
  - [draco](github.com/google/draco) 1.5.7

构建和安装 VSG 依赖项的两种方法将在接下来的两个部分中描述。
基于上述原因，我们**强烈建议**使用提供的 VSG 构建脚本。

### 1. VSG Framework

获取 Chrono::VSG 模块所需的所有 VSG 前置条件的官方方法是构建 [vsgFramework](https://github.com/vsg-dev/vsgFramework)，它收集了多个与 VSG 相关的项目，并简化了一步完成构建和安装的过程。

VSG 库本身正在积极开发中，vsgFramework 也是如此。虽然功能齐全，但有时会出现问题，可能需要一些修复才能获得所需的依赖库。以下说明反映了 vsgFramework 代码的当前状态。

  1. 克隆 vsgFramework [GitHub 仓库](https://github.com/vsg-dev/vsgFramework)。
     假设源代码位于本地目录 **[vsgFramework_source]**。
  2. 为 vsgFramework 创建一个 **build** 目录和一个 **install** 目录。
     假设这些目录分别为 **[vsgFramework_build]** 和 **[vsgFramework_install]**。
  3. 使用 CMake 配置 vsgFramework。请注意，Chrono::VSG 所需的唯一组件是 *assimp*、*vsgImGui* 和 *vsgXchange*。启用相应的 `BUILD_***` CMake 选项，并取消选择所有其他选项。
  4. 将安装目录 (`CMAKE_INSTALL_PREFIX`) 设置为上面创建的 **[vsgFramework_install]** 目录。
  5. 请注意，vsgFramework 可以创建 *静态* 或 *动态* VSG 库。任意类型在 Linux 或 MacOS 上都可以使用。然而，只有 *动态* 库 (*DLLs*) 在 Windows 上可用。相应地设置 CMake 变量 `BUILD_SHARED_LIBS`。
  6. 完成 CMake 配置并生成构建脚本。
  7. 构建并安装 vsgFramework 库（使用您在 CMake 中选择的生成器的适当方法；make、ninja、VS 等）。
  8. 安装在 **[vsgFramework_install]** 中的 VSG 头文件、库和 DLL（如果适用）必须在配置 Chrono 时可用并可访问 CMake。如果需要（例如在 Windows 上），请将 **[vsgFramework_install]/bin** 目录添加到系统 `PATH` 环境变量中。

  <div class="ce-warning">
  `assimp` 组件需要 `zlib`。<br>
  在某些 Linux 系统上，安装默认的 zlib 包可能无法提供适合动态链接的库。<br>
  您可能需要自行重新构建 zlib，确保生成位置无关代码。<br>
  特别是，如果使用 GCC，请确保添加标志 `-fPIC`。
  </div>

### 2. VSG 构建脚本

由于 VSG 库本身正在积极开发，其最新版本可能与当前的 Chrono::VSG 代码不兼容。为了确保 Chrono::VSG 与其 VSG 依赖项之间的兼容性，我们提供了一组脚本（随 Chrono 源代码提供），这些脚本下载 VSG 依赖项的特定代码版本，构建所有必要的库，并将它们安装到用户指定的位置。

这些脚本（`buildVSG.bat` 和 `buildVSG.sh`，分别用于 Windows 和 Linux）位于 [Chrono 仓库](https://github.com/projectchrono/chrono/tree/main/contrib/build-scripts/vsg) 的 `contrib/build-scripts/vsg` 目录中。

1. 复制相应的脚本并将其放置在任意临时目录中。
2. 编辑脚本副本以：
   - 强制下载 VSG 库代码。
   - 指定安装目录（设置变量 `VSG_INSTALL_DIR`）。
   - 决定是构建共享库还是静态库，以及是否还要构建调试库。
3. 从脚本副本所在的位置运行脚本（`.\buildVSG.bat` 或 `sh buildVSG.sh`，视情况而定）。这将创建一个临时目录，其中将克隆所有源代码仓库，并创建一组目录，用于构建各个 VSG 依赖项。
4. 安装目录将在 `VSG_INSTALL_DIR/lib/cmake` 的子目录下包含所有 VSG CMake 项目配置脚本，这些脚本在启用 Chrono::VSG 模块时配置 Chrono 所需的所有内容。

## 构建说明

安装必要的依赖项后，执行以下步骤以配置和构建 Chrono::VSG 模块：

1. 重复[完整安装](@ref tutorial_install_chrono)的说明。

2. 将 `CH_ENABLE_MODULE_VSG` 设置为 'on'。

3. 当系统提示时，提供各个 VSG 项目配置脚本的路径（`vsg_DIR`、`vsgImGui_DIR` 和 `vsgXchange_DIR`）。例如，假设您使用了提供的 [构建脚本](#vsg_scripts)，这些路径应分别为 `<VSG_INSTALL_DIR>/lib/cmake/vsg`、`<VSG_INSTALL_DIR>/lib/cmake/vsgImGui` 和 `<VSG_INSTALL_DIR>/lib/cmake/vsgXchange`。

4. 再次按下 'Configure'，然后按下 'Generate'，并按照安装说明继续操作。

<div class="ce-warning">
使用第三方依赖项的共享库时，必须确保在运行时能够找到这些库。<br>
在 Windows 上，您可以将依赖项 DLL 复制到可执行文件所在的目录，或者将这些共享库的路径添加到 `PATH` 环境变量中。<br>
在 Linux 上，您可能需要将其追加到 `LD_LIBRARY_PATH` 环境变量中。
</div>

## 使用方法

- 请查阅本模块的 [API 部分](group__vsg__module.html) 以获取有关类和函数的文档。

- 请查阅 [示例](@ref tutorial_root) 的 C++ 源代码，以了解如何使用本模块的功能。
