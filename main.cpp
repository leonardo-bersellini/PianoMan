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

#ifdef DEBUG_MACRO
    std::cout << "testing..." << std::endl;
    std::vector<std::pair<Tune, TuneDuration>> test = {
        {Tune::Do, TuneDuration::Semplice}, 
        {Tune::Re, TuneDuration::Lunga},
        {Tune::Fa, TuneDuration::Croma}
    };
    pianist.play(0, test);
#endif

    Composer composer;

    std::string path;
    std::cout << "inserire path del music sheet: ";
    std::cin >> path;

    const auto& music = composer.generateFromMusicSheet(path);
    
    pianist.play(0, music.line_one);
    pianist.play(1, music.line_two);

    return 0;
}

//TODO aggiungere una funzione che calcoli il pith in base al tempo
// per il quale la nota deve essere sounata, in base alla durata della nota a pitch 1 (durata file.ogg).