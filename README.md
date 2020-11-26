# bit-sim


# Instructions to setup a VS17/VS19 project with SFML 2.5
See https://www.sfml-dev.org/tutorials/2.5/start-vc.php for details

0. Ignore message about SFML 2.5 being incompatible with VS19 and use it anyway

1. Edit Project-Settings
    - Ensure Configurations and Platform are set to "All"
    - C/C++ > General > Additional Include Dirs = <install-dir>\include
    - C/C++ > Preprocessor > Preprocessor Definitions: Prepend SFML_STATIC;
    - Linker > General > Additional Lib Dirs = <install-dir>\lib

    - Go to: Linker > Input > Additional Dependencies > Edit 
        - Insert: 
            winmm.lib;opengl32.lib;gdi32.lib;freetype.lib;
            sfml-system-s.lib;sfml-window-s.lib;sfml-graphics-s.lib;
    - Apply, switch configuration to Debug
        - Change second line insert to: 
            sfml-system-s-d.lib;sfml-window-s-d.lib;sfml-graphics-s-d.lib;

    - Done, Apply/Ok

2. Project files
    - Copy the following files from SFML\bin to <project-root>\<project-name>:
        sfml-system-2.lib
        sfml-system-d-2.lib
        sfml-window-2.lib
        sfml-window-d-2.lib
        sfml-graphics-2.lib
        sfml-graphics-d-2.lib

3. Create a Project Template
    - Follow Project > Export Template
