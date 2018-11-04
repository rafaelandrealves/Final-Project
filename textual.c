#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textual.h"

#define MAX_SIZE 200


/*  =========================================================
                    MODO TEXTUAL
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void TEXTUAL(char ficheiro1[], char ficheiro2[])
{
    UNICODE *v_paises=create_list();
    UNICODE *v_cidades=create_list();
    int anomax_paises = 0, anomin_paises = 0;
    int anomax_cidades = 0, anomin_cidades = 0;
    
    leitura_dados_paises(v_paises, ficheiro1, &anomax_paises, &anomin_paises);
    leitura_dados_cidades(v_cidades, ficheiro2, &anomax_cidades, &anomin_cidades);
    menu1(&v_paises, &v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);

    clearList(v_paises); // libertar todos os nós da lista dos paises
    clearList(v_cidades);  // libertar todos os nós da lista das cidades
}


/*  =========================================================
                    MENU PRINCIPAL
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[])
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];

    printf("=========================================================================\n\t\t\tMENU PRINCIPAL\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("0/ENTER. Sair da aplicação\n1. Filtragem de dados\n2. Historico de temperaturas\n3. Analise de temperaturas por ano\n4. Analise da temperatura global\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("0/ENTER. Sair da aplicação\n1. Filtragem de dados\n2. Historico de temperaturas\n3. Analise de temperaturas por ano\n4. Analise da temperatura global\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }
    switch (aux)
    {
        case 0:
            printf("=========================================================================\n\t\t\tAPLICAÇÃO FECHADA\n=========================================================================\n");
            break;
        case 1:
            // Filtragem de dados
            menu1_1(v_paises,v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            // Histórico de temperatura
            menu1_2(*v_paises,*v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // Análise de temperatura para um ano
            menu1_3(*v_paises,*v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 4:
            // Análise da temperaura global - Moving Average
            menu1_4(*v_paises, *v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            //menu1(v_paises,v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1(v_paises,v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}


/*  =========================================================
                    FILTRAGEM DE DADOS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[])
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];
    printf("=========================================================================\n\t\t\tFILTRAGEM DE DADOS\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Limpa critérios\n\t2. Escolhe intervalo para análise\n\t3. Escolhe mês para analise\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Limpa critérios\n\t2. Escolhe intervalo para análise\n\t3. Escolhe mês para analise\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }

    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(v_paises,v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // FUNÇÃO PARA LIMPAR CRITÉRIOS
            menu1_1_1(v_paises, v_cidades, ficheiro1, ficheiro2);
            menu1(v_paises,v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            // FUNÇÃO PARA INTERVALO PARA ANÁLISE
            menu1_1_2(v_paises, v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades);
            menu1(v_paises,v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // FUNÇÃO PARA ANALISAR MÊS
            menu1_1_3(v_paises, v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades);
            menu1(v_paises,v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_1(v_paises,v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}


/*  =========================================================
                HISTÓRICO DE TEMPERATURAS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_2(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[])
{
    int aux = 0, check = 0;
    char buffer[MAX_SIZE];
    
    printf("=========================================================================\n\t\t\tHISTÓRICO DE TEMPERATURAS\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Global: aplica-se a todos os paises\n\t2. Por pais: aplica-se a um unico pais\n\t3. Por cidade: aplica-se a uma unica cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Global: aplica-se a todos os paises\n\t2. Por pais: aplica-se a um unico pais\n\t3. Por cidade: aplica-se a uma unica cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }
    switch (aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises,&v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            //GLOBAL
            menu1_2_1(v_paises, anomax_paises, anomin_paises);
            menu1(&v_paises,&v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //POR PAIS
            menu1_2_2(v_paises, anomax_paises, anomin_paises);
            menu1(&v_paises,&v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            // POR CIDADE
            menu1_2_3(v_cidades, anomax_cidades, anomin_cidades);
            menu1(&v_paises,&v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_2(v_paises,v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}


/*  =========================================================
                ANÁLISE DE TEMPERATURA POR ANO
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_3(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[])
{
    int aux = 0, check = 0,ano = 0;
    char buffer[MAX_SIZE];

    printf("=========================================================================\n\t\t\tANÁLISE DE TEMPERATURA POR ANO\n=========================================================================\n");
    printf("Escolha o ano que deseja estudar [%d;%d]:\nCaso tenha aplicado critérios, este intervalo não se aplica!: ", anomin_paises, anomax_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &ano);
    while(check != 1 || ano > anomax_paises || ano < anomin_paises)
    {
        printf("Escolha o ano que deseja estudar [%d;%d]:\nCaso tenha aplicado critérios, este intervalo não se aplica!: ", anomin_paises, anomax_paises);
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &ano);
    }
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Analisa por pais\n\t2. Analisa por cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    if (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Analisa por pais\n\t2. Analisa por cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }


    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises, &v_cidades,anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // ANÁLISE POR PAIS
            menu1_3_1(v_paises, anomax_paises, anomin_paises, ano);
            menu1(&v_paises, &v_cidades,anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //ANÁLISE POR CIDADE
            menu1_3_2(v_cidades, anomax_cidades, anomin_cidades, ano);
            menu1(&v_paises,&v_cidades, anomax_paises,anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_3(v_paises,v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}


/*  =========================================================
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        ANÁLISE DA TEMPERATURA GLOBAL - MOVING AVERAGE
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    =========================================================*/
void menu1_4(UNICODE *v_paises, UNICODE * v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades, char ficheiro1[], char ficheiro2[])
{
    char buffer[MAX_SIZE];
    int aux=0;
    int check = 0;
    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA GLOBAL - MOVING AVERAGE\n=========================================================================\n");
    printf("Escolha uma das seguintes opcoes:\n");
    printf("\t1. Análise Global\n\t2. Análise por pais\n\t3. Análise por cidade\n\t0/ENTER. Voltar ao menu principal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &aux);
    while (check == 0)
    {
        printf("Volte a introduzir o número de um menu\n");
        printf("\t1. Análise Global\n\t2. Análise por pais\n\t3. Análise por cidade\n\t0/ENTER. Voltar ao menu principal\n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &aux);
    }
    switch(aux)
    {
        case 0:
            //VOLTAR AO MENU PRINCIPAL
            menu1(&v_paises,&v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 1:
            // ANÁLISE GLOBAL
            menu1_4_1(v_paises, anomin_paises);
            menu1(&v_paises,&v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 2:
            //ANÁLISE POR PAIS
            menu1_4_2(v_paises, anomin_paises);
            menu1(&v_paises,&v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        case 3:
            //ANALISE POR CIDADE
            menu1_4_3(v_cidades, anomin_paises);
            menu1(&v_paises,&v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
            break;
        default:
            printf("Volte a introduzir o número de um menu\n");
            menu1_4(v_paises,v_cidades, anomax_paises, anomin_paises, anomax_cidades, anomin_cidades, ficheiro1, ficheiro2);
    }
}

/*  =========================================================
                    LIMPAR CRITÉRIOS
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_1(UNICODE **v_paises, UNICODE ** v_cidades, char ficheiro1[], char ficheiro2[])
{
    printf("=========================================================================\n\t\t\tLIMPAR CRITÉRIOS\n=========================================================================\n");
    int anomin_lixo_paises = 0, anomax_lixo_paises = 0;
    int anomin_lixo_cidades = 0, anomax_lixo_cidades = 0;
    
    //limpar as listas atuais dos paises e das cidades
	clearList(*v_paises);
	clearList(*v_cidades);
	
    // voltar a ler os ficheiros para construir novas listas com os dados originais
    leitura_dados_paises(*v_paises, ficheiro1, &anomax_lixo_paises, &anomin_lixo_paises);
    leitura_dados_cidades(*v_cidades, ficheiro2, &anomax_lixo_cidades, &anomin_lixo_cidades);
    printf("=========================================================================\n\t\t\tCRITÉRIOS LIMPOS\n=========================================================================\n");
}


/*  =========================================================
                ESCOLHE INTERVALO PARA ANÁLISE
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_2(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades)
{
    printf("=========================================================================\n\t\tESCOLHA DE INTERVALO PARA ANÁLISE\n=========================================================================\n");
    char buffer[MAX_SIZE]={'\0'};
    int check=0;
    int mes_paises = 0,ano_paises=0, mes_cidades = 0, ano_cidades = 0;

    // OS VALORES SÃO PEDIDOS PARA OS PAISES E PARA AS CIDADES POIS PODEM NÃO TER OS MESMOS ANOS MINIMOS E MÁXIMOS

    printf("PARA OS PAISES: Insira o mês e ano que deseja fixar segundo a forma mês:ano. Mes:[1;12]. Ano:[%d;%d]\n", anomin_paises, anomax_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mes_paises,&ano_paises);
    while((check != 2) || (mes_paises>12 || mes_paises<1) || (ano_paises<anomin_paises || ano_paises>anomax_paises))
    {
        printf("A data não foi bem introduzida! Volte a introduzir a data: \n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mes_paises,&ano_paises);
    }
    printf("PARA AS CIDADES: Insira o mês e ano que deseja fixar segundo a forma mês:ano. Mes:[1;12]. Ano:[%d;%d]\n", anomin_cidades, anomax_cidades);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mes_cidades,&ano_cidades);
    while((check != 2) || (mes_cidades>12 || mes_cidades<1) || (ano_cidades<anomin_cidades || ano_cidades>anomax_cidades))
    {
        printf("A data não foi bem introduzida! Volte a introduzir a data: \n");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mes_cidades,&ano_cidades);
    }
    //limpeza dos dados para o intervalo definido
    //executa para os paises e para as cidades
    *v_paises = limparintervalo(v_paises, anomax_paises, anomin_paises, mes_paises, ano_paises);
    *v_cidades = limparintervalo(v_cidades, anomax_cidades, anomin_cidades, mes_cidades, ano_cidades);    
    printf("=========================================================================\n\t\t\tCRITÉRIO APLICADO\n=========================================================================\n\n");
}


/*  =========================================================
                ESCOLHE MÊS PARA ANÁLISE
    \param v_paises: lista dos paises
    \param v_cidades: lista das cidades
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ficheiro1: ficheiro para os paises
    \param ficheiro2: ficheiro para as cidades
    =========================================================*/
void menu1_1_3(UNICODE **v_paises, UNICODE ** v_cidades, int anomax_paises, int anomin_paises, int anomax_cidades, int anomin_cidades)
{
    char buffer[200]={'\0'};
    int check=0;
    int mesinicial,mesfinal=0;
    
    printf("=========================================================================\n\t\t\tESCOLHA DE MÊS PARA ANÁLISE\n=========================================================================\n");
    printf("Insira o mês inicial e final que deseja fixar segundo a forma mêsinicial:mêsfinal\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d:%d", &mesinicial,&mesfinal);
    while((check != 2) || (mesinicial > 12 || mesinicial < 1 || mesfinal < 1 || mesfinal > 12) || mesfinal == mesinicial)
    {
        printf("Volte a introduzir os meses: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d:%d", &mesinicial,&mesfinal);
    }

    // limpa os meses que não estão no intervalo indicado pelo utilizador
    // retorna um apontados para o inicio da nova lista
    // executa duas vezes pois é para os paises e para as cidades
    *v_paises = limpaMeses(v_paises, anomax_paises, anomin_paises, mesinicial, mesfinal);
    *v_cidades = limpaMeses(v_cidades, anomax_cidades, anomin_cidades, mesinicial, mesfinal);
    printf("=========================================================================\n\t\t\tCRITÉRIO APLICADO\n=========================================================================\n\n");
}



/*  =========================================================
                ANÁLISE GLOBAL DA TEMPERATURA
    \param v_paises: lista dos paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void menu1_2_1(UNICODE *v_paises, int anomax_paises, int anomin_paises)
{
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    int num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    UNICODE * aux = v_paises->next;
    UNICODE * tmp = NULL;
    char comando = 0;
    char buffer[MAX_SIZE];
    int intervalo = 0, check = 0;
    printf("=========================================================================\n\t\t\tANÁLISE GLOBAL DA TEMPERATRA\n=========================================================================\n");
    
    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_paises-anomin_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_paises-anomin_paises)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }

    while(aux->next != NULL)
    {
        // voltar a inicializar as variáveis utilizadas para os cálculos
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0; 
        anoFinal = aux->payload->dt.ano + intervalo - 1; // cálculo do ano final do intervalo para os calculos atuais
        tmp = aux; // manter o ponteiro para o inicio daquele ano e apenas "andar" até ao ano final daquele intervalo
        do
        {
            soma += (tmp->payload->temperatura); // para o cálculo da média
            num++; // para o cálculo da média
            if(tmp->payload->temperatura > max) max = tmp->payload->temperatura; // calculo da temperatura máxima
            if(tmp->payload->temperatura < min) min = tmp->payload->temperatura;
            valDados = 1; // os dados lidos foram válidos
            tmp = tmp->next;
        }while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal)); // enquanto que os dados que eu estou a ler sejam inferiores ao ano máximo do intervalo em curso
        med = soma/num; // calculo da média
        if(anoFinal >= anomax_paises) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1 && !(max == 0 && min == 0 && med == 0)) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_paises, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_paises);
        }
        else 
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1 && !(max == 0 && min == 0 && med == 0)) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        valDados = 0; // colocar a variável de validade a 0
        // "andar" com o apontador aux até encontrar o último elemento do ano final do intervalo em causa
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20) // caso já tenha impresso 20 linhas
        {    
            printf("Introduza 'a' mostrar mais dados ou 'q' para voltar ao menu principal\n");
            scanf("%c", &comando);
            if(comando == 97 && comando != 0) // detetar o 'a'
            {
                numLinhas = 0; // voltar a contar 20 linhas
                comando = 0;
            }
            else if(comando == 113 && comando != 0) // detetar o 'q'
            {
                getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
                return;
            }
            getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
        }
        numLinhas++; // incrementar o número de linhas impressas
    }
}



/*  =========================================================
                ANÁLISE DA TEMPERATURA DE UM PAIS
    \param v_paises: lista dos paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void menu1_2_2(UNICODE *v_paises, int anomax_paises, int anomin_paises)
{
    char nome_pais[MAX_SIZE];
    char buffer[MAX_SIZE];
    int i = 0, num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    UNICODE * aux = v_paises->next;
    UNICODE * tmp = NULL;
    int check = 0, intervalo = 0;
    char comando = 0;

    printf("=========================================================================\n\t\t\tANÁLISE DA TEMPERATURA DE UM PAIS\n=========================================================================\n");
    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_paises-anomin_paises);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_paises-anomin_paises)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza o nome de um pais: ");
    fgets(nome_pais, MAX_SIZE, stdin);
    // serve para retirar o \n e colocar \0 em todas as posições da string. Desta forma permite a comparação do nome com os paises
    for(i = strlen(nome_pais)-1; i < MAX_SIZE; i++)
    {
        nome_pais[i] = '\0';
    }    
    aux = v_paises->next;
    while(aux->next != NULL)
    {
        // voltar a inicializar as variáveis utilizadas para os cálculos
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0;
        anoFinal = aux->payload->dt.ano + intervalo - 1; // cálculo do ano final do intervalo para os calculos atuais
        tmp = aux;
        do
        {
            if(strstr(tmp->payload->pais, nome_pais) != NULL) // se encontrar o pais que o utilizador introduziu
            {
                soma += (tmp->payload->temperatura); // para o cálculo da média
                num++; // para o cálculo da média
                if(tmp->payload->temperatura > max) max = tmp->payload->temperatura; // calculo da tmeperatura máxima
                if(tmp->payload->temperatura < min) min = tmp->payload->temperatura; // calculo da temperatura minima
                valDados = 1; // dados válidos
            }
            tmp = tmp->next;
        }while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal)); // enquanto que os dados que eu estou a ler sejam inferiores ao ano máximo do intervalo em curso
        med = soma/num;
        if(anoFinal > anomax_paises) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_paises, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_paises);
        }
        else 
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        valDados = 0; // colocar a variável de validade a 0
        // "andar" com o apontador aux até encontrar o último elemento do ano final do intervalo em causa
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20) // caso já tenha impresso 20 linhas
        {
            printf("Introduza 'a' mostrar mais dados ou 'q' para voltar ao menu principal\n");
            scanf("%c", &comando);
            if(comando == 97 && comando != 0) // detetar o 'a'
            {
                numLinhas = 0; // voltar a contar 20 linhas
                comando = 0; // reenicializar a variavel
            }
            else if(comando == 113 && comando != 0) // detetar o 'q'
            {
                getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
                return;
            }
            getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
        }
		numLinhas++; // incrementa o número de linhas impressas

    }
}


/*  =========================================================
            ANÁLISE DA TEMPERATURA DE UMA CIDADE
    \param v_cidades: lista das cidades
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    =========================================================*/
void menu1_2_3(UNICODE * v_cidades, int anomax_cidades, int anomin_cidades)
{
    char nome_cidade[MAX_SIZE];
    char buffer[MAX_SIZE];
    int i = 0, num = 0, anoFinal = 0, numLinhas = 0, valDados = -1;
    float min = 500.0f, max = -50.0f, med = 0.0f, soma = 0.0f;
    int intervalo = 0, check = 0;
    UNICODE * tmp;
    UNICODE * aux = v_cidades->next;
    char comando = 0;

    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA DE UMA CIDADE\n=========================================================================\n");
    printf("Introduza o tempo de intervalo para análise [1, %d]: ", anomax_cidades-anomin_cidades);
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while (check == 0 || intervalo <= 0 || intervalo > anomax_cidades-anomin_cidades)
    {
        printf("O valor não é valido! Volte a introduzir um intervalo de tempo para análise: ");
        fgets(buffer, MAX_SIZE, stdin);
        check = sscanf(buffer, "%d", &intervalo);
    }

    printf("Introduza o nome de uma cidade: ");
    fgets(nome_cidade, MAX_SIZE, stdin);
    // serve para retirar o \n e colocar \0 em todas as posições da string. Desta forma permite a comparação do nome com os paises
    for(i = strlen(nome_cidade)-1; i < MAX_SIZE; i++)
    {
        nome_cidade[i] = '\0';
    }
    aux = v_cidades->next;
    while(aux->next != NULL)
    {
        // voltar a inicializar as variáveis utilizadas para os cálculos
        min = 500.0f;
        max = -50.0f;
        med = 0.0f;
        soma = 0.0f;
        num = 0;
        comando = 0;
        anoFinal = aux->payload->dt.ano + intervalo - 1; // cálculo do ano final do intervalo para os calculos atuais
        tmp = aux;
        do
        {
            if(strstr(tmp->payload->cidade, nome_cidade) != NULL)
            {
                soma += (tmp->payload->temperatura); // para o cálculo da média
                num++; // para o cálculo da média
                if(tmp->payload->temperatura > max) max = tmp->payload->temperatura; // calculo da temperatura máxima
                if(tmp->payload->temperatura < min) min = tmp->payload->temperatura; // calculo da temperatura minima
                valDados = 1; // os dados lidos foram válidos
            }
            tmp = tmp->next;
        }
        while((tmp->next != NULL) && (tmp->payload->dt.ano<=anoFinal)); // enquanto que os dados que eu estou a ler sejam inferiores ao ano máximo do intervalo em curso

        med = soma/num;
        if(anoFinal > anomax_cidades) // para no intervalo não aparecer um ano superior ao ano máximo
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anomax_cidades, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anomax_cidades);
        }
        else 
        {
            // verifica a validade dos dados e se há dados nesse intervalo
            if(valDados == 1) printf("[%d;%d[: MAX: %.5f\t MIN: %.5f\t MED: %.5f\n", aux->payload->dt.ano, anoFinal, max, min, med);
            else printf("[%d;%d[: Não há dados do pais neste intervalo\n", aux->payload->dt.ano, anoFinal);
        }
        valDados = 0; // colocar a variável de validade a 0
        // "andar" com o apontador aux até encontrar o último elemento do ano final do intervalo em causa
        while(aux->next != NULL && aux->payload->dt.ano <= anoFinal)
        {
            aux = aux->next;
        }
        if(numLinhas == 20)
        {
            printf("Introduza 'a' mostrar mais dados ou 'q' para voltar ao menu principal\n");
            scanf("%c", &comando);
            if(comando == 97 && comando != 0) // detetar o 'a'
            {
                numLinhas = 0; // volta a contar 20 linhas
                comando = 0; // reenicializar a variavel
            }
            else if(comando == 113 && comando != 0) // detetar o 'q'
            {
                getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
                return;
            }
            getchar(); // vai buscar o '\n' para não influeniar a próxima leitura
        }
        numLinhas++; // incrementar o número de linhas impressas

    }
}


/*  =========================================================
            ANÁLISE DA TEMPERATURA POR ANO POR PAIS
    \param v_paises: lista dos paises
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    =========================================================*/
void menu1_3_1(UNICODE *v_paises, int anomax, int anomin, int ano)
{
    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA POR ANO POR PAIS\n=========================================================================\n");
    int check=0;
    char buffer[100]={'\0'};
    int numPaises=0;
    printf("Qual o número de paises que pretende ver para cada critério? [1;20]: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &numPaises);
    while(check != 1 || numPaises > 20 || numPaises < 1)
    {
        printf("Volte a introduzir o número de paises para cada critério [1;20]: ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &numPaises);
    }
    analise_da_temperatura_ano_pais(v_paises->next->next,numPaises, ano);

}


/*  =========================================================
            ANÁLISE DA TEMPERATURA POR ANO POR CIDADE
    \param v_cidades: lista das cidades
    \param anomax_cidades: ano máximo das cidades
    \param anomin_cidades: ano minimo das cidades
    \param ano: ano para análise escolhido pelo utilizador
    =========================================================*/
void menu1_3_2(UNICODE * v_cidades, int anomax_paises, int anomin_cidades, int ano)
{
    int check=0;
    char buffer[100]={'\0'};
    int numCidades=0;

    printf("=========================================================================\n\t\tANÁLISE DA TEMPERATURA POR ANO POR CIDADE\n=========================================================================\n");
    printf("Qual o número de cidades que pretende ver para cada critério? [1;20]: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &numCidades);
    while(check!=1 || numCidades > 20 || numCidades < 1)
    {
        printf("Volte a introduzir o número de paises para cada critério [1;20]: ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &numCidades);
    }
    analise_da_temperatura_ano_cidade(v_cidades->next->next,numCidades, ano);
}


/*  =========================================================
                ANÁLISE GLOBAL - MOVING AVERGAE
    \param copia: lista ordenada de paises
    \param minficheiro:ano minimo no ficheiro dos paises
    =========================================================*/
void menu1_4_1(UNICODE *copia,float minficheiro)
{
    int intervalo=0,i=0;
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    char buffer[100]={'\0'};
    int check=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo<1)
    {
        printf("Volte a introduzir o número do intervalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }


    while(i<5)
    {
        minimo=100.0f;
        maximo=-100.0f;
        movingAverageG(copia->next->next,&maximo,&minimo,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f)
        {
            printf("O max para %d é %f\n",vetoranalise[i],maximo);
            printf("O min para %d é  %f\n",vetoranalise[i],minimo);
            printf("A diferença é %f\n",diferencamax);
        }
        i++;
    }


}

/*  =========================================================
                ANÁLISE POR PAIS - MOVING AVERAGE
    \param copia: lista  ordenada dos paises
    \param minficheiro: ano minimo no ficheiro dos paises
    =========================================================*/
void menu1_4_2(UNICODE *copia,float minficheiro)
{
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    int check=0, intervalo=0;
    char pais[100]={'\0'};
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    char buffer[100]={'\0'};
    int i=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo<1)
    {
        printf("Volte a introduzir o número do inertvalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza o pais para o cálculo: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%s", pais);
    while(check!=1)
    {
        printf("Volte a introduzir o pais\n ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%s", pais);
    }
    pais[strlen(pais)]='\0';
    while(i<5)
    {
        minimo=100.0f;
        maximo=-100.0f;
        movingAveragePais(copia->next->next,&maximo,&minimo,pais,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f)
        {
            printf("O max para %d é %f\n",vetoranalise[i],maximo);
            printf("O min para %d é  %f\n",vetoranalise[i],minimo);
            printf("A diferença é %f\n",diferencamax);
        }
        i++;
    }
}
/*  =========================================================
                ANÁLISE POR CIDADE - MOVING AVERAGE
    \param copia: lista  ordenada dos cidades
    \param minficheiro: ano minimo no ficheiro das cidades
    =========================================================*/
void menu1_4_3(UNICODE *copia,float minficheiro)
{
    int vetoranalise[6]={1860,1910,1960,1990,2013};
    int check=0, intervalo=0;
    float minimo=100.0f;
    float maximo=-100.0f;
    float diferencamax=0.0f;
    char cidade[100]={'\0'};
    char buffer[100]={'\0'};
    int i=0;

    printf("Introduza o intervalo que pretenda:\n");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%d", &intervalo);
    while(check!=1 ||intervalo > 12 || intervalo< 1)
    {
        printf("Volte a introduzir o número do inertvalo  [1;12]:");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%d", &intervalo);
    }
    printf("Introduza a cidade para o cálculo: ");
    fgets(buffer, MAX_SIZE, stdin);
    check = sscanf(buffer, "%s", cidade);
    while(check!=1)
    {
        printf("Volte a introduzir o cidade\n ");
        fgets(buffer, MAX_SIZE, stdin);
        check= sscanf(buffer, "%s", cidade);
    }
    cidade[strlen(cidade)]='\0';
    while(i<5)
    {
        minimo=100.0f;
        maximo=-100.0f;
        movingAverage_cidade(copia->next->next,&maximo,&minimo,cidade,minficheiro,intervalo,vetoranalise[i]);
        diferencamax=maximo-minimo;
        if(maximo!=-100.0f && minimo!=100.0f)
        {
            printf("O max para %d é %f\n",vetoranalise[i],maximo);
            printf("O min para %d é  %f\n",vetoranalise[i],minimo);
            printf("A diferença é %f\n",diferencamax);
        }
        i++;
    }


}
/*  =========================================================
            LER OS PARAMETROS DE EXECUÇÃO DO PROGRAMA
    \param argc: número de argumentos introduzidos
    \param argv[]: argumentos introduzidos no terminal na execução do programa
    \param ficheiron1: nome do ficheiro dos paises
    \param ficheiron2: nome do ficheiro das cidades
    \return: retorna 1 caso seja modo gráfico; retorna 0 para modo textual
    =========================================================*/
int obterParametros(int argc,char* argv[], char ficheiro1[],char ficheiro2[])
{
    int fich1 = -1, fich2 = -1;
    int varmodo = -1, erro=0;

    if(argc != 6)
    {
        printf("Parâmetros de inicialização inválidos!!!\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < argc; i++)
    {
        if(strstr(argv[i], "-f1") != NULL)
        {
            fich1 = i; // guarda a posição do '-f1'
                        // sabe que a seguir vai estar o nome do ficheiro1
            erro++;
        }
        if(strstr(argv[i], "-f2") != NULL)
        {
            fich2 = i; // guarda a posição do '-f2'
                        // sabe que a seguir vai estar o nome do ficheiro2
            erro++;
        }
        if((strstr(argv[i], "-g") != NULL) || (strstr(argv[i], "-t") != NULL))
        {
            varmodo = i; // guarda a posição do modo
            erro++;
        }
    }

    if(erro != 3)
    {
        printf("Os argumentos introduzidos não estão corretos!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(ficheiro1, argv[fich1+1]);
    strcpy(ficheiro2, argv[fich2+1]);

    if(strcmp(argv[varmodo], "-g") == 0)
    {
        return 1; // MODO GRÁFICO
    }
    else if (strcmp(argv[varmodo], "-t") == 0)
    {
        return 0; // MODO TEXTUAL
    }
	printf("Erro na introdução dos parametros"); // caso o utilizador não coloque -g nem -t
	exit(EXIT_FAILURE);
    
}


/*  =========================================================
            LEITURA DE DADOS DO FICHEIRO DE PAISES
    \param v_paises: lista dos paises
    \param ficheiro1: ficheiro para os paises
    \param anomax_paises: ano máximo dos paises
    \param anomin_paises: ano minimo dos paises
    =========================================================*/
void leitura_dados_paises(UNICODE *v_paises,char ficheiro1[], int* anomax_paises, int* anomin_paises)
{
    FILE * fp = NULL;
    int check=0;
    char buffer[MAX_SIZE]={'\0'}; // buffer para ler a linha do ficheiro
    UNICODE * vetorLista[2019] = {NULL}; // vetor com apontadores para uma lista. Essa lista contém os dados num dado ano igual à posição no vetor
    dados_temp *vect = NULL; // apontador para estrutura com o conteudo
    char nome[MAX_SIZE]={'\0'};
    int data_ano=0, data_mes=0, data_dia=0;
    float temperatura=0.0f, incerteza=0.0f;
    int _anomax = 0000, _anomin = 5000;
    fp = checkedFile(ficheiro1,"r");

    listvector(vetorLista); // criação de um dummy node para uma estrutura em cada posição do vetor

    while(fgets(buffer,MAX_SIZE,fp)!=NULL)
    {

        check = sscanf(buffer,"%d-%d-%d,%f,%f,%[^\n]",&data_ano,&data_mes,&data_dia,&temperatura,&incerteza,nome);

        if(check==6)
        {
            vect = (dados_temp*) checkedMalloc(sizeof(dados_temp)); // alocar memória para o conteudo da lista
			if(data_ano > _anomax) _anomax = data_ano; // calcular o ano máximo
			if(data_ano < _anomin) _anomin = data_ano; // calcular o ano minimo
			vect->dt.ano = data_ano;
			vect->dt.mes = data_mes;
			vect->dt.dia = data_dia;
			vect->temperatura = temperatura;
			vect->incerteza = incerteza;
			strcpy(vect->pais,nome);
			insert_sorted(vect, vetorLista[vect->dt.ano]); // inserir ordenadamente na lista com dados desse ano
                                                    // a posição 'N' do vetor contem a lista com dados do ano 'N'
        }

    }
    // retornar o ano máximo e o ano minimo para outras funções
    *anomax_paises = _anomax;
    *anomin_paises = _anomin;
    v_paises->next = juntarlista(vetorLista, *anomax_paises, *anomin_paises); // juntar as listas dos diferentes anos
    fclose(fp); 
    
    //para libertar a memória dos dummy nodes das listas de cada posição do vetor
    // não se pretende elimiar a lista inteira porque ela es´ta ligada para formar a lista principal!!!
    for (int i = 0; i < 2019; i++) free(vetorLista[i]);
}


/*  =========================================================
                        CRIAR UMA LISTA
    \return: retorna um ponteiro para o dummy node
    =========================================================*/
UNICODE * create_list ()
{
    dados_temp auxiliar; // conteúdo indiferente para o DAMMY NODE

    return create_node(&auxiliar);
}


/*  =========================================================
                    CRIAR UM NOVO NÓ DA LISTA
    \param _payload: apontador para o conteudo para adicionar ao nó da lista
    \return: retorna um ponteiro para o novo elemento
    =========================================================*/
UNICODE * create_node(dados_temp * _payload)
{
    UNICODE * aux = NULL;

    aux = (UNICODE *) checkedMalloc(sizeof(UNICODE)); // alocar memória para o novo elemento

    aux->next = NULL;
    aux->prev = NULL;
    aux->payload = _payload;
    return aux;
}


/*  =========================================================
                    INSERIR UM NOVO NÓ DA LISTA
    \param _head: apontador para a cabeça da lista
    \param _payload: apontador para o conteudo a adicionar
    =========================================================*/
void insert_node(UNICODE * _head, dados_temp * _payload)
{
    UNICODE *new_node = create_node(_payload); // criar um novo nó

    // fazer as ligações com os outros elementos
    new_node->prev = _head;
    new_node->next = _head->next;
    _head->next =new_node;
    if(new_node->next != NULL)
       new_node->next->prev=new_node;
}


/*  =========================================================
                IMPRIMIR A LISTA DOS PAISES
    \param head: ponteiro para a cabeça da lista a imprimir
    =========================================================*/
void printList(UNICODE * head)
{
    UNICODE * aux = NULL;
    aux = head->next;
    while(aux != NULL)
    {
        printf( "%d-%d-%d,%f,%f,%s\n",aux->payload->dt.ano,aux->payload->dt.mes,
                                      aux->payload->dt.dia,aux->payload->temperatura,
                                      aux->payload->incerteza,aux->payload->pais);
        aux=aux->next;
    }
}


/*  =========================================================
                INSERÇÃO ORDENADA POR DATA
    \param _payload: apontador para o conteudo a inserir na lista
    \param vectList: lista dos paises para inserir o novo nó
    =========================================================*/
void insert_sorted(dados_temp * _payload, UNICODE * vectList)
{
    UNICODE *aux = NULL;
    UNICODE * new_node = create_node(_payload);
    int colocou = 0;
    aux = vectList;
    do
    {
        if(aux->next!= NULL && new_node->payload->dt.mes < aux->next->payload->dt.mes) // se o valor do mes for inferior ao mes do próximo elemento
        {                                                                                // posição certa para colocar!
        
            new_node->prev = aux; // o prv fica igual ao elemento antes do que tem o mês superior
            new_node->next = aux->next; // o next fica a apontar para o elemento com mes superior
            aux->next = new_node; // apontar o prev do novo elemento para o novo elemento
            if(new_node->next != NULL) // caso não esteja no fim da lista
                new_node->next->prev=new_node; // o prev do elemento a seguir fica a apontar para o novo elemento
            colocou = 1; // já colocou o elemento
            return;
        }
     aux=aux->next;
    }while(aux != NULL);

    if(colocou==0) // não colocou o elemento no meio da lista por isso vai inserir na cauda
    {
        new_node = insert_tail(vectList,_payload);
        vectList = new_node;
    }
}


/*  =========================================================
                    INSERIR UM NÓ NA CAUDA
    \param _head: cabeça da lista a inserir o nó
    \param _payload: apontador para o conteúdo a inserir
    \return: retorna um apontador para o elemento que foi adicionado
    =========================================================*/
UNICODE * insert_tail(UNICODE *_head,dados_temp *_payload)
{

    UNICODE *aux = NULL;
    UNICODE *new_elem = NULL;
    new_elem = create_node(_payload);
    if(_head->next==NULL) // se a lista estiver vazia
    { 
        _head->next = new_elem; // apontar a head para o novo elemento
        new_elem->prev = _head; // apontar o prev desse elemento para a head
        new_elem->next = NULL; // o next fica a NULL
        return new_elem;
    }
    aux=_head;
    while(aux->next!=NULL) // encontrar o ultimo elemento
    {
        aux=aux->next;
    }
    aux->next=new_elem; // apontar o último elemento da lista para o novo elemento
    new_elem->prev=aux; // apontar o prev do novo elemento para o último elemento da lista
    return new_elem;
}


/*  =========================================================
                    REMOÇÃO DE UM NÓ DA LISTA
    \param _head: endereço da cabeça da lista
    \return: retorna 0 caso tenha sido removido
    =========================================================*/
int remove_node(UNICODE *_head)
{
    UNICODE *aux = _head;
    if(_head->next != NULL) // caso não seja o último elemento
        _head->next->prev = _head->prev; // colocar o elemento seguinte a apontar para o anterior
    _head->prev->next=_head->next; // colocar o elemento anterior a apontar para ao elemento seguinte
    free(aux->payload); // libertar o conteudo do elemento
    free(aux); // libertar o elemento

    return 0;

}


/*  =========================================================
                ELIMINAÇÃO DE TODA A LISTA
    \param _head: endereço da cabeça da lista
    =========================================================*/
void clearList(UNICODE *_head)
{

    UNICODE *aux = NULL, * tmp = NULL;
    aux = _head->next;
    if(aux == NULL) // lista vazia
    {
        return;
    }
    while(aux != NULL)
    {
        tmp = aux->next;
        if(aux->next != NULL)
        {
            aux->next->prev = aux->prev; // apontar o proximo elemento para o anterior
        }
        aux->prev->next = aux->next;
        free(aux); // libertar o nó
        aux = tmp; // colocar o aux a apontar para o elemento a seguir ao que foi removido
    }
}

/*  =========================================================
    COLOCA EM CADA POSIÇÃO DO VETOR UM APONTADOR PARA O DUMMY NODE DE UMA LISTA QUE VAI SER CRIADA NESTE FUNÇÃO
    \param vetor[2019]: vetor que contém apontadores para uma lista com dados do ano igual à posição no vetor
    =========================================================*/
void listvector(UNICODE *vetor[2019])
{
    int i=0;

    //colocar num vetor cada ano com as linhas desorganizadas e depois organizar
    while(i < 2019)
    {
        vetor[i] = create_list(); // todas as listas têm um dammy node
        i++;
    }
}


/*  =========================================================
    JUNÇÃO DAS LISTAS QUE CONTÉM DADOS DE UM ANO ORGANIZADOS
    \param vetor[2019]: vetor que contém apontadores para uma lista com dados do ano igual à posição no vetor
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    =========================================================*/
UNICODE* juntarlista(UNICODE *vetor[2019], int anomax, int anomin)
{
    int i=0;
    UNICODE *aux=NULL;
    UNICODE *tmp=NULL;
    UNICODE *retorna=NULL;
    int check=0, check1=0;
    for(i = anomin+1; i < anomax + 1; i++)
    {
        if((check==0) && (vetor[i-1] != NULL))
        {
            retorna=vetor[i-1]->next; // valor a retornar para ser o apontador para o inicio da lista
        }
        check = 1;
        
        // encontrar o último elemento da lista anterior ao ano atual
        aux = vetor[i-1];
        while(aux->next != NULL)
        {
            aux = aux->next;
            check1=1;
            tmp = aux;
        }
        if(check1 && vetor[i]->next != NULL)
        {
            if(vetor[i]->next != NULL)//tem dados
            {
                tmp->next = vetor[i]->next; // apontar o últimom elemento da lista do ano anterior par ao primeiro elemento da lista do ano atual
                                            // vetor[i]->next para não contar com o dummy node!!
                vetor[i]->next->prev = tmp; // apontar o elemento do ano atual para o último elemento do ano anterior
            }
            check1=0;
        }
    }
    return retorna;
}


/*  =========================================================
    REMOÇÃO DE NÓS ANTERIORES À DATA DEFINIDA PELO UTILIZADOR
    \param v: lista(dos paises ou das cidades) na qual vão ser removidos os dados que não cumpram os critérios definidos pelo utilizador
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    \param mes: mes definido pelo utilizador
    \param ano: ano definido pelo utilizador
    \return: retorna o apontados para o primeiro elemento da nova lista
    =========================================================*/
UNICODE* limparintervalo(UNICODE **v,int anomax, int anomin, int mes, int ano)
{
    UNICODE *temp=NULL;
    UNICODE *auxiliar = NULL;
    temp = (*v)->next;
    int head=0; // deteta quando encontra o primeiro elemento da restrição que o utilizador definiu


    while(head == 0)
    {
        if(temp->payload->dt.ano>=ano && temp->payload->dt.mes>=mes) // caso o nó esteja no intervalo que o utilizador definiu
        {
            head = 1; // sai do loop
        }
        else // remove tudo o que não satisfaça os critérios impostos pelo utilizador
        {
            remove_node(temp); // remoção do nó
            temp=temp->next; // passagem ao próximo elemento da lista
        }
    }
    auxiliar = temp; // guarda o endereço do primeiro elemento da nova lista
    return auxiliar; // retorna o endereço do primeiro elemento para colocar na lista
}


/*  =========================================================
    REMOÇÃO DE NÓS QUE NÃO ESTEJAM ENTRE OS MESES DEFINIDOS PELO UTILIZADOR
    \param v: lista(dos paises ou das cidades) na qual vão ser removidos os dados que não cumpram os critérios definidos pelo utilizador
    \param anomax: ano maximo do vetor de listas
    \param anomin: ano minimo do vetor de listas
    \param mesinicial: mes inicial definido pelo utilizador
    \param mesfinal: mes final defnio pelo utilizador
    \return: retorna o apontador para o inicio da nova lista
    =========================================================*/
UNICODE * limpaMeses(UNICODE **v, int anomax, int anomin, int mesinicial, int mesfinal)
{
    UNICODE * aux = (*v)->next;
    UNICODE * retorna = NULL;
	int check = 0;
    int anosDiferentes = (mesinicial>mesfinal ? 1 : 0);
    

    if(anosDiferentes == 0) // os meses pertencem ao mesmo ano, ou seja não é necessário mudar de ano
    {
        while(aux != NULL)
        {
            if((aux->payload->dt.mes >= mesinicial && aux->payload->dt.mes <= mesfinal) && aux->next != NULL)
            {
                if(check == 0)
                {
					retorna = aux; // guarda o endereço do primeiro elemento que cumpre os requesitos para retornar
					check = 1; // não volta a guardar mais nenhum endereço
				}
                aux = aux->next;
            }
            else
            {
                remove_node(aux); // remoção de tudo o que não satisfaça os critérios definidos
                aux = aux->next;
            }
        }
    }
    else if(anosDiferentes == 1) // os meses pertencem a anos diferentes. Por exemplo mesfinal = 2, mesinicial = 10
    {
        while(aux != NULL)
        {
            if((aux->payload->dt.mes >= mesinicial || aux->payload->dt.mes <= mesfinal) && aux->next != NULL)
            {
                if(check == 0)
                {
					retorna = aux; // guarda o endereço do primeiro elemento que cumpre os requesitos para retornar
					check = 1; // não volta a guardar mais nenhum endereço
				}
				aux = aux->next;
            }
            else
            {
                remove_node(aux); // remoção de tudo o que não satisfaça os critérios definidos
                aux = aux->next;
            }
        }
    }
    return retorna; //retorno do endereço do primeiro valor da lista

}

/*  =========================================================
    LEITURA DO FICHEIRO DAS CIDADES
    \param v_cidades: lista das cidades
    \param ficheiro2: nome do ficheiro das cidades
    \param anomax_cidades: ano maximo das cidades para retornar para outras funções
    \param anomin_cidades: ano minimo das cidades para retornar para outras funções
    =========================================================*/
void leitura_dados_cidades(UNICODE *v_cidades,char ficheiro2[], int *anomax_cidades, int *anomin_cidades)
{
    FILE * fp = NULL;
    dados_temp * payload;
    UNICODE * vetorLista[2019] = {NULL};

    char buffer[MAX_SIZE];
    char pais[MAX_SIZE];
    char cidade[MAX_SIZE];
    int ano = 0, mes = 0, dia = 0, check = 0, anomax = 0000, anomin = 5000;
    float temperatura = 0.0f, incerteza = 0.0f, nlatitude = 0.0f, nlongitude = 0.0f; 
    char clongitude = 0, clatitude = 0;
    char *lixo = NULL;
    fp = checkedFile(ficheiro2, "r");
    
    // criar um dummy node de uma lista para cada posição do vetor
    listvector(vetorLista);

    while( fgets(buffer, MAX_SIZE, fp) != NULL)
    {
        check = sscanf(buffer, "%d-%d-%d,%f,%f,%[^,],%[^,],%f%c,%f%c%[^\n]",&ano, &mes, &dia,
                &temperatura, &incerteza, cidade, pais, &nlatitude,
                &clatitude, &nlongitude, &clongitude, lixo );
        
        if(check == 11)
        {
            payload = (dados_temp *) checkedMalloc(sizeof(dados_temp));
			if(ano > anomax) anomax = ano; // cálculo do ano máximo
			if(ano < anomin) anomin = ano; // cálculo do ano minimo
			payload->dt.ano = ano;
			payload->dt.mes = mes;
			payload->dt.dia = dia;
			payload->temperatura = temperatura;
			payload->incerteza = incerteza;
			strcpy(payload->pais, pais);
			strcpy(payload->cidade, cidade);
			payload->latitude.angular = nlatitude;
			payload->longitude.angular = nlongitude;
			payload->latitude.direcao = (strcmp(&clatitude, "N") == 0 ? NORTE : SUL);
			payload->longitude.direcao = (strcmp(&clongitude, "W") == 0 ? OESTE : ESTE);
			insert_sorted(payload, vetorLista[payload->dt.ano]); // inserir ordenadamente na lista corresponde ao ano da linha lida
        }
    }
    // calculo do ano maximo e minimo para retornar para outras funções
    *anomax_cidades = anomax;
    *anomin_cidades = anomin;
    v_cidades->next = juntarlista(vetorLista, *anomax_cidades, *anomin_cidades); // juntar as listas correspondentes a cada ano
    fclose(fp);

    //para libertar a memória dos dummy nodes das listas de cada posição do vetor
    // não se pretende elimiar a lista inteira porque ela está ligada para formar a lista principal!!!
    for (int i = 0; i < 2019; i++) free(vetorLista[i]);
}


/*  =========================================================
                IMPRIMIR A LISTA DAS CIDADES
    \param head: ponteiro para a cabeça da lista a imprimir
    =========================================================*/
void printListCidades(UNICODE * head)
{
    UNICODE * aux = head->next;
    while(aux != NULL)
    {
        printf("%d-%d-%d,%f,%f,%s,%s,%f %d,%f %d\n",aux->payload->dt.ano, aux->payload->dt.mes, aux->payload->dt.dia,
        aux->payload->temperatura, aux->payload->incerteza, aux->payload->cidade, aux->payload->pais,
        aux->payload->latitude.angular, aux->payload->latitude.direcao, aux->payload->longitude.angular,
        aux->payload->longitude.direcao);
        aux = aux->next;
    }
}


/*  =========================================================
        FUNÇÃO QUE FAZ MALLOC E REALIZA A VERIFICAÇÃO
    \param size: tamanho da memória a alocar
    \return: retorna um ponteiro para esse espaço de memória alocado
    =========================================================*/
void * checkedMalloc(size_t size)
{
	void *mem = malloc(size);
    if(mem == NULL)
    {
        printf("Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return mem;
}


/*  =========================================================
        FUNÇÃO QUE ABRE UM FICHEIRO E RETORNA UM APONTADOR PARA O MESMO.
        FAZ A VERIFICAÇÃO DE VALIDADE DE ABERTURA
    \param fich: nome do ficheiro
    \param modo: modo de abertura do ficheiro: "r", "w", ...
    \return: retorna um ponteiro para o ficheiro aberto
    =========================================================*/
FILE * checkedFile(char * fich, char * modo)
{
	FILE * aux = fopen(fich, modo);
	if (aux == NULL)
	{
		printf("Falha na abertura do ficheiro %s\n", fich);
		exit(EXIT_FAILURE);
	}
	return aux;
}




/*  =========================================================
    Função que faz a análise da temperatura de uma determinado ano do ficheiro paises
    \param copia: lista dos paises
    \param numeropaises: O intervalo que o utilizador deseja
    \param ano: Contém o ano de análise
    =========================================================*/

void analise_da_temperatura_ano_pais(UNICODE *copia,int numeropaises,int ano)
{
    int i=0;
    int numerodeelementos=0;
    UNICODE *vetor[2019]={NULL};
    Paises *vetorpaises[1000];
    Amplitude *ampvetorpaises[1000]={NULL};
    Paises *vetorfinal[20]={NULL};
    Paises *vetormin[20]={NULL};
    Amplitude *vetoramp[20]={NULL};
    UNICODE *vetoraux[2019]={NULL};

    listvector(vetor);
    listvector(vetoraux);

    organizapaises(copia,&numerodeelementos,ano,vetor);
    organizapaises(copia,&numerodeelementos,ano,vetoraux);
    calculamedia(vetor,numerodeelementos,vetorpaises);
    calculaamplitude(vetoraux,numerodeelementos,ampvetorpaises);
    insertcountries(vetorpaises,vetorfinal,numerodeelementos,numeropaises);
    insertcountriesminimo(vetorpaises,vetormin,numerodeelementos,numeropaises);
    insertcountriesAmplitude(ampvetorpaises,vetoramp,numerodeelementos,numeropaises);

    printf("----------MAXIMO---------\n");

    while(i<numeropaises)
    {
        printf(" Com a temperatura maxima media %f é %s \n",vetorfinal[i]->media,vetorfinal[i]->pais);
        i++;
    }
    i=0;
    printf("----------MINIMO---------\n");
    while(i<numeropaises)
    {
        printf(" Com a temperatura minima media %f é %s \n",vetormin[i]->media,vetormin[i]->pais);
        i++;
    }

    i=0;
    printf("----------AMPLITUDE---------\n");
    while(i<numeropaises)
    {
        printf(" Com a maior amplitude media %s é %f \n",vetoramp[i]->pais, vetoramp[i]->dif);
        i++;
    }
}



/*  =========================================================
    Função que coloca os paises com maior amplitude num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a amplitude e e o nome de todos os paises
    \param vetorfinal:vetor que contém os paises com maior amplitude
    \param numerodedados:O número de paises
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcountriesAmplitude(Amplitude *vetor[1000],Amplitude *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)//percorro todos os paises de analise
    {
        for(int j=0;j<numeroinserido;j++)//Para o intervalo que o utilizador defeniu,passo para um vetor ordenado por amplitude
        {                               // para cada pais percorro o meu vetor todo 
            if(vetorfinal[j]==NULL)//caso não esteja lá nada,coloco
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if((vetor[i]->dif) > vetorfinal[j]->dif)// Se a diferença for menor no meu vetor final,movo todas as posições seguintes para baixo e coloco o novo valor
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }

        }
    }
}




/*  =========================================================
    Função que calcula a amplitude de cada pais que foi colocado no vetor
    \param vetor: vetor de listas que contém em cada posição uma apontador para uma lista com informação de um pais
    \param numerodedados: O numero de paises
    \param vetorpaises: vetor de estruturas que contém a amplitude e nome de cada pais
    =========================================================*/
void calculaamplitude(UNICODE *vetor[2019], int numerodedados,Amplitude *vetorpaises[1000])
{
    float maximo = -10.0f, minimo = 100.0f, diferenca = 0.0f;
    int i=0, check = 1;
    Amplitude *auxv = NULL;

    while(i<numerodedados)
    {
        maximo = -10.0f;
        minimo = 100.0f;
        diferenca = 0.0f;
        check = 0;
        while(vetor[i]->next != NULL)// para cada pais, encontro o maximo e o minimo,para fazer a diferença
        {
            auxv=(Amplitude*)realloc(vetorpaises[i],(i+1)*sizeof(Amplitude));
            vetorpaises[i]=auxv;
            if(vetor[i]->next->payload->temperatura > maximo)
            {
                maximo=vetor[i]->next->payload->temperatura;
            }
            if(vetor[i]->next->payload->temperatura<minimo)
            {
                minimo=vetor[i]->next->payload->temperatura;
            }
            vetor[i]=vetor[i]->next;
            check=1;
        }
        if(check==1)
        {
            diferenca=((maximo-minimo)*2)/2;//para o valor ficar positivo
            vetorpaises[i]->dif=diferenca;
            strcpy(vetorpaises[i]->pais,vetor[i]->payload->pais);
        }
        i++;
   }
}



/*  =========================================================
    Função que coloca os paises com menor temp num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a media e e o nome de todos os paises
    \param vetorfinal:vetor que contém os paises com menor temp
    \param numerodedados:O número de paises
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcountriesminimo(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)//percorro todos os paises
    {
        for(int j=0;j<numeroinserido;j++)//percorro todas as posições do meu vatorfinal
        {
            if(vetorfinal[j]==NULL)//se no meu vetor final não estiver lá nada,coloco
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media < vetorfinal[j]->media)// se a dif do meu vetorfinal for menor,movo todos os dados seguintes 1 casa para baixo e coloco o valor novo
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}




/*  =========================================================
    Função que coloca num vetor de listas a informação de cada cidade
    \param vetor: vetor de estruturas que contém a amplitude e e o nome de todos as cidades
    \param numerocidades:contém o número de cidades
    \param ano: O ano a analisar
    \param copia: lista com a informação do ficheiro ordenada
    =========================================================*/
void organizacidades(UNICODE *copia, int *numerocidades,int ano,UNICODE *vetor[2019])
{
    int numerodeelementos=0, i=0;
    dados_temp *vect[2000];
    while(copia->payload->dt.ano != ano)
    {
        copia=copia->next;
    }

    do
    {
        i=0;
        while( i<200)
        {
            if(vetor[i]->next==NULL)// Se o meu vetor tiver vazio na posição i,coloco o conteudo de um pais
            {
                vect[i] = (copia->payload);
                insert_node(vetor[i],vect[i]);
                break;
            }
            else if(strstr(copia->payload->cidade,vetor[i]->next->payload->cidade)!=NULL)// caso tenha conteudo e se for pais da posição que estou a analisar                              
            {//Coloco na lista desse pais
                    vect[i] = (copia->payload);
                    insert_node(vetor[i],vect[i]);
                    break;
            }

            i++;
        }
        copia=copia->next;
    }
    while( copia!=NULL && copia->payload->dt.ano==ano);
    i=0;
    do
    {
        if(vetor[i]->next->next!=NULL)
        {
            numerodeelementos++;
        }
        i++;
    }
    while(vetor[i]->next!=NULL);
    *numerocidades=numerodeelementos;
}



/*  =========================================================
    Função que coloca num vetor de listas a informação de cada pais
    \param vetor: vetor de estruturas que contém a amplitude e e o nome de todos os paises
    \param numerocidades:contém o número de paises
    \param ano: O ano a analisar
    \param copia: lista com a informação do ficheiro ordenada
    =========================================================*/
void organizapaises(UNICODE *copia, int *numeropaises,int ano,UNICODE *vetor[2019])
{

    int numerodeelementos=0;
    int i=0;
    dados_temp *vect[2000];
    UNICODE *aux=NULL;
    aux=copia;

    while(copia->next->payload->dt.ano != ano)
    {
        copia=copia->next;
        if(copia->next==NULL)
        {
            return;
        }
    }

    do
    {
        i=0;
        while( i<500)
        {
            if(vetor[i]->next==NULL)
            {
                vect[i] = (copia->payload);
                insert_node(vetor[i],vect[i]);
                break;
            }
            else if(strstr(copia->payload->pais,vetor[i]->next->payload->pais)!=NULL)
            {
                vect[i] = (copia->payload);
                insert_node(vetor[i],vect[i]);
                break;
            }

            i++;
        }
        copia=copia->next;
    }
    while( copia!=NULL && copia->payload->dt.ano==ano);
    i=0;
    do
    {
        if(vetor[i]->next->next!=NULL)
        {
            numerodeelementos++;
        }

        i++;
    }
    while(vetor[i]->next!=NULL);
    *numeropaises=numerodeelementos;
    copia=aux;

}



/*  =========================================================
    Função que calcula a amplitude de cada pais que foi colocado no vetor
    \param vetor: vetor de listas que contém em cada posição uma apontador para uma lista com informação de um pais
    \param numerodedados: O numero de paises
    \param vetorpaises: vetor de estruturas que contém a media e nome de cada pais
    =========================================================*/
void calculamedia(UNICODE *vetor[2019], int numerodedados,Paises *vetorpaises[1000])
{
    float soma=0;
    int i=0, numerodeinfo=0;
    Paises *auxv=NULL;

    while(i<numerodedados)
    {
        numerodeinfo=0;
        soma=0;
        while(vetor[i]->next!=NULL)
        {
            auxv=(Paises*)realloc(vetorpaises[i],(i+1)*sizeof(Paises));
            vetorpaises[i]=auxv;
            soma+=vetor[i]->next->payload->temperatura;
            numerodeinfo++;
            vetor[i]=vetor[i]->next;
        }
        vetorpaises[i]->media=soma/numerodeinfo;
        strcpy(vetorpaises[i]->pais,vetor[i]->payload->pais);
        i++;
    }
}



/*  =========================================================
    Função que coloca os paises com menor temp num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a amplitude e e o nome de todos os paises
    \param vetorfinal:vetor que contém os paises com maior temp
    \param numerodedados:O número de paises
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcountries(Paises *vetor[1000],Paises *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media > vetorfinal[j]->media)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}



/*  =========================================================
    Função que faz a análise da temperatura de uma determinado ano do ficheiro cidades
    \param copia: lista das cidades
    \param numerocidades: O intervalo que o utilizador deseja
    \param ano: Contém o ano de análise
    =========================================================*/
void analise_da_temperatura_ano_cidade(UNICODE *copia,int numerocidades,int ano)
{
    int i=0, numerodeelementos=0;
    UNICODE *vetor[2019]={NULL};
    UNICODE *vetoraux[2019]={NULL};
    cidades *vetorcidades[1000];
    AmpCidades *ampvetorcidades[1000]={NULL};
    cidades *vetorfinal[20]={NULL};
    cidades *vetormin[20]={NULL};
    AmpCidades *vetoramp[20]={NULL};

    listvector(vetor);
    listvector(vetoraux);
    organizacidades(copia,&numerodeelementos,ano,vetor);
    organizacidades(copia,&numerodeelementos,ano,vetoraux);
    calculamediacidades(vetor,numerodeelementos,vetorcidades);
    calculaamplitudeCidades(vetoraux,numerodeelementos,ampvetorcidades);
    insertcidade(vetorcidades,vetorfinal,numerodeelementos,numerocidades);
    insertcountriesminimocidade(vetorcidades,vetormin,numerodeelementos,numerocidades);
    insertcountriesAmplitudeCidades(ampvetorcidades,vetoramp,numerodeelementos,numerocidades);

    printf("----------MAXIMO---------\n");

    while(i<numerocidades){
        printf(" Com a temperatura maxima media %f é %s \n",vetorfinal[i]->media,vetorfinal[i]->cidade);
        i++;
    }
    i=0;
    printf("----------MINIMO---------\n");
    while(i<numerocidades){
        printf(" Com a temperatura minima media %f é %s \n",vetormin[i]->media,vetormin[i]->cidade);
        i++;
    }

    i=0;
    printf("----------AMPLITUDE---------\n");
    while(i<numerocidades){
        printf(" Com a maior amplitude media %s é %f \n",vetoramp[i]->cidade, vetoramp[i]->dif);
        i++;
    }
}



/*  =========================================================
    Função que coloca os paises com menor temp num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a media e e o nome de todos os paises
    \param vetorfinal:vetor que contém as cidades com maior temp
    \param numerodedados:O número de cidades
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media > vetorfinal[j]->media)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}



/*  =========================================================
    Função que coloca os paises com menor temp num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a media e e o nome de todos os paises
    \param vetorfinal:vetor que contém as cidades com menor temp
    \param numerodedados:O número de cidades
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcountriesminimocidade(cidades *vetor[1000],cidades *vetorfinal[20],int numerodedados,int numeroinserido){
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if(vetor[i]->media < vetorfinal[j]->media)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}



/*  =========================================================
    Função que calcula a amplitude de cada cidade que foi colocado no vetor
    \param vetor: vetor de listas que contém em cada posição uma apontador para uma lista com informação de uma cidade
    \param numerodedados: O numero de cidades
    \param vetorcidades: vetor de estruturas que contém a amplitude e nome de cada cidade
    =========================================================*/
void calculaamplitudeCidades(UNICODE *vetor[2019], int numerodedados,AmpCidades *vetorcidades[1000])
{

    float maximo=-10.0f, minimo=100.0f, diferenca=0.0f;
    int i=0, check=1;
    AmpCidades *auxv=NULL;

   while(i<numerodedados)
   {
        maximo=-10.0f;
        minimo=100.0f;
        diferenca=0.0f;
        check=0;
        while(vetor[i]->next!=NULL)
        {
            auxv=(AmpCidades*)realloc(vetorcidades[i],(i+1)*sizeof(AmpCidades));
            vetorcidades[i]=auxv;
            if(vetor[i]->next->payload->temperatura > maximo)
            {
                maximo=vetor[i]->next->payload->temperatura;
            }
            if(vetor[i]->next->payload->temperatura<minimo)
            {
                minimo=vetor[i]->next->payload->temperatura;
            }
            vetor[i]=vetor[i]->next;
            check=1;
        }
        if(check==1)
        {
            diferenca=((maximo-minimo)*2)/2;//para ser positivo
            vetorcidades[i]->dif=diferenca;
            strcpy(vetorcidades[i]->cidade,vetor[i]->payload->cidade);
        }
        i++;
    }
}



/*  =========================================================
    Função que coloca as cidades com maior amplitude de temp num vetor de forma ordenada
    \param vetor: vetor de estruturas que contém a amplitude e e o nome de todos as cidades
    \param vetorfinal:vetor que contém as cidades com maior amplitude
    \param numerodedados:O número de cidades
    \param numeroinserido: O intervalo que desejo
    =========================================================*/
void insertcountriesAmplitudeCidades(AmpCidades *vetor[1000],AmpCidades *vetorfinal[20],int numerodedados,int numeroinserido)
{
    for(int i=0;i<numerodedados;i++)
    {
        for(int j=0;j<numeroinserido;j++)
        {
            if(vetorfinal[j]==NULL)
            {
                vetorfinal[j]=vetor[i];
                break;
            }
            if((vetor[i]->dif) > vetorfinal[j]->dif)
            {
                for(int k=numeroinserido-2;k>=j;k--)
                {
                    vetorfinal[k+1]=vetorfinal[k];
                    vetorfinal[k]=vetorfinal[k-1];
                }
                vetorfinal[j]=vetor[i];
                break;
            }
        }
    }
}



/*  =========================================================
    Função que calcula a media de cada cidade que foi colocado no vetor
    \param vetor: vetor de listas que contém em cada posição uma apontador para uma lista com informação de uma cidade
    \param numerodedados: O numero de cidades
    \param vetorpaises: vetor de estruturas que contém a media e nome de cada cidade
    =========================================================*/
void calculamediacidades(UNICODE *vetor[2019], int numerodedados,cidades *vetorcidades[1000])
{

    float soma=0;
    int i=0;
    int numerodeinfo=0;
    cidades *auxv=NULL;

   while(i<numerodedados)
    {
        numerodeinfo=0;
        soma=0;
        while(vetor[i]->next!=NULL)
        {
            auxv=(cidades*)realloc(vetorcidades[i],(i+1)*sizeof(cidades));
            vetorcidades[i]=auxv;
            soma+=vetor[i]->next->payload->temperatura;
            numerodeinfo++;
            vetor[i]=vetor[i]->next;
        }
        vetorcidades[i]->media=soma/numerodeinfo;
        strcpy(vetorcidades[i]->cidade,vetor[i]->payload->cidade);
        i++;
    }
}



/*  =========================================================
    Função que calcula o Moving average para um pais
    \param copia: lista normal dos paises
    \param max: Temp maximo do Moving Average
    \param min:Temp minimo do Moving Average
    \param pais:Pais em análise
    \param minficheiro:o ao minimo do ficheiro
    \param intervalo:intervalo de meses que o utilizador deseja
    \param ano: O ano de analise, pode ser 1860,1910,1960,1990,2013
    =========================================================*/

void movingAveragePais(UNICODE *copia,float *max,float *min,char pais[100],float minficheiro,int intervalo, int ano)
{

    int i=1743;
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    UNICODE *listapaises=create_list();// crio um lista com dummy node que vai conter a informação nesse ano
    int check=0;


    while(i<=ano)
    {
        check=0;
        Ledadospais(copia,pais,listapaises,i,&check);// restringe a minha informação só às linhas que têm o ficheiro que desejo
        if(check==1) // só entra caso nesse ano tenha informação desse pais
        {
            calculamediaparacadames(listapaises,media_mes);
            criaagrupamentos(media_mes,intervalo,&media_ano);
            if(*max<media_ano)
            {
                *max=media_ano;
            }
            if(*min>media_ano)
            {
                *min=media_ano;
            }
            clearList(listapaises);// limpa a minha lista auxiliar para a usar outra vez
            media_ano=0.0f;
        }
    i++;// caso ele encontre um sem dados
    }
}



/*  =========================================================
    Função que calcula a media de cada mes na lista de paises
    \param vetor: contém a lista de paises que estamos a analisar
    \param media_mes: contém a media para cada mes
    =========================================================*/
void calculamediaparacadames(UNICODE *vetor,float media_mes[13])
{
    float soma=0.0f;
    int i=1;
    int numerodeinfo=0;
    UNICODE *aux=vetor;

    while(aux->next!=NULL && i<13)
    {
        numerodeinfo=0;
        soma=0.0f;
        while(aux->next!=NULL && aux->next->payload->dt.mes!=i)
        {
            i++;
            if( i==13)//caso não tenha informação,vou sair da função
            {
                return;
            }
        }
        while(aux->next!=NULL && aux->next->payload->dt.mes==i)
        {
            soma+=aux->next->payload->temperatura;
            numerodeinfo++;
            aux=aux->next;
        }

        if(aux!=NULL && soma!=0.0f)
        {
            if(aux->next!=NULL && aux->next->payload->dt.mes==i)
            {
                soma+=aux->next->payload->temperatura;
                numerodeinfo++;
            }
            if(soma!=0.0f)
            {
                media_mes[i-1]=soma/numerodeinfo;
            }
        }
        while(aux->next!=NULL && aux->next->payload->dt.mes!=i) // para evitar erros entre meses sem informação
        {
                i++;
                if( i==13){
                    return;
                }
        }
        if(aux==NULL){
            break;
        }
    }
}



/*  =========================================================
    Função que a partir da media de cada mês faz a media dos agrupamentos para os paises
    \param media_mes: contém a media para cada mes
    \param intervalo:O intervalo de meses que o utilizador define
    \param media_do_ano: contém a media final do Moving average para aquele ano
    =========================================================*/
void criaagrupamentos(float media_mes[13],int intervalo, float *media_do_ano)
{
    int k,j=1;
    int i=0;
    float somatemp=0.0f;
    float somaagrupamentos=0.0f;
    int numerodeinfo,numagrupamentos=0,p=0;
    float media_agrupamentos[13]={0.0f};
    while(j<13)
    {
        somatemp=0.0f;
        numerodeinfo=0;
        for(k=j;k<j+intervalo && k!=13 ;k++)
        {
            somatemp+=media_mes[k-1];
            if(media_mes[k-1]!=0.0f)
            {
                numerodeinfo++;
            }
        }
        if(somatemp!=0.0f)
        {
            media_agrupamentos[j-1]=somatemp/numerodeinfo; //media do agrupamento
        }
        j++;
    }
    while(i<12)
    {
        somaagrupamentos+=media_agrupamentos[i];
        if(media_agrupamentos[i]!=0.0f)
        {
            numagrupamentos++;
        }
        i++;
    }
    *media_do_ano=somaagrupamentos/numagrupamentos;
    while(media_mes[p]!=0.0f)
    {
        media_mes[p]=0.0f;
        p++;
    }
}




/*  =========================================================
    Função que restringe a minha informação apenas às linhas que relacionadas com o pais a analisar
    \param v: lista das cidades
    \param listapais:Nova lista com a informação pretendida
    \param ano: contém o ano que pretendo analisar
    \param check:serve paraa verificar que de facto existem dados nesse ano para esse pais
    =========================================================*/

void Ledadospais(UNICODE *v,char pais[100],UNICODE *listapais, int ano, int *check)
{
    UNICODE *aux=v;
    dados_temp *vect[2000];
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano)
    {
        aux=aux->next;
    }
    while(aux!=NULL && aux->payload->dt.ano==ano)
    {
        if(strstr(aux->payload->pais,pais)!=NULL)// se a linha que estou a analisar foi do pais que o utilizador definiu,então guardo na minha lista
        {
            vect[i]= (aux->payload);
            insert_tail(listapais,vect[i]);
            i++;
            *check=1;
        }
        aux=aux->next;
    }
}



/*  =========================================================
    Função que calcula o Moving average para uma cidade
    \param copia: lista normal das cidades
    \param max: Temp maximo do Moving Average
    \param min:Temp minimo do Moving Average
    \param pais:Cidade em análise
    \param minficheiro:o ao minimo do ficheiro
    \param intervalo:intervalo de meses que o utilizador deseja
    \param ano: O ano de analise, pode ser 1860,1910,1960,1990,2013
    =========================================================*/
void movingAverage_cidade(UNICODE *copia,float *max,float *min,char cidade[100],float minficheiro,int intervalo, int ano)
{

    int i=1743;
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    UNICODE *listacidades=create_list(); // crio um lista com dummy node que vai conter a informação nesse ano
    int check=0;

    while(i<=ano)
    {
        check=0;
        Ledadoscidades(copia,cidade,listacidades,i,&check);
        if(check==1) // restringe a minha informação só às linhas que têm o ficheiro que desejo
        {
            calculamediaparacadames(listacidades,media_mes); 
            criaagrupamentos_cidades(media_mes,intervalo,&media_ano);
            if(*max<media_ano)
            {
                *max=media_ano;
            }
            if(*min>media_ano)
            {
                *min=media_ano;
            }
            clearList(listacidades); // limpa a minha lista auxiliar para a usar outra vez
            media_ano=0.0f;
        }
        i++; // caso ele encontre um sem dados
    }
}





/*  =========================================================
    Função que a partir da media de cada mês faz a media dos agrupamentos para as cidades
    \param media_mes: contém a media para cada mes
    \param intervalo:O intervalo de meses que o utilizador define
    \param media_do_ano: contém a media final do Moving average para aquele ano
    =========================================================*/
void criaagrupamentos_cidades(float media_mes[13],int intervalo, float *media_do_ano)
{
    int k,j=1, i=0;
    float somatemp=0.0f;
    float somaagrupamentos=0.0f;
    int numerodeinfo=0,numagrupamentos=0,p=0;
    float media_agrupamentos[13]={0.0f};
    while(j<13)
    {
        somatemp=0.0f;
        numerodeinfo=0;
        for(k=j;k<j+intervalo && k!=13 ;k++) // divide os meses em intervalos que o utilizador definiu
        {
                somatemp+=media_mes[k-1];

                if(media_mes[k-1]!=0.0f) // só conta se existirem valores para esse mes
                {
                    numerodeinfo++;
                }
        }
        if(somatemp!=0.0f)
        {
            media_agrupamentos[j-1]=somatemp/numerodeinfo; //media do agrupamento
        }
        j++;
    }
    while(i<12)
    {
        somaagrupamentos+=media_agrupamentos[i];
        if(media_agrupamentos[i]!=0.0f)
        {
            numagrupamentos++;
        }
        i++;
    }
    *media_do_ano=somaagrupamentos/numagrupamentos;
    while(media_mes[p]!=0.0f)
    {
        media_mes[p]=0.0f;
        p++;
    }
}






/*  =========================================================
    Função que restringe a minha informação apenas às linhas que relacionadas com a cidade a analisar
    \param v: lista das cidades
    \param listacidade:Nova lista com a informação pretendida
    \param ano: contém o ano que pretendo analisar
    \param check:serve paraa verificar que de facto existem dados nesse ano para essa cidade
    =========================================================*/

void Ledadoscidades(UNICODE *v,char cidade[100],UNICODE *listacidade, int ano, int *check)
{
    UNICODE *aux=v;
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano)
    {
        aux=aux->next;
    }

    while(aux!=NULL && aux->payload->dt.ano==ano)
    {
        if(strstr(aux->payload->cidade,cidade)!=NULL)
        {
            insert_tail(listacidade,aux->payload);
            i++;
            *check=1;
        }
        aux=aux->next;
    }
}

/*  =========================================================
    Função que calcula o Moving average Global
    \param copia: lista normal dos paises
    \param max: Temp maximo do Moving Average
    \param min:Temp minimo do Moving Average
    \param minficheiro:o ao minimo do ficheiro
    \param intervalo:intervalo de meses que o utilizador deseja
    \param ano: O ano de analise, pode ser 1860,1910,1960,1990,2013
    =========================================================*/

void movingAverageG(UNICODE *copia,float *max,float *min,float minficheiro,int intervalo, int ano)
{

    int i=1743;
    float media_ano=0.0f;
    float media_mes[13]={0.0f};
    UNICODE *listaGlobal=create_list(); // crio um lista com dummy node que vai conter a informação nesse ano
    int check=0;

    while(i<=ano)
    {
        check=0;
        LedadosG(copia,listaGlobal,i,&check);
        if(check==1) // restringe a minha informação só às linhas que têm o ficheiro que desejo
        {
            calculamediaparacadames(listaGlobal,media_mes);
            criaagrupamentos(media_mes,intervalo,&media_ano);
            if(*max<media_ano)
            {
                *max=media_ano;
            }
            if(*min>media_ano)
            {
                *min=media_ano;
            }
            clearList(listaGlobal);
            media_ano=0.0f;
        }
        i++; // caso ele encontre um sem dados
    }
}


/*  =========================================================
    Função que restringe a minha informação apenas ao ano que quero analisar
    \param v: lista dos paises
    \param lista:Nova lista com a informação pretendida
    \param ano: contém o ano que pretendo analisar
    \param check:serve paraa verificar que de facto existem dados nesse ano para essa cidade
    =========================================================*/

void LedadosG(UNICODE *v,UNICODE *lista, int ano, int *check)
{
    UNICODE *aux=v;
    int i=0;
    while(aux!=NULL && aux->payload->dt.ano!=ano)
    {
        aux=aux->next;
    }

    while(aux!=NULL && aux->payload->dt.ano==ano)
    {
        insert_tail(lista,aux->payload);
        i++;
        *check=1;
        aux=aux->next;
    }
}
