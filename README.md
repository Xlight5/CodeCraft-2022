# Readme

## 编译

```shell
# pwd : xxx/CodeCraft-2022
mkdir build
cd build/
cmake ../src/
```

## 运行

编译之后可执行程序位于 bin 目录下，可直接运行。
.vscode 下的 luanch.json 提供了使用 vscode 运行程序的方式。

## 打包

打包需在 `xxx/CodeCraft-2022` 上级进行，使用打包脚本,如下所示:

```shell
#!/bin/bash
# packing.sh
SCRIPT=$(readlink -f "$0")
BASEDIR=$(dirname "$SCRIPT")
cd $BASEDIR

if [ ! -d CodeCraft-2022 ]
then
    echo "ERROR: $BASEDIR is not a valid directory of SDK_C++ for CodeCraft-2022."
    echo "  Please run this script in a regular directory of SDK_C++."
    exit -1
fi

rm -f CodeCraft-2022.zip
zip -r CodeCraft-2022.zip CodeCraft-2022
```

## 程序说明

### 运行状态

程序运行在两种模式下 Debug 或 Release, Debug 时程序需要额外的一个额外的输入参数，即为本项目路径，详细可以看下 launch.json 中的 arg 字段。
可以通过 `CMakeLists.txt` 中的 `CMAKE_BUILD_TYPE` 进行切换。

### 测试数据

为了方便程序的调试，将官方的 data 数据集迁移至本项目中，以便程序调试。

## 官方资料

[2022华为软件精英挑战赛](https://competition.huaweicloud.com/codecraft2022)
[赛题相关材料链接](https://bbs.huaweicloud.com/forum/thread-180679-1-1.html)
