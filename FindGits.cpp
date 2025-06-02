#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>
#include <array>

namespace fs = std::filesystem;

struct RepoInfo {
    std::string folderPath;
    bool isGitHubRepo;
    std::string gitStatus;
};

std::string runGitCommand(const fs::path& repoPath, const std::string& cmd) {
    std::string command = "cd /d \"" + repoPath.string() + "\" && git " + cmd + " 2>nul";
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) return "";
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        result += buffer.data();
    }
    _pclose(pipe);
    result.erase(result.find_last_not_of(" \n\r\t") + 1);
    return result;
}

bool containsGitHub(const fs::path& configPath) {
    std::ifstream configFile(configPath);
    std::string line;
    while (std::getline(configFile, line)) {
        if (line.find("github.com") != std::string::npos) {
            return true;
        }
    }
    return false;
}

std::string getGitStatus(const fs::path& repoPath) {
    std::string fetch = runGitCommand(repoPath, "fetch");
    std::string local = runGitCommand(repoPath, "rev-parse HEAD");
    std::string remote = runGitCommand(repoPath, "rev-parse HEAD@{u}");
    std::string base = runGitCommand(repoPath, "merge-base HEAD HEAD@{u}");

    if (local.empty() || remote.empty() || base.empty()) {
        return "Error or no upstream";
    }

    if (local == remote) return "Up to date";
    if (local == base) return "Behind";
    if (remote == base) return "Ahead";
    return "Diverged";
}

int main() {
    std::vector<std::string> searchRoots = {
        "C:/Users/jhandwer/OneDrive - St. Jude Children's Research Hospital/Programs/"
    };
    std::vector<RepoInfo> results;


    std::filesystem::path statusFile = std::filesystem::path(searchRoots[0]) / "git_repo_status.txt";

    std::ofstream outputFile(statusFile);

    
    if (!outputFile) {
        std::cerr << "Failed to open output file.\n";
        return 1;
    }

    for (const auto& root : searchRoots) {
        fs::path startPath(root);

        if (!fs::exists(startPath)) {
            std::cout << "Path not found: " << startPath << std::endl;
            continue;
        }

        std::cout << "Scanning " << startPath << " ..." << std::endl;

        try {
            for (const auto& dirEntry : fs::recursive_directory_iterator(startPath, fs::directory_options::skip_permission_denied)) {
                if (!dirEntry.is_directory()) continue;

                fs::path fullPath = dirEntry.path();
                fs::path gitPath = fullPath / ".git";
                fs::path configPath = gitPath / "config";

                if (fs::exists(gitPath)) {
                    bool isGitHub = fs::exists(configPath) && containsGitHub(configPath);
                    std::string status = getGitStatus(fullPath);

                    // Group based on first folder relative to root
                    fs::path relative = fs::relative(fullPath, startPath);
                    std::string groupName = relative.empty() ? fullPath.string() : (startPath / *relative.begin()).string();

                    results.push_back({ fullPath.string(), isGitHub, status });
                }
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error scanning " << startPath << ": " << ex.what() << std::endl;
        }
    }

    // Display grouped results by first-level subfolder under startPath
    std::map<std::string, std::vector<RepoInfo>> grouped;
        for (const auto& info : results) {
        fs::path fullPath(info.folderPath);
        fs::path relative = fs::relative(fullPath, searchRoots[0]);
        std::string groupName;

        if (!relative.empty()) {
            groupName = relative.begin()->string();  // First folder under startPath
        } else {
            groupName = ".";  // Root itself
        }

        grouped[groupName].push_back(info);
    }

    for (const auto& [group, repos] : grouped) {
        // std::cout << "\nGroup: " << group << "\n";
        outputFile << "\nGroup: " << group << "\n";

        for (const auto& repo : repos) {
            outputFile << "  Path: " << repo.folderPath
                    << "\n  GitHub: " << (repo.isGitHubRepo ? "Yes" : "No")
                    << "\n  Status: " << repo.gitStatus << "\n";
        }
    }
    std::cout << "Git Status file written" << "\n";

    return 0;
}
