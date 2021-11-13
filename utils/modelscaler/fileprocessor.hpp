#pragma once

#include <string>
#include <vector>

// I like overcomplicating myself

class FileProcessor
{
public:
    std::vector<std::string> filePaths;

    void AddPaths(std::string str); // Adds a string to the filePaths vector.
    void ProcessQCFile(std::string fileName, float scaleMult);

    size_t GetFilePathsSize() { return filePaths.size(); }; // Returns filePaths vector's size
    std::string GetPathFromFilePaths(size_t i) { return filePaths[i]; }; // Returns filePaths vector's element pointer that is at the desired index

};

// Thanks to Evan Teran
// Split string with delimiter
static inline std::vector<std::string> split(const std::string& text, char sep) {
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}