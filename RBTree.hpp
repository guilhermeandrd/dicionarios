/**
 * @file RBTree.hpp
 * @author Guilherme Andrade da Silva | Github: (@guilhermeandrd)
 * @brief Árvore Binária de Busca Rubro Negra (Arvore Rubro Negra)
 * Estrutura de dados avancada - 2025.1
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef RBTREE_HPP
#define RBTREE_HPP

//uso de booleao para a cor dos noh da rubro negra
#define RED true
#define BLACK false

#include <iostream>
#include <stack>
#include <utility>
#include <string>

/**
 * @brief implementacao da classe de arvore balanceada rubro negra,
 *        usando node para representacao dos seus nohs e tipos genericos
 *        para os seus pares
 * 
 * @tparam Key key type
 * 
 * @tparam Valeu value type
 */
template <typename Key, typename Value>
class RBtree{
private:

    /**
     * @brief estrutura auxiliar para os nohs da rubro negra, que usa tipos genericos
     */
    struct Node {

        bool color;
        std::pair <Key, Value> n_pair;
        Node* left;
        Node* right;
        Node* parent;     
        
        /**
        * @brief construtor para a estrutura node
        * 
        * @param k chave do par a ser inserido
        * 
        * @param v valor do par a ser inserido
        * 
        * @param color cor do noh a ser inserido (vermelho ou preto)
        * 
        * @param l ponteiro para noh esquerdo
        * 
        * @param r ponteiro para noh direito
        * 
        * @param p ponteiro para noh pai
        */
        Node(Key k, Value v, bool color, Node* l, Node* r, Node* p){
            this->n_pair = std::make_pair(k, v);
            this->color = color;
            left = l;
            right = r;
            parent = p;
        }

        ~Node() = default;
    };

    //raiz da arvore
    Node* root;

    //noh nil que vai ser usado para os codigos e etc
    Node* nil;

    //contador de rotacoes da arvore
    mutable size_t m_counter_rotation;

    //contador de comparacoes
    mutable size_t m_counter_comparator;

    //tamanho da tabela (quantos nohs ela tem)
    size_t m_size;

    
public:

    /**
     * @brief construtor default para a rubro negra.
     *        inicializa o nil e o root com par que tem valores defaults.
     *        a raiz eh preta e nil tambem.
     *        nil aponta para valores nulos no comeco e depois o fazemos apontar para ele mesmo.
     *        enquanto root aponta tambem para o noh nil.
     *        contadores e tamanho comecam com 0.
     * 
     */
    RBtree(){
        nil = new Node(Key(), Value(), BLACK, nullptr, nullptr, nullptr);
        nil->left = nil->right = nil;
        root = nil;
        root->parent = nil;
        m_counter_rotation = 0;
        m_counter_comparator = 0;
        m_size = 0;
    }

    /**
     * @brief funcao insert que insere um par de chave e valor na arvore. aqui criamos o noh a ser inserido 
     *        e chamos outra funcao que o realmente insere ao mesmo tempo que chama outras que regulam a arvore.
     *        todo noh que eh inserido comeca com a cor vermelha. cas o noh ja exista, o atualizamos e retornamos false.
     * 
     * @param k:= chave do par a ser inserido
     * @param v:= valor do par a ser inserido
     * 
     * @return True se e somente se o noh tiver sido inserido.
     */
    bool insert(Key k, Value v){
        Node *novo = new Node(k, v, RED, nullptr,nullptr, nullptr); //cria novo node a ser inserido como
        return _insert(novo);
    }
   
    /**
     * @brief remove noh que tem aquela respectiva chave caso ele exista. caso nao, nao faz nada. 
     *        tambem chama uma funcao auxiliar que realmente o remove.
     *      
     * @param k chave do noh a ser removido
     */
    void remove(const Key k){
        Node*p = root;

        while(p != nil && p->n_pair.first!=k){
            this->m_counter_comparator++;

            if(k < p->n_pair.first){
                this->m_counter_comparator++;

                p = p->left;
            }else{
                this->m_counter_comparator++;

                p = p->right;
            }
        }

        if(p != nil){
            _remove(p);
        }
    }

    /**
     * @brief verifica se um noh existe atraves de sua chave o pecorrendo de maneira iterativa
     * 
     * @param k chave do noh a ser procurado
     * 
     * @return True se existir, False se nao
     */
    bool contains(const Key k){
        Node*p = root;

        while(p != nil && p->n_pair.first!=k){
            //incrementa sempre por conta do while
            this->m_counter_comparator++;
            
            if(k < p->n_pair.first){
                this->m_counter_comparator++;

                p = p->left;
            }else{
                this->m_counter_comparator++;

                p = p->right;
            }

        }

        return p != nil;
    }

    /**
     * @brief faz uma busca pelo noh atraves de sua chave e retorna uma referencia
     * desse respectivo valor
     * 
     * @param k chave do noh que sera retornado seu valor
     * 
     * @return valor relacionada aquela chave
     */
    Value& at(const Key& k){
         Node*p = root;

        while(p != nil && p->n_pair.first!=k){
            //incrementa sempre por conta do while
            this->m_counter_comparator++;
            
            if(k < p->n_pair.first){
                this->m_counter_comparator++;

                p = p->left;
            }else{
                this->m_counter_comparator++;

                p = p->right;
            }

        }

        if(p == nil){
            throw std::out_of_range("arvore nao contem essa chave");
        }

        return p->n_pair.second;
    }

    /**
     * @brief faz uma busca pelo noh atraves de sua chave e retorna uma referencia constante
     * desse respectivo valor
     * 
     * @param k chave do noh que sera retornado seu valor
     * 
     * @return valor relacionada aquela chave
     */
    const Value& at(const Key& k) const{
        Node*p = root;

        while(p != nil && p->n_pair.first!=k){
            //incrementa sempre por conta do while
            this->m_counter_comparator++;
            
            if(k < p->n_pair.first){
                this->m_counter_comparator++;

                p = p->left;
            }else{
                this->m_counter_comparator++;

                p = p->right;
            }

        }

        if(p == nil){
            throw std::out_of_range("arvore nao contem essa chave");
        }

        return p->n_pair.second;
    }

    /**
     * @brief imprime a rubro negra em formato amigavel (chave, valor) e do lado sua cor em formato de string.
     * Tambem imprime os nós nils. Caso esteja vazia, imprime somente o noh nil;
     */
    void show(){

        rb_show(root, "");

    }

    /**
     * @brief verifica se a arvore esta vazia ou nao. uma arvore eh considerada vazia se soh tiver a raiz e o noh nil.
     * 
     * 
     * @return True se for vazia, False se nao
     */
    bool empty() const{
        return root == nil;
    }

    /**
     * @brief retorna quantas rotacoes a arvore ja fez durante suas funcoes ja realizadas
     * 
     * @return o numero de rotacoes no tipo size_t
     */
    size_t counter_rotation() const{
        return m_counter_rotation;
    }

    /**
     * @brief retorna quantas comparacoes de chaves a arvore ja fez durante suas funcoes ja realizadas
     * 
     * @return o numero de comparacoes de chaves no tipo size_t
     */
    size_t counter_comparator() const{
        return m_counter_comparator;
    }

     /**
     * @brief retorna o numero de nohs da arvore (seu tamanho)
     * 
     * @return o numero de nohs no tipo size_t
     */
    size_t size() const{
        return m_size;
    }
    
    /**
     * @brief limpa a arvore removendo todos os seus noh e fazendo o root apontar para nil.
     *        chama uma funcao privada que realmente o limpa. por fim, todos os contadores
     *        e tamanho sao zerados.
     *
     */
    void clear(){
        clear(root);
        root = root->left = root->right = nil;
        m_counter_rotation = 0;
        m_counter_comparator = 0;
        m_size = 0;
    }
    
    /**
     * @brief destrutor que usa o clear da rubro negra e por ultimo deleta o nil
     */
    ~RBtree(){
        clear();
        delete nil;
    }

    /**
     * @brief sobrecarga do operador de atribuicao. a arvore serah igual a que foi passada
     *        como parametro. seus contadores tambem serao copiados, assim como seu tamanho.
     * 
     * @param outra arvore a qual sera "copiada"
     * 
     * @return a arvore se torna igual a que foi passada como parametro
     */
    RBtree& operator=(const RBtree& outra){

        //verificamos se o endereco nao eh o mesmo para evitar autoatribuicao
        if(this != &outra){
            clear();
            this->root = copia(outra.root, this->nil);
            this->m_counter_rotation = outra.m_counter_rotation;
            this->m_size = outra.m_size;
            this->m_counter_comparator = outra.m_counter_comparator;        
        }

        return *this;
    }

    /**
     * @brief sobrecarga do construtor de copia. os constadores e tamanho tambem sao copiados.
     * 
     * @param outra arvore que serah copiada
     */
    RBtree(const RBtree& outra) : RBtree(){ //primeiro criamos a arvore usando o construtor default

        this->root = copia(outra.root, nil);
        this->m_counter_rotation = outra.m_counter_rotation;
        this->m_size = outra.m_size;
        this->m_counter_comparator = outra.m_counter_comparator;
    }

    /**
     * @brief  sobrecarga do operador de diferenca. faz uso de uma funcao privada recursiva.
     * 
     * @param outra arvore que sera comparada.
     * 
     * @return True se for diferente, False se nao 
     */
    bool operator!=(const RBtree& outra) const{
        return !(ehIgual(this->root, outra.root));
    }

    /**
     * @brief sobrecarga do operador de igualdade. faz uso de uma funcao privada recursiva. uma arvore rubro negra eh igual
     *        se todos os seus nohs sao os mesmos assim como a disposicao deles e as suas cores.
     * 
     * @param outra arvore a ser comparada
     * 
     * @return True se for igual, False se nao
     */
    bool operator==(const RBtree& outra) const{
        return ehIgual(root, outra.root);
    }

    //AS SOBRECARGAS FORAM FEITAS PARA MELHOR FUNCIONAMENTO DO CODIGO

private:

    /**
     * @brief funcao privada insere um noh que ja foi criado. tambem usamos
     *        uma funcao auxiliar que regula a arvore, caso ela nao estja mais balanceada.
     * 
     * @param z noh que ja foi previamente criado
     * 
     */
    bool _insert(Node* z){
        Node* x = this->root;
        Node* y = this->nil;

        while (x!= this->nil){
            y=x;
            if (z->n_pair.first < x->n_pair.first){
                this->m_counter_comparator++;
                
                x = x->left;
            }else if (z->n_pair.first > x->n_pair.first){
                this->m_counter_comparator+=2;

                x = x->right;
            } else{
                //se nao eh maior e nem menor eh igual                
                this->m_counter_comparator+=2;

                //atualizamos o valor
                x->n_pair.second = z->n_pair.second;

                delete z; //z nao vai ser usado, liberamos sua memoria

                return false;
            }
        }

        z->parent = y;

        if (y == this->nil){
            this->root = z;
        }else if (z->n_pair.first < y->n_pair.first) {
            this->m_counter_comparator++;

            y->left = z;
        }else{
            this->m_counter_comparator++;

            y->right = z;
        }

        z->left = this->nil;
        z->right = this->nil;
        z->color = RED;
        
        
        insertFixup(z);
        m_size++;
        return true;
    }

    /**
     * @brief verificamos se a arvore foi desbalanceada. caso tenha sido, a consertamos
     * 
     * @param z noh que foi inserido na funca insert
     */
    void insertFixup(Node* z){
        while(z->parent->color == RED){
            if(z->parent == z->parent->parent->left){
                Node* y = z->parent->parent->right;

                if(y->color == RED){
                    z->parent->color = BLACK; //caso 1
                    y->color = BLACK; //caso 1
                    z->parent->parent->color = RED; //caso 1
                    z = z->parent->parent;
                }else{
                    if(z == z->parent->right){
                        z = z->parent;       //caso 2a
                        leftRotate(z); //caso 2a
                    }
                    z->parent->color = BLACK; //caso 3a
                    z->parent->parent->color = RED; //casp 3a
                    rightRotate(z->parent->parent); //caso 3a
                }
            }else{
                //caso simehtrico
                Node* y = z->parent->parent->left;
                if(y->color == RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }else{
                    if(z == z->parent->left){
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        this->root->color = BLACK;
    }

    /**
     * @brief realiza a rotacao esquerda em um noh
     * 
     * @param x noh em que vai ser realizada a rotacao
     */
    void leftRotate(Node* x){
        Node* y = x->right;

        x->right = y->left;

        if(y->left != this->nil){
            y->left->parent = x;
        }

        y->parent = x-> parent;

        if(x->parent == this->nil){
            this->root = y;
        }else if(x== x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        this->m_counter_rotation++;
    }

     /**
     * @brief realiza a rotacao direita em um noh
     * 
     * @param x noh em que vai ser realizada a rotacao
     */
    void rightRotate(Node* x){
        Node* y = x->left;

        x->left = y->right;

        if(y->right != this->nil){
            y->right->parent = x;
        }

        y->parent = x->parent;

        if(x->parent == this->nil){
            this->root = y;
        }else if(x == x->parent->right){
            x->parent->right = y;
        }else{
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;

        this->m_counter_rotation++;
    }

    /**
     * @brief código de rb_transplant retirado do livro do Cornen.
     * usado para movimentar subárvores dentro da árvore rubro negra, que substitui uma subárvore como um 
     * filho de seu pai por uma outra subárvore. Quando substitui a subárvore enraizada no nó u pela 
     * subárvore enraizada no nó v, o pai do nó u torna​se o pai do nó v, e o pai de u acaba ficando 
     * com v como seu filho adequado. O código r_transplant foi adaptado para lidar com arvore rubro negra 
     * sem a desregular, tomando cuidados como: 
     * 1 - referenciar o nil da arvore, em vez de NIL. O que o c++ faz implicitamente.
     * 2 - a atribuição a .parent na linha 569 ocorre incondicionalmente, no algorimo do cornen: 
     * podemos atribuir a v.parent mesmo que aponte para a sentinela. 
     * Mas nesse código, tomamos cuidado para fazer isso quando v for diferente de nil, 
     * pois //TODO ver isso aqui
     */
    void rb_transplat(Node* u, Node* v){
        if(u->parent == nil){
            root = v;
        }else if(u == u->parent->left){
            u->parent->left = v;
        }else{
            u->parent->right = v;
        }

        if(v != nil)
            v->parent = u->parent;
    }

    /**
     * @brief remove o noh passado como parametro. considera os dois casos principais: 
     *        noh tem só um filho ou noh tem os dois filhos. no segundo caso, é usado uma funcao
     *        que busca o seu sucessor. apos isso, ele conserta a arvore, caso tenha se desregulado.
     * Faz uso da funcao rb_transplant para ajudar a remover o noh.
     * @param z noh a ser removido
     */
    void _remove(Node *z){
        Node* y = z;
        Node* x;
        bool  y_color_original = y->color;

        //Caso 1(a):  Quando queremos eliminar o nó z e z nao tem o filho esquerdo, e 
                    // z é removido da árvore e queremos que y seja z
        if(z->left == this->nil){
            x = z->right;
            rb_transplat(z, z->right);
        //Caso 1(b):  Quando queremos eliminar o nó z e z nao tem o filho direito,
                    // z é removido da árvore e queremos que y seja z
        }else if( z->right == this->nil){
            x = z->left;
            rb_transplat(z, z->left);
        }else{
        //Caso 2 : Quando z tem dois filhos, y deve ser o sucessor de z , e y passa 
                // para a posição de z na árvore

            y = minimum(z->right); //y eh igual a sucessor de z 

            /*
            Também lembramos a cor de y antes de ele ser eliminado da árvore ou passar para dentro dela, 
            e rastreamos o nó x que passa para a posição original de y na árvore 
            porque o nó x também poderia causar violações das propriedades vermelho-preto
            */

            y_color_original = y->color;
            x = y->right;

            if(y->parent == z){
                if(x != nil) x->parent = y; //TODO verificar o porque dessa verificacao
            }else{
                rb_transplat(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rb_transplat(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        if(y_color_original == BLACK){
            removeFixup(x);
        }

        delete z; //desaloca a memoria daquele noh

        m_size--; //diminui o size dessa rubro negra
    }

    /**
     * @brief conserta a arvore depois da remocao de um noh. eh usado
     * algoritmos de colorações e rotacoes para cada caso.
     * 
     * @param x um dos filhos do noh que foi deletado
     */
    void removeFixup(Node *x) {
        while (x != root && x->color == BLACK) {

            //x é um filho esquerdo
            if (x == x->parent->left) {
                Node *w = x->parent->right; // w é o irmão de x

                //caso 1: w é vermelho
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right; //w agora é preto e passamos para os casos 2, 3 ou 4
                }

                //caso 2: w é preto e ambos seus filhos são pretos
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent; //joga o problema uma ancestral;
                } else {
                    //caso 3: w é preto, e seu filho esquerdo é vermelho, direito é preto
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    
                    //caso 4: w é preto e seu filho direito é vermelho
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root; //problema resolvido, forçamos o fim do loop
                }
            } else { //se x é um filho direito (lógica simétrica)
                Node *w = x->parent->left; // w é o irmão de x

                // Caso 1
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                
                //caso 2
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    //caso 3
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    
                    //caso 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }

        x->color = BLACK;

    }


    /**
     * @brief procura o minimo uma arvore e o retorna caso ele exista.
     * 
     * @param node raiz da arvore a qual vai ser buscada seu minimo
     * 
     * @return sucessor do noh 
     */
    Node* minimum(Node* node){
    
        
        while(node->left != nil){
            node = node->left;
        }

        return node;
    }

    /**
     * @brief imprime recursivamente a arvore, imprimindo seus pares e as cores dos nohs
     * 
     * @param node raiz da arvore da qual 
     * 
     * @param heranca string que sera usada de maneira auxiliar para ajudar na impressao
     * 
     */
    void rb_show(Node *node, std::string heranca){
        //funcao que imprime os valores da arvore em ordem

        if(node != nil && (node->left != nullptr || node->right != nullptr))
            rb_show(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nil){
            std::cout << "nil" << std::endl;
            return;
        }

        std::string cor;
        if(node->color==BLACK){
            cor = "BLACK";
        }else{
            cor = "RED";
        }

        std::cout << node->n_pair.first << ", " << node->n_pair.second << " " << cor << std::endl;
        if(node != nil && (node->left != nullptr || node->right != nullptr))
            rb_show(node->left, heranca + "l");
    
    }

    /**
     * @brief funcao recursiva que copia uma arvore usando a raiz dessa arvore 
     *        e retorna a raiz agora com os nohs copiados
     * 
     * @param aux raiz vai ser copiada
     * 
     * @param pai raiz da arvore que vai receber as copias
     * 
     * @return raiz para arvore agora como copia de uma outra arvore
     */
    Node* copia(Node *aux, Node *pai){

        //verifica por seguranca se por algum acaso eh nullptr
        //verifica se eh nil, verificando se o noh esquerdo aponta para ele mesmo
        //pois o nil eh o unico noh que faz isso
        //sendo desnecessario a comparacao com a direita
        //e depois retorna o nil da arvore que estamos criando
        if(aux == nullptr || aux->left == aux) return this->nil;
        
        Node *node = new Node(aux->n_pair.first, aux->n_pair.second, aux->color, this->nil, this->nil, pai);
        
        node->right = copia(aux->right, node);
        node->left = copia(aux->left, node);

        return node;
    }

    /**
     * @brief funcao que recursivamente verifica se as arvores sao iguais atraves de seus nohs.
     *        noh sao iguais se tem chave, valor e cor iguais.
     * 
     * @param aux raiz da primeira arvore da comparacao
     * 
     * @param outro raiz da segunda arvore da comparacao
     * 
     * @return True se forem iguais, False se nao forem
     */
    bool ehIgual(const Node *aux, const Node *outro) const{

        //caso de parada, cheguei no nil e nao encontrei nenhuma diferenca
        if(aux == nil && outro == nil){
            return true;
        }else if(aux == nil || outro == nil){ //se soh uma das duas for nil
            return false;
        }else if(aux->n_pair != outro->n_pair || aux->color != outro->color){ //se os parem forem diferentes ou as cores forem diferenes
                                                                              //entao o noh como um todo eh diferente
            m_counter_comparator++;

            return false;
        }else{ 
            m_counter_comparator++;

            //continua a verificao para cada uma de suas subarvores
            return ehIgual(aux->right, outro->right) && ehIgual(aux->left, outro->left);
        }
    }  

    /**
     * @brief limpa recursivamente a arvore, menos o node nil
     * 
     * @param node raiz da arvore a ser limpada
     */
    void clear(Node* node) {

        if (node == nil) return;

        clear(node->left);

        clear(node->right);

        delete node;
    }
};

#endif //END_RB_TREE_HPP