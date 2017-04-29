#include <cstdio>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define SCREEN_FPS  10


using namespace std;


SDL_Surface * screen = NULL;
SDL_Event event;

char * caption = (char *)"Wahaha!EZ metro~";

SDL_Surface * loadimage(char * file) {
	SDL_Surface * loadedImage = NULL;
	SDL_Surface * optimized_image = NULL;

	loadedImage = IMG_Load(file);

	if(loadedImage != NULL) {
		optimized_image = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimized_image;
}

void apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}

bool init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

	// initial and set screen

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;

    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	if(screen == NULL) return false;

	SDL_WM_SetCaption(caption, NULL);

	return true;
}

void clean_up() {
	SDL_Quit();
}

int play_menu() {

	int type = 0; // 0 = menu, 1 = play, 2 = option, 3 = stuff

	freopen("menu.in", "r", stdin);

	int menu_case = 0;
	scanf("%d", &menu_case);

	SDL_Surface * 	menu_pic[menu_case];
	SDL_Rect 		menu_clip[menu_case];

	for(int i = 0; i < menu_case; i++) {
		menu_pic[i] = NULL;

		int x, y, px, py;

		char whichfile[100];
		scanf("%s%d%d%d%d", &whichfile, &x, &y, &px, &py);

		menu_pic[i] = loadimage(whichfile);

		// set clip of menu
		menu_clip[i].x = px;
		menu_clip[i].y = py;
		menu_clip[i].w = x;
		menu_clip[i].h = y;

		apply_surface(px, py, menu_pic[i], screen);
	}

	int x, y;

	while(event.type != SDL_QUIT && SDL_PollEvent(&event)) {

		if(event.type == SDL_QUIT) break;
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {
				x = event.button.x;
				y = event.button.y;

				// select which type should change
				for(int i = 2; i < 5; i++)
					if(x >= menu_clip[i].x && x <= menu_clip[i].x + menu_clip[i].w && y >= menu_clip[i].y && y <= menu_clip[i].y + menu_clip[i].h) type = i - 1;
			}
		}
		SDL_Flip(screen);

	}
	SDL_Delay(1000 / SCREEN_FPS + 10);
	// WE NEED¡@ANIMATION HERE~~~~~~~~~~~~~~~~~

	// menu clean up
	for(int i = 0; i < menu_case; i++) SDL_FreeSurface(menu_pic[i]);
	fclose(stdin);
	return type;
}

int play_staff() {
	int type = 3;

	// write something here

	return type;
}

int play_game() {
	int type = 1;

	freopen("play.in", "r", stdin);

	int game_case = 0;
	scanf("%d", &game_case);

	if(game_case == 0) {
		SDL_WM_SetCaption("No", NULL);
		SDL_Delay(1000);
	}

	SDL_Surface * game_pic[game_case];
	SDL_Rect game_clip[game_case];

	for(int i = 0; i < game_case; i++) {
		game_pic[i] = NULL;

		int x, y, px, py;
		char whichfile[100];
		scanf("%s%d%d%d%d", &whichfile, &x, &y, &px, &py);

		game_pic[i] = loadimage(whichfile);

		// set clip of game
		game_clip[i].x = px;
		game_clip[i].y = py;
		game_clip[i].w = x;
		game_clip[i].h = y;

		apply_surface(px, py, game_pic[i], screen);
	}

	while(SDL_PollEvent(&event) && type == 0) {

		if(event.type == SDL_QUIT) break;
		else if(event.type == SDL_MOUSEBUTTONDOWN) {
			if(event.button.button == SDL_BUTTON_LEFT) {


			}
		}
		SDL_Flip(screen);
		SDL_Delay(1000 / SCREEN_FPS);
	}

	for(int i = 0; i < game_case; i++) {
		SDL_FreeSurface(game_pic[i]);
	}
	return type;
}

int main(int argc, char * argv[]) {

	bool quit = false;
	int type = 0;  // 0 for menu, 1 for game play, 2 for , 3 for

	init();


	//if(SDL_Flip(screen) == -1) return 1;


	while(quit == false && event.type != SDL_QUIT) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) quit = true;
		}

		switch(type) {
			case 0:
				type = play_menu();
				break;
			case 1:
				SDL_WM_SetCaption("i got play pressed", NULL);
				SDL_Flip(screen);
				type = play_game();
				break;
			case 2:
				SDL_WM_SetCaption("i got option pressed", NULL);
				SDL_Flip(screen);
				break;
			case 3:
				SDL_Delay(1000);
				SDL_WM_SetCaption("i got staff pressed", NULL);
				type = play_staff();
				break;
		}
	}

	clean_up();

    return 0;
}
