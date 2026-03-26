使用 Doxygen 为代码编写文档 {#tutorial_doxygen}
==========================

## 参考链接

[Doxygen Manual](https://www.stack.nl/~dimitri/doxygen/manual/)

## 安装 doxygen

### Windows:
推荐的安装 doxygen 的方式是使用 [chocolatey](https://chocolatey.org/)。首先按照 chocolatey 的安装说明进行安装，然后运行

~~~shell
choco install doxygen.install -y
~~~

### Linux

通过您喜欢的软件包管理器安装 ```doxygen```

### OSX

使用 homebrew 安装 doxygen

~~~shell
brew install doxygen
~~~

## 构建文档

文档位于主 chrono 仓库的 `doxygen` 文件夹中。要构建文档，请在此目录中运行 `doxygen` 命令。默认情况下，文档将构建在 `/tmp/chrono_doxygen` 中。要更改输出目录，请编辑文件 `Doxyfile` 并更改变量 `OUTPUT_DIRECTORY`。

下面的说明还提到了旧的基于 MediaWiki 的 Chrono 文档中的相应语法。

### 链接

MediaWiki 中的链接 `[http://www.povray.org POVray]` 在 markdown 中变为 `[POVray](http://www.povray.org)`

### 在 doxygen 中引用页面

如果页面以以下内容开头

~~~markdown
About Chrono::Solidworks
==========================
~~~

在标题中，您可以使用 `@ref` 命令引用它

~~~markdown
[Chrono::SolidWorks](@ref manual_chrono_solidworks)
~~~

### 标题

在 mediawiki 中，`===` 指定标题，在 markdown 中，`###` 指定标题，井号越多，标题级别越低。<br>
示例：`=== Create a column ===` 变为 `### Create a column`

### 图片

图片必须位于 documentation/images/ 文件夹中，才能被 doxygen 识别。如果您想添加更多文件夹，请修改 `Doxyfile` 中的 `IMAGE_PATH             = documentation/images/` 设置。

图片可以按如下方式添加：

~~~markdown
![](http://projectchrono.org/assets/manual/SWaddin.jpg)
~~~

### 转换 Details 块

Wiki 中的文本：

~~~wiki
{{Details|content=
We suggest to install also the following third party packages for expanding the capabilities of Python in mathematical ad plotting areas:
* [http://numpy.scipy.org/ Numpy]
* [http://matplotlib.sourceforge.net/ Matplotlib].

NOTE. Precompiled binaries of Numpy and Matplotlib for Python 3.2 can be downloaded  from the unofficial [http://www.lfd.uci.edu/~gohlke/pythonlibs/ repository]. A faster option is to install the entire [http://www.lfd.uci.edu/~gohlke/pythonlibs/#scipy-stack SciPy stack] that includes both.
Otherwise there is a custom Python distribution called [http://enthought.com/products/epd.php Enthough] that already includes the two packages.
}}
~~~

变为：

~~~html
<div class=well>
We suggest to install also the following third party packages for expanding the capabilities of Python in mathematical ad plotting areas:
* [http://numpy.scipy.org/ Numpy]
* [http://matplotlib.sourceforge.net/ Matplotlib].

NOTE. Precompiled binaries of Numpy and Matplotlib for Python 3.2 can be downloaded  from the unofficial [repository](http://www.lfd.uci.edu/~gohlke/pythonlibs/). A faster option is to install the entire [stack](http://www.lfd.uci.edu/~gohlke/pythonlibs/#scipy-stack SciPy) that includes both.
Otherwise there is a custom Python distribution called [Enthough](http://enthought.com/products/epd.php) that already includes the two packages.
</div>
~~~

这是另一个例子：

~~~wiki
{{Details|content=
The files for this demo can be found in the directory ''C:\Documents\chrono\src\demos\mbs''. The directory contains all the sources needed for this example.
}}
~~~

以及应放入Markdown中的代码块

~~~markdown
<div class=well>
The files for this demo can be found in the directory ```C:\Documents\chrono\src\demos\mbs``` . The directory contains all the sources needed for this example.
</div>
~~~

对于旁边带有符号的注释，使用以下代码块：

~~~html
<span class="label label-success"><span class="glyphicon glyphicon-check"></span></span>

<span class="label label-info"><span class="glyphicon glyphicon-info-sign"></span></span>

<span class="label label-warning"><span class="glyphicon glyphicon-warning-sign"></span></span>

<span class="label label-danger"><span class="glyphicon glyphicon-exclamation-sign"></span></span>
~~~

对于较长的注释（可能为多行）且旁边带有符号，请使用以下代码块：

<div class="ce-info">
This is an info
</div>

<div class="ce-warning">
This is a warning
</div>

<div class="ce-danger">
This is a danger
</div>

~~~html

<div class="ce-info">
This is an info
</div>

<div class="ce-warning">
This is a warning
</div>

<div class="ce-danger">
This is a danger
</div>
~~~

### 代码块

~~~wiki
<source lang="py">
brick_material = chrono.ChContactMaterialNSC()
brick_material.SetFriction(0.6)
brick_material.SetDampingF(0.05)
brick_material.SetCompliance (0.00003)
brick_material.SetComplianceT(0.00001)
</source>
~~~

变为

~~~python
brick_material = chrono.ChContactMaterialNSC()
brick_material.SetFriction(0.6)
brick_material.SetDampingF(0.05)
brick_material.SetCompliance (0.00003)
brick_material.SetComplianceT(0.00001)
~~~

### 强调

把引号改成双星号

~~~wiki
''but it won't produce any collisions yet!''
~~~

~~~markdown
**but it won't produce any collisions yet!**
~~~

### 列表

~~~wiki
*First, start SolidWorks.

*Use menu File/New... and create a new Part.

*In the Part editor, create a doric column (like those that you can find in Greek temples) by using the [[File:Tutorial_collshapes_01.jpg]] '''Revolved boss / base''' tool in the toolbar. (Just create a profile like a rectangle, where one of the vertical sides is rather an almost flat arc, and the opposite side is the axis of revolution).

*You should obtain this:
~~~

变为（空格很重要！）

~~~markdown
* First, start SolidWorks.
* Use menu File/New... and create a new Part.
* In the Part editor, create a doric column (like those that you can find in Greek temples) by using the [[File:Tutorial_collshapes_01.jpg]] '''Revolved boss / base''' tool in the toolbar. (Just create a profile like a rectangle, where one of the vertical sides is rather an almost flat arc, and the opposite side is the axis of revolution).
* You should obtain this:
~~~

### 链接到源文件中的内容

~~~markdown
Creating A Powertrain In Chrono (demo_powertrain.cpp) {#tutorial_demo_powertrain}
==========================

\verbinclude demo_powertrain.cpp
~~~
