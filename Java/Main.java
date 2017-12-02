/**
* Copyright (C) 2017 Charles Hua. All rights reserved.
* Last edited date: 2017.12.2
* project name: File Compress
* file name: Main.java

**/

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FilterInputStream;
import java.io.IOException;
import java.util.Scanner;

public class Main{
	public static void main(String args[]) throws IOException{
	    String src,dest;
	    int fun;
	    Scanner scan = new Scanner(System.in);
	    do{
	        System.out.println("请输入功能前对应的序号");
	        System.out.println("    0.退出");
	        System.out.println("    1.压缩文件");
	        System.out.println("    2.解压文件");

	        fun = scan.nextInt();
	        switch (fun) {
	        case 1:{
	            System.out.println("请输入被压缩文件名(带后缀)");
	            src = scan.next();
	            FilterInputStream fin = null;
	            try{
	            	fin = new BufferedInputStream(new FileInputStream(src));
	            } catch (IOException e) {
	                System.out.println("File " + src + " doesn't exist.");
	            	break;
	            }
	            
	            System.out.println("请输入压缩后文件名(不带后缀)");
	            dest = scan.next();
	            DataOutputStream fout_bin = null;
	            try{
	            	fout_bin = new DataOutputStream(new FileOutputStream(dest+".hfm"));
	            } catch (IOException e){
	            	break;
	            }

	            Huffman_Compress file1 = new Huffman_Compress();
	            file1.Compress(fin, fout_bin);
	            System.out.println("已压缩到文件" + dest + ".hfm");
	        }break;
	        case 2:{
	        	System.out.println("请输入压缩文件名(不带后缀)");
	        	src = scan.next();
	        	DataInputStream fin_bin = null;
	            try{
	            	fin_bin = new DataInputStream(new FileInputStream(src + ".hfm"));
	            } catch (IOException e) {
	                System.out.println("File " + src + ".hfm doesn't exist.");
	            	break;
	            }
	            
	            System.out.println("请输入解压后文件名(带后缀)");
	            dest = scan.next();
	            FileOutputStream fout = null;
	            try{
	            	fout = new FileOutputStream(dest);
	            } catch (IOException e){
	            	break;
	            }

	            Huffman_Compress file1 = new Huffman_Compress();
	            file1.Decompress(fin_bin, fout);
	            System.out.println("已解压到文件" + dest);
	        }break;
	        default:
	        	System.out.println("No such function");
	        case 0:
	        	break;
	        } //switch
	    }while(fun != 0);
	return;	
	}
}