/*
    JOGO DA FORCA
    DESENVOLVIDO EM: 26/09/2024
    ATUALIZADO EM:27/09/2024
*/


#include <stdio.h>     
#include <stdlib.h>    
#include <stdbool.h>   // biblioteca para booleanos (true/false)
#include <string.h>    // biblioteca para manipular de strings
#include <time.h>
#include <locale.h>    // biblioteca para acentuacao


#define TAMANHO_ALFABETO 27         // define o tamanho do alfabeto a ser utilizado(26 letras + 1 espaco)

// estrutura para no da arvore Trie - Dicionario
typedef struct Dicionario {
    struct Dicionario* filhos[TAMANHO_ALFABETO]; // array de ponteiros para os filhos (representa letra ou espaco)
    bool fim_da_palavra;                    // indica se o no atual e o fim da palavra
} Dicionario;

// Função para criar um novo no da Trie
Dicionario* criarNo() {
    Dicionario* no = (Dicionario*)malloc(sizeof(Dicionario));  // aloca memoria para um novo no
    no->fim_da_palavra = false;  // inicialmente, o no nao representa o fim de uma palavra
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        no->filhos[i] = NULL;  // todos os ponteiros para os filhos iniciam como NULL
    }
    return no;  // retorna o ponteiro para o no recem-criado
}

// funcao para mapear letras e espacos
int obterIndice(char c) {
    if (c == ' ') {  // se for um espaco
        return 26;   // retorna o indice 26 (espaco)
    } else { //se for uma letra
        return c - 'a';  // para letras minusculas, retorna a posicao baseada no valor do numero do alfabeto
    }
}

// funcao para inserir uma palavra no "dicionario" (trie)
void inserirPalavra(Dicionario* trie, const char* palavra) {
    Dicionario* atual = trie;  // comeca a partir da raiz da Trie
    while (*palavra) {       // enquanto tiver letra
        int index = obterIndice(*palavra);  // converte o caractere em um indice valido (0-25 para letras, 26 para espaço)
        if (!atual->filhos[index]) {        // se nao houver um no filho para o caractere atual
            atual->filhos[index] = criarNo();  // cria um novo no
        }
        atual = atual->filhos[index];  // avanca para o proximo no na Trie
        palavra++;  // avanca para o proximo caractere da palavra
    }
    atual->fim_da_palavra = true;  // marca o ultimo no como o fim de uma palavra valida
}

// funcao para escolher uma palavra aleatoria da Trie
void escolherPalavraAleatoria(Dicionario* trie, char* palavra_selecionada, int profundidade) {
    Dicionario* atual = trie;  // comecamos a partir da raiz da Trie (do dicionario)
    while (1) {
        int i;
        int opcoes[TAMANHO_ALFABETO];  // array para armazenar indices de opcoes validas
        int num_opcoes = 0;

        // percorre os filhos do no atual para encontrar opcoes
        for (i = 0; i < TAMANHO_ALFABETO; i++) {
            if (atual->filhos[i]) {
                opcoes[num_opcoes++] = i;  // adiciona o indice da opcao valida ao array
            }
        }

        // se nao houver filhos ou se o no atual for o fim de uma palavra, finaliza
        if (num_opcoes == 0 || atual->fim_da_palavra) {
            palavra_selecionada[profundidade] = '\0';  // finaliza a string com o caractere nulo ('\0')
            return;  // sai da funcao
        }

        // escolhe uma letra (ou espaco) aleatoriamente entre as opções validas
        int escolha = opcoes[rand() % num_opcoes];
        if (escolha == 26) {  // se a escolha for um espaco
            palavra_selecionada[profundidade] = ' ';  // insere espaco
        } else {
            palavra_selecionada[profundidade] = 'a' + escolha;  // insere a letra correspondente (a -> 0, b -> 1, etc.)
        }
        atual = atual->filhos[escolha];  // avanca para o proximo no na Trie
        profundidade++;  // aumenta a profundidade da palavra gerada
    }
}

// funcao para verificar se uma letra esta presente na palavra
bool verificarLetra(const char* palavra, char letra) {
    while (*palavra) {  // percorre cada caractere da palavra
        if (*palavra == letra) {  // se encontrar a letra, retorna true
            return true;
        }
        palavra++;  // avanca para o proximo caractere
    }
    return false;  // se nao encontrar, retorna false
}

// funcao para exibir o estado atual da palavra com as letras adivinhadas ate o momento
void exibirEstadoPalavra(const char* palavra, const bool* letras_adivinhadas) {
    while (*palavra) {  // percorre cada caractere da palavra
        if (*palavra == ' ') {
            printf("  ");  // exibe duplo espaco para representar espaco
        } else if (letras_adivinhadas[*palavra - 'a']) {
            printf("%c ", *palavra);  // exibe a letra que ja foi adivinhada
        } else {
            printf("_ ");  // exibe underline se a letra não foi adivinhada
        }
        palavra++;  // avanca para o proximo caractere
    }
    printf("\n");
}

// funcao principal do jogo da forca
void jogar(Dicionario* trie) {
    char palavra_selecionada[100];  // array para armazenar a palavra escolhida (100 porque é o limite do tamanho da palavra)
    escolherPalavraAleatoria(trie, palavra_selecionada, 0);  // seleciona palavra aleatoria da Trie

    int tentativas_restantes = 6;  // qtd de tentativas que o jogador tem
    bool letras_adivinhadas[26] = { false };  // array para armazenar as letras adivinhadas pelo jogador

    printf("Jogo da Forca! Adivinhe a palavra:\n");

    // Laco principal do jogo
    while (tentativas_restantes > 0) {
        printf("\nTentativas restantes: %d\n", tentativas_restantes);  // exibe o numero de tentativas restantes
        exibirEstadoPalavra(palavra_selecionada, letras_adivinhadas);  // exibe o estado atual da palavra

        char letra;
        printf("Digite a letra minúscula: ");
        scanf(" %c", &letra);  // recebe a letra digitada pelo jogador

        // verifica se o jogador tentou inserir um espaço
        if (letra == ' ') {
            printf("Não pode inserir espaço! Tente outra letra.\n");
            continue;  // tentar novamente
        }

        // checa se a letra ja foi adivinhada
        if (letras_adivinhadas[letra - 'a']) {
            printf("Você já tentou essa letra. Tente outra.\n");
            continue;  // tentar outra letra
        }

        letras_adivinhadas[letra - 'a'] = true;  // marca a letra como adivinhada

        // verifica se a letra esta presente na palavra selecionada
        if (verificarLetra(palavra_selecionada, letra)) {
            printf("A letra '%c' está na palavra!\n", letra);
        } else {
            printf("A letra '%c' não está na palavra.\n", letra);
            tentativas_restantes--;  // reduz o numero de tentativas se a letra nao estiver presente
        }

        // verifica se o jogador adivinhou a palavra inteira
        bool palavra_descoberta = true;
        for (int i = 0; palavra_selecionada[i] != '\0'; i++) {
            if (palavra_selecionada[i] != ' ' && !letras_adivinhadas[palavra_selecionada[i] - 'a']) {
                palavra_descoberta = false;  // se alguma letra nao foi adivinhada, a palavra nao esta descoberta
                break;
            }
        }

        // se a palavra foi adivinhada, o jogo termina
        if (palavra_descoberta) {
            printf("\nParabéns! Você adivinhou a palavra: %s\n", palavra_selecionada);
            return;  // encerra o jogo
        }
    }

    // se o jogador nao conseguir adivinhar a palavra
    printf("\nVocê perdeu! A palavra era: %s\n", palavra_selecionada);
}

// funcao para criar a Trie com palavras pre-definidas
Dicionario* criarDicionario() {
    Dicionario* trie = criarNo();
    inserirPalavra(trie, "copa do brasil");
    inserirPalavra(trie, "serie a");
    inserirPalavra(trie, "serie b");
    inserirPalavra(trie, "serie c");
    inserirPalavra(trie, "brasileirao serie a");
    inserirPalavra(trie, "brasileirao serie b");
    inserirPalavra(trie, "campeonato carioca");
    inserirPalavra(trie, "campeonato paulista");
    inserirPalavra(trie, "campeonato mineiro");
    inserirPalavra(trie, "campeonato gaucho");
    inserirPalavra(trie, "campeonato cearense");
    inserirPalavra(trie, "campeonato pernambucano");
    inserirPalavra(trie, "campeonato baiano");
    inserirPalavra(trie, "campeonato goiano");
    inserirPalavra(trie, "copa libertadores");
    inserirPalavra(trie, "copa sulamericana");
    inserirPalavra(trie, "supercopa do brasil");
    inserirPalavra(trie, "recopa sulamericana");
    inserirPalavra(trie, "mundial de clubes");
    inserirPalavra(trie, "futebol brasileiro");
    inserirPalavra(trie, "torcida organizada");
    inserirPalavra(trie, "gol de placa");
    inserirPalavra(trie, "estadio do maracana");
    inserirPalavra(trie, "arena corinthians");
    inserirPalavra(trie, "mineirao");
    inserirPalavra(trie, "morumbis");
    inserirPalavra(trie, "beira rio");
    inserirPalavra(trie, "cristiano ronaldo");
    inserirPalavra(trie, "messi");
    inserirPalavra(trie, "neymar");
    inserirPalavra(trie, "meio campo");
    inserirPalavra(trie, "goleiro artilheiro");
    inserirPalavra(trie, "final de jogo");
    inserirPalavra(trie, "intervalo");
    inserirPalavra(trie, "tempo extra");
    inserirPalavra(trie, "cartao vermelho");
    inserirPalavra(trie, "cartao amarelo");
    inserirPalavra(trie, "escanteio");
    inserirPalavra(trie, "falta");
    inserirPalavra(trie, "gol");
    inserirPalavra(trie, "penalti decisivo");
    inserirPalavra(trie, "uniforme");
    inserirPalavra(trie, "camisa");
    inserirPalavra(trie, "gol de letra");
    inserirPalavra(trie, "lance");
    inserirPalavra(trie, "drible da vaca");
    inserirPalavra(trie, "bicicleta");
    return trie;
}

// funcao principal do programa
int main() {
    setlocale(LC_ALL, "");  // definicao do locale

    Dicionario* trie = criarDicionario();  // cria a Trie com palavras pre-definidas
    srand(time(NULL));  // inicializa o gerador de numeros aleatorios

    int opcao;

    // Loop para permitir que o jogador jogue várias vezes
    do {
        jogar(trie);  // chama a funcao para jogar o jogo da forca

        // pergunta ao jogador se ele deseja jogar novamente ou sair
        printf("\nDeseja jogar novamente? (1 - Sim / 2 - Não): ");
        scanf("%d", &opcao);

    } while (opcao == 1);  // se escolher 1, o jogo reinicia

    printf("GAME OVER!\n");

    return 0;
}
