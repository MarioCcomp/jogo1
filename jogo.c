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
        printf("Digite o nome do seu personagem: ");
        scanf("%s", personagem.nome);
        distribuir(pontos, &personagem);
        printf("%s %d %d %d %d %d", personagem.nome, personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.carisma);
    }
    
    return 0;
}

void distribuir(int pontos, PERS *personagem){
    printf("Voce tem %d pontos. Distribua-os da maneira que quiser\n", pontos);
    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem->forca, personagem->defesa, personagem->magia, personagem->folego, personagem->carisma);
    printf("\n");
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de forca a seguir: ", pontos);
        scanf("%d", &personagem->forca);
        if(personagem->forca > pontos || personagem->forca < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    
    pontos = pontos - personagem->forca;

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem->forca, personagem->defesa, personagem->magia, personagem->folego, personagem->carisma);
    printf("\n");
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de defesa a seguir: ", pontos);
        scanf("%d", &personagem->defesa);
        if(personagem->defesa > pontos || personagem->defesa < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    pontos = pontos - personagem->defesa;

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem->forca, personagem->defesa, personagem->magia, personagem->folego, personagem->carisma);
    printf("\n");
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de magia a seguir: ", pontos);
        scanf("%d", &personagem->magia);
        if(personagem->magia > pontos || personagem->magia < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    pontos = pontos - personagem->magia;

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem->forca, personagem->defesa, personagem->magia, personagem->folego, personagem->carisma);
    printf("\n");
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de folego a seguir: ", pontos);
        scanf("%d", &personagem->folego);
        if(personagem->folego > pontos || personagem->folego < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    pontos = pontos - personagem->folego;

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nCarisma: %d", personagem->forca, personagem->defesa, personagem->magia, personagem->folego, personagem->carisma);
    printf("\n");
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de carisma a seguir: ", pontos);
        scanf("%d", &personagem->carisma);
        if(personagem->carisma > pontos || personagem->carisma < 0){
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    pontos = pontos - personagem->carisma;

}
