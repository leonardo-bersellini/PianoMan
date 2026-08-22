#ifndef AST_H
#define AST_H

#include <vector>

#include "tokens.h"

enum class TuneDuration {
    Semplice,
    Lunga,
    Croma
};

class Stmt {
public:
    virtual ~Stmt() = default;
};

class MusicSheetAst : public Stmt {
public:
    std::vector<LineStmt> lines;
};

class LineStmt : public Stmt {
public:
    std::vector<TuneStmt> tunes;
};

class TuneStmt : public Stmt {
public:
    Token tune;
    TuneDuration duration;
};

#endif //AST_H
