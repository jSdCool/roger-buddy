#include "raylib-cpp.hpp"
#include <iostream>
#include "mousePosition.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

using namespace std;

int screenWidth = 300;
int screenHeight = 300;

raylib::Vector2 internalWindowPos;
raylib::Texture2D roger1;

Vector2 myVecToRayVec(myVector v) {
    return {v.x,v.y};
}

void UpdateDrawFrame(raylib::Window &window);

int main() {

    //transparent background and no title bar / edge shaddow
    unsigned int windowFlags = FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED;
    raylib::Window window(screenWidth, screenHeight, "Roger Buddy", windowFlags);

    roger1 = raylib::Texture2D("data/r1.png");

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
    float windowVelocity = 2;

    raylib::Vector2 mousePos = myVecToRayVec(getScreenMousePosition());


    raylib::Vector2 winSize = window.GetSize();

    raylib::Vector2 targetPos = mousePos - (winSize/2.0f);

    float dist = targetPos.Distance(internalWindowPos);
    if (dist > 40 ) {
        float direction = atan2(targetPos.y-internalWindowPos.y,targetPos.x-internalWindowPos.x);

        raylib::Vector2 travel = {cos(direction),sin(direction)};
        travel *= windowVelocity;

        raylib::Vector2 newPos = internalWindowPos + travel;

        window.SetPosition(newPos);//this uses the raw int of the pos so it can be weird
        internalWindowPos = newPos;
    }

    // Draw
    BeginDrawing();

    //completely transparent background
    ClearBackground({0,0,0,0});



    DrawRectangle(0, 0, screenWidth, 15, WHITE);
    roger1.Draw(0,40);


    EndDrawing();

}