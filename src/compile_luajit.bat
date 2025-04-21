@echo on

CALL "%ProgramFiles%\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
echo %cd%
msvcbuild.bat static amalg