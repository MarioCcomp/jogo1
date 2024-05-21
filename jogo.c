#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _dano{
    char descricao[80];
    int valor;
}DANO;


typedef struct _personagem{
    char nome[40];
    int forca;
    int danosasofrer[20];
    int defesa;
    int folego;
    int inventario[3];
    int vida;
    int carisma;
    int magia;
} PERS;


int main()
{
    srand(time(NULL));
    FILE *inicio;
    char inicio1[100];
    int digito;
    int numaleatorio;
    inicio = fopen("D:\\vscodeC\\proj\\jogo\\teste.txt", "r");
    while(!feof(inicio)){
        fgets(inicio1, 100, inicio);
        printf("%s", inicio1);
    }
    scanf("%d", &digito);
    if(digito == 1){
        PERS personagem;
        printf("Digite o nome do seu personagem: ");
        fgets(personagem.nome, 39, stdin);
        fgets(personagem.nome, 39, stdin);
        numaleatorio = ((rand() % 30) + 1);
        personagem.forca = numaleatorio;
        printf("%s %d", personagem.nome, personagem.forca);
    }
    
    return 0;
}