/**
 * @file AVLTree.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Árvore Binária de Busca Balanceada (AVL)
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <iostream>

#include "estruturas_auxiliares/OpenHashTable.hpp"

#ifndef DICIONARIO_OPEN_HPP
#define DICIONARIO_OPEN_HPP

template <typename Key, typename Value>
class OpenHashMap{
private:
    OpenHashTable<Key, Value> m_open_table;

public:
    //construtor
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    OpenHashMap() = default;

    //insert
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    bool add(Key k, Value v){
        return m_open_table.add(k, v);
    }

    //update
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    bool update(Key k, Value v){
        return !m_open_table.add(k, v);
    }

    //remove
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    void remove(const Key k){
        m_open_table.remove(k);
    }

    //contains
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    bool contains(const Key k){
        return m_open_table.contains(k);
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Value& at(const Key &k){
        return m_open_table.at(k);
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    const Value& at(const Key &k) const{
        return m_open_table.at(k);
    }

    //size, int k
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    size_t size(){
        return m_open_table.size();
    }

    //counter rotation
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    size_t counter_collision(){
        return m_open_table.counter_collision();
    }

    //counter comparator
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    size_t counter_comparator(){
        return m_open_table.counter_comparator();
    }

    //empty
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    bool empty(){
        return m_open_table.empty();
    }

    //clear
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    void clear(){
        m_open_table.clear();
    }

    //iterador
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    Value& operator[](Key &k){
        return m_open_table[k];
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    const Value& operator[](Key &k) const{
        return m_open_table[k];
    }

    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    std::vector<std::pair<Key, Value>> vetorize(){
        return m_open_table.vetorize();
    }

    
    //destrutor
    /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    ~OpenHashMap() = default;
};

#endif //#END_OF_DICIONARIO_AVL_HPP
