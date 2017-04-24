/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: huffman_compress.h



***************************************************/
#ifndef _HUFFMAN_COMPRESS_H
#define _HUFFMAN_COMPRESS_H

#include <fstream>
#include "huffman_tree.h"
class Huffman_Compress{
public:
    // constructors & destructor
    //general member function
    int Compress(std::ifstream& fin, std::ofstream& fout_bin);
    int Decompress(std::ifstream& fin_bin, std::ofstream& fout);

    //input/output function

    //data member
    int char_kinds_;  //字符种类数
    int char_tot_;  //字符总数
    unsigned char* char_set_; //字符集,有效下标1~char_kinds_
    unsigned int* weight_set_; //权重集,有效下标1~char_kinds_
    Huffman_Tree* hufm_tree_;
//private:

};

#endif // _HUFFMAN_COMPRESS_H
