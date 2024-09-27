# Atividade Final - Estrutura de Dados II

**Aluno:** Antonio Ivo de Oliveira Souza

## Problema 1: Jogo da Forca em C com Árvores Trie

### Descrição
Este projeto implementa um jogo da Forca utilizando a estrutura de dados Trie para armazenar e gerenciar o "dicionário" de palavras do jogo. A Trie permite inserções rápidas e busca eficiente de palavras, contribuindo para a mecânica do jogo. O objetivo do jogo é adivinhar uma palavra selecionada aleatoriamente da Trie, com base em palpites de letras feitas pelo jogador.

### Funcionalidades Implementadas

1. **Inserção de palavras na Trie**
   - Implementada a funcionalidade de inserção de palavras no "dicionário" Trie, possibilitando o uso futuro dessas palavras no jogo.
   
2. **Escolha de palavra aleatória da Trie**
   - O programa seleciona uma palavra aleatória do dicionário Trie para o jogador adivinhar.

3. **Verificação de letras na palavra**
   - Implementação da função que verifica se uma letra digitada pelo jogador está presente na palavra selecionada.

4. **Exibição do estado atual da palavra**
   - O estado atual da palavra é exibido, revelando as letras já adivinhadas e mantendo sublinhados (_) para as letras não adivinhadas.

5. **Contagem de tentativas e controle de erros**
   - O jogo reduz o número de tentativas disponíveis quando o jogador erra uma letra e notifica se a letra já foi tentada anteriormente.

6. **Controle do término do jogo**
   - Implementada a verificação de vitória (quando a palavra é adivinhada completamente) ou derrota (quando as tentativas acabam).

### Funcionalidades Implementadas Parcialmente

1. **Validação da entrada do jogador**
   - A validação de entradas impede espaços e verifica se a letra já foi usada anteriormente. No entanto, a validação não cobre completamente todos os casos, como a inserção de números ou símbolos.
