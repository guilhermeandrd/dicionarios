#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>

#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <unicode/ustream.h>
#include <unicode/uclean.h>

#include "estruturas_auxiliares/ChainedHashTable.hpp"
#include "estruturas_auxiliares/OpenHashTable.hpp"
#include "estruturas_auxiliares/RBTree.hpp"
#include "estruturas_auxiliares/AVLTree.hpp"
#include "estruturas_auxiliares/IcuCollator.hpp"
#include "dicionarioavl.hpp"
#include "dicionariochained.hpp"
#include "dicionarioopen.hpp"
#include "dicionariorb.hpp"

using namespace std;

#ifndef FREQ_HPP
#define FREQ_HPP

bool ordena = false;

template <typename Class>
void readFile(ifstream &file, Class &teste) {
    string linha;
    string k;
    
    // CONFIGURAÇÃO DO UNICODE-SET - Adicione o smart quote (') como caractere válido
    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[:L:]['’]"); // Inclui ambos tipos de apóstrofos
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);
    
    while(getline(file, linha)) {
        stringstream ss;
        ss << linha;
        
        while(ss >> k) {
            icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(k);
            icu::UnicodeString cleanWord;
            
            for (int32_t i = 0; i < tratar.length(); ++i) {
                int32_t e = i + 1;
                UChar32 ch = tratar.char32At(i);
                UChar32 chAfter = tratar.char32At(e);
                
                // Tratamento para smart quote (')
                //se for um smart code e a proxima letra tiver no 
                if (ch == 0x2019) { // Unicode para smart quote (')
                    // Verifica se é um smart quote válido (entre letras)
                   // if (wordChars.contains(tratar.char32At(i-1))) {
                        cleanWord.append('\'');
                   // }
                }
                
                if (wordChars.contains(ch)) {
                    cleanWord.append(ch);
                }
                
                // Tratamento para hífen
                if (ch == '-' && wordChars.contains(chAfter)) {
                    cleanWord.append('-');
                }
                
                if (U_IS_SUPPLEMENTARY(ch)) {
                    ++i;
                }
            }
            
            cleanWord.toLower();
            string key;
            cleanWord.toUTF8String(key);
            if (!key.empty())
                teste[key]++;
        }
    }
    file.close();
}


void readFile(ifstream &file, MapAvl<string, int>& teste) {
    string linha;
    string k;
    
    // CONFIGURAÇÃO DO UNICODE-SET - Adicione o smart quote (') como caractere válido
    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[:L:]['’]"); // Inclui ambos tipos de apóstrofos
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);
    
    while(getline(file, linha)) {
        stringstream ss;
        ss << linha;
        
        while(ss >> k) {
            icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(k);
            icu::UnicodeString cleanWord;
            
            for (int32_t i = 0; i < tratar.length(); ++i) {
                int32_t e = i + 1;
                UChar32 ch = tratar.char32At(i);
                UChar32 chAfter = tratar.char32At(e);
                
                // Tratamento para smart quote (')
                //se for um smart code e a proxima letra tiver no 
                if (ch == 0x2019) { // Unicode para smart quote (')
                    // Verifica se é um smart quote válido (entre letras)
                   // if (wordChars.contains(tratar.char32At(i-1))) {
                        cleanWord.append('\'');
                   // }
                }
                
                if (wordChars.contains(ch)) {
                    cleanWord.append(ch);
                }
                
                // Tratamento para hífen
                if (ch == '-' && wordChars.contains(chAfter)) {
                    cleanWord.append('-');
                }
                
                if (U_IS_SUPPLEMENTARY(ch)) {
                    ++i;
                }
            }
            
            cleanWord.toLower();
            string key;
            cleanWord.toUTF8String(key);
            if (!key.empty()){
                if(!teste.contains(key)){
                    teste.add(key, 0);
                }
                teste.at(key)++;
            }
        }
    }
    file.close();
}




void gerarArquivo(vector<pair<string, int>> dados, string nameFile = "impressaoDic"){

    //tratamento do nome do arquivo
    if(nameFile == "impressaoDic" || nameFile.empty()){
        time_t now = time(0);
        tm* ltm = localtime(&now);

        std::ostringstream oss;

        oss << nameFile << ltm->tm_hour << "-" 
        << ltm->tm_min << "-" 
        << ltm->tm_sec << "-" << ".txt";    
        nameFile = oss.str();
    }


    ofstream file(nameFile);

    if(!file.is_open())
        throw std::runtime_error("erro ao abrir o arquivo de frequencia");

    for(auto& node : dados){
        file << node.first << " " << node.second << endl;
    }

}

void frequencia(OpenHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    if(!fileOut.is_open())
         throw std::runtime_error("arquivo não foi aberto");
        
    if(ordena){
        //TODO sort com icucomparator
    }else{
        sort(vetorDic.begin(), vetorDic.end());
    }

    //TODO diferenciar as tabelas das arvores por que as tabelas sempre ordenam
    gerarArquivo(vetorDic, nameFile);
}

void frequencia(ChainedHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    if(!fileOut.is_open())
         throw std::runtime_error("arquivo não foi aberto");
    
    if(ordena){
        //TODO sort com icucomparator
    }else{
        sort(vetorDic.begin(), vetorDic.end());
    }

    //TODO diferenciar as tabelas das arvores por que as tabelas sempre ordenam
    gerarArquivo(vetorDic, nameFile);
}

void frequencia(MapRb<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    if(!fileOut.is_open())
         throw std::runtime_error("arquivo não foi aberto");

    if(ordena){
        //TODO sort com icucomparator
        sort(vetorDic.begin(), vetorDic.end());
    }

    //TODO diferenciar as tabelas das arvores por que as tabelas sempre ordenam
    gerarArquivo(vetorDic, nameFile);
}

void frequencia(MapAvl<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    if(!fileOut.is_open())
         throw std::runtime_error("arquivo não foi aberto");
    
    if(ordena){
        //TODO sort com icucomparator
        sort(vetorDic.begin(), vetorDic.end());
    }

    //TODO diferenciar as tabelas das arvores por que as tabelas sempre ordenam
    gerarArquivo(vetorDic, nameFile);
}

/*
FLUXO DE ORDENACAO

TABELAS
    SE TIVER ACENTO
        ORDENA COM MAIS CUSTO
    SE NAO
        ORDENA COM MENOS CUSTO

ARVORES
    SE TIVER ACENTO
        ORDENA COM MAIS CUSTO
    SE NAO
        NAO ORDENA
*/


#endif //END_OF_FREQ_HPP