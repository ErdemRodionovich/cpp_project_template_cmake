#include <iostream>
#include "configure.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char ** argv){
    std::cout<<"Hello world! MajorVersion="<<ertb::VERSION_MAJOR<<" Minor="<<ertb::VERSION_MINOR<<std::endl;
    return 0;
}