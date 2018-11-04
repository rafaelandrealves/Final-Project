#ifndef _GRAFICA_H
#define _GRAFICA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "data.h"
#include "textual.h"


void GRAFICO(char ficheiro2[]);
void leituraficheiro(UNICODE * vetorLista[2019], char ficheiro2[], int * _anomin, int * _anomax);
UNICODE * insert_tail(UNICODE *_head,dados_temp *_payload);
void desenhaCirculos(UNICODE * v_cidades [2019], SDL_Renderer * renderer, int Red, int Green, int Blue);
void printCidades(UNICODE * vetorLista[2019], int anomin);
void listvectorCidades(UNICODE *vetor[2019]);
int calcLatitudePixel (float angular, int direcao);
int calcLongitudePixel(float angular, int direcao);
void renderAno (SDL_Renderer * renderer, TTF_Font *font, int ano);
void calculaMedAno(UNICODE * vetorLista[2019], listGrafica * listaMedias[2019], int anomin, int anomax);
listGrafica * create_list_grafica();
listGrafica * create_node_grafica(cidades * _payload);
void listvetorGrafica(listGrafica * vetorMedia[2019]);
listGrafica * insert_tail_grafica(listGrafica * _head, cidades * _payload);
void ProcessMouseEvent(int _mouse_pos_x, int _mouse_pos_y, float * lat, int * dirlat, float * longi, int * dirlong, int * pos_x, int * pos_y);
void procuraCidade(SDL_Renderer * renderer, TTF_Font * font, listGrafica *lista [2019], float lat, int dirlat, float longi, int dirlong, int ano, int pt_x, int pt_y);
void renderCidade(SDL_Renderer * renderer, TTF_Font * font, char nome[MAX_SIZE], float media);
int distancia (int centro_lat, int centro_long, int ponto_lat, int ponto_long);
void clearList(UNICODE *_head);
void clearListGrafica(listGrafica *_head);
void renderEscala(SDL_Renderer * renderer, TTF_Font * font);
void InitEverything(int width, int height, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer, TTF_Font **_font);
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer);
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
void RenderTable(SDL_Surface **, SDL_Renderer *);
void filledCircleRGBA(SDL_Renderer * , int , int , int , int , int , int );

#endif
