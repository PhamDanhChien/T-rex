#include "Funtion_game.h"

const unsigned int SCREEN_WEIGHT = 1200;
const unsigned int SCREEN_HEIGHT = 600;
const string TITLE = "Produced By Chien Tukky";
const unsigned int LAND = 458;
const unsigned int SPEED_BKG = 10;
const unsigned int SPEED_LEG = 50;
const unsigned int VELOCITY = 60;
const unsigned int JUMP = VELOCITY*VELOCITY/20;
unsigned int HI = 0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* surface = NULL;
SDL_Event mainEvent;
Mix_Music *gMusic5 = NULL;


int Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		return -1;
	}

	if (TTF_Init() < 0){
		SDL_Log("Unable to initialize TTF %s", TTF_GetError());
		return -1;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        return -1;
    }

	window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WEIGHT, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL){
		printf("Could not create window %s", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL){
		printf("Could not create render %s", SDL_GetError());
		return -1;
	}

	Mix_Init(MIX_INIT_MP3);

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return -1;
	}
	return 0;
}

void ApplyTexture(SDL_Texture* texture, SDL_Rect &Rect,  int x, int y){
	Rect.x = x;
    Rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &Rect);
}


int Randomab(int a,int b){
	int t = rand()%(b-a+1)+a;
	return t;
}

string Convert(int a){
	string des;
	int du;
	char bien;
	if (a == 0) return "0";
	while(a != 0){
		du = a%10;
		a = a/10;
		bien = du+48;
		des = bien+des;
	}
	return des;
}

void Showtext(int a, int b, SDL_Rect &Rect_score, TTF_Font* font, SDL_Color fg){
	string s1, s2;
	s1 = Convert(a);
	s2 = Convert(b);
	string text ="High Score: " + s1 + "       Your Scores: " + s2;
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	SDL_Texture* text_score = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, text.c_str(), &Rect_score.w, &Rect_score.h);
    SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, text_score, NULL, &Rect_score);
	delete text_score;
}

void Show_text(int a, string b, SDL_Rect &Rect, TTF_Font* font, SDL_Color fg){
	string s1, text;
	s1 = Convert(a);
	text = b + s1;
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	SDL_Texture* text_score = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, text.c_str(), &Rect.w, &Rect.h);
    SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, text_score, NULL, &Rect);
	delete text_score;
}

bool Contact(SDL_Rect r1, SDL_Rect r2, int i){
	if(i==1){
		if(r2.x+10 <= r1.x+r1.w && r1.x+r1.w <= r2.x+r2.w-30){
			if(r2.y+20 <= r1.y+40 && r1.y+40 <= r2.y+r2.h) return true;
		}
	}
	if(i==2){
		if(r2.x+30 <= r1.x+r1.w && r1.x+r1.w <= r2.x+r2.w-30){
			if(r2.y+20 <= r1.y+40 && r1.y+40 <= r2.y+r2.h-30) return true;
		}
	}
	if(i==1){
		if(r2.x <= r1.x+35 && r1.x+35 <= r2.x+r2.w-25){
			if(r2.y+10 <= r1.y+r1.h && r1.y+r1.h <= r2.y+r2.h) return true;
		}
	}
	if(i==2){
		if(r2.x+30 <= r1.x+35 && r1.x+35 <= r2.x+r2.w-50){
			if(r2.y+10 <= r1.y+r1.h && r1.y+r1.h <= r2.y+r2.h) return true;
		}
	}
	if(r2.x+10 <= r1.x && r1.x <= r2.x+r2.w-25){
		if(r2.y <= r1.y+60 && r1.y+60 <= r2.y+r2.h) return true;
	}
	return false;
}

void Update_Rect_trex(SDL_Rect &Rect_trex, int& y, int& Giatoc, bool& inland){
	static double t;
	if(Giatoc == -10){
		t+=0.035;
		Rect_trex.y =  LAND - Rect_trex.h - VELOCITY*t - 0.5*Giatoc*t*t;
	}

	if(Rect_trex.y == LAND - Rect_trex.h - JUMP) {
		Giatoc = 10;
		t=0.5;
	}

	if(Giatoc == 10){
		t+=0.035;
		Rect_trex.y = LAND - Rect_trex.h - JUMP  + 0.5*Giatoc*t*t;
	}

	if(Rect_trex.y > LAND - Rect_trex.h){
		Rect_trex.y = LAND - Rect_trex.h;
		Giatoc = 0;
		t=0;
		inland = true;
	}

	y++; if(y==2*SPEED_LEG) y=0;
}

void Show_trex(SDL_Rect Rect_trex, SDL_Texture* text_trex1, SDL_Texture* text_trex2, SDL_Texture* text_trex, int y, bool inland){
	if(y/SPEED_LEG==0 && inland == true) SDL_RenderCopy(renderer, text_trex1, NULL, &Rect_trex);
	else if(y/SPEED_LEG==1 && inland == true) SDL_RenderCopy(renderer, text_trex2, NULL, &Rect_trex);
	else SDL_RenderCopy(renderer, text_trex, NULL, &Rect_trex);
}

void Show_bkg(SDL_Texture* text_bkg, SDL_Rect Rect_bkg, int &del_bkg){
	static int i=0;
	ApplyTexture(text_bkg, Rect_bkg, del_bkg, 0);
	ApplyTexture(text_bkg, Rect_bkg, Rect_bkg.w+del_bkg, 0);

	if(i==SPEED_BKG && del_bkg > - Rect_bkg.w){
		i=0;
	    del_bkg--;
	}

	if(del_bkg == - Rect_bkg.w) del_bkg=0;
	i++;
}

SDL_Texture* Randtext(SDL_Texture *text1, SDL_Texture *text2){
	SDL_Texture* temp = NULL;
	if(rand()%2==0) temp = text1;
	else temp = text2;
	return temp;
}

int Again(){
	while(true){
		while (SDL_PollEvent(&mainEvent)){
		    switch (mainEvent.type){

		        case SDL_QUIT:{
			        return 0;
                    break;
                }

		        case SDL_KEYDOWN:{
                    if( mainEvent.key.keysym.sym == ' ' || mainEvent.key.keysym.sym == SDLK_UP){
						return 1;
                    }
                    else return 0;
                    break;
		        }

		        default: break;
            }
        }
	}

}

void Close(){
	SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

int Play_Game(){
	if(window == NULL) Init();
	system("title Produced By Chien Tukky");

	FILE *fp = NULL;
	fp = fopen("fl/Chien.dat", "rb");
	fread(&HI, sizeof(int), 1, fp);
	fclose(fp);

	TTF_Font* font = NULL;
	font = TTF_OpenFont("fl/comicz.ttf", 20);

	SDL_Color fg = { 255 , 20, 144 }, bg = {255, 69, 0}, ag = {0, 0, 255};

    surface = SDL_LoadBMP("pt/bg_day.bmp");
//    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
    SDL_Texture* text_bkg1 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = SDL_LoadBMP("pt/bg_night.bmp");
//    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
    SDL_Texture* text_bkg2 = SDL_CreateTextureFromSurface(renderer, surface);

	surface = SDL_LoadBMP("pt/trex_extra.bmp");
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture* text_trex = SDL_CreateTextureFromSurface(renderer, surface);

	surface = SDL_LoadBMP("pt/trex1_extra.bmp");
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture* text_trex1 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = SDL_LoadBMP("pt/trex2_extra.bmp");
	SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture* text_trex2 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = SDL_LoadBMP("pt/thr1_extra.bmp");
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture* text_thr1 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = SDL_LoadBMP("pt/thr2_extra.bmp");
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture* text_thr2 = SDL_CreateTextureFromSurface(renderer, surface);

    surface = TTF_RenderText_Solid(font, "Press 'X' To Exit Game!" , ag);
	SDL_Texture* text_hepl = SDL_CreateTextureFromSurface(renderer, surface);

	surface = TTF_RenderText_Solid(font, "Press SPACEBAR Or KEY UP To Play Again!" , bg);
	SDL_Texture* text_again = SDL_CreateTextureFromSurface(renderer, surface);

	Mix_Chunk *gMusic = NULL;
	Mix_Chunk *gMusic1 = NULL;
	Mix_Chunk *gMusic2 = NULL;
	Mix_Chunk *gMusic3 = NULL;
	Mix_Chunk *gMusic4 = NULL;
	Mix_Chunk *gMusic6 = NULL;
	Mix_Chunk *gMusic7 = NULL;
	Mix_Chunk *gMusic8 = NULL;


	Mix_FreeMusic(gMusic5);

	gMusic = Mix_LoadWAV("ms/jump.wav");
	gMusic1 = Mix_LoadWAV("ms/awp1.wav");
	gMusic2 = Mix_LoadWAV("ms/die1.wav");
	gMusic3 = Mix_LoadWAV("ms/go.wav");
	gMusic4 = Mix_LoadWAV("ms/com_go.wav");
	gMusic5 = Mix_LoadMUS("ms/Opera.wav");
	gMusic6 = Mix_LoadWAV("ms/fireinhole.wav");
	gMusic7 = Mix_LoadWAV("ms/boom.wav");
	gMusic8 = Mix_LoadWAV("ms/chien_mix.wav");


	SDL_FreeSurface(surface);

    SDL_Texture* temp1 = Randtext(text_thr1, text_thr2);
    SDL_Texture* temp2 = Randtext(text_thr1, text_thr2);
    SDL_Texture* temp_bkg = text_bkg1;

	SDL_Rect Rect_bkg;
	SDL_Rect Rect_highscore;
	SDL_Rect Rect_score;
	SDL_Rect Rect_trex;
	SDL_Rect Rect_help;
	SDL_Rect Rect_again;
	SDL_Rect Rect_thr1;
	SDL_Rect Rect_thr2;

	//Lấy kích thước hình
	SDL_QueryTexture(temp_bkg, NULL, NULL, &Rect_bkg.w, &Rect_bkg.h);
	SDL_QueryTexture(text_trex1, NULL, NULL, &Rect_trex.w, &Rect_trex.h);
	SDL_QueryTexture(text_thr1, NULL, NULL, &Rect_thr1.w, &Rect_thr1.h);
	SDL_QueryTexture(text_thr2, NULL, NULL, &Rect_thr2.w, &Rect_thr2.h);
	TTF_SizeText(font, "Press 'X' To Exit Game!", &Rect_help.w, &Rect_help.h);
	TTF_SizeText(font, "Press SPACEBAR Or KEY UP To Play Again!", &Rect_again.w, &Rect_again.h);

	Rect_help.x = 100;
	Rect_help.y = 50;

	Rect_again.x = 400;
	Rect_again.y = 220;

	Rect_thr1.x = 1200;
	Rect_thr1.y = LAND-Rect_thr1.h;

	Rect_trex.x = 150;
	Rect_trex.y = LAND-Rect_trex.h;

	int Score=1, b=0, type_trex=0, type=0;
	int Giatoc=0, del_bkg = 0, ran=Randomab(600 , 1000), range=600;
	bool inland = true, isRunning = true;
	double toadox=2000, kc = 1;
	int bom = Randomab(10, 30), bom1 = Randomab(0, 1);

	Rect_thr2.x=1200+ran;
	Rect_thr2.y=LAND-Rect_thr2.h;

	Rect_highscore.x = SCREEN_WEIGHT-300;
	Rect_highscore.y = 50;

	Rect_score.x = 430;
	Rect_score.y = 180;

	SDL_Rect Rect_first;

//	Mix_PlayChannel( 0, gMusic, -1 );
	Mix_PlayChannel( -1, gMusic3, 0 );
	Mix_PlayChannel(-1, gMusic8, -1);


	while(isRunning){
        while (SDL_PollEvent(&mainEvent)){
		    switch (mainEvent.type){

		        case SDL_QUIT:{
			        isRunning = false;
                    break;
                }

		        case SDL_KEYDOWN:{
                    if(inland == true && (mainEvent.key.keysym.sym == ' ' || mainEvent.key.keysym.sym == SDLK_UP)){
						Mix_PlayChannel( -1, gMusic, 0 );
						Giatoc = -10;
                        inland = false;
                    }
                    if(mainEvent.key.keysym.sym == 'x') isRunning = false;
           			break;
		        }

		        default: break;
            }
        }

        if( ( (Score/50) % 2 ) == 0 ) temp_bkg = text_bkg1;
        else temp_bkg = text_bkg2;
        Show_bkg(temp_bkg, Rect_bkg, del_bkg);

		Show_trex(Rect_trex, text_trex1, text_trex2, text_trex, type_trex, inland);
        Update_Rect_trex(Rect_trex, type_trex, Giatoc, inland);

//		Showtext(HI , Score, Rect_score, font, fg);
//		Show_text(Score, "Your Score: ", Rect_score, font, fg);

		Show_text(HI, "High Score:  ", Rect_highscore, font, fg);
		SDL_RenderCopy(renderer, text_hepl, NULL, &Rect_help);

	    if(temp1 == text_thr1){
			ApplyTexture(temp1, Rect_thr1, toadox, Rect_thr1.y);
			Rect_first.w=Rect_thr1.w;
			Rect_first.h=Rect_thr1.h;
			type=1;
		}
	    else {
			ApplyTexture(temp1, Rect_thr2, toadox, Rect_thr2.y);
			Rect_first.w=Rect_thr2.w;
			Rect_first.h=Rect_thr2.h;
			type=2;
		}
		if(temp2 == text_thr1) ApplyTexture(temp2, Rect_thr1, toadox+ran, Rect_thr1.y);
	    else ApplyTexture(temp2, Rect_thr2, toadox+ran, Rect_thr2.y);

		toadox-=kc;
		if(kc < 2.5) kc += 0.00003;
		if(kc >= 2.5) range = 800;

	    if(toadox <= -200){
			toadox = toadox+ran;
			temp1 = temp2;
			temp2 = Randtext(text_thr1, text_thr2);
			ran = Randomab(range , 1400);
	    }

	    Rect_first.x=toadox;
	    Rect_first.y=Rect_thr2.y;

		b++;
        if(b%200 == 0){Score++; b=0;}

        if(Score == 50 && b==100) Mix_PlayChannel( -1, gMusic4, 0 );
        if(Score == 15 && b == 100) Mix_PlayMusic( gMusic5, -1 );
        if(bom1 == 0){
			if(Score == 50-bom && b==100) Mix_PlayChannel( -1, gMusic6, 0 );
			if(Score == 50-bom+7 && b==100) Mix_PlayChannel( -1, gMusic7, 0 );
        }
		else{
			if(Score == 50+bom && b==100) Mix_PlayChannel( -1, gMusic6, 0 );
			if(Score == 50+bom+7 && b==100) Mix_PlayChannel( -1, gMusic7, 0 );
		}

		SDL_RenderPresent(renderer);

		if(Contact(Rect_trex, Rect_first, type) == true) {

			if(HI<Score) HI=Score;

			fp = fopen("fl/Chien.dat", "wb");
			fwrite(&HI, sizeof(int), 1, fp);
			fclose(fp);

			Mix_FreeChunk(gMusic8);
			Mix_PlayChannel( -1, gMusic1, 0 );
			SDL_Delay(700);
			Mix_PlayChannel( -1, gMusic2, 0 );

			Show_text(Score, "Game Over!!!          Your Score: ", Rect_score, font, bg);
			SDL_RenderCopy(renderer, text_again, NULL, &Rect_again);
			SDL_RenderPresent(renderer);
			if(Again() == 1) return 1;
			else{
				Close();
				return 0;
			}

		}

		SDL_RenderClear(renderer);
	}

    Close();
	return 0;
}
