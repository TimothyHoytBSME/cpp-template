#ifndef STORIES_HPP
#define STORIES_HPP

#include "../gamedata.hpp"
#include <cstdint>


inline uint32_t game_intro(){
    uint32_t startAction = 0;
    game.generate();

    while(!game.nameValid()){
        errl();
        game.name = getInputStr("Welcome " + game.name + ", what is your name?");
    }
    
    errl();
    err("Hi, ", game.name, ".");
    errl();
    errl();
    err("  You are in an old deserted house. ");
    err("You just got an email from your friend. ");
    err("He told you the zombie apocalypse has started, and you need to get your family now... ");
    errl("Your phone died, and you believe him. So you rush out the door. ");
    errl("On your way out, you grab an item:");
    errl();
    errl("  1: Lighter, 2: Flashlight, 3: Raincoat, 4: Knife, 5: Rope");
    errl();

    while (!game.startItemValid()){
        game.startItem = getInputUint32_t("Which item?", 1, 5);
    }
    
    int si = game.startItem;
    std::string sistr = game.startItemName();
    err("  You put the ", sistr);
    if(si==1 || si==2 || si==4){
        err(" in your pocket");
    }else if (si==3){
        err(" on");
    }else {
        err(" on your carabiner");
    }
    err(", then leave the house. ");
    err("You had been hiking all day, and are at least 10 miles from town (where your family is). ");
    err("You take off running down the old dirt road. It is 30 minutes before dusk, early spring. ");
    err("The road runs through a wide mountain valley. ");
    errl();
    errl();
    
    err("There are a few clouds in the sky. ");
    game.randomizeWeather();

    game.passTime(20);
    err("You continue to run for a solid 20 minutes, but are starting to lose your breath. ");
    err("You slow to a walk, and take quick inventory. ");
    errl("Of course you have the ", sistr, ", but you also have:");
    errl();
    errl("  Jeans with nylon belt");
    errl("  Long-sleeve shirt");
    errl("  Light hoodie");
    errl("  Small hiking bag");
    errl("  Empty water bottle");
    errl("  Dead phone");
    errl("  Hiking boots");
    errl("  A granola bar");
    errl();

    uint32_t ate = getInputUint32_t("Your stomach starts to growl. Eat the granola? (1:Yes, 2:No)", 1, 2);
    game.ate = (ate == 1);

    if(ate){
        errl("That was tasty, too bad you have no water.");
    }
    
    game.randomizeWeather();
    game.report();

    errl("You could:");
    errl();
    errl("  1: Go back to the house");
    errl("  2: Push on");
    uint32_t lim = 2;
    if(!game.raining && (game.startItem == 1)){
        errl("  3: Make a fire");
        lim = 3;
    }
    errl();

    uint32_t sa = getInputUint32_t("What will you do?", 1, lim);
    startAction = sa;

    if(sa==1){
        err("You reluctantly turn around, ");
        if(game.userWet){
            err("soaked head to toe, ");
        }
        errl("you suddenly realize your situation and decide to get more supplies.");
    }else if(sa==2){
        err("You catch your breath, ");
        if(game.userWet){
            err("soaked head to toe, ");
        }
        errl("you catch your breath and continue onward with a slight jog.");
    }else{
        err("You glance around. It's not raining anymore, so you'll try to make a fire. ");
        if(game.userWet){
            err("Hopefully this lighter works. ");
        }
        
        if(game.userWet){
            err("You start gathering wood. ");
        }
        errl();

        bool fire = game.tryToMakeFire();
        
        if(!fire){
            lim = 2;

            errl("You could:");
            errl();
            errl("  1: Go back to the house");
            errl("  2: Push on");
            //todo try again
            errl();
            sa = getInputUint32_t("What will you do?", 1, lim);
            startAction = sa;

            if(sa==1){
                err("You reluctantly turn around, ");
                if(game.userWet){
                    err("soaked head to toe, ");
                }
                errl("you suddenly realize your situation and decide to get more supplies.");
            }else if(sa==2){
                err("You catch your breath, ");
                if(game.userWet){
                    err("soaked head to toe, ");
                }
                errl("you catch your breath and continue onward with a slight jog.");
            }
        }else{
            lim = 2;
            errl("You could:");
            errl();
            errl("  1: Go back to the house");
            errl("  2: Push on");
            if(game.userWet){
                errl("  3: Dry your cloths");
                lim = 3;
            }
            errl();
            sa = getInputUint32_t("What will you do?", 1, lim);
            startAction = sa;
        }
    }

    return startAction;
}



inline void return_to_house(){
    errl();
    errl("(You are returning to the house.)");
}


inline void push_on(){
    errl();
    errl("(You are pushing on.)");
}

inline void dry_cloths(){
    errl();
    errl("(You are drying your cloths.)");
}   


#endif // end of file