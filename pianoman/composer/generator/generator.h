#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

#include "tunes.h"
#include "..\ast.h"

class Generator
{
public:

    MusicSheet generateMusic(const MusicSheetAst& ast) 
    {
        //le linee saranno due, ma salvate in segmenti in un vettore
        //nota: tune.duration adesso viene ignorata.

        std::cout << "[generator] music-sheet-ast: statements line one: " << ast.lineOne.size() << std::endl;
        std::cout << "[generator] music-sheet-ast: statements line two: " << ast.lineTwo.size() << std::endl;

        //linea uno
        for(const auto& line : ast.lineOne) 
        {
            for(const auto& tune : line.tunes) 
            {
                sheet.line_one.push_back(tokenToTune(tune.tune));
            }
        }

        //linea due
        for(const auto& line : ast.lineTwo)
        {
            for(const auto& tune : line.tunes)
            {
                sheet.line_two.push_back(tokenToTune(tune.tune));
            }
        }

        return sheet;
    }

private:
    MusicSheet sheet;

    Tune tokenToTune(Token tune)
    {
        switch(tune) {
            case Token::Do: return Tune::Do;
            case Token::Re: return Tune::Re;
            case Token::Mi: return Tune::Mi;
            case Token::Fa: return Tune::Fa;
            case Token::Sol: return Tune::Sol;
            case Token::La: return Tune::La;
            case Token::Si: return Tune::Si;
            default: 
                throw std::runtime_error("internal error: this token is not a tune [function token-to-tune]");
                break;
        }
    }
};

#endif //GENERATOR_H