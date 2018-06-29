#include "GameWindow.h"


using namespace std;


GameWindow::GameWindow(){
    al_init();
    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);
    
    
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();  // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0);
    bigFont = al_load_ttf_font("Caviar_Dreams_Bold.ttf",72,0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    game_init();
}

void GameWindow::game_destroy() {


    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_bitmap(youWin);
    al_destroy_bitmap(youLose);
    al_destroy_bitmap(again);        
    al_destroy_bitmap(list);

    delete startButton;
    delete twoPlayerBtn;
    delete homeButton;
    delete retryButton;
    if (board1) {
        board1->destroy();
        delete board1;
    }
    if (board2) {
        board2->destroy();
        delete board2;
    }

}

void GameWindow::game_init() {
    startButton = new Button(window_width/2 - 150, window_height/2 , 300, 100);
    twoPlayerBtn = new Button(window_width/2 - 150, window_height/2 + 200, 300, 100);
    homeButton = new Button(window_width/2 - 350, 1100, 300, 100);
    retryButton = new Button(window_width/2 + 50, 1100 , 300, 100);
    youWin = al_load_bitmap("./img/youWin.png");
    youLose = al_load_bitmap("./img/youLose.png");
    tie = al_load_bitmap("./img/tie.png");
    
    again = al_load_bitmap("./img/again.png");
    list = al_load_bitmap("./img/list.png");
    gameover = al_load_bitmap("./img/gameover.png");
    al_reserve_samples(3);
    sample = al_load_sample("TetrisBattleMusic.ogg");
    backgroundMusic = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundMusic, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundMusic, al_get_default_mixer());

    sample = al_load_sample("excellent.wav");
    excellentSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(excellentSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(excellentSound, al_get_default_mixer());

    sample = al_load_sample("gameover.wav");
    gameoverSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(gameoverSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(gameoverSound, al_get_default_mixer());
    
    sample = al_load_sample("countdown.wav");
    countdownSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(countdownSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(countdownSound, al_get_default_mixer());
    
    nowMute = false;
    //game_start_scene();
}

void GameWindow::game_play() {
    // al_rest(10.0);
    // game_destroy();

    
    int msg = GAME_INIT;
    game_start_scene();
    while(msg != GAME_EXIT) {
        if (!al_is_event_queue_empty(event_queue)) {

            msg = process_event();
            if (msg == GAME_PLAY) {
                game_play_scene();
            }
            else if (msg == GAME_PLAY2) {
                game_play_scene2();
            }
            else if (msg == GAME_START) {
                game_start_scene();
            }
        }
        else msg = GAME_CONTINUE;
    }
    if (msg == GAME_EXIT) {
        game_destroy();
    }

}

void GameWindow::game_reset() {
    al_stop_timer(timer);
}

int GameWindow::process_event() {
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            //cout << "intimer" <<endl;
            if (scene == GAME_PLAY2) {
                if (countDown == 15) al_play_sample_instance(countdownSound);
                if (countDown > 0) countDown--;
                else {
                    game_end();
                }
                if (board1->board_state == 1) {
                    board1->pieceDown();
                    redraw = true;
                }
                else {
                    if (board1->gameOverCount > 0) board1->gameOverCount--;
                    else if (board1->gameOverCount == 0 && countDown!=0){
                        board1->reset();
                        
                    }
                }
                if (board2->board_state == 1) {
                    board2->pieceDown();
                    redraw = true;
                }
                else {
                    if (board2->gameOverCount > 0) board2->gameOverCount--;
                    else if (board2->gameOverCount == 0 && countDown!=0){
                        board2->reset();
                    }
                }
                
                while(board1->forEnemy > 0) {
                    board2->addGarbageLines();
                    board1->forEnemy--;
                }
                
                
                while(board2->forEnemy > 0) {
                    board1->addGarbageLines();
                    board2->forEnemy--;
                }
            }
            else if (scene == GAME_PLAY) {
                if (countDown == 15) {
                    al_play_sample_instance(countdownSound);
                    al_set_sample_instance_gain(countdownSound, !nowMute);
                    
                }
                if (countDown > 0) countDown--;
                else {
                    game_end1();
                }

                if (board1->board_state == 1) {
                    board1->pieceDown();
                    redraw = true;
                }
                else if (board1->board_state == 0) {
                    game_end1();
                }
                /*else {
                    if (board1->gameOverCount > 0) board1->gameOverCount--;
                    else if (board1->gameOverCount == 0 && countDown!=0){
                        board1->reset();
                        
                    }
                }*/
            }
            
            

        }
        
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        instruction = GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if (scene == GAME_START) {
                if (startButton->mouseIn(mouse_x, mouse_y)) {
                    draw_start_scene();
                    startButton->drawClicked("One Player");
                    al_flip_display();    
                    startButton->clicking = true;
                }
                else if (twoPlayerBtn->mouseIn(mouse_x, mouse_y)) {
                    draw_start_scene();
                    twoPlayerBtn->drawClicked("Two Player");
                    al_flip_display();    
                    twoPlayerBtn->clicking = true;
                }
            }
            else if (scene == GAME_END) {
                if (homeButton->mouseIn(mouse_x, mouse_y)) {
                    draw_end();
                    homeButton->drawClicked("Home");
                    al_flip_display();    
                    homeButton->clicking = true;
                }
                else if (retryButton->mouseIn(mouse_x, mouse_y)) {
                    draw_end();
                    retryButton->drawClicked("Try Again");
                    al_flip_display();    
                    retryButton->clicking = true;
                }
            }
            else if (scene == GAME_END1) {
                if (homeButton->mouseIn(mouse_x, mouse_y)) {
                    draw_end1();
                    homeButton->drawClicked("Home");
                    al_flip_display();    
                    homeButton->clicking = true;
                }
                else if (retryButton->mouseIn(mouse_x, mouse_y)) {
                    draw_end1();
                    retryButton->drawClicked("Try Again");
                    al_flip_display();    
                    retryButton->clicking = true;
                }
            }
                
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        if (scene == GAME_START) {
            startButton->clicking = false;
            twoPlayerBtn->clicking = false;
            if (startButton->mouseIn(mouse_x, mouse_y)) {
                draw_start_scene();
                startButton->drawHover("One Player");
                al_flip_display();    
                instruction = GAME_PLAY;
            }
            else if (twoPlayerBtn->mouseIn(mouse_x, mouse_y)) {
                draw_start_scene();
                twoPlayerBtn->drawHover("Two Player");
                al_flip_display();    
                instruction = GAME_PLAY2;
            }
            else redraw = true;
        }
        else if (scene == GAME_END) {
            homeButton->clicking = false;
            retryButton->clicking = false;
            if (homeButton->mouseIn(mouse_x, mouse_y)) {
                draw_end();
                homeButton->drawHover("Home");
                al_flip_display();    
                instruction = GAME_START;
            }
            else if (retryButton->mouseIn(mouse_x, mouse_y)) {
                draw_end();
                retryButton->drawHover("Try Again");
                al_flip_display();    
                instruction = GAME_PLAY2;
            }
            else redraw = true;
        }
        else if (scene == GAME_END1) {
            homeButton->clicking = false;
            retryButton->clicking = false;
            if (homeButton->mouseIn(mouse_x, mouse_y)) {
                cout << "home in" << endl;
                draw_end1();
                homeButton->drawHover("Home");
                al_flip_display();    
                instruction = GAME_START;
                cout << "given instruction" << endl;
            }
            else if (retryButton->mouseIn(mouse_x, mouse_y)) {
                draw_end1();
                retryButton->drawHover("Try Again");
                al_flip_display();    
                instruction = GAME_PLAY;
            }
            else redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        if (scene == GAME_START) {
            if (startButton->mouseIn(mouse_x, mouse_y) && !startButton->clicking) {
                draw_start_scene();
                startButton->drawHover("One Player");
                al_flip_display();    
                //cout << "hover" << endl;
            }
            else if (twoPlayerBtn->mouseIn(mouse_x, mouse_y) && !twoPlayerBtn->clicking) {
                draw_start_scene();
                twoPlayerBtn->drawHover("Two Player");
                al_flip_display();    
                //cout << "hover" << endl;
            }
            else if (!startButton->clicking && !twoPlayerBtn->clicking) redraw = true;
        }
        else if (scene == GAME_END) {
            if (homeButton->mouseIn(mouse_x, mouse_y) && !homeButton->clicking) {
                draw_end();
                homeButton->drawHover("Home");
                al_flip_display();    
                //cout << "hover" << endl;
            }
            else if (retryButton->mouseIn(mouse_x, mouse_y) && !retryButton->clicking) {
                draw_end();
                
                retryButton->drawHover("Try Again");
                al_flip_display();    
                //cout << "hover try" << endl;
            }
            else if (!homeButton->clicking && !retryButton->clicking) redraw = true;

        }
        else if (scene == GAME_END1) {
            if (homeButton->mouseIn(mouse_x, mouse_y) && !homeButton->clicking) {
                draw_end1();
                homeButton->drawHover("Home");
                al_flip_display();    
                //cout << "hover" << endl;
            }
            else if (retryButton->mouseIn(mouse_x, mouse_y) && !retryButton->clicking) {
                draw_end1();
                
                retryButton->drawHover("Try Again");
                al_flip_display();    
                //cout << "hover try" << endl;
            }
            else if (!homeButton->clicking && !retryButton->clicking) redraw = true;

        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_H:
                instruction = GAME_START;
            break;
            case ALLEGRO_KEY_R:
                if (scene == GAME_PLAY) instruction = GAME_PLAY;
                else if (scene == GAME_PLAY2) instruction = GAME_PLAY2;
            break;
            case ALLEGRO_KEY_M:
                mute();
            break;
            case ALLEGRO_KEY_P:
                if (scene == GAME_PLAY || scene == GAME_PLAY2)pause();
                
            break;

            case ALLEGRO_KEY_LEFT:
                cout << "LEFT" << endl;
                if (board1->board_state== 1)board1->pieceLeft();
                redraw = true;
            break;

            case ALLEGRO_KEY_RIGHT:
                cout << "RIGHT" << endl;
                if (board1->board_state== 1)board1->pieceRight();
                redraw = true;
            break;
            
            case ALLEGRO_KEY_DOWN:
                cout << "DOWN" << endl;
                if (board1->board_state== 1 && !board1->stop)board1->pieceDown();
                redraw = true;
            break;

            case ALLEGRO_KEY_UP:
                cout << "UP" << endl;
                if (board1->board_state== 1)board1->pieceRotate();
                redraw = true;
                
            break;

            case ALLEGRO_KEY_SPACE:
                cout << "SPACE" << endl;
                if (board1->board_state== 1)board1->pieceDrop();
                redraw = true;
                
            break;

            case ALLEGRO_KEY_X:
                cout << "X" <<endl;
                if (board1->board_state== 1)board1->addGarbageLines();
                redraw = true;
                
            break;

            case ALLEGRO_KEY_ENTER:
                cout << "ENTER" <<endl;
                if (board1->board_state== 1)board1->pieceHold();
                redraw = true;
                
            break;
//////////////////////////////////////////////
            case ALLEGRO_KEY_A:
                cout << "A" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1)board2->pieceLeft();
                    redraw = true;
                }
                
                
            break;

            case ALLEGRO_KEY_S:
                cout << "S" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1 && !board2->stop)board2->pieceDown();
                    redraw = true;
                }
                
            break;

            case ALLEGRO_KEY_D:
                cout << "D" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1)board2->pieceRight();
                    redraw = true;
                }
            break;

            case ALLEGRO_KEY_W:
                cout << "W" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1)board2->pieceRotate();
                    redraw = true;
                }
                
            break;

            case ALLEGRO_KEY_LSHIFT:
                cout << "SHIFT" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1)board2->pieceDrop();
                    redraw = true;
                }
                
            break;


            case ALLEGRO_KEY_TAB:
                cout << "TAB" <<endl;
                if (scene == GAME_PLAY2) {
                    if (board2->board_state == 1)board2->pieceHold();
                    redraw = true;
                }
                
            break;
        }
    }

    if (redraw) {
        if (scene == GAME_START) {
            draw_start_scene();
            al_flip_display();
        }
        else if (scene == GAME_PLAY) {
            draw_play_scene();
            al_flip_display();
        }
        else if (scene == GAME_PLAY2) {
            draw_play_scene2();
            al_flip_display();
        }
        else if (scene == GAME_END) {
            draw_end();
            al_flip_display();
        }
        else if (scene == GAME_END1) {
            draw_end1();
            al_flip_display();
        }
        redraw = false;
    }

    return instruction;
}

void GameWindow::game_start_scene() {
    al_stop_sample_instance(backgroundMusic);
    countDown = 30;
    scene = GAME_START;
    cout << "ssstart" << endl;
    if (board1) delete board1;
    cout << "ssstart f" << endl;
    if (board2) delete board2;
    cout << "ssstart s" << endl;
    draw_start_scene();
    al_flip_display();    
    
}

void GameWindow::draw_start_scene() {
    al_clear_to_color(al_map_rgb(255, 160, 170));
    startButton->drawNormal("One Player");
    twoPlayerBtn->drawNormal("Two Player");
    al_draw_text(bigFont, al_map_rgb(255, 255, 255), window_width/2, 320, 1, "TETRIS BATTLE");
    
    
}

void GameWindow::game_play_scene() {
    countDown = 60;
    scene = GAME_PLAY;
    al_stop_sample_instance(backgroundMusic);    
    al_play_sample_instance(backgroundMusic);
    al_set_sample_instance_gain(backgroundMusic, !nowMute);
    
    board1 = new Board(735,250);
    board2 = new Board(400,250);
    board2->board_state = -1;
    board1->mute(nowMute);
    board2->mute(nowMute);
    al_start_timer(timer);
    draw_play_scene();
    al_flip_display();    
    
}

void GameWindow::game_play_scene2() {
    scene = GAME_PLAY2;
    
    al_stop_sample_instance(backgroundMusic);
    al_play_sample_instance(backgroundMusic);
    al_set_sample_instance_gain(backgroundMusic, !nowMute);
    
    countDown = 100;
    board1 = new Board(1220,250);
    board2 = new Board(250,250);
    board1->mute(nowMute);
    board2->mute(nowMute);
    al_start_timer(timer);
    draw_play_scene2();
    al_flip_display();    
    
}

void GameWindow::draw_play_scene2() {
    al_clear_to_color(al_map_rgb(255, 220, 220));
    board1->draw();
    board2->draw();

    char buffer[50];
    sprintf(buffer, "COUNT DOWN: %d", countDown);
    al_draw_text(bigFont, al_map_rgb(229, 115, 115), window_width/2, 100, 1, buffer);

    
    sprintf(buffer, "%d", board1->getLines());
    al_draw_text(font, al_map_rgb(255, 255, 255), 1125, 367, 1, buffer);
    sprintf(buffer, "%d", board2->loseTimes);
    al_draw_text(font, al_map_rgb(255, 255, 255), 1125, 563, 1, buffer);
    sprintf(buffer, "%d", board1->combos);
    al_draw_text(font, al_map_rgb(255, 255, 255), 1757, 933, 1, buffer);
    //sprintf(buffer, "ch: %d", board1->comboCheck);
    //al_draw_text(font, al_map_rgb(255, 255, 255), 1725, 863, 1, buffer);

    
    sprintf(buffer, "%d", board2->getLines());
    al_draw_text(font, al_map_rgb(255, 255, 255), 155, 367, 1 , buffer);
    sprintf(buffer, "%d", board1->loseTimes);
    al_draw_text(font, al_map_rgb(255, 255, 255), 155, 563, 1, buffer);
    sprintf(buffer, "%d", board2->combos);
    al_draw_text(font, al_map_rgb(255, 255, 255), 788, 933, 1, buffer);
}

void GameWindow::draw_play_scene() {
    al_clear_to_color(al_map_rgb(255, 220, 220));
    board1->draw();

    char buffer[50];
    sprintf(buffer, "COUNT DOWN: %d", countDown);
    al_draw_text(bigFont, al_map_rgb(229, 115, 115), window_width/2, 100, 1, buffer);

    sprintf(buffer, "%d", board1->getLines());
    al_draw_text(font, al_map_rgb(255, 255, 255), 640, 367, 1 , buffer);
    al_draw_text(font, al_map_rgb(255, 255, 255), 640, 563, 1, "-");
    sprintf(buffer, "%d", board1->combos);
    al_draw_text(font, al_map_rgb(255, 255, 255), 1273, 933, 1, buffer);
    
}

void GameWindow::game_end() {
    scene = GAME_END;
    al_stop_sample_instance(backgroundMusic);
    al_play_sample_instance(excellentSound);
    al_set_sample_instance_gain(excellentSound, !nowMute);
    
    al_play_sample_instance(gameoverSound);
    al_set_sample_instance_gain(gameoverSound, !nowMute);
    
    al_stop_timer(timer);
    board1->board_state = -1;
    board2->board_state = -1;
    draw_end();
    al_flip_display();  
    
}

void GameWindow::game_end1() {
    scene = GAME_END1;
    al_stop_sample_instance(backgroundMusic);
    if (board1->board_state != 0){
        al_play_sample_instance(excellentSound);
        al_set_sample_instance_gain(excellentSound, !nowMute);
        
    }
    else {
        al_play_sample_instance(gameoverSound);
        al_set_sample_instance_gain(gameoverSound, !nowMute);        
    }
    al_stop_timer(timer);
    
    draw_end1();
    if(board1->board_state == 1)board1->board_state = -1;
    al_flip_display();  
    
}

void GameWindow::draw_end() {
    
    draw_play_scene2();
    if (board1->loseTimes < board2->loseTimes || (board1->loseTimes == board2->loseTimes && board1->getLines() > board2->getLines()) ) {
        al_draw_filled_rectangle(board1->getX(), board1->getY(), board1->getX() + board_width, board1->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(youWin,0,0,600,370,board1->getX() + 75,550,300,185,0);
        al_draw_filled_rectangle(board2->getX(), board2->getY(), board2->getX() + board_width, board2->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(youLose,0,0,600,370,board2->getX() + 75,550,300,185,0);
    }
    else if (board1->loseTimes > board2->loseTimes || (board1->loseTimes == board2->loseTimes && board1->getLines() < board2->getLines()) ){
        al_draw_filled_rectangle(board1->getX(), board1->getY(), board1->getX() + board_width, board1->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(youLose,0,0,600,370,board1->getX() + 75,550,300,185,0);
        al_draw_filled_rectangle(board2->getX(), board2->getY(), board2->getX() + board_width, board2->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(youWin,0,0,600,370,board2->getX() + 75,550,300,185,0);
    }
    else {
        al_draw_filled_rectangle(board1->getX(), board1->getY(), board1->getX() + board_width, board1->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(tie,0,0,600,370,board1->getX() + 75,550,300,185,0);
        al_draw_filled_rectangle(board2->getX(), board2->getY(), board2->getX() + board_width, board2->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(tie,0,0,600,370,board2->getX() + 75,550,300,185,0);
    }
    //al_draw_bitmap(again, 1010, 1100, 0);
    //al_draw_bitmap(list,  810, 1100, 0);
    homeButton->drawNormal("Home");
    retryButton->drawNormal("Try Again");
    
}

void GameWindow::draw_end1() {
    
    draw_play_scene();
    if (board1->loseTimes == 0) {
        al_draw_filled_rectangle(board1->getX(), board1->getY(), board1->getX() + board_width, board1->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        char buffer[50];
        sprintf(buffer, "%d LINES", board1->getLines());
        al_draw_text(bigFont, al_map_rgb(255, 255, 255), window_width/2, 500, 1, buffer);

    
        //al_draw_scaled_bitmap(youWin,0,0,600,370,board1->getX() + 75,550,300,185,0);
    }
    else {
        al_draw_filled_rectangle(board1->getX(), board1->getY(), board1->getX() + board_width, board1->getY() + board_height, al_map_rgba(0, 0, 0, 100));
        al_draw_scaled_bitmap(gameover,0,0,600,370,board1->getX() + 75,550,300,185,0);
        
    }
    //al_draw_bitmap(again, 1010, 1100, 0);
    //al_draw_bitmap(list,  810, 1100, 0);
    homeButton->drawNormal("Home");
    retryButton->drawNormal("Try Again");
    
}


void GameWindow::pause() {
    if (al_get_timer_started(timer)){
        al_stop_timer(timer);
        board1->board_state = -1;
        board2->board_state = -1;
        al_set_sample_instance_gain(backgroundMusic, 0);
    }
    else {
        al_start_timer(timer);
        board1->board_state = 1;
        board2->board_state = 1;
        al_set_sample_instance_gain(backgroundMusic, !nowMute);
        
    }
    

}


void GameWindow::mute() {
    

    if (nowMute) {
        nowMute = false;

        al_set_sample_instance_gain(backgroundMusic, !nowMute);
    }
    else {
        nowMute = true;
        al_set_sample_instance_gain(backgroundMusic, !nowMute);
    }
    board1->mute(nowMute);
    board2->mute(nowMute);
}