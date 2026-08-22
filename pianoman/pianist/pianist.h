#ifndef PIANIST_H
#define PIANIST_H

#include <SFML/Audio.hpp>

#include <map>
#include <stdexcept>
#include <iostream>
#include <array>

#include "tunes.h"
#include "player.h"

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
            std::cout << "tune caricato" << std::endl;

            m_notes.insert({tune, std::move(b)});
        }
    }

    ~Pianist() = default;

    void play(const int& player_id, const std::vector<Tune>& tunes) 
    {
        // traduce ogni tune in soundbuffer e li delega ad un player

        std::vector<const sf::SoundBuffer*> sounds;
        sounds.reserve(tunes.size()); 

        for(const auto& t : tunes) {
            sounds.push_back(&m_notes.at(t));
        }

        m_players.at(player_id).play(std::move(sounds));
    }

    void setPlayerPitch(const int& player_id, float pitch) {
        m_players.at(player_id).setPitch(pitch);
    }


private:
    std::map<Tune, sf::SoundBuffer> m_notes; //note del piano
    std::array<Player, 2> m_players;
};

#endif //PIANIST_H