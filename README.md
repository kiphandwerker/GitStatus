# Git Repository Status Scanner

This C++ utility recursively scans a specified directory to detect local Git repositories, identify whether they are linked to GitHub, and check their sync status with the upstream remote (e.g., whether they are ahead, behind, or up to date).

It outputs the results grouped by the first-level subfolder into a formatted `git_repo_status.txt` report.

## Features

- Recursively searches through a specified root directory for Git repositories.
- Detects whether each repository is connected to GitHub.
- Runs Git commands to determine:
  - If the repository is up to date
  - If it is ahead or behind the remote
  - If it has diverged or has no upstream
- Outputs results grouped by project or folder
- Saves the report to a `git_repo_status.txt` file

### Prerequisites

- Windows environment (uses `cd /d` and `_popen`)
- Git installed and available in PATH
- C++17 or later (uses `<filesystem>`)


### Code highlights
- Git Command Execution: Uses `_popen` to execute Git commands within each repository.

- Status Detection: Compares local HEAD, upstream HEAD, and merge-base to determine sync status.

- GitHub Detection: Parses `.git/config` to look for "github.com".

- Formatted Output: Results are grouped and formatted using `std::setw` for alignment.

### Limitations
- Currently works only on Windows due to cd /d and _popen usage.

- Assumes that Git is installed and configured properly on the system.

- Only supports checking one root directory at a time.

## Usage
<ol>
<li>Replace the path with the directory you'd like to search through

```c
    std::vector<std::string> searchRoots = {
        "path/goes/here"
    };
```
Note: git_repo_status.txt will be created at the start of the search root.

<li>Use a C++17-compatible compiler. Example with g++:

```bash
g++ -std=c++17 -o main FindGits.cpp
```
## Optional
- Create a .bat file so that you can easily run the .exe file

```bash
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
    start "" "path/to/FindGits.exe"
    goto menu
) else if "%choice%"=="2" (
    echo Opening file...
    start "" "path/to/git_repo_status.txt"
    goto menu
) else if "%choice%"=="3" (
    echo Exiting...
    exit
) else (
    echo Invalid choice.
    goto menu
)
```

</ol>