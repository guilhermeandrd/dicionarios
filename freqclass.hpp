/**
 * @file freqclass.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Árvore Binária de Busca Balanceada (AVL)
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <unicode/ustream.h>
#include <unicode/uclean.h>
#include <unicode/uchar.h>

#include "estruturas_auxiliares/IcuCollator.hpp"
#include "dicionarioavl.hpp"
#include "dicionariochained.hpp"
#include "dicionarioopen.hpp"
#include "dicionariorb.hpp"

#ifndef FREQ_HPP
#define FREQ_HPP

class Frequencia{

private:
    bool ordena = false;
    size_t larguraMaxima = 0;

    template <typename Class>
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    void readFile(ifstream &file, Class &teste) {
        string linha;
        string k;
        
        icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[:L:]"); 
        UErrorCode status = U_ZERO_ERROR;
        icu::UnicodeSet wordChars(pattern, status);
        UErrorCode statusSort = U_ZERO_ERROR;
        icu::UnicodeSet wordSort("[[a-z-][A-Z]]", statusSort);

        while(getline(file, linha)) {
            stringstream ss;
            ss << linha;
            
            while(ss >> k) {
                icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(k);
                icu::UnicodeString cleanWord;
                
                for (int32_t i = 0; i < tratar.length(); ++i) {
                    int32_t e = i + 1;
                    int32_t f = i -1;
                    UChar32 ch = tratar.char32At(i);
                    UChar32 chAfter = tratar.char32At(e);
                    UChar32 chBefore = tratar.char32At(f);
                    
                    if (wordChars.contains(ch)) {
                        cleanWord.append(ch);
                    }
                    
                    // Tratamento para hífen
                    //TODO pensar num tratamento masi robusto para travessão
                    if (u_isalpha(chAfter) && (ch == '-' || ch == 0x2014) && u_isalpha(chBefore)) {
                        cleanWord.append('-');
                    }


                    if(!wordSort.contains(ch) && ch != 0x2019 && wordChars.contains(ch)){
                        ordena = true;
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
                //se nao tem if !contains -> insere com valor 0. at ++;
                icu::UnicodeString keyUni = icu::UnicodeString::fromUTF8(key);

                size_t lengthCW = cleanWord.length();
                if(lengthCW > larguraMaxima){
                    larguraMaxima = cleanWord.length();
                }
            }
        }
        file.close();
    }


    //TODO verificar se o relogio da funcao para o que o arquivo pediu
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    void gerarArquivo(vector<pair<string, int>> dados, string nameFile = "impressaoDic", auto duracao = std::chrono::high_resolution_clock::now(), bool temRotacao = false, size_t metrica1= 0, size_t metrica2 = 0){
        
        //auto fim = std::chrono::high_resolution_clock::now();


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

        //auto duracao = fim - inicio;
        auto duracao_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duracao);    
        size_t larguraColuna = larguraMaxima + 4;
        
        if(temRotacao){
            file << "A ESTRUTURA TEM AS SEGUINTES INFORMAÇÕES: " << endl
            << "tempo de compilação: " << duracao_ns.count() << " nanosegundos"<< endl
            << "números de comparações de chaves: " << metrica1 << endl
            << "número de rotações:" << metrica2 << endl
            << endl;
            //cabeçalho da tabela hash
        }else{
            file << "A ESTRUTURA TEM AS SEGUINTES INFORMAÇÕES: " << endl
            << "tempo de compilação: " << duracao_ns.count() << " nanosegundos"<< endl
            << "números de comparações de chaves: " << metrica1 << endl
            << "número de colisões: " << metrica2 << endl
            << endl;
        }
        file << std::left << std::setw(larguraColuna) << "Palavra" << "Frequencia" << endl;
        
        file << string(larguraColuna + 12, '-') << endl;
        
        for(auto& node : dados){
            
            icu::UnicodeString palavraAcentuada = icu::UnicodeString::fromUTF8(node.first);
            size_t lengthNF = node.first.length();
            size_t lengthPA = palavraAcentuada.length();

            if(lengthNF > lengthPA){
                size_t larguraAcentuada = larguraColuna + (lengthNF - lengthPA);
                file << left << setw(larguraAcentuada) << node.first << node.second << endl;
            }else{
                file << left << setw(larguraColuna) << node.first << node.second << endl;
            }

        }
    }

public:

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Frequencia(OpenHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

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
            
            cout << "foi ordenado por icu" << endl;
        }else{
            sort(vetorDic.begin(), vetorDic.end());
        }

        //fim da contagem (tabela foi gerada agora vamos só)
        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = fim - inicio;

        gerarArquivo(vetorDic, nameFile, duracao, false, dic.counter_comparator(), dic.counter_collision());
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Frequencia(ChainedHashMap<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

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

        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = fim - inicio;

    
        gerarArquivo(vetorDic, nameFile, duracao, false, dic.counter_comparator(), dic.counter_collision());
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Frequencia(MapRb<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){

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

        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = fim - inicio;

        gerarArquivo(vetorDic, nameFile, duracao, true, dic.counter_comparator(), dic.counter_rotation());
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Frequencia(MapAvl<string, int> dic, ifstream &file, string nameFile = "impressaoDic"){
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

        auto fim = std::chrono::high_resolution_clock::now();

        auto duracao = fim - inicio;
        gerarArquivo(vetorDic, nameFile, duracao, true, dic.counter_comparator(), dic.counter_rotation());
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



};


#endif //END_OF_FREQ_HPP