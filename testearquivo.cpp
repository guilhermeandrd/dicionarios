#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

#include "estruturas_auxiliares/ChainedHashTable.hpp"
#include "estruturas_auxiliares/OpenHashTable.hpp"
#include "estruturas_auxiliares/RBTree.hpp"
#include "estruturas_auxiliares/AVLTree.hpp"

using namespace std;

template <typename Key, typename Value>

void lerArquivo( fstream &file, ChainedHashTable<Key, Value>& teste){
    string linha;
    Value v;
    Key k;
    
    while(getline(file, linha)){
        stringstream ss;
        //stringstream ler linha
        ss << linha;
        cout << ss.gcount();
        //a separamos por chave e valor
        ss >> k >> v;
        cout << ss.gcount();

        teste.add(k, v);
    }

    file.close();

}

int main() {
    
    //vetor com dados que serão usados no teste
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

    //inicializacao das estruturas
    for(auto& node : dadosDeTeste){
        //hashEncTESTE.add(node.first, node.second);
        hashOpenTESTE.add(node.first, node.second);
        TreeAvlTESTE.insert(node.first, node.second);
        TreeRbTeste.insert(node.first, node.second);
    }
    string name = "teste.txt";
    TreeAvlTESTE.impressao();
    
    //agora teste de insercao atraves de um arquivo
    fstream file("teste.txt", ios::in);
    
    lerArquivo(file, hashEncTESTE);
    cout << hashEncTESTE;
    return 0;
}

