//
// Created by stefan on 02.12.17.
//

#ifndef TREE_INCLUDES_INFORMATIONTYPE
#define TREE_INCLUDES_INFORMATIONTYPE

namespace InformationType {
    enum InfoType {
        intType = 0,
        intArrayType = 1,
        arrayType = 2,
        noType = 3,
        errorType = 4,

        opPlus = 5,
        opMinus = 6,
        opMult = 7,
        opDiv = 8,
        opLess = 9,
        opGreater = 10,
        opEqual = 11,
        opUnequal = 12,
        opAnd = 13
    };
}

#endif TREE_INCLUDES_INFORMATIONTYPE
