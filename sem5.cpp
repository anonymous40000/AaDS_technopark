#include <iostream>

template<typename T, typename C>
class BinaryTree {
public:
    BinaryTree(const C& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();

    void Add(const T& key);
    bool Has(const T& key);

    void Traverse(void (*visit)(const T&)) const { traverse(root, visit); };
private:
    struct Node {
        Node* Left;
        Node* Right;
        T key;
        Node(const T& key) : Left(nullptr), Right(nullptr), key(key) {}
    };
    Node* root;
    C cmp;

    void deleteNode(Node* node);
    void add(Node*& node, const T& key);
    bool has(Node* node, const T& key) const;
    void traverse(Node* node, void (*visit)(const T&)) const;
};


template<typename T, typename C>
BinaryTree<T, C>::~BinaryTree() 
{
    deleteNode(root);
}

template<typename T, typename C>
void BinaryTree<T, C>::deleteNode(Node* node)
{
    if (node == nullptr) {
        return;
    }
    deleteNode(node->Left);
    deleteNode(node->Right);
    delete node;
}

template<typename T, typename C>
void BinaryTree<T, C>::Add(const T& key) 
{
    add(root, key);
}

template<typename T, typename C>
void BinaryTree<T, C>::add(Node*& node, const T& key) 
{
    if (node == nullptr) {
        node = new Node(key);
        return;
    }

    if (cmp(key, node->key)) {
        add(node->Left, key);
    } else {
        add(node->Right, key);
    }
}

template<typename T, typename C>
bool BinaryTree<T, C>::Has(const T& key) 
{
    return has(root, key);
}

template<typename T, typename C>
bool BinaryTree<T, C>::has(Node* node, const T& key) const
{
    if (node == nullptr) {
        return false;
    }

    if (node->Key == key) {
        return true;
    }

    if (cmp(key, node->Key)) {
        return has(node->Left, key);
    }

    return (node->Right, key);
}

template<typename T, typename C>
void BinaryTree<T, C>::traverse(Node* node, void (*visit)(const T&)) const
{
    if (node == nullptr) {
        return;
    }
    traverse(node->Left, visit);
    visit(node->key);
    traverse(node->Right, visit);
}


struct IntCmp {
    bool operator()(int l, int r) const { return l < r; }
};

int main()
{
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);
    tree.Add(30);
    tree.Add(10);
    tree.Add(40);
    tree.Add(5);
    tree.Add(15);
    tree.Add(35);
    tree.Add(50);
    tree.Add(6);
    tree.Add(14);

    tree.Traverse([](const int& key) {std::cout << key << " ";});
}