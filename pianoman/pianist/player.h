#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>

#include <thread>
#include <vector>

class Player 
{
public:
    Player() = default;
    ~Player() { 
        stop();
    }

    // copie invalide (pericolose con thread)
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    
    void play(std::vector<const sf::SoundBuffer*> sounds) 
    {
        stop(); //ferma un esecuzione se in corso

        m_thread = std::thread([this, sounds = std::move(sounds)]() {
            for(const auto* s : sounds) 
            {
                if(!s) continue;
                m_sound.setBuffer(*s);
                m_sound.play();
                waitForFinished();
            }
        });
    }

    void stop() {
        //termina l'esecuzione di sound e thread
        //eventualmente esegue il join del thread per evitare crash

        if(m_thread.joinable()) {
            m_thread.join();
        }
        m_sound.stop();
    }

    void setPitch(const float pitch) {
        m_sound.setPitch(pitch);
    }
    
private:
    sf::Sound m_sound;
    std::thread m_thread;

    void waitForFinished() {
        while(m_sound.getStatus() == sf::Sound::Status::Playing) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

};

#endif //PLAYER_H