#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100
struct Node* construct(struct Node *root,char *treeElements);


struct Node{
    int value;
    struct Node *right;
    struct Node *left;

};


struct Node* minValueNode(struct Node* node)
{
    struct Node* current = node;


    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->value)
        root->left = deleteNode(root->left, key);


    else if (key > root->value)
        root->right = deleteNode(root->right, key);


    else {

        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);


        root->value = temp->value;

        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}


struct Node* newNode(int item)
{
    struct Node* temp = (struct Node*) malloc(sizeof(struct Node));
    temp->value = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* node, int item)
{
    if (node == NULL)
        return newNode(item);

    if (item < node->value ||item == node->value)
        node->left = insert(node->left, item);
    else if (item > node->value)
        node->right = insert(node->right, item);

    return node;
}

void inorder(struct Node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }

}



struct Node* parent(struct Node* root,int item)
{
     if(root!=NULL){
        if(root->value == item){
                return root;

        }else if(root->value < item){

                if(root->right != NULL)
                {
                    if(root->right->value == item){
                        return root;
                    }else{ parent(root->right, item);}

                }
                else
                {
                    return NULL;
                }
        }else if(root->value > item){
                if(root->left != NULL)
                {   if(root->left->value == item){
                        return root;
                    }else {parent(root->left, item);}

                }
                else
                {
                    return NULL;
                }
        }else{ return NULL;}

        }
}




int main()
{   char *input;
    struct Node* root = NULL;
    input = (char*) calloc(500,sizeof(char));

    while(strcasecmp(gets(input),"EXIT")!=0){

       // printf("Inputunuz: %s\n",input);
        char *command = strtok(input," ");
       // printf("Command: %s\n",command);

        if(strcasecmp(command,"CONSTRUCT")==0){

            char *treeElements = strtok(NULL," ");
            root = construct(root,treeElements);
        }
        else if(strcasecmp(command,"INSERT")==0){
            char *item = strtok(NULL," ");
           // printf("%s",item);
           int itemValue = atoi(item);
           insert(root,itemValue);
           struct Node *parentt = parent(root,itemValue);
           if(itemValue == root->value){
                printf("It is a root node\n");
            }else if(parentt == NULL){
                printf("\n Data not in the tree");
            }else{printf("The parent of %d is %d\n",itemValue,parentt->value);}
        }
        else if(strcasecmp(command,"LIST")==0) {
            inorder(root);
            printf("\n");
        }
        else if(strcasecmp(command,"PARENT")==0) {

            int p = atoi(strtok(NULL," "));
            struct Node* parentOf = parent(root,p);
            if(p == root->value){
                printf("It is a root node\n");
            }else if(parentOf == NULL){
                printf("\n Data not in the tree");
            }else{printf("The parent of %d is %d\n",p,parentOf->value);}

        }else if(strcasecmp(command,"DELETE")==0){
            char *del = strtok(NULL," ");
            int deletedItem = atoi(del);
            int rootValue = root->value;
            root = deleteNode(root,deletedItem);
            if(rootValue != root->value){
                printf("Root changed. The new root is %d\n",root->value);
            }
        }else {printf("You did not enter correct command. Please try again.\n");}

    }


    return 0;
}

struct Node* construct(struct Node *root,char *treeElements){ // CONSTRUCT [31,65,3,10,5,100,3,12] [3,4,5]

        treeElements = strtok(treeElements,"[");
        treeElements[strlen(treeElements)-1] = '\0';

        int comma = 0;

        for(int m=0;m<strlen(treeElements);m++){
            char c = treeElements[m];
            if(c == ','){
                comma++;
            }
        }

        treeElements = strtok(treeElements,",");

        root = insert(root,atoi(treeElements));
        int i=0;
        while(i<comma){
            treeElements = strtok(NULL,",");

            insert(root,atoi(treeElements));
            i++;
        }

        return root;

}


