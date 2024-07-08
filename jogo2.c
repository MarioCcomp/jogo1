#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define COEF_CRITICO 3
#define cp personagem->capitulo

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

ATAQUE *ataq1, *ataq2, *ataq3;



void limparTela()
{
     system("cls"); //Use este caso esteja rodando em windows
   // system("clear"); //Use este caso esteja rodando em linux
}

void inicializarAtaques() {
    ataq1 = (ATAQUE *) malloc(sizeof(ATAQUE));
    ataq2 = (ATAQUE *) malloc(sizeof(ATAQUE));
    ataq3 = (ATAQUE *) malloc(sizeof(ATAQUE));

    
    if (ataq1 == NULL || ataq2 == NULL || ataq3 == NULL) {
        printf("Erro: falha na alocação de memória.\n");
        exit(1); 
    }

    
    strcpy(ataq1->nome, "bola de fogo");
    strcpy(ataq2->nome, "bilada");
    strcpy(ataq3->nome, "Corta relampago");

    ataq1->dano = 30;
    ataq2->dano = 50;
    ataq3->dano = 20;
}

void liberarAtaques() { // Libera a memoria alocada
    free(ataq1);
    free(ataq2);
    free(ataq3);
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
    getchar();
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
    if(heroi->vida < 0)  printf("%s: 0 de vida.\n", heroi->nome);
     else printf("%s: %d de vida.\n", heroi->nome, heroi->vida);
    if(vilao->vida < 0) printf("%s: 0 de vida.\n", vilao->nome);
    else printf("%s: %d de vida.\n", vilao->nome, vilao->vida);
}

int combater(PERS *heroi, PERS *vilao)
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
    
    //limparTela();
    status(heroi, vilao);
       if(heroi->vida <= 0){
        return 0;
    }
    else{
        return 1;
    }
    
}


int facilita(char *hab, int *pontos, PERS personagem){

    printf("Forca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nDestreza: %d\nCarisma: %d", personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.destreza, personagem.carisma);
    printf("\n");
    int x;
    while(1){
        printf("Pontos disponiveis %d\nAtribua os valores de %s a seguir: ", *pontos, hab);
        scanf("%d", &x);
        getchar();
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


void status2(PERS personagem){
    printf("\n"); 
    printf("%s voce tem os seguintes atributos:\nForca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nDestreza: %d\nCarisma: %d\n", personagem.nome, personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.destreza, personagem.carisma);
}

PERS pegarDig(int dig){
    if(dig == 1){
        FILE *salvar;
        int pontos = 30;
        PERS personagem = {0};
        salvar = fopen("salvar.bin", "w");
        printf("Digite o nome do seu personagem: ");
        fgets(personagem.nome, 40, stdin);
        personagem.nome[strcspn(personagem.nome, "\n")] = '\0';
        personagem.capitulo = 0;
        personagem.vida = 100;
        personagem.ataques[0] = ataq1;
        personagem.ataques[1] = ataq2;
        personagem.ataques[2] = ataq3;
        distribuir(pontos, &personagem);
        status2(personagem);
        personagem.capitulo = 1;
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


int func(char *txt, int i){
    for(int j = i; txt[j] != ']'; j++){
        if(txt[j + 1] == ']'){
            i = j + 1;
            return i;
        }
    }
}

int capitulo1(PERS *personagem){
    int vivo, teste = 0;
    PERS goblin;
    goblin.forca = (rand()%4) + 1;
    goblin.defesa = (rand()%4) + 1;
    goblin.destreza = (rand()%4) + 1;
    goblin.magia = (rand()%4) + 1;
    goblin.folego = (rand()%4) + 1;
    goblin.ataques[0] = ataq1;
    goblin.ataques[1] = ataq2;
    goblin.ataques[2] = ataq3;
    goblin.vida = 40;
    strcpy(goblin.nome, "Goblin");
    FILE *cap;
    char txt[201];
    cap = fopen("C:\\vscodeC\\proj\\jogo\\capitulo1.txt", "r");
    while(1){
        fgets(txt, 200, cap);
        for(int i = 0; txt[i] != '\0'; i++){
            if(txt[i] == '\n'){
            txt[i + 1] = '\0';
            }
        }
        for(int i = 0; txt[i] != '\0'; i++){
            if(txt[i] == '['){
                printf("%s", personagem->nome);
                i = func(txt, i);
            }
            else if(txt[i] == '+'){
                teste = 1;
                break;
            }
            else printf("%c", txt[i]);
            
        }


        if(teste) break;
    }
    teste = 0;
      printf("\n");
      char escolha;
      printf("Digite uma opcao: ");
      while(1){ 
      scanf("%c", &escolha);
      getchar();
      if(escolha == 'A' || escolha == 'a'){
        printf("Voce avista o goblin de longe e rapidamente voce tenta correr atras dele");
        printf("\n");
        if(goblin.destreza > personagem->destreza){
            printf("apesar de voce ter bastante gas, e acha realmente que vai conseguir alcançar o goblin, "
            "voce acaba tropeçando em um grande buraco, deixando o goblin escapar e fazendo com que a mulher perca os seus itens");
        }
        else{
            printf("ao voce correr bastante, apesar de muito esforco e cansado, voce consegue capturar o goblin, recuperando a bolsa da mulher e levando o goblin para as autoridades\n");
            personagem->destreza++;
            personagem->carisma++;
            printf("Como recompensa, voce recebeu um pomto de destreza e de carisma");
            status2(*personagem);
        }
        break;
      }
      else if(escolha == 'B' || escolha == 'b'){
        printf("Voce avista o goblin fugindo, mas achando que ele é muito rápido, e voce"
        " decide nao correr atras, com medo de se cansar e se distrair do seu objetivo principal\n");
        printf("Por consequencia disso, voce diminuiu 1 ponto de carisma\n");
        personagem->carisma--;
        status2(*personagem);
        break;
      }
      else if(escolha == 'C' || escolha == 'c'){
        printf("Voce percebe que o goblin esta indo em sua direção e rapidamente da uma"
        " rasteira nele jogando a bolsa pra longe. Porém, o goblin fica revoltado com ele e decide ir pra cima de voce, iniciando uma grande briga.");
        vivo = combater(personagem, &goblin);
        if(vivo){
            printf("%s derrotou com certa facilidade o goblin, que não demonstrava "
            "muita força física, e devolveu a bolsa para a mulher, sendo aplaudido por uma multidão que os cercava.\n", personagem->nome);
            printf("Parabens, voce recebeu um aumento de carisma e de forca");
            personagem->forca++;
            personagem->carisma++;
            status2(*personagem);
            printf("\n");

        }
        else{
            printf("morreu otario");
        }
        break;
      }
      else{
        printf("Digite uma opcao valida: ");
        continue;
      }
      }

      // PARTE 2 CAP 1
        while(1){
            fgets(txt, 200, cap);
            for(int i = 0; txt[i] != '\0'; i++){
                if(txt[i] == '\n'){
                 txt[i + 1] = '\0';
                 }
        }
            for(int i = 0; txt[i] != '\0'; i++){
                if(txt[i] == '['){
                printf("%s", personagem->nome);
                 i = func(txt, i);
            }
            else if(txt[i] == '+'){
                teste = 1;
                break;
            }
            else printf("%c", txt[i]);
            
        }
                if(teste) break;
        }
            printf("\n");
            printf("Escolha sua opcao: ");
            while(1){
            scanf("%c", &escolha);
            getchar();
            if(escolha == 'A' || escolha == 'a'){
                printf("Quando o homem encapuzado senta na mesa você logo pergunta quem seria o misterioso homem.\n "
                "Homem Encapuzado: Sou apenas um conhecedor dos segredos de Eldoria. Sei que você busca respostas sobre"
                " o assassinato de sua família. Há um artefato antigo, perdido há séculos, que pode estar relacionado ao crime que devastou sua vida.\n");
                printf("Com essa revelacao, as duvidas sobre quem seria o homem e como ele sabia disso surgem na sua cabeça."
                " Porem, antes mesmo de você fazer uma pergunta se quer, o homem encapuzado some em frente aos seus olhos.\n\nSua busca por justica agora se intensifica,"
                " com novas pistas e segredos que precisam ser desvendados.");
                personagem->capitulo++;
                return 1;



              
            }
            else if(escolha == 'B' || escolha == 'b'){
                printf("Ao ver o homem encapuzado sentado a sua frente sem ao menos voce autorizar a sua participacao,"
                " voce tenta o expulsar. Mas parecendo que voce nao tinha dito nada, o homem encapuzado diz: Sou apenas"
                " um conhecedor dos segredos de Eldoria. Sei que voce busca respostas sobre o assassinato de sua familia."
                " Ha um artefato antigo, perdido ha seculos, que pode estar relacionado ao crime que devastou sua vida.\n"
                "Com essa revelacao, as duvidas sobre quem seria o homem e como ele sabia disso surgem na sua cabeca."
                " Porem, antes mesmo de voce fazer uma pergunta se quer, o homem encapuzado some em frente aos seus olhos.\n"
                "Sua busca por justica agora se intensifica, com novas pistas e segredos que precisam ser desvendados.");
                personagem->capitulo++;
                return 1;
            }
            else{
                printf("Escolha uma opcao valida: ");
                continue;
            }
            }
}

void salvar(PERS *personagem){
    FILE *fp;
    fp = fopen("salvar.bin", "w");
    fwrite(&personagem, 1, sizeof(PERS), fp);
    fclose(fp);
}

int historia(PERS *personagem){

    if(cp == 1){
      capitulo1(personagem);
      return 0;
    }
    else if(cp == 2){
      //  capitulo2(personagem);
        return 1;
    }
    else if(cp == 3){
       // capitulo3(personagem);
        return 1;
    }
    else if(cp == 4){
       // capitulo4(personagem);
        return 1;
    }
    else if(cp == 5){
        //capitulo5(personagem);
        return 0;
    }
}



int main()
{
    srand(time(NULL));
    FILE *inicio;
    char inicio1[200];
    int digito, teste = 1;
    int numaleatorio;
    inicializarAtaques();
    inicio = fopen("C:\\vscodeC\\proj\\jogo\\teste.txt", "r");
    while(fgets(inicio1, 199, inicio) != NULL){
        printf("%s", inicio1);
    }
    fclose(inicio);
    while(1){
        scanf("%d", &digito);
        getchar();
        if(digito > 3 || digito < 1){
            printf("Por favor, insira um digito valido");
            continue;
        }
        else
        break;
    }
    PERS personagem;
    personagem = pegarDig(digito); // Verifica o digito de entrada
    while(teste){
    teste = historia(&personagem);
    }
    
        

    
    return 0;
}
