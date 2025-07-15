#include <iostream>
#include <string>
#include <unicode/unistr.h>
#include <unicode/uniset.h>
#include <unicode/ustream.h> // Para impressão direta
#include <unicode/uclean.h>   // Para u_cleanup
#include <fstream>
#include <sstream>

using namespace std;
int main() {

    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[[:L:]']");
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);

    //Teste de leitura de arquivo com tratamento de string
    std::ifstream file("stringtst.txt");
    std::string utf8line;

    while(getline(file, utf8line)) {
        
        
        stringstream ss(utf8line);
        string word;
        
        while (ss >> word) {

            //CONVERTE STRING PARA UNICODE
            icu::UnicodeString tratar = icu::UnicodeString::fromUTF8(word);
            //FAZ TRATAMENTO DE UNICODESET
            icu::UnicodeString palavra_limpa;

        for (int32_t i = 0; i <tratar.length(); ++i) {
            int32_t e = i + 1;
            UChar32 ch = tratar.char32At(i);
            UChar32 chAfter = tratar.char32At(e);

            if (wordChars.contains(ch)){
                palavra_limpa.append(ch);
            }

            //CASO EM QUE O CARACTER QUE VEM DEPOIS É UMA LETRA
            if(ch=='-' && wordChars.contains(chAfter)){
                palavra_limpa.append('-');
            }
            if (U_IS_SUPPLEMENTARY(ch)) {
                ++i; // Avança um a mais em caso de par de substituição (UTF-16)
            }
         }


            //CONTINUAMOS PARA O RESTANTE

            // Regra do hífen: se a "palavra" for apenas um hífen, ignore.
            if (word != "-") {
                palavra_limpa.toLower();
                // A 'word' aqui está limpa e válida de acordo com suas regras.
                // Você pode convertê-la de volta para UnicodeString se precisar.
                cout << "Palavra encontrada: " << palavra_limpa << "\n";
            }
        }
    }
    
    u_cleanup();
    return 0;
}
