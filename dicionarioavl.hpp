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
     /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    MapAvl() = default;


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
    void add(Key k, Value v){
        m_avl.insert(k, v);
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
        return m_avl.update(k, v);
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
        m_avl.remove(k);
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
        return m_avl.contains(k);
    }

    //at
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
        return m_avl.at(k);
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
        return m_avl.at(k);
    }

    //impressao
     /**
     * @brief
     * 
     * @param
     * 
     * @return
     * 
     * //TODO anotar isso 
     */
    void impressao(std::string nameFile = "text.avl"){
        m_avl.impressao(nameFile);
    }

    //size
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
        return m_avl.size();
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
        return m_avl.counter_rotation();
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
        return m_avl.counter_comparator();
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
        return m_avl.empty();
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
        m_avl.clear();
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
        return m_avl.vetorize();
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
    Value& operator[](const Key& k){
        return m_avl[k];
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
    const Value& operator[](const Key& k) const{
        return m_avl[k];
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
    ~MapAvl() = default;

};

#endif //#END_OF_DICIONARIO_AVL_HPP
