#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

#include "textual.h"
#include "grafica.h"
#include "data.h"

#define NORTE 0
#define ESTE 2
#define SUL 1
#define OESTE 3

#define TABLE_SIZE 850        // main game space size
#define SQUARE_SEPARATOR 8    // square separator in px

/*#define M_PI 3.1415926
#define MAX_SIZE 200            // tamanho máximo para algumas strings
#define IMAGE_HEIGHT 980        
#define IMAGE_WIDTH 1920        // tamanho da imagem
#define WINDOW_POSX 0           // posição inicial da janela x
#define WINDOW_POSY 1000        // posição inicial da janela y
#define WINDOW_SIZE_X 1920      // tamanho da janela x
#define WINDOW_SIZE_Y 980       // tamanho da janela y
#define CENTRO_X 960            // pixel do centro do mapa x
#define CENTRO_Y 490            // pixel do centro do mapa y
#define RAIO 11     */             // raio das circunferências no mapa

#define M_PI 3.1415926
#define MAX_SIZE 200            // tamanho máximo para algumas strings
#define IMAGE_HEIGHT 798        
#define IMAGE_WIDTH 1438        // tamanho da imagem
#define WINDOW_POSX 0           // posição inicial da janela x
#define WINDOW_POSY 1000        // posição inicial da janela y
#define WINDOW_SIZE_X 1438      // tamanho da janela x
#define WINDOW_SIZE_Y 798       // tamanho da janela y
#define CENTRO_X 719            // pixel do centro do mapa x
#define CENTRO_Y 399            // pixel do centro do mapa y
#define RAIO 7                 // raio das bolas



void GRAFICO(char ficheiro2[])
{
    int width = WINDOW_SIZE_X, height = WINDOW_SIZE_Y;
    TTF_Font *serif = NULL;
    SDL_Surface * imgs[1];
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    int quit = 0;                               // variável para sair da aplicação
    UNICODE * vetorLista[2019] = {NULL};        // vetor de listas com os dados todos do ficheiro das cidades
    listGrafica * vetorMedias[2019] = {NULL};   // vetor de listas com cada uma das cidades (dados relevantes para a parte gráfica)
    int anomin = 0, anomax = 0;                 // ano minimo e ano maximo para os dados
    int ano = 0;                                // variável para definir o ano a apresentar
    listGrafica * aux = NULL;                   // lista que contem o conteudo das cidades
    int mostra = 1;                             // define se o modo está em pausa(=0) ou não (=1)
    float longitude = 0.0f, latitude = 0.0f;    // variáveis para identificar a posição do rato (em coordenadas cartesianas)
    int dirLatitude = 0, dirLongitude = 0;      // variáveis para identificar a posição do rato (em coordenadas cartesianas)
    int pt_x, pt_y;                             // variáveis para guardar a posição do rato em pixeis
	int delay = 50;                             // adicionar um delay na parte gráfica

    
    leituraficheiro(vetorLista, ficheiro2, &anomin, &anomax); // leitura do ficheiro para um vetor de listas
    calculaMedAno(vetorLista, vetorMedias, anomin, anomax); // cálculo da média de cada ano para cada cidade e transferência para um vetor de listas
    InitEverything(width, height, imgs, &window, &renderer, &serif); // inicialização da fonte, imagens, janela
    renderEscala(renderer, serif);
    while(quit == 0)
    {
        for(ano = anomin; ano <= anomax; ano++) // precorrer todos os anos pois o vetor de listas está dividido por anos
        {   
            if(ano == anomin)
            {
				RenderTable(imgs, renderer); // renderização do fundo
				renderCidade(renderer, serif, "Selecione uma cidade", 0); // render um quadrado que vai aparecer o nome de uma cidade selecionada pelo utilizador e a sua temperatura
                renderEscala(renderer, serif);
				SDL_RenderPresent(renderer);
			}            
            renderAno(renderer, serif, ano); // render o ano no canto superior esquerdo da janela
            SDL_RenderPresent(renderer);
            while(SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = 1; // sair!
                }
                else if(event.type == SDL_KEYDOWN)
                {
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_q:
                            quit = 1; // sair!
                            break;
                        case SDLK_SPACE:
                            mostra = !mostra; // parar de mostrar dados ou mostrar dados
                            break;
                        default:
                            //nothing
                            break;
                    }
                }
                else if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    ProcessMouseEvent(event.button.x, event.button.y,&latitude,&dirLatitude, &longitude, &dirLongitude, &pt_x, &pt_y); // obtém as coordenadas geográficas do rato
                    procuraCidade(renderer, serif, vetorMedias, latitude, dirLatitude, longitude, dirLongitude, ano, pt_x, pt_y); // verifica se o utilizador carregou em alguma cidade.
                                                                                                                      // em caso afirmativo, rende um quadrado com a temperatura 
                                                                                                                      // média nesse ano para essa cidade
                }

            }
            while(mostra == 0 && !quit) // no caso de o utilizador ter carregado no SPACE, o programa fica à espera que o utilizador volte a carregar no espaço para que possa continuar o programa
            {
                while(SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        quit = 1;
                    }
                    else if(event.type == SDL_KEYDOWN)
                    {
                        switch( event.key.keysym.sym )
                        {
                            case SDLK_q:
                                quit = 1;
                                break;
                            case SDLK_SPACE:
                                mostra = !mostra;
                                break;
                            default:
                                //nothing
                                break;
                        }
                    }

                }
            }
            if(quit) break; // sair do loop
            aux = vetorMedias[ano]->next; // aponta o aux para o primeiro elemento da lista desse ano (sem contar com o dammy node)
            while(aux != NULL)
            {
                // rende um circulo por cada cidade
                // o centro do circulo é calculado pelas funções calcLongitudePixel e calcLatitudePixel que retornam esse valor
                // a componente R é calculada para ir alterando com a temperatura
                // a compoente G é 0
                // a componente B é calculada para ir alterando com a temperatura
                filledCircleRGBA(renderer, calcLongitudePixel(aux->payload->longitude.angular, aux->payload->longitude.direcao),
                            calcLatitudePixel(aux->payload->latitude.angular, aux->payload->latitude.direcao), 
                            RAIO, -10 + aux->payload->media*255/35, 0, 255-(aux->payload->media*255/35));
                // continuar a mostrar a temperatura de uma cidade depois do utilizador ter carregado em cima dela
                // para atualizar a temperatura da cidade que o utilizador selecionou
                procuraCidade(renderer, serif, vetorMedias, latitude, dirLatitude, longitude, dirLongitude, ano, pt_x, pt_y);
                SDL_RenderPresent(renderer);
                aux = aux->next; // apontar para o próximo elemento
            }
            SDL_Delay( delay ); // adicionar um delay
				
        }
    }
	
    TTF_CloseFont(serif); // fechar a fonte
    SDL_FreeSurface(imgs[0]); // libertar a imagem do fundo
    SDL_DestroyRenderer(renderer); // apagar o renderer que atualiza a janela
    SDL_DestroyWindow(window); // fechar a janela da aplicação
    SDL_Quit(); // fechar a biblioteca SDL
    
    for(int i = 0; i < 2019; i++)
    {
        clearList(vetorLista[i]);
        clearListGrafica(vetorMedias[i]);
    }
    
}


/*  =========================================================
    FUNÇÃO QUE PERMITE INICIALIZAR A JANELA, FONTE, IMAGENS
    \param width: largura em pixeis da janela
    \param height: altura em pixeis da janela
    \param img[]: imagem para o fundo
    \param _window: representa a janela da aplicação
    \param renderer: para atualizar todas as alterações na janela
    \param font: fonte para render texto
    =========================================================*/
void InitEverything(int width, int height, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer, TTF_Font **_font)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(width, height);
    *_renderer = CreateRenderer(width, height, *_window);

    // load the table texture
    _img[0] = IMG_Load("terra4.png");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *_font = TTF_OpenFont("FreeSerif.ttf", 30);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}


/*  =========================================================
    INICIALIZA A BIBLIOTECA GRÁFICA SDL2
    =========================================================*/
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}


/*  =========================================================
    INICIALIZA A BIBLIOTECA SDL2_ttf
    =========================================================*/
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}


/*  =========================================================
    CRIA UMA JANELA PARA A APLICAÇÃO
    \param width: largura da janela
    \param height: altura da janela
    \return: retorna um ponteiro para a janela que foi criada
    =========================================================*/
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "WarmingUp | Rodrigo Figueiredo 90185 | Rafael Cordeiro 90171", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}


/*  =========================================================
    CRIA UM RENDERIZÁVEL PARA A JANELA DA APLICAÇÃO
    \param width: largura da janela
    \param height: altura da janela
    \param _window: representa a janela à qual a renderização vai estar associada
    \return: retorna um ponteiro para a renderização que foi criada
    =========================================================*/
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}


/*  =========================================================
    RENDE A IMAGEM DE FUNDO
    \param _img[]: imagem de fundo
    \param renderer: para render a janela da aplicação
    =========================================================*/
void RenderTable(SDL_Surface *_img[], SDL_Renderer* _renderer )
{

    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest;


    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = _img[0]->w;
    tableSrc.h = _img[0]->h;
    tableDest.w = IMAGE_WIDTH;
    tableDest.h = IMAGE_HEIGHT;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // destroy everything
    SDL_DestroyTexture(table_texture);
}


/*  =========================================================
    RENDE UM CIRCULO PREENCHIDO
    \param renderer: apontador para render a janela
    \param _circleX: coordenada em X do centro do circulo
    \param _circleY: coordenada em Y do centro do circulo
    \param _circleR: raio do circulo
    \param r: vermelho
    \param g: verde
    \param b: azul
    =========================================================*/
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{
    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);
    
    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);
    
    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
}


/*  =========================================================
    LÊ O FICHEIRO DAS CIDADES. COLOCA NUM VETOR DE LISTAS QUE NA POSIÇÃO 'N' CONTÉM UM
    APONTADOR PARA A LISTA QUE CONTÉM OS DADOS DO ANO 'N'
    \param vetorLista[2019]: vetor de listas que vai guardar o apontador para a respetiva lista
    \param ficheiro2: apontador para o ficheiro das cidades
    \param _anomin: ano minimo no ficheiro (para retornar para o main)
    \param _anomax: ano maximo no ficheiro (para retornar para o main)
    =========================================================*/
void leituraficheiro(UNICODE * vetorLista[2019], char ficheiro2[], int * _anomin, int * _anomax)
{
    FILE * fp = NULL;
    dados_temp * payload = NULL;
    char buffer[MAX_SIZE];
    char pais[MAX_SIZE];
    char cidade[MAX_SIZE];
    int ano = 0, mes = 0, dia = 0, check = 0;
    float temperatura = 0.0f, incerteza = 0.0f, nlatitude = 0.0f, nlongitude = 0.0f; 
    char clongitude = 0, clatitude = 0;
    int anomin = 5000, anomax = 0; 
    char * lixo = NULL;

    fp = fopen(ficheiro2, "r");
    if(fp == NULL)
    {
        printf("Falha na abertura do ficheiro %s\n",ficheiro2);
        exit(EXIT_FAILURE);
    }
    listvectorCidades(vetorLista); // criação de listas (com dummy node) para todas as posições do vetor lista
    while(fgets(buffer, MAX_SIZE, fp) != NULL)
    {
        check = sscanf(buffer, "%d-%d-%d,%f,%f,%[^,],%[^,],%f%c,%f%c%[^\n]",&ano, &mes, &dia,
                &temperatura, &incerteza, cidade, pais, &nlatitude, &clatitude,
                &nlongitude, &clongitude, lixo);
        if (check == 11)
        {
            payload = (dados_temp *) checkedMalloc(sizeof(dados_temp));
            payload->dt.ano = ano;
            if(ano < anomin) anomin = ano; // calculo do ano minimo
            if(ano > anomax) anomax = ano; // calculo do ano maximo
            payload->dt.mes = mes;
            payload->dt.dia = dia;
            payload->temperatura = temperatura;
            payload->incerteza = incerteza;
            strcpy(payload->pais, pais);
            strcpy(payload->cidade, cidade);
            payload->latitude.angular = nlatitude;
            payload->longitude.angular = nlongitude;
            payload->latitude.direcao = (clatitude == 'N') ? NORTE : SUL;
            payload->longitude.direcao = (clongitude == 'W') ? OESTE : ESTE;
            insert_tail(vetorLista[ano], payload); // inserir na cauda da lista do respetivo ano
        }
    }
    *_anomin = anomin; // retorna para outas funções os valores de ano maximo e ano minimo
    *_anomax = anomax;
}



/*  =========================================================
                IMPRIME TODAS AS CIDADES
    \param vetorLista[2019]: vetor de listas que vai guardar o apontador para a respetiva lista
    \param _anomin: ano minimo no ficheiro
    =========================================================*/

void printCidades(UNICODE * vetorLista[2019], int anomin)
{
    UNICODE * aux = NULL;
    for(int i = anomin; i < 2019; i++) // precorrer todos os anos que serve para precorrer todas as posições do vetor
    {
        aux = vetorLista[i]->next; // aux aponta para o elemento a seguir ao dummy node
        while(aux != NULL)
        {
            printf("%d-%d-%d,%f,%f,%s,%s,%f %d,%f %d\n",aux->payload->dt.ano, aux->payload->dt.mes, aux->payload->dt.dia,
            aux->payload->temperatura, aux->payload->incerteza, aux->payload->cidade, aux->payload->pais,
            aux->payload->latitude.angular, aux->payload->latitude.direcao, aux->payload->longitude.angular,
            aux->payload->longitude.direcao);
            aux = aux->next; // proximo elemento
        }
    }
}


/*  =========================================================
   CRIA UMA LISTA COM DAMMY NODE PARA CADA POSIÇÃO DO VETOR DE LISTAS UNICODE
   \param vetorLista[2019]: vetor de listas que vai guardar o apontador para a respetiva lista
    =========================================================*/
void listvectorCidades(UNICODE *vetor[2019])
{
    int i=0;

    // criar uma lista para cada posição do vetor
    // cada posição do vetor aponta para uma lista que apenas contém dados do ano da respetiva posição do apontador no vetor
    while(i<2019)
    {
       vetor[i] = create_list(); // todas as listas têm um dammy node
        i++;
    }
}


/*  =========================================================
          CRIA UMA LISTA COM A POSIÇÃO PARA O DAMMY NODE
    \return ponteiro para o dammy node da lista criada
    =========================================================*/
listGrafica * create_list_grafica()
{
    cidades auxiliar;
    
    return create_node_grafica(&auxiliar); // criar um nó para o dummy node
}

/*  =========================================================
        CRIA UM NÓ DO TIPO CIDADES PARA ADICIONAR À LISTA
    \param _payload: apontador para o conteudo para inserir no novo elemento da lista
    \return: ponteiro para o novo elemento da lista
    =========================================================*/
listGrafica * create_node_grafica(cidades * _payload)
{
    listGrafica * aux = NULL;

    aux = (listGrafica *) checkedMalloc(sizeof(listGrafica)); // alocação de memória para o dummy node

    aux->next = NULL;
    aux->payload = _payload;
    return aux;
}
/*  =========================================================
    CRIA UMA LISTA PARA CADA POSIÇÃO DO VETOR DE LISTAS DAS CIDADES QUE CONTÉM A INFORMAÇÃO IMPORTANTE PARA A PARTE GRÁFICA
    \param vetorMedia[2019]: vetor de listas que na posição 'N' contém um apontador para a lista do tipo listGrafica que apenas
        contém os dados do ano 'N' para cada cidade
    =========================================================*/
void listvetorGrafica(listGrafica * vetorMedia[2019])
{
    int i = 0;

    while(i < 2019)
    {
        vetorMedia[i] = create_list_grafica(); // criar uma lista com dummy node para cada posição do veto
        i++;
    }
}

/*  =========================================================
    CALCULA OS PIXEIS_Y DE UM PONTO COM BASE NAS COORDENADAS GEOGRÁFICAS
    \param angular: angulo da longitude
    \param direcao: indica se é ESTE ou OESTE
    \return: retorna a coordenada em pixel desse ponto
    =========================================================*/
int calcLongitudePixel(float angular, int direcao)
{
    if (direcao == OESTE) return CENTRO_X - angular*CENTRO_X/180;
    else if (direcao == ESTE) return CENTRO_X + angular*CENTRO_X/180;
    
    return -1;
}

/*  =========================================================
    CALCULA OS PIXEIS_Y DE UM PONTO COM BASE NAS COORDENADAS GEOGRÁFICAS
    \param angular: angulo da latitude
    \param direcao: indica se é NORTE ou SUL
    \return: retorna a coordenada em pixel desse ponto
    =========================================================*/
int calcLatitudePixel (float angular, int direcao)
{
    if(direcao == NORTE) return CENTRO_Y - angular*CENTRO_Y/90;
    else if(direcao == SUL) return CENTRO_Y + angular*CENTRO_Y/90;

    return -1;
}



int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}


/*  =========================================================
    RENDE NO CANTO SUPERIOR ESQUERDO O ANO AO QUAL SE REFEREM OS DADOS APRESENTADOS
    \param renderer: para render a janela
    \param font: fonte para escrever o ano
    \param ano: ano a escrever
    =========================================================*/
void renderAno (SDL_Renderer * renderer, TTF_Font *font, int ano)
{
    SDL_Color preto = {0,0,0};
    SDL_Color light = {225, 231, 228};
    char strano[5];

    SDL_SetRenderDrawColor(renderer, light.r, light.g, light.b, light.a);   // criação da cor para o retangulo
    SDL_Rect anoRect = {45, 25, 90, 50};                                    // criação do retangulo
    SDL_RenderFillRect(renderer, &anoRect);                                 // rende o retangulo
    sprintf(strano, "%d", ano);                                             // coloca na string o valor do ano
    RenderText(55, 27, strano, font, &preto, renderer);                     // aparece o texto no ecra

}


/*  =========================================================
    A PARTIR DO VETOR DE LISTAS INICIAL VAI SER CRIADO OUTRO QUE APENAS CONTÉM A INFORMAÇÃO NECESSÁRIA PARA EXECUTAR A PARTE GRÁFICA
    \param vetorLista[2019]: vetor de listas que vai guardar o apontador para a respetiva lista
    \param vetorMedias[2019]: vetor de listas que na posição 'N' contém um apontador para a lista do tipo listGrafica que apenas
        contém os dados do ano 'N' para cada cidade
    \param anomin: ano minmo dos dados
    \param anomax: ano máximo dos dados
    =========================================================*/
void calculaMedAno(UNICODE * vetorLista[2019], listGrafica * listaMedias[2019], int anomin, int anomax)
{
    int ano = 0;
    char cidade[100];
    UNICODE * aux = NULL;
    cidades * payload_aux = NULL;
    float soma = 0.0f, media = 0.0f;
    int num = 0;
    float latitude = 0.0f, longitude = 0.0f;
    int dirlat = 0, dirlong = 0;


    listvetorGrafica(listaMedias); // criação de listas com dummy node para cada posição do vetor
    for(ano = anomin; ano <= anomax; ano++)
    {
        aux = vetorLista[ano]->next; // aponta para o nó a seguir ao dammy node
        soma = 0.0f;
        media = 0.0f;
        num = 0;
        while(aux != NULL)
        {
            soma = 0.0f;
            media = 0.0f;
            num = 0;
            strcpy(cidade, aux->payload->cidade); // guarda a cidade que está a calcular a média para saber quando é que está a ver outra cidade
            do
            {
                soma += aux->payload->temperatura;
                num++;
                dirlat = aux->payload->latitude.direcao;
                dirlong = aux->payload->longitude.direcao;
                latitude = aux->payload->latitude.angular;
                longitude = aux->payload->longitude.angular;
                aux = aux->next;
            }while(aux != NULL && strcmp(aux->payload->cidade, cidade) == 0); // enquanto ainda estiver com dados daquela cidade
            payload_aux = (cidades * ) checkedMalloc(sizeof(cidades)); // alocação de memória para o novo elemento na nova lista
            media = soma/num;
            strcpy(payload_aux->cidade, cidade);
            payload_aux->media = media;
            payload_aux->latitude.angular = latitude;
            payload_aux->latitude.direcao = dirlat;
            payload_aux->longitude.angular = longitude;
            payload_aux->longitude.direcao = dirlong;
            insert_tail_grafica(listaMedias[ano], payload_aux); // inserir na causa da lista das cidades
        }
        
    }
}


/*  =========================================================
    INSERE UM NOVO ELEMENTO NA CAUDA DA LISTA DO TIPO listGrafica
    \param _head: apontador para o inicio da lista na qual se quer inserir o novo elemento
    \param _payload: apontador para o conteúdo que se pretende colocar nesse elemento
    \return: retorna um apontador para esse elemento
    =========================================================*/
listGrafica * insert_tail_grafica(listGrafica * _head, cidades * _payload)
{
    listGrafica *aux = NULL;
    listGrafica *new_elem = NULL;
    new_elem = create_node_grafica(_payload);
    if(_head->next==NULL) // se a lista estiver vazia
    { 
        _head->next = new_elem; //aponta a head para o novo elemento;
        new_elem->next = NULL;
        return new_elem;
    }
    aux=_head;
    while(aux->next!=NULL) //encontrar o ultimo elemento
    {
        aux=aux->next;
    }

    aux->next=new_elem; // colocar o último elemento da lista a apontar para o novo elemento
    return new_elem;
}


/*  =========================================================
    DETERMINA A POSIÇÃO DO RATO
    * ProcessMouseEvent: gets the square pos based on the click positions !
    * \param _mouse_pos_x position of the click on pixel coordinates
    * \param _mouse_pos_y position of the click on pixel coordinates
    * \param _pt_x square nr
    * \param _pt_y square nr
    =========================================================*/
void ProcessMouseEvent(int _mouse_pos_x, int _mouse_pos_y, float * lat, int * dirlat, float * longi, int * dirlong, int * pos_x, int * pos_y )
{
    int posx = _mouse_pos_x; // posição_x do rato
    int posy = _mouse_pos_y; // posição_y do rato

    if(posy >= CENTRO_Y) // hemisfério sul
    {
        *dirlat = SUL;
        *lat = (90*posy /(float)CENTRO_Y) - 90;
    }
    else if(posy < CENTRO_Y) // hemisfério norte
    {
        *dirlat = NORTE;
        *lat = 90 - (90*posy/(float)CENTRO_Y);
    }
    if(posx >= CENTRO_X) // este
    {
        *dirlong = ESTE;
        *longi = (180*posx/(float)CENTRO_X) - 180;
    }
    else if(posx < CENTRO_X) // oeste
    {
        *dirlong = OESTE;
        *longi = 180 - (180*posx/(float)CENTRO_X);
    }
    *pos_x = posx;
    *pos_y = posy;
    
}


/*  =========================================================
    A PARTIR DA POSIÇÃO DO RATO, VERIFICA SE O UTILIZADOR ESTÁ A CARREGAR EM ALGUMA CIDADE
    \param renderer: para render a janela
    \param font: fonte para escrever o ano
    \param list[2019]: vetor de listas que na posição 'N' contém um apontador para a lista do tipo listGrafica que apenas
        contém os dados do ano 'N' para cada cidade
    \param lat: latitude desse ponto
    \param dirlat: direção da latitude: NORTE/SUL
    \param longi: longitude desse ponto
    \param dirlong: direção da longitude: ESTE/OESTE
    \param ano: ano corrente na gráfica
    =========================================================*/
void procuraCidade(SDL_Renderer * renderer, TTF_Font * font, listGrafica *lista [2019], float lat, int dirlat, float longi, int dirlong, int ano, int posx, int posy)
{
    listGrafica * aux = NULL;
    int check = 0; // verifica se o rato está sobre alguma cidade ou não

    aux = lista[ano]->next;
    while(aux != NULL)
    {              
        if(distancia(calcLongitudePixel(aux->payload->longitude.angular,aux->payload->longitude.direcao),
					calcLatitudePixel(aux->payload->latitude.angular, aux->payload->latitude.direcao), posx, posy))
                    // se o utilizador carregar a uma distancia inferior ao raio da bola do centro da bola
        {
            check = 1;
            break;
        }
        aux = aux->next;
    }
    if(check) renderCidade(renderer, font, aux->payload->cidade, aux->payload->media);
    if(!check) renderCidade(renderer, font, "Selecione uma cidade", 0);
}


/*  =========================================================
    RENDE NO ECRÃ A CIDADE QUE O UTILIZADOR CARREGOU E A SUA TEMPERATURA
    \param renderer: para render a janela
    \param font: fonte para escrever o ano
    \param nome[MAX_SIZE]: nome da cidade que o utilizador carregou
    \param media: temperatura média desse cidade
    =========================================================*/
void renderCidade(SDL_Renderer * renderer, TTF_Font * font, char nome[MAX_SIZE], float media)
{
    SDL_Color preto = {0,0,0};
    SDL_Color branco = {225, 231, 228};
    char temperatura[5];
    char bola[2] = "o";
    char unidades[2] = "C";

    SDL_SetRenderDrawColor(renderer, branco.r, branco.g, branco.b, branco.a);
    SDL_Rect cidade_rect = {45, 530, 300, 150};
    SDL_RenderFillRect(renderer, &cidade_rect);
    RenderText(70, 535, nome, font, &preto, renderer);
    sprintf(temperatura, "%.4f", media);
    RenderText(100, 600, temperatura, font, &preto, renderer);
    RenderText(220, 588, bola, font, &preto, renderer);
    RenderText(235, 600, unidades, font, &preto, renderer);

}

/*  =========================================================
    CALCULA A DISTANCIA DE UM DADO PONTO AO CENTRO DE UMA CIRCUNFERÊNCIA
    \param centro_lat: latitude do centro da circunferência
    \param centro_long: longitude do centro da circunferência
    \param ponto_lat: latitude do ponto que o utilizador carregou
    \param ponto_long: longitude do ponto que o utilizador carregou
    =========================================================*/
int distancia (int centro_x, int centro_y, int ponto_x, int ponto_y)
{
    if(sqrt(pow(centro_x - ponto_x,2) + pow(centro_y - ponto_y, 2)) <= RAIO) return 1; // caso onde o utilizador carregou esteja dentro 
                                                                                    // da circunferencia dessa cidade
    
    return 0;
}

/*  =========================================================
            ELIMINAÇÃO DE TODA A LISTA listGrafica
    \param _head: endereço da cabeça da lista
    =========================================================*/
void clearListGrafica(listGrafica *_head)
{
    /*UNICODE *aux=NULL;
    aux=(*_head)->next;
    while(remove_node(&aux) != -1)
    {
        if(aux->next!=NULL)
        {
            aux=aux->next;
        }
        else
        {
            return;
        }
    }*/
    listGrafica *aux = NULL, * tmp = NULL;
    aux = _head->next;
    if(aux == NULL) // lista vazia
    {
        return;
    }
    while(aux != NULL)
    {
        tmp = aux->next;
        free(aux->payload); // libertar o conteudo
        free(aux); // libertar o nó
        aux = tmp; // colocar o aux a apontar para o elemento a seguir ao que foi removido
    }
}


/*  =========================================================
            RENDER DA LEGENDA DAS CORES
    \param renderer: para render a janela
    \param font: fonte para escrever as temperaturas
    =========================================================*/
void renderEscala(SDL_Renderer * renderer, TTF_Font * font)
{
    SDL_Color preto = {0,0,0};
    SDL_Color branco = {225, 231, 228};

    char minimo[10] = "-3  C";
    char medio[10] = "17,5  C";
    char maximo[10] = "32  C";
    char bola[2] = "o";

    SDL_SetRenderDrawColor(renderer, branco.r, branco.g, branco.b, branco.a);
    SDL_Rect legenda = {45, 400, 280, 90};
    SDL_RenderFillRect(renderer, &legenda);
    RenderText(55, 450, minimo, font, &preto, renderer); // render a temperatura minima
    RenderText(80, 435, bola, font, &preto, renderer); // render a bolina do grau
    RenderText(145, 450, medio, font, &preto, renderer); // render a temperatura média
    RenderText(200, 435, bola, font, &preto, renderer);// render a bolina do grau
    RenderText(255, 450, maximo, font, &preto, renderer); // render a temperatura máxima
    RenderText(286, 435, bola, font, &preto, renderer);// render a bolina do grau
    
    filledCircleRGBA(renderer, 70, 425, RAIO+10, 0, 0, 255); // bola azul
    filledCircleRGBA(renderer, 190, 425, RAIO+10, 127, 0, 127); // bola roxa
    filledCircleRGBA(renderer, 300, 425, RAIO+10, 255, 0, 0); // bola vermelha
}