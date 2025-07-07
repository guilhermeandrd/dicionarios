/**
 * @file ChainedHashTable.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Uma tabela hash com tratamento de colisao por encadeamento exterior
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef CHAINED_HASHTABLE_HPP
#define CHAINED_HASHTABLE_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>


/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por encadeamento exterior (chained hash table).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ChainedHashTable {
private:
    // quantidade de pares (chave,valor)
    size_t m_number_of_elements;

    // tamanho atual da tabela
    size_t m_table_size;

    // O maior valor que o fator de carga pode ter. 
    // Seja load_factor = m_number_of_elements/m_table_size.
    // Temos que load_factor <= m_max_load_factor.
    // Quando load_factor ultrapassa o valor de m_max_load_factor, 
    // eh preciso executar a operacao de rehashing.                   
    float m_max_load_factor;
    int busca;
    // tabela                               
    std::vector<std::list<std::pair<Key,Value>>> m_table;

    // referencia para a funcao de codificacao
    Hash m_hashing;

    //contador de comparaco de chaves
    mutable size_t m_counter_comparator;

    // contador de colisao 
    mutable size_t m_counter_collision;

    /**
     * @brief Retorna o menor numero primo que eh maior que ou igual
     * a x e maior que 2.
     * 
     * @param x := um numero nao negativo
     * @return size_t := um numero primo
     */
    size_t get_next_prime(size_t x) {
        if(x <= 2) return 3;
        x = (x % 2 == 0) ? x + 1 : x;
        bool not_prime = true;
        while(not_prime) {
            not_prime = false;
            for(int i = 2; i <= sqrt(x); i+=2) {
                if(x % i == 0) {
                    not_prime = true;
                    break;
                }
            }
            x += 2;
        }
        return x - 2;
    }

    /**
     * @brief Retorna um inteiro no intervalo [0 ... m_table_size-1].
     * Esta funcao recebe uma chave k e faz o seguinte:
     * (1) computa o codigo hash h(k) usando a 
     *     funcao no atributo privado m_hashing
     * (2) computa um indice no intervalo [0 ... m_table_size-1] 
     *     aplicando o metodo da divisao: h(k) % m_table_size
     * 
     * @param k := um valor de chave do tipo Key
     * @return size_t := um inteiro no intervalo [0 ... m_table_size-1]
     */
    size_t hash_code(const Key& k) const{
        return m_hashing(k) % m_table_size;
    }


public:
    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots.
     * 
     * @param tableSize := o numero de slots da tabela. 
     */
    ChainedHashTable(size_t tableSize = 19, float load_factor = 0.7){
        m_number_of_elements = 0;
        m_table_size = get_next_prime(tableSize);
        m_table.resize(m_table_size);
        if(load_factor <= 0){
            m_max_load_factor = 0.7;
        }else{
            m_max_load_factor = load_factor;
        }

        m_counter_comparator = 0;
        m_counter_collision = 0;
        busca = 0;
    }


    /**
     * @brief Retorna o numero de elementos na tabela hash
     */
    size_t size() const{
        return m_number_of_elements;
    }

    size_t counterComparator(){
        return m_counter_comparator;
    }

    size_t counterCollision(){
        return m_counter_collision;
    }


    /**
     * @brief Retorna um booleano indicando se a tabela esta vazia
     */
    bool empty() const{
        return m_number_of_elements == 0;
    }


    /**
     * @brief Retorna o numero de slots na HashTable (o tamanho da tabela).
     * Um slot eh um campo na tabela hash para o qual 
     * os elementos são atribuidos com base no valor de hashing de sua chave.
     * O numero de slots influencia diretamente no fator de carga da 
     * tabela hash (e, portanto, a probabilidade de colisao).
     * 
     * @return size_t := o numero de slots
     */
    size_t bucket_count() const{
        return m_table_size;
    }


    /**
     * @brief Retorna o numero de elementos armazenados no slot n da tabela.
     * O valor de n deve ser tal que 0 <= n <= m_table_size - 1
     * 
     * @param n := numero do slot
     * @return size_t := numero de elementos no slot n
     */
    size_t bucket_size(size_t n) const{
        if(n < 0 || n >= m_table_size){
            throw std::out_of_range("invalid index");
        }

        return m_table[n].size();
    }


    /**
     * @brief Retorna o numero do slot onde a chave k estaria localizada.
     * 
     * @param k := chave  
     * @return size_t := numero do slot
     */
    size_t bucket(const Key& k) const{
        return hash_code(k);
    }

    /**
     * @brief retorna o valor do fator de carga atual
     */
    float load_factor() const{
        return static_cast<float>(m_number_of_elements) / m_table_size;
    }


    /**
     * @brief retorna o maior valor que o fator de carga pode ter
     */
    float max_load_factor() const{
        return m_max_load_factor;
    }


    /**
     * @brief Todos os pares de (chave,valor) da tabela hash sao deletados: 
     * os destrutores das listas encadeadas sao chamados e eles sao removidos da estrutura de dados, 
     * deixando-o com zero pares na tabela (size() == 0).
     * Tambem zera os contadores e seu numero de elementos.
     */
    void clear(){

        for(auto& list : m_table){
            list.clear();
        }

        m_number_of_elements = 0;
        m_counter_collision = 0;
        m_counter_comparator = 0;
    }


    /**
     * @brief Destroy the Hash Table object
     */
    ~ChainedHashTable() = default;


    /**
     * @brief Insere um novo elemento na tabela hash.
     * Se m_number_of_elements / m_table_size > m_max_load_factor entao a funcao
     * invoca a funcao rehash() passando o dobro do tamanho atual da tabela.
     * O elemento eh inserido somente se a chave dele ja nao estiver presente
     * na tabela (numa tabela hash, as chaves sao unicas).
     * Caso a insercao seja feita, isso incrementa o numero de elementos da tabela em 1 unidade.
     * Retorna true se e somente se a insercao for feita.
     * 
     * @param k := chave
     * @param v := valor 
     */
    bool add(const Key& k, const Value& v){
        
        if(load_factor() >= m_max_load_factor){
            rehash(m_table_size * 2);
        }

        int slot = hash_code(k);

        for(auto p : m_table[slot]){
            this->m_counter_comparator++;
            if(p.first == k){

                return false;
            }
        }

        if(!m_table[slot].empty()){
            this->m_counter_collision++;
        }
        
        m_table[slot].push_back(std::make_pair(k,v));


        m_number_of_elements++;

        return true;
        
    }


    /**
     * @brief Recebe como entrada uma chave k e retorna true 
     * se e somente se a chave k estiver presente na tabela hash.
     * 
     * @param k := chave a ser pesquisada
     */
    bool contains(const Key& k){
        size_t slot = hash_code(k);

        for(auto& p : m_table[slot]){
            if(p.first == k){
                this->m_counter_comparator++;

                return true;
            }
        }

        return false;
    }


    /**
     * @brief Retorna uma referencia para o valor associado a chave k.
     * Se k nao estiver na tabela, a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return V& := valor associado a chave
     */
    Value& at(const Key& k){
        size_t slot = hash_code(k);

        for(auto& p : m_table[slot]){
            if(p.first == k){
                this->m_counter_comparator++;

                return p.second;
            }
        }

        throw std::out_of_range("hash nao contem esse elemento"); //error
    }

    /**
     * @brief Retorna uma referencia constante  para o valor associado a chave k.
     * Se k nao estiver na tabela, a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return V& := valor associado a chave
     */ 
    const Value& at(const Key &k) const{
        size_t slot = hash_code(k);

        for(auto& p : m_table[slot]){
            if(p.first == k){
                this->m_counter_comparator++;

                return p.second;
            }
        }

        throw std::out_of_range("hash nao contem esse elemento"); //error
    }
     

    /**
     * @brief Recebe um inteiro nao negativo m e faz com que o tamanho
     * da tabela seja um numero primo maior ou igual a m.
     * Se m for maior que o tamanho atual da tabela, um rehashing eh realizado.
     * Se m for menor que o tamanho atual da tabela, a funcao nao tem nenhum efeito.
     * Um rehashing eh uma operacao de reconstrucao da tabela:
     * Todos os elementos no container sao rearranjados de acordo 
     * com o seu valor de hashing dentro na nova tabela.
     * Isto pode alterar a ordem de iteracao dos elementos dentro do container.
     * Operacoes de rehashing sao realizadas automaticamente pelo container 
     * sempre que load_factor() ultrapassa o m_max_load_factor.
     * 
     * @param m := o novo tamanho da tabela hash
     */
    void rehash(size_t m){
        size_t new_table_size = get_next_prime(m);

        if(new_table_size > m_table_size){
            std::vector<std::list<std::pair<Key, Value>>> old_vec; //

            old_vec = m_table;
            m_table.clear();
            m_table.resize(new_table_size);
            m_number_of_elements = 0;
            m_table_size = new_table_size;

            //Isso eh O(n)
            for(auto& list : old_vec){
                for(auto& par : list){
                    add(par.first, par.second);
                }
                list.clear(); //linha opcional
            }
        }
    }

    /**
     * @brief Remove da tabela hash o elemento com chave k se ele existir.
     * Ao remover o elemento, o numero de elementos eh decrementado em 1 unidade.
     * Retorna um booleano indicando se a remocao foi realizada.
     * 
     * @param k := chave a ser removida
     */
    bool remove(const Key& k){
        size_t slot = hash_code(k);

        for(auto it = m_table[slot].begin(); it != m_table[slot].end(); ++it){
            if(it->first == k){
                this->m_counter_comparator++;

                m_table[slot].erase(it);
                m_number_of_elements--;
                return true;
            }
        }

        return false;
    }


    /**
     * @brief Redimensiona a tabela hash de modo que ela tenha 
     * o tamanho mais apropriado a fim de conter pelo menos n elementos.
     * Se n > m_table_size * m_max_load_factor, entao a operacao 
     * de rehash() eh executada sendo passado para ela o tamanho apropriado da nova tabela.
     * Se n <= m_table_size * m_max_load_factor, entao 
     * a funcao nao tem efeito, nao faz nada.   
     * 
     * @param n := numero de elementos 
     */
    void reserve(size_t n){
        if(n > m_table_size * m_max_load_factor){
            rehash(n / m_max_load_factor);
        }
    }


    /**
     * @brief Recebe um float lf e muda o valor 
     * do atributo m_max_load_factor para esse valor.
     * Uma restricao eh que: 0 < m_max_load_factor.
     * Se lf nao estiver dentro desse intervalo entao uma 
     * out_of_range exception eh lancada
     * Ao mudar o fator de carga, eh possivel que a tabela hash tenha 
     * que ser redimensionada. Para isso, invocamos 
     * a funcao reserve(m_number_of_elemebnts).
     * 
     * @param lf := novo fator de carga
     */
    void set_max_load_factor(float lf){
        if(lf<= 0){
            throw std::out_of_range("invalid load factor");
        }
        // se lf > 0 ok entao ajusta fator de carva e redimensiona a tabela
        m_max_load_factor = lf;
        reserve(m_number_of_elements);
    }


    /**
     * @brief Sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao insere um novo elemento com essa chave e retorna um
     * referencia ao seu valor mapeado. Observe que isso sempre aumenta 
     * o tamanho da tabela em um, mesmo se nenhum valor mapeado for atribuido 
     * ao elemento (o elemento eh construido usando seu construtor padrao).
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    Value& operator[](const Key& k){
        size_t slot = hash_code(k);

        for(auto& par : m_table[slot]){
            if(par.first == k){
                this->m_counter_comparator++;
                busca++;
                return par.second;
            }
        }

        m_table[slot].push_back({k, Value()});
        m_number_of_elements++;
        busca++;
        return m_table[slot].back().second;
    }

    int buscaint(){
        return this->busca;
    }
    /**
     * @brief Versao const da sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento na tabela, a funcao
     * retorna uma referencia ao seu valor mapeado. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento na tabela, 
     * a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    const Value& operator[](const Key& k) const{
        return at(k);
    }

    friend std::ostream& operator<<(std::ostream& os, ChainedHashTable<Key, Value>& m){
        
        //std::ostream& os;
        for(auto& node : m.m_table){

            if(!node.empty()){
                for(auto& noh : node){
                    os << "(" << noh.first << ", " << noh.second << ")";
                    if(noh != node.back()){
                        os << ",";
                    }
                }
                os << std::endl;
            }
        }

        return os;
    }

};


#endif