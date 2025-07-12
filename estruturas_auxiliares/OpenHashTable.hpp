/**
 * @file OpenHashTable.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Uma tabela hash com tratamento de colisao por encadeamento aberto
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef OPEN_HASHTABLE_HPP
#define OPEN_HASHTABLE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <cstddef>

/**
 * @brief struct para status que guarda os status Empty, Active e Deleted
 * 
 */
enum Status{
    Empty,
    Active,
    Deleted
};

/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por encadeamento aberto (open hash table).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class OpenHashTable{
private:

    /**
     * @brief Estrutura auxiliar para armazenar os pares e status de cada elemento
     *        da Open Hash Table.
     */
    struct Node{
        Status n_status;
        std::pair <Key, Value> n_pair{};

        Node() : n_status(Empty){}

        ~Node() = default;
    };

    //fato de carga da hash table
    float m_max_load_factor;

    //representacao da tabela atraves de um vetor
    std::vector<Node> m_table;

    Hash m_hashing;

    //atributo para os numeros de elementos que estao ativos
    size_t m_numbers_of_elements;

    //para o tamanho da tabela se usa m_table.capacity que dará na mesma coisa

    //contador de comparacoes das chaves
    //deixamos mutable para nao interfir em funcoes consts e ele ser
    //incrementado nessas funcoes
    mutable size_t m_counter_comparator = 0;

    //contador de colisoes
    mutable size_t m_counter_collision = 0;

    //funcao que retorna o proximo de x ou x se x for primo
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

    //primeiro hash code
    size_t hash_code(const Key& k) const{
        return m_hashing(k) % m_table.size();
    }

    //segundo hash code
    size_t hash_code_second(const Key& k) const{
        return (m_hashing(k) % (m_table.size() - 1))+ 1;
    }

    //hash code que realmente sera usado para hashing duplo
    size_t h(Key k, size_t i){
        return (hash_code(k) + i * hash_code_second(k)) % m_table.size();
    }

public:

    
    /**
     * @brief construtor defacult. escolhi tamanho 47 para guardar pelo menos 23 elementos antes de um rehash
     *        caso nao seja esccolhido um fator de carga, ele eh setao em 0.5 para melhor funcionamento.
     *        os elementos comecam em 0.
     * 
     * @param tableSize tamanho da tabela
     * 
     * @param load_factor fator de carga da tabela hash
     * 
     */
    OpenHashTable(size_t tableSize = 47, float load_factor = 0.5){
        m_table.resize(get_next_prime(tableSize));

        m_numbers_of_elements = 0;

        if(load_factor <= 0){
            m_max_load_factor = 0.5;
        }else{
            m_max_load_factor = load_factor;
        }
    }
    
    /**
     * @brief insere um par com a chave e o valor passados no parametro na tabela.
     *        insere atraves de hashing duplo para melhor uso da tabela. caso a
     *        chave ja exista, ela eh apenas atualizada, retornando false.
     * 
     * @param k chave a ser inserida
     * 
     * @param v valor a ser inserido
     * 
     * @return True se e somente se a insercao tiver sido feita
     */
    bool add(const Key& k, const Value& v){


        //o rehash acontece quando a tabela tá cheia OU o seu fator máximo de carga foi alcançado
        if(m_table.capacity() == m_numbers_of_elements || load_factor() >= m_max_load_factor){
            rehash(m_table.capacity() * 2);
        }

        size_t i = 0;
        ptrdiff_t index = -1;

        while(i < m_table.size()){
            size_t j = h(k, i);

            if(m_table[j].n_status == Active){
                
                if(m_table[j].n_pair.first == k){
                    m_counter_comparator++;
                    
                    index = j;
                    
                    break;
                }

                if(i == 0){
                    m_counter_collision++;
                }

            }else if(m_table[j].n_status == Empty){

                if( index == -1){
                    index = j;
                }

                break;

            }else if(index == -1){
                index = j;
            }

            i++;
        }

        if(index != -1){

            if(m_table[index].n_status == Active){
                m_table[index].n_pair.second = v;
                return false;
            }

            m_table[index].n_pair.first = k;
            m_table[index].n_pair.second = v;
            m_table[index].n_status = Active;

            m_numbers_of_elements++;
        
            return true;
        }
        
        return false;
    }
    
    /**
     * @brief verifica se a chave existe na tabela. caso exista, retorna true. a verificacao tambe,
     *        eh feita atraves de hashing duplo.
     * 
     * @param k chave a ser buscada
     * 
     * @return True se e somense se a chave existir
     */
    bool contains(const Key k){
        size_t i = 0;
        size_t j = 0;

        do{
            j = h(k, i);
            if(m_table[j].n_status == Active && m_table[j].n_pair.first == k){
                m_counter_comparator++;
                return true;
            }
            
            i++;
        }while(m_table[j].n_status != Empty && i < m_table.size());

        
        return false;
    }

    /**
     * @brief verifica atraves do numero de elementos se tabela esta vazia ou nao.
     *        a tabela eh considerada vazia se nenhum de seus elementos for ativo.
     * 
     * 
     * @return True e se somente se a tabela estiver vazia.
     */
    bool empty() const{
        return m_numbers_of_elements == 0;
    }

    /**
     * @brief verifica quantos buckets existem na tabela. como eh implementado com um vetor, 
     *        eh quantos buckets ja foram criados, sendo de qualquer status, ateh emptys.
     * 
     * @return retorna o numero de buckets que existem, de qualquer status, em tipo size_t
     */
    size_t bucket_count() const{
        return m_table.capacity();
    }

    /**
     * @brief verifica o numero de comparacoes de chaves que foram realizadas durante as operacoes
     *      
     * @return retorna o numero de comparacoes de chave que foram feitas, em tipo size_t
     */
    size_t counter_comparator(){
        return m_counter_comparator;
    } 

    /**
     * @brief verifica o numero de colisoes que aconteceram durante as insercoes
     *      
     * @return retorna o numero de colisoes, em tipo size_t
     */
    size_t counter_collision(){
        return m_counter_collision;
    }

    /**
     * @brief retorna quantos elementos tem na tabela
     */
    size_t size(){
        return m_numbers_of_elements;
    }

    /**
     * @brief retorna o fator de carga atual da tabela
     */
    float load_factor(){
        return static_cast<float>(m_numbers_of_elements) /m_table.size();
    }
    
    /**
     * @brief retorna o fator maximo de carga da tabela
     */
    float max_load_factor(){
        return m_max_load_factor;
    }

    
    /**
     * @brief Seta todos os status dos node para Empty.
     * tabela continua com o mesmo tamanho, o mesmo numero de buckets.
     * Escolha feita por conta que um resize para diminuir o tamanho da tabela
     * levaria mais tempo para fazer a realocao. Tambem atribuimos zero para o 
     * numero de elementos e seus contadores.
     */
    void clear(){

        //muda todas os valores para empty
        for(auto& node : m_table){
            node.n_status = Empty;
            node.n_pair.first = Key();
            node.n_pair.second = Value();
        }

        m_numbers_of_elements = 0;
        m_counter_collision = 0;
        m_counter_comparator = 0;
    }

    /**
     * @brief verifica se a chave existe, caso exista, retorna o valor relacionado a ela.
     * caso nao, retorna um erro.
     * 
     * @param k chave em que sera procurada seu valor
     * 
     * @return valor relacionado a chave
     */
    Value& at(const Key& k){
        size_t i = 0;
        size_t j = 0;

        do{
            j = h(k, i);
            if(m_table[j].n_status == Active && m_table[j].n_pair.first == k){
                m_counter_comparator++;
                return m_table[j].n_pair.second;
            }
            
            i++;
        }while(m_table[j].n_status != Empty && i < m_table.size());

        
        throw std::out_of_range("hash nao contem esse elemento"); //error
    }

    /**
    * @brief versao const da funcao at.
    * verifica se a chave existe, caso exista, retorna o valor relacionado a ela.
    * caso nao, retorna um erro.
    * 
    * @param k chave em que sera procurada seu valor
    * 
    * @return valor relacionado a chave
    */
    const Value& at(const Key& k) const{
        size_t i = 0;
        size_t j = 0;

        do{
            j = h(k, i);
            if(m_table[j].n_status == Active && m_table[j].n_pair.first == k){
                m_counter_comparator++;

                return m_table[j].n_pair.second;
            }
            
            i++;
        }while(m_table[j].n_status != Empty && i < m_table.size());

        throw std::out_of_range("hash nao contem esse elemento"); //error
    }

   
    /**
     * @brief deixa a tabela do tamanho apropriado
     * para guarde pelo menos n elementos. caso haja necessidade de ser feito
     * um rehash, eh feito para guardar esses n elementos
     * 
     * @param n numero de elementos que a tabela esta preparada para receber
     * 
     */
    void reserve(size_t n){
        if(n > m_table.size() * m_max_load_factor){ 
            rehash(n / m_max_load_factor);
        }
    }

    /**
     * @brief Mudar o fator maximo de carga da Open Hash Table.
     * Faz um reserve para o numero atual de elementos, utilizando o novo fator maximo de carga.
     * 
     * @param lf novo fator maximo de carga
     * 
     */
    void set_max_load_factor(float lf){
        
        //verifica se esse fator de carga eh valido
        if(lf <= 0){
            throw std::out_of_range("invalid load factor");
        }

        m_max_load_factor = lf;

        //rehasha para o novo tamanho da tabela
        reserve((m_numbers_of_elements));
    }

    /** 
     * @brief uso do algoritmo de contains e add.
     * se a chave existir, retornamos seu valor relacionado.
     * se nao conter aquela chave, a inserimos e retornamos seu valor,
     * que no caso eh o construtor vazio daquele tipo.
     *  
     * @param k chave que corresponde aquele bucket
     * 
     * 
     * @return valor se ele existir, se nao, o criamos e retornamos seu objeto "vazio", usando o construtor padrao.
     */
    Value& operator[](const Key& k){

        //vou fazer uma busca por essa chave
        size_t i = 0;
        size_t j = 0;

        //copia do código de contains retorna agora o valor
        do{
            j = h(k, i);
            if(m_table[j].n_status == Active && m_table[j].n_pair.first == k){
                m_counter_comparator++;
                //se achar, retorno o seu valor
                return m_table[j].n_pair.second;
            }
            
            i++;
        }while(m_table[j].n_status != Empty && i < m_table.size());

        //copia do codigo de inserir
        if(m_numbers_of_elements == m_table.capacity() || load_factor() >= m_max_load_factor){
            //std::cout << std::endl <<"essa eh a capacidade" <<  m_table.capacity() << "  size::" << m_table.size() << std::endl;
            rehash(m_table.capacity() * 2);
        }

        i = 0;
        ptrdiff_t index = -1;

        while(i < m_table.size()){
            int j = h(k, i);
            //auto& node = m_table[index];

            if(m_table[j].n_status == Active){
                if(m_table[j].n_pair.first == k){
                    m_counter_comparator++;

                    index = j;

                    break;
                }else{
                    m_counter_collision++;
                }
            }else if(m_table[j].n_status == Empty){
                if( index == -1){
                    index = j;

                    break;
                }
            }else if(index == -1){
                index = j;
            }

            i = i + 1;
        }

        // como a chave nao existe entao nao precisamos do if que fazemos no add
        // ja a inserimos
        m_table[index].n_pair.first = k;
        m_table[index].n_pair.second = Value();
        m_table[index].n_status = Active;
    
        m_numbers_of_elements++;

        return m_table[index].n_pair.second;

        
        //se nao, a crio e a retorno
    }

    /** 
     * @brief versao const do iterador. uso do algoritmo de contains e add.
     * se a chave existir, retornamos seu valor relacionado.
     * se nao conter aquela chave, a inserimos e retornamos seu valor,
     * que no caso eh o construtor vazio daquele tipo.
     *  
     * @param k chave que corresponde aquele bucket
     * 
     * 
     * @return valor se ele existir, se nao, o criamos e retornamos seu objeto "vazio", usando o construtor padrao.
     */
    const Value& operator[](const Key& k) const{
        return at(k);
    }
    
    /** 
     * @brief sobrecarga do operador de cout, para melhor uso da tabela
     * 
     * @param os objeto ostream que sera retornado
     * 
     * @param m open_hash_table que serah impressa na tela
     * 
     * @return objeto ostream que sera interpretado pelo operador <<
     * 
     */
    friend std::ostream& operator<<(std::ostream& os, OpenHashTable<Key, Value>& m){
        
        //std::ostream& os;
        for(auto& node : m.m_table){
            if(node.n_status == Active){
                os << "(" << node.n_pair.first << ", " << node.n_pair.second << ")" << std::endl;
            }
        }

        return os;
    }
    
    /**
     * @brief Remove o bucket que corresponde a essa chave:
     *        Muda o status do bucket para deleted 
     *        e muda o valor e chave para seus construtores defaults.
     * 
     * @param k - chave do bucket que sera excluido
     * 
     * @return Retorna True se a remocao foi feita e False se a remocao nao der certo,
     *         caso essa chave nao exista na tabela.
     */
    bool remove(Key k){
        size_t i = 0;
        size_t j = 0;

        do
        {
            j = h(k, i);
            if(m_table[j].n_status == Active && m_table[j].n_pair.first == k){
                m_counter_comparator++;

                m_table[j].n_status = Deleted;
                m_table[j].n_pair.first = Key();
                m_table[j].n_pair.second = Value();

                m_numbers_of_elements--;
                return true;

            }

            i++;
        }while(m_table[j].n_status != Empty && i < m_table.size());

        return false;
    }

    /**
     * @brief  operacao que insere as chaves em uma tabela hash com tamanho maior 
     *          ao menos para comportar m elementos
     * @param m quantos elementos irao ser inseridos
     * 
     */
    void rehash(size_t m){

            std::vector<Node> old_vec;
    
            old_vec = m_table;
    
            //atribui empty para todos os valores
            for(auto& node : m_table){
                node.n_status = Empty;
                node.n_pair.first = Key();
                node.n_pair.second = Value();
            }

            m_numbers_of_elements = 0;
            m_table.resize(get_next_prime(m));
    
            for(auto& node : old_vec){
                if(node.n_status == Active){
                    add(node.n_pair.first, node.n_pair.second);
                }
            }
    }

    std::vector<std::pair<Key, Value>> vetorize(){
        if(m_numbers_of_elements == 0)
            throw std::invalid_argument("a tabela open hash está vazia");

        std::vector<std::pair<Key, Value>> retorno;

        for(auto& node : m_table){
            if(node.n_status == Active)
                retorno.push_back({node.n_pair.first, node.n_pair.second});
        }

        return retorno;
    }

    /**
     * @brief : destrutor da open_hash_table
     */
    ~OpenHashTable() = default;
};

#endif //FIM DO HASH OPEN