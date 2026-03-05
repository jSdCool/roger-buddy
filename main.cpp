#include "raylib-cpp.hpp"
#include <iostream>
#include <vector>
#include "mousePosition.hpp"
#include <ctime>
#include <memory>

#include "TargetDestination.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

using namespace std;

int screenWidth = 250;
int screenHeight = 250;

raylib::Vector2 internalWindowPos;
raylib::Texture2D roger1;
int animationFrame = 0;
int counter =0;
vector<raylib::Texture2D> rogerSwim;
vector<raylib::Texture2D> rogerSwimFlipped;
constexpr float SWIM_ANGLE_OFFSET = DEG2RAD * 30;
unique_ptr<TargetDestination> currentTarget = make_unique<MouseDestination>();
bool targetReached = false;

Vector2 myVecToRayVec(myVector v) {
    return {v.x,v.y};
}

void setNewRandomTarget() {
    int number = GetRandomValue(0,15);
    if (number < 2) {
        currentTarget = make_unique<MouseDestination>();
    } else {
        currentTarget = make_unique<PositionDestination>();
    }
}

void UpdateDrawFrame(raylib::Window &window);

int main() {
    SetRandomSeed(time(nullptr));

    //transparent background and no title bar / edge shaddow
    unsigned int windowFlags = FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST;
    raylib::Window window(screenWidth, screenHeight, "Roger Buddy", windowFlags);

    roger1 = raylib::Texture2D("data/r1.png");

    rogerSwim.reserve(10);
    rogerSwimFlipped.reserve(10);
    for (int i=0;i<10;i++) {
        rogerSwim.emplace_back("data/rc"+to_string(i+1)+".png");
        raylib::Image toFlip("data/rc"+to_string(i+1)+".png");
        toFlip.FlipHorizontal();
        rogerSwimFlipped.emplace_back(toFlip);
    }

    window.SetIcon(roger1);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    internalWindowPos = window.GetPosition();
    // Main game loop
    while (!window.ShouldClose()){    // Detect window close button or ESC key
        UpdateDrawFrame(window);
    }
#endif

    return 0;
}


void UpdateDrawFrame(raylib::Window &window) {
    // Update

    //move the window to the mouse slowly
    float windowVelocity = 3;

    raylib::Vector2 winSize = window.GetSize();

    raylib::Vector2 targetPos = currentTarget->getTargetPosition() - (winSize/2.0f);

    float dist = targetPos.Distance(internalWindowPos);
    float direction = atan2(targetPos.y-internalWindowPos.y,targetPos.x-internalWindowPos.x);
    if (dist > 40 && !targetReached) {


        raylib::Vector2 travel = {cos(direction),sin(direction)};
        travel *= windowVelocity;

        raylib::Vector2 newPos = internalWindowPos + travel;

        window.SetPosition(newPos);//this uses the raw int of the pos so it can be weird
        internalWindowPos = newPos;

        //animation counter, only if moving
        counter++;
        if (counter == 5) {
            counter = 0;
            animationFrame++;
            if (animationFrame == 10) {
                animationFrame = 0;
            }
        }
    }else {
        targetReached = true;
        counter++;
        if (counter >=70) {
            setNewRandomTarget();
            counter =0;
            targetReached = false;
        }
    }

    float swimAngle = direction - SWIM_ANGLE_OFFSET;



    bool flip = swimAngle > DEG2RAD*90 - SWIM_ANGLE_OFFSET || swimAngle < -DEG2RAD*90 - SWIM_ANGLE_OFFSET;

    if (flip) {
        if (swimAngle > 0 ) {
            swimAngle -= PI - 2*SWIM_ANGLE_OFFSET;
        } else {
            swimAngle += PI + 2*SWIM_ANGLE_OFFSET;
        }
    }

    swimAngle *= RAD2DEG;



    // Draw
    BeginDrawing();

    //completely transparent background
    ClearBackground({0,0,0,0});


    //draw the swiming animation
    raylib::Rectangle dst {0.0f,0.0f,200.0f,200.0f};
    if (animationFrame == 9) {
        dst.x = -2;
        dst.y = 9;
    }
    dst.x+=static_cast<float>(window.GetWidth())/2;
    dst.y+=static_cast<float>(window.GetHeight())/2;
    // bool flip = false;
    if (flip) {
        rogerSwimFlipped[animationFrame].Draw(Rectangle{0.0f,0.0f,static_cast<float>(rogerSwim[animationFrame].width),static_cast<float>(rogerSwim[animationFrame].height)},dst,{100,100},swimAngle);
    }else {
        rogerSwim[animationFrame].Draw(Rectangle{0.0f,0.0f,static_cast<float>(rogerSwim[animationFrame].width),static_cast<float>(rogerSwim[animationFrame].height)},dst,{100,100},swimAngle);
    }

    EndDrawing();

}