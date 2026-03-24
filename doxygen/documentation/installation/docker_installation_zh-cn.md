使用 Chrono 构建 Docker 镜像 {#docker_installation}
==========================

本指南介绍如何构建一个安装了 Chrono 的 Docker 镜像，包括所选模块和依赖项。该镜像是使用自定义 Dockerfile 创建的，该文件汇总了多个片段文件——每个文件都附加了必要的 CMake 选项和预构建环境命令。Docker Compose 用于协调构建和运行过程。

## 先决条件

确保您具备以下条件：

- 系统上已安装 Docker。如果没有，请从 [官方网站](https://docs.docker.com/get-docker/) 下载并安装 Docker。
- 系统上已安装 Docker Compose。如果没有，请从 [官方网站](https://docs.docker.com/compose/install/) 下载并安装 Docker Compose。这是可选的，但推荐用于协调构建和运行过程。本指南将使用 Docker Compose。
- 您已克隆 Chrono 仓库。

## 背景

提供的 `docker-compose.yml` 定义了两个服务：`dev` 和 `vnc`。`dev` 服务是主要镜像，用于构建包含所选模块和依赖项的 Chrono 库。`vnc` 服务是可选的，帮助在没有 `X11` 的系统上进行可视化，或者在远程访问没有显示器的机器时使用。

\include docker-compose.yml

您还可以在构建时通过 `APT_DEPENDENCIES` 和 `PIP_DEPENDENCIES` 环境变量在 `docker-compose.yml` 中提供额外的依赖项或要求。您还可以根据需要为片段提供额外的构建参数。基础镜像必须是基于 `debian` 的（某些模块可能需要基于 `ubuntu` 的镜像）。

默认的 `docker-compose.yml` 文件将在可用时将 NVIDIA GPU 附加到容器中。如果您没有 NVIDIA GPU，可以注释掉 `docker-compose.yml` 文件中 `deploy` 之后的部分。

为了简化 dockerfile，我们利用了一个开源项目 [`dockerfile-x`](https://github.com/devthefuture-org/dockerfile-x)（不需要任何安装）。该项目提供了 `INCLUDE` 指令，允许我们在单个 Dockerfile 中包含多个文件。通过这种方式，我们只需在需要的模块上调用 `INCLUDE`，最终的 dockerfile 将自动生成。

\include snippets/chrono.dockerfile

您可以注释掉（或创建新的）包含所需模块的片段。`CMAKE_OPTIONS` 变量应更新为为所包含模块提供相关的 CMake 选项。例如，启用 `Chrono::Vehicle` 模块需要将 `CH_ENABLE_MODULE_VEHICLE` 选项设置为 `ON`，如下所示：

```
ENV CMAKE_OPTIONS="${CMAKE_OPTIONS} -DCH_ENABLE_MODULE_VEHICLE=ON"
```

## 构建 Docker 镜像

从 Chrono 仓库的任意位置运行以下命令：

```bash
docker compose -f contrib/docker/docker-compose.yml build
```

这将构建 `dev` 和 `vnc` 服务。`dev` 服务将在镜像中全局构建和安装 Chrono。默认的 chrono 构建目录位于 `/home/chrono/chrono`，默认的安装目录位于 `/home/chrono/packages/chrono`。可以分别通过 `CHRONO_DIR` 和 `CHRONO_INSTALL_DIR` 变量进行更改。默认情况下，为了加快构建过程，演示和测试被禁用。

默认情况下，启用以下模块：

- PyChrono
- Chrono::Vehicle
- Chrono::Irrlicht
- Chrono::Parser
- Chrono::VSG
- Chrono::Sensor
- Chrono::ROS

<div class="ce-warning">
这可能需要一些时间，具体取决于您的系统以及您包含的模块。为了加快速度，您可以注释掉一些不需要的模块。
</div>

## 运行 Docker 容器

`dev` 服务的目的是在容器内附加一个 shell。为此，请运行以下命令：

```bash
docker compose -f contrib/docker/docker-compose.yml run dev
```

默认情况下，初始目录是 `/home/chrono/chrono-dev`，该目录是主机的 `chrono` 目录的一个卷。这意味着您可以使用 chrono 构建模板项目。您可以根据需要添加其他卷。

### 可视化 GUI 应用程序

默认情况下，`/tmp/.X11-unix` 目录会挂载到容器中，这允许在主机上显示 GUI 应用程序。如果由于某种原因无法使用此功能，您可以使用 `vnc` 服务来可视化容器。这使用 `NoVNC` 在浏览器中显示容器的桌面。默认情况下，VNC 服务器将在 `8080` 之间的任意端口上运行。然后，您可以导航到 [http://localhost:8080](http://localhost:8080) 查看桌面。如果您在远程机器上，请确保将端口转发到本地机器。

<div class="ce-info">
`docker-compose.yml` 文件实际上将端口设置为 `8080-8099`，因此如果 `8080` 已被使用，它将尝试下一个可用端口。如果出现问题，您可以运行 `docker ps` 查看正在使用的端口。
</div>

## 其他注意事项

### 在没有 NVIDIA GPU 的情况下构建 Docker 镜像

如上所述，默认的 `docker-compose.yml` 文件将在可用时将 NVIDIA GPU 附加到容器中。如果您没有 NVIDIA GPU，可以注释掉 `docker-compose.yml` 文件中 `deploy` 之后的部分。

### 安装 Chrono::Sensor

要安装 Chrono::Sensor，您需要支持 CUDA，拥有 NVIDIA 显卡，并在本地拥有 OptiX 许可证和构建脚本。如果您有 NVIDIA 显卡，请确保在 `ch_sensor.dockerfile` 之前包含 `cuda.dockerfile`。然后，您可以下载 [OptiX 7.7 安装脚本](https://developer.nvidia.com/designworks/optix/downloads/legacy) 并将其放置在 `contrib/docker/data`。
