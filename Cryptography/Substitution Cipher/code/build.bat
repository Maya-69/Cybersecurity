@echo off
setlocal enabledelayedexpansion

:: Set up MSVC environment
call "D:\Microsoft Visual Studio\Ide\VC\Auxiliary\Build\vcvars64.bat"

if "%~1" == "" (
    echo Usage: build.bat filename[.cpp]
    exit /b 1
)

set "SRC=%~1"
for %%f in ("%SRC%") do set "NAME=%%~nf"

set "OUTDIR=build\%NAME%"
if not exist build mkdir build
if not exist "%OUTDIR%" mkdir "%OUTDIR%"

pushd "%OUTDIR%"
:: Compiling
cl /Zi /EHsc "..\..\%SRC%" /Fe:"%NAME%.exe"
if errorlevel 1 (
    echo Build failed!
    popd
    exit /b 1
)
echo Build successful: %NAME%.exe in %OUTDIR%
popd