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
      Node *left;
      Node *right;
      Node *parent;
      T val;
      Node(T val){
        this->val=val;
        this->right=nullptr;
        this->left=nullptr;
        this->parent=nullptr;
      }
  };
  BSTree<T>::Node * root;
public:

  BSTree();
  bool empty();
  ~BSTree();
  bool insert(T val);
  bool find(T val);
  bool remove(int num);
  void sortedArray(vector<int> &list);
  bool removeHelper(BSTree<T>::Node * node, int num);
  bool insertHelper(BSTree<T>::Node * node, T val);
  bool findHelper(BSTree<T>::Node * node, T val);
  void sortedArrayHelper(BSTree<T>::Node * node,vector<int> &list);
  int height();
  int findHeight(Node* node);
  void balance();
  void balanceHelper(BSTree<T>::Node * node,vector<int> &list);
  void promotion(BSTree<T>::Node * node);
  Node* searchMin(BSTree<T>::Node * node);
  void shortCircuit(BSTree<T>::Node * node);
  void deleteLeaf(BSTree<T>::Node * node);
  Node* findNode(BSTree<T>::Node * node,int num);
  void deleteHelper(BSTree<T>::Node * node);
};
template<class T>
BSTree <T>:: BSTree(){
  this->root=NULL;
}
template<class T>
BSTree <T>:: ~BSTree(){
  //deleteHelper(root);
}
template<class T>
void BSTree <T>:: deleteHelper(BSTree<T>::Node * node){

    if (node == NULL) return;

    deleteHelper(node->left);
    deleteHelper(node->right);


    delete node;
}

template <class T>
bool BSTree <T>:: empty(){
  if(this->root==NULL){
    return true;
  }
  else{
    return false;
  }
}
template<class T>
typename BSTree<T>::Node*  BSTree<T>::findNode(BSTree<T>::Node * node,int num){

  if (num < node->val) {
      if (node->left != NULL) {
          return findNode(node->left,num);
      }
  } else if (num > node->val) {
      if (node->right != NULL) {
          return findNode(node->right,num);
      }
  } else if (num == node->val){
      return node;
  }else {
    node =nullptr;
  }

}
template<class T>
typename BSTree<T>::Node* BSTree<T>::searchMin(BSTree<T>::Node * node){
  while (node->left != NULL)
{
    node = node->left;
}
return node;
}
template <typename T>
void BSTree<T>::deleteLeaf(BSTree<T>::Node * node){
  if(node->parent == NULL){
    root = nullptr;
  }
  else{
	  if (node->parent->right == node){
		  node->parent->right = NULL;
	  }else{
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

template <class T>
void BSTree<T>::promotion(BSTree<T>::Node * node){
  Node * d_node = searchMin(node->right);
	node->val = d_node->val;
	//Leaf
	if(d_node->left==NULL && d_node->right==NULL){
		deleteLeaf(d_node);
	//one branch
	}else{
		shortCircuit(d_node);

	}
}


template <class T>
bool BSTree<T>::removeHelper(BSTree<T>::Node * node, int num ){
	node = findNode(node,num);
  if ( node ==NULL )
      return false;
  else {
		if ( node->left == nullptr && node->right == nullptr ){

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
bool BSTree<T>::remove(int num){
  if (root == NULL) {
    return false;
  }
  return removeHelper(root, num );
}


// ----------------------------------- FIND AND FINDHELPER ------------------------------------------------//

template <typename T>
bool BSTree<T>:: find(T val){
  if (root == NULL) {
    return false;
  }
  return findHelper(root , val);
}
template <class T>
bool BSTree<T>::findHelper(BSTree<T>::Node * node, T val) {
  if (val< node->val){
      if(node->left==NULL){
          return false;
      }
      return findHelper(node->left,val);
  }
  else if(val> node->val){
      if (node->right==NULL){
          return false;
      }
      return findHelper(node->right,val);
  }
  return true;

  }
// ----------------------------------- FIND AND FINDHELPER ------------------------------------------------//

// ----------------------------------- SORTED AND SORTEDHELPER ------------------------------------------------//

template <typename T>
void BSTree<T>::sortedArray(vector<int> &list){
  if (root == NULL) {
    return ;

  }
  return sortedArrayHelper(root, list );
}
template <class T>
void BSTree<T>::sortedArrayHelper(BSTree<T>::Node * node,vector<int> &list){
      if (node == NULL)
        return;
      sortedArrayHelper(node->left, list );
      list.push_back (node->val);
      sortedArrayHelper(node->right, list );

}
// ----------------------------------- SORTED AND SORTEDHELPER ------------------------------------------------//

// ----------------------------------- INSERT AND INSERTHELPER ------------------------------------------------//

template <class T>
bool BSTree <T>::insert(T val){
  // If the root is null, make new node with val
  // Otherwise, invoke helper

  if (root == NULL) {
    root = new Node(val);
    root->parent == nullptr;
    return true;
  }
  return insertHelper(root , val);
}
template <class T>
bool BSTree<T>::insertHelper(BSTree<T>::Node * node, T val) {
  if (val < node->val) {
      if (node->left != NULL) {
          return insertHelper(node->left,val);
      } else {
          node->left = new Node(val);
          node->left->parent = node;
      }
  } else if (val > node->val) {
      if (node->right != NULL) {
          return insertHelper(node->right,val);
      } else {
          node->right = new Node(val);
          node->right->parent = node;
      }

  } else {
      return false;
  }
}
// ----------------------------------- INSERT AND INSERTHELPER ------------------------------------------------//




#endif
