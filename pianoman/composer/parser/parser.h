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
    MusicSheetAst parseProgram(const std::vector<Token> tokens) 
    {
        this->tokens = tokens;
        index = 0;

        while(index < tokens.size()) 
        {
            expect(Token::NewLine);
            sheet_ast.lineOne.push_back(parseLine());
            sheet_ast.lineTwo.push_back(parseLine());
            expect(Token::EndLine);
        }

        return sheet_ast;
    }

private:
    std::vector<Token> tokens;
    std::size_t index;

    MusicSheetAst sheet_ast;

    Token advance() {
        if(index >= tokens.size()) throw std::runtime_error("advance in parser exceeded tokens size");
        auto t = tokens.at(index);
        index++;

        return t;
    }

    Token peek(const int i = 0) const {
        if(index >= tokens.size()) throw std::runtime_error("peek in parser reached tokens at size + 1");
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

    LineStmt parseLine() 
    {
        expect(Token::StartLine);
        
        LineStmt line; 

        while(index < tokens.size() && peek() != Token::StartLine && peek() != Token::EndLine) 
        {
            if(peek() == Token::LParent) {
                expect(Token::LParent);
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Semplice;
                line.tunes.push_back(s);
                expect(Token::RParent);
            }
            else if(peek() == Token::LBracket) {
                expect(Token::LBracket);
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Lunga;
                line.tunes.push_back(s);
                expect(Token::RBracket);
            }
            else if(peek() == Token::LBrace) {
                expect(Token::LBrace);
                expectTune();
                TuneStmt s;
                s.tune = advance();
                s.duration = TuneDuration::Croma;
                line.tunes.push_back(s);
                expect(Token::RBrace);
            }
            else if(peek() == Token::PausaSemplice) {
                TuneStmt s;
                s.tune = Token::PausaSemplice;
                s.duration = TuneDuration::Semplice;
                line.tunes.push_back(s);
                advance();
            }
            else if(peek() == Token::PausaLunga) {
                TuneStmt s;
                s.tune = Token::PausaLunga;
                s.duration = TuneDuration::Lunga;
                line.tunes.push_back(s);
                advance();
            }
            else if(peek() == Token::PausaCroma) {
                TuneStmt s;
                s.tune = Token::PausaCroma;
                s.duration = TuneDuration::Croma;
                line.tunes.push_back(s);
                advance();
            }
            else throw std::runtime_error("error: unexpected token in line");
            
        }

        if(index > tokens.size()) throw std::runtime_error("Expected endline before end of file");

        return line;
    }
};

#endif //PARSER_H