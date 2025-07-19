#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdexcept>

#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <unicode/ustream.h>
#include <unicode/uclean.h>

using namespace std;

//estruturas
#include "dicionarioavl.hpp"
#include "dicionariochained.hpp"
#include "dicionariorb.hpp"
#include "dicionarioopen.hpp"

//frequencia
#include "freqclass.hpp"

#include <chrono>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <functional>


using namespace std;

//TODO teste de inserir um arquivo 100 vezes na estrutura
//TODO teste de buscar algo na estrutura n vezes
//TODO teste  de estresse das árvores
//TODO teste de estresse das tabelas 
//TODO teste de palavras repetidas

int main() {

   ChainedHashMap<string, int> teste;
    auto duracao = chrono::nanoseconds::zero();
    
    ifstream file("estressatabela.txt");
    
    for(int i=0; i < 100; i++){
        auto inicio = std::chrono::high_resolution_clock::now();
        Frequencia(teste, file, "lixo");
        file.open("estressatabela.txt");

        auto fim = std::chrono::high_resolution_clock::now();

        auto tempoGasto = (fim - inicio);

        duracao = duracao + tempoGasto;

        cout << i << endl;
    }

    auto tempoTeste = duracao/100;    

    cout << tempoTeste.count();
    return 0;
}