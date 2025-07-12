#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdexcept>

using namespace std;

//estruturas
#include "dicionarioavl.hpp"
#include "dicionariochained.hpp"
#include "dicionariorb.hpp"
#include "dicionarioopen.hpp"

//frencia
#include "freq.hpp"

int main(int argc, char* argv[]) {

    cout << "numero de parametros = " << argc << endl;

    for(int i = 0; i < argc; ++i) {
        cout << "argumento [" << i << "] = " << argv[i] << endl;
    } 
    string primeiro = argv[0];
    string segundo = argv[1];
    string terceiro=  argv[2];
    
    //primeiro parametro    
    cout << terceiro;

    //segundo - tipo da estrutra a ser utilizada
    //terceiro - string a ser lida
    //abre arquivo no modo leitura
    ifstream file(terceiro);

    if(!file.is_open())
        throw std::invalid_argument("arquivo nao existe");
    
    if(segundo == "dicionarioAvl"){
        MapAvl<string, int> dic;
        frequencia(dic, file);

    }/*else if(segundo == "dicionarioRb"){
        MapAvl<string, int> dic;
        gerarArquivo(dic, terceiro);
    }else if(segundo == "dicionarioOpen"){
        MapAvl<string, int> dic;
        gerarArquivo(dic, terceiro);

    }else if(segundo == "dicionarioChained"){
        MapAvl<string, int> dic;
        gerarArquivo(dic, terceiro);

    }*/
    else 
        cout << "Nome da estrutura errado ou estrutura inexistente" 
        << "As estruturas tem os seguintes nomes" << endl;

    return 0;
}
