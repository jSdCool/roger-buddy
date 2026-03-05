#pragma once
#include <raylib-cpp.hpp>


class TargetDestination {
public:
    TargetDestination()= default;

    virtual raylib::Vector2 getTargetPosition() =0;

    virtual ~TargetDestination()= default;
};


class MouseDestination : public TargetDestination {
public:
    raylib::Vector2 getTargetPosition() override;
};

class PositionDestination : public TargetDestination {
    raylib::Vector2 target;
public:
    PositionDestination();
    raylib::Vector2 getTargetPosition() override;
};