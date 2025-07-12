#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

//estruturas bases

#include "estruturas_auxiliares/ChainedHashTable.hpp"
#include "estruturas_auxiliares/OpenHashTable.hpp"
#include "estruturas_auxiliares/RBTree.hpp"
#include "estruturas_auxiliares/AVLTree.hpp"

int main() {

    //dados para se usados nos testes
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
    RBtree<int, string> testeRb;
    AvlTree<int, string> testeAvl;
    ChainedHashTable<int, string> testeChained;
    OpenHashTable<int, string> testeOpen;

    //insercao dos dados
    for(auto& node : dadosDeTeste){
        testeAvl.insert(node.first, node.second);
        testeRb.insert(node.first, node.second);
        testeChained.add(node.first, node.second);
        testeOpen.add(node.first, node.second);
    }

    //criacao dos vetores
    vector<pair<int, string>> dadosRb = testeRb.vetorize();
    vector<pair<int, string>> dadosAvl = testeAvl.vetorize();
    vector<pair<int, string>> dadosChained = testeChained.vetorize();
    vector<pair<int, string>> dadosOpen = testeOpen.vetorize();

    //impressao dos vetores
    ofstream file("testevetor.txt");
        //da rb
        file <<   "RUBRO NEGRA:" << endl;
        for(auto& node : dadosRb){
            file << node.first << " " << node.second << endl;
        }

        //da avl
        file <<   "AVL:" << endl;

        for(auto& node : dadosAvl){
            file << node.first << " " << node.second << endl;
        }


        //da chained
        file <<   "CHAINED HASH:" << endl;

        for(auto& node : dadosChained){
            file << node.first << " " << node.second << endl;
        }


        //da open
        file <<   "OPEN HASH:" << endl;

        for(auto& node : dadosOpen){
            file << node.first << " " << node.second << endl;
        }

    //ordenacao dos vetores das tabelas
    sort(dadosChained.begin(), dadosChained.end());
    sort(dadosOpen.begin(), dadosOpen.end());

    for(int i=0; i<dadosAvl.size(); i++){
        if(!(dadosOpen[i]==dadosChained[i]&&dadosChained[i]==dadosAvl[i]&&dadosAvl[i]==dadosRb[i]))
            throw logic_error("erro na ordenacao");
    }

    return 0;
}