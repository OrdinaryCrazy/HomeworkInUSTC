#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

enum Color{red, black};
typedef struct RedBlackNode{
    struct RedBlackNode* left;
    struct RedBlackNode* right;
    struct RedBlackNode* parent;
    int key;
    enum Color color;
}RedBlackNode;
typedef struct RedBlackTree{
    RedBlackNode* root;
    RedBlackNode* nil;
}RedBlackTree;
void RB_LeftRotate(RedBlackTree* T,RedBlackNode* x){
    RedBlackNode* y = x->right;
    x->right = y->left;
    if(y->left != T->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->nil){
        T->root = y;
    }
    else{
        if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}
void RB_RightRotate(RedBlackTree* T,RedBlackNode* x){
    RedBlackNode* y = x->left;
    x->left = y->right;
    if(y->right != T->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->nil){
        T->root = y;
    }
    else{
        if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }
    y->right = x;
    x->parent = y;
}
void RB_InsertFixup(RedBlackTree* T,RedBlackNode* x){
    while(x->parent->color == red){     //破坏红黑树性质：红结点子节点为黑节点，所以需要调整
        if(x->parent == x->parent->parent->left){ //这一步区分主要是叔节点位置以及之后的左右旋
            RedBlackNode* y = x->parent->parent->right;
            if(y->color == red){    //case1: 同层双红，问题上移
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else{   //case2,3:调整之后各节点黑高不变，调整完即结束
                if(x == x->parent->right){  //case2:统一到违反规定的红色子节点在其父左儿子
                    x = x->parent;
                    RB_LeftRotate(T,x);
                }
                //case3:红色父节点变黑上移，黑色爷节点变红下移，各节点黑高不变，红结点子节点为黑节点性质得到恢复
                x->parent->color = black;           
                x->parent->parent->color = red;
                RB_RightRotate(T,x->parent->parent);
            }
        }
        else{
            RedBlackNode* y = x->parent->parent->left;
            if(y->color == red){    //case1: 同层双红，问题上移
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else{   //case2,3:调整之后各节点黑高不变，调整完即结束
                if(x == x->parent->left){  //case2:统一到违反规定的红色子节点在其父右儿子
                    x = x->parent;
                    RB_RightRotate(T,x);
                }
                //case3:红色父节点变黑上移，黑色爷节点变红下移，各节点黑高不变，红结点子节点为黑节点性质得到恢复
                x->parent->color = black;           
                x->parent->parent->color = red;
                RB_LeftRotate(T,x->parent->parent);
            }
        }
    }
    T->root->color = black;
}
void RB_Insert(RedBlackTree* T,RedBlackNode* x){
    RedBlackNode* y = T->nil;
    RedBlackNode* z = T->root;
    while(z != T->nil){
        y = z;
        if(x->key > z->key){
            z = z->right;
        }
        else{
            z = z->left;
        }
    }
    x->parent = y;
    if(y == T->nil){
        T->root = x;
    }
    else{
        if(x->key < y->key){
            y->left = x;
        }
        else{
            y->right = x;
        }
    }
    x->left = x->right = T->nil;
    x->color = red;
    RB_InsertFixup(T,x);
}
void RB_TransPlant(RedBlackTree* T,RedBlackNode* replaced,RedBlackNode* replace){
    if(replaced->parent == T->nil){
        T->root = replace;
    }
    else{
        if(replaced == replaced->parent->left){
            replaced->parent->left = replace;
        }
        else{
            replaced->parent->right = replace;
        }
    }
    replace->parent = replaced->parent;
}
void RB_DeleteFixup(RedBlackTree* T,RedBlackNode* x){
    while(x != T->root && x->color == black){   //x上有两重黑，所以需要调整
        if(x == x->parent->left){
            RedBlackNode* w = x->parent->right; 
            if(w->color == red){    //case1:兄弟节点为红色，统一到兄弟节点为黑色
                w->color = black;
                x->parent->color = red;
                RB_LeftRotate(T,x->parent);
                w = x->parent->right;
            }
            if(w->left->color == black && w->right->color == black){
                //case2:兄弟节点两个子节点都是黑色，则可以安全地脱掉一层黑色到父节点
                w->color = red;
                x = x->parent;
            }
            else{
                if(w->right->color == black){
                    //case3:兄弟节点的左儿子是红色，统一到右儿子是红色
                    w->left->color = black;
                    w->color = red;
                    RB_RightRotate(T,w);
                    w = x->parent->right;
                }
                //case4:修改颜色保持其他节点黑高，重叠的黑色脱到下移的原父节点
                w->color = x->parent->color;
                w->right->color = black;
                x->parent->color = black;
                RB_LeftRotate(T,x->parent);
                x = T->root;    //此时重叠黑高度已经被消化，强行退出循环
            }
        }
        else{
            RedBlackNode* w = x->parent->left; 
            if(w->color == red){    //case1:兄弟节点为红色，统一到兄弟节点为黑色
                w->color = black;
                x->parent->color = red;
                RB_RightRotate(T,x->parent);
                w = x->parent->left;
            }
            if(w->left->color == black && w->right->color == black){
                //case2:兄弟节点两个子节点都是黑色，则可以安全地脱掉一层黑色到父节点
                w->color = red;
                x = x->parent;
            }
            else{
                if(w->left->color == black){
                    //case3:兄弟节点的右儿子是红色，统一到左儿子是红色
                    w->right->color = black;
                    w->color = red;
                    RB_LeftRotate(T,w);
                    w = x->parent->left;
                }
                //case4:修改颜色保持其他节点黑高，重叠的黑色脱到下移的原父节点
                w->color = x->parent->color;
                w->left->color = black;
                x->parent->color = black;
                RB_RightRotate(T,x->parent);
                x = T->root;    //此时重叠黑高度已经被消化，强行退出循环
            }
        }
    }
    x->color = black;
}
void RB_Delete(RedBlackTree* T,RedBlackNode* x){
    RedBlackNode* y = x;
    int y_original_color = y->color;    //y是真正被删除的节点
    RedBlackNode* z;                    //z是取代y的节点
    if(x->left == T->nil){  
        z = x->right;
        RB_TransPlant(T,x,z);
    }
    else{
        if(x->right == T->nil){
            z = x->left;
            RB_TransPlant(T,x,z);
        }
        else{
            y = x->right;
            while(y->left != T->nil){
                y = y->left;
            }
            y_original_color = y->color;
            z = y->right;
            if(y != x->right){
                RB_TransPlant(T,y,z);
                y->right = x->right;
                y->right->parent = y;
            }
            else{
                z->parent = y;
            }
            RB_TransPlant(T,x,y);
            y->left = x->left;
            y->left->parent = y;
            y->color = x->color;
            free(x);
        }
    }
    if(y_original_color == black){
        RB_DeleteFixup(T,z);
    }
}
void RB_InOrderTraverse(RedBlackTree* T, RedBlackNode* from, FILE* out){
    if(from == T->nil){
        return;
    }
    RB_InOrderTraverse(T,from->left,out);
    fprintf(out,"%d\n",from->key);
    RB_InOrderTraverse(T,from->right,out);
}
void RB_ProOrderTraverse(RedBlackTree* T, RedBlackNode* from, FILE* out){
    if(from == T->nil){
        return;
    }
    fprintf(out,"%d\n",from->key);
    RB_ProOrderTraverse(T,from->left,out);
    RB_ProOrderTraverse(T,from->right,out);
}
void RB_PastOrderTraverse(RedBlackTree* T, RedBlackNode* from, FILE* out){
    if(from == T->nil){
        return;
    }
    fprintf(out,"%d\n",from->key);
    RB_PastOrderTraverse(T,from->left,out);
    RB_PastOrderTraverse(T,from->right,out);
}
RedBlackNode* RB_Find(RedBlackTree* T,int target){
    RedBlackNode* x = T->root;
    while(x != T->nil && x->key != target){
        if(x->key > target){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    return x;
}
void Clear_RBTree(RedBlackTree* T, RedBlackNode* from){
    if(from == T->nil){
        return;
    }
    Clear_RBTree(T, from->left);
    Clear_RBTree(T, from->right);
    free(from);
}
int main(){
    srand((int)time(0)); 
    FILE* InputFile = fopen("../inputA/input_integer.txt","r");
    int keys[100],i,j;
    for(i = 0;i < 100;i++){
        fscanf(InputFile,"%d\n",&keys[i]);
    }
    fclose(InputFile);
    struct timeval start,end;
    long sumt;
    RedBlackTree* T = malloc(sizeof(RedBlackTree));
    T->nil = malloc(sizeof(RedBlackNode));
    T->root = T->nil;
    T->nil->color = black;
    /********************* size20  ************************/
    FILE* InOrderOut = fopen("../outputA/size20/inorder.txt","w");
    FILE* PreOrderOut = fopen("../outputA/size20/preorder.txt","w");
    FILE* PastOrderOut = fopen("../outputA/size20/postorder.txt","w");
    FILE* time1out = fopen("../outputA/size20/time1.txt","w");
    FILE* deleteout = fopen("../outputA/size20/delete_data.txt","w");
    FILE* time2out = fopen("../outputA/size20/time2.txt","w");
    sumt = 0;
    for(i = 0;i < 2;i++){
        long ten_cost = 0;
        for(j = 0;j < 10;j++){
            RedBlackNode* in = malloc(sizeof(RedBlackNode));
            in->key = keys[i * 10 + j];
            gettimeofday(&start,NULL);
            RB_Insert(T,in);
            gettimeofday(&end,NULL);
            ten_cost += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        }
        fprintf(time1out,"%d ~ %d time cost: %ld us\n",i * 10 + 1, (i + 1) * 10,ten_cost);
        sumt += ten_cost;
    }
    fprintf(time1out,"size = 20, sumtime cost: %ld us\n",sumt);
    
    RB_InOrderTraverse(T,T->root,InOrderOut);
    RB_ProOrderTraverse(T,T->root,PreOrderOut);
    RB_PastOrderTraverse(T,T->root,PastOrderOut);
    
    for(i = 0;i < 2;i++){
        RedBlackNode* dele = T->nil;
        while(dele == T->nil){
            int choose = rand() % 20;
            dele = RB_Find(T,keys[choose]);
        }
        fprintf(deleteout,"will delete: %d\n",dele->key);
        gettimeofday(&start,NULL);
        RB_Delete(T,dele);
        gettimeofday(&end,NULL);
        long deletime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        fprintf(time2out,"delete cost = %ld us\n",deletime);
        RB_InOrderTraverse(T,T->root,deleteout);
    }
    
    fclose(InOrderOut);
    fclose(PreOrderOut);
    fclose(PastOrderOut);
    fclose(time1out);
    fclose(deleteout);
    fclose(time2out);
    Clear_RBTree(T,T->root);
    T->root = T->nil;
    /********************* size40  ************************/
    InOrderOut = fopen("../outputA/size40/inorder.txt","w");
    PreOrderOut = fopen("../outputA/size40/preorder.txt","w");
    PastOrderOut = fopen("../outputA/size40/postorder.txt","w");
    time1out = fopen("../outputA/size40/time1.txt","w");
    deleteout = fopen("../outputA/size40/delete_data.txt","w");
    time2out = fopen("../outputA/size40/time2.txt","w");
    sumt = 0;
    for(i = 0;i < 4;i++){
        long ten_cost = 0;
        for(j = 0;j < 10;j++){
            RedBlackNode* in = malloc(sizeof(RedBlackNode));
            in->key = keys[i * 10 + j];
            gettimeofday(&start,NULL);
            RB_Insert(T,in);
            gettimeofday(&end,NULL);
            ten_cost += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        }
        fprintf(time1out,"%d ~ %d time cost: %ld us\n",i * 10 + 1, (i + 1) * 10,ten_cost);
        sumt += ten_cost;
    }
    fprintf(time1out,"size = 40, sumtime cost: %ld us\n",sumt);
    
    RB_InOrderTraverse(T,T->root,InOrderOut);
    RB_ProOrderTraverse(T,T->root,PreOrderOut);
    RB_PastOrderTraverse(T,T->root,PastOrderOut);
    fclose(InOrderOut);
    fclose(PreOrderOut);
    fclose(PastOrderOut);
    fclose(time1out);
    for(i = 0;i < 4;i++){
        RedBlackNode* dele = T->nil;
        while(dele == T->nil){
            int choose = rand() % 40;
            dele = RB_Find(T,keys[choose]);
            //printf("%d\n",dele == T->nil);
        }
        fprintf(deleteout,"will delete: %d\n",dele->key);
        //printf("will delete: %d,  %d,  %d\n",dele->key,dele == T->nil, dele->left == T->nil);
        gettimeofday(&start,NULL);
        RB_Delete(T,dele);
        gettimeofday(&end,NULL);
        long deletime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        fprintf(time2out,"delete cost = %ld us\n",deletime);
        RB_InOrderTraverse(T,T->root,deleteout);
    }
    
    fclose(deleteout);
    fclose(time2out);
    Clear_RBTree(T,T->root);
    //printf("hhdkasjk %d\n",T->root);
    
    T->root = T->nil;
    /********************* size60  ************************/
    InOrderOut =   fopen("../outputA/size60/inorder.txt","w");
    PreOrderOut =  fopen("../outputA/size60/preorder.txt","w");
    PastOrderOut = fopen("../outputA/size60/postorder.txt","w");
    time1out =     fopen("../outputA/size60/time1.txt","w");
    deleteout =    fopen("../outputA/size60/delete_data.txt","w");
    time2out =     fopen("../outputA/size60/time2.txt","w");
    
    sumt = 0;
    for(i = 0;i < 6;i++){
        long ten_cost = 0;
        for(j = 0;j < 10;j++){
            RedBlackNode* in = malloc(sizeof(RedBlackNode));
            in->key = keys[i * 10 + j];
            gettimeofday(&start,NULL);
            RB_Insert(T,in);
            gettimeofday(&end,NULL);
            ten_cost += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        }
        fprintf(time1out,"%d ~ %d time cost: %ld us\n",i * 10 + 1, (i + 1) * 10,ten_cost);
        sumt += ten_cost;
    }
    fprintf(time1out,"size = 60, sumtime cost: %ld us\n",sumt);
    
    RB_InOrderTraverse(T,T->root,InOrderOut);
    RB_ProOrderTraverse(T,T->root,PreOrderOut);
    RB_PastOrderTraverse(T,T->root,PastOrderOut);
    
    for(i = 0;i < 6;i++){
        RedBlackNode* dele = T->nil;
        while(dele == T->nil){
            int choose = rand() % 60;
            dele = RB_Find(T,keys[choose]);
        }
        fprintf(deleteout,"will delete: %d\n",dele->key);
        gettimeofday(&start,NULL);
        RB_Delete(T,dele);
        gettimeofday(&end,NULL);
        long deletime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        fprintf(time2out,"delete cost = %ld us\n",deletime);
        RB_InOrderTraverse(T,T->root,deleteout);
    }
    
    fclose(InOrderOut);
    fclose(PreOrderOut);
    fclose(PastOrderOut);
    fclose(time1out);
    fclose(deleteout);
    fclose(time2out);
    Clear_RBTree(T,T->root);
    T->root = T->nil;
    /********************* size80  ************************/
    InOrderOut = fopen("../outputA/size80/inorder.txt","w");
    PreOrderOut = fopen("../outputA/size80/preorder.txt","w");
    PastOrderOut = fopen("../outputA/size80/postorder.txt","w");
    time1out = fopen("../outputA/size80/time1.txt","w");
    deleteout = fopen("../outputA/size80/delete_data.txt","w");
    time2out = fopen("../outputA/size80/time2.txt","w");
    sumt = 0;
    for(i = 0;i < 8;i++){
        long ten_cost = 0;
        for(j = 0;j < 10;j++){
            RedBlackNode* in = malloc(sizeof(RedBlackNode));
            in->key = keys[i * 10 + j];
            gettimeofday(&start,NULL);
            RB_Insert(T,in);
            gettimeofday(&end,NULL);
            ten_cost += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        }
        fprintf(time1out,"%d ~ %d time cost: %ld us\n",i * 10 + 1, (i + 1) * 10,ten_cost);
        sumt += ten_cost;
    }
    fprintf(time1out,"size = 80, sumtime cost: %ld us\n",sumt);
    
    RB_InOrderTraverse(T,T->root,InOrderOut);
    RB_ProOrderTraverse(T,T->root,PreOrderOut);
    RB_PastOrderTraverse(T,T->root,PastOrderOut);
    
    for(i = 0;i < 8;i++){
        RedBlackNode* dele = T->nil;
        while(dele == T->nil){
            int choose = rand() % 80;
            dele = RB_Find(T,keys[choose]);
        }
        fprintf(deleteout,"will delete: %d\n",dele->key);
        gettimeofday(&start,NULL);
        RB_Delete(T,dele);
        gettimeofday(&end,NULL);
        long deletime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        fprintf(time2out,"delete cost = %ld us\n",deletime);
        RB_InOrderTraverse(T,T->root,deleteout);
    }
    
    fclose(InOrderOut);
    fclose(PreOrderOut);
    fclose(PastOrderOut);
    fclose(time1out);
    fclose(deleteout);
    fclose(time2out);
    Clear_RBTree(T,T->root);
    T->root = T->nil;
    /********************* size100 ************************/
    InOrderOut = fopen("../outputA/size100/inorder.txt","w");
    PreOrderOut = fopen("../outputA/size100/preorder.txt","w");
    PastOrderOut = fopen("../outputA/size100/postorder.txt","w");
    time1out = fopen("../outputA/size100/time1.txt","w");
    deleteout = fopen("../outputA/size100/delete_data.txt","w");
    time2out = fopen("../outputA/size100/time2.txt","w");
    sumt = 0;
    for(i = 0;i < 10;i++){
        long ten_cost = 0;
        for(j = 0;j < 10;j++){
            RedBlackNode* in = malloc(sizeof(RedBlackNode));
            in->key = keys[i * 10 + j];
            gettimeofday(&start,NULL);
            RB_Insert(T,in);
            gettimeofday(&end,NULL);
            ten_cost += (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        }
        fprintf(time1out,"%d ~ %d time cost: %ld us\n",i * 10 + 1, (i + 1) * 10,ten_cost);
        sumt += ten_cost;
    }
    fprintf(time1out,"size = 100, sumtime cost: %ld us\n",sumt);
    
    RB_InOrderTraverse(T,T->root,InOrderOut);
    RB_ProOrderTraverse(T,T->root,PreOrderOut);
    RB_PastOrderTraverse(T,T->root,PastOrderOut);
    
    for(i = 0;i < 10;i++){
        RedBlackNode* dele = T->nil;
        while(dele == T->nil){
            int choose = rand() % 100;
            dele = RB_Find(T,keys[choose]);
        }
        fprintf(deleteout,"will delete: %d\n",dele->key);
        gettimeofday(&start,NULL);
        RB_Delete(T,dele);
        gettimeofday(&end,NULL);
        long deletime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        fprintf(time2out,"delete cost = %ld us\n",deletime);
        RB_InOrderTraverse(T,T->root,deleteout);
    }
    
    fclose(InOrderOut);
    fclose(PreOrderOut);
    fclose(PastOrderOut);
    fclose(time1out);
    fclose(deleteout);
    fclose(time2out);
    Clear_RBTree(T,T->root);
    T->root = T->nil;
    /*********************************************************************/
    return 0;
}