2016-04-11

Additional "engineSDL" Visual Studio project settings (static library):
	* Properties > C/C++ > General > Additional Include Directories
		Add .\headers
	* Properties > C/C++ > General > Additional Included Directories
		Add header directory ...\externLibs\visualCpp\SDL2-2.0.4\include
		Add header directory ...\externLibs\visualCpp\SDL2_ttf-devel-2.0.14-VC\SDL2_ttf-2.0.14\include
		Add header directory ...\externLibs\visualCpp\SDL2_gfx-1.0.1
	* Properties > Configuration Properties > VC++ Directories > Library Directories
		Add library directory ...\externLibs\visualCpp\SDL2-2.0.4\lib\x86
		Add library directory ...\externLibs\visualCpp\SDL2_ttf-devel-2.0.14-VC\SDL2_ttf-2.0.14\lib\x86
		Add library directory ...\externLibs\visualCpp\SDL2_gfx-1.0.1\Win32\Debug
	* Properties > Linker > Input > Additional dependencies
		Add "SDL2.lib SDL2main.lib"
		Add "SDL2_ttf.lib"
		Add "SDL2_gfx.lib"
	* Properties > C/C++ > All Options > Additional Options
		Add -D_WIN32_WINNT=0x0501 

Additional "demoGame" Visual Studio project settings:
	* Properties > C/C++ > General > Additional Include Directories
		Add ..\engineSDL\headers
	* References > Project > Solution
		Add engineSDL as reference
	* Properties > Linker > System > Sub-System
		Add type /CONSOLE
		
		
Doxygen:
	To initialize doxygen
		$ doxygen -g doxygen.config
	To generate documentation
		$ doxygen doxygen.config
