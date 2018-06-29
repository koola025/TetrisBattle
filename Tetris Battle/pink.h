#ifndef PINK_H_INCLUDED
#define PINK_H_INCLUDED

#include "Piece.h"

class pink : public Piece
{
    public:
        pink(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x4E00;
            this->shape[1] = 0x4C40;
            this->shape[2] = 0x0E40;
            this->shape[3] = 0x4640;
            this->color = "pink";
            pic = al_load_bitmap("./img/pink.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // PINK_H_INCLUDED
