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
    // String de teste original
    
    /*icu::UnicodeString palavra_suja = UNICODE_STRING_SIMPLE("Olá, mundo-123! Bem-vindo.");

    std::cout << "--- INÍCIO DO TESTE ---" << std::endl;
    std::cout << "String Original: " << palavra_suja << std::endl;

    const icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[[:L:]-]");
    
    std::cout << "Padrão UnicodeSet usado: " << pattern << std::endl;

    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);

    if (U_FAILURE(status)) {
        std::cerr << "ERRO: Falha ao criar o UnicodeSet. Código do erro: " 
                  << u_errorName(status) << std::endl;
        u_cleanup();
        return 1;
    }

    std::cout << "UnicodeSet criado com sucesso." << std::endl;

    // --- Limpeza da string ---
    icu::UnicodeString palavra_limpa;

    for (int32_t i = 0; i < palavra_suja.length(); ++i) {
        UChar32 ch = palavra_suja.char32At(i);

        if (wordChars.contains(ch)) {
            palavra_limpa.append(ch);
        }

        //TODO fazer tratametno de palavra por palavra usando sstream
        //TODO fazer tratamento do "-"
        if (U_IS_SUPPLEMENTARY(ch)) {
            ++i; // Avança um a mais em caso de par de substituição (UTF-16)
        }
    }

    std::cout << "-------------------------" << std::endl;
    std::cout << "String Limpa:    " << palavra_limpa << std::endl;
    std::cout << "--- FIM DO TESTE ---" << std::endl;*/

    icu::UnicodeString pattern = UNICODE_STRING_SIMPLE("[[:L:] ]");
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeSet wordChars(pattern, status);

    //Teste de leitura de arquivo com tratamento de string
    std::ifstream file("stringtst.txt");
    std::string utf8line;

    while(getline(file, utf8line)) {

        // Converte a linha para UnicodeString
        //icu::UnicodeString u_line = icu::UnicodeString::fromUTF8(utf8line);
        
        // Aplica a limpeza inicial: remove toda pontuação exceto o hífen.
        //limpeza geral
        

        //wordChars.retainAll(u_line); talvez seja uma linha inutil
        
        //limpeza especifica do caso do "-"


        // Para quebrar a linha em palavras, convertemos de volta para string
        // e usamos um stringstream.
        //std::string cleaned_line_utf8;
        
        
        stringstream ss(utf8line);
        string word;
        
        // PASSO 2 e 3: Tokenização e análise por palavra
        //TODO fazer o tratamento aqui deve ser mais eficiente
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

            //TODO fazer tratamento do "-"
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
                //TODO deixar string minuscula
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
