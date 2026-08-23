#ifndef AST_H
#define AST_H

#include <vector>
#include <array>

#include "tokens.h"
#include "tunes.h"

class Stmt {
public:
    virtual ~Stmt() = default;
};

class TuneStmt : public Stmt {
public:
    Token tune;
    TuneDuration duration;
};

class LineStmt : public Stmt {
public:
    std::vector<TuneStmt> tunes;
};

class MusicSheetAst : public Stmt {
public:
    std::vector<LineStmt> lineOne;
    std::vector<LineStmt> lineTwo;
};

#endif //AST_H
