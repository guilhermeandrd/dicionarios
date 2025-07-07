#include <iostream>

#include "ChainedHashTable.hpp"

#ifndef DICIONARIO_CHAINED_HPP
#define DICIONARIO_CHAINED_HPP

template <typename Key, typename Value>
class ChainedTableMap{
    ChainedHashTable<Key, Value> m_chained_table;

    //construtor
    MapAvl(){
        m_chained_table;
    }

    //construtor com avl
    MapAvl(ChainedHashTable<Key, Value> p_chained_table){
        m_chained_table = p_chained_table;
    }

    //construtor com avl
    MapAvl(const AvlTree<Key, Value> p_chained_table){
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

    //at

    //impressao

    //size

    //counter rotation

    //counter comparation

    //size

    //clear

    //destrutor


};

#endif //#END_OF_DICIONARIO_AVL_HPP
