#ifndef TREE_h
#define TREE_h
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
  bool empty();
  bool insert(T val);
  bool find(T val);
  bool remove(T val);
  void sortedArray(vector<int> &list);
  bool findhelper(BSTree<T>::Node * node, T val);
  bool inserthelper(BSTree<T>::Node * node, T val);
  bool removehelper(BSTree<T>::Node * node, T val);
  void sortedarrayhelper(BSTree<T>::Node * node,vector<int> &list);
  void removeleaf(BSTree<T>::Node * remnode);
  void shortcircuit(BSTree<T>::Node * remnode);
  void promotion(BSTree<T>::Node * remnode);
  Node* findmin(BSTree<T>::Node * minnode);
  Node* findnode(BSTree<T>::Node * fnode,T val);
  int height();
  int findHeight(Node* node);
  void balance();
  void balanceHelper(BSTree<T>::Node * node,vector<int> &list);
  ~BSTree();
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
bool BSTree <T>::insert(T val){
  if(root == NULL) {
    root = new Node(val);
    root->parent == nullptr;
    return true;
  }
  return inserthelper(root , val);
}
template <typename T>
bool BSTree<T>::inserthelper(BSTree<T>::Node * node, T val) {
  if(val > node->value) {
    if(node->right != NULL) {
      return inserthelper(node->right,val);
    }
    else{
      node->right = new Node(val);
      node->right->parent = node;
    }
  } 
  else if(val < node->value) {
    if(node->left != NULL) {
        return inserthelper(node->left,val);
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
template <typename T>
bool BSTree<T>:: find(T val){
  if(root == NULL) {
    return false;
  }
  return findhelper(root , val);
}
template <typename T>
bool BSTree<T>::findhelper(BSTree<T>::Node * node, T val) {
  if(val< node->value){
      if(node->left==NULL){
          return false;
      }
      return findhelper(node->left,val);
  }
  else if(val> node->value){
      if (node->right==NULL){
          return false;
      }
      return findhelper(node->right,val);
  }
  return true;
}
template <typename T>
bool BSTree<T>::remove(T val){
  if(root == NULL) {
    return false;
  }
  return removehelper(root,val);
}
template <typename T>
bool BSTree<T>::removehelper(BSTree<T>::Node * remnode, T val ){
  remnode = findnode(remnode,val);
  if(remnode ==NULL )
      return false;
  else{
    if(remnode->left == nullptr && remnode->right == nullptr ){
      removeleaf(remnode);
    }
    if((remnode->left==nullptr && remnode->right != nullptr) || (remnode->left != nullptr && remnode->right==nullptr) ) {
      shortcircuit(remnode);
    }
    if(remnode->left != nullptr && remnode->right != nullptr){
      promotion(remnode);
    }
  return true;
  }
}
template <typename T>
void BSTree<T>::removeleaf(BSTree<T>::Node * remnode){
  if(remnode->parent == NULL){
    root = nullptr;
  }
  else{
    if(remnode->parent->right == remnode){
    remnode->parent->right = NULL;
    }
    else{
      remnode->parent->left = NULL;
    }
    delete remnode;
    remnode = NULL;
  }
}
template <typename T>
void BSTree<T>::shortcircuit(BSTree<T>::Node * remnode){
  if(remnode->parent == NULL){
    if(remnode->right !=NULL && remnode->left == NULL){
      root = remnode->right;
      delete remnode;
      root->parent=nullptr;
    }
    if(remnode->right ==NULL && remnode->left != NULL){
      root = remnode->left;
      delete remnode;
      root->parent=nullptr;
    }
  }
  else{
    if(remnode->parent->right == remnode){
      if(remnode->right == NULL && remnode->left != NULL){
        remnode->parent->right = remnode->left;
        remnode->parent = remnode->left->parent;
      }
      else
      {
        remnode->parent->right =remnode->left;
      }
      remnode->parent->right = remnode->right;
      remnode->right->parent = remnode->parent;
      delete remnode;
      remnode = NULL;
    }
    else{
      if(remnode->left == NULL){
        remnode->parent->left = remnode->right;
        remnode->right->parent = remnode->parent;
      }
      else{
        remnode->parent->left = remnode->left;
        remnode->left->parent = remnode->parent;
      }  
      delete remnode;
      remnode = NULL;
    }
  }
}
template <typename T>
void BSTree<T>::promotion(BSTree<T>::Node * remnode){
  Node * pronode = findmin(remnode->right);
  remnode->value = pronode->value;
  if(pronode->left==NULL && pronode->right==NULL){
    removeleaf(pronode);
  }
  else{
    shortcircuit(pronode);    
  }
}
template <typename T>
void BSTree<T>::sortedArray(vector<int> &list){
  if(root == NULL) {
    return ;
  }
  return sortedarrayhelper(root, list);
}
template <typename T>
void BSTree<T>::sortedarrayhelper(BSTree<T>::Node * node,vector<int> &list){
      if(node == NULL){
        return;
      }  
      sortedarrayhelper(node->left, list );
      list.push_back (node->value);
      sortedarrayhelper(node->right, list );
}
template<typename T>
typename BSTree<T>::Node*  BSTree<T>::findnode(BSTree<T>::Node * fnode,T val){
  if(val > fnode->value) {
    if(fnode->right != NULL){
      return findnode(fnode->right,val);
    }
  } 
  else if(val < fnode->value){
    if(fnode->left != NULL) {
      return findnode(fnode->left,val);
    }
  } 
  else if(val == fnode->value){
    return fnode;
  }
  else{
    fnode =nullptr;
  }
}
template<typename T>
typename BSTree<T>::Node* BSTree<T>::findmin(BSTree<T>::Node * minnode){
  while(minnode->left != NULL){
    minnode = minnode->left;
  }
  return minnode;
}


#endif
