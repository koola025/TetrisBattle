#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include "Piece.h"

class red : public Piece
{
    public:
        red(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0xC600; 
            this->shape[1] = 0x4C80;
            this->shape[2] = 0xC600;
            this->shape[3] = 0x4C80;
            this->color = "red";
            pic = al_load_bitmap("./img/red.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // RED_H_INCLUDED
