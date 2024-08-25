# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("ludo")
set(GLM_ENABLE_CXX_17 ON)
add_subdirectory("submodules/glm")
# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
add_library(ludo SHARED
        "src/main.cpp"
        "src/android-out.cpp"
        "src/renderer.cpp"
        "src/ludo/animation.cpp"
        "src/ludo/board.cpp"
        "src/ludo/input.cpp"
        "src/ludo/scene.cpp"
        "src/ludo/scenes/match_scene.cpp"
        "src/ludo/scenes/test_scene.cpp"
        "src/ludo/screen.cpp"
        "src/ludo/sprite.cpp"
        "src/ludo/time.cpp"
)
target_include_directories(ludo PRIVATE "includes")
# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)
# Configure libraries CMake uses to link your target library.
target_link_libraries(ludo
        glm
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log
)