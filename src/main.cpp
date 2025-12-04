
#include "utils/logging.hpp"
#include "utils/utils.hpp"
#include <regex>


int main(int argc, char** argv){
    struct UserData {
        std::string name = "Human";
        unsigned int startItem = 0;
        bool nameValid(){
            if(name == "Human") return false;
            std::regex pattern("^(?=.*[a-zA-Z0-9])[a-zA-Z0-9 ]+$");
            if(!std::regex_match(name, pattern)) return false;
            return true;
        }
        bool startItemValid(){
            if(startItem == 0 || startItem > 5) return false;
            return true;
        }

    } userData;

    for(int i=1; i<argc; i++){
        std::string arg = argv[i];
        printl("Arg",i,": ",arg);
    }

    while(!userData.nameValid()){
        userData.name = getInputStr("\nWelcome " + userData.name + ", what is your name?");
    }

    err("\nHi, ", userData.name, ".\n\n  You are in an old deserted house. ");
    err("You just got an email from your friend. ");
    err("He told you the zombie apocalypse has started, and you need to get your family now.. ");
    err("Your phone died, and you believe him. So you rush out the door. ");
    errl("On your way out, you grab an item:\n");
    
    errl("  1: Lighter, 2: Flashlight, 3: Raincoat, 4: Knife, 5: Rope\n");

    while (!userData.startItemValid()){
        userData.startItem = getInputUint32_t("Which item?", 1, 5);
    }

    int si = userData.startItem;
    err("  You put the ", (si==1)? "lighter" : (si==2)? "flashlight" : (si==3)? "raincoat" : (si==4)? "knife" : "rope");
    if(si==1 || si==2 || si==4){
        err(" in your pocket");
    }else if (si==3){
        err(" on");
    }else {
        err(" on your carabiner");
    }
    err(", then leave the house. ");
    err("You had been hiking all day, and are miles from town (where your family is). ");
    err("You take off running down the old dirt road. It is about 10:00 AM, early spring. ");





    // runTests();
    enterToExit();
    return 0;
}
