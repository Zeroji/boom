#include <iostream>
#include "Client.hpp"

int main() {
    std::cout << "Hello, World! [BOOM]" << std::endl;
    Client client;
    client.run();
    return 0;
}
