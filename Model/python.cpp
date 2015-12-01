
#include "gameworld.h"
#include <boost/python.hpp>


char const* getmapinfo(){
    GameWorld gw("round1");
    std::string ret = gw.GetMapInfoInJSON();
    return ret.c_str();
}

char const* getsimulation(float shootX, float shootY){
    GameWorld gw("round1");
    std::string ret = gw.GetSimulationJSON(shootX,shootY);
    return ret.c_str();
}

BOOST_PYTHON_MODULE(libgameworld){
    using namespace boost::python;
    def("getmapinfo", getmapinfo);
    def("getsimulation", getsimulation);
} 
