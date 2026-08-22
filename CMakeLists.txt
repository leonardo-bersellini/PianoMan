cmake_minimum_required(VERSION 3.16)
project(PianoMen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Users/Utente/Desktop/C++/utilities/sfml/")
find_package(SFML 2.6.2 COMPONENTS graphics window system audio REQUIRED)

add_executable(PianoMan
    main.cpp

    pianoman/tunes.h
    
    pianoman/pianist/pianist.h 
    pianoman/pianist/player.h

    pianoman/composer/composer.h
    pianoman/composer/tokens.h

    pianoman/composer/lexer/lexer.h
    pianoman/composer/parser/parser.h
    pianoman/composer/generator/generator.h
)

target_include_directories(PianoMan PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(PianoMan PRIVATE 
    ${CMAKE_SOURCE_DIR}/pianoman
)

target_link_libraries(PianoMan
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
) 

# copia delle dipendenze

add_custom_command(TARGET PianoMan POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/dependencies"
            "$<TARGET_FILE_DIR:PianoMan>"
)

# copia delle risorse

add_custom_command(TARGET PianoMan POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:PianoMan>/assets"
)
