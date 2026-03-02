#include "raylib-cpp.hpp"
#include <iostream>
#include "mousePosition.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

using namespace std;

int screenWidth = 800;
int screenHeight = 450;

Vector2 myVecToRayVec(myVector v) {
    return {v.x,v.y};
}

void UpdateDrawFrame(raylib::Window &window);

int main() {

    //transparent background and no title bar / edge shaddow
    unsigned int windowFlags = FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED;
    raylib::Window window(screenWidth, screenHeight, "Roger Buddy", windowFlags);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

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
    float windowVelocity = 10;

    raylib::Vector2 mousePos = myVecToRayVec(getScreenMousePosition());

    raylib::Vector2 winPos = window.GetPosition();
    raylib::Vector2 winSize = window.GetSize();

    raylib::Vector2 targetPos = mousePos - (winSize/2.0f);

    float dist = targetPos.Distance(winPos);
    if (dist > 30 ) {
        float direction = atan2(targetPos.y-winPos.y,targetPos.x-winPos.x);

        raylib::Vector2 travel = {cos(direction),sin(direction)};
        travel *= windowVelocity;

        raylib::Vector2 newPos = winPos + travel;

        window.SetPosition(newPos);//this intergizes the position so small angles dont work well
    }

    // Draw
    BeginDrawing();

    //completely transparent background
    ClearBackground({0,0,0,0});



    DrawRectangle(0, 0, screenWidth, 15, WHITE);

    DrawText("Congrats! You created your first raylib-cpp window!", 160, 200, 20, LIGHTGRAY);

    EndDrawing();

}