#include "CLI11.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv) { // Standard main function
    CLI::App app{"App description"};

    int p = 0;
    app.add_option("-p,--parameter", p, "Parameter description");

    try {
        app.parse(argc, argv); // Explicitly call parse
    } catch (const CLI::ParseError &e) {
        // Handle errors explicitly
        return app.exit(e);
    }

    // Use parsed value
    std::cout << "Parameter value: " << p << std::endl;

    return 0;
}
