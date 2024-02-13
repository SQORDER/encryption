#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
void encryptFile(const std::string& filename, const std::string& password) {
    std::ifstream inputFile(filename, std::ios::binary);
    std::ofstream outputFile(filename + ".bin", std::ios::binary);
    if (inputFile && outputFile) {
        char ch;
        std::size_t passwordIndex = 0;
        while (inputFile.get(ch)) {
            ch = ch ^ password[passwordIndex];
            outputFile.put(ch);

            passwordIndex = (passwordIndex + 1) % password.length();
        }
        std::cout << "File " << filename << " successfully encrypted!" << std::endl;
    } else {
        std::cout << "ERROR OPEN FILE!" << std::endl;
    }
}
void decryptFile(const std::string& filename, const std::string& password) {
    std::ifstream inputFile(filename, std::ios::binary);
    std::ofstream outputFile(filename.substr(0, filename.size() - 4), std::ios::binary);
    if (inputFile && outputFile) {
        char ch;
        std::size_t passwordIndex = 0;
        while (inputFile.get(ch)) {
            ch = ch ^ password[passwordIndex];
            outputFile.put(ch);

            passwordIndex = (passwordIndex + 1) % password.length();
        }
        std::cout << "File " << filename << " successfully decrypted!" << std::endl;
    } else {
        std::cout << "ERROR OPEN FILE!" << std::endl;
    }
}
int main() {
    std::cout << "Select method to use (E - encrypt, D - decrypt): ";
    char mode;
    std::cin >> mode;
    if (mode == 'E' || mode == 'e') {
        std::string password;
        std::cout << "Enter Password: ";
        std::cin >> password;
        std::filesystem::path resourceDir("resource");

        if (std::filesystem::exists(resourceDir) && std::filesystem::is_directory(resourceDir)) {
            for (const auto& entry : std::filesystem::directory_iterator(resourceDir)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().string();
                    encryptFile(filename, password);
                }
            }
        } else {
            std::cout << "ERROR: 'resource' not found!" << std::endl;
        }
    } else if (mode == 'D' || mode == 'd') {
        std::string password;
        std::cout << "Enter Password: ";
        std::cin >> password;
        std::filesystem::path resourceDir("resource");
        if (std::filesystem::exists(resourceDir) && std::filesystem::is_directory(resourceDir)) {
            for (const auto& entry : std::filesystem::directory_iterator(resourceDir)) {
                if (entry.is_regular_file()) {
                    std::string filename = entry.path().string();
                    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".bin") {
                        decryptFile(filename, password);
                    }
                }
            }
        } else {
            std::cout << "ERROR: 'resource' not found!" << std::endl;
        }
    } else {
        std::cout << "Error method use!" << std::endl;
    }
    return 0;
}
