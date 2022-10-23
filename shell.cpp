#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>


int printUserName(){
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    std::cout << username << " >>> ";
    return 1;
}

std::string getCommandInput(){
    std::string command;
    std::cin >> command;
    return command;
}

int main() {
    bool isRunning = true;
    
    while (isRunning)
    {
        printUserName();
        getCommandInput();
    }
    
    return 0;
}