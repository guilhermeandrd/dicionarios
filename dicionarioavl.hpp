#include <iostream>

#include "estruturas_auxiliares/AVLTree.hpp"

#ifndef DICIONARIO_AVL_HPP
#define DICIONARIO_AVL_HPP

template <typename Key, typename Value>
class MapAvl{
    AvlTree<Key, Value> m_avl;

    //construtor
    MapAvl(){
        m_avl;
    }

    //construtor com avl
    MapAvl(AvlTree<Key, Value> p_avl){
        m_avl = p_avl;
    }

    //construtor com avl
    MapAvl(const AvlTree<Key, Value> p_avl){
        m_avl = p_avl;
    }

    //insert
    void add(Key k, Value v){
        m_avl.insert(k, v);
    }

    //update
    bool update(Key k, Value){
        return m_avl.update(k, v);
    }

    //remove
    void remove(const Key k){
        m_avl.remove(k);
    }

    //contains
    bool contains(const Key k){
        return m_avl.contains(k);
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
