/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: huffman_tree.h



***************************************************/
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H

#include <iostream>
#include <string.h>

struct HTNode{
    HTNode():weight(0), parent(0), lchild(0), rchild(0){};
    HTNode(unsigned int w, int p, int l, int r):weight(w), parent(p), lchild(l), rchild(r){};
    unsigned int weight;
    int parent, lchild, rchild;
};

//typedef char T;

class Huffman_Tree{
public:
    // constructors & destructor
    //general member function
    int Creat(unsigned int* w, int n);
    int Coding();
    int Decoding(std::string &bits, std::string &str);
    //input/output function
    int print();
    //data member
    HTNode* h_tree_; //�����������׵�ַ
    std::string* h_code_; //
    int* h_code_len;  //��¼����Hufman����ĳ���
//private:
    int root_; //���ڵ��±�
    int leaf_; //Ҷ�ڵ���Ŀ
};



#endif // _HUFFMAN_TREE_H
