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
    {Token::Do, "Do"},
    {Token::Re, "Re"},
    {Token::Mi, "Mi"},
    {Token::Fa, "Fa"},
    {Token::Sol, "Sol"},
    {Token::La, "La"},
    {Token::Si, "Si"},
};



#endif //TOKENS_H