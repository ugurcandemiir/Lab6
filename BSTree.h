#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class BSTree{
private:
  class Node{
    public:
      T value;
      Node *left;
      Node *right;
      Node *parent;
      Node(T value){
        this->value=value;
        this->right=nullptr;
        this->left=nullptr;
        this->parent=nullptr;
      }
  };
  BSTree<T>::Node * root;
public:

  BSTree();
  ~BSTree();
  bool empty();
  bool insert(T val);
  bool find(T val);
  bool remove(T val);
  void sortedArray(vector<int> &list);
  bool findHelper(BSTree<T>::Node * node, T val);
  bool insertHelper(BSTree<T>::Node * node, T val);
  bool removeHelper(BSTree<T>::Node * node, T val);
  void sortedArrayHelper(BSTree<T>::Node * node,vector<int> &list);
  void deleteLeaf(BSTree<T>::Node * node);
  void shortCircuit(BSTree<T>::Node * node);
  void promotion(BSTree<T>::Node * node);
  Node* findMin(BSTree<T>::Node * node);
  Node* findNode(BSTree<T>::Node * node,T val);
  int height();
  int findHeight(Node* node);
  void balance();
  void balanceHelper(BSTree<T>::Node * node,vector<int> &list);
  void deleteHelper(BSTree<T>::Node * node);
};

template<typename T>
BSTree <T>:: BSTree(){
  this->root=NULL;
}
template<typename T>
BSTree<T>::~BSTree(){
  //deleteHelper(root);
}
template <typename T>
bool BSTree <T>:: empty(){
  if(this->root==NULL){
    return true;
  }
  else{
    return false;
  }
}


template <typename T>
bool BSTree<T>:: find(T val){
  if(root == NULL) {
    return false;
  }
  return findHelper(root , val);
}
template <typename T>
bool BSTree<T>::findHelper(BSTree<T>::Node * node, T val) {
  if(val< node->value){
      if(node->left==NULL){
          return false;
      }
      return findHelper(node->left,val);
  }
  else if(val> node->value){
      if (node->right==NULL){
          return false;
      }
      return findHelper(node->right,val);
  }
  return true;
}
template <typename T>
bool BSTree<T>::remove(T val){
  if(root == NULL) {
    return false;
  }
  return removeHelper(root,val);
}
template <typename T>
bool BSTree<T>::removeHelper(BSTree<T>::Node * node, T val ){
  node = findNode(node,val);
  if(node ==NULL )
      return false;
  else{
    if(node->left == nullptr && node->right == nullptr ){
      deleteLeaf(node);
    }
    if((node->left==nullptr && node->right != nullptr) || (node->left != nullptr && node->right==nullptr) ) {
      shortCircuit(node);
    }
    if(node->left != nullptr && node->right != nullptr){
      promotion(node);
    }
  return true;
  }
}
template <typename T>
void BSTree<T>::deleteLeaf(BSTree<T>::Node * node){
  if(node->parent == NULL){
    root = nullptr;
  }
  else{
    if(node->parent->right == node){
    node->parent->right = NULL;
    }
    else{
      node->parent->left = NULL;
    }
    delete node;
    node = NULL;
  }
}
template <typename T>
void BSTree<T>::shortCircuit(BSTree<T>::Node * node){
  if(node->parent == NULL){
    if(node->right !=NULL && node->left == NULL){
      root = node->right;
      delete node;
      root->parent=nullptr;
    }
    if(node->right ==NULL && node->left != NULL){
      root = node->left;
      delete node;
      root->parent=nullptr;
    }
  }
  else{
    if(node->parent->right == node){
      if(node->right == NULL && node->left != NULL){
        node->parent->right = node->left;
        node->parent = node->left->parent;
      }
      else
      {
        node->parent->right =node->left;
      }
      node->parent->right = node->right;
      node->right->parent = node->parent;
      delete node;
      node = NULL;
    }
    else{
      if(node->left == NULL){
        node->parent->left = node->right;
        node->right->parent = node->parent;
      }
      else{
        node->parent->left = node->left;
        node->left->parent = node->parent;
      }
      delete node;
      node = NULL;
    }
  }
}
template <typename T>
void BSTree<T>::promotion(BSTree<T>::Node * node){
  Node * n_node = findMin(node->right);
  node->value = n_node->value;
  if(n_node->left==NULL && n_node->right==NULL){
    deleteLeaf(n_node);
  }
  else{
    shortCircuit(n_node);
  }
}

template<typename T>
typename BSTree<T>::Node*  BSTree<T>::findNode(BSTree<T>::Node * node,T val){
  if(val > node->value) {
    if(node->right != NULL){
      return findNode(node->right,val);
    }
  }
  else if(val < node->value){
    if(node->left != NULL) {
      return findNode(node->left,val);
    }
  }
  else if(val == node->value){
    return node;
  }
  else{
    node =nullptr;
  }
}
template<typename T>
typename BSTree<T>::Node* BSTree<T>::findMin(BSTree<T>::Node * node){
  while(node->left != NULL){
    node = node->left;
  }
  return node;
}

// ----------------------------------- SORTED AND SORTEDHELPER ------------------------------------------------//
template <typename T>
void BSTree<T>::sortedArray(vector<int> &list){
  if(root == NULL) {
    return ;
  }
  return sortedArrayHelper(root, list);
}
template <typename T>
void BSTree<T>::sortedArrayHelper(BSTree<T>::Node * node,vector<int> &list){
      if(node == NULL){
        return;
      }
      sortedArrayHelper(node->left, list );
      list.push_back (node->value);
      sortedArrayHelper(node->right, list );
}
// ----------------------------------- SORTED AND SORTEDHELPER ------------------------------------------------//

// ----------------------------------- INSERT AND INSERTHELPER ------------------------------------------------//
template <typename T>
bool BSTree <T>::insert(T val){
  if(root == NULL) {
    root = new Node(val);
    root->parent == nullptr;
    return true;
  }
  return insertHelper(root , val);
}
template <typename T>
bool BSTree<T>::insertHelper(BSTree<T>::Node * node, T val) {
  if(val > node->value) {
    if(node->right != NULL) {
      return insertHelper(node->right,val);
    }
    else{
      node->right = new Node(val);
      node->right->parent = node;
    }
  }
  else if(val < node->value) {
    if(node->left != NULL) {
        return insertHelper(node->left,val);
      }
      else{
        node->left = new Node(val);
        node->left->parent = node;
      }
  }
  else{
    return false;
  }
}
// ----------------------------------- INSERT AND INSERTHELPER ------------------------------------------------//

#endif
