#include <iostream>

using namespace std;

class TreeNode{
private:
public:
    int key;
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    TreeNode(int k);
};
TreeNode::TreeNode(){
    key = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
};
TreeNode::TreeNode(int k){
    key = k;
    parent = NULL;
    left = NULL;
    right = NULL;
};

void inorder(TreeNode *x);
TreeNode *search(TreeNode *x, int k);
TreeNode *minimum(TreeNode* x);
TreeNode *maximum(TreeNode* x);
TreeNode *successor(TreeNode *x);
TreeNode *predecessor(TreeNode *x);
void insertion(TreeNode *tree, TreeNode *target);
TreeNode * deletion(TreeNode *tree, TreeNode *target);


TreeNode *root = NULL;

int main(){

}

void inorder(TreeNode *x){
    if(x != NULL){
        inorder(x->left);
        cout << x->key << " ";
        inorder(x->right);
    }
}

TreeNode *search(TreeNode *x, int k){
    if(x == NULL || k == x->key)
        return x;
    
    if(k < x->key)
        return search(x->left, k);
    else
        return search(x->right, k);
    
}

TreeNode *minimum(TreeNode* x){
    while(x->left != NULL)
        x = x->left;

    return x;
}

TreeNode *maximum(TreeNode* x){
    while(x->right != NULL)
        x = x->right;

    return x;
}

TreeNode *successor(TreeNode *x){
    if(x->right != NULL)
        return minimum(x->right);
    
    TreeNode *y = x->parent;

    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }

    return y;
    
}

TreeNode *predecessor(TreeNode *x){
    if(x->left != NULL)
        return maximum(x->left);
    
    TreeNode *y = x->parent;

    while(y != NULL && x == y->left){
        x = y;
        y = y->parent;
    }

    return y;
    
}

void insertion(TreeNode *tree, TreeNode *target){
    TreeNode *y = NULL;
    TreeNode *x = root;

    while(x != NULL){
        y = x;
        if(target->key < x->key)
            x = x->left;
        else
            x = x->right;
        
    }

    target->parent = y;

    if(y == NULL)
        root = target;
    else if(target->key < y->key)
        y->left = target;
    else
        y->right = target;
}

TreeNode *deletion(TreeNode *tree, TreeNode *target){
    TreeNode *x = NULL;
    TreeNode *y = NULL;

    if(target->left == NULL || target->right == NULL)
        y = target;
    else
        y = successor(target);

    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if(x != NULL)
        x->parent = y->parent;

    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if(y != target){
        target->key = y->key;
        target->parent = y->parent;
        target->left = y->left;
        target->right = y->right;
    }
    
    return y;
}