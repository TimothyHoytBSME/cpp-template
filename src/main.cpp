
#include "game/game.hpp"

int main(int argc, char** argv){

    if(argc > 1){
        err("Running with ", (argc-1), " args: ");
        bool runtests = false;
        for(int i=1; i<argc; i++){
            std::string arg = argv[i];
            err(arg);
            if(i< argc-1){
                err(", ");
            }
            errl();

            if(arg == "runTests"){
                runtests = true;
            }
        }

        if(runtests){
            runUtilsTests();
        }
    }

    runGame();
    errl("\n\nGame Stopped\n\n");
    enterToExit();
    return 0;
}
