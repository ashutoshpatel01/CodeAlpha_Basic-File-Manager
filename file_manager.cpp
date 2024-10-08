#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void list_directory(const std::string& path) {
    std::cout << "Listing directory: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << entry.path().string() << std::endl;
    }
}

void view_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filepath << std::endl;
    }
}

void create_directory(const std::string& dirpath) {
    if (fs::create_directory(dirpath)) {
        std::cout << "Directory created: " << dirpath << std::endl;
    } else {
        std::cerr << "Failed to create directory: " << dirpath << std::endl;
    }
}

void copy_file(const std::string& source, const std::string& destination) {
    try {
        fs::copy(source, destination);
        std::cout << "File copied from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void move_file(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    std::string command;
    std::string path, source, destination;

    while (true) {
        std::cout << "\nEnter a command (list, view, create_dir, copy, move, exit): ";
        std::cin >> command;

        if (command == "list") {
            std::cout << "Enter directory path: ";
            std::cin >> path;
            list_directory(path);
        } 
        else if (command == "view") {
            std::cout << "Enter file path: ";
            std::cin >> path;
            view_file(path);
        } 
        else if (command == "create_dir") {
            std::cout << "Enter new directory path: ";
            std::cin >> path;
            create_directory(path);
        } 
        else if (command == "copy") {
            std::cout << "Enter source file path: ";
            std::cin >> source;
            std::cout << "Enter destination path: ";
            std::cin >> destination;
            copy_file(source, destination);
        } 
        else if (command == "move") {
            std::cout << "Enter source file path: ";
            std::cin >> source;
            std::cout << "Enter destination path: ";
            std::cin >> destination;
            move_file(source, destination);
        } 
        else if (command == "exit") {
            break;
        } 
        else {
            std::cout << "Invalid command!" << std::endl;
        }
    }

    return 0;
}
