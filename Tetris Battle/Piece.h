#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include "global.h"


#define block_size 45


class Piece
{
    public:
        // constructor
        //Piece();
        
        void draw();
        void drawSmall();
        void drawHold();
        void drawShadow();
        int outBounds(int x, int y, int d, int s);
        
        string getColor() {return color;}
        int Pos_x;
        int Pos_y;
        int dir = 0;
        
        int board_left;
        int board_right; 
        int board_bottom;
        unsigned short int shape[4] = {0, 0, 0, 0};
        


    protected:
        
        string color;
          
        ALLEGRO_BITMAP* pic;  
        ALLEGRO_BITMAP* shadow;   
         
        


};



#endif // PIECE_H_INCLUDED
