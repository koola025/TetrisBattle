#include "Board.h"
#include "GameWindow.h"


void Board::loadBricks() {
    for(int i = 0; i < brick_num; i++) {
        char filename[50];
        ALLEGRO_BITMAP *bitmap;
        sprintf(filename, "./img/%s.png", bricksColor[i]);
        picPointer[i] = al_load_bitmap(filename);
        
        colorPic[bricksColor[i]] = i;
    }
    gameover = al_load_bitmap("./img/gameover.png");
    box = al_load_bitmap("./img/box.png");
    //stone = al_load_bitmap("./img/stone.png");
    al_reserve_samples(3);
    sample = al_load_sample("erase1.wav");
    erase1 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(erase1, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(erase1, al_get_default_mixer());

    sample = al_load_sample("rotate.wav");
    rotate = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(rotate, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(rotate, al_get_default_mixer());

    sample = al_load_sample("hardDrop.wav");
    hardDrop = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hardDrop, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hardDrop, al_get_default_mixer());

    sample = al_load_sample("died.wav");
    died = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(died, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(died, al_get_default_mixer());

    sample = al_load_sample("hold.wav");
    hold = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hold, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hold, al_get_default_mixer());

    sample = al_load_sample("combo1.wav");
    combo1 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(combo1, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(combo1, al_get_default_mixer());

    sample = al_load_sample("combo2.wav");
    combo2 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(combo2, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(combo2, al_get_default_mixer());

    sample = al_load_sample("combo3.wav");
    combo3 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(combo3, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(combo3, al_get_default_mixer());

    sample = al_load_sample("combo4.wav");
    combo4 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(combo4, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(combo4, al_get_default_mixer());

    sample = al_load_sample("combo5.wav");
    combo5 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(combo5, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(combo5, al_get_default_mixer());
}

void Board::init() {
    forEnemy = 0;
    board_state = 1;
    loseTimes = 0;
    comboCheck = 0;
    combos = 0;
    gameOverCount = 0;
    stop = false;
    addingPiece = false;
    needDeleteStone = false;
    boardMute = false;
    
    oldLines = 0;
    lines = 0;
    garbageLines = 0;
    stoneLine = 16;
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 10; j++) {
            drawOrigin(i, j);
        }
    }
    curPiece = newPiece();
    //cout << "creating shadow"<<endl;
    shadowPiece = copyPiece();
    addShadow();
    //cout << "finish shadow"<<endl;
    nextPiece = newPiece();
    holdPiece = NULL;
    //nextPiece->Pos_x +=390;
}

void Board::reset() {
    cout << "board reset" << endl;
    if (curPiece) delete curPiece;
    if (shadowPiece) delete shadowPiece;
    if (nextPiece) delete nextPiece;
    if (holdPiece) delete holdPiece;
    forEnemy = 0;
    board_state = 1;
    //loseTimes = 0;
    comboCheck = 0;
    combos = 0;
    gameOverCount = 0;
    boardMute = false;
    
    stop = false;
    addingPiece = false;
    needDeleteStone = false;
    
    oldLines = 0;
    //lines = 0;
    garbageLines = 0;
    stoneLine = 16;
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 10; j++) {
            drawOrigin(i, j);
        }
    }
    curPiece = newPiece();
    //cout << "creating shadow"<<endl;
    shadowPiece = copyPiece();
    addShadow();
    //cout << "finish shadow"<<endl;
    nextPiece = newPiece();
    holdPiece = NULL;
    //nextPiece->Pos_x +=390;
}

void Board::destroy() {
    al_destroy_bitmap(gameover);
    al_destroy_bitmap(box);
    
}

void Board::gameOver() {
    board_state = 0;
    al_play_sample_instance(died);
    al_set_sample_instance_gain(died, !boardMute);
    gameOverCount = 2;
    loseTimes++;
    //draw();
    //al_flip_display();

    
    
    cout << "at over"<< endl;
    
    //al_rest(1);
    //reset();
}

Piece* Board::newPiece() {
    
    int ran =  rand() % 7;
    Piece *piece;


    if (ran == 0) 
    piece = new pink(Pos_x + 90, Pos_y-45, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 1) 
    piece = new red(Pos_x + 90, Pos_y-45, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 2) 
    piece = new yellow(Pos_x + 90, Pos_y-90, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 3) 
    piece = new orange(Pos_x + 90, Pos_y-45, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 4) 
    piece = new green(Pos_x + 90, Pos_y-45, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 5) 
    piece = new darkblue(Pos_x + 90, Pos_y-45, Pos_x, Pos_x+board_width, Pos_y + board_height);
    else if (ran == 6) 
    piece = new lightblue(Pos_x + 90, Pos_y-135, Pos_x, Pos_x+board_width, Pos_y + board_height);

    cout << "new piece: "<< piece->getColor() << endl;


    return piece;
}

Piece* Board::copyPiece() {
    
    Piece *piece = NULL;
    if (curPiece->getColor() == "lightblue") {
        piece = new lightblue(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "pink") {
        piece = new pink(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "red") {
        piece = new red(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "orange") {
        piece = new orange(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "yellow") {
        piece = new yellow(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "green") {
        piece = new green(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    else if (curPiece->getColor() == "darkblue") {
        piece = new darkblue(Pos_x + 90, Pos_y, Pos_x, Pos_x+board_width, Pos_y + board_height);
    }
    




    return piece;
}



void Board::draw() {
    

    //cout << "board draw" << endl;    
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 10; j++) {
            al_draw_bitmap(getPic(color[i][j]), Pos_x + j * block_size, Pos_y + i * block_size, 0);
        
        }
    }
    
    addShadow();
    shadowPiece->drawShadow();
    
    curPiece->draw();
   
    al_draw_filled_rectangle(Pos_x, Pos_y-135, Pos_x + board_width, Pos_y,  al_map_rgb(255, 220, 220));
   
    al_draw_bitmap(box, Pos_x - 250 , Pos_y - 218 , 0);
    nextPiece->drawSmall();
    if (holdPiece) holdPiece->drawHold();
    //cout << "done draw" << endl;
    if (board_state == 0) {
        al_draw_filled_rectangle(Pos_x, Pos_y, Pos_x + board_width, Pos_y + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(gameover,0,0,600,370,Pos_x + 75,550,300,185,0);
    }
    
}

void Board::drawBlack() {
    
 
    for(int i = 0; i < 17; i++) {
        for(int j = 0; j < 10; j++) {
            al_draw_bitmap(getPic(color[i][j]), Pos_x + j * block_size, Pos_y + i * block_size, 0);
        
        }
    }
    
    addShadow();
    shadowPiece->drawShadow();
    curPiece->draw();
    
   
    al_draw_filled_rectangle(Pos_x, Pos_y-135, Pos_x + board_width, Pos_y-10,  al_map_rgb(255, 220, 220));
   
    //al_draw_bitmap(box, Pos_x - 250 , Pos_y - 218 , 0);
    nextPiece->drawSmall();
    if (holdPiece) holdPiece->drawHold();
    //cout << "done draw" << endl;
    if (board_state == 0) {
        al_draw_filled_rectangle(Pos_x, Pos_y, Pos_x + board_width, Pos_y + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(gameover,0,0,600,370,Pos_x + 75,550,300,185,0);
    }
    
}

void Board::drawOrigin(int i, int j) {
    if ( (i+j) % 2 ) color[i][j] = "black1";
    else color[i][j] = "black2";
}

void Board::deleteLine(int line){
    for(int i = 0; i < 10; i++) {
        drawOrigin(line, i);
    }
    lines++;
    if (lines - oldLines > 2) {
        forEnemy++;
        oldLines = lines;
    }
    al_play_sample_instance(erase1);
    al_set_sample_instance_gain(erase1, !boardMute);

}

void Board::shiftDown(int line){
    for(int i = line; i >= 1; i--) {
        for(int j = 0; j < 10; j++) {
            if (color[i-1][j] != "black1" && color[i-1][j] != "black2") {
                color[i][j] = color[i-1][j];
            }
            else {
                drawOrigin(i, j);
            }
        }
    }
}

void Board::shiftUp(int line){
    for(int i = 0; i < line; i++) {
        for(int j = 0; j < 10; j++) {
            if (color[i+1][j] != "black1" && color[i+1][j] != "black2") {
                color[i][j] = color[i+1][j];
            }
            else {
                drawOrigin(i, j);
            }
        }
    }
}

void Board::addGarbageLines(){
    garbageLines++;
    if (!addingPiece) {
        addStone();
    }
    else cout << "in adding" << endl;
    
}

void Board::pieceDown() {
    if(touches(curPiece->Pos_x, curPiece->Pos_y + block_size, curPiece->dir, false)) {
        addingPiece = true;
        cout << "by1" << endl;
        addPiece();
        if (needDeleteStone) {
            deleteStone();
            
            needDeleteStone = false;
        }
        
    }
    else if (curPiece->outBounds(curPiece->Pos_x, curPiece->Pos_y + block_size, curPiece->dir, stoneLine)) {
        addingPiece = true;
        cout << "by2" << endl;
        
        addPiece();
    }
    else {
        curPiece->Pos_y += block_size;
        //cout << "go down" << endl;
    }

}


void Board::pieceLeft() {
    if (!curPiece->outBounds(curPiece->Pos_x - block_size, curPiece->Pos_y, curPiece->dir, stoneLine) && !touches(curPiece->Pos_x - block_size, curPiece->Pos_y, curPiece->dir, false)) curPiece->Pos_x -= block_size;

}

void Board::pieceRight() {
    if (!curPiece->outBounds(curPiece->Pos_x + block_size, curPiece->Pos_y, curPiece->dir, stoneLine) && !touches(curPiece->Pos_x + block_size, curPiece->Pos_y, curPiece->dir, false)) curPiece->Pos_x += block_size;

}

void Board::pieceRotate() {
    if (curPiece->outBounds(curPiece->Pos_x, curPiece->Pos_y, (curPiece->dir - 1 + 4) % 4, stoneLine) != 3 && !touches(curPiece->Pos_x, curPiece->Pos_y, (curPiece->dir - 1 + 4) % 4, false)) {
        curPiece->dir = (curPiece->dir - 1 + 4) % 4;
        al_play_sample_instance(rotate);
        al_set_sample_instance_gain(rotate, !boardMute);
        
    }
    
    while (curPiece->outBounds(curPiece->Pos_x, curPiece->Pos_y, curPiece->dir, stoneLine) == 1) {
        curPiece->Pos_x += block_size;
    }
    while (curPiece->outBounds(curPiece->Pos_x, curPiece->Pos_y, curPiece->dir, stoneLine) == 2) {
        curPiece->Pos_x -= block_size;
    }

}

void Board::pieceDrop() {
    al_stop_sample_instance(hardDrop);
    curPiece->Pos_y = shadowPiece->Pos_y;
    addingPiece = true;
    if(touches(curPiece->Pos_x, curPiece->Pos_y + block_size, curPiece->dir, false))
        cout << "by3" << endl;
    addPiece();
    al_play_sample_instance(hardDrop);
    al_set_sample_instance_gain(hardDrop, !boardMute);
    
    
    if (needDeleteStone) {
            deleteStone();
            needDeleteStone = false;
    }
    
}

void Board::pieceHold() {
    Piece *tmp = NULL;
    if (holdPiece) {
        tmp = curPiece;
        curPiece = holdPiece;
        holdPiece = tmp;
    }
    else {
        holdPiece = curPiece;
        curPiece = nextPiece;
        nextPiece = newPiece();
    }
    al_play_sample_instance(hold);
    al_set_sample_instance_gain(hold, !boardMute);
    
    cout << "hold on" << endl;
    curPiece->Pos_x = Pos_x + 90;
    if (curPiece->getColor() == "lightblue") curPiece->Pos_y = Pos_y - 135;
    else if (curPiece->getColor() == "yellow") curPiece->Pos_y = Pos_y - 90;
    else curPiece->Pos_y = Pos_y - 45;

    holdPiece->Pos_x = Pos_x + 90;
    holdPiece->dir = 0;
    if (holdPiece->getColor() == "lightblue") holdPiece->Pos_y = Pos_y - 135;
    else if (holdPiece->getColor() == "yellow") holdPiece->Pos_y = Pos_y - 90;
    else holdPiece->Pos_y = Pos_y - 45;

    delete shadowPiece;
    shadowPiece = copyPiece();
    addShadow();
    
}

void Board::addShadow() {
    int x = curPiece->Pos_x;
    int y = curPiece->Pos_y;
    int d = curPiece->dir;
    while(!touches(x, y + block_size, d, true) && !shadowPiece->outBounds(x, y + block_size, d, stoneLine)) {
        y += block_size;

    }
    shadowPiece->Pos_x = x;
    shadowPiece->Pos_y = y;
    shadowPiece->dir = d;

}

void Board::addStone() {
    cout << "add stone" << endl;
    
    
    if(touches(curPiece->Pos_x, curPiece->Pos_y, curPiece->dir, false)) {
        //addPiece();
        stop = true;
    }
    else if(touches(curPiece->Pos_x, curPiece->Pos_y + block_size, curPiece->dir, false) || curPiece->outBounds(curPiece->Pos_x, curPiece->Pos_y + block_size, curPiece->dir, stoneLine)) {
        //stop = true;
        addPiece();
        if (needDeleteStone) {
            deleteStone();
            needDeleteStone = false;
        }
    }
    else {
        shiftUp(16);
        //cout << "drawstone: " << stoneLine << endl;
        for(int i = 0; i < 10; i++) {
            color[16][i] = "stone";
        }
        int ran = rand()%10;
        color[16][ran] = "bomb";
        stoneLine--;
    }
    for(int i = 0; i < 10; i++) {
        if (color[0][i] != "black1" && color[0][i] != "black2") {
            gameOver();
            return;
        }
    }
}
void Board::deleteStone() {
    for(int i = 0; i < 10; i++) {
        drawOrigin(stoneLine+1, i);
    }
    stoneLine++;
    shiftDown(stoneLine);
    if (comboCheck > 1) {
        combos = 1;
        comboCheck = 0;
        al_play_sample_instance(combo1);
        al_set_sample_instance_gain(combo1, !boardMute);
    }
    else {
        combos++;
        comboCheck = 0;
        if (combos > 2) forEnemy++;
        
        /*if (combos == 2) 
        al_play_sample_instance(combo2);
        else if (combos == 3)
        al_play_sample_instance(combo3);
        else if (combos == 4)
        al_play_sample_instance(combo4);
        else */
        al_play_sample_instance(combo3);
        al_set_sample_instance_gain(combo3, !boardMute);
        
        
    }
}
void Board::addPiece() {
    comboCheck++;
    //if (comboCheck > 1) combos = 0;
    cout <<"add piece:" << comboCheck<<endl;
    if (touches(curPiece->Pos_x, curPiece->Pos_y, curPiece->dir, false)) {
        cout << "over" <<endl;
        gameOver();
        return;
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = curPiece->shape[curPiece->dir] & (1 << (15 - (i * 4 + j)));
            int nx = (curPiece->Pos_x - Pos_x) / block_size + j;
            int ny = (curPiece->Pos_y - Pos_y) / block_size + i;
            
            if (mask && ny >= 0) {
                
                color[ny][nx] = curPiece->getColor();
            }
        }
    }
    for(int i = 0; i < 10; i++) {
        if (color[0][i] != "black1" && color[0][i] != "black2") {
            gameOver();
            return;
        }
    }
    delete curPiece;
    delete shadowPiece;
    stop = false;
    addingPiece = false;
    //nextPiece->Pos_x = Pos_x + 90;
    curPiece = nextPiece;
    shadowPiece = copyPiece();
    nextPiece = newPiece();
    //nextPiece->Pos_x +=390;
   
    checkLine();
}

void Board::checkLine() {
    int count = 0;
    int firstLine = -1;
    for(int i = 0; i < 17; i++) {
        count = 0;
        for(int j = 0; j < 10; j++) {
            if (color[i][j] != "black1" && color[i][j] != "black2" & color[i][j] != "stone" ) count++;
        }
        if (count == 10) {
            if (comboCheck > 1) {
                cout << "first combo: " << combos <<endl;
                combos = 1;
                comboCheck = 0;
                al_play_sample_instance(combo1);
                al_set_sample_instance_gain(combo1, !boardMute);
                cout << combos <<endl;
            }
            else {
                cout << "add combo: " << combos <<endl;
                combos++;
                comboCheck = 0;
                if (combos > 2) forEnemy++;
                cout << combos <<endl;
                al_play_sample_instance(combo3);
                al_set_sample_instance_gain(combo3, !boardMute);
                
                /*if (combos == 2) {
                    if (al_get_sample_instance_playing(combo1))
                    al_play_sample_instance(combo2);
                }
                
                else if (combos == 3)
                al_play_sample_instance(combo3);
                else if (combos == 4)
                al_play_sample_instance(combo4);
                else 
                al_play_sample_instance(combo5);*/
            }
            deleteLine(i);
            //al_rest(0.2);
            shiftDown(i);
            //if (firstLine == -1) firstLine = i;
        }
        else {
            
        }
    }
    if (comboCheck > 0 && !needDeleteStone) {
            cout << "combos go to 0: " << combos <<endl;
            combos = 0;
            comboCheck = 0;
            cout << combos <<endl;
    }
    
}

bool Board::touches(int x, int y, int d, bool s) {
    bool check = false;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int mask = curPiece->shape[d] & (1 << (15 - (i * 4 + j)));
            int nx = (x - Pos_x) / block_size + j;
            int ny = (y - Pos_y) / block_size + i;
            if (mask && ny < 17 && ny >=0) {
                if (color[ny][nx] != "black1" && color[ny][nx] != "black2") {
                    //addingPiece = true;
                    check = true;
                    //cout << "touches: " << ny << " "<< nx << " " <<color[ny][nx]<< " "<< s <<  endl;
                    if (color[ny][nx] == "bomb" && !s) {
                        needDeleteStone = true;
                    }
                    //break;
                }
            }
        }
    }

    return check;
    
}

void Board::mute(bool m)  {
    if (!m) {
        
        
        
        
        boardMute = false;

        
    }
    else {
        
        boardMute = true;
    }
}