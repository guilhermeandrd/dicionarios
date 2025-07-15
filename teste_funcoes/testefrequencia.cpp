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
    Key k;
    
    while(getline(file, linha)){
        stringstream ss;
        //stringstream ler linha
        ss << linha;

        //a separamos por chaves
        while(ss >> k){
            teste[k]++;
        }
            

    }

    file.close();

}

template <typename Key, typename Value>

void lerArquivolento( fstream &file, ChainedHashTable<Key, Value>& teste){
    string linha;
    Key k;
    
    while(getline(file, linha)){
        stringstream ss;
        //stringstream ler linha
        ss << linha;

        //a separamos por chaves
        while(ss >> k){
            teste[k] = teste[k]+1;
        }
            

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
    ChainedHashTable<string, int> hashEncTESTE;
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
    
    //agora teste de insercao atraves de um arquivo
    fstream file("bibliateste.txt", ios::in);
    lerArquivo(file, hashEncTESTE);
    
    ChainedHashTable<string, int> teslento;
    fstream file2("bibilaateste2.txt", ios::in);

    lerArquivolento(file2, teslento);

    cout << hashEncTESTE.buscaint() << endl << teslento.buscaint();

    return 0;
}

