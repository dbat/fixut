@echo OFF
setlocal enableExtensions enableDelayedExpansion
set "fixut=%~dps0fixut.exe"
goto START

:Help
echo.
echo. SYNOPSYS:
echo.	fix all broken torrent files (*.^^!ut) in current dir
echo.
echo. USAGE:
echo. 	%~n0 [ -d ]
echo. 	-d or /d: (optional) delete *.^^!ut files after fix
echo.
echo. REQUIRES:
echo.	fixut.exe (get it from https://github.com/dbat/fixut)
echo.
echo. NOTES:
echo. 	Windows XP+
echo.

exit/b

:START
if /i "%~1"=="/?" goto Help
if /i "%~1"=="-?" goto Help
if /i "%~1"=="-h" goto Help
if /i "%~1"=="--help" goto Help
if not exist %fixut% goto Help

set "DELUT="
if /i "%~1"=="/d" set "DELUT=1"
if /i "%~1"=="-d" set "DELUT=1"

set "CTR=0"
for %%f in (*.^^!ut) do (
  if exist "%%~nf" (
    %fixut% "%%~nf"
    if "%DELUT%"=="1" del "%%~nf.^!ut"
    set /a "CTR=!CTR!+1"
  ) else (
    echo. Warning^^! Missing file: "%%~nf"
  )
)
echo.
set "FILES1=files"
if "%CTR%"=="1" set "FILES1=file"
if %CTR% gtr 0 (
  echo. All done, %CTR% %FILES1% processed
  if not "%DELUT%"=="1" echo. You can delete all succesfully repaired *.^^!ut files
) else (
  echo. No matching files
)
pause
