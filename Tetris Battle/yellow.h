#ifndef YELLOW_H_INCLUDED
#define YELLOW_H_INCLUDED

#include "Piece.h"

class yellow : public Piece
{
    public:
        yellow(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x0660;
            this->shape[1] = 0x0660;
            this->shape[2] = 0x0660;
            this->shape[3] = 0x0660;
            this->color = "yellow";
            pic = al_load_bitmap("./img/yellow.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // YELLOW_H_INCLUDED
