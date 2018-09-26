@echo OFF
setlocal enableExtensions enableDelayedExpansion
set "fixut=%~dps0fixut.exe"
goto START

:Help
echo.
echo. SYNOPSYS
echo.	fix all broken torrent files (*.!ut) in current dir
echo.
echo. REQUIRES:
echo.	fixut.exe (get it from https://github.com/dbat/fixut)
echo.

exit/b

:START
if /i "%~1"=="-h" goto Help
if /i "%~1"=="/?" goto Help
if not exist %fixut% goto Help

for %%f in (*.?ut) do (
  if exist "%%~nf" (
    %fixut% "%%~nf"
  ) else (
    echo. Warning^^! Missing file: "%%~nf"
  )
)
echo.
echo. All done, you can delete all succesfully repaired *ut files
