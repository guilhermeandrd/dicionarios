#include <iostream>
#include <vector>
#include <utility>
#include <string>

#include "estruturas_auxiliares/ChainedHashTable.hpp"
#include "estruturas_auxiliares/OpenHashTable.hpp"
#include "estruturas_auxiliares/RBTree.hpp"
#include "estruturas_auxiliares/AVLTree.hpp"

using namespace std;

//TESTE PARA VER SE O ITERADOR FACILITA NA FREQUENCIA
int main() {

    //DADOS DO TESTE EM FORMATO DE VETOR PARA FACILITAR NO TESTE
    std::vector<std::pair<std::string, int>> dados_para_teste = {
    {"Alpha", 101}, {"Beta", 203}, {"Gamma", 154}, {"Delta", 332}, {"Omega", 218},
    {"Alpha", 119}, {"Beta", 255}, {"Gamma", 188}, {"Delta", 340}, {"Omega", 229},
    {"Alpha", 132}, {"Beta", 210}, {"Gamma", 199}, {"Delta", 315}, {"Omega", 245},
    {"Alpha", 105}, {"Beta", 281}, {"Gamma", 160}, {"Delta", 380}, {"Omega", 211},
    {"Alpha", 140}, {"Beta", 209}, {"Gamma", 173}, {"Delta", 301}, {"Omega", 288},
    {"Alpha", 115}, {"Beta", 215}, {"Gamma", 201}, {"Delta", 399}, {"Omega", 204},
    {"Gamma", 183}, {"Alpha", 166}, {"Beta", 240}, {"Omega", 251}, {"Delta", 319},
    {"Alpha", 199}, {"Beta", 233}, {"Gamma", 159}, {"Delta", 375}, {"Omega", 260},
    {"Beta", 212}, {"Alpha", 111}, {"Omega", 299}, {"Gamma", 191}, {"Delta", 364},
    {"Alpha", 108}, {"Beta", 248}, {"Gamma", 178}, {"Delta", 321}, {"Omega", 238},
    {"Alpha", 121}, {"Beta", 283}, {"Gamma", 164}, {"Delta", 342}, {"Omega", 208},
    {"Alpha", 139}, {"Beta", 265}, {"Gamma", 177}, {"Delta", 350}, {"Omega", 239},
    {"Alpha", 122}, {"Beta", 220}, {"Gamma", 189}, {"Delta", 325}, {"Omega", 255},
    {"Alpha", 118}, {"Beta", 271}, {"Gamma", 150}, {"Delta", 370}, {"Omega", 221},
    {"Alpha", 150}, {"Beta", 219}, {"Gamma", 163}, {"Delta", 311}, {"Omega", 278},
    {"Alpha", 125}, {"Beta", 225}, {"Gamma", 211}, {"Delta", 389}, {"Omega", 214},
    {"Gamma", 173}, {"Alpha", 176}, {"Beta", 250}, {"Omega", 261}, {"Delta", 329},
    {"Alpha", 189}, {"Beta", 223}, {"Gamma", 149}, {"Delta", 365}, {"Omega", 270},
    {"Beta", 222}, {"Alpha", 101}, {"Omega", 289}, {"Gamma", 181}, {"Delta", 354},
    {"Alpha", 118}, {"Beta", 238}, {"Gamma", 188}, {"Delta", 331}, {"Omega", 248},
    {"Alpha", 131}, {"Beta", 273}, {"Gamma", 174}, {"Delta", 352}, {"Omega", 218}
    };

    //TESTE COM TABELA ENCADEADA
    ChainedHashTable<string, int> testeEncadeada;

    //LOOP QUE ITERA UM ELEMENTO SEMPRE QUE O ACHA, O ITERANDO UMA VEZ
    //CASO ELE NAO EXISTA, O ELEMENTO É CRIADO E JA É POSSUI VALOR UM
    for(auto& node : dados_para_teste){
        testeEncadeada[node.first]++;
    }

    cout << testeEncadeada;

    cout << dados_para_teste.size() << endl;

    //TESTE COM TABELA ABERTA
    OpenHashTable<string, int> testeAberta;

    for(auto& node : dados_para_teste){
        testeAberta[node.first]++;
    }

    cout << testeAberta;

    //TESTE COM RUBRO NEGRA

    RBtree<string, int> rb;


    for(auto& node : dados_para_teste){
        rb[node.first];
    }

    rb.show();

    //TESTE COM AVL

    //DEPOIS DISSO ORDENA

        //para as árvores, basta imprimir em ordem
        //para as tabelas, é necessário passar tudo para um vetor e aí o ordenar
        //funcao_ideal(arquivo, arv) - retorna o arquivo com aquela arvore em ordem

    //E INSERE EM UM ARQUIVO DE SAÍDA

    rb.remove("Beta");

    rb.show();
    return 0;
}