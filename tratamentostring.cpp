#include <iostream>
#include <string>
#include <vector>

#include <unicode/unistr.h>  // for UnicodeString
#include <unicode/ustream.h> // for supporting output of UnicodeString
#include <unicode/ucnv.h>    // For text file encoding conversions
#include <fstream>
#include <sstream>

using namespace std;

int main() {

    /* REGRAS PARA TRATAMENTO DE STRING:
    Sinais de pontuação (aspas simples, aspas duplas, sinal de interrogação, sinal
    de exclamação, vı́rgula, dois-pontos, ponto final, sı́mbolos aritméticos tais como
    igualdade, soma, subtração e outros,) devem ser desconsiderados, ou seja, não
    são entradas do dicionário, nem fazem parte de palavras.
    • O caso do hifen é mais especial. Ele pode ser usado num texto para indicar a
    fala de um personagem. Neste caso, ele pode ser descartado. Em português, o
    hı́fen é usado em palavras, tais como “mostrá-lo”. Neste caso, acho prudente o
    hı́fen ser parte da palavra. Logo, neste caso, mostrá-lo seria uma entrada do
    dicionário.
    */
    string teste1 = "TOP-SECRET file (located at C: Archives_2025  [Project_Janus]log_007.txt) from Dr. Eva Rostova read: My team's main objective, as per directive {Alpha-9}, is to analyze the artifact; its cost is estimated at over $2,500,000! I've only got a 48-hour window (isn't that 'crazy'?) to get this done.";

    //TESTE INICIAL

    //LER UM ARQUIVO E VER COMO ELE IMPRIME AQUILO
    ifstream file("stringtst.txt");
    icu::UnicodeString linha;

    string utf8line;
    UConverterUnicodeSet(utf8line);
    

    vector<string> vec_names;

    while(getline(file, utf8line)) {
        vec_names.push_back(utf8line);
        
    }

    file.close();

    vector<icu::UnicodeString> vec_unicode_names;

    for(auto& str : vec_names){

        icu::UnicodeString name = icu::UnicodeString::fromUTF8(str);
        vec_unicode_names.push_back(name);
    }

    // obtem o numero de caracteres numa UnicodeString
    for(auto& uStr : vec_unicode_names) {
        int32_t size = uStr.length();
        string utf8str;
        for(int i=0;i<utf8str.size();i++){

        }
        uStr.toUTF8String(utf8str); // converte a UnicodeString para UTF-8
        cout << "numero de caracteres da string " << utf8str << " é " << size << "\n";
    }

    //USO DO UNICODE SET PARA RETIRAR O QUE EU NAO QUERO

    
    return 0;
}