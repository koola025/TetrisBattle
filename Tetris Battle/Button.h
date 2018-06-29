#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "global.h"
//#include "GameWindow.h"

#define window_width 1920
#define window_height 1280

class Button
{
    public:
        // constructor
        Button(int x, int y, int w, int h): Pos_x(x), Pos_y(y), Width(w), Height(h) {
            font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0);
        }
        
        void drawNormal(char buffer[50]);
        void drawHover(char buffer[50]);
        void drawClicked(char buffer[50]);
        bool mouseIn(int click_x, int click_y);
        bool clicking = false;
        


    private:
        int Pos_x;
        int Pos_y;
        int Width;
        int Height;
        
        ALLEGRO_FONT *font = NULL;
};



#endif // BUTTON_H_INCLUDED
