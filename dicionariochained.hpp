#include <iostream>

#include "estruturas_auxiliares/ChainedHashTable.hpp"

#ifndef DICIONARIO_CHAINED_HPP
#define DICIONARIO_CHAINED_HPP

template <typename Key, typename Value>

class DicionarioChainedHash{
private:
    ChainedHashTable<Key, Value> m_chained_table;

    //construtor
public:
    DicionarioChainedHash(){
        m_chained_table;
    }

    //construtor com tabela encadeada
    /*DicionarioChainedHash(ChainedHashTable<Key, Value> p_chained_table){
        m_chained_table = p_chained_table;
    }

    //construtor com tabela encadeada
    DicionarioChainedHash(const ChainedHashTable<Key, Value> p_chained_table){
        m_chained_table = p_chained_table;
    }*/

    //insert
    bool add(Key k, Value v){
        return m_chained_table.add(k, v);
    }

    //update
    bool update(Key k, Value v){
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
    ~DicionarioChainedHash() = default;
};

#endif //#END_OF_DICIONARIO_AVL_HPP
