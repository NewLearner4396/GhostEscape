#include <iostream>
#include <filesystem>
#include "game.h"

int main(int , char **)
{
    // // output the current working directory
    // std::filesystem::path currentPath = std::filesystem::current_path();
    // std::cout << "Current path: " << currentPath << std::endl;
    // // update the parent path as current path and working directory
    // std::filesystem::path parentPath = currentPath.parent_path();
    // std::filesystem::current_path(parentPath);
    // std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    std::cout << "This a simple game for you to have fun!" << std::endl;

    Game& game = Game::getInstance();
    game.init("GhostEscape", 1280, 720);
    game.run();

    std::cout << "Happy Game!" << std::endl;
    return 0;
}
