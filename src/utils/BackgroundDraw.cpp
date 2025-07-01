#include "BackgroundDraw.hpp"

void backgroundDraw(Color color, const char *texto, int posX, int posY, int fontsize, Color textCol) {
    ClearBackground(color); 
    DrawText(texto, posX, posY, fontsize, textCol);
}
