@echo off
:menu
echo.
echo What would you like to do?
echo 1. Run the script
echo 2. Open git_repo_status
echo 3. Quit out of terminal
set /p choice=Enter your choice: 

if "%choice%"=="1" (
    echo Running the script...
    start "" "C:/Users/jhandwer/OneDrive - St. Jude Children's Research Hospital/Programs/Cpp/FindGits/FindGits.exe"
    goto menu
) else if "%choice%"=="2" (
    echo Opening file...
    start "" "C:/Users/jhandwer/OneDrive - St. Jude Children's Research Hospital/Programs/git_repo_status.txt"
    goto menu
) else if "%choice%"=="3" (
    echo Exiting...
    exit
) else (
    echo Invalid choice.
    goto menu
)