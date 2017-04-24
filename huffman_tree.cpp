/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: huffman_tree.cpp

理论方法
    example.          //explanation

***************************************************/
#include <iostream>
#include "huffman_tree.h"
using namespace std;

int Huffman_Tree::Creat(unsigned int* w, int n)
{
    leaf_ = n;
    int m = 2 * n - 1;
    h_tree_ = new HTNode[m+1];
    int i = 0, j = 0, jmin;

    for (i=1; i<=n; i++)
        h_tree_[i].weight = w[i];
    for (i=n+1; i<2*n; i++){ //构造第i个节点
        //add left child
        jmin = 0;
        for (j=1; j<i; j++)
            if (h_tree_[j].parent==0 && (jmin==0 || h_tree_[j].weight<h_tree_[jmin].weight))
                jmin = j;
        h_tree_[i].lchild = jmin;
        h_tree_[jmin].parent = i;
        h_tree_[i].weight += h_tree_[jmin].weight;
        //add right child
        jmin = 0;
        for (j=1; j<i; j++)
            if (h_tree_[j].parent==0 && (jmin==0 || h_tree_[j].weight<h_tree_[jmin].weight))
                jmin = j;
        h_tree_[i].rchild = jmin;
        h_tree_[jmin].parent = i;
        h_tree_[i].weight += h_tree_[jmin].weight;
    }
    root_ = 2 * n - 1;
    return 0;
}

int Huffman_Tree::print()
{
    int i;
    for (i=1; i <= root_; i++)
        std::cout << h_tree_[i].weight << " " << h_tree_[i].parent << " " << h_tree_[i].lchild << " " << h_tree_[i].rchild << std::endl;
    return 0;
}

int Huffman_Tree::Coding()
{  //得到每个字符对应的编码
    h_code_ = new std::string[leaf_+1];
    h_code_len = new int[leaf_+1];
    int i,curr,father;
    std::string str;

    for (i=1; i<=leaf_; i++){
        str = "";
        curr = i;
        h_code_len[i] = 0;
        do{
            father = h_tree_[curr].parent;
            if (h_tree_[father].lchild == curr)
                str = "0" + str;
                else str = "1" + str;
            curr = father;
            h_code_len[i]++;
        }while(curr != 2*leaf_-1);
        h_code_[i] = str;
#ifdef DEBUG
        std::cout<< i <<" "<< h_code_[i] << " "<< h_code_len[i] << std::endl;
#endif // DEBUG
    }
    return 0;
}

//int Huffman_Tree::Decoding(std::string &bits, std::string &str)
//{
//    int i = 0;
//    int curr = root_;
//    while (bits[i]!='\n'){
//       // std::cout<<curr;//<<" "<<bits[i];
//        switch (bits[i]){
//            case '0':
//                if (h_tree_[curr].lchild != 0)
//                    curr = h_tree_[curr].lchild;
//                break;
//            case '1':
//                if (h_tree_[curr].rchild != 0)
//                    curr = h_tree_[curr].rchild;
//        }
//        //到达叶节点
//        if (curr <= leaf_){
//            std::cout<<h_code_[curr]<<" ";
//            std::cout<<std::endl;
//            curr = root_;
//        }
//        i++;
//    }
//    if (curr != root_)
//        std::cout<<"more bits wanted in the end."<<std::endl;
//    return 0;
//}


