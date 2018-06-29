#ifndef LIGHTBLUE_H_INCLUDED
#define LIGHTBLUE_H_INCLUDED

#include "Piece.h"

class lightblue : public Piece
{
    public:
        lightblue(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x2222;
            this->shape[1] = 0x0F00;
            this->shape[2] = 0x4444;
            this->shape[3] = 0x00F0;
            this->color = "lightblue";
            pic = al_load_bitmap("./img/lightblue.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // LIGHTBLUE_H_INCLUDED
