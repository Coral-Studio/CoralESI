# Coral Extensible Software Interface

# 中文

## 简介

一款软件引导接口/启动器，将多个程序集中于一款软件接口管理。

作为通用的引导平台在开机时注册或启动程序，尤其是在装有还原的系统中，将本程序底层驱动在还原关闭时注入系统，并将软件文件放入非还原盘，之后仅需通过改变非还原盘上的文件即可增删软件或更改系统，一劳永逸。

**请注意：** 本软件仅是通过其他手段达到安装软件的效果并简化操作，并不是直接突破还原限制，且本软件的底层程序需要关闭还原才可安装。

## 功能及使用说明

1. CESI_entrypoint:

   CESI 的启动接入点，进行自检并启动子功能等。

   在同级文件夹下放置名为 `DISABLE` 的空文件即可关闭 CESI 的所有功能。
2. CESI_run:

   按顺序启动 `CESI_run.manifest` 中的软件，`CESI_run.manifest` 格式如下：

   ```
   C:\Windows\System32\notepad.exe
   C:\Windows\System32\cmd.exe|echo Hello
   CESI_EOF_MARK
   ```

   其中第一行示例为仅运行软件，第二行示例为运行软件并且设置命令行参数。
   必须一行一条命令，必须使用 `|` 作为软件路径与命令行参数的分隔符且分隔符周围不得有任何多余空格，必须使用绝对路径（未来考虑支持相对路径），必须使用 `CESI_EOF_MARK` 作为清单文件的终止符。

## 安装

*目标平台为 Windows，目前暂无支持其他系统的计划。*

*以下所有操作请均以**管理员身份**进行*

1. 关闭还原功能。
2. 执行 `Compile.bat` 文件，请确保系统环境中存在 `g++`，推荐使用 `TDM-GCC 9.2` 编译器进行编译。
3. 执行 `Set CESI Startup (sc).bat` 或 `Set CESI Startup (reg).bat`，推荐使用前者，前者采用系统服务的方式注册开启自启，后者采用普通应用的方式注册，可能会导致开机命令行闪现。
4. 开启还原功能并重启，完成。

> 需要根据实际需求或文件路径修改的内容：
> `Set CESI Startup (sc).bat` 或 `Set CESI Startup (reg).bat`
> `CESI_run\CESI_run.manifest`

# English

*Translated by GPT*
*Please note: Updates to the English version of this readme may not be real-time.*

## Introduction

A software boot interface/launcher that centralizes multiple programs under a single software interface management.

As a universal boot platform for registering or launching programs at startup, especially useful in systems with restore capabilities, this program injects its underlying drivers into the system when restore is disabled, and places software files on a non-restored disk. Thereafter, software can be added, deleted, or system changes made simply by modifying files on the non-restored disk, providing a permanent solution.

**Please note:** This software achieves software installation through alternative means to simplify operations, rather than directly bypassing restore restrictions. The underlying program of this software requires restore to be disabled for installation.

## Features and Usage Instructions

1. CESI_entrypoint:

   CESI's startup entry point performs self-checks and initiates sub-functions.

   Place an empty file named `DISABLE` in the same folder to disable all CESI functionalities.
2. CESI_run:

   Sequentially launches software listed in `CESI_run.manifest`. The format of `CESI_run.manifest` is as follows:

   ```
   C:\Windows\System32\notepad.exe
   C:\Windows\System32\cmd.exe|echo Hello
   CESI_EOF_MARK
   ```

   The first line runs the software only, while the second line runs the software with command line parameters. Each command must be on a separate line, use `|` as the separator between the software path and command line parameters without any additional spaces around the separator, and must use absolute paths (with future consideration for relative paths). Use `CESI_EOF_MARK` as the termination marker for the manifest file.

## Installation

*Target platform is Windows; there are currently no plans to support other systems.*

*Perform all operations below with **administrator privileges**.*

1. Disable restore functionality.
2. Run the `Compile.bat` file. Ensure that the environment `g++` command line is set up. It is recommended to use the `TDM-GCC 9.2` compiler for compilation.
3. Run either `Set CESI Startup (sc).bat` or `Set CESI Startup (reg).bat`. The former registers and starts CESI as a system service for startup, while the latter registers CESI as a regular application, which may cause a brief command line flash during startup.
4. Enable restore functionality and restart to complete the process.

> Modify the following according to actual needs or file paths:
> `Set CESI Startup (sc).bat` or `Set CESI Startup (reg).bat`
> `CESI_run\CESI_run.manifest`
