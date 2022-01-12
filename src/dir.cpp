#include "filesystem"
#include "string"

std::string GetExecutableDirectory() {
    return std::filesystem::current_path().std::filesystem::path::parent_path();
}
