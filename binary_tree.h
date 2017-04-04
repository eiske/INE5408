// Copyright [2016] <Vinicius Eiske>
#include "./array_list.h"

namespace structures {

/**
 * @brief      Class for binary tree.
 *
 * @tparam     T     { description }
 */
template<typename T>
class BinaryTree {
 public:
    BinaryTree() {
        root = nullptr;
        size_ = 0;
    }

    /**
     * @brief      Destroys the binary tree
     */
    ~BinaryTree() {}

    /**
     * @brief      Insert data to Tree
     *
     * @param[in]  data  The data
     */
    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        size_++;
    }

    /**
     * @brief      Remove data from Tree
     *
     * @param[in]  data  The data
     */
    void remove(const T& data) {
        bool teste;
        if (empty()) {
            printf("Arvore vazia.");
        } else {
            teste = root->remove(data);
        }
        if (teste == true)
            size_--;
    }

    /**
     * @brief      Search data from Tree
     *
     * @param[in]  data  The data
     *
     * @return     bool
     */
    bool contains(const T& data) const {
        if (empty())
            return false;
        else
            return root->contains(data);
    }
    /**
     * @brief      Verify if empty
     *
     * @return     bool
     */
    bool empty() const {
        if (size_ == 0)
            return true;
        else
            return false;
    }
    /**
     * @brief      Return size
     *
     * @return     size
     */
    std::size_t size() const {
        return size_;
    }
    /**
     * @brief      pre order
     *
     * @return     { description_of_the_return_value }
     */
    ArrayList<T> pre_order() const {
        structures::ArrayList<T> list{};
        if (empty()) {
            printf("Arvore vazia.");
        } else {
            root->pre_order(list);
        }
        return list;
    }
    /**
     * @brief      in order
     *
     * @return     { description_of_the_return_value }
     */
    ArrayList<T> in_order() const {
        structures::ArrayList<T> list{};
        if (empty()) {
            printf("Arvore vazia.");
        } else {
            root->in_order(list);
        }
        return list;
    }
    /**
     * @brief      post oreder
     *
     * @return     { description_of_the_return_value }
     */
    ArrayList<T> post_order() const {
        structures::ArrayList<T> list{};
        if (empty()) {
            printf("Arvore vazia.");
        } else {
            root->post_order(list);
        }
        return list;
    }

 private:
    struct Node {
        explicit Node(const T& data_):
            data{data_}
        {}

        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        /**
         * @brief      Insert data to node
         *
         * @param[in]  data_  The data
         */
        void insert(const T& data_) {
            if (data_ > data) {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            } else {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            }
        }
        /**
         * @brief      Remove data from node
         *
         * @param[in]  data_  The data
         *
         * @return     bool
         */
        bool remove(const T& data_) {
            if (data_ == data) {
                if (right != nullptr && left != nullptr) {
                    auto aux = minValue(right);
                    data = aux->data;
                    return right->remove(data);
                } else {
                    if (right != nullptr) {
                        data = right->data;
                        return right->remove(data);
                    } else if (left != nullptr) {
                        data = left->data;
                        return left->remove(data);
                    } else {
                        delete this;
                        return true;
                    }
                }
            } else if (data_ > data) {
                if (right != nullptr) {
                    return right->remove(data_);
                }
            } else {
                if (left != nullptr) {
                    return left->remove(data_);
                }
            }
            return false;
        }
        /**
         * @brief      Contains in node
         *
         * @param[in]  data_  The data
         *
         * @return     bool
         */
        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ > data) {
                if (right != nullptr)
                    return right->contains(data_);
            } else {
                if (left != nullptr)
                    return left->contains(data_);
            }
            return false;
        }
        /**
         * @brief      pre order
         *
         * @param      v     { parameter_description }
         */
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }
        /**
         * @brief      in order
         *
         * @param      v     { parameter_description }
         */
        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }
        /**
         * @brief      post order
         *
         * @param      v     { parameter_description }
         */
        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }
         /**
         * @brief      Minimun value
         *
         * @return     { description_of_the_return_value }
         */
        Node* minValue(Node* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures
