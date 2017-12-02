
class HTNode{
    int weight = 0;
    int parent = 0, lchild = 0, rchild = 0;
    public HTNode(){}
    public HTNode(int w, int p, int l, int r){
        weight = w;
        parent = p;
        lchild = l;
        rchild = r;
    }
};

class Huffman_Tree{
    // constructors & destructor
    public Huffman_Tree(){}
   
	//data member  
//private:
    int root_; //根节点下标
    int leaf_; //叶节点数目  
	HTNode[] h_tree_; //哈夫曼数组首地址
    String[] h_code_; //
    int[] h_code_len;  //记录各个Hufman编码的长度
    
    //general member function
    public int Creat(int[] w, int n) {
        leaf_ = n;
        int m = 2 * n - 1;
        h_tree_ = new HTNode[m+1];
        int i = 0, j = 0, jmin;

        for (i=1; i<2*n; i++)
        	h_tree_[i] = new HTNode();
        
        for (i=1; i<=n; i++)
        	h_tree_[i].weight = w[i];
          //  h_tree_[i].weight = w[i];
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
    public int Coding(){
     //得到每个字符对应的编码
    	h_code_ = new String[leaf_+1];
    	h_code_len = new int[leaf_+1];
    	int i,curr,father;
        String str;

   	    for (i=1; i<=leaf_; i++){
   	        str = "";
   	        curr = i;
   	        h_code_len[i] = 0;
   	        do{
    	        father = h_tree_[curr].parent;
    	        if (h_tree_[father].lchild == curr)
    	            str = "0" + str;
                else
                	str = "1" + str;
   	            curr = father;
                h_code_len[i]++;
    	    }while(curr != 2*leaf_-1);
    	    h_code_[i] = str;
    	    
    	  //  System.out.println(i+" "+h_code_[i]+" "+h_code_len[i]);

    	}
        return 0;
   	}

    //input/output function
    public int print(){
        int i;
    	System.out.println("num. wght. prt. lch. rch.") ;
        for (i=1; i <= root_; i++){
        	System.out.print(i+" ") ;
        	System.out.print(h_tree_[i].weight+" ") ;
    	    System.out.print(h_tree_[i].parent+" ") ;
        	System.out.print(h_tree_[i].lchild+" ") ;
        	System.out.println(h_tree_[i].rchild+" ") ;
        }
        return 0;
    }
};