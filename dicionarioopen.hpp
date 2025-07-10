#include <iostream>

#include "estruturas_auxiliares/OpenHashTable.hpp"

#ifndef DICIONARIO_CHAINED_HPP
#define DICIONARIO_CHAINED_HPP

template <typename Key, typename Value>
class OpenTableMap{
    OpenHashTable<Key, Value> m_open_table;

    //construtor
    OpenHashMap(){
        m_open_table;
    }

    //construtor com avl
    OpenHashMap(OpenHashTable<Key, Value> p_open_table){
        m_open_table = p_open_table;
    }

    //construtor com avl
    OpenHashMap(const OpenHashTable<Key, Value> p_open_table){
        m_open_table = p_avl;
    }

    //insert
    bool add(Key k, Value v){
        m_open_table.add(k, v);
    }

    //update
    bool update(Key k, Value){
        return !m_open_table.add(k, v);
    }

    //remove
    void remove(const Key k){
        m_open_table.remove(k);
    }

    //contains
    bool contains(const Key k){
        return m_open_table.contains(k);
    }

    Value& at(const Key &k){
        return m_open_table.at(k);
    }

    //impressao
    /*void impressao(std::string nameFile = "text.avl"){
        m_chained_table.impressao(string);
    }*/

    //size, int k
    size_t size(){
        return m_open_table.size();
    }

    //counter rotation
    size_t counter_collision(){
        return m_open_table.counter_collision();
    }

    //counter comparator
    size_t counter_comparator(){
        return m_open_table.counter_comparator();
    }

    //empty
    bool empty(){
        return m_open_table.empty();
    }

    //clear
    void clear(){
        m_open_table.clear();
    }

    //iterador
    Value& operator[](Key &k){
        return m_open_table[k];
    }

    //destrutor
    ~OpenTableMap() = default;
};

#endif //#END_OF_DICIONARIO_AVL_HPP
