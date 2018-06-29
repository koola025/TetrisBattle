#ifndef GREEN_H_INCLUDED
#define GREEN_H_INCLUDED

#include "Piece.h"

class green : public Piece
{
    public:
        green(int x, int y, int bl, int br, int bb) {
            this->Pos_x = x;
            this->Pos_y = y;
            this->board_left = bl;
            this->board_right = br;
            this->board_bottom = bb;
            this->shape[0] = 0x6C00;
            this->shape[1] = 0x8C40;
            this->shape[2] = 0x6C00;
            this->shape[3] = 0x8C40;
            this->color = "green";
            pic = al_load_bitmap("./img/green.png");
            shadow = al_load_bitmap("./img/shadow.png");

        }


};

#endif // GREEN_H_INCLUDED
