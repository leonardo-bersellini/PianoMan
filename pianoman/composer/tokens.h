#ifndef TOKENS_H
#define TOKENS_H

#include <unordered_map>
#include <string>

enum class Token
{
    Do,
    Re,
    Mi,
    Fa,
    Sol,
    La,
    Si,

    PausaSemplice,
    PausaLunga,
    PausaCroma,

    LParent,
    RParent,
    LBracket,
    RBracket,
    LBrace,
    RBrace,

    NewLine,
    StartLine,
    EndLine,
};

std::unordered_map<Token, std::string> keywords = {
    {Token::Do, "DO"},
    {Token::Re, "RE"},
    {Token::Mi, "MI"},
    {Token::Fa, "FA"},
    {Token::Sol, "SOL"},
    {Token::La, "LA"},
    {Token::Si, "SI"}
};

std::string tokenToString(Token t)
{
    switch(t) {
        case Token::Do: return "Do";
        case Token::Re: return "Re";
        case Token::Mi: return "Mi";
        case Token::Fa: return "Fa";
        case Token::Sol: return "Sol";
        case Token::La: return "La";
        case Token::Si: return "Si";
        case Token::LParent: return "(";
        case Token::RParent: return ")";
        case Token::StartLine: return "start-line";
        case Token::NewLine: return "newline";
        case Token::EndLine: return "endline";
        case Token::PausaSemplice: return "pausa-semplice";
        case Token::PausaLunga: return "pausa-lunga";
        case Token::PausaCroma: return "pausa-croma";
    }

    return "unknown";
}



#endif //TOKENS_H