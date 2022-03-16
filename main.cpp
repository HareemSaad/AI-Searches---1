#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

//for tree
struct Node {
    int data;                                                                                   //data
    struct Node* LeftChild;                                                            //LeftChild
    struct Node* RightChild;                                                          //RightChild
};

struct Node* Root = NULL;

//for queue
struct QueueNode
{
    struct Node* BTNode = NULL; //data
    struct QueueNode* link; //link
};

struct QueueNode* Front = NULL; // global variable start, equate start with null
struct QueueNode* Rear = NULL;

void EnQueue(struct Node* NewNode) {                                // declare temp node type pointer variable
    Rear = new QueueNode;
    Rear->BTNode = NewNode;
    Rear->link = NULL;
    if (Front == NULL) {
        Front = Rear;
    } else {
        struct QueueNode* curr = Front; //declare node type pointer variable curr with assigned value of start
        while(curr->link!=NULL) {
            curr = curr->link;
        }
        curr->link=Rear;
    }
}

void PrintQueue() {
    if(Front==NULL) {
        printf("\nlist empty");
    } else {
        printf("\nyour list is... ");
        struct QueueNode* curr = Front; //declare node type pointer variable curr with assigned value of start
        while(curr!=NULL) {
            cout <<  curr->BTNode->data << endl;
            curr = curr->link;
        }
    }
}

int DeQueue() {
    struct QueueNode* curr = Front; //declare node type pointer variable curr with assigned value of start
    if (Front==NULL) {
        printf("\nQueue underflow");
    } else {
        Front = curr->link;
        int a = curr ->BTNode->data;
        delete(curr);
        return a;
    }
}

//rest of tree functions
struct Node* Insert(struct Node* node, int data) {
    if (node==NULL) {
        struct Node* temp;                                                                      // declare temp node type pointer variable
        temp = new Node;
        temp->data = data;
        //all set to null
        temp->LeftChild=NULL;
        temp->RightChild=NULL;
        return temp;
    }
    if (data < node->data) {
       node->LeftChild = Insert(node->LeftChild, data);
    } else {
        node->RightChild = Insert(node->RightChild, data);
    }
    return node;
}

int LevelOfTree(struct Node* node)
{
  if (node == NULL)
    return 0;

  int leftDepth = LevelOfTree(node->LeftChild);
  int rightDepth = LevelOfTree(node->RightChild);
  
  return max(leftDepth, rightDepth) + 1;
}

void BFS(struct Node* curr) {
    EnQueue(curr);
    while(Front!=NULL) {
        curr = Front->BTNode;
        if (curr->LeftChild != NULL) {
            EnQueue(curr->LeftChild);
        }
        if (curr->RightChild != NULL) {
            EnQueue(curr->RightChild);
        }
        cout << DeQueue() << " ";
    }
    cout<<endl;
}

void DFS(struct Node* curr) {
    if (curr==NULL)
    {
        return;
    }
    cout << curr->data << " ";
    DFS(curr->LeftChild);
    DFS(curr->RightChild);
}

struct Node* DLS(struct Node* curr, int to_search, int DepthLimit, int Depth = -1) {
    Depth++;
    cout << curr->data << " t: " << Depth << endl;
    if (curr->data == to_search) {
        return curr;
    } else if (Depth >= DepthLimit) {
        return NULL;
    } else {
        struct Node* temp;
        if (curr->LeftChild != NULL) {
            temp = DLS(curr->LeftChild, to_search, DepthLimit, Depth);
            if (temp != NULL) {
                return temp;
            }
        }
        if (curr->RightChild != NULL) {
            temp = DLS(curr->RightChild, to_search, DepthLimit, Depth);
            if (temp != NULL) {
                return temp;
            }
        }
        return NULL;
    }
}

struct Node* IDS(struct Node* curr, int to_search) {
    struct Node* temp;
    int depth = 0, level = LevelOfTree(curr);
    while (depth < level) {
        //cout << "d: " << depth << " l: " << level << endl;
        temp = DLS(curr, to_search, depth);
        cout <<  endl;
        if (temp!=NULL && temp->data == to_search) {
                cout << "~~" << temp->data << endl;
            return temp;
        }
        depth++;
        //cout << "d: " << depth << " l: " << level << endl;
    }
    cout << "value not found" << endl;
    return NULL;
};

int main()
{
    int a;
    int value, tosearch;
    struct Node* temp;
    struct Node* temp1;
    while(1) {
        printf ("\nchoose an option: \n1-Insert\t2-BFS\t\t3-DFS\t\t4-DLS\t\t5-IDS\nOpt:");
        scanf ("%d", &a);
        switch (a) {
            case 1: {
//                printf ("\nenter value: ");
//                scanf ("%d", &value);
//                Root = Insert(Root, value);
                Root = Insert(Root, 77);
                Root = Insert(Root, 55);
                Root = Insert(Root, 88);
                Root = Insert(Root, 44);
                Root = Insert(Root, 66);
                Root = Insert(Root, 11);
                Root = Insert(Root, 56);
                Root = Insert(Root, 78);
                Root = Insert(Root, 99);
                Root = Insert(Root, 79);

                break;
            }
            case 2: {
                BFS(Root);
                break;
            }
            case 3: {
                DFS(Root);
                break;
            }
            case 4: {
                cout << "\nenter tosearch: ";
                cin >> tosearch;
                temp = DLS(Root, tosearch, 2);
                if (temp != NULL)
                    cout << "data fount at node with address " << temp << " with data " << temp->data <<endl;
                else
                    cout << "value not found" <<endl;
                break;
            }
            case 5: {
                cout << "\nenter tosearch: ";
                cin >> tosearch;
                temp1 = IDS(Root, tosearch);
                if (temp1 != NULL)
                    cout << "data fount at node with address " << temp1<< " with data " << temp1->data <<endl;
                break;
            }
            default: {
                exit(a);
            }
        }
    }
}







