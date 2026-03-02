#include "raylib-cpp.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


int screenWidth = 800;
int screenHeight = 450;


void UpdateDrawFrame();

int main() {

    raylib::Window window(screenWidth, screenHeight, "Roger Buddy");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!window.ShouldClose()){    // Detect window close button or ESC key
        UpdateDrawFrame();
    }
#endif

    return 0;
}


void UpdateDrawFrame() {
    // Update


    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first raylib-cpp window!", 160, 200, 20, LIGHTGRAY);

    EndDrawing();

}