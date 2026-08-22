#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <stdexcept>

#include "..\tokens.h"

class Lexer 
{
public:

    std::vector<Token> analiseSheet(const std::string& sheet) 
    {
        index = 0;
        buffer = sheet;

        while(!index > sheet.size()) 
        {
            const char c = sheet.at(index);

            if(c == '#') {
                m_tokens.push_back(readLineIdentifier());
            }
            else if(c == '(') {
                m_tokens.push_back(Token::LParent);
            }
            else if(c == ')') {
                m_tokens.push_back(Token::RParent);
            }
            else if(c == '[') {
                m_tokens.push_back(Token::LBracket);
            }
            else if(c == ']') {
                m_tokens.push_back(Token::RBracket);
            }
            else if(c == '{') {
                m_tokens.push_back(Token::LBrace);
            }
            else if(c == '}') {
                m_tokens.push_back(Token::RBrace);
            }
            else if(c == '-') {
                m_tokens.push_back(Token::StartLine);
            }
            else {
                m_tokens.push_back(checkKeyword());
            }
        }

        return m_tokens;
    }

private:
    std::vector<Token> m_tokens;
    std::size_t index = 0;
    std::string buffer;

    char advance() {
        if(index > buffer.size()) return '\0';
        char r = buffer.at(index);
        index++;

        return r;
    }

    char peek(const int i = 0) const {
        return buffer.at(index +i);
    }

    Token readLineIdentifier() 
    {
        std::string identifier;
        while(index < buffer.size() && peek(1) != ' ') {
            identifier += advance();
        }

        if(identifier == "#LINE") {
            return Token::NewLine;
        }
        else if(identifier == "#ENDLINE") {
            return Token::EndLine;
        }
        else throw std::runtime_error("Expected line-identifier after #");
    }

    Token checkKeyword() 
    {
        std::string word;

        while(index < buffer.size()) {
            if(peek(1) == '(' || peek(1) == ')') break;
            if(peek(1) == '[' || peek(1) == ']') break;
            if(peek(1) == '{' || peek(1) == '}') break;

            word += advance();
        }

        if(index > buffer.size()) throw std::runtime_error("Expected keyword before end of file");

        for(const auto& [token, keyword] : keywords) {
            if(word == keyword) return token;
        }
    }

};

#endif //LEXER_H