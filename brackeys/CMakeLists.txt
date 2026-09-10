cmake_minimum_required(VERSION 3.11)

project(fairio)

add_executable(${PROJECT_NAME}
    HelloWorld.cpp
    Brackeys2DTexture.cpp
    BrackeysText.cpp
    CreditsScene.cpp
    Enemy.cpp
    Entity.cpp
    Helper.cpp
    MainMenuScene.cpp
    Player.cpp
    PlayingScene.cpp
    Projectile.cpp
    Scenes.cpp
    TutorialScene.cpp
    Vector2Overloads.cpp
    Weapon.cpp
)

find_package(raylib REQUIRED CONFIG REQUIRED COMPONENTS raylib)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pspdebug
    pspdisplay
    pspge
    raylib
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(PSP)
    # Create an EBOOT.PBP file
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
        VERSION 01.00
    )
endif()