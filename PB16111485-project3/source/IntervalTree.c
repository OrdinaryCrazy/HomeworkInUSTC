#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 30

enum Color{Red, Black};
typedef struct IntervalTreeNode{
    struct IntervalTreeNode* LeftChild;
    struct IntervalTreeNode* RightChild;
    struct IntervalTreeNode* Parent;
    int low,high,max;
    enum Color color;
}IntervalTreeNode;
typedef struct IntervalTree{
    IntervalTreeNode* Root;
    IntervalTreeNode* Nil;
}IntervalTree;
int max3(int a,int b,int c){
    return a > b ? ( a > c ? a : c ) : ( b > c ? b : c );
}
void IT_LeftRotate(IntervalTree* T,IntervalTreeNode* x){
    IntervalTreeNode* y = x->RightChild;
    x->RightChild = y->LeftChild;
    if(y->LeftChild != T->Nil){
        y->LeftChild->Parent = x;
    }
    y->Parent = x->Parent;
    if(x->Parent == T->Nil){
        T->Root = y;
    }
    else{
        if(x == x->Parent->LeftChild){
            x->Parent->LeftChild = y;
        }
        else{
            x->Parent->RightChild = y;
        }
    }
    y->LeftChild = x;
    y->max = x->max;
    x->Parent = y;
    x->max = max3(x->high,x->LeftChild->max,x->RightChild->max);
}
void IT_RightRotate(IntervalTree* T,IntervalTreeNode* x){
    IntervalTreeNode* y = x->LeftChild;
    x->LeftChild = y->RightChild;
    if(y->RightChild != T->Nil){
        y->RightChild->Parent = x;
    }
    y->Parent = x->Parent;
    if(y->Parent == T->Nil){
        T->Root = y;
    }
    else{
        if(x == x->Parent->LeftChild){
            x->Parent->LeftChild = y;
        }
        else{
            x->Parent->RightChild = y;
        }
    }
    y->RightChild = x;
    y->max = x->max;
    x->Parent = y;
    x->max = max3(x->high,x->LeftChild->max,x->RightChild->max);
}
void IT_InsertFixup(IntervalTree* T,IntervalTreeNode* x){
    while(x->Parent->color == Red){
        if(x->Parent == x->Parent->Parent->LeftChild){
            IntervalTreeNode* w = x->Parent->Parent->RightChild;
            if(w->color == Red){
                x->Parent->color = Black;
                w->color = Black;
                x->Parent->Parent->color = Red;
                x = x->Parent->Parent;
            }
            else{
                if(x == x->Parent->RightChild){
                    x = x->Parent;
                    IT_LeftRotate(T,x);
                }
                x->Parent->color = Black;
                x->Parent->Parent->color = Red;
                IT_RightRotate(T,x->Parent->Parent);
            }
        }
        else{
            IntervalTreeNode* w = x->Parent->Parent->LeftChild;
            if(w->color == Red){
                x->Parent->color = Black;
                w->color = Black;
                x->Parent->Parent->color = Red;
                x = x->Parent->Parent;
            }
            else{
                if(x == x->Parent->LeftChild){
                    x = x->Parent;
                    IT_RightRotate(T,x);
                }
                x->Parent->color = Black;
                x->Parent->Parent->color = Red;
                IT_LeftRotate(T,x->Parent->Parent);
            }
        }
    }
    T->Root->color = Black;
}
void IT_Insert(IntervalTree* T,IntervalTreeNode* x){
    IntervalTreeNode* y = T->Nil;
    IntervalTreeNode* z = T->Root;
    while(z != T->Nil){
        y = z;
        if(x->low < z->low){
            z = z->LeftChild;
        }
        else{
            z = z->RightChild;
        }
    }
    x->Parent = y;
    if(y == T->Nil){
        T->Root = x;
    }
    else{
        if(x->low > y->low){
            y->RightChild = x;
        }
        else{
            y->LeftChild = x;
        }
    }
    x->LeftChild = x->RightChild = T->Nil;
    x->max = x->high;
    x->color = Red;
    while(y != T->Nil){
        y->max = max3(y->high,y->LeftChild->max,y->RightChild->max);
        y = y->Parent;
    }
    IT_InsertFixup(T,x);
}
void IT_TransPlant(IntervalTree* T,IntervalTreeNode* replaced, IntervalTreeNode* replace){
    if(replaced->Parent == T->Nil){
        T->Root = replace;
    }
    else{
        if(replaced == replaced->Parent->LeftChild){
            replaced->Parent->LeftChild = replace;
        }
        else{
            replaced->Parent->RightChild = replace;
        }
    }
    replace->Parent = replaced->Parent;
}
void IT_DeleteFixup(IntervalTree* T,IntervalTreeNode* x){
    while(x != T->Root && x->color == Black){
        if(x == x->Parent->LeftChild){
            IntervalTreeNode* w = x->Parent->RightChild;
            if(w->color == Red){
                w->color = Black;
                x->Parent->color = Red;
                IT_LeftRotate(T,x->Parent);
                w = x->Parent->RightChild;
            }
            if(w->RightChild->color == Black && w->LeftChild->color == Black){
                w->color = Red;
                x = x->Parent;
            }
            else{
                if(w->LeftChild->color == Red){
                    w->color = Red;
                    w->LeftChild->color = Black;
                    IT_RightRotate(T,w);
                    w = x->Parent->RightChild;
                }
                w->color = x->Parent->color;
                x->Parent->color = Black;
                w->RightChild->color = Black;
                IT_LeftRotate(T,x->Parent);
                x = T->Root;
            }
        }
        else{
            IntervalTreeNode* w = x->Parent->LeftChild;
            if(w->color == Red){
                w->color = Black;
                x->Parent->color = Red;
                IT_RightRotate(T,x->Parent);
                w = x->Parent->LeftChild;
            }
            if(w->RightChild->color == Black && w->LeftChild->color == Black){
                w->color = Red;
                x = x->Parent;
            }
            else{
                if(w->RightChild->color == Red){
                    w->color = Red;
                    w->RightChild->color = Black;
                    IT_LeftRotate(T,w);
                    w = x->Parent->LeftChild;
                }
                w->color = x->Parent->color;
                x->Parent->color = Black;
                w->LeftChild->color = Black;
                IT_RightRotate(T,x->Parent);
                x = T->Root;
            }
        }
    }
    x->color = Black;
}
void IT_Delete(IntervalTree* T,IntervalTreeNode* x){
    IntervalTreeNode* y = x;
    int y_origin_color = y->color;
    IntervalTreeNode* z;
    if(x->LeftChild == T->Nil){
        z = x->LeftChild;
        IT_TransPlant(T,x,z);
    }
    else{
        if(x->RightChild == T->Nil){
            z = x->RightChild;
            IT_TransPlant(T,x,z);
        }
        else{
            y = x->RightChild;
            while(y->LeftChild != T->Nil){
                y = y->LeftChild;
            }
            y_origin_color = y->color;
            z = y->RightChild;
            if(y != x->RightChild){
                IT_TransPlant(T,y,z);
                y->RightChild = x->RightChild;
                y->RightChild->Parent = y;
            }
            else{
                z->Parent = y;
            }
            IT_TransPlant(T,x,y);
            y->LeftChild = x->LeftChild;
            y->LeftChild->Parent = y;
            y->color = x->color;
            free(x);
        }
    }
    y = z;
    while(y != T->Nil){
        y->max = max3(y->high,y->LeftChild->max,y->RightChild->max);
        y = y->Parent;
    }
    if(y_origin_color == Black){
        IT_DeleteFixup(T,z);
    }
}
void IT_InOrderTraverse(IntervalTree* T,IntervalTreeNode* from, FILE* out){
    if(from == T->Nil){
        return;
    }
    IT_InOrderTraverse(T,from->LeftChild,out);
    //if(from->Parent != T->Nil) fprintf(out,"[%d, %d]\t",from->Parent->low,from->Parent->high);
    fprintf(out,"[%d,%d],%d\n",from->low,from->high,from->max);
    IT_InOrderTraverse(T,from->RightChild,out);
}
IntervalTreeNode* IT_Search(IntervalTree* T,int low,int high){
    IntervalTreeNode* x = T->Root;
    while(x != T->Nil && !(low <= x->high && high >= x->low)){
        if(x->LeftChild != T->Nil && x->LeftChild->max >= low){
            x = x->LeftChild;
        }
        else{
            x = x->RightChild;
        }
    }
    return x;
}
int main(){
    srand((int)time(0)); 
    FILE* InputFile = fopen("../inputB/input_inteval.txt","r");
    int i;
    IntervalTree* T = malloc(sizeof(IntervalTree));
    T->Nil = malloc(sizeof(IntervalTreeNode));
    T->Root = T->Nil;
    T->Nil->color = Black;
    T->Nil->max = T->Nil->max = (__INT_MAX__) * (-1);
    int h[SIZE],l[SIZE];
    for(i = 0;i < SIZE;i++){
        fscanf(InputFile,"%d,%d\n",&l[i],&h[i]);
    }
    fclose(InputFile);
    //insert
    for(i = 0;i < SIZE;i++){
        IntervalTreeNode* Item = malloc(sizeof(IntervalTreeNode));
        Item->high = h[i];
        Item->low = l[i];
        IT_Insert(T,Item);
    }
    
    FILE* InOrder = fopen("../outputB/inorder.txt","w");
    FILE* DeleteData = fopen("../outputB/delete_data.txt","w");
    FILE* Search = fopen("../outputB/search.txt","w");
    //traverse
    IT_InOrderTraverse(T,T->Root,InOrder);
    int low, high;
    IntervalTreeNode* temp;
    //search
    /************************************************/
    high = rand() % 25 + 1;
    low = rand() % high;
    temp = IT_Search(T,low,high);
    if(temp != T->Nil){
        fprintf(Search,"Search: [%d, %d], Result: [%d, %d]\n",low, high, temp->low, temp->high);
    }
    else{
        fprintf(Search,"Search: [%d, %d], Result: NULL\n",low, high);
    }
    /************************************************/
    high = rand() % 3 + 27;
    low = high - rand() % (high - 26) - 1;
    temp = IT_Search(T,low,high);
    if(temp != T->Nil){
        fprintf(Search,"Search: [%d, %d], Result: [%d, %d]\n",low, high, temp->low, temp->high);
    }
    else{
        fprintf(Search,"Search: [%d, %d], Result: NULL\n",low, high);
    }
    /************************************************/
    high = rand() % 20 + 31;
    low = high - rand() % (high - 30) - 1;
    temp = IT_Search(T,low,high);
    if(temp != T->Nil){
        fprintf(Search,"Search: [%d, %d], Result: [%d, %d]\n",low, high, temp->low, temp->high);
    }
    else{
        fprintf(Search,"Search: [%d, %d], Result: NULL\n",low, high);
    }
    //delete
    for(i = 0;i < 3;i++){
        IntervalTreeNode* dele = T->Nil;
        while(dele == T->Nil){
            int tmp = rand() % 30;
            dele = IT_Search(T,l[tmp],h[tmp]);
        }
        fprintf(DeleteData,"will delete: [%d, %d]\n",dele->low,dele->high);
        IT_Delete(T,dele);
        IT_InOrderTraverse(T,T->Root,DeleteData);
    }
    fclose(InOrder);
    fclose(DeleteData);
    fclose(Search);
}