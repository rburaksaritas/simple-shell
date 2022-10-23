#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <fstream>

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
int listDir(){
    system("ls");
    return 1;
}

// Prints the given name of the used device.
int myComputerName(){
    char hostname[HOST_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    std::cout << hostname << std::endl;
    return 1;
}

// Prints out the current ip adress.
int whatsMyIp(){
    system("hostname -I");
    return 1;
}

// Main function where the program runs.
int main() {
    // Boolean to control the program running state.
    bool isRunning = true;
    
        std::string listdirCommand = "listdir";
        std::string mycomputernameCommand = "mycomputername";
        std::string whatsmyipCommand = "whatsmyip";
        std::string printfileCommand = "printfile";

    // While loop until "exit" command is given.
    // takes input and executes the command in a loop.
    while (isRunning)
    {
        printUserName();
        std::string command = getCommandInput();
        checkExit(command, isRunning);

        if (command == listdirCommand){
            listDir();
        } else if (command == mycomputernameCommand){
            myComputerName(); 
        } else if (command == whatsmyipCommand){
            whatsMyIp();
        }
    }
    
    return 0;
}