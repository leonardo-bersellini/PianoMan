#include <iostream>

#include <SFML/Audio.hpp>

/*
 *  PIANO MAN PROJECT
 *
 *  Esecutore di "song-script" con sfml. legge uno speciale script ed esegue le note.
 *  Il progetto è quindi diviso in interprete (suona le note) e generatore di canzoni (scrive 
 *  lo spartito adatto per l'interprete).
 * 
 *  Interprete: "Pianist"
 *  Generatore: "Composer"
 */

#include "pianist/pianist.h"
#include "composer/composer.h"

int main() 
{
    Pianist pianist;

    std::cout << "testing..." << std::endl;
    std::vector<Tune> test = {Tune::Do, Tune::Re, Tune::Mi};
    pianist.play(0, test);

    Composer composer;

    std::string path;
    std::cout << "inserire path del music sheet: ";
    std::cin >> path;

    const auto& music = composer.generateFromMusicSheet(path);

    pianist.setPlayerPitch(0, 3.5);
    pianist.setPlayerPitch(1, 3.5);
    
    pianist.play(0, music.line_one);
    pianist.play(1, music.line_two);

    return 0;
}

//TODO aggiungere una funzione che calcoli il pith in base al tempo
// per il quale la nota deve essere sounata, in base alla durata della nota a pitch 1 (durata file.ogg).