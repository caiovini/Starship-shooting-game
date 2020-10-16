
#include "screen.h"


Screen::Screen(int width , int height){

    Log *log = new Log();
    
    SDL_Init(SDL_INIT_EVERYTHING);         
    
    window = SDL_CreateWindow(
        "Space pixel",              
        SDL_WINDOWPOS_UNDEFINED,           
        SDL_WINDOWPOS_UNDEFINED,           
        width,                               
        height,                                
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        
        log->showLog(log->error , std::string("Could not create window: ").append(SDL_GetError()));
        return;
    }
            
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);

    if (!renderer) {

        log->showLog(log->error , "Render creation for surface fail");
        return;
    }  

    log->showLog(log->info , "Graphic init");
}

void Screen::handle_stars(std::vector<int> starsX , std::vector<int> &starsY , SDL_Rect darea){

    SDL_Rect rect;

    int blink = rand() % numberOfStars; // Blink random star

    for(int i = 0; i < starsX.size(); i++){

        if(starsY.at(i) == darea.h){

            starsY.at(i) = -10; // if Star hits the bottom, go back a little bit over the top of the screen
        }else{

            starsY.at(i) ++;
        }

        if(blink != i){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Draw small stars on screen

            rect.w = starSize;
            rect.h = starSize;
            rect.x = starsX.at(i);
            rect.y = starsY.at(i);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    
}

bool Screen::menu(){

    Log *log = new Log();

    SDL_Rect darea;

    SDL_RenderGetViewport(renderer, &darea);

    TTF_Init();

    TTF_Font *verdanaFont = TTF_OpenFont("fonts/Verdana.ttf", 128);
    SDL_Color textColor = { 255, 255, 255, 0 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(verdanaFont, "Choose your ship", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Surface *backgroundSurface = IMG_Load(menu_background.c_str());
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);


    SDL_Surface *shipsSurface[6];
    SDL_Texture *shipsTexture[6];

    shipsSurface[0] = IMG_Load(ship01.c_str());
    shipsTexture[0] = SDL_CreateTextureFromSurface(renderer, shipsSurface[0]);

    shipsSurface[1] = IMG_Load(ship02.c_str());
    shipsTexture[1] = SDL_CreateTextureFromSurface(renderer, shipsSurface[1]);
    
    shipsSurface[2] = IMG_Load(ship03.c_str());
    shipsTexture[2] = SDL_CreateTextureFromSurface(renderer, shipsSurface[2]);

    shipsSurface[3] = IMG_Load(ship04.c_str());
    shipsTexture[3] = SDL_CreateTextureFromSurface(renderer, shipsSurface[3]);

    shipsSurface[4] = IMG_Load(ship05.c_str());
    shipsTexture[4] = SDL_CreateTextureFromSurface(renderer, shipsSurface[4]);

    shipsSurface[5] = IMG_Load(ship06.c_str());
    shipsTexture[5] = SDL_CreateTextureFromSurface(renderer, shipsSurface[5]);

    unsigned int shipSize = 150;
    unsigned int shipPositionY = 150;
    unsigned int shipPositionX = 100;

    SDL_Rect shipRect[6];
    shipRect[0].w = shipSize;
    shipRect[0].h = shipSize;
    shipRect[0].x = shipPositionX;
    shipRect[0].y = shipPositionY;

    shipRect[1].w = shipSize;
    shipRect[1].h = shipSize;
    shipRect[1].x = shipPositionX * 3.3;
    shipRect[1].y = shipPositionY;

    shipRect[2].w = shipSize;
    shipRect[2].h = shipSize;
    shipRect[2].x = shipPositionX * 5.7;
    shipRect[2].y = shipPositionY;

    shipRect[3].w = shipSize;
    shipRect[3].h = shipSize;
    shipRect[3].x = shipPositionX;
    shipRect[3].y = shipPositionY * 3;

    shipRect[4].w = shipSize;
    shipRect[4].h = shipSize;
    shipRect[4].x = shipPositionX * 3.3;
    shipRect[4].y = shipPositionY * 3;

    shipRect[5].w = shipSize;
    shipRect[5].h = shipSize;
    shipRect[5].x = shipPositionX * 5.7;
    shipRect[5].y = shipPositionY * 3;


    SDL_Rect textRect;
    textRect.w = 300;
    textRect.h = 40;
    textRect.x = darea.w / 2 - textRect.w / 2;
    textRect.y = darea.h / 100;

    SDL_Rect selector;
    selector.w = 50;
    selector.h = 3;
    selector.x = shipRect[chooser].x + 50;
    selector.y = shipRect[chooser].y + shipRect[chooser].h;
    

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_FreeSurface(shipsSurface[0]);
    SDL_FreeSurface(shipsSurface[1]);
    SDL_FreeSurface(shipsSurface[2]);
    SDL_FreeSurface(shipsSurface[3]);
    SDL_FreeSurface(shipsSurface[4]);
    SDL_FreeSurface(shipsSurface[5]);

    TTF_Quit();
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    int opacity = 5;
    int chooserCounter = 0;
    bool enterPressed = false;

    bool is_running = true;
    while( is_running ){

        SDL_RenderClear(renderer);
            
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_RenderCopy(renderer, shipsTexture[0], nullptr, &shipRect[0]);
        SDL_RenderCopy(renderer, shipsTexture[1], nullptr, &shipRect[1]);
        SDL_RenderCopy(renderer, shipsTexture[2], nullptr, &shipRect[2]);
        SDL_RenderCopy(renderer, shipsTexture[3], nullptr, &shipRect[3]);
        SDL_RenderCopy(renderer, shipsTexture[4], nullptr, &shipRect[4]);
        SDL_RenderCopy(renderer, shipsTexture[5], nullptr, &shipRect[5]);

        if(chooserCounter < 100){
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &selector);
            chooserCounter ++;
            if(chooserCounter == 100){
                chooserCounter = 200;
            }
        }else{
            chooserCounter --;
            if(chooserCounter == 100){
                chooserCounter = 0;
            }
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity);
        if (enterPressed){
            opacity += 5;
            if(opacity > 255)
                is_running = false;
        }
        SDL_RenderFillRect(renderer, nullptr);

            
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
           
        while( SDL_PollEvent( &event ) ){

                
            if( event.type == SDL_KEYDOWN ){

                switch ( event.key.keysym.sym ){

                    case SDLK_LEFT:
                        if(chooser > 0 && !enterPressed){
                            chooser --;
                            selector.x = shipRect[chooser].x + 50;
                            if(chooser < 3)
                                selector.y = shipRect[chooser].y + shipRect[chooser].h;
                        }
                        break;

                    case SDLK_RIGHT:
                        if(chooser < 5 && !enterPressed){
                            chooser ++;
                            selector.x = shipRect[chooser].x + 50;
                            if(chooser > 2)
                                selector.y = shipRect[chooser].y + shipRect[chooser].h;
                        }
                        break;

                    case SDLK_ESCAPE:
                        log->showLog(log->info , "Quit on menu");
                        return 0;
                
                    case SDLK_RETURN:
                        log->showLog(log->info , "Ship chosen");
                        enterPressed = true;
                        break;
                }
                    
            } else if ( event.type == SDL_QUIT){
                log->showLog(log->info , "Quit on menu");  
                return 0;
 
            } else if( event.type == SDL_KEYUP ){
                continue;

            } 
            
        }
        
    }

    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(shipsTexture[0]);
    SDL_DestroyTexture(shipsTexture[1]);
    SDL_DestroyTexture(shipsTexture[2]);
    SDL_DestroyTexture(shipsTexture[3]);
    SDL_DestroyTexture(shipsTexture[4]);
    SDL_DestroyTexture(shipsTexture[5]);
    return 1;
}

SDL_Texture* generateScoreText(TTF_Font* font , SDL_Renderer* renderer , int points){

     std::string score = "Score: ";

    
    SDL_Surface *scoreTextSurface = TTF_RenderText_Solid(font, score.append(std::to_string(points)).c_str() ,  { 255, 255, 255, 200 });
    SDL_Texture *scoreTextTexture = SDL_CreateTextureFromSurface(renderer, scoreTextSurface);
    SDL_FreeSurface(scoreTextSurface);

    return scoreTextTexture;
}

void Screen::render(){

    SDL_Rect darea;
    SDL_Rect lifebarRect;
    SDL_Rect lifeTextRect;
    SDL_Rect scoreTextRect;
    SDL_Rect gameOverTextRect;

    SDL_RenderGetViewport(renderer, &darea);

    SpaceShip *spaceship;


    Meteor *meteor = new Meteor(renderer);
    Enemy *enemy = new Enemy(renderer , darea);
    Log *log = new Log();

    std::vector<std::string> files;

    switch (chooser){
    case 0:
        spaceship = new SpaceShip(renderer , ship01);
        break;
    
    case 1:
        spaceship = new SpaceShip(renderer , ship02);
        break;
    
    case 2:
        spaceship = new SpaceShip(renderer , ship03);
        break;

    case 3:
        spaceship = new SpaceShip(renderer , ship04);
        break;

    case 4:
        spaceship = new SpaceShip(renderer , ship05);
        break;

    case 5:
        spaceship = new SpaceShip(renderer , ship06);
        break;
    }

     

    std::vector<int> starsX (numberOfStars);
    std::vector<int> starsY (numberOfStars);

    for(int i = 0; i < starsX.size(); i++){

        starsX.at(i) = rand() % darea.w;
        starsY.at(i) = rand() % darea.h;

    }

    int points = 0;
    TTF_Init();

    TTF_Font *verdanaFont = TTF_OpenFont("fonts/FreeMonoOblique.ttf", 128);
    SDL_Color whiteTextColor = { 255, 255, 255, 200 };
    SDL_Surface *lifeTextSurface = TTF_RenderText_Solid(verdanaFont, "Life", whiteTextColor);
    SDL_Texture *lifeTextTexture = SDL_CreateTextureFromSurface(renderer, lifeTextSurface);
    SDL_Surface *gameOverTextSurface = TTF_RenderText_Solid(verdanaFont, "GAME OVER", whiteTextColor);
    SDL_Texture *gameOverTextTexture = SDL_CreateTextureFromSurface(renderer, gameOverTextSurface);
    
    SDL_FreeSurface(lifeTextSurface);
    SDL_FreeSurface(gameOverTextSurface);    

    scoreTextRect.x = darea.w / 2;
    scoreTextRect.y = 10;
    scoreTextRect.w = 100;
    scoreTextRect.h = 25;

    lifebarRect.x = 10;
    lifebarRect.y = 10;
    lifebarRect.w = 200;
    lifebarRect.h = 10;

    lifeTextRect.x = 10;
    lifeTextRect.y = 20;
    lifeTextRect.w = 50;
    lifeTextRect.h = 25;

    gameOverTextRect.x = darea.w / 2.7;
    gameOverTextRect.y = darea.h / 2.5;
    gameOverTextRect.w = 200;
    gameOverTextRect.h = 100;

    
    SDL_Texture* scoreTextTexture = generateScoreText(verdanaFont , renderer , points);
    bool isKeyDown = false , is_running = true , gameOver = false;;
    unsigned int opacity = 255;
    unsigned int blinkSpaceship = 0;

    unsigned int moveCycle = 0 , shootingCycle = 0 , keyPressed = 0;
    while( is_running ){
        
           
        while( SDL_PollEvent( &event ) ){
                
            if( event.type == SDL_KEYDOWN ){
                isKeyDown = true;

                switch ( event.key.keysym.sym ){

                    case SDLK_LEFT:
                        keyPressed = SDLK_LEFT;
                        moveCycle = 15;
                        break;

                    case SDLK_RIGHT:
                        keyPressed = SDLK_RIGHT;
                        moveCycle = 15;
                        break;

                    case SDLK_UP:
                        keyPressed = SDLK_UP;
                        moveCycle = 15;
                        break;

                    case SDLK_DOWN:
                        keyPressed = SDLK_DOWN;
                        moveCycle = 15;
                        break;

                    case SDLK_ESCAPE:
                        return;
                
                    case SDLK_x:
                        if(!gameOver){
                            if(!shootingCycle){
                                shootingCycle = 30;
                                spaceship->shoot();
                            }
                        }
                        break;
                }
                    
            } else if ( event.type == SDL_QUIT){
                return;
 
            } else if( event.type == SDL_KEYUP ){
                isKeyDown = false;
                
            } 
            
        }

        if(moveCycle && !gameOver){

            switch (keyPressed){

                case (SDLK_RIGHT):
                    spaceship->moveRight(darea);
                    break;
            
                case (SDLK_DOWN):
                    spaceship->moveDown(darea);
                    break;

                case (SDLK_LEFT):
                    spaceship->moveLeft();
                    break;

                case (SDLK_UP):
                    spaceship->moveUp();
                    break;
            }

            if(!isKeyDown)
                moveCycle --;

        }

        if(shootingCycle)
            shootingCycle --;


        SDL_RenderClear(renderer);
        
        this->handle_stars(starsX , starsY , darea);
        meteor->render(darea);
        if(!blinkSpaceship){
            spaceship->render();
            if(meteor->checkCollisionMeteor(spaceship->shipRect) || enemy->checkCollisionEnemy(spaceship->shipRect)){
                lifebarRect.w -= 10;
                blinkSpaceship = 100;
                if(!lifebarRect.w){
                    gameOver = true;
                    opacity = 200;
                }
            }
        }else{
            blinkSpaceship --;
            if(0 == blinkSpaceship % 2)
                spaceship->render();
        }
        
        enemy->render();

        // Check collision between shoots coming from the player and the enemy  
        for(int i = 0; i < spaceship->shoots.size(); i++){
            
            if(enemy->checkCollisionEnemy(spaceship->shoots[i].shootRect)){
                spaceship->shoots.erase( spaceship->shoots.begin() + i);
                points ++;
                scoreTextTexture = generateScoreText(verdanaFont , renderer , points);
                break;
            }

        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150); // GREEN
        SDL_RenderFillRect(renderer, &lifebarRect);
        SDL_RenderCopy(renderer, lifeTextTexture, nullptr, &lifeTextRect);
        SDL_RenderCopy(renderer, scoreTextTexture, nullptr, &scoreTextRect);
        
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity); // BLACK Fadein screen
        SDL_RenderFillRect(renderer, nullptr);

        if(gameOver)
            SDL_RenderCopy(renderer, gameOverTextTexture, nullptr, &gameOverTextRect);
            
        SDL_UpdateWindowSurface(window);

        if(opacity && !gameOver){
            opacity --;
        }

        SDL_Delay(1);
    }

    TTF_Quit();
}

