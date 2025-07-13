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

//frencia
#include "freq.hpp"

int main(int argc, char* argv[]) {
    
    string primeiro = argv[0];
    string segundo = argv[1];
    string terceiro=  argv[2];
    string nameFile = argv[3];
    
    //primeiro parametro    
    //cout << terceiro;

    //segundo - tipo da estrutra a ser utilizada
    //terceiro - string a ser lida
    //abre arquivo no modo leitura
    ifstream file(terceiro);

    if(!file.is_open())
        throw std::invalid_argument("arquivo nao existe");
    
    if(segundo == "dicionarioAvl"){
        MapAvl<string, int> dic;
        frequencia(dic, file, nameFile);

    }else if(segundo == "dicionarioRb"){
        MapRb<string, int> dic;
        frequencia(dic, file, nameFile);
    }else if(segundo == "dicionarioOpen"){
        OpenHashMap<string, int> dic;
        frequencia(dic, file, nameFile);

    }else if(segundo == "dicionarioChained"){
        ChainedHashMap<string, int> dic;
        frequencia(dic, file, nameFile);

    }
    else 
        cout << "Nome da estrutura errado ou estrutura inexistente" 
        << "As estruturas tem os seguintes nomes" << endl;

    return 0;
}
