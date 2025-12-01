
#include "utils/utils.hpp"

int main(int argc, char** argv){
    for(int i=1; i<argc; i++){
        std::string arg = argv[i];
        printl("Arg",i,": ",arg);
    }

    runTests();

    enterToExit();
    flushAll();
    return 0;
}
