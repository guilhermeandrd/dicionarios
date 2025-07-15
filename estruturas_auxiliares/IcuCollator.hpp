#include <iostream>
#include <unicode/coll.h> //para uso do collator


//TODO revisar isso aqui e comentar
struct IcuComparator{

    //ponteiro para o comparator icu
    mutable icu::Collator* collator;

    //aqui vamos instanciar um collator para o idioma especifico
    //que foi passado por locale
    //construtor
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

    bool operator()(const std::string& a, const std::string& b) const{
        
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


    //destrutor para collator
    ~IcuComparator(){
        delete collator;
    }
};