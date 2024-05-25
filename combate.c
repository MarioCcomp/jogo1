#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COEF_CRITICO 3

typedef struct _dano{
    char descricao[80];
    int valor;
}DANO;

typedef struct ataque {
    char nome[21];
    int dano;
} ATAQUE;

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
    ATAQUE *ataques[3];
} PERS;

void limparTela()
{
    // system("cls"); //Use este caso esteja rodando em windows
    system("clear"); //Use este caso esteja rodando em linux
}

void criarPers(PERS *heroi, PERS *vilao)
{
    ATAQUE *ataq1, *ataq2, *ataq3;
    ataq1 = (ATAQUE *) malloc(sizeof(ATAQUE));
    ataq2 = (ATAQUE *) malloc(sizeof(ATAQUE));
    ataq3 = (ATAQUE *) malloc(sizeof(ATAQUE));
    strcpy(ataq1->nome, "bola de fogo");
    strcpy(ataq2->nome, "bilada");
    strcpy(ataq3->nome, "Corta relampago");

    ataq1->dano = 5;
    ataq2->dano = 1;
    ataq3->dano = 2;

    strcpy(heroi->nome, "Joao");
    heroi->defesa = 20;
    heroi->folego = 20;
    heroi->vida = 20;
    heroi->destreza = 20;
    heroi->magia = 20;
    heroi->ataques[0] = ataq1;
    heroi->ataques[1] = ataq2;
    heroi->ataques[2] = ataq3;
    // heroi->inventario = 20;
    // heroi->carisma = 20;
    // heroi->danosasofrer = 20;


    strcpy(vilao->nome, "calvo");
    vilao->defesa = 20;
    vilao->folego = 20;
    vilao->vida = 20;
    vilao->destreza = 20;
    vilao->magia = 20;
    vilao->ataques[0] = ataq1;
    vilao->ataques[1] = ataq2;
    vilao->ataques[2] = ataq3;
    // vilao->inventario = 20;
    // vilao->carisma = 20;
    // vilao->danosasofrer = 20;
}

void atacar(PERS *atacante, PERS *atacado, ATAQUE *ataque)
{
    int critico = (rand()%COEF_CRITICO) + 1, dano = ataque->dano * critico;

    atacado->vida -= dano;
    printf("%s usou %s", atacante->nome, ataque->nome);
    printf("\n");
    printf("%s sofreu %d de dano", atacado->nome, dano);
    printf("\n");
}

void jogadorAtaca(PERS *heroi, PERS *vilao)
{
    int ataqEscolhido;
    printf("Escolha um ataque:");
    printf("\n");
    for (int i=0; i<3; i++) {
        printf("%d: %s", i+1, heroi->ataques[i]->nome);
        printf("\n");
    }
    scanf("%d", &ataqEscolhido);
    atacar(heroi, vilao, heroi->ataques[ataqEscolhido-1]);
}

void vilaoAtaca(PERS *heroi, PERS *vilao)
{
    int ataque = rand()%3;
    atacar(vilao, heroi, vilao->ataques[ataque]);
}

void status(PERS *heroi, PERS *vilao)
{
    printf("\n");
    printf("%s: %d de vida.\n", heroi->nome, heroi->vida);
    printf("%s: %d de vida.\n", vilao->nome, vilao->vida);
}

void combater(PERS *heroi, PERS *vilao)
{
    int turno = 0;
    if (heroi->destreza < vilao->destreza) {
        turno = 1;
    }

    /* jogadorAtaca(heroi, vilao);
    printf("%d", vilao->vida); */

    while (heroi->vida > 0 && vilao->vida > 0) {
        status(heroi, vilao);
        if (turno % 2 == 0) {
            jogadorAtaca(heroi, vilao);
        } else {
            vilaoAtaca(heroi, vilao);
        }

        turno++;
    }
    
    limparTela();
    status(heroi, vilao);
    return;
}

void main()
{
    PERS heroi, vilao;
    criarPers(&heroi, &vilao);
    
    combater(&heroi, &vilao);
    if (heroi.vida <= 0) {
        printf("Voce perdeu.");
    } else {
        printf("Voce ganhou.");
    }
}
