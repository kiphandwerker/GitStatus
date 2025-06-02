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


## Usage

### Prerequisites

- Windows environment (uses `cd /d` and `_popen`)
- Git installed and available in PATH
- C++17 or later (uses `<filesystem>`)

### Compile

Use a C++17-compatible compiler. Example with g++:

```bash
g++ -std=c++17 -o main FindGits.cpp
```

### Code highlights
- Git Command Execution: Uses `_popen` to execute Git commands within each repository.

- Status Detection: Compares local HEAD, upstream HEAD, and merge-base to determine sync status.

- GitHub Detection: Parses `.git/config` to look for "github.com".

- Formatted Output: Results are grouped and formatted using `std::setw` for alignment.

### Limitations
- Currently works only on Windows due to cd /d and _popen usage.

- Assumes that Git is installed and configured properly on the system.

- Only supports checking one root directory at a time.