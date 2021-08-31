#include "BinSearchTree.hpp"
#include "TreeNode.hpp"
#include <iostream>
#include <queue>
#include <stdlib.h>
using namespace std;

TreeNode *BinSearchTree::local_insert( TreeNode *root, int v ) {
    if (root == nullptr)
        return new TreeNode(v);
    if (root->value() < v)
        root->rightSubtree(local_insert(root->rightSubtree(), v));
    else
        root->leftSubtree(local_insert(root->leftSubtree(), v));
    return root;
}

TreeNode *BinSearchTree::local_remove( TreeNode *root, int v) {
    if(root == nullptr) return root;
    if(v < root->value())
        root->leftSubtree(local_remove(root->leftSubtree(), v) );
    else if (v > root->value())
        root->rightSubtree(local_remove(root->rightSubtree(), v) );
    else
    {
        if(root->leftSubtree()== nullptr) {
            TreeNode *temp = root->rightSubtree();
            free(root);
            return temp;
        }
        else if(root->rightSubtree()== nullptr) {
            TreeNode *temp = root->rightSubtree();
            free(root);
            return temp;
        }

        TreeNode *temp = removeHelper(root->rightSubtree());
        root->value() = temp->value();
        local_remove(root->rightSubtree(), temp->value());
    }
    return root;
}

TreeNode *BinSearchTree::removeHelper(TreeNode *root) {
    TreeNode* current = root;
    while(current && current->leftSubtree() != nullptr)
        current = current->leftSubtree();
    return current;
}

bool BinSearchTree::remove(int v){
    if(find(v)) {
        root = local_remove(root, v);
        return true;
    }
    return false;
}

bool BinSearchTree::find(int v) {
    return local_find(root, v);
}
bool BinSearchTree::local_find(TreeNode*root,int v) {
  if(root==nullptr)
    return false;
  if(root->value() == v)
    return true;
  if(local_find(root->leftSubtree(),v))
    return true;
  return local_find(root->rightSubtree(),v);

}


bool BinSearchTree::iterFind(int v) {
    TreeNode *temp = root;
    while(temp!=nullptr){
        if(temp->value() == v)
            return true;
        if(temp->value() < v)
            temp = temp->rightSubtree();
        else
            temp = temp->leftSubtree();
  }
  return false;
}
int BinSearchTree::iterMaxDepth() {
  if(root == nullptr)
    return 0;
  queue<TreeNode *> q;
  q.push(root);
  int height = 0;
  while(!q.empty()){
    int nodeCount = q.size();

    while(nodeCount--){
      TreeNode *node =q.front();
      q.pop();
      if(node->leftSubtree())
	q.push(node->leftSubtree());
      if(node->rightSubtree())
	q.push(node->rightSubtree());
    }
    height++;
  }
  return height;
}

int BinSearchTree::local_maxDepth(TreeNode *root) {
    if (root == nullptr)
        return 0;
    int left = local_maxDepth(root->leftSubtree())+1;
    int right = local_maxDepth(root->rightSubtree())+1;
    if(left < right)
        return right;
    return left;
}

int BinSearchTree::local_size(TreeNode *root) {
    if(root==nullptr)
        return 0;
    return  local_size(root->rightSubtree()) + local_size(root->leftSubtree()) + 1;
}


int BinSearchTree::size() {
  return local_size(root);
}

void BinSearchTree::local_inorderDump(TreeNode *root) {
    if (root==nullptr)
        return;
    local_inorderDump(root->leftSubtree());
    cout<< root->value() << endl;
    local_inorderDump(root->rightSubtree());
}

void BinSearchTree::levelOrderDump() {
    TreeNode*temp;
    std::queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        temp= q.front();
        q.pop();
        std::cout<<temp->value()<<std::endl;
        if(temp->leftSubtree()!=nullptr)
            q.push(temp->leftSubtree());
        if(temp->rightSubtree()!= nullptr)
            q.push(temp->rightSubtree());
    }
}
void BinSearchTree::local_valuesAtLevel(TreeNode *root, int k, int current){
    if(root==nullptr)
        return;
    if(current == k) {
        cout << root->value() << endl;
        return;
    }
    if(current > k)
        return;
    local_valuesAtLevel(root->leftSubtree(),k,current+1);
    local_valuesAtLevel(root->rightSubtree(),k,current+1);
}
void BinSearchTree::iterValuesAtLevel(int k ){
  if(root== nullptr)
     return;
  std::queue<TreeNode *> q;
  q.push(root);
  q.push(nullptr);
  int height = 1;
  while(!q.empty()) {
      TreeNode *newNode = q.front();
      if(height == k && newNode !=nullptr)
          std::cout << newNode->value() << std::endl;
      q.pop();
      if(newNode == nullptr) {
          if(q.front())
              q.push(nullptr);
          height++;
     }
      else{
          if(newNode->leftSubtree())
              q.push(newNode->leftSubtree());
          if(newNode->rightSubtree())
              q.push(newNode->rightSubtree());
      }
  }
}


void BinSearchTree::valuesAtLevel( int k ){
    local_valuesAtLevel(root, k, 1);
}

void BinSearchTree::inorderDump() {
    local_inorderDump(root);
}



int BinSearchTree::maxDepth() {
    return local_maxDepth(root);
}

int BinSearchTree::kthSmallest( int k ){
  if(k > local_size(root))
      return -1;
   return local_kthSmallest(k,0,root);
}


int BinSearchTree::local_kthSmallest( int k, int value, TreeNode *root ){
    int current = value+local_size(root->leftSubtree())+1;
    if(k==current)
        return root->value();
    if(k<current)
        return local_kthSmallest(k, value, root->leftSubtree());
    return local_kthSmallest(k, current,root->rightSubtree());

}

bool BinSearchTree::hasRootToLeafSum( int sum ){
    if(local_hasRootToLeafSum(root, sum, 0))
        return true;
    return false;
}

bool BinSearchTree::local_hasRootToLeafSum(TreeNode *root, int sum, int total) {
    if(root==nullptr)
        return false;
    int count = root->value();
    total = count + total;
    if(total==sum) {
        if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr)
            return true;
    }
    if(local_hasRootToLeafSum(root->leftSubtree(), sum, total))
        return true;
    else if(local_hasRootToLeafSum(root->rightSubtree(),sum, total))
        return true;
    return false;
}
bool BinSearchTree::areIdentical( BinSearchTree *bst ){
    if(local_areIdentical(root, bst->root))
        return true;
    return false;
}

bool BinSearchTree::local_areIdentical(TreeNode *root, TreeNode *bstroot) {
    if (root == nullptr && bstroot == nullptr)
        return true;
    else if (root == nullptr|| bstroot == nullptr)
        return false;
    if(local_areIdentical(root->leftSubtree(), bstroot->leftSubtree())) {
        if(local_areIdentical(root->rightSubtree(), bstroot->rightSubtree()))
            return true;
    }
    return false;
}

BinSearchTree *BinSearchTree::intersectWith( BinSearchTree *bst ) {
  BinSearchTree * newtree = new BinSearchTree;
  intersect(root, bst, newtree);
  return newtree;
}

void BinSearchTree::intersect(TreeNode *root2,BinSearchTree *bst, BinSearchTree *result) {
  if(bst == nullptr || root2 == nullptr)
    return;
  if(bst->find(root2->value())) 
      result->insert(root2->value());
  intersect(root2->leftSubtree(), bst, result);
  intersect(root2->rightSubtree(), bst, result);
}

BinSearchTree *BinSearchTree::unionWith( BinSearchTree *bst ){
    TreeNode *root2 = bst->root;
    auto *newtree = new BinSearchTree();
    createUnion(newtree, root2);
    return newtree;
}
void BinSearchTree::createUnion(BinSearchTree *newtree, TreeNode *root) {
    if(root == nullptr)
        return;
    if(newtree->find(root->value())) {
        createUnion(newtree, root->leftSubtree());
        createUnion(newtree, root->rightSubtree());
    }
    else {
        newtree->insert(root->value());
        createUnion(newtree, root->leftSubtree());
        createUnion(newtree, root->rightSubtree());
    }
}


BinSearchTree *BinSearchTree::differenceOf( BinSearchTree *bst ){
  BinSearchTree *newTree = new BinSearchTree();
  difference(root, bst, newTree);
  difference(bst->root, this, newTree);
  return newTree;
}

void BinSearchTree::difference(TreeNode *root, BinSearchTree*bst, BinSearchTree *newTree) {
    if(root == nullptr)
        return;
    if(!bst->find(root->value()))
      newTree->insert(root->value());
    difference(root->leftSubtree(), bst, newTree);
    difference(root->rightSubtree(), bst, newTree);
}
