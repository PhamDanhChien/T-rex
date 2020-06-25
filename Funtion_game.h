
#include <iostream>
#include <conio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include <bits/stdc++.h>
#include <cmath>
#undef main

using namespace std;




int Init();
void ApplyTexture(SDL_Texture* texture, SDL_Rect &Rect,  int x, int y);
int Randomab(int a,int b);
void Update_Rect_trex(SDL_Rect &Rect_trex, int& y, int& Giatoc, bool& inland);
void Showtext(int a, int b, SDL_Rect &Rect_score, TTF_Font* font, SDL_Color fg);
void Show_HighScore(int a, SDL_Rect &Rect_score, TTF_Font* font, SDL_Color fg);
void Show_bkg(SDL_Texture* text_bkg, SDL_Rect Rect_bkg, int &del_bkg);
void Show_trex(SDL_Rect Rect_trex, SDL_Texture* text_trex1, SDL_Texture* text_trex2, SDL_Texture* text_trex, int y, bool inland);
bool Contact(SDL_Rect r1, SDL_Rect r2, int i);
int Again();
void Close();
SDL_Texture* Randtext(SDL_Texture *text1, SDL_Texture *text2);
int Play_Game();





