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

    // Draw
    BeginDrawing();

    //completely transparent background
    ClearBackground({0,0,0,0});

    Vector2 mousePos = myVecToRayVec(getScreenMousePosition());

    DrawRectangle(0, 0, screenWidth, 15, WHITE);

    DrawText("Congrats! You created your first raylib-cpp window!", 160, 200, 20, LIGHTGRAY);
    raylib::DrawText("Mouse pos: "+to_string(mousePos.x)+" "+to_string(mousePos.y),106,250,20,GREEN);

    EndDrawing();

}