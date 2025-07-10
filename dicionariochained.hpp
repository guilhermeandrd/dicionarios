#include <iostream>

#include "estruturas_auxiliares/ChainedHashTable.hpp"

#ifndef DICIONARIO_CHAINED_HPP
#define DICIONARIO_CHAINED_HPP

template <typename Key, typename Value>
class ChainedTableMap{
    ChainedHashTable<Key, Value> m_chained_table;

    //TODO deixar elas com o mesmo fator de carga
    //construtor
    MapAvl(){
        m_chained_table;
    }

    //construtor com tabela encadeada
    MapAvl(ChainedHashTable<Key, Value> p_chained_table){
        m_chained_table = p_chained_table;
    }

    //construtor com tabela encadeada
    MapAvl(const ChainedHashTable<Key, Value> p_chained_table){
        m_chained_table = p_avl;
    }

    //insert
    bool add(Key k, Value v){
        m_chained_table.add(k, v);
    }

    //update
    bool update(Key k, Value){
        return !m_chained_table.add(k, v);
    }

    //remove
    void remove(const Key k){
        m_chained_table.remove(k);
    }

    //contains
    bool contains(const Key k){
        return m_chained_table.contains(k);
    }

    Value& at(const Key &k){
        return m_chained_table.at(k);
    }

    //impressao
    /*void impressao(std::string nameFile = "text.avl"){
        m_chained_table.impressao(string);
    }*/

    //size, int k
    size_t size(){
        return m_chained_table.size();
    }

    //counter rotation
    size_t counter_collision(){
        return m_chained_table.counterCollision();
    }

    //counter comparator
    size_t counter_comparator(){
        return m_chained_table.counterComparator();
    }

    //empty
    bool empty(){
        return m_chained_table.empty();
    }

    //clear
    void clear(){
        m_chained_table.clear();
    }

    //iterador
    Value& operator[](Key &k){
        return m_chained_table[k];
    }

    //destrutor
    ~ChainedTableMap() = default;
};

#endif //#END_OF_DICIONARIO_AVL_HPP
