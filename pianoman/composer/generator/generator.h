#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "tunes.h"
#include "..\ast.h"

class Generator
{
public:

    MusicSheet generateMusic(const std::vector<Stmt>& stmts) 
    {
        for(auto& st : stmts) 
        {
            if(auto s = dynamic_cast<const TuneStmt*>(&st)) {
                //ricavare un Tune con qualcosa tipo TokenToTune
                //per adesso nulla ma in futuro utilizzare anche la durata della nota nel musicsheet
            }
        }
    }

private:
    MusicSheet sheet;
};

#endif //GENERATOR_H