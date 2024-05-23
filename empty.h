#ifndef EMPTY_H__
#define EMPTY_H__

#include "piece.h"

#define EMPTY_CHARACTER '-'

class Empty : public Piece {
    public:
        Empty();
        ~Empty();

};

#endif
