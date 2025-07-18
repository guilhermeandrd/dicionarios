# 📖 Dicionários - Implementação de Estruturas de Dados

Projeto desenvolvido como trabalho final para a disciplina de Estrutura de Dados Avançadas, focado na implementação e análise de diferentes estruturas de Dicionários (Maps).

## ✨ Estruturas Implementadas

O projeto inclui as seguintes estruturas de dados:

-   Tabela Hash com Encadeamento
-   Tabela Hash com Endereçamento Aberto
-   Árvore AVL
-   Árvore Rubro-Negra

---

## 🚀 Como Utilizar

Siga os passos abaixo para compilar e executar o programa.

Para compilar o projeto, você precisará ter a biblioteca **ICU (International Components for Unicode)** instalada. Utilize o seguinte comando no seu terminal:

```bash
g++ -std=c++20 -Wall main.cpp -o meu_programa $(pkg-config --cflags --libs icu-uc icu-i18n)

```
Depois tente:

```bash
./meu_programa estrutura_que_voce_vai_usar nome_do_arquivo_que_vai_ser_lido nome_do_arquivo_de_saida

```

Exemplo:

```bash
 ./meu_programa dicionarioAvl sherlock_holmes.txt sherlockavl.txt
```

Ou então:

```bash
./meu_programa dicionarioAvl sherlock_holmes.txt
```

