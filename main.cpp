#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "ChainedHashTable.hpp"
#include "OpenHashTable.hpp"
#include "RBTree.hpp"
#include "AVLTree.hpp"

using namespace std;

template <typename Key, typename Value, typename Arvore>
void insereArvore(vector<pair<Key, Value>> vetor, Arvore &rb);

template <typename Key, typename Value, typename Tabela>
void insereTabela(vector<pair<Key, Value>> vetor, Tabela &rb);


template <typename Key, typename Value, typename Class>
void verificaConter(vector<pair<Key, Value>> vetor, Class teste);

template <typename Key, typename Value, typename Class>
void removeClass(vector<pair<Key, Value>> vetor, Class &teste);

template <typename Key, typename Value, typename Tabela>
void updateTabela(vector<pair<Key, Value>> vetor, Tabela &teste);

int main() {
    
    vector<pair<int, string>> dadosDeTeste = {
        {44, "Engenharia"}, {17, "Medicina"}, {88, "Direito"}, {32, "Fisica"}, {65, "Quimica"},
        {97, "Biologia"}, {28, "Historia"}, {54, "Geografia"}, {82, "Filosofia"}, {93, "Sociologia"},
        {29, "Matematica"}, {76, "Letras"}, {68, "Psicologia"}, {10, "Arquitetura"}, {50, "Jornalismo"},
        {5, "Publicidade"}, {39, "Propaganda"}, {70, "Cinema"}, {80, "Teatro"}, {99, "Musica"},
        {15, "Danca"}, {25, "Educacao Fisica"}, {35, "Ciencia da Computacao"}, {45, "Sistemas de Informacao"},
        {55, "Analise de Sistemas"}, {60, "Redes de Computadores"}, {75, "Seguranca da Informacao"},
        {85, "Inteligencia Artificial"}, {95, "Robotica"}, {100, "Design Grafico"}, {12, "Moda"},
        {22, "Gastronomia"}, {48, "Veterinaria"}, {62, "Farmacia"}, {78, "Nutricao"}
    };

    //criacao das estruturas 
    ChainedHashTable<int, string> hashEncTESTE;
    OpenHashTable<int, string> hashOpenTESTE;
    AvlTree<int, string> TreeAvlTESTE;
    RBtree<int, string> TreeRbTeste;

    //inicializamos com os dados do teste
    insereArvore(dadosDeTeste, TreeAvlTESTE);
    insereArvore(dadosDeTeste, TreeRbTeste);
    insereTabela(dadosDeTeste, hashOpenTESTE);
    insereTabela(dadosDeTeste, hashEncTESTE);

    //TESTE DE INSERCOES
    //as imprimos para ver se estao corretas
    cout << hashEncTESTE;
    cout << endl;
    cout << hashOpenTESTE;
    cout << endl;
    TreeAvlTESTE.show();
    TreeRbTeste.show();

    //metricas 
    cout << "comparacoes:" << endl
    << "rubro negra: " << TreeRbTeste.counter_comparator() << endl
    << "avl: " << TreeAvlTESTE.counter_comparator() << endl
    << "hash aberto: " << hashOpenTESTE.counter_comparator() << endl
    << "hash encadadeado: " << hashEncTESTE.counterComparator() << endl;

    cout << "rotacoes e colisoes" << endl
    << "rb" << TreeRbTeste.counter_rotation() << endl
    << "avl" << TreeAvlTESTE.counter_rotation() << endl
    << "opem: " << hashOpenTESTE.counter_collision() << endl
    << "enc: " << hashEncTESTE.counterCollision() << endl;

    //TESTE DO CONTAINS e TESTE DO AT
    verificaConter(dadosDeTeste, TreeRbTeste);
    verificaConter(dadosDeTeste, TreeAvlTESTE);
    verificaConter(dadosDeTeste, hashOpenTESTE);
    verificaConter(dadosDeTeste, hashEncTESTE);


    //TESTE DO REMOVE
    //remove todos os elementos das estruturas
    //tem que ficar vazias apos esse teste
    removeClass(dadosDeTeste, TreeAvlTESTE);
    removeClass(dadosDeTeste, TreeRbTeste);
    removeClass(dadosDeTeste, hashEncTESTE);
    removeClass(dadosDeTeste, hashOpenTESTE);

    cout << hashEncTESTE << endl << hashOpenTESTE;
    TreeAvlTESTE.show();
    TreeRbTeste.show();

    //SIZES
    cout << TreeAvlTESTE.size() << " " << TreeRbTeste.size() << " " << hashOpenTESTE.size() << " " 
    << hashEncTESTE.size() << endl;

    //TESTE DO CLEAR
    //as impressoes devem ficam vazias apos esse teste
    
    //a inicializamos novamente para os testes
    insereArvore(dadosDeTeste, TreeAvlTESTE);
    insereArvore(dadosDeTeste, TreeRbTeste);
    insereTabela(dadosDeTeste, hashOpenTESTE);
    insereTabela(dadosDeTeste, hashEncTESTE);
    TreeAvlTESTE.clear();
    TreeRbTeste.clear();
    hashEncTESTE.clear();
    hashOpenTESTE.clear();

    cout << "tabela hash encadeada: "  << endl << "\n" << hashEncTESTE << endl
    << "tabela hash aberta:" << endl << "\n" << hashOpenTESTE;

    cout << "arvore avl: " << endl << "\n";
    TreeAvlTESTE.show();

    cout << "arvore rubro negra: " << endl << "\n";
    TreeRbTeste.show();


    //TESTE DO UPDATE PARA AS TABELAS
    insereTabela(dadosDeTeste, hashOpenTESTE);
    insereTabela(dadosDeTeste, hashEncTESTE);
    updateTabela(dadosDeTeste, hashEncTESTE);
    updateTabela(dadosDeTeste, hashOpenTESTE);

    //TESTE DO UPDATE PARA AS ARVORES
    //as inicaliza novamente
    insereArvore(dadosDeTeste, TreeRbTeste);
    insereArvore(dadosDeTeste, TreeAvlTESTE);

    //atualiza o valor de chave 5
    TreeRbTeste.insert(5, "Farmacia");
    TreeRbTeste.show();

    //atualiza o valor de chave 5
    TreeAvlTESTE.update(5, "Zoologia");
    TreeAvlTESTE.show();

    //ESSA LINHA AQUI IRA RETORNAR ERRO SE TIVER CORRETAMENTE IMPLEMENTADO
    //POIS NAO EXISTE UM PAR COM CHAVE 288
    //TreeAvlTESTE.update(288, "error");

    //TESTE DO ITERADOR PARA TABELAS
    cout << hashOpenTESTE[5] << endl;
    cout << hashEncTESTE[5] << endl;


    
    //CONTADORES E METRICAS FINAIS
    cout << "comparacoes:" << endl
    << "rubro negra: " << TreeRbTeste.counter_comparator() << endl
    << "avl: " << TreeAvlTESTE.counter_comparator() << endl
    << "hash aberto: " << hashOpenTESTE.counter_comparator() << endl
    << "hash encadadeado: " << hashEncTESTE.counterComparator() << endl;

    cout << "rotacoes e colisoes" << endl
    << "rb" << TreeRbTeste.counter_rotation() << endl
    << "avl" << TreeAvlTESTE.counter_rotation() << endl
    << "opem: " << hashOpenTESTE.counter_collision() << endl
    << "enc: " << hashEncTESTE.counterCollision() << endl;

    

    return 0;
}

template <typename Key, typename Value, typename Arvore>
/**
 * @brief insere os valores do vetor na arvore passada, seja rubro negra ou avl
 */
void insereArvore(vector<pair<Key, Value>> vetor, Arvore &rb){
    for(auto& node : vetor){
        rb.insert(node.first, node.second);
    }
}

/**
 * @brief insere os valores do vetor na tabela passada, seja qual tipo for
 */
template <typename Key, typename Value, typename Tabela>
void insereTabela(vector<pair<Key, Value>> vetor, Tabela &rb){
    for(auto& node : vetor){
        rb.add(node.first, node.second);
    }
}


template <typename Key, typename Value, typename Class>
/**
 * @brief verifica se os elementos do vetor estão em um classe qualquer,
 * para o teste dar certo, todos os elementos do vetor devem estar na classe.
 * além disso, ele executa a função at da classe. testando o contains e at 
 * ao mesmo tempo.
 */
void verificaConter(vector<pair<Key, Value>> vetor, Class teste){
    for(auto& node : vetor){
        if(!teste.contains(node.first)){
            cout << "contains nao foi corretamente implementado";
        }else{
            cout << teste.at(node.first) << endl;
        }
    }
}

template <typename Key, typename Value, typename Class>
/**
 * @brief testa o remove da classe passando um vetor, se o elemento ainda
 * existir apos a insercao, entao o remove nao foi implementado corretamente
 */
void removeClass(vector<pair<Key, Value>> vetor, Class &teste){
    for(auto& node : vetor){
        teste.remove(node.first);
        if(teste.contains(node.first)){
            cout << "deu erro";
        }
    }
}

template <typename Key, typename Value, typename Tabela>
/**
 * @brief testa o update da tabela, passando um vetor que adciona o elemento que ja existe.
 * para dar certo, os elementos do vetor tem que estar todos ja inseridos na tabela.
 * como ele nao vai inserir, no maximo atualizar, a funcao add ira retornar false 
 * e nao ira imprimir o "deu erro".
 */
void updateTabela(vector<pair<Key, Value>> vetor, Tabela &teste){
    for(auto& node : vetor){
        if(teste.add(node.first, node.second)){
            cout << "deu erro";
        }
    }
}