#include "raylib.h"
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>


using namespace std::chrono;
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
        float posX, posY;
    public:
        Entity(){posX = 0; posY = 0;}
        Entity(float x,float y){posX = x; posY = y;}
        virtual ~Entity() {}

        float get_posX() const {
            return posX;
        }

        float get_posY() const {
            return posY;
        }

        virtual void draw() const = 0;

        virtual void update (float delta) = 0;

        void set_position(float x, float y) { posX = x; posY = y; }

        void move(Direction dir, float distance){
            float _posX = posX;
            float _posY = posY;
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
        virtual void bounds_check_x(float &x){
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
        virtual void bounds_check_y(float &y){
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
        MyRectangle(float x,float y,int w, int h, Color col) : Entity(x,y) {width=w;height=h;color = col;}
        void update(float delta) override {}

        void draw() const {
            DrawRectangle(int(posX),int(posY),width,height,color);
        }

        void bounds_check_x(float &x){
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
        void bounds_check_y(float &y){
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
    const float base_speed; 
    float speed;
    public:
        Player(int w, int h, Color col, float s) : MyRectangle(w,h,col), base_speed(s) {}
        Player(float x,float y,int w, int h, Color col, float s) : MyRectangle(x,y,w,h,col), base_speed(s) {}
        void update(float delta) override {movSpeed();move(getInput(),speed*delta);}

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
        void movSpeed(){
            if (IsKeyDown(KEY_LEFT_SHIFT)){
                    speed = base_speed*2;
                }
                else {
                    speed = base_speed;
                }
            return;
        }
        
};

class Enemy : public MyRectangle {
    float speed;
    int born_date;
    Direction move_dir;
    public:
        Enemy(int w, int h, Color col, float s) : MyRectangle(w,h,col) {
            speed=s;
            auto now = system_clock::now();
            born_date = duration_cast<milliseconds>(now.time_since_epoch()).count();
            move_dir = NONE;
        }
        Enemy(float x,float y,int w, int h, Color col, float s) : MyRectangle(x,y,w,h,col) {
            speed=s;
            auto now = system_clock::now();
            born_date = duration_cast<milliseconds>(now.time_since_epoch()).count();
            move_dir = NONE;
        }

        void update(float delta) override {
            move(move_dir,speed*delta);
            auto now = system_clock::now();
            int now_millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
            if (now_millis - born_date >= 200){
                move_dir = random_dir();
                born_date = now_millis;
            }
        }
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

    float player_posX = SCREEN_WIDTH/2-player_width/2;
    float player_posY = SCREEN_HEIGHT/2-player_height/2;

    float speed = 500;
    Direction move = NONE;

    Color player_col = GREEN;

    vector<unique_ptr<Entity>> entities; //vector de entidades

    entities.push_back(make_unique<Player>(player_posX, player_posY, player_width, player_height, player_col, speed));

    float enemy_posX = random_int(SCREEN_WIDTH);
    float enemy_posY = random_int(SCREEN_HEIGHT);
    int enemy_width = player_width/2;
    int enemy_height = player_height/2;
    Color enemy_col = RED;
    entities.push_back(make_unique<Enemy>(enemy_posX, enemy_posY, enemy_width, enemy_height, enemy_col, speed));

    float deltaTime;

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        //cout << deltaTime << '\n';
        for (auto& e : entities){ // como recorrer vector
            e->update(deltaTime);
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
