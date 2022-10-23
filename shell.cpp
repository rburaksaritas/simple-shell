#include <iostream>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// Gets the username of user and anchor >>>.
int printUserName(){
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    std::cout << username << " >>> ";
    return 1;
}

// Gets input command from commandline.
std::string getCommandInput(){
    std::string command;
    std::getline(std::cin, command);
    return command;
}

// Checks if the input command equals to "exit".
// If so, sets isRunning to false in order to stop program. 
int checkExit(std::string command, bool &isRunning){
    std::string exitCommand = "exit";
    if (command == exitCommand){
        isRunning = false;
        return 1;
    }
    return 0;
}

// Prints out the contents of the current directory.
int listdir(){
    system("ls");
    return 1;
}


int main() {
    // Boolean to control the program running state.
    bool isRunning = true;
    
        std::string listdirCommand = "listdir";
        std::string mycomputernameCommand = "mycomputername";
        std::string whatsmyipCommand = "whatsmyip";

    while (isRunning)
    {
        printUserName();
        std::string command = getCommandInput();
        checkExit(command, isRunning);

        if (command == listdirCommand){
            listdir();
        } 
    }
    
    return 0;
}