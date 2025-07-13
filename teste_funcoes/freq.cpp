#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

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

void readFile(fstream &file, RBtree<string, int>& teste) {
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
            if (!key.empty())
                if(!teste.contains(key))
                    teste.add(key, 1);
                
                teste.at(key)++;
        }
    }
    file.close();
}

void gerarArquivo(vector<pair<string, int>> dados, ofstream &file){

    for(auto& node : dados){
        file << node.first << " " << node.second << endl;
    }

}

void frequencia(MapAvl<string, int> dic, ifstream &file){

    readFile(file, dic);

    vector<pair<string, int>> vetorDic = dic.vetorize();

    ofstream fileOut("teste.dic");

    gerarArquivo(vetorDic, fileOut);
}

int main() {
    
    //criacao das estruturas 
    ChainedHashTable<string, int> hashEncTESTE;
    OpenHashTable<int, string> hashOpenTESTE;
    AvlTree<string, int> TreeAvlTESTE;
    RBtree<string, int> TreeRbTeste;

    string name = "teste.txt";
    
    //agora teste de insercao atraves de um arquivo
    fstream file("kjv-bible.txt", ios::in);
    vector<pair<string, int>> dados;
    //lerArquivo(file, hashEncTESTE, dados);
    readFile(file, TreeRbTeste);

    vector<pair<string, int>> rb = TreeRbTeste.vetorize();

    //TODO fazer uma funca begin para cada uma das estruturas
    TreeRbTeste.impressao("xique_xique2.txt");
    
    cout << TreeRbTeste.size();

    IcuComparator comparadorPtBR(icu::Locale("pt_BR"));

    std::sort(rb.begin(), rb.end(), 
        [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
            // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
            return comparadorPtBR(a.first, b.first);
        }
    );
    
    // 3. PRONTO! O seu 'vetorDePalavras' agora está perfeitamente ordenado.
    // Agora você pode imprimir o conteúdo do vetor para um arquivo.

    //ETAPAS
    
    //ler o arquivo com a estrutura

    //vetorizar a estrutura

    //saber se precisa ordenar

    //se precisar   - ordena + custo

    //passa a o vetor para um arquivo agora

    return 0;
}