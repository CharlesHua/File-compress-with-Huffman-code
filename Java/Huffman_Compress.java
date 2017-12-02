
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

class Huffman_Compress{
    // constructors
    //general member function

    //input/output function

    //data member
    int char_kinds_;  //�ַ�������
    int char_tot_;  //�ַ�����
    byte[] char_set_; //�ַ���,��Ч�±�1~char_kinds_
    int[] weight_set_; //Ȩ�ؼ�,��Ч�±�1~char_kinds_
    Huffman_Tree hufm_tree_;
//private:

    public short str2short(String st)
    {
        short ch = 0;
        for (int i=0; i<st.length(); i++)
            ch = (short) ((ch | ((st.charAt(i)-'0') << i)) & 0xffff);
        return ch;
    }

    public int Compress(FilterInputStream fin, DataOutputStream fout_bin) throws IOException{
    //ѹ���ļ�
        fin.mark(fin.available() + 2);

    	//���ݱ�ѹ���ļ�����Hufman��
    
    	System.out.println("��������Huffman����...");
        
    	short ch;
        int[] weight = new int[257];
       // for (int i=1; i<257; i++)
       // 	weight[i]=0;
        //ͳ��Ȩ��
        while(true){
            ch = (short) fin.read();
          //  System.out.print(ch+"  ");
            if (ch != -1)
                weight[ch]++;
            else break;
        };

        char_kinds_ = 0;
        char_tot_ = 0;
        //ͳ���ַ����������ַ�����
        for (int i=0; i<=256; i++)
            if (weight[i] != 0){
                char_kinds_++;  //�ַ�������
                char_tot_ += weight[i];  //���ַ���
            }

        //��д������Ϣ1
        fout_bin.writeInt(char_kinds_);
        fout_bin.writeInt(char_tot_);

    	System.out.println("ԭ�ļ���СΪ" + char_tot_ + "����");
        
        //�������Ȩ�ر�����Hufman����
        char_set_ = new byte[char_kinds_+1];
        weight_set_ = new int[char_kinds_+1];
        int[] code_order = new int[257];

        for (short i=0,j=0; i<=256; i++)
            if (weight[i] != 0){
                j++;
                code_order[i] = j;
                char_set_[j] = (byte) i;
                weight_set_[j] = weight[i];
            }

        //��д������Ϣ2----Ȩ�ر�
        //System.out.println("Ȩ�ر�");
        for (int i=1; i<=char_kinds_; i++){
            fout_bin.writeByte(char_set_[i]);
            fout_bin.writeInt((weight_set_[i]));
          //  System.out.println(char_set_[i] + " " + weight_set_[i]);
        }

        //����Hufman��
        hufm_tree_ = new Huffman_Tree();
        hufm_tree_.Creat(weight_set_, char_kinds_);

        //����ÿ����Ч�ַ��ı����
        hufm_tree_.Coding();


        fin.reset();

        System.out.println("��������ѹ���ļ�...");

        //���ѹ����ı���
        StringBuffer str = new StringBuffer("");
        byte bin_code;

        do{
            ch =  (short) fin.read();
            if (ch != -1){
            //	System.out.print("append: "+code_order[ch]+" str = " + str);
                str.append(hufm_tree_.h_code_[code_order[ch]]);
           // 	System.out.println("-> " + str);
                while(str.length()>=8){
             //   	System.out.print("cut: str = " + str);
                    bin_code = (byte) str2short(new String(str.substring(0,8)));
                    fout_bin.writeByte(bin_code);
                    str = str.delete(0, 8); //��ȡ�±�8���Ժ�Ĳ���
               // 	System.out.println("-> " + str + ", bin_code = " + bin_code);
                }
            } //if (!fin.eof())
            else{
                bin_code = (byte) str2short(str.toString());
                fout_bin.writeByte(bin_code);
                break;
            }
        }while (ch != -1);

    //�������ѹ����ı���

        fin.close();
        fout_bin.close();

        return 0;
    }

    
    public int Decompress(DataInputStream fin_bin, OutputStream fout) throws IOException{//��ѹ�ļ�
    	int tot_decoded = 0;
        int str_len = 0;

        char_kinds_ = 0;
        char_tot_ = 0;

    	System.out.println("���ڽ�ѹ�ļ�...");
        
        
        //��ȡ������Ϣ1
        char_kinds_ = fin_bin.readInt();
        char_tot_ = fin_bin.readInt();

        byte[] char_set_ = new byte[char_kinds_+1];
        int[] weight_set_ = new int[char_kinds_+1];
        //��ȡ������Ϣ2----Ȩ�ر�
     //   System.out.println("Ȩ�ر�");
        for (int i=1; i<=char_kinds_; i++){
        	char_set_[i] = fin_bin.readByte();
        	weight_set_[i] = fin_bin.readInt();
     //       System.out.println(char_set_[i] + " " + weight_set_[i]);
        }


        //Huffman_Tree HT1;
        //���¹���Hufman��
        hufm_tree_ = new Huffman_Tree();
        hufm_tree_.Creat(weight_set_, char_kinds_);

        int curr = hufm_tree_.root_;
        byte huffman_code = 0;
        while (tot_decoded < char_tot_){
            if (str_len == 0){
            	huffman_code = fin_bin.readByte();
                str_len = 8; 
            }

            if (curr > hufm_tree_.leaf_){ //��δ����Ҷ�ڵ�
                switch (huffman_code & 1){
                case 0:
                    curr = hufm_tree_.h_tree_[curr].lchild;
                    break;
                case 1:
                    curr = hufm_tree_.h_tree_[curr].rchild;
                }
                huffman_code = (byte) (huffman_code >> 1);
                str_len--;
            }
            else{ //����Ҷ�ڵ�
                fout.write(char_set_[curr]);
                curr = hufm_tree_.root_;
                tot_decoded++;
            }
        }
        if (curr != hufm_tree_.root_)
            System.out.println("more bits wanted in the end.");

        fin_bin.close();
        fout.close();

        return 0;
    }
}

