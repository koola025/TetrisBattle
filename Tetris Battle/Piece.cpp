#include "Piece.h"

/*static const unsigned short int pieces[7][4] =
{
	{ 0x2222, 0x0F00, 0x4444, 0x00F0 }, // PIECE_I
	{ 0x6C00, 0x8C40, 0x6C00, 0x8C40 }, // PIECE_S
	{ 0xC600, 0x4C80, 0xC600, 0x4C80 }, // PIECE_Z
	{ 0x8E00, 0x44C0, 0xE200, 0xC880 }, // PIECE_J
	{ 0x2E00, 0xC440, 0x0E80, 0x88C0 }, // PIECE_L
	{ 0x0660, 0x0660, 0x0660, 0x0660 }, // PIECE_O
	{ 0x4E00, 0x4C40, 0x0E40, 0x4640 }, // PIECE_T
};
*/

void Piece::draw() {
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = shape[dir] & (1 << (15 - (i * 4 + j)));
            if (mask) al_draw_bitmap(pic, Pos_x + j * block_size, Pos_y + i * block_size, 0);
        }
    }

}

void Piece::drawSmall() {
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = shape[dir] & (1 << (15 - (i * 4 + j)));
            if (mask) {
                if (color == "lightblue") 
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 394, Pos_y + i * 25 + 146,25,25 ,0);
                else if (color == "yellow") 
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 408, Pos_y + i * 25 + 95,25,25 ,0);
                else
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 419, Pos_y + i * 25 + 80,25,25 ,0);
                
            }
        }
    }

}

void Piece::drawHold() {
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = shape[dir] & (1 << (15 - (i * 4 + j)));
            if (mask) {
                if (color == "lightblue") 
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 194 - 445, Pos_y + i * 25 + 703 + 90,25,25 ,0);
                else if (color == "yellow") 
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 208 - 445, Pos_y + i * 25 + 652 + 90,25,25 ,0);
                else
                al_draw_scaled_bitmap(pic, 0, 0, 45, 45, Pos_x + j * 25 + 219 - 445, Pos_y + i * 25 + 637 + 90,25,25 ,0);
                
            }
        }
    }

}

void Piece::drawShadow() {
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = shape[dir] & (1 << (15 - (i * 4 + j)));
            if (mask) al_draw_bitmap(shadow, Pos_x + j * block_size, Pos_y + i * block_size, 0);
        }
    }

}

int Piece::outBounds(int x, int y, int d, int s) {
    int check = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = shape[d] & (1 << (15 - (i * 4 + j)));
            int nx = x+j*block_size;
            int ny = y+i*block_size;
            if (mask) {
                //cout << nx <<" "<<i<<" "<< j << endl;
                if (nx >= board_right) return 2;
                if (nx < board_left) return 1;
                if (ny >= board_bottom || ny > 250 + s*block_size)  {
                    //cout << "ny: " << ny << "s: "<< 250 + s*block_size << endl; 
                    return 3;
                }
            }
        }
    }

    return check;
    
}

