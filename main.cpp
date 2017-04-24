/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: main.cpp

理论方法
    example.          //explanation



***************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "huffman_tree.h"
#include "huffman_compress.h"
using namespace std;

int PrintManu()
{
    cout << "请输入功能前对应的序号" << endl
         << "    0.退出" << endl
         << "    1.压缩文件" << endl
         << "    2.解压文件" << endl
        ;
    return 0;
}

int main()
{
    string src,dest;
    int fun;
    do{
        PrintManu();
        cin >> fun;
        switch (fun) {
        case 1:{
            cout << "请输入被压缩文件名(带后缀)" << endl;
            cin >> src;
            ifstream fin(src, std::ios::binary);
            if (!fin){
                cout << "File " << src << " doesn't exist." <<endl;
                break;
            }
            cout << "请输入压缩后文件名(不带后缀)" << endl;
            cin >> dest;
            ofstream fout_bin(dest + ".huf", std::ios::binary);
            if (!fout_bin){
                cout << "Fail to creat fail " + dest + ".huf" <<endl;
                break;
            }
            Huffman_Compress file1;
            file1.Compress(fin, fout_bin);
            cout << "已压缩到文件" + dest + ".huf" << endl;
        }break;
        case 2:{
            cout << "请输入压缩文件名(不带后缀)" << endl;
            cin >> src;
            ifstream fin_bin(src + ".huf", std::ios::binary);
            if (!fin_bin){
                cout << "File " + src + ".huf" + " doesn't exist." <<endl;
                break;
            }
            cout << "请输入解压后文件名(带后缀)" << endl;
            cin >> dest;
            ofstream fout(dest, std::ios::binary);
            if (!fout){
                cout << "Fail to creat fail " + dest <<endl;
                break;
            }
            Huffman_Compress file1;
            file1.Decompress(fin_bin, fout);
            cout << "已解压到文件" + dest << endl;
        }break;
        } //switch
    }while(fun);
    return 0;
}
