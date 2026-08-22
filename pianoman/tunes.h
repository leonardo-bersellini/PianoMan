#ifndef TUNES_H
#define TUNES_H

#include <map>
#include <string>
#include <chrono>

enum class Tune
{
    Do,
    Re,
    Mi,
    Fa,
    Sol,
    La,
    Si,
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
inline const std::chrono::seconds tune_duration = std::chrono::seconds(1);

struct MusicSheet {
    std::vector<Tune> line_one;
    std::vector<Tune> line_two;
};

#endif //TUNES_H