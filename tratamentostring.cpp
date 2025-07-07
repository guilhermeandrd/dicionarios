#include <iostream>
#include <string>


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
    string teste1 = "TOP-SECRET file (located at C:\ Archives_2025 \ [Project_Janus]\log_007.txt) from Dr. Eva Rostova read: My team's main objective, as per directive {Alpha-9}, is to analyze the artifact; its cost is estimated at over $2,500,000! I've only got a 48-hour window (isn't that 'crazy'?) to get this done.";
    return 0;
}