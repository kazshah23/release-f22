/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node *& answer = find(root, key);
    return answer -> value;

}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == nullptr) {
        return subtree;
    }
    if (subtree -> key == key) {
        return subtree;
    } else if (subtree -> key > key) {
        return find(subtree -> left, key);
    } else {
        return find(subtree -> right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
    
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    BST<K, V>::Node*& node = find(subtree, key);
    if (!node) node = new Node(key, value);

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K firstK = first -> key;
    K secondK = second -> key;
    V firstV = first -> value;
    V secondV = second -> value;

    first -> key = secondK;
    second -> key = firstK;
    first -> value = secondV;
    second -> value = firstV;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    BST<K, V>::Node*& node = find(subtree, key);
    BST<K, V>::Node*& tmp = find(subtree, key);
    if (node -> left == nullptr && node -> right == nullptr) {
        node = nullptr;
        delete node;
    } else if (node -> left == nullptr && node -> right != nullptr) { 
        Node* add = node -> right;
        delete node;
        node = add;
        return;
    } else if (node -> right == nullptr && node -> left != nullptr) {
        Node* add = node -> left;
        delete node;
        node = add;
        return;
    } else { 
        Node* toonlink = node -> left;
        while(toonlink -> right) {
            toonlink = toonlink -> right;
        }
        swap(node, toonlink);
        remove(node ->left, toonlink->key);
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> ans;
    for (const auto& nodes : inList) ans.insert(nodes.first, nodes.second);
    return ans;

}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> ans(inList.size());
    std::sort(inList.begin(), inList.end());
    do {
        BST<K,V> tree;
        for (const auto &pair : inList) {
            tree.insert(pair.first, pair.second);
        }
        ++ans[tree.height()];
    } while (std::next_permutation(inList.begin(), inList.end()));

    return ans;
}