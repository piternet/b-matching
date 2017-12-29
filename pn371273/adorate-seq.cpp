#include "blimit.hpp"

#include <iostream>
#include <string>
#include <cstdio>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "usage: "<<argv[0]<<" thread-count inputfile b-limit"<< std::endl;
        return 1;
    }

    int thread_count = std::stoi(argv[1]);
    int b_limit = std::stoi(argv[3]);
    std::string input_filename(argv[2]);

    
    for (int b_method = 0; b_method < b_limit + 1; b_method++) {
        // this is just to show the blimit with which the program is linked
        std::cerr << "bvalue node 44: " << bvalue(b_method, 44) << std::endl;

        // TODO: implement b-adorators here

        // fake result
        std::cout << 42 << std::endl;
    }
}
