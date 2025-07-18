/**
 * @file dicionarioavl.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Dicionário Implementado Com Árvoe Rubro Negra
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <iostream>

#include "estruturas_auxiliares/RBTree.hpp"

#ifndef DICIONARIO_RB_HPP
#define DICIONARIO_RB_HPP

template <typename Key, typename Value>
class MapRb{
private:
    RBtree<Key, Value> m_rb;

public:

     /**
     * @brief Construtor para dicionário rubro negro, 
     * ele usa o próprio construtor da árvore rubro negra.
     * 
     */
    MapRb() = default;

     /**
     * @brief Função que insere um par chave-valor no dicionário.
     * Caso a chave já exista, o valor é atualizado e é retornado false
     * @param k := chave do par
     * 
     * @param v := valor do par
     * 
     * @return True se e somente se o valor for inserido
     */
    bool add(Key k, Value v){
        return m_rb.insert(k, v);
    }

    /**
     * @brief Função que atualiza um valor de um par chave-valor
     * que já existe. Se o par não existir, aquele par 
     * é criado e inserido e é retornado false.
     * 
     * @param k := chave do par
     * 
     * @param v := valor do par
     * 
     * @return True se e somente se tiver atualizado.
     * 
     */
    bool update(Key k, Value v){
        return !m_rb.insert(k, v);
    }

    /**
     * @brief Remove um par chave-valor da estrutura se a chave 
     * existir.
     * 
     * @param k := chave do par chave-valor que será removido
     * 
     */
    void remove(const Key k){
        m_rb.remove(k);
    }

    /**
     * @brief Função que verifica se um par chave-valor está contido 
     * na estrutura. 
     * 
     * @param k := chave do par chave-valor que será buscado
     * 
     * @return True se e somente se o par com a chave k existir
     * 
     */
    bool contains(const Key k){
        return m_rb.contains(k);
    }
    
    /**
     * @brief Retorna o valor do par chave-valor caso exista.
     * Caso não, um erro é retornado.
     * 
     * @param k := chave do par chave-valor, a qual o valor vai ser retornado
     * 
     * @return Value& := referência do valor do par.
     * 
     */
    Value& at(const Key &k){
        return m_rb.at(k);
    }

     /**
     * @brief Versão const do at. 
     * Retorna o valor constante do par chave-valor caso exista.
     * Caso não, um erro é retornado.
     * 
     * @param k := chave do par chave-valor, a qual o valor vai ser retornado
     * 
     * @return Value& := referência do valor do par.
     * 
     */
    const Value& at(const Key &k) const{
        return m_rb.at(k);
    }

     /**
     * @brief Retorna quantos pares estão armazenados na estrutura.
     * 
     */
    size_t size(){
        return m_rb.size();
    }

     /**
     * @brief Retorna quantas rotações a estrutura já realizou.
     * 
     */
    size_t counter_rotation(){
        return m_rb.counter_rotation();
    }

     /**
     * @brief Retorna quantas comparações de chaves
     * a estrutura já realizou.
     * 
     */
    size_t counter_comparator(){
        return m_rb.counter_comparator();
    }

    /**
     * @brief Retorna true se e somente se a estrutura estiver vazia
     * 
     */
    bool empty(){
        return m_rb.empty();
    }

    /**
     * @brief Limpa a estrutura, removendo todos os pares da estrutura.
     * Ademais, tamanho é zerado, assim com as métricas da estrutura.
     *
     */
    void clear(){
        m_rb.clear();
    }

     /**
     * @brief Sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento do dicionário, a funcao
     * retorna uma referencia ao seu valor. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento do dicionário, 
     * a funcao insere um novo elemento com essa chave e retorna um
     * referencia ao seu valor. Observe que isso sempre aumenta 
     * o tamanho da dicionário em um, mesmo se nenhum valor mapeado for atribuido 
     * ao elemento (o elemento eh construido usando seu construtor padrao).
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    Value& operator[](Key &k){
        return m_rb[k];
    }

    /**
     * @brief Versao const da sobrecarga do operador de indexacao.
     * Se k corresponder a chave de um elemento do dicionário, a funcao
     * retorna uma referencia ao seu valor. Caso contrario, 
     * se k nao corresponder a chave de nenhum elemento do dicionário, 
     * a funcao lanca uma out_of_range exception.
     * 
     * @param k := chave
     * @return Value& := valor associado a chave
     */
    const Value& operator[](Key &k) const{
        return m_rb[k];
    }

 /**
     * @brief cria um vetor da estrutura em ordem simétrica
     * O vetor já está ordenado, se a estrutura estiver vazia é lançada um throw invalid_argument
     * 
     * @return vector<pair<Key, Value>> := vetor com pares do mesmo tipo da chave e do valor 
     * da estrutura.
     * 
     */
    std::vector<std::pair<Key, Value>> vetorize(){
        return m_rb.vetorize();
    }

     /**
     * @brief Destrutor para dicionário rubro negro, 
     * ele usa o próprio destrutor da árvore rubro negra.
     * 
     */
    ~MapRb() = default;

};

#endif //#END_OF_DICIONARIO_AVL_HPP
