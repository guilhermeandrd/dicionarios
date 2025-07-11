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

#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <ctime>

/**
 * @brief implementacao da estrutura Arvore AVL
 *        usando como estrutura auxilar o struct node ja definido,
 *        sendo a estrutura node e a classe de tipos genericos
 * 
 * @tparam Key key type
 * 
 * @tparam Value value type
 * 
 */
template <typename Key, typename Value>

class AvlTree{
private:

    /**
     * @brief Estrutura auixiliar para nohs da arvore avl,
     *        contem a altura do noh, o par de chave e valor
     *        e ponteiros para o seu noh a esquerda e direita
     */
    struct Node{
        int height;
        Node* right;
        Node* left;
        std::pair <Key, Value> n_pair;
        
        /**
         * @brief construtor para o noh da arvore
         * 
         * @tparam Key chave do par
         * 
         * @tparam Value valor do par
         * 
         * @tparam Int altura do noh
         * 
         * @tparam Node* seu noh esquerdo
         * 
         * @tparam Node* seu noh direito
         * 
         */
        Node(Key k, Value v, int height, Node* l, Node* r) {
            this->n_pair = std::make_pair(k, v);
            this->height = height;
            left = l;
            right = r;
        }

        ~Node() = default;
    };

    //atributos da classe arvore avl

    //raiz da arvore avl
    Node *m_root;

    //contador de rotacoes
    mutable size_t m_counter_rotation; //toda vez que ocorre uma rotacao ele aumenta

    //contador de comparacoes de chaves
    mutable size_t m_counter_comparator;

    //tamanho da arvore (numero de nohs)
    size_t m_size;

public:

    /**
     * @brief construtor padrao que cria arvore com raiz nula
     *        e com seus contadores e tamanho zerados
     */
    AvlTree(){
        m_root = nullptr;
        m_counter_rotation = 0;
        m_counter_comparator = 0;
        m_size = 0;
    }

    /**  
    * @brief publica que insere o valor e sua chave,
    *        caso a chave ja exista, nada é feito.
    * 
    * @param k chave que serah inserida
    * 
    * @param v valor que serah inserido junto com a chave
    * 
    * @return True se e somente se o par tiver sido inserido
    */
    void insert(Key k, Value v){
        m_root = _insert(m_root, k, v);
    }

    /**
     * @brief busca o nó e o atualiza caso exista
     * 
     * @param k chave do noh a ser procurado
     * 
     * @param v novo valor do par
     * 
     * //TODO melhorar isso aqui
     */
    bool update(Key k, Value v){
        return _update(m_root, k , v);
    }
 
    /**
     * @brief remove todos os nohs da arvore,
     *        tambem zera todos os contadores
     *        e tamanho
     */
    void clear() {
        m_root = clear(m_root);
        m_counter_rotation = 0;
        m_counter_comparator = 0;
        m_size = 0;
    }

    /**
     * @brief imprime a arvore em um formato mais amigavel. caso esteja vazia, imprime somente o nullptr como "#".
     */
    void show(){
        bshow(m_root, "");
    }
    
    /**
     * @brief verifica se aquele par com aquela chave existe
     * 
     * @param k chave a ser verificada se existe
     * 
     * @return True se existir e False se nao
     */
    bool contains(const Key k){
        Node *aux = contains(m_root, k);
        return aux != nullptr;
    }

    /**
     * @brief retorna uma referencia do valor relacionado com a chave passada no parametro,
     *        se a chave existir.
     * 
     * @param k chave do par do qual serah retornado o valor
     * 
     * @return valor relacionado aquela chave
     */
    Value& at(const Key& k){
        Node *aux = contains(m_root, k);

        if(aux == nullptr){
            throw std::out_of_range("arvore nao contem esse elemento"); //error
        }

        return aux->n_pair.second;
    }

    /**
     * @brief retorna uma referencia constante do valor relacionado com a chave passada no parametro,
     *        se a chave existir.
     * 
     * @param k chave do par do qual serah retornado o valor
     * 
     * @return valor relacionado aquela chave
     */
    const Value& at(const Key& k) const{
        Node *aux = contains(m_root, k);

        if(aux == nullptr){
            throw std::out_of_range("arvore nao contem esse elemento"); //error
        }

        return aux->n_pair.second;
    }
    
    /**
     * @brief funcao que remove uma noh com uma respectiva chave da arvore se ele existir. 
     *        eh passado a raiz e a chave para uma funcao que a remove de maneira recursiva e
     *        retorna a nova raiz da arvore sem o elemento.
     * 
     * @param k chave do noh a ser removido
     * 
     */
    void remove(const Key k){
        m_root = remove(m_root, k);
    }
    
    /**
     * @brief verifica se uma arvore eh vazia atraves de sua raiz
     * 
     * @return True se for vazia, False se não for vazia
     */
    bool empty() const{
        return m_root == nullptr;
    }

    /**
     * @brief retorna o numero de rotacoes que ja foi realizada na arvore em suas funcoes.
     * 
     * @return tipo size_t do numero de rotacoes
     */
    size_t counter_rotation() const{
        return m_counter_rotation;
    }

    /**
     * @brief retorna o numero de comparacoes de chaves que ja foi realizado na arvore em suas funcoes.
     * 
     * @return tipo size_t do numero de comparacoes de chaves
     */
    size_t counter_comparator() const{
        return m_counter_comparator;
    }

    /**
     * @brief retorna o tamanho da arvore (o numero de nohs)
     * 
     * @return tipo size_t do tamanho da arvore (numero de nohs)
     */
    size_t size() const{
        return m_size;
    }

    /**
    * @brief sobrecarga do operador de atribuicao
    * 
    * @param outra arvore a qual sera atribuida a que chamou o operador
    * 
    * @return a arvore eh igual a outra, copiando seus nohs, contadores e size
    */
    AvlTree& operator=(const AvlTree& outra){
        if(this != &outra){
            clear();
            this->m_root = copia(outra.m_root);
            this->m_counter_rotation = outra.m_counter_rotation;
            this->m_counter_comparator = outra.m_counter_comparator;
            this->m_size = outra.m_size;
        }

        return *this;
    }

    /**
     * @brief sobrecarga do construtor de copia. a arvore recebe copia da que foi
     *        passada como parametro, assim como seu tamanho e respectivos contadores.
     * 
     * @param aux referencia de arvore constante
     * 
     * @return arvore recebe uma copia da que foi passada como parametro
     */
    AvlTree (const AvlTree& aux) : AvlTree(){ //faz uso do construtor padrao da arvore e depois recebe a copia
        this->m_root = copia(aux.m_root);
        this->m_counter_rotation = aux.m_counter_rotation;
        this->m_size = aux.m_size;
        this->m_counter_comparator = aux.m_counter_comparator;
    }

    /**
     * @brief sobrecarga do operador de diferenca
     * 
     * @param outra arvore a ser comparada
     * 
     * @return True se for diferente, False se for igual
     */
    bool operator!=(const AvlTree& outra) const{
        return !(*this == outra); //basicamente negamos a sua igualdade
    }

   /**
     * @brief sobrecarga do operador de igualdade. faz uso de uma funcao privada 
     * e recursiva que verifica a sua igualdade.
     * 
     * @param outra arvore a ser comparada
     * 
     * @return True se for igual, False se for diferente
     */
    bool operator==(const AvlTree &outra) const{
        return ehIgual(m_root, outra.m_root);
    }

    /**
     * @brief destruitor para a arvore que usa o clear
     */
    ~AvlTree() {
        m_root = clear(m_root);
    }
    
    void impressao(std::string nameFile = "testeAVL"){

        //primeiro ocorre o tratamento da string
        
        //o usuario nao passou nome para o teste
        if(nameFile == "testeAVL"){

            //obtem a hora atual para gerar sempre arquvios de nomes diferentes
            time_t agora = time(0);
            tm* ltm = localtime(&agora);

            //usa ostringstream para montar o nome do arquivo
            std::ostringstream oss;
            oss << nameFile << ltm->tm_hour << "-" << ltm->tm_min << "-" 
            << ltm->tm_sec << "-" << ".txt";

            //nome do arquivo igual ao objeto ostringstream
            nameFile = oss.str();
        }

        std::fstream file (nameFile, std::ios::in | std::ios::out);

        if(m_root==nullptr)
            throw std::invalid_argument("raiz da arvore é nul");

        if(!file.is_open()){
            
            std::ofstream creator(nameFile);

            if(!creator.is_open())
                throw std::runtime_error("erro critico ao criar o arquivo");
            
            creator.close();
            file.open(nameFile, std::ios::in | std::ios::out);
        }
        

        Node* node = m_root;
        std::stack<Node*> pilha;
        while(!pilha.empty() || node != nullptr){
            if(node != nullptr){
                pilha.push(node);
                node = node->left;
            }else{
                node = pilha.top();
                pilha.pop();

                //coloca node no arquivo
                file << node->n_pair.first << " " << node->n_pair.second << std::endl;

                node = node->right;
            }
        }

        file.close();
    }
private:

    /**
     * @brief Função que recebe um ponteiro para um nodo e retorna a altura do nodo. Tempo: O(1)
     * 
     * @param node ponteiro para o noh do qual serah retornado sua altura.
     * 
     * @return a altura do nodo
     */
    int height(Node *node) {
        if(node == nullptr) return 0;
        else return node->height;
    }

    /**
     * @brief calcula e retorna o fator de balanceamento de um node
     * 
     * @param node ponteiro para um node
     * 
     * @return fator de balanceamento daquele node
     */
    int balance(Node *node) {
        return height(node->right) - height(node->left);
    }

    /**
     * @brief executa uma rotacao direita em um node passado como parametro. Tempo O(1)
     * 
     * @param p ponteiro do node a ser realizado uma rotacao direita
     * 
     * @return retorna raiz da nova arvore depois da rotacao
     */
    Node *right_rotation(Node *p) {
        Node *u = p->left;
        p->left = u->right;
        u->right = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));

        this->m_counter_rotation++;

        return u;
    }

    /**
     * @brief executa uma rotacao esquerda em um node passado como parametro. Tempo O(1)
     * 
     * @param p ponteiro do node a ser realizado uma rotacao esquerda
     * 
     * @return retorna raiz da nova arvore depois da rotacao
     */
    Node *left_rotation(Node *p) {
        Node *u = p->right;
        p->right = u->left;
        u->left = p;
        p->height = 1 + std::max(height(p->left), height(p->right));
        u->height = 1 + std::max(height(u->left), height(u->right));

        this->m_counter_rotation++;
        
        return u;
    }

    /**
     * @brief Funcao privada recrusiva que insere um nodo na arvore. Caso o noh seja repetido,
     *        nada é feito. Caso tenha tido algum desbalanceamento, a arvore eh regulada
     *        usando o fixUpNode.
     * 
     * @param node raiz da arvore na qual sera feita a insercao
     * 
     * @param k chave que sera inserida
     * 
     * @param v valor que sera inserido
     * 
     * @return raiz para a nova arvore agora com o elemento inserido.
     */
    Node*_insert(Node *node, Key k, Value v) {

        if (node == nullptr){ // Caso base 1: árvore vazia
            this->m_size++;
            
            return new Node(k, v, 1, nullptr, nullptr);
        } 
        
        this->m_counter_comparator++;
        if (node->n_pair.first == k) { // Caso base 2: achei um nó repetido
            
            //encerra a insercao
            return node;
        }
        
        this->m_counter_comparator++;
        if (k < node->n_pair.first){ // Caso geral
            node->left = _insert(node->left, k, v);
        } else {
            node->right = _insert(node->right, k, v);
        }
        
        // código do retorna das chamadas recursivas
        node = fixup_node(node, k);   
        return node;
    }
    
    /** 
     * @brief funcao recursiva que busca um nó e o atualiza se ele existir. caso nao exista
     *        é retornado false.
     * 
     * @param k chave do nó a ser procurado
     * 
     * @param v novo valor do nó
     * 
     * @return True se e somente se o par tiver sido atualizado
     */
    bool _update(Node* node, Key k, Value v){
        
        // Caso de parada:
        // a chave nao existe
        if(node == nullptr) {
            return false;
        }

        // Caso de parada:
        //achei ou não achei a chave
        this->m_counter_comparator++;
        if(node->n_pair.first == k) {
            
            //atualiza o valor
            node->n_pair.second = v;
            return true;
        }

        // Caso geral: ainda nao achei 
        // e ainda tem arvore para percorrer
        this->m_counter_comparator++;
        if(k < node->n_pair.first){
            return _update(node->left, k, v);
        }else{
            return _update(node->right, k, v);
        }
    }


    /**
     * @brief Função que recebe um ponteiro para a raiz de uma árvore e verifica se é necessário fazer algum reblanaceamento nele.
     * Essa função também recalcula a altura do nó.
     * 
     * @param node raiz da subarvore que sera balanceada
     * 
     * @param k chave da raiz
     * 
     * @return raiz da arvore agora balanceada
     */
    Node *fixup_node(Node *node, Key k) {
        int bal = balance(node);
        
        if(bal < -1){
            
            this->m_counter_comparator++;
            // Caso 1(a)
            if(k < node->left->n_pair.first){
                return right_rotation(node);
                
            }
            
            this->m_counter_comparator++;
            // Caso 1(b)
            if(k > node->left->n_pair.first){
                node->left = left_rotation(node->left);
                return right_rotation(node);
            }
        }

        if(bal > 1){
            
            this->m_counter_comparator++;
            // Caso 2(a)
            if(k > node->right->n_pair.first){
                return left_rotation(node);
            }

            this->m_counter_comparator++;
            // Caso 2(b)
            if(k < node->right->n_pair.first){
                node->right = right_rotation(node->right);
                return left_rotation(node);
            }
        }
        
        // Caso node balanceado
        node->height = 1 + std::max(height(node->left), height(node->right));
        return node;
    }

    /**
     * @brief Funcao recursiva privada que recebe a raiz  de uma arvore e garante que todos os descendentes 
     * dessa raiz e a propria raiz sejam liberados para a memoria.
     * 
     * @param node raiz da funcao que vai ser limpada
     * 
     * @return Retorna nullptr indicando que a arvore ficou vazia.
     */
     Node *clear(Node *node) {
        if(node != nullptr) {
            node->left = clear(node->left);
            node->right = clear(node->right);
            delete node;
        }        

        return nullptr;
    }

    /**
     * @brief funcao recursiva que imprime a arvore em formato amigavel
     * 
     * @param node raiz da arvore a ser feita sua impressao
     * 
     * @param heranca string que eh usada ao longo da impressao
     */
    void bshow(Node *node, std::string heranca) {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->n_pair.first << ", " << node->n_pair.second << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }

    /**
     * @brief funcao que busca o noh atravez de um ponteiro para a raiz da arvore e a chave
     *        do noh a ser buscado
     * 
     * @param node raiz da arvore no qual o noh esta
     * 
     * @param k chave do noh a ser procurado
     * 
     * @return o noh se for achado, ou nullptr se ele nao existir
     */
    Node *contains(Node *node, Key k) {
        
        // Caso de parada: a chave nao existe
        if(node == nullptr){
            return node;
        }
        
        //Caso de parada: achei a chave
        this->m_counter_comparator++;
        if(node->n_pair.first == k) {
            return node;
        }

        // Caso geral: ainda nao achei 
        // e ainda tem arvore para percorrer
        this->m_counter_comparator++;
        if(k < node->n_pair.first){
            return contains(node->left, k);
        }else{
            return contains(node->right, k);
        }
    }


    /**
     * @brief funcao que procura o noh para ser feita sua remocao
     *        a busca eh feita atravez de sua chave. caso ele exista, ele é deletado.
     * 
     * @param node noh a ser removido
     * 
     * @param k chave do noh a ser removido
     * 
     * @return raiz para a nova arvore feita a remocao do noh e balanceada
     */
    Node *remove (Node *node, Key key) {
        if (node == nullptr) // node nao encontrado
            return nullptr;

        this->m_counter_comparator++;
        if (key < node->n_pair.first){
            node->left = remove(node->left , key);

        }else if (key > node->n_pair.first){
            this->m_counter_comparator++;
            node->right = remove(node->right, key);

        }else if (node->right == nullptr) {
            this->m_counter_comparator++;

            Node *child = node->left;
            delete node;

            this->m_size--;
            
            return child;
        }else {// tem filho direito : troca pelo sucessor
            this->m_counter_comparator++;

            node->right = remove_successor(node, node->right);
            node = fixup_deletion(node);

            return node;
        }
            

        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node);
        return node ;
    }

    /**
     * @brief função que remove o sucessor do noh passado e conserta a arvore o rebalanceando de acordo
     * 
     * @param root para a raiz da arvore na qual sera feita a remocao
     * 
     * @param node noh do qual sera removido seu sucessor
     * 
     * @return raiz para a nova arvore depois que esse processo for feito
     */
    Node *remove_successor(Node *root, Node *node){

        if (node -> left != nullptr ){
            node -> left = remove_successor(root , node -> left ) ;
            node = fixup_deletion(node);
            return node;
        }else {
            root->n_pair = node->n_pair;
            Node *aux = node->right;
            delete node;

            this->m_size--;
            
            return aux;
        }

        // Atualiza a altura do node e regula o node
        node = fixup_deletion(node);
        return node ;
    }

    /**
     * @brief conserta a remocao de um, fazendo rotacoes e balanceando a arvore
     * 
     * @param node ponteiro raiz da noh que sera balanceada depois de uma remocao
     *      
     * @return novo ponteiro da raiz para a arvore agora balanceada
     */
    Node *fixup_deletion(Node *node){
        node->height = 1 + std::max (height(node->left), height(node->right));
        int bal = balance(node);

        // node pode estar desregulado , ha 4 casos a considerar
        if (bal>1 && balance(node->right) >= 0){
            return left_rotation(node);
        }else if (bal > 1 && balance(node->right) < 0){
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }else if ( bal < -1 && balance(node->left) <= 0){
            return right_rotation(node);
        }else if ( bal < -1 && balance(node->left) > 0){
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }

        return node;
    }  
    
    /**
     * @brief cria recursivamente a copia de uma arvore
     * 
     * @param aux ponteiro da raiz da arvore que serah copiada
     * 
     * @return ponteiro para a copia da arvore
     */
    Node* copia(Node *aux){
        if(aux == nullptr) return nullptr;

        Node *right = copia(aux->right);
        Node *left = copia(aux->left);

        int novaAltura = 1 + std::max(height(right), height(left));

        Node *node = new Node(aux->n_pair.first, aux->n_pair.second, novaAltura, left, right);

        return node;
    }

    /**
     * @brief verifica recursivamente se as arvores sao iguais ou nao
     *        eh usado como definicao de igualdade entre duas arvores
     *        se elas possuem elementos iguals (chave e valor) e a 
     *        a mesma organização de seus elementos
     * 
     * @param aux ponteiro para uma das arvores
     * 
     * @param outro ponteiro para a segunda arvore
     * 
     * @return True se forem iguais e False se nao
     */
    bool ehIgual(const Node *aux, const Node *outro) const{
        if(aux == nullptr && outro == nullptr){ //cheguei no final e nao deu false
            return true;
        }else if(aux == nullptr || outro == nullptr){
            return false;
        }else if(aux->n_pair != outro->n_pair){ //eh igual mas nao cheguei no final, logo continuo
            this->m_counter_comparator++;
            return false;
        }else{ //nao cheguei no final e eh diferente
           
            this->m_counter_comparator++;

            return ehIgual(aux->right, outro->right) && ehIgual(aux->left, outro->left);
        }
    }
    
    /**
     * @brief gera um arquivo de uma arvore em ordem
     */
    void imprimeArvore(Node* root, std::fstream &file){
        if(root==nullptr)
            throw std::invalid_argument("raiz da arvore é nul");
        
        Node* node = root;
        std::stack<Node*> pilha;
        file.open("fstream.txt", std::ios::in | std::ios::out | std::ios::trunc);      
        while(!pilha.empty() || node != nullptr){
            if(node != nullptr){
                pilha.push(node);
                node = node->left;
            }else{
                node = pilha.top();
                pilha.pop();

                //coloca node no arquivo
                file << node->n_pair.first << " " << node->n_pair.second << std::endl;

                node = node->right;
            }
        }

    }

};


#endif