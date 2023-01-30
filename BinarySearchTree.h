#pragma once

#include <functional> // std::less
#include <iostream>
#include <queue> // std::queue
#include <utility> // std::pair

template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
  public:
    using key_type        = K;
    using value_type      = V;
    using key_compare     = Comparator;
    using pair            = std::pair<key_type, value_type>;
    using pointer         = pair*;
    using const_pointer   = const pair*;
    using reference       = pair&;
    using const_reference = const pair&;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

  private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const_reference theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( pair && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    using node           = BinaryNode;
    using node_ptr       = node*;
    using const_node_ptr = const node*;

    node_ptr _root;
    size_type _size;
    key_compare comp;

  public:
    BinarySearchTree(): _root{nullptr}, _size{0} {
        // TODO
    }
    BinarySearchTree( const BinarySearchTree & rhs ): _size{rhs._size} {
        // TODO
        this->_root = clone(rhs._root);
    }
    BinarySearchTree( BinarySearchTree && rhs ):_size{rhs._size}, _root{rhs._root} {
        // TODO
        rhs._root = nullptr;
        rhs._size = 0;
    }
    ~BinarySearchTree() {
        // TODO
        clear();
    }

    const_reference min() const { return min( _root )->element; }
    const_reference max() const { return max( _root )->element; }
    const_reference root() const {
        // TODO
        return _root->element;
    }
    bool contains( const key_type & x ) const { return contains( x, _root ); }
    value_type & find( const key_type & key ) { return find( key, _root )->element.second; }
    const value_type & find( const key_type & key ) const { return find( key, _root )->element.second; }
    bool empty() const {
        // TODO
        return _size == 0;
    }
    size_type size() const {
        // TODO
        return _size;
    }

    void clear() {
        clear( _root );
        _size = 0;
    }
    void insert( const_reference x ) { insert( x, _root ); }
    void insert( pair && x ) { insert( std::move( x ), _root ); }
    void erase( const key_type & x ) { erase(x, _root); }

    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        // TODO
        if (this == &rhs){
            return *this;
        }
        this->clear();
        this->_root = clone(rhs._root);
        this->_size = rhs._size;
        return *this;
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        // TODO
        if (this == &rhs){
            return *this;
        }
        this->clear();
        this->_root = rhs._root;
        this->_size = rhs._size;
        rhs._root = nullptr;
        rhs._size = 0;
    }

  private:
    void insert( const_reference x, node_ptr & t ) {
        // TODO
        //std::cout << x.first << " " << x.second << std::endl;
        if (t == nullptr){
            t = new BinaryNode(x, nullptr, nullptr);
            _size++;
            //std::cout << _size << " " << t << " " << _root << std::endl;
        }
        else if (comp(x.first, t->element.first))
        {
            //std::cout << x.first << " < " << t->element.first << std::endl;
            insert(x, t->left);
        }
        else if (x.first > t->element.first){
            //std::cout << x.first << " > " << t->element.first << std::endl;
            insert(x, t->right);
        }
        else
        {
            //std::cout << x.first << " == " << t->element.first << std::endl;
            t->element = x;
        }
    }
    void insert( pair && x, node_ptr & t ) {
        // TODO
        if (t == nullptr){
            t = new BinaryNode(std::move(x), nullptr, nullptr);
            _size++;
        }
        else if (comp(x.first, t->element.first))
        {
            insert(std::move(x), t->left);
        }
        else if (x.first > t->element.first){
            insert(std::move(x), t->right);
        }
        else
        {
            t->element = std::move(x);
        }
    }

    void erase( const key_type & x, node_ptr & t ) {
        // TODO -- Bonus
    }

    const_node_ptr min( const_node_ptr t ) const {
        // TODO
        const_node_ptr current = t;
        while (current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    const_node_ptr max( const_node_ptr t ) const {
        // TODO
        const_node_ptr current = t;
        while (current->right != nullptr){
            current = current->right;
        }
        return current;
    }

    bool contains( const key_type & x, const_node_ptr t ) const {
        // TODO
        if (t == nullptr){
            return false;
        }
        else{
            if (t->element.first == x){
                return true;
            }
            else if (comp(x,t->element.first)){
                return contains(x,t->left);
            }
            else if (x > t->element.first){
                return contains(x,t->right);
            }
        }
    }

    node_ptr find( const key_type & key, node_ptr t ) {
        // TODO
        while (t != nullptr){
            if (comp(key,t->element.first)){
                t = t->left;
            }
            else if (key > t->element.first){
                t = t->right;
            }
            else{
                return t;
            }
        }
    }
    const_node_ptr find( const key_type & key, const_node_ptr t ) const {
        // TODO
        while (t != nullptr){
            if (comp(key,t->element.first)){
                t = t->left;
            }
            else if (key > t->element.first){
                t = t->right;
            }
            else{
                return t;
            }
        }
    }

    void clear( node_ptr & t ) {
        // TODO
        if (t == nullptr){
            return;
        }
        clear(t->left);
        clear(t->right);
        delete t;
        t = nullptr;
    }
    
    node_ptr clone ( const_node_ptr t ) const {
        // TODO
        if (t == nullptr){
            return nullptr;
        }
        node_ptr root = new BinaryNode(t->element,t->left,t->right);
        if (t->left != nullptr){
            root->left = clone(t->left);
        }
        if (t->right != nullptr){
            root->right = clone(t->right);
        }
        return root;
    }

  public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend std::ostream& printNode(std::ostream& o, const typename BinarySearchTree<KK, VV, CC>::node& bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
        std::ostream & out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev
    );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> & bst, 
        std::ostream & out
    );
};

template <typename KK, typename VV, typename CC>
std::ostream& printNode(std::ostream & o, const typename BinarySearchTree<KK, VV, CC>::node & bn) {
    return o << '(' << bn.element.first << ", " << bn.element.second << ')';
}

template <typename KK, typename VV, typename CC>
void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out = std::cout ) {
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;
    
    // TODO -- Guide in Instructions
    if (bst._root == nullptr){
        return;
    }
    std::deque<node_ptr> levelTraverse;
    levelTraverse.push_back(bst._root);
    bool empty = true;
    size_t level = 0;
    do{
        empty = true;
        for (size_t i = 0; i < (1<<level); ++i){
            node_ptr popped = levelTraverse[0];
            if (popped == nullptr){
                out << "null ";
                levelTraverse.push_back(nullptr);
                levelTraverse.push_back(nullptr);
            }
            else
            {
                out << "(" << popped->element.first << ", " << popped->element.second << ") ";
                levelTraverse.push_back(popped->left);
                levelTraverse.push_back(popped->right);
                if (popped->left != nullptr || popped->right != nullptr){
                    empty = false;
                }
            }
            levelTraverse.pop_front();
        }
        out << std::endl;
        level++;
    }
    while(!empty);
}

template <typename KK, typename VV, typename CC>
void printTree( const BinarySearchTree<KK, VV, CC> & bst, std::ostream & out = std::cout ) { printTree<KK, VV, CC>(bst._root, out ); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth = 0 ) {
    if (t != nullptr) {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
    std::ostream & out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr
) {
    if(node) {
        std::hash<KK> khash{};

        out << "\t" "node_" << (uint32_t) khash(node->element.first)
            << "[label=\"" << node->element.first 
            << " [" << node->element.second << "]\"];" << std::endl;
        
        if(prev)
            out << "\tnode_" << (uint32_t) khash(prev->element.first) <<  " -> ";
        else
            out << "\t";
        
        out << "node_" << (uint32_t) khash(node->element.first) << ";" << std::endl;
    
        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> & bst, 
    std::ostream & out = std::cout
) {
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
