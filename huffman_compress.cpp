/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: huffman_compress.cpp

理论方法
    example.          //explanation



***************************************************/
#include <iostream>

#include "huffman_compress.h"
using namespace std;

unsigned char str_to_uch(string st)
{
    unsigned char ch = 0;
    for (unsigned int i=0; i<st.length(); i++)
        ch = ch | ((st[i]-'0') << i);
    return ch;
}


//#define DEBUG

int Huffman_Compress::Compress(ifstream& fin, ofstream& fout_bin)
{ //压缩文件
/***********************************************************
//
//           根据被压缩文件构造Hufman树
*/
    unsigned char ch;

    int weight[257] = {0};
    //统计权重
    while(1){
        fin.read((char*)&ch, sizeof(unsigned char));
        if (!fin.eof())
            weight[ch]++;
        else break;
    };

    char_kinds_ = 0;
    char_tot_ = 0;
    //统计字符种类数和字符总数
    for (int i=0; i<=256; i++)
        if (weight[i]){
            char_kinds_++;  //字符种类数
            char_tot_ += weight[i];  //总字符数
        }

    //编写编码信息1
    fout_bin.write((char*)&char_kinds_, sizeof(char_kinds_));
    fout_bin.write((char*)&char_tot_, sizeof(char_tot_));


    //构造非零权重表用于Hufman编码
    char_set_ = new unsigned char[char_kinds_+1];
    weight_set_ = new unsigned int[char_kinds_+1];
    int code_order[257] = {0};

    for (int i=0,j=0; i<=256; i++)
        if (weight[i]){
            j++;
            code_order[i] = j;
            char_set_[j] = i;
            weight_set_[j] = weight[i];
        }

    //编写编码信息2----权重表
    for (int i=1; i<=char_kinds_; i++){
        fout_bin.write((char*)(char_set_+i), sizeof(unsigned char));
        fout_bin.write((char*)(weight_set_+i), sizeof(unsigned int));
    }

   // Huffman_Tree HT1;
    hufm_tree_ = new Huffman_Tree;

    //构造Hufman树
    hufm_tree_->Creat(weight_set_, char_kinds_);
#ifdef DEBUG
    cout << "creat success" << endl;
#endif // DEBUG

    //计算每个有效字符的编码表
    hufm_tree_->Coding();

#ifdef DEBUG
    //打印树的内容
    HT1.print();
#endif // DEBUG

    fin.clear();
    fin.seekg(0, ios::beg);

    //输出压缩后的编码
    string str="";
    string str_out = "";
    unsigned char bin_code;

    while(!fin.eof()){
        fin.read((char*)&ch, sizeof(unsigned char));
        if (!fin.eof()){
#ifdef DEBUG
             cout <<"   "<< ch <<" ";
#endif // DEBUG
            str = str + hufm_tree_->h_code_[code_order[ch]];
            while(str.length()>=8){
            bin_code = str_to_uch(str.substr(0,8));
#ifdef DEBUG
                cout << str.substr(0,8) ;
#endif // DEBUG
                fout_bin.write((char*)&bin_code, sizeof(bin_code));
                str = str.substr(8); //截取下标8及以后的部分
            }
        } //if (!fin.eof())
        else{
            bin_code = str_to_uch(str);
            //cout << str;
            fout_bin.write((char*)&bin_code, sizeof(bin_code));
            break;
        }
    }

/**
    while(!fin.eof()){
        if (!fin.eof())
#ifdef DEBUG
             cout <<"   "<< ch <<" ";
#endif // DEBUG
            str = str + HT1.h_code_[code_order[ch]];
        while(str.length()>=8 || fin.eof()){
            bin_code = str_to_uch(str.substr(0,8));
#ifdef DEBUG
            cout << str.substr(0,8) ;
#endif // DEBUG
            fout_bin.write((char*)&bin_code, sizeof(bin_code));
            if (str.length()>=8)
                str = str.substr(8); //截取下标8及以后的部分
            if (fin.eof() && str.length()==0)
                break;
        }
    };
*/
//结束输出压缩后的编码

    fin.close();
    fout_bin.close();

    return 0;
}


int Huffman_Compress::Decompress(ifstream& fin_bin, ofstream& fout)
{ //解压文件
    int tot_decoded = 0;
    int str_len = 0;

    char_kinds_ = 0;
    char_tot_ = 0;

    //读取编码信息1
    fin_bin.read((char*)&char_kinds_, sizeof(char_kinds_));
    fin_bin.read((char*)&char_tot_, sizeof(char_tot_));

    char_set_ = new unsigned char[char_kinds_+1];
    weight_set_ = new unsigned int[char_kinds_+1];
    //读取编码信息2----权重表
    for (int i=1; i<=char_kinds_; i++){
        fin_bin.read((char*)(char_set_+i), sizeof(unsigned char));
        fin_bin.read((char*)(weight_set_+i), sizeof(unsigned int));
    }

    //Huffman_Tree HT1;
    //重新构造Hufman树
    hufm_tree_->Creat(weight_set_, char_kinds_);

    int curr = hufm_tree_->root_;
   // unsigned char hufman_code = 0;
    unsigned int hufman_code = 0;
    while (tot_decoded < char_tot_){
        if (str_len == 0){
            fin_bin.read((char*)&hufman_code, sizeof(hufman_code));
            str_len = sizeof(hufman_code) * 8;
        }

        if (curr > hufm_tree_->leaf_){ //尚未到达叶节点
            switch (hufman_code & 1){
            case 0:
                curr = hufm_tree_->h_tree_[curr].lchild;
                break;
            case 1:
                curr = hufm_tree_->h_tree_[curr].rchild;
            }
            hufman_code = hufman_code >> 1;
            str_len--;
        }
        else{ //到达叶节点
#ifdef DEBUG
          cout<<char_set[curr];
#endif // DEBUG
            fout.write((char*)(char_set_+curr), sizeof(unsigned char));
            curr = hufm_tree_->root_;
            tot_decoded++;
        }
    }
    if (curr != hufm_tree_->root_)
        std::cout<<"more bits wanted in the end."<<std::endl;

    fout.close();

    return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
