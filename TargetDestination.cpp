#include "TargetDestination.hpp"

#include <iostream>
#include <ostream>

#include "mousePosition.hpp"

raylib::Vector2 vconv (myVector v) {
    return {v.x,v.y};
}


//Mouse Dest
raylib::Vector2 MouseDestination::getTargetPosition() {
    //Do a check here for if the system supports global mouse positioning
    return vconv(getScreenMousePosition());
}


//Position Dest
PositionDestination::PositionDestination() {
    //get a random screen position to go to
    int monitor = GetRandomValue(0,GetMonitorCount()-1);
    int height = GetMonitorHeight(monitor);
    int width = GetMonitorWidth(monitor);
    raylib::Vector2 monitorPos = GetMonitorPosition(monitor);
    raylib::Vector2 newPos{static_cast<float>(GetRandomValue(0, width)),static_cast<float>(GetRandomValue(0, height))};
    newPos += monitorPos;
    // std::cout << "targeting position: " << newPos.x << " "<< newPos.y << " Width: "<< width << " height: "<<height << " monitor: "<<monitor << std::endl;
    target = newPos;
}

raylib::Vector2 PositionDestination::getTargetPosition() {
    return target;
}
