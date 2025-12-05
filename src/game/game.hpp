#ifndef GAME_HPP
#define GAME_HPP

#include "stories/stories.hpp"


inline void runGame(){

    switch(game_intro()){
        case 1:
            return_to_house();
            break;
        case 2:
            push_on();
            break;
        case 3:
            dry_cloths();
            break;
        default:
            push_on();
            break;
    }
}

#endif // end of file