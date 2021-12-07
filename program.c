#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DICTnode 
{
    char word[128], meaning[256];
    struct DICTnode *left, *right;
};

struct DICTnode *root = NULL;

// creating a node
struct DICTnode *createNode(char *word, char *meaning)
{
    struct DICTnode *newnode; // declaring node of DICTnode structure
    newnode = (struct DICTnode *)malloc(sizeof(struct DICTnode)); // allocating memory in heap for declared node
    strcpy(newnode->word, word); // setting value of word
    strcpy(newnode->meaning, meaning); // setting value of meaning
    newnode->left = newnode->right = NULL; // pointing its right and left to null
    printf("Word added to dict. Successfully\n");
    return newnode; // returning created node
}


// function to insert word in bst
void insert(char *word, char *meaning) 
{
    struct DICTnode *parent = NULL, *current = NULL, *newnode = NULL; // declaring nodes
    int res = 0; // created flag to add word in right node or left node
    if (!root) // if root is equal to null then we directly create new node
    {
        root = createNode(word, meaning);
        return;
    }
    for (current = root; current != NULL;
         current = (res > 0) ? current->right : current->left) // updating current w.r.t res means if res is greater than 0 it will update it to right node else left node
    {
        res = strcasecmp(word, current->word); // it will update res
        if (res == 0) 
        {
            printf("Duplicate entry!!\n");
            return;
        }
        parent = current; // updating parent node with current node
    }
    newnode = createNode(word, meaning); // i had parent node and im creting its childnode
    res > 0 ? (parent->right = newnode) : (parent->left = newnode); // if res is greater than 0 then it will be added as right node either left node
    return;
}

/*

there are three cases in deletion of particular node
    1. The node is at leaf node
    2. The node is non-leaf node
    3. The node is root node

*/


// deleting a word from dict
void deleteNode(char *str)
{
    struct DICTnode *parent = NULL, *current = NULL, *temp = NULL;  // declaring nodes
    int flag = 0, res = 0; // created flags
    if (!root) // if root is null we do this 
    {
        printf("Dict. is Empty!!\n");
        return;
    }
    current = root; // if root is not iqual to null then we will update it will current
    while (1) // while true
    {
        res = strcasecmp(current->word, str); // it will update res
        if (res == 0) // we got the word and now it's time to delete it
            break;
        flag = res; // update the flag value with res
        parent = current; // updating parent will current node
        current = (res > 0) ? current->left : current->right; // we are updating current w.r.t res value
        if (current == NULL) // if current is null then we will simply return
            printf("Word is Not Present in Dict.\n");
            return;
    }

    /* deleting leaf node */
    if (current->right == NULL) 
    {
        if (current == root && current->left == NULL) // if the leaf node is a root node
        {
            free(current);
            root = NULL;
            printf("Word Deleted Successfully.\n");
            return;
        }
        else if (current == root) // current node is a root node but it has left node
        {
            root = current->left; // updating root with left node
            free(current); // deleting current node
            printf("Word Deleted Successfully.\n");
            return;
        }

        flag > 0 ? (parent->left = current->left) : (parent->right = current->left);
    }
    else
    {
        /* delete node with single child */
        temp = current->right; 
        if (!temp->left) // if left is null of temp. node
        {
            temp->left = current->left; // set that left node to current node's left
            if (current == root) 
            {
                root = temp;
                free(current);
                printf("Word Deleted Successfully.\n");
                return;
            }
            flag > 0 ? (parent->left = temp) : (parent->right = temp);
        }
        else
        {
            /* delete node with two children */
            struct DICTnode *successor = NULL;
            while (1)
            {
                successor = temp->left; // setting the successor
                if (!successor->left) // if it is null
                    break;
                temp = successor; // updating temp with successor
            }
            temp->left = successor->right;
            successor->left = current->left; // setting successor
            successor->right = current->right;
            if (current == root) //deleting condition
            {
                root = successor; 
                free(current); // freeing memory
                printf("Word Deleted Successfully.\n");
                return;
            }
            (flag > 0) ? (parent->left = successor) : (parent->right = successor);
        }
    }
    free(current);
    printf("Word Deleted Successfully.\n");

    return;
}


// searching particular word
void findElement(char *str)
{
    struct DICTnode *temp = NULL; // declaring temporary node
    int flag = 0, res = 0; // initializing flags
    if (root == NULL) // if tree is Empty
    {
        printf("Dict. Is Empty.\n");
        return;
    }
    temp = root; // if tree is not empty then set it's root to temp
    while (temp) // traversing the temp
    {
        if ((res = strcasecmp(temp->word, str)) == 0) // if we get a word
        {
            printf("Word   : %s", str);
            printf("Meaning: %s", temp->meaning);
            flag = 1;
            break;
        }
        temp = (res > 0) ? temp->left : temp->right; // if we does not get word
    }
    if (!flag) // if flag is 0 then we can say that we dont have word
        printf("Search Element not found in Dict.\n");
    return;
}

/*
in inOrder Traversal program we do 
    1. apply inorder on left node 
    2. print root node
    3. apply inorder on right node

in preOrder Traversal program we do 
    1. print root node
    2. apply preOrder on left node 
    3. apply preOrder on right node

in postOrder Traversal program we do 
    1. apply postOrder on left node 
    2. apply postOrder on right node
    3. print root node

simply we can say that its a game of recursion
*/


// traversing whole dict.
void inorderTraversal(struct DICTnode *myNode)
{   
    if(!root){
        printf("Dict. Is Empty.\n");
    }

    if (myNode) // if node is present
    {
        inorderTraversal(myNode->left); // 1st step of inorder
        printf("Word    : %s", myNode->word); // 2nd step of inorder
        printf("Meaning : %s", myNode->meaning); // 2nd step of inorder
        printf("\n");
        inorderTraversal(myNode->right); // 3rd step of inorder
    }
    return;
}

int main()
{
    int ch;
    char str[128], meaning[256];
    while (1) 
    {
        printf("\n1. Insertion\t2. Deletion\n");
        printf("3. Searching\t4. Traversal\n");
        printf("5. Exit\nEnter ur choice:");
        scanf("%d", &ch); // getting input from user
        getchar();
        switch (ch) // switch statement on char
        {
        case 1:
            printf("Word to insert:");
            fgets(str, 100, stdin); // getting input from user
            printf("Meaning:");
            fgets(meaning, 256, stdin); // getting input from user
            insert(str, meaning); // calling insert function
            break;
        case 2:
            printf("Enter the word to delete:");
            fgets(str, 100, stdin); // getting input from user
            deleteNode(str); // calling delete function
            break;
        case 3:
            printf("Enter the search word:");
            fgets(str, 100, stdin); // getting input from user
            findElement(str); // calling search function
            break;
        case 4:
            inorderTraversal(root); // calling traversal function
            break;
        case 5:
            exit(0); // exit opt.
        default:
            printf("You have entered wrong option\n");
            break;
        }
    }
    return 0;
}