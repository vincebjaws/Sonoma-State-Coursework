#include<stdlib.h>
#include "TreeNode.hpp"

// Forward declaration of TreeNode class below.
// Since BinSearchTree uses TreeNode pointers rather
// than objects, we can get away with this in the .hpp.
// You should include "TreeNode.hpp" in the BinSearchTree.cpp

class BinSearchTree {
public:
  void insert( int v )       { root = local_insert( root, v); }
  bool find( int v );                       //Done
  bool iterFind( int v );                   //Done
  int size();                               //Done
  void inorderDump();                       //Done
  int maxDepth();                           //Done
  void levelOrderDump();                    //Done
  void valuesAtLevel( int k );              //Done
  bool remove( int v );                     //Done
  int kthSmallest( int k );                 //Done
  void iterValuesAtLevel( int k );          //Done
  int iterMaxDepth();                      //Done
  bool hasRootToLeafSum( int sum );        //Done
  bool areIdentical( BinSearchTree *bst ); //Done
  BinSearchTree *intersectWith( BinSearchTree *bst );
  BinSearchTree *unionWith( BinSearchTree *bst );
  BinSearchTree *differenceOf( BinSearchTree *bst );
  ~BinSearchTree();
private:
  void  difference(TreeNode *root, BinSearchTree *bst, BinSearchTree *newTree);
  void  intersect(TreeNode *root2,BinSearchTree *bst,BinSearchTree *result);
  void  createUnion(BinSearchTree *newtree, TreeNode *root);
   TreeNode *local_insert( TreeNode *, int );//
   TreeNode *local_remove(TreeNode *, int);//
   TreeNode *removeHelper(TreeNode*);//
   int local_maxDepth(TreeNode *);//
   int local_size(TreeNode*); //
   void local_inorderDump(TreeNode*); //
   void local_levelOrderDump(TreeNode*); //
  bool local_find( TreeNode *, int ); //
  void local_valuesAtLevel(TreeNode*, int, int); //
  bool local_areIdentical(TreeNode *, TreeNode *); //
  bool local_hasRootToLeafSum(TreeNode *, int, int);//
  int local_kthSmallest( int k, int value, TreeNode *root ); //
  TreeNode *root;

};
