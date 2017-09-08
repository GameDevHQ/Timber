# Timber
The Timberman game clone, which is based on ideas and concepts from a "Beginning C++ Game Programming" book by John Horton.

Hotkeys
--------
- "Esc" for exit from the game
- "Enter" for start the game
- "Right arrow" / "Left arrow" for making a cut of a tree from an appropriate side

Requirements
------------
- C++11
- SFML 2.4.2 (x32 version)

How to build 
------------
After opening the project in Visual Studio, go to "Project -> Timber properties...":
1) Select "All configurations" in "Configuration" section
2) In "C/C++ -> General -> Additional include directories" section append the "include" directory of SFML library
3) In "Linker -> General -> Additional library directories" section append the "lib" directory of SFML library
4) Select "Debug" in "Configuration" section
5) Append the string (without quotes) "sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-network-d.lib;sfml-audio-d.lib;" at the beginning of the
"Linker -> Input -> Additional dependencies" section
6) Select "Release" in "Configuration" section
7) Append the string (without quotes) "sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-network.lib;sfml-audio.lib;" at the beginning of the
"Linker -> Input -> Additional dependencies" section

Screenshots
-----------
<p align="center">
  <img src="https://github.com/GameDevHQ/Timber/blob/master/Screenshots/Screenshot_1.png"/>
</p>
