#ifndef GAMEWORLDH
#define GAMEWORLDH

#include <iostream>
#include "../Boxing/Boxing.h"
#include <string>
#include <sstream>

class GameWorld{
private:
    BoWorld world;
    BoEntity *missleEntity;
    BoShape *squareShape;
    
    Vector2 missleStartPos;
public:
    GameWorld(const char* name);
    ~GameWorld();
    
    std::string GetMapInfoInJSON();
    std::string GetSimulationJSON(float shootX, float shootY);
    
};
 
#endif