/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.4.24
file name: main.cpp

���۷���
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
    cout << "�����빦��ǰ��Ӧ�����" << endl
         << "    0.�˳�" << endl
         << "    1.ѹ���ļ�" << endl
         << "    2.��ѹ�ļ�" << endl
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
            cout << "�����뱻ѹ���ļ���(����׺)" << endl;
            cin >> src;
            ifstream fin(src, std::ios::binary);
            if (!fin){
                cout << "File " << src << " doesn't exist." <<endl;
                break;
            }
            cout << "������ѹ�����ļ���(������׺)" << endl;
            cin >> dest;
            ofstream fout_bin(dest + ".huf", std::ios::binary);
            if (!fout_bin){
                cout << "Fail to creat fail " + dest + ".huf" <<endl;
                break;
            }
            Huffman_Compress file1;
            file1.Compress(fin, fout_bin);
            cout << "��ѹ�����ļ�" + dest + ".huf" << endl;
        }break;
        case 2:{
            cout << "������ѹ���ļ���(������׺)" << endl;
            cin >> src;
            ifstream fin_bin(src + ".huf", std::ios::binary);
            if (!fin_bin){
                cout << "File " + src + ".huf" + " doesn't exist." <<endl;
                break;
            }
            cout << "�������ѹ���ļ���(����׺)" << endl;
            cin >> dest;
            ofstream fout(dest, std::ios::binary);
            if (!fout){
                cout << "Fail to creat fail " + dest <<endl;
                break;
            }
            Huffman_Compress file1;
            file1.Decompress(fin_bin, fout);
            cout << "�ѽ�ѹ���ļ�" + dest << endl;
        }break;
        } //switch
    }while(fun);
    return 0;
}
