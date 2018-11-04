#ifndef _DATA_H
#define _DATA_H


#define NORTE 0
#define ESTE 2
#define SUL 1
#define OESTE 3
#define MAX_SIZE 200            // tamanho máximo para algumas strings

typedef struct // estrutura a ser utilizada para a data
{
    int dia;
    int mes;
    int ano;
} data;

typedef struct // estrutura a ser utilizada para as coordenadas geográficas
{
    float angular;
    int direcao;
} geo_coord;

typedef struct // estrutura que contem a informação de um pais ou cidade
{
    data dt;
    float temperatura;
    float incerteza;
    char pais[MAX_SIZE];
    char cidade[MAX_SIZE];
    geo_coord latitude;
    geo_coord longitude;
} dados_temp;

typedef struct UNICODE // lista principal que contém a informação de um pais ou cidade
{
    dados_temp *payload;
    struct UNICODE * next;
    struct UNICODE * prev; // só está presenta na lista dupla
} UNICODE;


typedef struct Paises // armazenar a média e o nome de cada pais para o menu 3
{
    char pais[MAX_SIZE];
    float media;

}Paises;

typedef struct Amplitude // serve para armazenar a amplitude e o nome do pais para o menu 3
{
    float dif;
    char pais[MAX_SIZE];
}Amplitude;

typedef struct cidades // estrtura para a parte gráfica que contém a média para um dado ano, o nome da cidade e as coordenadas
{
    char cidade[MAX_SIZE];
    float media;
    geo_coord latitude;
    geo_coord longitude;
} cidades;

typedef struct listGrafica // lista que contem nós do tipo cidade e contém a informação necessária para a parte gráfica
{
    cidades * payload;
    struct listGrafica * next;
} listGrafica;


typedef struct AmpCidades // função de armazenar a amplitude e o nome de uma cidade para o menu 3
{
    float dif;
    char cidade[100];
}AmpCidades;

#endif
