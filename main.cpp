#include "lib.h"

#include "extra.h"

#include <iostream>

int main (int, char **) {
    std::cout << "Version: " << version() + extra_func() << std::endl; 
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
