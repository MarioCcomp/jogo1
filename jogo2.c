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

    ataq1->dano = 25;
    ataq2->dano = 15;
    ataq3->dano = 20;
}

void liberarAtaques() {
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
    printf("Comeca a luta entre %s e %s\n", heroi->nome, vilao->nome);
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
        limparTela();
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
    printf("%s voce tem os seguintes atributos:\nForca: %d\nDefesa: %d\nMagia: %d\nFolego: %d\nDestreza: %d\nCarisma: %d\n\n", personagem.nome, personagem.forca, personagem.defesa, personagem.magia, personagem.folego, personagem.destreza, personagem.carisma);
}

PERS pegarDig(int dig){
    PERS retorno;
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
        limparTela();
        distribuir(pontos, &personagem);
        limparTela();
        personagem.capitulo = 1;
        fwrite(&personagem, 1, sizeof(PERS), salvar);
        fclose(salvar);
        return personagem;
    }
    else if(dig == 2){
    FILE *salvar;
    int choice;
    salvar = fopen("salvar.bin", "r");
    PERS save;
    fread(&save, sizeof(PERS), 1, salvar);
    status2(save);
    //printf("\n");
    while(1){
                    printf("Digite 1 para continuar\nDigite 2 para ver o status do seu personagem\nFaca sua escolha: ");
                    scanf("%d", &choice);
                    getchar();
                    if(choice == 1){
                        limparTela();
                        break;
                    }
                    else if(choice == 2){
                        limparTela();
                        status2(save);
                    }
                    else{
                        printf("Digite um digito valido");
                    }
                }
    return save;
    }
    else if(dig == 3){
        exit(1);
    }
    return retorno;
}


int func(char *txt, int i){
    for(int j = i; txt[j] != ']'; j++){
        if(txt[j + 1] == ']'){
            i = j + 1;
            return i;
        }
    }
    return 0;
}


void printar(char *file, PERS *personagem){
    FILE *fp;
    fp = fopen(file, "r");
    int teste = 0;
    char txt[201];
    while(1){
        teste = 0;
        fgets(txt, 200, fp);
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
        if(teste){
            fclose(fp);
            break;  
        } 
    }
} 

long printar2(char *file, PERS *personagem, long position){
    FILE *fp;
    long position2;
    fp = fopen(file, "r");
    fseek(fp, position, SEEK_SET);
    int teste = 0;
    char txt[201];
    while(1){
        teste = 0;
        fgets(txt, 200, fp);
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
        if(teste){
            position2 = ftell(fp);
            fclose(fp);
            return position2;
            break;  
        } 
    }
} 

void printarMens(PERS personagem){
        int choice;
        while(1){
        printf("\nDigite 1 para continuar\nDigite 2 para ver o status do seu personagem\nDigite 3 para sair do jogo (AVISO: Caso esteja no meio do capitulo, o progresso atual sera perdido e o jogo voltara ao comeco do capitulo atual)\nFaca sua escolha: ");
        scanf("%d", &choice);
        getchar();
        if(choice == 1){
            limparTela();
            break;
        }
        else if(choice == 2){
            limparTela();
            status2(personagem);
        }
        else if(choice == 3){
            if(personagem.capitulo == 1){
                FILE *fp;
                fp = fopen("salvar.bin", "w");
                fclose(fp);
            }
            exit(1);
        }
        else{
            printf("Digite um digito valido\n");
        }
    }
}

void printarFim(PERS personagem){
        int choice;
        while(1){
        printf("\nDigite 1 para ver o status do seu personagem\nDigite 2 para sair do jogo\nFaca sua escolha: ");
        scanf("%d", &choice);
        getchar();
         if(choice == 1){
            limparTela();
            status2(personagem);
        }
        else if(choice == 2){
            if(personagem.capitulo == 1){
                FILE *fp;
                fp = fopen("salvar.bin", "w");
                fclose(fp);
            }
            exit(1);
        }
        else{
            printf("Digite um digito valido\n");
        }
    }
}

void limparBufferTeclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Descarta o caractere lido
    }
}

void printarFiltrado(char texto[1001], char nome[40])
{
    for (int i=3; i<strlen(texto); i++) {
        if (texto[i] == '$') {
            printf("%s", nome);
        } else {
            printf("%c", texto[i]);
        }
    }
}


int capitulo1(PERS *personagem){
    int vivo;
    long position = 0;
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
    limparTela();
    position = printar2("capitulo1.txt", personagem, position);
      printf("\n");
      char escolha;
      printf("Digite uma opcao: ");
      while(1){ 
      scanf("%c", &escolha);
      getchar();
      limparTela();
      if(escolha == 'A' || escolha == 'a'){
        if(goblin.destreza > personagem->destreza){
            printar("capitulo1parte1AF.txt", personagem);
            printf("\nPelo seu esforco, voce acaba de receber 1 ponto de destreza");
            personagem->destreza++;
        }
        else{
            printar("capitulo1parte1AV.txt", personagem);
            personagem->destreza++;
            personagem->carisma++;
            printf("\nComo recompensa, voce recebeu um ponto de destreza e de carisma\n");
        }
        printarMens(*personagem);
        break;
      }
      else if(escolha == 'B' || escolha == 'b'){
        printar("capitulo1parte1B.txt", personagem);
        printf("\nPor consequencia disso, voce perdeu 1 ponto de carisma\n");
        personagem->carisma--;
        printarMens(*personagem);
        break;
      }
      else if(escolha == 'C' || escolha == 'c'){
        printf("Voce percebe que o goblin esta indo em sua direcao e rapidamente da uma"
        " rasteira nele jogando a bolsa pra longe. Porem, o goblin fica revoltado e decide ir pra cima de voce, iniciando uma grande briga.");
        vivo = combater(personagem, &goblin);
        if(vivo){
            printf("%s derrotou com certa facilidade o goblin, que nao demonstrava "
            "muita forca fisica, e devolveu a bolsa para a mulher, sendo aplaudido por uma multidao que os cercava.\n", personagem->nome);
            printf("Parabens, voce recebeu um aumento de carisma e de forca");
            personagem->forca++;
            personagem->carisma++;
            printf("\n");

        }
        else{
            printf("morreu otario\n");
        }
        printarMens(*personagem);
        break;
      }
      else{
        printf("Digite uma opcao valida: ");
        continue;
      }
      }

      // PARTE 2 CAP 1
        position = printar2("capitulo1.txt", personagem, position);
            printf("\n");
            printf("Escolha sua opcao: ");
            while(1){
            scanf("%c", &escolha);
            getchar();
            limparTela();
            if(escolha == 'A' || escolha == 'a'){
                printar("capitulo1parte2A.txt", personagem);
                printf("\n");
                personagem->capitulo++;
                salvar(*personagem);
                printarMens(*personagem);
                return 1;
            }
            else if(escolha == 'B' || escolha == 'b'){
                printar("capitulo1parte2B.txt", personagem);
                printf("\n");
                personagem->capitulo++;
                salvar(*personagem);
                
                printarMens(*personagem);
                return 1;
            }
            else{
                limparTela();
                printf("Escolha uma opcao valida: ");
                continue;
            }
            }
}

int capitulo2(PERS *personagem)
{
    FILE *f = fopen("capitulo2.txt", "r");
    char texto[1001];
    char escolha = 'Z';
    while (fgets(texto, sizeof(texto), f) != NULL) {
        int tam = strlen(texto);
        if (escolha == 'a' || escolha == 'A') {
            if (texto[0] == '[' && texto[1] == 'A' && texto[2] == ']') {
                printarFiltrado(texto, personagem->nome);
                printf("\n");
            }
        } else if (escolha == 'b' || escolha == 'B') {
            if (texto[0] == '[' && texto[1] == 'B' && texto[2] == ']') {
                printarFiltrado(texto, personagem->nome);
                printf("\n");
            }
        } else if (escolha == 'c' || escolha == 'C') {
            if (texto[0] == '[' && texto[1] == 'C' && texto[2] == ']') {
                printarFiltrado(texto, personagem->nome);
                printf("\n");
            }
        } else if (escolha == 'Z') {
            if (texto[3] == '+') {
                scanf("%c", &escolha);
            }
            printarFiltrado(texto, personagem->nome);
            printf("\n");
        }
    }
    printf("\n");
    if (escolha == 'a' || escolha == 'A') {
        personagem->magia += 10;
        printf("Voce recebeu 10 pontos de magia");
    } else if (escolha == 'b' || escolha == 'B') {
        personagem->carisma +=10;
        printf("Voce recebeu 10 pontos de carisma");
    } else if (escolha == 'c' || escolha == 'C') {
        personagem->magia += 10;
        printf("Voce recebeu 10 pontos de magia");
    }
    personagem->capitulo++;
    salvar(*personagem);
    return 1;
}


int capitulo3(PERS *personagem){
    char escolha;
    long position = 0, p2 = 0;
    position = printar2("capitulo3.txt", personagem, position);
    printf("\n");
    printarMens(*personagem);
    position = printar2("capitulo3.txt", personagem, position);
    

    printf("\nFaca sua escolha: ");
    scanf("%c", &escolha);
    getchar();
    if(escolha == 'A' || escolha == 'a'){
        limparTela();
        printar("capitulo3opcaoa.txt", personagem);
    }
    else if(escolha == 'B' || escolha == 'b'){
        limparTela();
        printar("capitulo3opcaob.txt", personagem);
    }
   //parte 2 cap 3

    position = printar2("capitulo3.txt", personagem, position);
    printf("\nFaca sua escolha: ");
    scanf("%c", &escolha);
    getchar();
    limparTela();
    if(escolha == 'a' || escolha == 'A'){
        printar("cp3pt2opa.txt", personagem);
    }
    else if(escolha == 'b' || escolha == 'B'){
        p2 = printar2("cp3pt2opb.txt", personagem, p2);
        printarMens(*personagem);
        p2 = printar2("cp3pt2opb.txt", personagem, p2);
    }
    position = printar2("capitulo3.txt", personagem, position);
    printf("\n");
    printarMens(*personagem);
    position = printar2("capitulo3.txt", personagem, position);
    printf("\n");
    printarMens(*personagem);
    position = printar2("capitulo3.txt", personagem, position);
    printf("\n");
    printarMens(*personagem);
    position = printar2("capitulo3.txt", personagem, position);
    printf("\nFaca sua escolha: ");
    while(1){
    scanf("%c", &escolha);
    getchar();
    if(escolha == 'a' || escolha == 'A'){
        printar("cp3pt3opa.txt", personagem);
        printf("\n");
        printarMens(*personagem);
        personagem->capitulo++;
        break;
    }
    else if(escolha == 'b' || escolha == 'B'){
        printar("cp3pt3opb.txt", personagem);
        printf("\n");
        printarMens(*personagem);
        personagem->capitulo++;
        break;
    }
    else{
        printf("\nDigite uma opcao valida: ");
    }
    }
    return 0;
}

int capitulo4(PERS *personagem, char arquivo[30])
{
    limparTela();
    limparBufferTeclado();
    char file[50] = "capitulo4/";
    strcat(file, arquivo);
    FILE *f = fopen(file, "r");
    char texto[1001];
    char escolha = 'Z';
    while (fgets(texto, sizeof(texto), f) != NULL) {
        int tam = strlen(texto);
        if (texto[0] == '[' && (texto[1] == escolha  || texto[1] == escolha - 32) && texto[2] == ']') {
            if (texto[3] == '+') {
                scanf(" %c", &escolha);
            } else if (texto[3] == '@') {
                fgets(texto, sizeof(texto), f);
                char ch = '&';
                char *pos = strchr(texto, ch);
                int index = pos - texto;
                texto[index] = '\0';
                capitulo4(personagem, texto);
                break;
            } else {
                printarFiltrado(texto, personagem->nome);
                printf("\n");
            }
        }
    }
    personagem->capitulo++;
    salvar(*personagem);
    return 1;
}

int capitulo5(PERS *personagem){
    salvar(*personagem);
    PERS vilao;
    vilao.forca = (rand()%4) + 1;
    vilao.defesa = (rand()%4) + 1;
    vilao.destreza = (rand()%4) + 1;
    vilao.magia = (rand()%4) + 1;
    vilao.folego = (rand()%4) + 1;
    vilao.ataques[0] = ataq1;
    vilao.ataques[1] = ataq2;
    vilao.ataques[2] = ataq3;
    vilao.vida = 60;
    strcpy(vilao.nome, "Lord Dredge");
    int vivo = 0, temp;
    char escolha;
    long position = 0;
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    vivo = combater(personagem, &vilao);
    printf("\n");
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    position = printar2("capitulo5.txt", personagem, position);
    printarMens(*personagem);
    position = printar2("capitulo5.txt", personagem, position);
    printf("\n");
    printf("\n");
    printar("capitulo5esc.txt", personagem);
    printf("\nFaça sua escolha: ");
    while(1){
    scanf("%c", &escolha);
    getchar();
    if(escolha == 'A' || escolha == 'a'){
        printar("capitulo5A.txt", personagem);
        printf("\n\n");
        printf("Voce chegou ao fim do jogo, parabens\n");
        while(1){
        printarFim(*personagem);
        scanf("%d", &temp);
        getchar();
        if(temp != 1 || temp != 2){
            printf("Digite um numero valido: ");
        }
        }
    }
    else if(escolha == 'B' || escolha == 'b'){
        printar("capitulo5B.txt", personagem);
        printf("\n\n");
        printf("Voce chegou ao fim do jogo, parabens\n");
        while(1){
        printarFim(*personagem);
        scanf("%d", &temp);
        getchar();
        if(temp != 1 || temp != 2){
            printf("Digite um numero valido: ");
        }
        }
    }
    else if(escolha == 'C' || escolha == 'c'){
        printar("capitulo5C.txt", personagem);
        printf("\n\n");
        printf("Voce chegou ao fim do jogo, parabens\n");
        while(1){
        printarFim(*personagem);
        scanf("%d", &temp);
        getchar();
        if(temp != 1 || temp != 2){
            printf("Digite um numero valido: ");
        }
        }

    }
    else{
        printf("Escolha uma opcao valida: ");
    }
    }
    
    
    return 1;
}



void salvar(PERS personagem){
    FILE *fp;
    fp = fopen("salvar.bin", "w");
    fwrite(&personagem, 1, sizeof(PERS), fp);
    fclose(fp);
}

int historia(PERS *personagem){

    if(cp == 1){
      capitulo1(personagem);
      return 1;
    }
    else if(cp == 2){
      capitulo2(personagem);
        return 1;
    }
    else if(cp == 3){
        capitulo3(personagem);
        return 1;
    }
    else if(cp == 4){
        capitulo4(personagem, "capitulo4.txt");
        return 1;
    }
    else if(cp == 5){
        capitulo5(personagem);
        return 0;
    }
    return 0;
}



int main()
{
    srand(time(NULL));
    FILE *inicio;
    char inicio1[200];
    int digito, teste = 1;
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
