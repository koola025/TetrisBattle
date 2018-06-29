#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "global.h"
#include "Piece.h"
#include "lightblue.h"
#include "red.h"
#include "yellow.h"
#include "green.h"
#include "orange.h"
#include "pink.h"
#include "darkblue.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define board_width 450
#define board_height 765

#define block_size 45
#define brick_num 11

#define b1_middle 625
class Board
{
    public:
        // constructor
        Board(int x, int y): Pos_x(x), Pos_y(y) {
            //pink = al_load_bitmap("./img/pink.png");
            //black1 = al_load_bitmap("./img/black1.png");
            //black2 = al_load_bitmap("./img/black2.png");
            
            loadBricks();
            init();
            
        }
        void loadBricks();
        void init();
        void gameOver();
        void destroy();
        void reset();

        Piece *newPiece();
        Piece *copyPiece();
        void pieceDown();
        void pieceLeft();
        void pieceRight();
        void pieceRotate();
        void pieceDrop();
        void pieceHold();
        void addPiece();
        void addShadow();
        void addStone();
        void deleteStone();
        void checkLine();
        void deleteLine(int line);
        void shiftDown(int line);
        void shiftUp(int line);
        bool touches(int x, int y, int d, bool s);
        void draw();
        void drawBlack();
        void drawOrigin(int i, int j);
        void mute(bool m);

        ALLEGRO_BITMAP* getPic(string color) {return picPointer[colorPic[color]];}
        int getLines() {return lines;}
        int getGarbageLines() {return garbageLines;}
        int getX() {return Pos_x;}
        int getY() {return Pos_y;}
        void addGarbageLines();

        map<string, int> colorPic;
        char bricksColor[brick_num][20] = {"pink", "red", "yellow", "orange", "green", "darkblue", "lightblue", "black1", "black2","stone","bomb"};
        ALLEGRO_BITMAP* picPointer[brick_num];
        int board_state;
        bool stop;
        int forEnemy;
        int loseTimes;
        int combos;
        int comboCheck;
        int gameOverCount;
        bool boardMute;
    private:
        int Pos_x;
        int Pos_y;
        int lines;
        int garbageLines;
        int stoneLine;
        bool needDeleteStone;
        int oldLines;
        bool addingPiece;
        
        ALLEGRO_SAMPLE *sample = NULL;
        ALLEGRO_SAMPLE_INSTANCE *erase1 = NULL;
        ALLEGRO_SAMPLE_INSTANCE *rotate = NULL;
        ALLEGRO_SAMPLE_INSTANCE *hardDrop = NULL;
        ALLEGRO_SAMPLE_INSTANCE *died = NULL;
        ALLEGRO_SAMPLE_INSTANCE *hold = NULL;
        
        ALLEGRO_SAMPLE_INSTANCE *combo1 = NULL;
        ALLEGRO_SAMPLE_INSTANCE *combo2 = NULL;
        ALLEGRO_SAMPLE_INSTANCE *combo3 = NULL;
        ALLEGRO_SAMPLE_INSTANCE *combo4 = NULL;
        ALLEGRO_SAMPLE_INSTANCE *combo5 = NULL;
        
        
        
        Piece *curPiece, *nextPiece, *shadowPiece, *holdPiece;
        
        string color[17][10];
        ALLEGRO_BITMAP* gameover = NULL;
        ALLEGRO_BITMAP* box = NULL;
        //ALLEGRO_BITMAP* stone = NULL;

        //ALLEGRO_BITMAP *pink = NULL;
        //ALLEGRO_BITMAP *black1 = NULL;
       //ALLEGRO_BITMAP *black2 = NULL;


};



#endif // BUTTON_H_INCLUDED
