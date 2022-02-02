#ifndef TREE_HPP
# define TREE_HPP

namespace ft
{

    template<class T>
    class treeNode
    {
        public:
            typedef T           value_type;
            typedef treeNode<T> *nodePtr;
            typedef size_t      size_type;

        private:
            value_type  value;
            nodePtr     left;
            nodePtr     right;
            size_type      height;

        public:
            treeNode(value_type &val = value_type()):
            value(val), left(NULL), right(NULL), height(0) {}

            treeNode(const treeNode &other):
            value(other.value), left(other.left), right(other.right), height(other.height) {}

            ~treeNode() {}

            treeNode    &operator=(const treeNode &other)
            {
                this->value = other.value;
                this->left = other.left;
                this->right = other.right;
                this->height = other.height;

                return *this;
            }
    };


    class Tree 
    {

    };

}

#endif