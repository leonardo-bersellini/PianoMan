#ifndef TUNES_H
#define TUNES_H

#include <map>
#include <unordered_map>
#include <string>
#include <chrono>
#include <utility>

enum class Tune
{
    Do,
    Re,
    Mi,
    Fa,
    Sol,
    La,
    Si,
    Pausa
};

//il fattore di durata effettivo è calcolato in player
enum class TuneDuration {
    Semplice,
    Lunga,
    Croma
};

std::unordered_map<TuneDuration, float> duration_factor = {
    {TuneDuration::Semplice, 1.0},
    {TuneDuration::Lunga, 2.0},
    {TuneDuration::Croma, 0.5}
};

std::map<Tune, std::string> tunes_source =
{
    {Tune::Do,  "assets/do-c.ogg"},
    {Tune::Re,  "assets/re-d.ogg"},
    {Tune::Mi,  "assets/mi-e.ogg"},
    {Tune::Fa,  "assets/fa-f.ogg"},
    {Tune::Sol, "assets/sol-g.ogg"},
    {Tune::La,  "assets/la-a.ogg"},
    {Tune::Si,  "assets/si-b.ogg"}
};

//durata dei file di risorsa
inline constexpr std::chrono::seconds tune_source_duration = std::chrono::seconds(1);

//fattore di velocità di riproduzione.
//modificando questa variabile si modifica il valore di un tempo.
inline constexpr float speed_scale = 1.5;

struct MusicSheet {
    std::vector<std::pair<Tune, TuneDuration>> line_one;
    std::vector<std::pair<Tune, TuneDuration>> line_two;
};

#endif //TUNES_H