#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define cp personagem->capitulo

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
    int capitulo;
} PERS;

int facilita(char *hab, int *pontos, PERS personagem);
void distribuir(int pontos, PERS *personagem);
void limparTela();
void historia(PERS *personagem);
PERS pegarDig(int dig);
void capitulo0(PERS *personagem);
void status(PERS personagem); // printa os atributos do personagem


int main()
{
    srand(time(NULL));
    FILE *inicio;
    char inicio1[200];
    int digito;
    int numaleatorio;
    inicio = fopen("D:\\vscodeC\\proj\\jogo\\teste.txt", "r");
    while(!feof(inicio)){
        fgets(inicio1, 199, inicio);
        printf("%s", inicio1);
    }
    fclose(inicio);
    while(1){
        scanf("%d", &digito);
        if(digito > 3 || digito < 1){
            printf("Por favor, insira um digito valido");
            continue;
        }
        else
        break;
    }
    PERS personagem;
    personagem = pegarDig(digito); // Verifica o digito de entrada

    printf("%s", personagem.nome);

    
    return 0;
}

void distribuir(int pontos, PERS *personagem){
    printf("Voce tem %d pontos. Distribua-os da maneira que quiser\n", pontos);
    int pontos2 = pontos;
    char forca[6] = "forca";
    char defesa[7] = "defesa";
    char magia[6] = "magia";
    char folego[7] = "folego";
    char destreza[9] = "destreza";
    char carisma[8] = "carisma";
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
            limparTela();
            printf("Voce nao tem pontos suficientes\n");
            continue;
        }
        else
            break;
    }
    *pontos = *pontos - x;
    return x;


}

void limparTela()
{
     system("cls"); //Use este caso esteja rodando em windows
    //system("clear"); //Use este caso esteja rodando em linux
}

PERS pegarDig(int dig){
    if(dig == 1){
        FILE *salvar;
        int pontos = 30;
        PERS personagem = {0};
        salvar = fopen("salvar.bin", "w");
        printf("Digite o nome do seu personagem: ");
        scanf("%s", personagem.nome);
        personagem.capitulo = 0;
        distribuir(pontos, &personagem);
        status(personagem);
        fwrite(&personagem, 1, sizeof(PERS), salvar);
        fclose(salvar);
        return personagem;
    }
    else if(dig == 2){
    FILE *salvar;
    salvar = fopen("salvar.bin", "r");
    PERS save;
    fread(&save, sizeof(PERS), 1, salvar);
    return save;
    }
    else if(dig == 3){
        exit(1);
    }
}

void status(PERS personagem){
    printf("\n"); 
    printf("%s voce tem os seguintes atributos:\nForca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nDestreza: %d\nCarisma: %d", personagem.nome, personagem.forca, personagem.defesa, personagem.magia, personagem.destreza, personagem.folego, personagem.carisma);
    printf("\n");
}


void historia(PERS *personagem){
    if(cp == 0){
      capitulo0(&personagem);
      status(*personagem);  
    }
}

void capitulo0(PERS *personagem){
    
}
