# Coral Extensible Software Interface

# 中文

## 简介

一款软件引导接口/启动器，将多个程序集中于一款软件接口管理。

作为通用的引导平台在开机时注册或启动程序，尤其是在装有还原的系统中，将本程序底层驱动在还原关闭时注入系统，并将软件文件放入非还原盘，之后仅需通过改变非还原盘上的文件即可增删软件或更改系统，一劳永逸。

**请注意:** 本软件仅为通过其他手段达到安装软件的效果并简化操作，而并不是直接突破还原限制，且本软件的底层程序需要关闭还原才可安装。

## 功能及使用说明

### CESI_entrypoint

CESI 的启动接入点，进行自检并启动子功能等。

在同级文件夹下放置名为 `DISABLE` 的空文件即可关闭 CESI 的所有功能。

### CESI_run

按顺序执行 `CESI_run.manifest` 中的命令行，`CESI_run.manifest` 格式如下：

```
C:\Windows\System32\notepad.exe
C:\Windows\System32\cmd.exe /c echo Hello
CESI_EOF_MARK
```

必须以 `CESI_EOF_MARK` 结尾且不得有空行。

### CESI_install

提供一系列操作选项以安装软件，支持的操作如下：

- `COPY|[source absolute/relative path]|[destination folder absolute path][type=Folder/File]`
- ~~`REG|[ADD/CHG/DEL]|[RootKey]|[Path]|[KeyName]|[ValueName][ValueType=REG_SZ/REG_DWORD]`~~(暂未开发完毕)
- `RUN|[file absolute/relative path]|[WAIT(optional)]`
- `EXEC|[file absolute/relative path]|[parameters]|[SHOW|HIDE]`
- `CMD|[command]|[WAIT(optional)]`
- `KEY|[action=Press/Down/Up]|[KeyValue]`
- `SLEEP|[millisecond]`

请将某个软件相关文件存储在 `CESI_install` 的子文件夹中，并在 `CESI_install.manifest` 中添加子文件夹名，同样地，该文件必须以 `CESI_EOF_MARK` 结尾且不得有空行。

在子文件夹中还需要配置 `CESI_INSTALL_LIST` 清单文件，该文件必须以 `CESI_INSTALL_LIST_FORMATVERSION_1` 开头并以 `CESI_EOF_MARK` 结尾，不得有空行或多余空格，清单中的命令可以为上述四条命令，请严格以 `|` 作为分隔符且分隔符左右不得有多余空格，除了 `CMD` 和 `RUN` 选项外文件中的路径不需要额外用引号包裹。注释可以以 `#` 开头添加至文件中。请参考 `TemplateInstallationFolder` 中的 `CESI_INSTALL_LIST.template` 文件。

值得注意的是我们在该 `.template` 文件下方添加了一些以 `//` 开头的注释，理论上 `CESI_EOF_MARK` 标志下方的行不会被 CESI 读取，但我们仍强烈建议您在使用时删去这些注释以及空行。

> RUN 与 EXEC 的区别：
>
> RUN 与 EXEC 选项都可以运行一个可执行文件，前者更偏向于在自身运行环境中新运行一个进程，并且可以选择 CESI 是否等待该进程运行结束；后者更偏向于“激活”一个外部程序，CESI 只激活而无法参与程序的后续操作，并且后者可以额外设置程序运行时窗体显示或隐藏。从底层实现上来说，RUN 选项使用 `CreateProcess` 方法而 EXEC 使用 `ShellExecute` 方法。

## 安装

*目标平台为 Windows，目前暂无支持其他系统的计划。*

*以下所有操作请均以**管理员身份**进行*

1. 关闭还原功能。
2. 执行 `Compile.bat` 文件，请确保系统环境中存在 `g++`，推荐使用 `TDM-GCC 9.2` 编译器进行编译。
3. 执行 `Set CESI Startup (sc).bat` 或 `Set CESI Startup (reg).bat`，推荐使用前者，前者采用系统服务的方式注册开启自启，后者采用普通应用的方式注册，可能会导致开机命令行闪现。
4. 开启还原功能并重启，完成。

> 需要根据实际需求或文件路径修改的内容：
>
> `Set CESI Startup (sc).bat` 或 `Set CESI Startup (reg).bat`
>
> `CESI_run\CESI_run.manifest`
>
> `CESI_install\CESI_install.manifest`
>
> `CESI_install` 文件夹中的子文件夹，即软件的安装文件；以及子文件中的 `CESI_INSTALL_LIST` 文件，即 CESI 安装该软件的任务流程。