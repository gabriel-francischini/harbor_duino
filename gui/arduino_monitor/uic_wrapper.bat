@echo off
SetLocal EnableDelayedExpansion
(set PATH=C:\qt-everywhere-opensource-src-5.6.0\qtbase\lib;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=C:\qt-everywhere-opensource-src-5.6.0\qtbase\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=C:\qt-everywhere-opensource-src-5.6.0\qtbase\plugins
)
C:\qt-everywhere-opensource-src-5.6.0\qtbase\bin\uic.exe %*
EndLocal
