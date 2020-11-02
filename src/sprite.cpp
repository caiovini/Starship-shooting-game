#include "sprite.h"


const std::string flame01 { "assets/Spaceships/PNG/Flame_01.png" };
const std::string flame02 { "assets/Spaceships/PNG/Flame_02.png" };
const std::string laser   { "assets/Spaceships/PNG/laser/laserBlue.png" };

const std::string meteor { "assets/Spaceships/PNG/enemy/meteorBrown.png" };

const std::string enemyImages[4] = { "assets/Spaceships/PNG/enemies/enemyBlack.png" , "assets/Spaceships/PNG/enemies/enemyBlue.png" , "assets/Spaceships/PNG/enemies/enemyGreen.png" , "assets/Spaceships/PNG/enemies/enemyRed.png"};



Meteor::Meteor(SDL_Renderer* renderer){

    this->renderer = renderer;
    meteorSurface = IMG_Load(meteor.c_str());;
    meteorTexture = SDL_CreateTextureFromSurface(renderer, meteorSurface);
    is_rendered = false;
    angle = 0.0f;

    SDL_FreeSurface(meteorSurface);
}


void Meteor::render(SDL_Rect darea){

    if(is_rendered){

        if(angle == 360) // Rotate meteor
            angle = 0.0f;
        
        angle += 1.0f; 

        SDL_RenderCopyEx(renderer, meteorTexture, nullptr , &meteorRect , angle , nullptr , SDL_FLIP_NONE);

        meteorRect.x ++;
        meteorRect.y ++;
        if(meteorRect.x > darea.w || meteorRect.y > darea.h)
             is_rendered = false;
    }else{

        if(rand() % 10000 > 9990){

            int positionX =  rand() & darea.w / 2;
            int positionY =  rand() & darea.h / 2;

            if(positionX > positionY){

                positionY = -50;
            }else{

                positionX = -50;
            }
        
            meteorRect.x = positionX;
            meteorRect.y = positionY;
            meteorRect.w = 50;
            meteorRect.h = 50;

            is_rendered = true;
        }
    }
}

bool Meteor::checkCollisionMeteor(SDL_Rect objectTested){

    SDL_Rect tempRect;

    // Decrease the size of the meteor so the total area for comparison would be more accurate
    tempRect.w = meteorRect.w / 10;
    tempRect.h = meteorRect.h / 10;
    tempRect.x = meteorRect.x;
    tempRect.y = meteorRect.y;

    if(checkCollision(objectTested , tempRect)){

        this->destroy(); // Case collision, destroy it
        return true;
    }

    return false;

}


void Meteor::destroy(){

    meteorRect.x = -10;
    meteorRect.y = -10;

    is_rendered = false;
}

SpaceShip::SpaceShip(SDL_Renderer* renderer , std::string shipSelected){

     this->renderer = renderer;

     spriteSurface = IMG_Load(shipSelected.c_str());
     spriteShip = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    
     // Flames
     spriteSurface = IMG_Load(flame01.c_str());
     spriteFlame[0] = SDL_CreateTextureFromSurface(renderer, spriteSurface);
     spriteSurface = IMG_Load(flame02.c_str());
     spriteFlame[1] = SDL_CreateTextureFromSurface(renderer, spriteSurface);

     // Free up surface
     SDL_FreeSurface(spriteSurface);

     shipRect.x = initialPositionX;
     shipRect.y = initialPositionY;
     shipRect.w = spaceSize;
     shipRect.h = spaceSize;


     // Flame position
     flameRect.x = shipRect.x - 25;
     flameRect.y = shipRect.y + 30;
     flameRect.w = flameSize;
     flameRect.h = flameSize;

}

void SpaceShip::shoot(){

    SDL_Rect    shootRect;

    Lasers ls = Lasers();

    ls.shootRect.x = shipRect.x + shipRect.w / 2.2;
    ls.shootRect.y = shipRect.y;
    ls.shootRect.w = 15;
    ls.shootRect.h = 30;

    SDL_Surface* laserSurface;

    laserSurface = IMG_Load(laser.c_str());
    ls.spriteLaser = SDL_CreateTextureFromSurface(renderer, laserSurface);

    SDL_FreeSurface(laserSurface);
    shoots.push_back(ls); // Add new laser to the list

}


void SpaceShip::render(){

    SDL_RenderCopy(renderer, spriteShip, nullptr , &shipRect);
    SDL_RenderCopy(renderer, spriteFlame[rand() % 2], nullptr , &flameRect); // Random flame png

    // Laser
    if(shoots.size()){

        for(int i = 0; i < shoots.size(); i++){

            SDL_RenderCopy(renderer, shoots[i].spriteLaser , nullptr , &shoots[i].shootRect);
            shoots[i].shootRect.y -= 2;
            if(shoots[i].shootRect.y < -10)
                shoots.erase( shoots.begin() + i); // Lase beam is out of screen boundaries

        }
    }
}

void SpaceShip::moveRight(SDL_Rect darea){

    if(shipRect.x < darea.w - shipRect.w/1.2){

        shipRect.x  +=2;
        flameRect.x +=2;
    }
}

void SpaceShip::moveLeft(){

    if(shipRect.x > -30){

        shipRect.x  -=2;
        flameRect.x -=2;

    }
}

void SpaceShip::moveDown(SDL_Rect darea){

    if(shipRect.y < darea.h - shipRect.h){

        shipRect.y  +=2;
        flameRect.y +=2;

    }
}

void SpaceShip::moveUp(){

    if(shipRect.y > -30){

        shipRect.y  -=2;
        flameRect.y -=2;
    }
}

Enemy::Enemy(SDL_Renderer* renderer , SDL_Rect darea){

    this->renderer = renderer;
    this->darea = darea;

    this->setup();
}

void Enemy::setup(){

    laserSurface = IMG_Load(laser.c_str());

    // Render each enemy
    for (int i = 0; i < numberOfEnemies; i ++){

        enemySurface = IMG_Load(enemyImages[i].c_str());
        enemies[i].textureEnemy = SDL_CreateTextureFromSurface(renderer, enemySurface);
        enemies[i].laserEnemy = SDL_CreateTextureFromSurface(renderer, laserSurface);

        enemies[i].enemyRect.w = enemySize;
        enemies[i].enemyRect.h = enemySize;
        enemies[i].enemyRect.x = finalEnemyPositionX[i];
        enemies[i].enemyRect.y = initialEnemyPositionY;

        finalEnemyPositionY[i] = rand() % 300 + 50;

        enemies[i].laserRect.w = 15;
        enemies[i].laserRect.h = 30;
        enemies[i].laserRect.x = finalEnemyPositionX[i] + 20;
        enemies[i].laserRect.y = finalEnemyPositionY[i] + 50;

        enemies[i].enemyLifebar.w = 50;
        enemies[i].enemyLifebar.h = 5;
        enemies[i].enemyLifebar.x = enemies[i].enemyRect.x;
        enemies[i].enemyLifebar.y = finalEnemyPositionY[i] - 20;

    }

    SDL_FreeSurface(enemySurface);
    SDL_FreeSurface(laserSurface);

}

void Enemy::render(){

    int numberOfDeads = 0;

    for(int i = 0; i < numberOfEnemies; i++){
        if(enemies[i].enemyRect.y < finalEnemyPositionY[i])
            enemies[i].enemyRect.y ++;

        if(enemies[i].enemyLifebar.w > 0){
            SDL_RenderCopy(renderer, enemies[i].textureEnemy , nullptr , &enemies[i].enemyRect); // Render if enemy has life

        }else{

            enemies[i].enemyRect.x = -20;
            enemies[i].enemyRect.y = -20;
            numberOfDeads ++;
            if(numberOfDeads == numberOfEnemies){ // If all enemies are dead, setup them all over again
                this->setup();
                break;    
            }
            continue;

        }

        if(enemies[i].enemyRect.y == finalEnemyPositionY[i]){


            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150); // GREEN
            SDL_RenderFillRect(renderer, &enemies[i].enemyLifebar);

            SDL_RenderCopyEx(renderer, enemies[i].laserEnemy , nullptr , &enemies[i].laserRect , 180.0f , nullptr , SDL_FLIP_NONE);

            enemies[i].laserRect.y ++;
            if(enemies[i].laserRect.y > darea.h + 200){

                enemies[i].laserRect.x = enemies[i].enemyRect.x + 20;
                enemies[i].laserRect.y = enemies[i].enemyRect.y + 50;

            }
        }
    }
}

bool Enemy::checkCollisionEnemy(SDL_Rect objectTested){

    SDL_Rect temp;

    for (int i = 0; i < numberOfEnemies; i++){

        temp = enemies[i].laserRect;
        temp.y -= 50;


        if (checkCollision(objectTested , enemies[i].enemyRect)){
            enemies[i].enemyLifebar.w -= 10;
            return true;
        }

        // Laser hits ship
        if (checkCollision(objectTested , temp)){
            enemies[i].laserRect.y = darea.h + 100;
            return true;
        }
        
    }

    return false;
}


bool checkCollision( SDL_Rect a, SDL_Rect b ){


    //The sides of the rects
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

     //If any of the sides from A are outside of B
    if( bottomA <= topB )
        return false;
    

    if( topA >= bottomB )
        return false;
    

    if( rightA <= leftB )
        return false;
    

    if( leftA >= rightB )
        return false;
    
    //If none of the sides from A are outside B
    return true;
}
