#ifndef PIANIST_H
#define PIANIST_H

#include <SFML/Audio.hpp>

#include <map>
#include <stdexcept>
#include <iostream>
#include <array>

#include "tunes.h"
#include "player.h"

/*
 *  PIANIST
 *  Il pianista del progetto. Il suo compito è quello di riprodurre la musica
 *  assegnatali. può eseguire più linee musicali contemporaneamente.
 */

class Pianist 
{
public:
    Pianist() {
        for(const auto& [tune, src] : tunes_source)
        {
            sf::SoundBuffer b;
            if(!b.loadFromFile(src)) {
                throw std::runtime_error("errore nel caricamento di " + src);
            }

            #ifdef DEBUG_MACRO
                std::cout << "[pianist] tune caricato" << std::endl;
            #endif

            m_notes.insert({tune, std::move(b)});
        }
    }

    ~Pianist() = default;

    void play(const int& player_id, const std::vector<std::pair<Tune, TuneDuration>>& note) 
    {
        // traduce ogni tune in soundbuffer e li delega ad un player

        #ifdef DEBUG_MACRO
            std::cout << "[pianist] received tunes: ";
            for(const auto& n : note) {std::cout << static_cast<int>(n.first) << " ";}
            std::cout << std::endl;
        #endif

        std::vector<std::pair<const sf::SoundBuffer*, TuneDuration>> sounds;
        sounds.reserve(note.size()); 

        for(const auto& n : note) {
            //si passano al player le note con la rispettiva durata
            sf::SoundBuffer* note;
            if(n.first == Tune::Pausa) note = nullptr;
            else note = &m_notes.at(n.first);
            
            sounds.push_back({note, n.second});
        }

        m_players.at(player_id).play(std::move(sounds));
    }


private:
    std::map<Tune, sf::SoundBuffer> m_notes; //note del piano
    std::array<Player, 2> m_players;
};

#endif //PIANIST_H