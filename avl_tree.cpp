#include <iostream>
#include <vector>


template<typename T>
class Tree{
public:
    Tree() = default;
    explicit Tree(std::vector<T> values);
    struct Node{
        Node* left{nullptr};
        Node* right{nullptr};
        int height{1};
        int size{1};
        T value;
    };
    void Insert(T value);
    void PrintInOrder() const;
    void PrintPostOrder() const;
    int GetHeight() const;
    int GetSize() const;
private:
    Node* root{nullptr};
    //avl_tree
//    static void printpostorder();
    static void balance_subtree(Node*& current_node);
    static int height_difference(Node* left_node, Node* right_node);
    static int tree_height(Node *current_node);
    static int tree_size(Node *current_node);
    static void fix_height(Node *&current_node);
    static void fix_size(Node *current_node);
    //insert
    static void insert(Node*& current_node, Node * new_node);
    //print
    static void printinorder_recursive(Node* node) ;
    static void printpostorder_recursive(Node * node);
    //rotates
    static void small_right_rotate(Node*& current_node);
    static void small_left_rotate(Node*& current_node);
    static void big_right_rotate(Node*& current_node);
    static void big_left_rotate(Node*& current_node);


    int get_height() const;
    int get_size() const;
};

template<typename T>
void Tree<T>::PrintInOrder() const{
    printinorder_recursive(root);
}

template<typename T>
void Tree<T>::printinorder_recursive(Node *node){
    if (node == nullptr) {
        return;
    }
    printinorder_recursive(node->left);
    std::cout<<node->value<<" ";
    printinorder_recursive(node->right);

}


template<typename T>
void Tree<T>::PrintPostOrder() const{
    printpostorder_recursive(root);
}

template<typename T>
void Tree<T>::printpostorder_recursive(Node * node) {
    if (node == nullptr) {
        return;
    }

    printpostorder_recursive(node->left);
    printpostorder_recursive(node->right);
    std::cout<<node->value<<" ";
}

template<typename T>
void Tree<T>::Insert(T value) {
    Node * new_node = new Node{.value = std::move(value)};
    if (root == nullptr){
        root = new_node;
        std::cout<<root->value<<std::endl;

    } else {
        std::cout<<"Insert"<<std::endl;
        std::cout<<value<<std::endl;
        insert(root, new_node);
    }
}

template<typename T>
void Tree<T>::insert(Node *& current_node, Node * new_node) {
    if (new_node->value <= current_node->value){
        if(current_node->left == nullptr) {
            current_node->left = new_node;
            if (current_node->right == nullptr ){
                fix_height(current_node);
                fix_size(current_node);
            }
            return;
        }else {
            insert(current_node->left, new_node);
        }
    }else {
        if (current_node->right == nullptr) {
            current_node->right = new_node;
            if (current_node->left == nullptr ){
                fix_height(current_node);
                fix_size(current_node);
            }
            return;
        } else {
            insert(current_node->right, new_node);
        }
    }
    balance_subtree(current_node);
}

template<typename T>
void Tree<T>::balance_subtree(Node *&current_node) {
    std::cout<<"balance_subtree"<<std::endl;
    std::cout<<"val = "<<current_node->value<<std::endl;
    std::cout<<"tree_height(current_node->left) = "<<tree_height(current_node->left)<<std::endl;
    std::cout<<"tree_height(current_node->right) = "<<tree_height(current_node->right)<<std::endl;
    if (height_difference(current_node->left, current_node->right) > 1) {
        std::cout<<"if (height_difference(current_node->left, current_node->right) == 2) "<<std::endl;
        auto left_node = current_node->left;
        if (height_difference(left_node->left, left_node->right) >= 0) {
            small_right_rotate(current_node);
        } else {
            big_right_rotate(current_node);
        }
    }
    if(height_difference(current_node->right, current_node->left) == 2) {
        std::cout<<"f(height_difference(current_node->right, current_node->left) == 2) {"<<std::endl;
        auto right_node = current_node->right;
        if (height_difference(right_node->left, right_node->right) <= 0) {
            small_left_rotate(current_node);
        } else {
            big_left_rotate(current_node);
        }
    }
    fix_height(current_node);
    fix_size(current_node);
    std::cout<<std::endl;
    std::cout<<"postorder"<<std::endl;
    printpostorder_recursive(current_node);
    std::cout<<std::endl;
}



//rotates
template<typename T>
void Tree<T>::small_right_rotate(Node *&current_node) {
    auto left_node = current_node->left;
    auto tmp_child = left_node->right;//c
    left_node->right = current_node;//a
    current_node->left = tmp_child;//c
    fix_height(current_node);
    fix_size(current_node);
    current_node = left_node;//b
    fix_height(left_node);
    fix_size(left_node);
    std::cout<<"I did small_right_rotate"<<std::endl;
}

template<typename T>
void Tree<T>::big_left_rotate(Node *&current_node) {
    small_right_rotate(current_node->right);
    small_left_rotate(current_node);
    std::cout<<"I did big_left_rotate"<<std::endl;
}

template<typename T>
void Tree<T>::big_right_rotate(Node *&current_node) {
    small_left_rotate(current_node->left);
    small_right_rotate(current_node);
    std::cout<<"I did big_right_rotate"<<std::endl;
}

template<typename T>
void Tree<T>::small_left_rotate(Node *&current_node) {
    auto right_node = current_node->right;
    auto tmp_child = right_node->left;//c
    right_node->left = current_node;//a
    current_node->right = tmp_child;//c
    fix_height(current_node);
    fix_size(current_node);
    current_node = right_node;//b
    fix_height(right_node);
    fix_size(right_node);
    std::cout<<"I did small_left_rotate"<<std::endl;
}

template<typename T>
int Tree<T>::height_difference(Node * left_node, Node* right_node){
    return (tree_height(left_node) - tree_height(right_node));
}

template<typename T>
int Tree<T>::tree_height(Node *current_node){
    if (current_node == nullptr){
        return 0;
    }
    return current_node->height;
}

template<typename T>
void Tree<T>::fix_height(Node *&current_node) {
    std::cout<<"fix_height"<<std::endl;

    current_node->height = std::max(tree_height(current_node->left), tree_height(current_node->right)) + 1;
    std::cout<<current_node->value<<" "<<current_node->height<<std::endl;
}


template<typename T>
void Tree<T>::fix_size(Node *current_node) {
    current_node->size = tree_size(current_node->left), tree_size(current_node->right) + 1;
}

template<typename T>
int Tree<T>::tree_size(Node *current_node){
    if (current_node == nullptr){
        return 0;
    }
    return current_node->size;
}


template<typename T>
int Tree<T>::GetHeight() const{
    return get_height();
}

template<typename T>
int Tree<T>::get_height() const{
    return tree_height(root);
}


template<typename T>
int Tree<T>::GetSize() const {
    return get_size();
}

template<typename T>
int Tree<T>::get_size() const{
    return tree_size(root);
}

//Constr
template<typename T>
Tree<T>::Tree(std::vector<T> values) {
    for(auto&& value : values) {
        Insert(std::move(value));
    }
}


int main()
{
    Tree<int> tree;
    int N;
    std::cin>>N;
    int k = 0;
    for(int i = 0; i < N; ++i) {
        std::cin>>k;
        tree.Insert(k);
    }
    std::cout<<std::endl;
    int size = tree.GetHeight();
    std::cout<<size;
    std::cout<<std::endl;
    tree.PrintPostOrder();
    //7 10 2 6 1 9 4 5 8 3
    std::cout<<std::endl;
    return 0;
}
