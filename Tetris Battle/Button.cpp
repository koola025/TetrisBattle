#include "Button.h"

bool Button::mouseIn(int click_x, int click_y){
    if (click_x > Pos_x && click_x < Pos_x + Width
    && click_y > Pos_y && click_y < Pos_y + Height) {
        return true;
    }
    else return false;
}

void Button::drawNormal(char buffer[50]){
    al_draw_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 5.0, 5.0, al_map_rgb(255, 255, 255) , 10.0);
    al_draw_filled_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 5.0, 5.0, al_map_rgb(229, 115, 115));
    al_draw_text(font, al_map_rgb(255, 255, 255), (Pos_x + Pos_x + Width)/2, (Pos_y + Pos_y + Height)/2 - 20, 1, buffer);
}


void Button::drawHover(char buffer[50]){
    al_draw_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 5.0, 5.0, al_map_rgb(255, 255, 255) , 10.0);
    al_draw_filled_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 1.0, 1.0, al_map_rgb(115, 58, 58));
    al_draw_text(font, al_map_rgb(255, 255, 255), (Pos_x + Pos_x + Width)/2, (Pos_y + Pos_y + Height)/2 - 20, 1, buffer);
}

void Button::drawClicked(char buffer[50]){
    al_draw_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 5.0, 5.0, al_map_rgb(229, 115, 115) , 10.0);
    al_draw_filled_rounded_rectangle(Pos_x, Pos_y, Pos_x + Width, Pos_y + Height, 1.0, 1.0, al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(229, 115, 115), (Pos_x + Pos_x + Width)/2, (Pos_y + Pos_y + Height)/2 - 20, 1, buffer);
}