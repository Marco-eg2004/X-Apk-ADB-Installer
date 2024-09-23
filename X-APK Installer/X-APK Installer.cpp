#include <iostream>
#include <cstdlib>
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<boost/filesystem.hpp>)
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#else
#error "No filesystem support"
#endif

// Function to install APK or XAPK using adb
void installApp(const std::string& filePath) {
    std::string command = "adb install \"" + filePath + "\"";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Successfully installed: " << filePath << std::endl;
    }
    else {
        std::cout << "Failed to install: " << filePath << std::endl;
    }
}

int main() {
    // Get the current directory
    std::string currentDir = fs::current_path().string();

    std::cout << "Looking for APK and XAPK files in: " << currentDir << std::endl;

    // Iterate over the files in the current directory
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        std::string filePath = entry.path().string();

        // Check if the file is an APK or XAPK
        if (filePath.substr(filePath.find_last_of(".") + 1) == "apk" ||
            filePath.substr(filePath.find_last_of(".") + 1) == "xapk") {

            std::cout << "Found: " << filePath << std::endl;
            installApp(filePath);
        }
    }

    // Wait for user input before closing
    system("pause");  // Pause for Windows, can use other methods on Linux/macOS

    return 0;
}
