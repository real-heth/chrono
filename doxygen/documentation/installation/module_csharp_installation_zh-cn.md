安装 CSHARP 模块 {#module_csharp_installation}
==========================

这是一个可选模块，添加了 Chrono 对 C# 的支持。

## 功能

**CSHARP 模块**允许用户在 C# 程序中使用 Chrono，并将 Chrono 接口与诸如 [Unity3D](http://www.unity.com) 等引擎连接。
  
## 要求

- 要 **构建** 此模块：
    - 必须安装 [SWIG](http://www.swig.org/) 包装生成器。在 Mac 上输入 <tt>brew install swig</tt>。

<div class="ce-warning">
Chrono::Csharp requires SWIG version **4.0.0* or newer.
On the Mac **SWIG v. 4.0.1** is known to work. It is installed by homebrew.
</div>

## 构建说明

1. 在系统上安装 SWIG。需要版本 4.0.0 或更高版本。（在 Windows 上，只需解压到所需位置）。

2. 重复 [完整安装](@ref tutorial_install_chrono) 的说明，但当您看到 CMake 窗口时，必须添加以下步骤：

3. 将 `CH_ENABLE_MODULE_CSHARP` 设置为 'on'，然后按 'Configure'（刷新变量列表）。

4. 当您按下 'Configure' 时，CMake 应该已经检测到您的 SWIG 工具。这应该会在 CMake 中创建两个变量，分别是 <tt>SWIG_DIR</tt> 和 <tt>SWIG_EXECUTABLE</tt>。
   如果一切正常，它们应该会自动包含有意义的值，
   例如 <tt>C:/swigwin-4.0.0/Lib</tt> 和 <tt>C:/swigwin-4.0.0/swig.exe</tt>，
   因此您无需修改它们。（在 Windows 上，您可能需要手动设置它们）。

5. 再次按下 'Configure'，然后按 'Generate'，并按照安装说明继续操作。

## 注意事项

Csharp 模块的构建过程，由 CMake 生成，包括以下自动步骤：

- 预处理 C++ 源代码文件，以生成包含通过 API 访问 C++ 函数代码的 .cxx 包装文件，以及（数百个）.cs 文件。这些 C# 文件均生成在 BUILD 目录下的 `chrono_csharp` 子目录中。

- C++ 编译器编译 .cxx 文件并生成一个或多个库文件。在 Windows 上，DLL 库文件会在 *BUILD* 树的 `bin/<Configuration>` 目录中创建。在 Linux 上，.so 共享库会在 *BUILD* 树的 `lib` 目录中创建。

- SWIG 生成的文件 (.cs) 和生成的库文件 (.dll 在 Windows 上，.so 在 Linux/Mac 上) 会在 *BUILD* 树的上述位置生成并可使用。同样，在安装后，所有 Chrono::Csharp 文件会被复制到 *INSTALL* 树的两个不同位置（C# 文件在 `include/chrono_csharp` 下，库文件在 Windows 和 Linux 上分别在 `bin` 或 `lib` 下）。  

<div class="ce-info">
请注意，SWIG 工具需要几分钟时间来处理源代码并生成 .cxx 包装文件。当您开始编译整个 Chrono 项目时，SWIG 执行其任务时，过程可能会看起来“冻结”一到两分钟。
</div>
