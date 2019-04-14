#include <iostream>
#include <fstream>
#include <cstdlib>

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

int main(int argc, char const *argv[]){
    // init variable------------------------------------------------------------------------------
    ifstream fin;
    ofstream fout;
    int size, buffer;
    TreeNode *tmp;

    // open files ---------------------------------------------------------------------------------
    fin.open("input");
    if (!fin) {
        cout << "file in failed" << endl;
        return 0;
    }
    fout.open("output");
    if (!fout) {
        cout << "file in failed" << endl;
        return 0;
    }

    // get k which is the kth small element---------------------------------------------------------
    if(argc != 2){
        cout << "Usage: ./BST k\n";
        return 1;
    }
    int k_in = atoi(argv[1]);
    cout << "k: " << k_in << "\n";

    // get data from input file --------------------------------------------------------------------
    fin >> size;
    cout << "Size: " << size << "\n\n";
    for(int i = 0; i < size; i++) {
        fin >> buffer;
        if (buffer == EOF) {
            cout << "file size error: " << buffer ;
            return 1;
        }
        tmp = new TreeNode(buffer);
        insertion(root, tmp);
    }

    // print inorder data -------------------------------------------------------------------------------
    cout << "Inorder: ";
    inorder(root);
    cout << "\n";
    cout << "Min: " << minimum(root)->key << "\n";
    cout << "Max: " << maximum(root)->key << "\n\n";
    
    cout << "Root: " << root->key << "\n";
    if(root->left != NULL)
        cout << "Roots's left: " << root->left->key << "\n";
    else
        cout << "Roots's left: " << "NULL" << "\n";
    if(root->right != NULL)
        cout << "Roots's right: " << root->right->key << "\n";
    else
        cout << "Roots's right: " << "NULL" << "\n";
    if(predecessor(root) != NULL)
        cout << "Roots's Predecesser: " << predecessor(root)->key << "\n";
    else
        cout << "Roots's Predecesser: " << "NULL" << "\n";
    if(successor(root) != NULL)
        cout << "Root's Successor: " << successor(root)->key << "\n\n";
    else
        cout << "Root's Successor: " << "NULL" << "\n\n";
    

    TreeNode *s = search(root, k_in);
    cout << "Search " << k_in << ": \n";
    if(s != NULL){
        if(s->parent != NULL)
            cout << k_in << "'s Parent: " << s->parent->key << "\n";
        else
            cout << k_in << "'s Parent: " << "NULL" << "\n";
        if(s->left != NULL)
            cout << k_in << "'s Left: " << s->left->key << "\n";
        else
            cout << k_in << "'s Left: " << "NULL" << "\n";
        if(s->right != NULL)
            cout << k_in << "'s Right: " << s->right->key << "\n";
        else
            cout << k_in << "'s Right: " << "NULL" << "\n";
        if(predecessor(s) != NULL)
            cout << k_in << "'s Predecesser: " << predecessor(s)->key << "\n";
        else
            cout << k_in << "'s Predecesser: " << "NULL" << "\n";
        if(successor(s) != NULL)
            cout << k_in << "'s Successor: " << successor(s)->key << "\n\n";
        else
            cout << k_in << "'s Successor: " << "NULL" << "\n\n";
    }
    else{
        cout << k_in << " not exist" << "\n\n";
    }    

    TreeNode *del = deletion(root, root);
    delete(del);
    cout << "Deletion root: ";
    inorder(root);
    cout << "\n";
    cout << "Root after deletion: " << root->key << "\n";
    if(root->left != NULL)
        cout << "Roots's left: " << root->left->key << "\n";
    else
        cout << "Roots's left: " << "NULL" << "\n";
    if(root->right != NULL)
        cout << "Roots's right: " << root->right->key << "\n";
    else
        cout << "Roots's right: " << "NULL" << "\n";
    if(predecessor(root) != NULL)
        cout << "Roots's Predecesser: " << predecessor(root)->key << "\n";
    else
        cout << "Roots's Predecesser: " << "NULL" << "\n";
    if(successor(root) != NULL)
        cout << "Root's Successor: " << successor(root)->key << "\n\n";
    else
        cout << "Root's Successor: " << "NULL" << "\n\n";

    // write sorted data to output file -----------------------------------------------------------
    // fout << size << endl;
    // for(int i = 0; i < size; i++) {
    //     fout << data[i] << endl;
    // }

    // end program stuff----------------------------------------------------------------------------
    fin.close();
    fout.close();
    return 0;
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
    // if right child exist
    if(x->right != NULL)
        return minimum(x->right);
    
    // if right child exist
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

    // choose node to be move
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
        int tmp = target->key;
        target->key = y->key;
        y->key = tmp;
    }
    
    return y;
}