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

int main() 
{
    Pianist pianist;

    std::vector<Tune> song = {
        Tune::Mi, Tune::Mi, Tune::Fa, Tune::Sol, 
        Tune::Sol, Tune::Fa, Tune::Mi, Tune::Re,
        Tune::Do, Tune::Do, Tune::Re, Tune::Mi,
        Tune::Mi, Tune::Re, Tune::Re
    };

    std::cout << "playing" << std::endl;

    //TODO aggiungere una funzione che calcoli il pith in base al tempo
    // per il quale la nota deve essere sounata, in base alla durata della nota a pitch 1 (durata file.ogg).
    pianist.setPlayerPitch(1, 4);
    pianist.play(1, song);

    return 0;
}