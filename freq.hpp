#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>

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
//TODO soh falta a formatação
string maior = "";

template <typename Class>
void readFile(ifstream &file, Class &teste) {
    string linha;
    string k;
    
    // CONFIGURAÇÃO DO UNICODE-SET - Adicione o smart quote (') como caractere válido
    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[:L:]['’]"); // Inclui ambos tipos de apóstrofos
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);
    icu::UnicodeString patternSort = UNICODE_STRING_SIMPLE("a-z, A-Z, '");
    UErrorCode statusSort = U_ZERO_ERROR;
    icu::UnicodeSet wordSort(patternSort, statusSort);

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

                if(!wordSort.contains(ch)){
                    ordena = true;
                }
                
                if (U_IS_SUPPLEMENTARY(ch)) {
                    ++i;
                }
            }
            
            cleanWord.toLower();
            string key;

            //TODO ver se é a maior
            if(key.size() > maior.size())
                maior = key;


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




void gerarArquivo(vector<pair<string, int>> dados, string nameFile = "impressaoDic", auto inicio = std::chrono::high_resolution_clock::now(), bool temRotacao = false, size_t metrica1= 0, size_t metrica2 = 0){

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


    //CABECAO DO ARQUIVO
    //cabeçalho da avl
    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = fim - inicio;
    auto duracao_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duracao);    
    
    if(temRotacao){
        file << "A ESTRUTURA TEM AS SEGUINTES INFORMAÇÕES: " << endl
        << "tempo de compilação: " << duracao_ns.count() << " nanosegundos"<< endl
        << "números de comparações de chaves: " << metrica1 << endl
        << "número de rotações:" << metrica2 << endl
        << endl << "FREQUENCIA: " << endl;
    //cabeçalho da tabela hash
    }else{
        file << "A ESTRUTURA TEM AS SEGUINTES INFORMAÇÕES: " << endl
        << "tempo de compilação: " << duracao_ns.count() << " nanosegundos"<< endl
        << "números de comparações de chaves: " << metrica1 << endl
        << "número de colisões: " << metrica2 << endl
        << endl << "FREQUENCIA: " << endl;
    }
    
    for(auto& node : dados){
        file << node.first << " " << node.second << endl;
    }

    //TODO colocar ponteiro no comeco para colocar o cabeçalho

}

void frequencia(OpenHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    //inicia relogio de contagem
    auto inicio = std::chrono::high_resolution_clock::now();


    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

        
    if(ordena){
        IcuComparator comparadorPtBR(icu::Locale("pt_BR"));

        std::sort(vetorDic.begin(), vetorDic.end(), 
            [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
                // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
                return comparadorPtBR(a.first, b.first);
            });        
    }else{
        sort(vetorDic.begin(), vetorDic.end());
    }

    gerarArquivo(vetorDic, nameFile, inicio, false, dic.counter_collision(), dic.counter_collision());

}

void frequencia(ChainedHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    auto inicio = std::chrono::high_resolution_clock::now();

    if(!file.is_open())
    throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);
    
    vector<pair<string, int>> vetorDic = dic.vetorize();

    
    if(ordena){
        //sort com icucomparator
        IcuComparator comparadorPtBR(icu::Locale("pt_BR"));
        std::sort(vetorDic.begin(), vetorDic.end(), 
        [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
            // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
            return comparadorPtBR(a.first, b.first);
        }
    );
    }else{
        sort(vetorDic.begin(), vetorDic.end());
    }
    
    gerarArquivo(vetorDic, nameFile, inicio, false, dic.counter_comparator(), dic.counter_collision());
}

void frequencia(MapRb<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

    auto inicio = std::chrono::high_resolution_clock::now();

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    if(ordena){
        //sort com icucomparator
            IcuComparator comparadorPtBR(icu::Locale("pt_BR"));

    std::sort(vetorDic.begin(), vetorDic.end(), 
        [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
            // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
            return comparadorPtBR(a.first, b.first);
        });    
    }

    gerarArquivo(vetorDic, nameFile, inicio, true, dic.counter_comparator(), dic.counter_rotation());
}

void frequencia(MapAvl<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){
    auto inicio = std::chrono::high_resolution_clock::now();

    if(!file.is_open())
        throw std::runtime_error("arquivo não foi aberto");
    
    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    if(!fileOut.is_open())
         throw std::runtime_error("arquivo não foi aberto");
    
    if(ordena){
        //sort com icucomparator
        IcuComparator comparadorPtBR(icu::Locale("pt_BR"));

        std::sort(vetorDic.begin(), vetorDic.end(), 
            [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
                // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
                return comparadorPtBR(a.first, b.first);
            });       
    }

    gerarArquivo(vetorDic, nameFile, inicio, true, dic.counter_comparator(), dic.counter_rotation());
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