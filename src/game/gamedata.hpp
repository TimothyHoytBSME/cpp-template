#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include "../utils/utils.hpp"
#include <cmath>

struct User {
    
};

struct World{
    
    
};

inline struct Game{
    
    std::string name = "Human";
    uint32_t time = 1260; //9PM (21Hrs)
    uint32_t day = 0;
    uint32_t startItem = 0;
    uint32_t temp = 5; //0 to 10 cold to hot
    bool raining = false;
    bool worldWet = false;
    bool userWet = false;
    bool dayTime = true;
    bool sunSetting = false;
    bool sunRising = false;
    bool moonlight = false;
    bool ate = false;

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

    std::string startItemName(){
        return (startItem==1)? "lighter" : (startItem==2)? "flashlight" : (startItem==3)? "raincoat" : (startItem==4)? "knife" : "rope";
    }

    void generate(){
        worldWet = randFloat() >= 0.75f;
        moonlight = randFloat() >= 0.5f;
    }

    void randomizeWeather(){
        bool wasRaining = raining;
        raining = randFloat() > 0.75f;
        if(raining){worldWet = true;}
        
        errl();
        if(wasRaining && !raining){
            errl("The weather has cleared.");
        }else if(!wasRaining && raining){
            errl("It starts raining.");
        }
        
        if(!wasRaining && raining){
            if(startItem==3){
                errl("Good thing you have this raincoat.");
            }else{
                errl("You are wet.");
                userWet = true;
            }
        }
        
        errl();
    }

    void passTime(uint32_t minutes, bool doreport = true){
        time+=minutes;
        while(time > 1440){ //MIDNIGHT
            time -= 1440;
            day++;
        }

        //todo, update temperature?
        float ft = 5.0f - 5.0f*sin(M_2_PI*(float)time / 1440.0f);
        if(raining){
            ft*=0.75f;
        }
        temp = floor(ft);
        if(doreport){report();}
    }
    
    void report(){
        float fh = (float)time * 0.01666666666f;
        uint32_t hrs = floor(fh);
        uint32_t mins = time - 60*hrs;
        bool PM = hrs >= 12;
        if(PM){
            hrs -= 12;
        }

        sunSetting = PM && hrs == 9 && mins < 30;
        sunRising = !PM && hrs == 5 && mins >= 30;
        dayTime = (!PM && hrs>=6) || (PM && (hrs < 9));

        err("It is ", hrs, ":",(mins<10)? "0":"", mins, PM? "PM":"AM", ". ");

        if(sunSetting){
            err("It is almost dark. ");
        }else if (sunRising){
            err("The sun is starting to rise. ");
        }else if (!dayTime){
            err("It is dark outside");
            if(moonlight){
                if(raining){
                    err(", and the clouds block the moonlight. ");
                }else{
                    err(", but the moon is out. ");
                }
            }else{
                err(". ");
            }
        }

        switch(temp){
            case 0:
                err("It is freezing outside. ");
                break;
            case 1:
                err("It is unbearably cold outside. ");
                break;
            case 2:
                err("It is unpleasantly cold outside. ");
                break;
            case 3:
                err("It is kind of chilly outside. ");
                break;
            case 7:
                break;
                err("It is a bit warm outside. ");
            case 8:
                break;
                err("It is hot outside. ");
            case 9:
                break;
                err("It is unbearably hot outside. ");
            case 10:
                break;
                err("It is dangerously hot outside. ");
            default:
                err("Temperature: ", temp, "/10");
                break;
        }
        errl(); errl();
    }

    inline bool tryToMakeFire(){
        bool haslighter = startItem == 1;
        if(!haslighter) return false;
        bool lighterwet = userWet;
        float odds = 0.9f - lighterwet*0.3f - worldWet*0.4f;
        bool fire = randFloat() < odds;
        if(fire){
            errl("You have made a nice fire.");
        }else{
            errl("You can't seem to get this fire going.");
        }
        passTime(30);
        return fire;
    }
} game;


#endif // end of file