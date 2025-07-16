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

#include "estruturas_auxiliares/RBTree.hpp"

#ifndef DICIONARIO_RB_HPP
#define DICIONARIO_RB_HPP

template <typename Key, typename Value>
class MapRb{
private:
    RBtree<Key, Value> m_rb;

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
    MapRb() = default;

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
        return m_rb.insert(k, v);
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
        return !m_rb.insert(k, v);
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
        m_rb.remove(k);
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
        return m_rb.contains(k);
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
        return m_rb.at(k);
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
        return m_rb.at(k);
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
        return m_rb.size();
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
    size_t counter_rotation(){
        return m_rb.counter_rotation();
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
        return m_rb.counter_comparator();
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
        return m_rb.empty();
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
        m_rb.clear();
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
        return m_rb[k];
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
        return m_rb[k];
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
        return m_rb.vetorize();
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
    ~MapRb() = default;

};

#endif //#END_OF_DICIONARIO_AVL_HPP
