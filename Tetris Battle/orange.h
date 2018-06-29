#ifndef ORANGE_H_INCLUDED
#define ORANGE_H_INCLUDED

#include "Piece.h"

class orange : public Piece
{
    public:
        orange(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x2E00;
            this->shape[1] = 0xC440;
            this->shape[2] = 0x0E80;
            this->shape[3] = 0x88C0;
            this->color = "orange";
            pic = al_load_bitmap("./img/orange.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // ORANGE_H_INCLUDED
