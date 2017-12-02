//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_RULETYPES
#define TREE_INCLUDES_RULETYPES

namespace Rules {
    enum RuleType {
        PROG = 0,
        DECLS = 1,
        DECL = 2,
        ARRAY = 3,
        STATEMENTS = 4,
        STATEMENT = 5,
        EXP = 6,
        EXP2 = 7,
        INDEX = 8,
        OP_EXP = 9,
        OP = 10,
        NRT = 11,
        EPS = 12,
    };
}

#endif TREE_INCLUDES_RULETYPES
