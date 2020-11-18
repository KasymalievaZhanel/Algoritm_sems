#include <iostream>
#include <vector>


template<typename T>
class Tree{
    public:
    Tree(std::vector<T> values);
        struct Node{
            Node* left;
            Node* right;
            T value;
        };
        void Insert(T value);
        void PrintInOrder() const;
        void PrintPostOrder() const;
    private:
        Node* root{nullptr};
        static void insert(Node *& current_node, Node * new_node);
        void printinorder_recursive(Node* node) const;
        void printpostorder_recursive(Node * node) const;

};

template<typename T>
void Tree<T>::PrintInOrder() const{
    printinorder_recursive(root);
}

template<typename T>
void Tree<T>::printinorder_recursive(Node *node) const{
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
void Tree<T>::printpostorder_recursive(Node * node) const{
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
    insert(root, new_node);
}

template<typename T>
void Tree<T>::insert(Node *& current_node, Node * new_node) {
    if(current_node == nullptr){
        current_node = new_node;
        return;
    }
    if (new_node->value < current_node->value){
        insert(current_node->left, new_node);
    } else {
        insert(current_node->right, new_node);
    }
}


template<typename T>
Tree<T>::Tree(std::vector<T> values) {
    for(auto&& value : values) {
        Insert(std::move(value));
    }
}

int main()
{
    Tree<int> tree{{1, 2, 3, 4, 5}};
    tree.PrintInOrder();
}
