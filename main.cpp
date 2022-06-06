#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game_map.h"
#include <string>

#define MAP_SIZE 4
#define WINNING_LENGTH 4
#define TILE_SIZE 30

using namespace std;

// Window and screen
SDL_Window *game_window = nullptr;
SDL_Surface *game_screen = nullptr;

// Tile images
SDL_Surface *blank = nullptr;
SDL_Surface *O = nullptr;
SDL_Surface *X = nullptr;
SDL_Surface *win_tile = nullptr;

// Font pointer
TTF_Font *font = nullptr;

// Text surfaces
SDL_Surface *red_turn = nullptr;
SDL_Surface *blue_turn = nullptr;
SDL_Surface *red_won = nullptr;
SDL_Surface *blue_won = nullptr;
SDL_Surface *instructions = nullptr;
SDL_Surface *instructions_2 = nullptr;

// window parameters
int window_width;
int window_height;

int **result = nullptr;
int player_id; // 1 is red and -1 is blue
bool victory;



// Initializing SDL, game window and display screen
int game_init(){
    if (SDL_Init(SDL_INIT_VIDEO)!= 0){
        cout << "couldn't initialize sdl" << endl;
        return 1;
    }

    game_window = SDL_CreateWindow("TicTacToe on Torus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   window_width, window_height, SDL_WINDOW_SHOWN);
    if (game_window == nullptr){
        cout << "couldn't initialize game window" << endl;
        return 2;
    }

    int flags = IMG_INIT_PNG;
    if ((IMG_Init(flags) & flags) != flags){
        cout << "couldn't initialize sdl image" << endl;
        return 3;
    }

    game_screen =  SDL_GetWindowSurface(game_window);
    if(game_screen == nullptr){
        cout << "couldn't initialize game screen" << endl;
        return 4;
    }
    SDL_FillRect(game_screen, nullptr, SDL_MapRGB(game_screen->format, 255, 255, 255));

    if(TTF_Init() == -1){
        cout << "couldn't initialize TTF" << endl;
        return 5;
    }

    return 0;
}



// Loading tile images, fonts and creating surfaces
int load_data() {
    blank = IMG_Load("./data/w.png");
    if (blank == nullptr) {
        cout << "couldn't load blank image\n" << IMG_GetError() << endl;
        return 6;
    }

    X = IMG_Load("./data/x.png");
    if (X == nullptr) {
        cout << "couldn't load X image" << endl;
        return 7;
    }


    O = IMG_Load("./data/o.png");
    if (O == nullptr) {
        cout << "couldn't load O image" << endl;
        return 8;
    }

    win_tile = IMG_Load("./data/g.png");
    if (O == nullptr) {
        cout << "couldn't load winning tile image" << endl;
        return 9;
    }

    font = TTF_OpenFont("./data/Pixel.ttf", 20);
    if(font == nullptr){
        cout << "couldn't load font" << endl;
        return 10;
    }

    red_turn = TTF_RenderText_Solid(font, "player's  turn:  RED", {255,0,0});
    blue_turn = TTF_RenderText_Solid(font, "player's  turn:  BLUE", {0,0,255});
    red_won = TTF_RenderText_Solid(font, "winner:  RED", {255,0,0});
    blue_won = TTF_RenderText_Solid(font, "winner:  BLUE", {0,0,255});
    instructions = TTF_RenderText_Solid(font, "click  to  place  a  tile", {0,0,0});
    instructions_2 =  TTF_RenderText_Solid(font, "press  space  to  restart", {0,0,0});

    return 0;
}



// Function for clearing winner's green tiles
void clear_result(){
    if(result != nullptr){
        for (int i = 0; i < WINNING_LENGTH; i++)delete [] result[i];
        delete [] result;
        result = nullptr;
    }
}



// Function closing the game
void close_game(){
    clear_result();

    SDL_FreeSurface(blank);
    SDL_FreeSurface(X);
    SDL_FreeSurface(O);
    SDL_FreeSurface(game_screen);
    blank = X = O = game_screen = nullptr;
    SDL_DestroyWindow(game_window);
    game_window = nullptr;

    SDL_FreeSurface(red_turn);
    SDL_FreeSurface(blue_turn);
    SDL_FreeSurface(red_won);
    SDL_FreeSurface(blue_won);
    SDL_FreeSurface(instructions);
    SDL_FreeSurface(instructions_2);

    TTF_CloseFont(font);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}



// Displaying the image on the screen
void draw_game(game_map &map){
    SDL_FillRect(game_screen, nullptr, SDL_MapRGB(game_screen->format, 255, 255, 255));

    SDL_Rect target_rect;
    target_rect.w = TILE_SIZE;
    target_rect.h = TILE_SIZE;
    for (int i = 0; i < MAP_SIZE; i++){
        for (int j = 0; j < MAP_SIZE; j++){
            for(int k = 0; k < MAP_SIZE; k++){
                target_rect.x = k * TILE_SIZE;
                target_rect.y = j * TILE_SIZE + i*TILE_SIZE*(MAP_SIZE+1);
                if (map[i][j][k] == 0)SDL_BlitSurface(blank, nullptr, game_screen, &target_rect);
                else if(map[i][j][k] == 1)SDL_BlitSurface(X, nullptr, game_screen, &target_rect);
                else SDL_BlitSurface(O, nullptr, game_screen, &target_rect);
            }
        }
    }

    if(result != nullptr){
        for(int i = 0; i < WINNING_LENGTH; i++){
            target_rect.x = result[i][2] * TILE_SIZE;
            target_rect.y = result[i][1] * TILE_SIZE + result[i][0]*TILE_SIZE*(MAP_SIZE+1);
            target_rect.w = TILE_SIZE;
            target_rect.h = TILE_SIZE;
            SDL_BlitSurface(win_tile, nullptr, game_screen, &target_rect);
        }
    }

    if(result != nullptr and !victory) victory = true;

    target_rect.x = (MAP_SIZE+1)*TILE_SIZE;
    target_rect.y = 4*TILE_SIZE + 5;
    target_rect.w = 5*TILE_SIZE;
    target_rect.h = 2*TILE_SIZE;
    if(victory){
        if(player_id == 1)SDL_BlitSurface(blue_won, nullptr, game_screen, &target_rect);
        else SDL_BlitSurface(red_won, nullptr, game_screen, &target_rect);
    }else{
        if(player_id == 1) SDL_BlitSurface(red_turn, nullptr, game_screen, &target_rect);
        else SDL_BlitSurface(blue_turn, nullptr, game_screen, &target_rect);
    }

    target_rect.y = TILE_SIZE + 5;
    SDL_BlitSurface(instructions, nullptr, game_screen, &target_rect);
    target_rect.y = 2*TILE_SIZE + 5;
    SDL_BlitSurface(instructions_2, nullptr, game_screen, &target_rect);

    SDL_UpdateWindowSurface(game_window);

}



// Reseting and restarting the game. Activated on spacebar or after victory on left mouse click
void reset(game_map &map){
    clear_result();
    map.clear();
    player_id = 1;
    victory = false;
}



// Event handling function while playing
void mouse_handler( SDL_Event* e , game_map &map){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        int i = y/((MAP_SIZE+1)*TILE_SIZE);
        int j = (y%((MAP_SIZE+1)*TILE_SIZE))/TILE_SIZE;
        int k = x/TILE_SIZE;
        if( e->type ==  SDL_MOUSEBUTTONDOWN and e->button.button == SDL_BUTTON_LEFT and i < MAP_SIZE and j < MAP_SIZE and k < MAP_SIZE ){
            map.place(i, j, k, player_id);
            result = map.check();
            player_id *= -1;
        }

    }
}



// Event handling function after one player's victory
void winning_handler(SDL_Event* e , game_map &map){
    if( e->type ==  SDL_MOUSEBUTTONDOWN and e->button.button == SDL_BUTTON_LEFT){
        reset(map);
    }
}



// . . . . . no idea . . . what could this possibly be??
int main(int argc, char ** argv) {
    window_width = window_height = (MAP_SIZE + 1) * MAP_SIZE * TILE_SIZE;

    int err_value = game_init();
    if(err_value != 0){
        cout << "couldn't initialize the game" << endl;
        return err_value;
    }

    err_value = load_data();
    if( err_value != 0){
        cout << "couldn't load images" << endl;
        return err_value;
    }

    player_id = 1;
    game_map map = game_map(MAP_SIZE, WINNING_LENGTH, player_id);

    SDL_Event event_handler;
    bool playing = true;
    victory = false;

    while(playing){
        SDL_WaitEvent(&event_handler);
        if(event_handler.type == SDL_KEYDOWN and event_handler.key.keysym.sym == SDLK_SPACE) reset(map);
        if (event_handler.type == SDL_QUIT) playing = false;
        if(!victory) mouse_handler(&event_handler, map);
        else winning_handler(&event_handler, map);
        draw_game(map);
    }

    close_game();
    return 0;
}
