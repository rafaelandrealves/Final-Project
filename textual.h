#ifndef _TEXTUAL_H
#define _TEXTUAL_H
#include "data.h"

void TEXTUAL(char ficheiro1[], char ficheiro2[]);
void menu1(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char  ficheiro2[]);
void menu1_1(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[]);
void menu1_2(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[]);
void menu1_3(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[]);
void menu1_4(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[]);
void menu1_1_1(UNICODE **v_paises, UNICODE ** v_cidades, char ficheiro1[], char ficheiro2[]);
void menu1_1_2(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades);
void menu1_1_3(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades);
void menu1_2_1(UNICODE *v_paises, int anomax_paises, int anomin_paises);
void menu1_2_2(UNICODE *v_paises, int anomax_paises, int anomin_paises);
void menu1_2_3(UNICODE * v_cidades, int anomax_cidades, int anomin_cidades);
void menu1_3_1(UNICODE *v_paises, int anomax_paises, int anomin_paises, int ano);
void menu1_3_2(UNICODE * v_cidades, int anomax_paises, int anomin_cidades,int ano);
void menu1_4_2(UNICODE *copia,float minficheiro);
void menu1_4_3(UNICODE *copia,float minficheiro);
void menu1_4_1(UNICODE *copia,float minficheiro);
int obterParametros(int argc,char* argv[],char ficheiro1[],char ficheiro2[]);
void leitura_dados_paises(UNICODE *v_paises,char* ficheiro1, int *anomax_paises, int *anomin_paises);
void leitura_dados_cidades(UNICODE *v_cidades,char *ficheiro2, int *anomax_cidades, int *anomin_cidades);
UNICODE * create_list ();
UNICODE * create_node(dados_temp * _payload);
void insert_node(UNICODE * _head, dados_temp * _payload);
void printList(UNICODE * head);
UNICODE * insert_tail(UNICODE *_head,dados_temp *_payload);
void insert_sorted(dados_temp * _payload, UNICODE * vect);
void clearList(UNICODE *_head);
int remove_node(UNICODE *_head);
UNICODE* juntarlista(UNICODE *vetor[2019], int anomax_paises, int anomin_paises);
void listvector(UNICODE *vetor[2019]);
UNICODE * limparintervalo(UNICODE **v, int anomax_paises, int anomin_paises, int mes, int ano);
UNICODE * limpaMeses(UNICODE **v, int anomax_paises, int anomin_paises, int mesinicial, int mesfinal);
void printListCidades(UNICODE * head);
void * checkedMalloc(size_t size);
FILE * checkedFile(char * fich, char * modo);
void analise_da_temperatura_ano_pais(UNICODE *copia,int numeropaises,int ano);
void calculamedia(UNICODE *vetor[2019], int numerodedados,Paises *vetorpaises[1000]);
void organizapaises(UNICODE *copia, int *numeropaises,int ano,UNICODE *vetor[2019]);
void insertcountries(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido);
void insertcountriesminimo(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido);
void calculaamplitude(UNICODE *vetor[2019], int numerodedados,Amplitude *vetorpaises[1000]);
void insertcountriesAmplitude(Amplitude *vetor[1000],Amplitude *vetorfinal[20],int numerodedados,int numeroinserido);
void analise_da_temperatura_ano_cidade(UNICODE *copia,int numeropaises,int ano);
void insertcidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido);
void insertcountriesminimocidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido);
void calculaamplitudeCidades(UNICODE *vetor[2019], int numerodedados,AmpCidades *vetorcidades[1000]);
void insertcountriesAmplitudeCidades(AmpCidades *vetor[1000],AmpCidades *vetorfinal[20],int numerodedados,int numeroinserido);
void calculamediacidades(UNICODE *vetor[2019], int numerodedados,cidades *vetorcidades[1000]);
void organizacidades(UNICODE *copia, int *numerocidades,int ano,UNICODE *vetor[2019]);
void movingAveragePais(UNICODE *copia,float *max,float *min,char pais[100],float minficheiro,int intervalo, int ano);
void criaagrupamentos(float media_mes[13],int intervalo, float *media_do_ano);
void remove_nodes_vetor(UNICODE *vetor[2019]);
void organizapaisesMA(UNICODE *copia, int *numeropaises,int ano,UNICODE *vetor[2019],char pais[100]);
void Ledadospais(UNICODE *v,char pais[100],UNICODE *listapais, int ano,int *check);
void calculamediaparacadames(UNICODE *vetor,float media_mes[13]);
void Ledadoscidades(UNICODE *v,char cidade[100],UNICODE *listacidade, int ano, int *check);
void criaagrupamentos_cidades(float media_mes[13],int intervalo, float *media_do_ano);
void movingAverage_cidade(UNICODE *copia,float *max,float *min,char cidade[100],float minficheiro,int intervalo, int ano);
void criaagrupamentosGlobal(float media_mes[13],int intervalo, float *media_do_ano);
void LedadosG(UNICODE *v,UNICODE *lista, int ano, int *check);
void movingAverageG(UNICODE *copia,float *max,float *min,float minficheiro,int intervalo, int ano);

#endif
