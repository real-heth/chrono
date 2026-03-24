撰写白皮书       {#tutorial_writing_whitepapers}
==========================

“白皮书”是提供技术与分析细节的文档，用以说明并支撑 Chrono 中软件实现的依据与原理。

为了保持这些白皮书文档的一致性，强烈建议使用 Chrono 专用的 LaTeX 文档类生成源文档。我们提供了一个 **chrono.cls** LaTeX 类，可替代 article 类用于生成白皮书。项目网站上的白皮书页面即是使用该类生成的。

## 查找 chrono.cls LaTeX 类

- 在仓库的 ```docs\latex_white_papers``` 目录下可以找到 ```chrono.cls``` 和 ```logo_projectchrono_h200.png```。
  
- 将这些文件复制到生成 LaTeX 文档的目录中（例如 ```mywhitepaper.tex``` 所在目录）

## 使用 chrono.cls LaTeX 类

- 在你的 ```mywhitepaper.tex``` 文件中，开始时使用

~~~{.tex}
\documentclass{chrono}
~~~

- 如有需要，包含额外的宏包:

~~~{.tex}
\usepackage{graphicx}
\usepackage{amsmath, amssymb} 
\usepackage[english]{alg}
\usepackage{empheq}
~~~

- 文档的其余部分应具有如下结构:

~~~{.tex}
\begin{document}

\title{My title here}

\author{John Doe}

\maketitle
\thispagestyle{fancy}

\begin{abstract} 
Blah blah..
\end{abstract}

# add sections here...

\end{document}
~~~

## 引用参考和链接

```chrono.cls``` 类提供一些宏，用于创建指向 Chrono API 的链接。

- 链接到 Chrono 的 C++ 类: ```\urlChronoAPIclass```. <br>
  例如: ```\urlChronoAPIclass{chrono::ChMatrix}``` 或 ```\urlChronoAPIclass{chrono::fea::ChElement}```.<br>
  注意必须添加命名空间。此宏将类名转换为使用 Doxygen 生成的 Chrono API 文档的 .html 页面的装饰名称。

- 链接到 Chrono 的 C++ 命名空间: ```\urlChronoAPInamespace```. 
  例如: ```\urlChronoAPInamespace{fea}```
  
- 链接到 Chrono 的 C++ 模块: ```\urlChronoAPImodule```. 传入大写的 Chrono 模块名称。  
  例如: ```\urlChronoAPImodule{FEA}``` 或 ```\urlChronoAPIclass{MATLAB}```。
  
- 使用自定义字体输入 Chrono 名称，使用 ```\Chrono```。

- 使用自定义字体输入 Chrono 名称，并且该名称可以点击链接到 www.projectchrono.org，使用 ```\urlChrono```。
  
## PDF 应该存储在哪里？

生成 PDF 后，可以将其存储在仓库或 FTP 站点中。然后，在 ```chrono\doxygen\documentation\whitepapers``` 目录下的 ```whitepapers.md``` 文件中添加指向你的文档的链接。

<div class="ce-warning">
编译这些白皮书 LaTeX 源文件并未集成在自动的 Doxygen 工具链中，因此由你负责构建、检查交叉链接、上传等工作。
</div>
