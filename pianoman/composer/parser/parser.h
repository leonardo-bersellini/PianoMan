#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <stdexcept>

#include "..\tokens.h"
#include "..\ast.h"

class Parser 
{
public:
    std::vector<Stmt> parseProgram(const std::vector<Token> tokens) 
    {
        this->tokens = tokens;
        index = 0;

        auto currentTkn = tokens.at(index);

        expect(Token::NewLine);
        void parseLine();
        expect(Token::EndLine);
    }

private:
    std::vector<Token> tokens;
    std::size_t index;

    std::vector<Stmt> stmts;

    Token advance() {
        if(index > tokens.size()) return tokens.back();
        auto t = tokens.at(index);
        index++;

        return t;
    }

    Token peek(const int i = 0) const {
        return tokens.at(index +i);
    }

    void expect(Token t) {
        if(peek() == t) {advance(); return;}
        else throw std::runtime_error("Expected a different token");
    }

    void expectTune() {
        if(peek() != Token::Do && peek() != Token::Re && peek() != Token::Mi
            && peek() != Token::Fa && peek() != Token::Sol && peek() != Token::La && peek() != Token::Si) 
            {
                throw std::runtime_error("Expected a note");
            }
    }

    void parseLine() 
    {
        expect(Token::StartLine);
        
        while(index < tokens.size() || peek() == Token::StartLine || peek() == Token::EndLine) 
        {
            if(peek() == Token::LParent) {
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Semplice;
                stmts.push_back(s);
                expect(Token::RParent);
            }
            else if(peek() == Token::LBracket) {
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Lunga;
                stmts.push_back(s);
                expect(Token::RBracket);
            }
            else if(peek() == Token::LBrace) {
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Croma;
                stmts.push_back(s);
                expect(Token::RBrace);
            }
            else throw std::runtime_error("error: unexpected token in line");
            
        }

        if(index > tokens.size()) throw std::runtime_error("Expected endline before end of file");
    }
};

#endif //PARSER_H