#include <iostream>

#include "estruturas_auxiliares/RBTree.hpp"

#ifndef DICIONARIO_CHAINED_HPP
#define DICIONARIO_CHAINED_HPP

template <typename Key, typename Value>
class MapRb{
    RBtree<Key, Value> m_rb;

    //construtor
    MapRb(){
        m_rb;
    }

    //construtor com avl
    MapRb(RBtree<Key, Value> p_chained_table){
        m_rb = p_chained_table;
    }

    //construtor com avl
    MapRbl(const RBtree<Key, Value> p_chained_table){
        m_rb = p_avl;
    }

    //insert
    bool add(Key k, Value v){
        m_rb.insert(k, v);
    }

    //update
    bool update(Key k, Value){
        return !m_rb.insert(k, v);
    }

    //remove
    void remove(const Key k){
        m_rb.remove(k);
    }

    //contains
    bool contains(const Key k){
        return m_rb.contains(k);
    }

    Value& at(const Key &k){
        return m_rb.at(k);
    }

    //impressao
    /*void impressao(std::string nameFile = "text.avl"){
        m_chained_table.impressao(string);
    }*/

    //size, int k
    size_t size(){
        return m_rb.size();
    }

    //counter rotation
    size_t counter_rotation(){
        return m_rb.counter_rotation();
    }

    //counter comparator
    size_t counter_comparator(){
        return m_rb.counter_comparator();
    }

    //empty
    bool empty(){
        return m_rb.empty();
    }

    //clear
    void clear(){
        m_rb.clear();
    }

    //iterador
    Value& operator[](Key &k){
        return m_rb[k];
    }

    //destrutor
    ~MapRb() = default;

};

#endif //#END_OF_DICIONARIO_AVL_HPP
