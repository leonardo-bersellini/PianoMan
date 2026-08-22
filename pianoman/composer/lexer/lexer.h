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

        while(index < sheet.size()) 
        {
            const char c = sheet.at(index);

            if (c == ' ' || c == '\n' || c == '\r')
            {
                advance();
            }
            else if(c == '#') {
                m_tokens.push_back(readLineIdentifier());
            }
            else if(c == '(') {
                m_tokens.push_back(Token::LParent);
                advance();
            }
            else if(c == ')') {
                m_tokens.push_back(Token::RParent);
                advance();
            }
            else if(c == '[') {
                m_tokens.push_back(Token::LBracket);
                advance();
            }
            else if(c == ']') {
                m_tokens.push_back(Token::RBracket);
                advance();
            }
            else if(c == '{') {
                m_tokens.push_back(Token::LBrace);
                advance();
            }
            else if(c == '}') {
                m_tokens.push_back(Token::RBrace);
                advance();
            }
            else if(c == '-') {
                m_tokens.push_back(Token::StartLine);
                advance();
            }
            else {
                m_tokens.push_back(checkKeyword());
            }
        }

        std::cout << "[lexer] tokens: ";
        for(const auto& t : m_tokens) {
            std::cout << tokenToString(t) << std::endl;
        }
        std::cout << std::endl;

        return m_tokens;
    }

private:
    std::vector<Token> m_tokens;
    std::size_t index = 0;
    std::string buffer;

    char advance() {
        if(index >= buffer.size()) throw std::runtime_error("advance in lexer exceeded buffer size");
        char r = buffer.at(index);
        index++;

        return r;
    }

    char peek(const int i = 0) const {
        if (index + i >= buffer.size()) throw std::runtime_error("peek in lexer out of range");
        return buffer.at(index +i);
    }

    Token readLineIdentifier() 
    {
        std::string identifier;
        while(index < buffer.size() && peek() != ' ' && peek() != '\n') {
            identifier += advance();
        }

        if(identifier == "#LINE") {
            return Token::NewLine;
        }
        else if(identifier == "#ENDLINE") {
            return Token::EndLine;
        }
        else throw std::runtime_error("Expected line-identifier after #. identifier:" + identifier);
    }

    Token checkKeyword() 
    {
        std::string word;

        while(index < buffer.size()) {
            if(peek() == '(' || peek() == ')') break;
            if(peek() == '[' || peek() == ']') break;
            if(peek() == '{' || peek() == '}') break;
            if(peek() == '\n' || peek() == '-') break;
            if(peek() == ' ') break;

            word += advance();
        }

        if(index > buffer.size()) throw std::runtime_error("Expected keyword before end of file");

        for(const auto& [token, keyword] : keywords) {
            if(word == keyword) return token;
        }

        throw std::runtime_error("check keyword in lexer failed: word: " + word + " is not a keyword");
    }

};

#endif //LEXER_H