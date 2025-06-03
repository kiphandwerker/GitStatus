@echo off
echo.
echo What would you like to do?
echo 1. Run the script
echo 2. Open git_repo_status
echo 3. Quit out of terminal
set /p choice=Enter your choice: 

if "%choice%"=="1" (
    echo Running the script...
    start "" "C:/Users/19018/OneDrive/Programs/C/Cpp/Gitstatus/FindGits.exe"
) else if "%choice%"=="2" (
    echo Opening file...
    start "" "C:/Users/19018/OneDrive/Programs/git_repo_status.txt"
) else if "%choice%"=="3" (
    exit
) else (
    echo Invalid choice. Exiting.
)