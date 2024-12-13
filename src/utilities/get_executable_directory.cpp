#include "utilities/get_executable_directory.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

std::filesystem::path get_executable_directory() {
    std::filesystem::path executablePath;

#ifdef _WIN32
    char buffer[MAX_PATH];
    HMODULE hModule = GetModuleHandleA(NULL);
    if (hModule != NULL) {
        GetModuleFileNameA(hModule, buffer, MAX_PATH);
        executablePath = std::filesystem::path(buffer).parent_path();
    }
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '0';
        executablePath = std::filesystem::path(buffer).parent_path();
    }
#endif

    return executablePath;
}

