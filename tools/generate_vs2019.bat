@echo off
echo Updating submodules...
git submodule update --init --remote --recursive
echo Generating project files...
call "premake5.exe" vs2019 --file=premake.lua