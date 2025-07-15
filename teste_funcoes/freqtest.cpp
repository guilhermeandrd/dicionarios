#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <unicode/ustream.h> // Para impressão direta
#include <unicode/uclean.h>   // Para u_cleanup

#include "estruturas_auxiliares/ChainedHashTable.hpp"
#include "estruturas_auxiliares/OpenHashTable.hpp"
#include "estruturas_auxiliares/RBTree.hpp"
#include "estruturas_auxiliares/AVLTree.hpp"
#include "estruturas_auxiliares/IcuCollator.hpp"

using namespace std;

template <typename Key, typename Value>
void lerArquivo( fstream &file, ChainedHashTable<Key, Value>& teste, vector<pair<string, int>> &vetor){
    string linha;
    Key k;
    
    //CONFIGURAÇÃO DO UNICODE-SET
    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[[:L:] ]");
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);
    
    while(getline(file, linha)){
        stringstream ss;
        //stringstream ler linha
        ss << linha;
        
        //a separamos por chaves
        //fazemos tratamento de string
        while(ss >> k){
            icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(k);

            icu::UnicodeString cleanWord;

            for (int32_t i = 0; i <tratar.length(); ++i) {
                int32_t e = i + 1;
                UChar32 ch = tratar.char32At(i);
                UChar32 chAfter = tratar.char32At(e);

                if (wordChars.contains(ch)){
                    cleanWord.append(ch);
                }

                //CASO EM QUE O CARACTER QUE VEM DEPOIS É UMA LETRA
                if(ch=='-' && wordChars.contains(chAfter)){
                    cleanWord.append('-');
                }
                if (U_IS_SUPPLEMENTARY(ch)) {
                    ++i; // Avança um a mais em caso de par de substituição (UTF-16)
                }
            }
            cleanWord.toLower();
            string key;
            cleanWord.toUTF8String(key);
            teste[key]++;
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

void lerArquivo( fstream &file, RBtree<string, int>& teste){
    string linha;
    string k;
    
    //CONFIGURAÇÃO DO UNICODE-SET
    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[:L:][']");
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);
    
    while(getline(file, linha)){
        stringstream ss;
        //stringstream ler linha
        ss << linha;
        //a separamos por chaves
        //fazemos tratamento de string
        while(ss >> k){
            icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(k);
            icu::UnicodeString cleanWord;
            cleanWord.findAndReplace("’", "'");
            
            for (int32_t i = 0; i <tratar.length(); ++i) {
                int32_t e = i + 1;
                UChar32 ch = tratar.char32At(i);
                UChar32 chAfter = tratar.char32At(e);
                
                //tratamento para smart quote

                /* se a minha palavra tiver a substring "’"
                entao eu a guardo
                no final da iteração eu insiro onde ela deve ficar e ando quantos indici preicisar*/
                

                if (wordChars.contains(ch)){
                    cleanWord.append(ch);
                }

                //CASO EM QUE O CARACTER QUE VEM DEPOIS É UMA LETRA
                if(ch=='-' && wordChars.contains(chAfter)){
                    cleanWord.append('-');
                }

                if (U_IS_SUPPLEMENTARY(ch)) {
                    ++i; // Avança um a mais em caso de par de substituição (UTF-16)
                }
            }
            cleanWord.toLower();
            string key;
            cleanWord.toUTF8String(key);
            if(!key.empty())
                teste[key]++;
        }
            

    }

    file.close();

}

void lerArquivoApos(fstream &file, RBtree<string, int>& teste) {
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
                        cleanWord.append(ch);
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

void gerarArquivo(vector<pair<string, int>> dados, ofstream file){
    
    for(auto& node : dados){
        file << node.first << " " << node.second << endl;
    }

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
    AvlTree<string, int> TreeAvlTESTE;
    RBtree<string, int> TreeRbTeste;

    //inicializacao das estruturas
    for(auto& node : dadosDeTeste){
        //hashEncTESTE.add(node.first, node.second);
        hashOpenTESTE.add(node.first, node.second);
        //TreeAvlTESTE.insert(node.first, node.second);
        //TreeRbTeste.insert(node.first, node.second);
    }
    string name = "teste.txt";
    
    //agora teste de insercao atraves de um arquivo
    fstream file("kjv-bible.txt", ios::in);
    vector<pair<string, int>> dados;
    //lerArquivo(file, hashEncTESTE, dados);
    lerArquivoApos(file, TreeRbTeste);

    vector<pair<string, int>> rb = TreeRbTeste.vetorize();

    TreeRbTeste.impressao("xique_xique2.txt");
    
    cout << TreeRbTeste.size();

    IcuComparator comparadorPtBR(icu::Locale("pt_BR"));

    //funca sort com lambda que agora sabe o comparar corretamente
    std::sort(rb.begin(), rb.end(), 
        [&comparadorPtBR](const std::pair<string, int>& a, const std::pair<string, int>& b) {
            // A lambda captura o comparador e o usa para comparar as chaves (as palavras)
            return comparadorPtBR(a.first, b.first);
        }
    );
    // 3. PRONTO! O seu 'vetorDePalavras' agora está perfeitamente ordenado.
    // Agora você pode imprimir o conteúdo do vetor para um arquivo.
    gerarArquivo(rb, ofstream ("teste2.txt"));

    return 0;
}

