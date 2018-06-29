#ifndef DARKBLUE_H_INCLUDED
#define DARKBLUE_H_INCLUDED

#include "Piece.h"

class darkblue : public Piece
{
    public:
        darkblue(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x8E00;
            this->shape[1] = 0x44C0;
            this->shape[2] = 0xE200;
            this->shape[3] = 0xC880;
            this->color = "darkblue";
            pic = al_load_bitmap("./img/darkblue.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // DARKBLUE_H_INCLUDED
