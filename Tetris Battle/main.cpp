//
//  main.cpp
//  Tetris Battle
//
//  Created by Starla on 2018/6/2.
//  Copyright © 2018年 Starla. All rights reserved.
//

// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_font.h>

#include "GameWindow.h"


using namespace std;

int main(int argc, char *argv[]) {
    GameWindow *TetrisBattle = new GameWindow();
    TetrisBattle->game_play();
    
    
    
    return 0;
}
