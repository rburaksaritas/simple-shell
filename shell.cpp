#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>


int main() {
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);
    std::cout << username << " >>> ";
    return 0;
}