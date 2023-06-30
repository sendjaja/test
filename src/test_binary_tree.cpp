#include "test_binary_tree.h"

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
}node;

static node *root;

static int insert(int new_value);
// static int remove(int old_value) ;
// static int search(int value);

int insert(int new_value) {
    cout << "Inserting: " << new_value << endl;

    struct node *tempNode = (struct node*) malloc(sizeof(struct node));
    memset(tempNode, 0, sizeof(struct node));
    struct node *current;
    struct node *parent;

    tempNode->value = new_value;
    tempNode->left = NULL;
    tempNode->right = NULL;

    //if root is null or empty
    if(root == NULL)
    {
        root = tempNode;
    }
    else
    {
        current = root;
        parent = NULL;

        while(1)
        {
            parent = current;

            if(new_value < parent->value)
            {
                //new_value is smaller, then go to left
                cout << "new_value is smaller" << endl;

                //assign current to the root->left
                current = current->left;

                if(current == NULL)
                {
                    //root->left is null, this is the right place
                    //assign the root left to tempNode
                    parent->left = tempNode;
                    return 0;
                }
            } 
            else
            {
                //new_value is bigger, then go to right
                cout << "new_value is bigger" << endl;

                //Assign current to the root->right
                current = current->right;

                if(current == NULL)
                {
                    //root->right is null, this is the right place
                    //assign the root right to tempNode
                    parent->right = tempNode;
                    return 0;
                }
            }
        }
    }

    return 0;
}

/*
int remove(int old_value)
{
    return 0;
}

int search(int value)
{
    return 0;
}
*/

void in_order_recurse(node *cur_node)
{
    if(cur_node != NULL)
    {
        //In order traversal
        //Will go to left first, then parent, then right
        in_order_recurse(cur_node->left);
        cout << cur_node->value << endl;
        in_order_recurse(cur_node->right);
    }
}

void pre_order_recurse(node *cur_node)
{
    if(cur_node != NULL)
    {
        //Pre order traversal
        //Will go to parent first, then left, then right
        cout << cur_node->value << endl;
        pre_order_recurse(cur_node->left);
        pre_order_recurse(cur_node->right);
    }
}

void post_order_recurse(node *cur_node)
{
    if(cur_node != NULL)
    {
        //Post order traversal
        //Will go to left first, then right, then parent
        post_order_recurse(cur_node->left);
        post_order_recurse(cur_node->right);
        cout << cur_node->value << endl;
    }
}

int display_tree()
{
    // int level=0;
    // struct node *temp;

    cout << "============" << endl;
    cout << "Display tree" << endl;
    cout << "============" << endl;

    cout << "In order traversal" << endl;
    in_order_recurse(root);
    cout << "Pre order traversal" << endl;
    pre_order_recurse(root);
    cout << "Post order traversal" << endl;
    post_order_recurse(root);

    return 0;
}

int test_binary_tree()
{
    cout << "Start of binary tree" << endl;
    insert(5);
    insert(3);
    insert(7);
    insert(1);
    insert(9);
    display_tree();
    return 0;
}