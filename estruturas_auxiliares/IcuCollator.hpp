/**
 * @file IcuCollator.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Estrutura do Icu Comparator
 * @version 0.1
 * @date 2025-07-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ICUCOLLATOR_HPP
#define ICUCOLLATOR_HPP

#include <iostream>
#include <unicode/coll.h> //para uso do collator


/**
 * @brief Estrutura Icu Comparator.
 * Feita para comparar corretamente palavras com acento.
 * Por exemplo: É e E. Com essa estrutura, ele terão a mesma 
 * ordem, ficando em locais corretos quando ordenamos alfabeticamente.
 * É usada na função Sort, para ordenar corretamente textos em português.
 */
struct IcuComparator{

    //ponteiro para o comparator icu
    mutable icu::Collator* collator;

    //aqui vamos instanciar um collator para o idioma especifico
    //que foi passado por locale
     /**
     * @brief Construtor que instancia um collator para um idioma especifico.
     * É passado um objeto locale do Icu e com ele é feito um collator
     * para o idioma do local.
     * 
     * 
     * @param locale := idioma/local que o collator vai ser instanciada
     *
     */
    IcuComparator(const icu::Locale& locale){
        //boa prática para sabermos quando deu erro
        //no caso quando o collator nao foi criado de alguma maneira
        UErrorCode status = U_ZERO_ERROR;
        collator = icu::Collator::createInstance(locale, status);

        //se houve falha na criacao
        if(U_FAILURE(status)){
            throw std::runtime_error("Houve erro na criação do collator");
            collator = nullptr;
        }

    }

     /**
     * @brief Sobrecarga do operator () para comparação de strings.
     * Com isso, as strings agora podem ser comparadas levando em 
     * conta a ordem alfabética do local entre outras nuances da linguagem.
     * 
     * @param a string que vai ser comparada
     * 
     * @param b string que vai ser comparada
     * 
     * @return True se e somente se a vier antes de b na ordem da linguagem escolhida
     * 
     */
    bool operator()(const std::string& a, const std::string& b) const{
        
        //fallback para caso de dar erro
        if(!collator){
            UErrorCode status = U_ZERO_ERROR;
            collator = icu::Collator::createInstance(icu::Locale("en_USA"), status);
            return a < b;
        }

        //convertemos as strings para unicode string
        //assim podemos usar as funções do icu
        icu::UnicodeString ustr_a = icu::UnicodeString::fromUTF8(a);
        icu::UnicodeString ustr_b = icu::UnicodeString::fromUTF8(b);
        
        UErrorCode status = U_ZERO_ERROR;
        
        //com a funcao compare do collator que é um ponteiro
        //verificamos se a vem antes de b
        //retornando true se assim for
        return collator->compare(ustr_a, ustr_b, status) == UCOL_LESS;
    }

     /**
     * @brief Destrutor para objeto collator
     * 
     * 
     *
     */
    //destrutor para collator
    ~IcuComparator(){
        delete collator;
    }
};

#endif //END_OF_ICU_COLLATOR