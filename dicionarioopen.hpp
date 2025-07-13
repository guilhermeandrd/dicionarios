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
    OpenHashMap(){
        m_open_table;
    }

    //construtor com avl
    /*OpenHashMap(OpenHashTable<Key, Value> p_open_table){
        m_open_table = p_open_table;
    }

    //construtor com avl
    OpenHashMap(const OpenHashTable<Key, Value> p_open_table){
        m_open_table = p_avl;
    }*/

    //insert
    bool add(Key k, Value v){
        return m_open_table.add(k, v);
    }

    //update
    bool update(Key k, Value v){
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

    const Value& at(const Key &k) const{
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

    const Value& operator[](Key &k) const{
        return m_open_table[k];
    }

    std::vector<std::pair<Key, Value>> vetorize(){
        return m_open_table.vetorize();
    }
    //destrutor
    ~OpenHashMap() = default;
};

#endif //#END_OF_DICIONARIO_AVL_HPP
