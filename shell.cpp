#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <fstream>
#include <vector>
#include <algorithm>

/**
 * @author Ramazan Burak Saritas
 * 2020400321
*/

// Gets and prints the username of user followed by anchor >>>.
int printUserName(){
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    std::cout << username << " >>> ";
    return 1;
}

// Gets input command from commandline as string.
std::string getCommandInput(){
    std::string command;
    std::getline(std::cin, command);
    return command;
}

// Parses command input by whitespace.
std::vector<std::string> parseCommandInput(std::string commandInput){
    std::string next;
    std::vector<std::string> result;
    // Iterates each character with const_iterator.
    for (std::string::const_iterator iterator = commandInput.begin(); 
            iterator != commandInput.end(); iterator ++){
        // Adds the token into result vector 
        // if we have characters accumulated 
        // when the iterator hits whitespace.
        if (*iterator == ' '){
            if (!next.empty()){
                result.push_back(next);
                next.clear();
            }
        } 
        // Add next character into the sequence.
        else {
            next += *iterator;
        }
    }
    if (!next.empty()){
        result.push_back(next);
    }
    return result;    
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

// Take a file name as an argument, read its content 
// and write them on the standard output, line by line. 
int printFile(std::string fileName){
    std::string commandLine = std::string("while IFS= read -r line\n") +
        std::string("do\n") + 
        std::string("   echo -en \033[1A\n") +  // Prevent blank lines between lines.
        std::string("   read input </dev/tty\n") + // Enter input.
        std::string("    if [[ -z $input ]]\n") +
        std::string("    then\n") +
        std::string("        echo $line\n") +   // Print line.
        std::string("    fi\n") +
        std::string("done < ") + fileName;
    system(commandLine.c_str());
    return 1;
}

// Takes a file name as an argument, and redirect the standard output
// to a new file using the redirection operator, >, (greater than symbol).
int printFile(std::string sourceFile, std::string newFile){
    // Generates command text "cp (source) (new)" to run on system.
    std::string commandLine = "cp " + sourceFile + " " + newFile;
    system(commandLine.c_str());
    return 1;
}

// Searches a simple command in up to maximum 15 commands 
// that are executed before. The output is a simple "Yes" or "No".
std::string didIDoThat(std::string commandLine, std::vector<std::string> history){
    // Uses find() from <algorithm> library to see if the given command exists in history.
    if (std::find(history.begin(), history.end(), commandLine) != history.end()){
        return "Yes";
    } else{
        return "No";
    }
}

// Opens the default text editor.
int helloText(){
    // Creates a new file named untitled.txt and opens it with default text editor.
    std::string commandLine = "touch untitled.txt\n xdg-open untitled.txt";
    system(commandLine.c_str());
    return 1;
}   

// Main function where the program runs.
int main() {
    // Boolean to control the program running state.
    bool isRunning = true;
    // Vector to store command history.
    std::vector<std::string> history;

    // Command strings to match them with commands.
    std::string listdirCommand = "listdir";
    std::string mycomputernameCommand = "mycomputername";
    std::string whatsmyipCommand = "whatsmyip";
    std::string printfileCommand = "printfile";
    std::string dididothatCommand = "dididothat";
    std::string hellotextCommand = "hellotext";

    // While loop until "exit" command is given.
    // takes input and executes the command in a loop.
    while (isRunning)
    {
        printUserName();
        std::string commandInput = getCommandInput();
        std::vector<std::string> parsedInput = parseCommandInput(commandInput);
        // Sets the command part from the given input command line.
        std::string command = parsedInput[0];
        // Pushes current command line to history as a whole string.
        history.push_back(commandInput);
        // Remove first element of history if the size exceeds 15.
        if (history.size()>15){
            history.erase(history.begin());
        }        
        // Checks if the given commands matches exit command.
        checkExit(command, isRunning);

        // Checks if the given command matches any defined command.
        // Executes related function if it matches.
        if (command == listdirCommand){
            listDir();
        } else if (command == mycomputernameCommand){
            myComputerName(); 
        } else if (command == whatsmyipCommand){
            whatsMyIp();
        } else if (command == printfileCommand){
            // If the printfile has one argument, 
            // executes the printFile with one parameter.
            if (parsedInput.size() == 2){
                std::string fileName = parsedInput[1];
                printFile(fileName);
            // If the command has form printfile (source) > (new), 
            // executes the printFile with two parameters.
            } else if (parsedInput.size() == 4){
                std::string sourceFile = parsedInput[1];
                std::string newFile = parsedInput[3];
                printFile(sourceFile, newFile);
            }
        } else if (command == dididothatCommand){
            // remove dididothat part and quotes from whole input string.
            std::string givenCommand = commandInput.substr(12, commandInput.length()-12);
            // remove last quote.
            givenCommand.pop_back();
            std::cout << didIDoThat(givenCommand, history) << std::endl;
        } else if (command == hellotextCommand){
            helloText();
        } else {
            std::cout << "";
        }
    }
    
    return 0;
}