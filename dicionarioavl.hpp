#include <iostream>

#include "estruturas_auxiliares/AVLTree.hpp"
#include <string>
#include <vector>
#include <algorithm>

#ifndef DICIONARIO_AVL_HPP
#define DICIONARIO_AVL_HPP

template <typename Key, typename Value>
class MapAvl{
private:
    AvlTree<Key, Value> m_avl;
public:
    //construtor
    MapAvl(){
        m_avl;
    }

    //construtor com avl
    /*MapAvl(AvlTree<Key, Value> p_avl){
        m_avl = p_avl;
    }*/

    //construtor com avl
    /*MapAvl(const AvlTree<Key, Value> p_avl){
        m_avl = p_avl;
    }*/

    //insert
    void add(Key k, Value v){
        m_avl.insert(k, v);
    }

    //update
    bool update(Key k, Value v){
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
    Value& at(const Key &k){
        return m_avl.at(k);
    }


    const Value& at(const Key &k){
        return m_avl.at(k);
    }

    //impressao
    void impressao(std::string nameFile = "text.avl"){
        m_avl.impressao(nameFile);
    }

    //size
    size_t size(){
        return m_avl.size();
    }

    //counter rotation
    size_t counter_rotation(){
        return m_avl.counter_rotation();
    }

    //counter comparator
    size_t counter_comparator(){
        return m_avl.counter_comparator();
    }

    //empty
    bool empty(){
        return m_avl.empty();
    }

    //clear
    void clear(){
        m_avl.clear();
    }

    std::vector<std::pair<Key, Value>> vetorize(){
        return m_avl.vetorize();
    }


    //destrutor
    ~MapAvl() = default;

};

#endif //#END_OF_DICIONARIO_AVL_HPP
