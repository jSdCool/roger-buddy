#pragma once

//the Windows API has some functions named the same as raylib's functions, so we can not include both of the at the same time
struct myVector {
    float x, y;
};

myVector getScreenMousePosition();