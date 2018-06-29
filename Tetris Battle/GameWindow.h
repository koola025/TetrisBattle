#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "global.h"
#include "Button.h"
#include "Board.h"
#include <vector>
#include <list>
#include <time.h>

#define GAME_INIT -1
#define GAME_START 0
#define GAME_SETTING 1
#define GAME_PLAY 2
#define GAME_PLAY2 3
#define GAME_CONTINUE 4
#define GAME_END 5
#define GAME_END1 6


#define GAME_EXIT 8



// clock rate
const float FPS = 1;

class GameWindow
{
    public:
        // constructor
        GameWindow();
        void game_destroy();

        void game_init();
        void game_play();
        void game_reset();

        void game_start_scene();
        void draw_start_scene();

        void game_play_scene();
        void draw_play_scene();

        void game_play_scene2();
        void draw_play_scene2();

        void game_end();
        void draw_end();

        void game_end1();
        void draw_end1();

        int process_event();

        void pause();
        void mute();



    private:
        ALLEGRO_DISPLAY* display = NULL;
        
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_EVENT event;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_FONT *font = NULL;
        ALLEGRO_FONT *bigFont = NULL;
        
        ALLEGRO_BITMAP* youWin = NULL;
        ALLEGRO_BITMAP* youLose = NULL;
        ALLEGRO_BITMAP* tie = NULL;
        
        ALLEGRO_BITMAP* again = NULL;
        ALLEGRO_BITMAP* list = NULL;
        ALLEGRO_BITMAP* gameover = NULL;
        
        ALLEGRO_SAMPLE *sample = NULL;
        ALLEGRO_SAMPLE_INSTANCE *backgroundMusic = NULL;
        ALLEGRO_SAMPLE_INSTANCE *excellentSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *gameoverSound = NULL;
        ALLEGRO_SAMPLE_INSTANCE *countdownSound = NULL;

        Board *board1 = NULL;
        Board *board2 = NULL;

        Button *startButton = NULL;
        Button *twoPlayerBtn = NULL;

        Button *homeButton = NULL;
        Button *retryButton = NULL;

        bool redraw = false;
        int mouse_x, mouse_y;
        int scene;
        int countDown;
        bool nowMute;
        
};


#endif // MAINWINDOW_H_INCLUDED
