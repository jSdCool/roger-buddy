# Roger Buddy

Hey Stan I'm on the internet too!

----
This digital assistant / companion is based on the character Roger from American Dad. Specifically season 20 ep 2 where Roger briefly appears on teh family computer.


Current functionality:
- Roger swims randomly sims around the screen, sometimes to your mouse pointer but usually random positions.


## Compile instructions
This project is currently only tested on Windows. It might work on other platforms but no promises

Pre requisites:
- MSVC build tools 2022 or later [link](https://visualstudio.microsoft.com/downloads/?q=build+tools#build-tools-for-visual-studio-2026)
- Cmake 3.14 or later [link](https://cmake.org/download/)

Build:
- Download / clone this repo
- Inside the project folder create a folder named build
- Open a terminal / command prompt inside the build folder
- In the terminal run `cmake ..` this may take a while to resolve dependencies 
- In that same terminal run `cmake --build . --config Release`
- Ensure the data folder is in the same folder as your generated executable
Your exe is now ready simply double click it in file explorer or run it from the command line

Or, load this project into your favorite C++ IDE and let it do all the work for you

  