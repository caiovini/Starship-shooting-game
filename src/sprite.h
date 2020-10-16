#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>

const std::string ship01 { "assets/Spaceships/PNG/Spaceships/01/Spaceship_01_BLUE.png" };
const std::string ship02 { "assets/Spaceships/PNG/Spaceships/02/Spaceship_02_BLUE.png" };
const std::string ship03 { "assets/Spaceships/PNG/Spaceships/03/Spaceship_03_BLUE.png" };
const std::string ship04 { "assets/Spaceships/PNG/Spaceships/04/Spaceship_04_BLUE.png" };
const std::string ship05 { "assets/Spaceships/PNG/Spaceships/05/Spaceship_05_BLUE.png" };
const std::string ship06 { "assets/Spaceships/PNG/Spaceships/06/Spaceship_06_BLUE.png" };

const std::string menu_background { "assets/menu_backgorund.jpg" };

class Meteor{
    public:
        SDL_Rect meteorRect;

    private:
        SDL_Texture* meteorTexture;
        SDL_Surface* meteorSurface;
        SDL_Renderer* renderer;


        bool is_rendered;
        float angle;

    public:
        Meteor(SDL_Renderer* renderer);
        bool checkCollisionMeteor(SDL_Rect objectTested);
        void render(SDL_Rect darea);
        void destroy();

};

class SpaceShip{

    private: 

        SDL_Surface* spriteSurface;
        SDL_Texture* spriteShip;
        SDL_Texture* spriteFlame[2];
        SDL_Renderer* renderer;

        SDL_Rect    flameRect;


        struct Lasers{
            SDL_Rect    shootRect;
            SDL_Texture* spriteLaser;

        };
    

        int initialPositionX = 100;
        int initialPositionY = 600;
        int spaceSize = 150;
        int flameSize = 200;

    public:
        SDL_Rect    shipRect;
        std::vector<Lasers> shoots;
    
    public:
        SpaceShip(SDL_Renderer* renderer , std::string shipSelected);
        void render();
        void moveRight(SDL_Rect darea);
        void moveLeft();
        void moveUp();
        void moveDown(SDL_Rect darea);
        void shoot();
};

class Enemy{

    private:
        int enemySize = 50;
        int initialEnemyPositionY = -10;
        int numberOfEnemies = 4;
        int finalEnemyPositionY[4];
        int finalEnemyPositionX[4] = { 100 , 300 , 500 , 700 };


        SDL_Surface* enemySurface;
        SDL_Surface* laserSurface;
        SDL_Renderer* renderer;
        SDL_Rect darea;

        struct enemy{
            
            SDL_Texture* textureEnemy;
            SDL_Rect enemyRect;
            SDL_Texture* laserEnemy;
            SDL_Rect laserRect;
            SDL_Rect enemyLifebar;
            bool isDestroyed;
        };

    public: 
        enemy enemies[4];

    public:
        Enemy(SDL_Renderer* renderer , SDL_Rect darea);
        void render();
        bool checkCollisionEnemy(SDL_Rect objectTested);


    private:
        void setup();

};


bool checkCollision( SDL_Rect a, SDL_Rect b );


