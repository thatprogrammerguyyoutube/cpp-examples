#pragma once

#include <memory>
#include <optional>
#include <queue>

#ifndef BST_DEFAULT_COPY_MAX_RECURSION_THRESHOLD
#define BST_DEFAULT_COPY_MAX_RECURSION_THRESHOLD 100000
#endif

template<typename Data, typename Comp = std::less<>>
class BinarySearchTree {
    struct Node {
        Data data;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(Data data) : data(std::move(data)) {}

        auto copy() -> Node* {
            auto cpy = new Node(data);
            if (left) {
                cpy->left = left->copy();
            }
            if (right) {
                cpy->right = right->copy();
            }
            return cpy;
        }
    };
public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree& other);

    BinarySearchTree(BinarySearchTree&& other) noexcept;

    auto operator=(BinarySearchTree&& other) noexcept -> BinarySearchTree&;

    auto operator=(const BinarySearchTree& other) -> BinarySearchTree&;

    ~BinarySearchTree();

    [[nodiscard]] auto size() const -> size_t { return count; }

    [[nodiscard]] auto empty() const -> bool { return root == nullptr; }

    template<typename ...Args>
    auto add(Data data, Args ...args) -> BinarySearchTree&;

    auto add(Data data) -> BinarySearchTree&;

    template<typename ...Args>
    [[nodiscard]] auto contains(const Data& data, const Args& ...args) const -> bool;

    [[nodiscard]] auto contains(const Data& data) const -> bool;

    template<typename ...Args>
    auto remove(Data data, Args ...args) -> bool;

    auto remove(const Data& data) -> bool;

    [[nodiscard]] auto copy_recursive() const -> BinarySearchTree {
        auto cpy = BinarySearchTree{};
        if (root != nullptr) {
            cpy.root = root->copy();
        }
        cpy.count = count;
        return cpy;
    }

    [[nodiscard]] auto copy_queue() const -> BinarySearchTree {
        auto cpy = BinarySearchTree{};
        auto queue = std::queue<Node*>{};
        queue.emplace(root);
        while(!queue.empty()) {
            auto* elem = queue.front();

            if (elem) {
                cpy.add(elem->data);
                queue.emplace(elem->left);
                queue.emplace(elem->right);
            }

            queue.pop();
        }
        return cpy;
    }
private:
    Node* root = nullptr;
    Comp cmp = {};
    size_t count = 0;

    auto remove_leaf(Node* parent, Node* child);

    auto remove_swap_with_single_child(Node* node);

    auto remove_swap_with_successor(Node* node);

    auto next_node(Node* cur, const Data& data) const -> Node**;
};

template<typename Data, typename Comp>
BinarySearchTree<Data, Comp>::BinarySearchTree(const BinarySearchTree &other) {
    if (other.root) {
        auto tmp = (other.size() < BST_DEFAULT_COPY_MAX_RECURSION_THRESHOLD) ? other.copy_recursive() : other.copy_queue();
        std::swap(root, tmp.root);
        std::swap(count, tmp.count);
    }
}

template<typename Data, typename Comp>
BinarySearchTree<Data, Comp>::BinarySearchTree(BinarySearchTree &&other) noexcept {
    std::swap(root, other.root);
    std::swap(count, other.count);
}

template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::operator=(BinarySearchTree &&other) noexcept-> BinarySearchTree& {
    std::swap(root, other.root);
    std::swap(count, other.count);
    return *this;
}

template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::operator=(const BinarySearchTree &other) -> BinarySearchTree & {
    auto tmp = BinarySearchTree{other};
    std::swap(tmp.root, root);
    std::swap(tmp.count, count);
    return *this;
}

template<typename Data, typename Comp>
BinarySearchTree<Data, Comp>::~BinarySearchTree() {
    std::queue<Node*> queue;
    queue.emplace(root);
    while (!queue.empty()) {
        decltype(auto) cur = queue.front();
        if (cur) {
            queue.emplace(cur->left);
            queue.emplace(cur->right);
            delete cur;
        }
        queue.pop();
    }
}

template<typename Data, typename Comp>
template<typename... Args>
auto BinarySearchTree<Data, Comp>::add(Data data, Args... args) -> BinarySearchTree & {
    add(data);
    add(args...);
    return *this;
}

template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::add(Data data) -> BinarySearchTree & {
    if (root == nullptr) {
        root = new Node{std::move(data)};
        ++count;
    }
    else {
        auto* ptr = root;
        while (true) {
            decltype(auto) next = next_node(ptr, data);
            if (!next) {
                return *this;
            }

            // Add the data
            if (*next == nullptr) {
                ++count;
                *next = new Node{std::move(data)};
                break;
            }
            ptr = *next;
        }
    }
    return *this;
}

template<typename Data, typename Comp>
template<typename... Args>
auto BinarySearchTree<Data, Comp>::contains(const Data &data, const Args &... args) const -> bool {
    return contains(data) && (... && contains(args));
}

template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::contains(const Data &data) const -> bool {
    auto* ptr = root;
    while (ptr != nullptr) {
        decltype(auto) next = next_node(ptr, data);
        if (!next) {
            return true;
        }
        ptr = *next;
    }
    return false;
}

template<typename Data, typename Comp>
template<typename... Args>
auto BinarySearchTree<Data, Comp>::remove(Data data, Args... args) -> bool {
    return remove(data) | (... | remove(args));
}


template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::remove(const Data &data) -> bool {
    auto* ptr = root;
    decltype(ptr) prev = nullptr;
    while (ptr != nullptr) {
        decltype(auto) next = next_node(ptr, data);

        // Haven't found the node to delete yet
        if (next) {
            prev = ptr;
            ptr = *next;
            continue;
        }

        // ptr is for the node to be deleted
        auto numChildren = (ptr->left != nullptr) + (ptr->right != nullptr);
        if (numChildren == 0) {
            remove_leaf(prev, ptr);
        }
        else if (numChildren == 1) {
            remove_swap_with_single_child(ptr);
        }
        else if (numChildren == 2) {
            remove_swap_with_successor(ptr);
        }
        --count;
        return true;
    }

    // Indicate that we did not remove anything
    return false;
}


template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::remove_leaf(Node *parent, Node *child) {
    if (parent == nullptr) {
        delete root;
        root = nullptr;
    }
    else if (parent->left == child) {
        delete parent->left;
        parent->left = nullptr;
    }
    else {
        delete parent->right;
        parent->right = nullptr;
    }
}

template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::remove_swap_with_single_child(Node *node) {
    if (node->left) {
        auto child = node->left;
        std::swap(node->data, child->data);
        std::swap(node->right, child->right);
        node->left = child->left;
        child->left = nullptr;
        delete child;
    }
    else {
        auto child = node->right;
        std::swap(node->data, child->data);
        std::swap(node->left, child->left);
        node->right = child->right;
        child->right = nullptr;
        delete child;
    }
}


template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::remove_swap_with_successor(Node *node) {
    decltype(auto) prev = node;
    decltype(auto) cur = node->right;

    while (cur != nullptr && cur->left != nullptr) {
        prev = cur;
        cur = cur->left;
    }
    std::swap(cur->data, node->data);

    decltype(auto) old = prev->left;

    if (prev == node) {
        old = prev->right;
        prev->right = cur->right;
    }
    else {
        prev->left = cur->right;
    }

    cur->right = nullptr;

    delete old;
}


template<typename Data, typename Comp>
auto BinarySearchTree<Data, Comp>::next_node(Node *cur, const Data &data) const -> Node ** {
    // Go left
    if (cmp(data, cur->data)) {
        return &cur->left;
    }
        // Go right
    else if (cmp(cur->data, data)) {
        return &cur->right;
    }
        // We're at the node already
    else {
        return nullptr;
    }
}
