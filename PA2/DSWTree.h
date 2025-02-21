#ifndef DSWTREE_H
#define DSWTREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod { preorder, inorder, postorder };

template<class T>
class DSWTree {
public: // DO NOT CHANGE THIS PART.
    DSWTree();

    DSWTree(const DSWTree<T>& obj);

    ~DSWTree();

    bool isEmpty() const;

    int getHeight() const;

    const int getNodeHeight(const T& element) const;

    int getSize() const;

    bool insert(const T& element);

    bool remove(const T& element);

    void removeAllNodes();

    const T& get(const T& element) const;

    void print(TraversalMethod tp = inorder) const;

    void printPretty() const;

    DSWTree<T>& operator=(const DSWTree<T>& rhs);

    bool isBalanced();

    void balance();

    void createBackbone(Node<T>*& root);

    void createCompleteTree(Node<T>*& root, int size);

    const T& getCeiling(const T& element) const;

    const T& getFloor(const T& element) const;

    const T& getMin() const;

    const T& getMax() const;

    const T& getNext(const T& element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T>* node, TraversalMethod tp) const;
    void printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const;
    Node<T>* traversAndmakeNode(Node<T>*& node, Node<T>* othernode) const;
    int tree_height(Node<T>* root)const;
    int intsayaci(Node<T>* root)const;
    void silici(Node<T>* root)const;
    Node<T>* inserthelper(const T& element, Node<T>*& root) const;
    void removehelper(const T& eleman, Node<T>*& node)const;
    void height_update(Node<T>* node)const;
    bool isInside(Node<T>* node, T element) const;
    bool isbalance_helper(Node<T>* root) const;
    int getnodehelper(T element, Node<T>* node) const;
    void createhelper(Node<T>*& node);
    void rotateWithLeftChild(Node<T>*& k2);
    void rotateWithRightChild(Node<T>*& k2);
    //void ceilhelper(const T& element, T& element2,Node<T>*node,int &flag) const;


private: // DO NOT CHANGE THIS PART.
    Node<T>* root;
};
//****************************************
//****************************************
template<class T>
Node<T>* DSWTree<T>::traversAndmakeNode(Node<T>*& node, Node<T>* othernode) const {
    if (othernode == NULL) {
        node = NULL;
        return node;
    }
    if (othernode != NULL) {

        Node<T>* newnode = new Node<T>(othernode->element, NULL, NULL, 0);
        node = newnode;
        if (node != NULL) {
            traversAndmakeNode(node->left, othernode->left);

            traversAndmakeNode(node->right, othernode->right);
        }
        return node;
    }





}

template<class T>
DSWTree<T>::DSWTree() {
    root = NULL;
    /* TODO */
}
//****************************************
//****************************************

template<class T>
DSWTree<T>::DSWTree(const DSWTree<T>& obj) {
    /* TODO */
    root = NULL;


    if (obj.root != NULL) {
        traversAndmakeNode(root, obj.root);
        if (root != NULL)
            root->height = obj.root->height;
    }
    height_update(root);



}

//****************************************
//****************************************

template<class T>
void DSWTree<T>::silici(Node<T>* node) const {
    if (node != NULL) {
        silici(node->left);
        silici(node->right);
        delete node;
    }
}

template<class T>
DSWTree<T>::~DSWTree() {
    /* TODO */
    silici(root);
}
//****************************************
//****************************************

template<class T>
bool DSWTree<T>::isEmpty() const {
    if (root == NULL) {
        return true;
    }
    else {
        return false;
    }
    /* TODO */
}

//****************************************
//****************************************
template<class T>
int DSWTree<T>::tree_height(Node<T>* root) const {
    if (root == NULL)
        return -1;
    else {
        return 1 + std::max(tree_height(root->left), tree_height(root->right));
    }
}

template<class T>
void DSWTree<T>::height_update(Node<T>* node)const {
    if (node == NULL) {
        return;
    }
    node->height = tree_height(node);
    height_update(node->right);
    height_update(node->left);
}

template<class T>
bool DSWTree<T>::isInside(Node<T>* node, T element) const
{
    if (node == NULL) {
        return false;
    }
    if (node->element > element) {
        return isInside(node->left, element);
    }
    else if (node->element < element) {
        return isInside(node->right, element);
    }
    else {
        return true;
    }
}

template<class T>
int DSWTree<T>::getHeight() const {
    /* TODO */
    if (root == NULL) {
        return -1;
    }
    else {
        return tree_height(root);
    }
}
//****************************************
//****************************************


template<class T>
int DSWTree<T>::intsayaci(Node<T>* root) const {
    if (root == NULL) {
        return 0;
    }
    else {
        return intsayaci(root->left) + intsayaci(root->right) + 1;
    }
}

template<class T>
int DSWTree<T>::getSize() const {
    /* TODO */
    if (root == NULL) {
        return 0;
    }
    else {
        return intsayaci(root);
    }
}
//****************************************
//****************************************
template <class T>
Node<T>* DSWTree<T>::inserthelper(const T& element, Node<T>*& root) const {
    if (root == NULL) {


        Node<T>* newnode = new Node<T>(element, NULL, NULL, 0);


        return newnode;
    }

    if (element < root->element)
    {

        root->left = inserthelper(element, root->left);

    }
    else if (element > root->element)
    {

        root->right = inserthelper(element, root->right);
    }

    return root;
}

template<class T>
bool DSWTree<T>::insert(const T& element) {
    /* TODO */
    root = inserthelper(element, root);
    height_update(root);
    return true;
}


template<class T>
void DSWTree<T>::removehelper(const T& eleman, Node<T>*& node)const {

    if (node == NULL) {
        return;
    }
    if (eleman < node->element)
    {

        removehelper(eleman, node->left);

    }
    else if (eleman > node->element)
    {
        removehelper(eleman, node->right);
    }
    else {
        if (node->right != NULL && node->left != NULL) {
            Node<T>* curr = node->right;
            while (curr->left != NULL) {
                curr = curr->left;
            }
            node->element = curr->element;
            removehelper(node->element, node->right);
        }
        else {
            Node<T>* curr = node;
            if (node->left != NULL) {
                node = node->left;
            }
            else {
                node = node->right;
            }
            delete curr;
        }

    }
}


template<class T>
bool DSWTree<T>::remove(const T& element) {
    /* TODO */
    if (root == NULL) {
        return false;
    }
    if (isInside(root, element)) {
        removehelper(element, root);
        height_update(root);
        return true;
    }
    else { return false; }

    // buraya bir tane isInside func ekle ve içinde yoksa direk 0 döndür, varsa fonskyonu cagir.


}

template<class T>
void DSWTree<T>::removeAllNodes() {
    /* TODO */

    silici(root);
    root=NULL;
    
}

template<class T>
const T& DSWTree<T>::get(const T& element) const {
   Node<T>* node = root;
   
   while (node != NULL) {
       if (element== node->element) {
           return node->element;
       }else if (element <node->element) {
           node= node->left;
       }else {
           node =node->right; 
       }
   }
   throw NoSuchItemException();
}

template<class T>
void DSWTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
}

template<class T>
void DSWTree<T>::print(Node<T>* node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (node == NULL)
            return;
        std::cout << "\t" << node->element;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);


        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    }
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == postorder) {
        /* TODO */
        if (node == NULL)
            return;

        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }



        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
}

template<class T>
void DSWTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void DSWTree<T>::printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
DSWTree<T>& DSWTree<T>::operator=(const DSWTree<T>& rhs) {
    /* TODO */
    removeAllNodes();


    if (rhs.root != NULL) {
        traversAndmakeNode(root, rhs.root);
        if (root != NULL)
            root->height = rhs.root->height;
    }
}

template <class T>
void DSWTree<T>::balance() {
    /* TODO */
    if (root != NULL) {
        createBackbone(root);
        

        createCompleteTree(root, getSize());
        
    }
    height_update(root);

}

template<class T>
bool DSWTree<T>::isbalance_helper(Node<T>* root) const
{
    if (root == NULL) {
        return true;
    }

    if (std::abs(tree_height(root->left) - tree_height(root->right)) > 1) {
        return false;
    }
    else {
        return isbalance_helper(root->left) && isbalance_helper(root->right);
    }
}


template <class T>
bool DSWTree<T>::isBalanced() {
    /* TODO */
    return isbalance_helper(root);

}



/*
template<class T>
void DSWTree<T>::createhelper(Node<T>* &node) {
    if (node == NULL) { return; }
    if (node->left) {
        Node<T>* left = node->left;
        Node<T>* curr = left->right;
        node->left = curr;
        left->right = node;
        node = left;

        height_update(left);
        height_update(left->right);

        createhelper(node);
    }
    else {
        createhelper(node->right);
    }
}

template <class T>
void DSWTree<T>::createBackbone(Node<T>*& root) {

    if (root == NULL) {
        return;
    }
    createhelper(root);
}*/


template <class T>
void DSWTree<T>::rotateWithLeftChild(Node<T>*& k2)
{
    Node<T>* k1 = k2;
    k2 = k2->left;
    k1->left = k2->right;
    k2->right = k1;
}

template <class T>
void DSWTree<T>::rotateWithRightChild(Node<T>*& k2)
{
    Node<T>* k1 = k2;
    k2 = k2->right;
    k1->right = k2->left;
    k2->left = k1;
    
}


template<class T>
void DSWTree<T>::createhelper(Node<T>*& node) {
    if (node == NULL) { return; }
    if (node->left) {
        rotateWithLeftChild(node);

        createhelper(node);
        height_update(node);
    }
    else {

        createhelper(node->right);
        height_update(node);
    }




}

template <class T>
void DSWTree<T>::createBackbone(Node<T>*& root) {
    /* TODO */
    if (root == NULL) {
        return;
    }

    createhelper(root);
}

template<class T>
void DSWTree<T>::createCompleteTree(Node<T>*& root, int size) {

    int m = std::pow(2, floor(std::log(size + 1) / std::log(2))) - 1;
    int logm = size - m;
    Node<T>* temp = root;
    Node<T>* prev = NULL;
    int flag = 0;
    while (logm > 0) {
        rotateWithRightChild(temp);
        Node<T>* prevroot = temp;
        if (flag == 0) {
            root = prevroot;
        }
        else prev->right = prevroot;
        flag = 1;
        temp = prevroot;
        prev = temp;
        temp = temp->right;
        logm = logm - 1;
    }



    while (m > 1) {
        m = m / 2;
        Node<T>* temp = root;
        Node<T>* prev = NULL;
        for (int flag2 = 0; flag2 < m; flag2++) {
            rotateWithRightChild(temp);
            Node<T>* prevroot = temp;
            if (flag2 == 0) {
                root = prevroot;
            }
            else prev->right = prevroot;
            temp = prevroot;
            prev = temp;
            temp = temp->right;

        }

    }

    height_update(root);
}

template <class T>
const T &DSWTree<T>::getCeiling(const T &element) const {
    if (root == NULL) {
        throw NoSuchItemException();
    }
    Node<T>* curet=root;
    Node<T>* target=NULL;
    /*todo*/
    
    while(curet){
        if(curet->element >= element){
            target=curet;
            curet=curet->left;
        }else{
            curet=curet->right;
        }
        
    }
    
    if(target==NULL){
        throw NoSuchItemException();
    }
   
    return target->element;
}




template<class T>
const T& DSWTree<T>::getFloor(const T& element) const {
    /* TODO */
    if (root == NULL) {
        throw NoSuchItemException();
    }
    Node<T>* curet=root;
    Node<T>* target=NULL;

    
    while(curet){
        if(curet->element <= element){
            target=curet;
            curet=curet->right;
        }else{
            curet=curet->left;
        }
        
    }
    
    if(target==NULL){
        throw NoSuchItemException();
    }
   
    return target->element;
}


template<class T>
const T& DSWTree<T>::getMin() const {
    /* TODO */
    if (root == NULL) {
        throw NoSuchItemException();
    }
    Node<T>* curr = root;
    while (curr && curr->left != NULL) {
        curr = curr->left;
    }
    return curr->element;

}




template<class T>
const T& DSWTree<T>::getMax() const {
    /* TODO */
    if (root == NULL) {
        throw NoSuchItemException();
    }
    Node<T>* curr = root;
    while (curr && curr->right != NULL) {
        curr = curr->right;
    }
    return curr->element;
}
template<class T>
const T& DSWTree<T>::getNext(const T& element) const {
    /* TODO */
    /* TODO */
    if (root == NULL) {
        throw NoSuchItemException();
    }
    Node<T>* curet=root;
    Node<T>* target=NULL;

    
    while(curet){
        if(curet->element > element){
            target=curet;
            curet=curet->left;
        }else{
            curet=curet->right;
        }
        
    }
    
    if(target==NULL){
        throw NoSuchItemException();
    }
   
    return target->element;
}

template<class T>
int DSWTree<T>::getnodehelper(T element, Node<T>* node) const {
    if (node != NULL) {


        if (node->element > element) {
            getnodehelper(element, node->left);
        }
        else if (node->element < element) {
            getnodehelper(element, node->right);
        }
        else {
            return node->height;
        }
    }
}

template<class T>
const int DSWTree<T>::getNodeHeight(const T& element) const {
    if (isInside(root, element) == false) {
        return -1;
    }
    else {
        height_update(root);
        return getnodehelper(element, root);
    }
    /* TODO */
}

#endif //DSWTREE_H
