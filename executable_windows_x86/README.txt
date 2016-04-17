# engineSDL_2016

2016-04-17

Abstract:
A very basic SDL/C++ (without OpenGL nor sound) 2D sprite-based game for Ludum Dare 35 jam (theme: Shapeshift), built for Windows-x86.

Work breakout:
~25h to write the game engine library.
~10h to write and test the game.
~4h to design 20 levels and draw the textures.

License:
This source code and the assets are free software following the WTF public license:  
	http://www.wtfpl.net/about/

Depends on:
* Visual C++ Redistributable for Visual Studio 2015 (x86)
	Available at: https://www.microsoft.com/en-us/download/details.aspx?id=48145
	Please install it if you don't have it yet.
* SDL 2.0.4
	http://libsdl.org/download-2.0.php
	Runtime DLL provided.
* SDL_gfx 2.0.25
	https://sourceforge.net/projects/sdlgfx/
	Compiled locally and runtime DLL provided.
* SDL_ttf
	http://www.libsdl.org/projects/SDL_ttf/
	Runtime DLL provided.
* JsonCpp (requires python)
	https://github.com/open-source-parsers/jsoncpp
	Included as source code.
	
How to use it:
1) Unzip the folder.
2) Install Visual C++ Redistributable for Visual Studio 2015 (x86), if you need it.
3) Run the executable file named LudumDare_v1.exe
4) Enjoy! My record score is 19724 points.
	
Know bugs:	
- Sometimes, if you resize the window, the background image and the symbol grid lose their alignment.
	
-- edgyeddy --	
EOF		