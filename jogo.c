#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
    int destreza;
    int carisma;
    int magia;
} PERS;

int facilita(char *hab, int *pontos, PERS personagem);
void distribuir(int pontos, PERS *personagem);


int main()
{
    srand(time(NULL));
    FILE *inicio;
    char inicio1[200];
    int digito;
    int pontos = 100;
    int numaleatorio;
    inicio = fopen("D:\\vscodeC\\proj\\jogo\\teste.txt", "r");
    while(!feof(inicio)){
        fgets(inicio1, 199, inicio);
        printf("%s", inicio1);
    }
    fclose(inicio);
    
    scanf("%d", &digito);
    if(digito == 1){
        PERS personagem = {0};
        char nome[40];
        printf("Digite o nome do seu personagem: ");
        fgets(nome, 39, stdin);    //scanf("%s", personagem.nome);
        strcpy(personagem.nome, nome);
        distribuir(pontos, &personagem);
        //personagem.forca = numaleatorio;
        printf("%s %d %d %d %d %d", personagem.nome, personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.carisma);
    }
    
    return 0;
}

void distribuir(int pontos, PERS *personagem){
    printf("Voce tem %d pontos. Distribua-os da maneira que quiser\n", pontos);
    int pontos2 = pontos;
    char forca[10] = "forca";
    char defesa[10] = "defesa";
    char magia[10] = "magia";
    char folego[10] = "folego";
    char destreza[] = "destreza";
    char carisma[10] = "carisma";
    personagem->forca = facilita(forca, &pontos2, *personagem);
    personagem->defesa = facilita(defesa, &pontos2, *personagem);
    personagem->magia = facilita(magia, &pontos2, *personagem);
    personagem->folego = facilita(folego, &pontos2, *personagem);
    personagem->destreza = facilita(destreza, &pontos2, *personagem);
    personagem->carisma = facilita(carisma, &pontos2, *personagem);


}

int facilita(char *hab, int *pontos, PERS personagem){

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.carisma);
    printf("\n");
    int x;
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de %s a seguir: ", *pontos, hab);
        scanf("%d", &x);
        if(x > *pontos || x < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    *pontos = *pontos - x;
    return x;


}
