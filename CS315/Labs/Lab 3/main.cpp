    #include <iostream>
    #include <fstream>
    #include "BinSearchTree.hpp"

    int main( int argc, char *argv[] ) {
        // create a tree and then print the values of its nodes 
        // from the smallest to the largest.

        BinSearchTree *tree = new BinSearchTree();
        std::fstream myfile("../input2.txt", std::ios_base::in);
        int v;
        while( myfile >> v ) {
            //std::cout << v << std::endl;
            tree->insert( v );
        }
        tree->levelOrderDump();
        std::cout << "Starting in order dump" << std::endl;
        tree->inorderDump();
        std::cout << "End of in order dump" << std::endl;
        if(tree->find(199983))
            std::cout << "passed" << std::endl;
        else
           std::cout << "failed" << std::endl;
        if(tree->iterFind(213412354))
           std::cout << "passed" << std::endl;
        else
            std::cout << "failed" << std::endl;
        std::cout << tree->maxDepth() << std::endl;
        std::cout << tree->size() << std::endl;
        std::cout << "Starting level order dump" << std::endl;
//        tree->levelorderDump();
        std::cout << "End of level order dump" << std::endl;
        std::cout << "Values at level" << std::endl;
        tree->valuesAtLevel(2);
        std::cout << "Remove" << std::endl;
        /*if(tree->remove(1))
            std::cout<< "Passed" << std::endl;
        else
            std::cout<< "Failed"<< std::endl;
        */if(tree->hasRootToLeafSum(22))
            std::cout<<"passed"<<std::endl;
        else
            std::cout<<"failed"<<std::endl;
        BinSearchTree *tree2 = new BinSearchTree;
        tree2-> insert(12);
        tree2-> insert(5);
        tree2-> insert(3);
        tree2-> insert(2);
        tree2-> insert(1);
        tree2-> insert(18);
        tree2-> insert(17);
        tree2-> insert(19);
        tree2-> insert(6);
        std::cout << "Starting kthSmallest: " << std::endl;
        std::cout<<tree->kthSmallest(4) << std::endl;
        if(tree->areIdentical(tree2))
            std::cout<<"true";
        else
            std::cout<<"false";


        return 0;			    
    }
