#include "raylib.h"
//#include <iostream>
#include <vector>
#include <memory>
#include <random>


using namespace std;

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT
};


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MAX_ENEMIES = 10;

Direction random_dir() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(0,8);
    return static_cast<Direction>(dist(gen));
}

int random_int(int range) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dist(0,range);
    return dist(gen);
}




class Entity {
    protected:
        int posX, posY;
    public:
        Entity(){posX = 0; posY = 0;}
        Entity(int x,int y){posX = x; posY = y;}
        virtual ~Entity() {}

        int get_posX() const {
            return posX;
        }

        int get_posY() const {
            return posY;
        }

        virtual void draw() const = 0;

        virtual void update () = 0;

        void set_position(int x, int y) { posX = x; posY = y; }

        void move(Direction dir, int distance){
            int _posX = posX;
            int _posY = posY;
            switch (dir) {
                case UP:   _posY-=distance;break;
                case DOWN: _posY+=distance;break;
                case RIGHT:_posX+=distance;break;
                case LEFT: _posX-=distance;break;
                case UP_RIGHT:   _posX+=distance;_posY-=distance;break;
                case UP_LEFT:    _posX-=distance;_posY-=distance;break;
                case DOWN_LEFT:  _posX-=distance;_posY+=distance;break;
                case DOWN_RIGHT: _posX+=distance;_posY+=distance;break;
                default: break;
            }
            bounds_check_x(_posX);
            bounds_check_y(_posY);
        }
        virtual void bounds_check_x(int &x){
            if (x>SCREEN_WIDTH){
                posX = SCREEN_WIDTH;
            }
            else if (x<0){
                posX = 0;
            }
            else {
                posX = x;
            }
            return;
        }
        virtual void bounds_check_y(int &y){
            if (y>SCREEN_HEIGHT){
                posY = SCREEN_HEIGHT;
            }
            else if (y<0){
                posY = 0;
            }
            else {
                posY = y;
            }
            return;
        }
};

class MyRectangle : public Entity {
        int width, height;
        Color color;
    public:
        MyRectangle(int w, int h, Color col){width=w;height=h;color = col;}
        MyRectangle(int x,int y,int w, int h, Color col) : Entity(x,y) {width=w;height=h;color = col;}
        void update() override {}

        void draw() const {
            DrawRectangle(posX,posY,width,height,color);
        }

        void bounds_check_x(int &x){
            if (x>SCREEN_WIDTH-width){
                posX = SCREEN_WIDTH-width;
            }
            else if (x<0){
                posX = 0;
            }
            else {
                posX = x;
            }
            return;
        }
        void bounds_check_y(int &y){
            if (y>SCREEN_HEIGHT-height){
                posY = SCREEN_HEIGHT-height;
            }
            else if (y<0){
                posY = 0;
            }
            else {
                posY = y;
            }
            return;
        }
};

class Player : public MyRectangle {
    int move_d;
    public:
        Player(int w, int h, Color col, int d) : MyRectangle(w,h,col) {move_d = d;}
        Player(int x,int y,int w, int h, Color col, int d) : MyRectangle(x,y,w,h,col) {move_d = d;}
        void update() override {move(getInput(),move_d*movSpeed());}

        Direction getInput(){
            bool up=false,down=false,left=false,right=false;
            if (IsKeyDown(KEY_DOWN)){
                down = true;
            }
            if (IsKeyDown(KEY_UP)){
                up = true;
            }
            if (IsKeyDown(KEY_RIGHT)){
                right = true;
            }
            if (IsKeyDown(KEY_LEFT)){
                left = true;
            }

            Direction dirv = NONE, dirh = NONE;


            // vertical direction
            if ((up && down) || (!up && !down)){
                dirv = NONE;
            }
            else if (up){
                dirv = UP;
            }
            else if (down){
                dirv = DOWN;
            }
            

            //horizontal direction
            if ((left && right)||(!left && !right)){
                dirh = NONE;
            }
            else if (left){
                dirh = LEFT;
            }
            else if (right){
                dirh = RIGHT;
            }


            // direction decider
            if (dirv == NONE){
            
                return dirh;
            }
            else if (dirh == RIGHT){
                if (dirv == UP){
                    return UP_RIGHT;
                }
                else {
                    return DOWN_RIGHT;
                }
            }
            else if (dirh == LEFT){
                if (dirv == UP){
                    return UP_LEFT;
                }
                else {
                    return DOWN_LEFT;
                }
            }
            else if (dirv == UP){
                return UP;
            }
            else if (dirv == DOWN){
                return DOWN;
            }
            
            if (dirh = NONE){
                return dirv;
            }


            

            return NONE;
        }
        int movSpeed(){
            if (IsKeyDown(KEY_LEFT_SHIFT)){
                    return 2;
                }
                else {
                    return 1;
                }
        }
        
        void modify_dist (int d){
            move_d = d;
        }
};

class Enemy : public MyRectangle {
    int move_d;
    public:
        Enemy(int w, int h, Color col, int d) : MyRectangle(w,h,col) {move_d = d;}
        Enemy(int x,int y,int w, int h, Color col, int d) : MyRectangle(x,y,w,h,col) {move_d = d;}

        void update() override {move(random_dir(),move_d);}
};

void backgroundDraw(Color color, const char *texto, int posX, int posY, int fontsize, Color textCol){
    ClearBackground(color); 
    DrawText(texto, posX, posY, fontsize, textCol);
}




int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ventana ejemplo");
    SetTargetFPS(60);

    Color bkg_color = { 0, 255, 244, 255 };

    // Calculo para centrar player:
    //player size
    const int player_width = SCREEN_WIDTH /10;
    const int player_height = SCREEN_HEIGHT /10;

    int player_posX = SCREEN_WIDTH/2-player_width/2;
    int player_posY = SCREEN_HEIGHT/2-player_height/2;

    int mov_amount = 3;
    Direction move = NONE;

    Color player_col = GREEN;

    vector<unique_ptr<Entity>> entities; //vector de entidades

    entities.push_back(make_unique<Player>(player_posX, player_posY, player_width, player_height, player_col, mov_amount));

    int enemy_posX = random_int(SCREEN_WIDTH);
    int enemy_posY = random_int(SCREEN_HEIGHT);
    int enemy_width = player_width/2;
    int enemy_height = player_height/2;
    Color enemy_col = RED;
    entities.push_back(make_unique<Enemy>(enemy_posX, enemy_posY, enemy_width, enemy_height, enemy_col, mov_amount));

    float deltaTime;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        for (auto& e : entities){ // como recorrer vector
            e->update();
            // for (auto it = entities.begin(); it != entities.end(); ) {
            //     if (/* condición para borrar */) {
            //         it = entities.erase(it); // borra y devuelve el siguiente
            //     } else {
            //         ++it;
            //     }
            // }
        }
        BeginDrawing();
            backgroundDraw(bkg_color,"Contador = ", 2, 0, 20, BLACK);
            for (auto& e : entities){ // como recorrer vector
                e->draw();
            }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
