#ifndef TREE_HPP
# define TREE_HPP

# include "Pair.hpp"
# include <cstdlib>

namespace ft
{

    typedef size_t      size_type;

    template<class T>
    struct TreeNode
    {
        typedef T           value_type;
        
        value_type      value;
        TreeNode        *left;
        TreeNode        *right;
        TreeNode        *parent;
        size_type       height;
        bool            end;

        TreeNode(T val, bool isEnd = false)
        {
            value = val;
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
            end = isEnd;
        }
    };
    
    template<class T>
    size_type   height(TreeNode<T> *node)
    {
        return node ? node->height : 0;
    }

    template<class T>
    int     bfactor(TreeNode<T> *node)
    {
        return height(node->right) - height(node->left); 
    }

    template<class T>
    void    fixHeight(TreeNode<T> *node)
    {
        size_type   hl = height(node->left);
        size_type   hr = height(node->right);
        node->height = (hl < hr ? hl : hr) + 1;
    }

    template<class T>
    TreeNode<T>    *rotateRight(TreeNode<T> *node)
    {
        TreeNode<T> *q = node->left;
        node->left = q->right;
        q->right = node;
        fixHeight(node);
        fixHeight(q);

        return q;
    }

    template<class T>
    TreeNode<T>    *rotateLeft(TreeNode<T> *node)
    {
        TreeNode<T> *p = node->right;
        node->right = p->left;
        p->left = node;
        fixHeight(node);
        fixHeight(p);

        return p;
    }

    template<class T>
    TreeNode<T>    *balance(TreeNode<T> *node)
    {
        fixHeight(node);
        if (bfactor(node) == 2)
        {
            if (bfactor(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (bfactor(node) == -2)
        {
            if (bfactor(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        return node;
    }

    template<class T>
    TreeNode<T>    *insertNode(TreeNode<T> *node, T value)
    {
        if (!node)
            return new TreeNode<T>(value);
        if (value < node->value)
            node->left = insertNode(node->left, value);
        else
            node->right = insertNode(node->right, value);

        return balance(node);
    }
    
    template<class T>
    TreeNode<T>    *findMin(TreeNode<T> *node)
    {
        return (node->left && !node->left->end) ? findMin(node->left) : node;
    }

    template<class T>
    TreeNode<T>    *findMax(TreeNode<T> *node)
    {
        return (node->right && !node->right->end) ? findMax(node->right) : node;
    }

    template<class T>
    TreeNode<T>    *findNode(TreeNode<T> *node)
    {
        if (!node)
            return NULL;
        if (value < node->value)
            node->left = removeNode(node->left, value);
        else if (value > node->value)
            node->right = removeNode(node->right, value);
        else
            return node;
    }

    template<class T>
    TreeNode<T>    *removeMin(TreeNode<T> *node)
    {
        if (node->left == NULL)
            return node->right;
        node->left = removeMin(node->left);

        return balance(node);
    }

    template<class T>
    TreeNode<T>    *removeNode(TreeNode<T> *node, T value)
    {
        if (!node)
            return NULL;
        if (value < node->value)
            node->left = removeNode(node->left, value);
        else if (value > node->value)
            node->right = removeNode(node->right, value);
        else
        {
            TreeNode<T> *left = node->left;
            TreeNode<T> *right = node->right;
            delete  node;
            if (!right)
                return left;
            TreeNode<T> *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return balance(min);
        }

        return balance(node);
    }

    template<class T>
    TreeNode<T>    *findAllParents(TreeNode<T> *node)
    {
        if (node->left)
            node->left->parent = node;
            node->left = findAllParents(node->left);
        if (node->right)
            node->right->parent = node;
            node->right = findAllParents(node->right);
        
        return node;
    }

    template<class T>
    bool    isLeftChild(TreeNode<T> *node)
    {
        return node == node->parent->left; 
    }

    template<class T>
    TreeNode<T>    *treeNextIter(TreeNode<T> *x)
    {
        if (x->right)
            return findMin(x->right);
        while (!isLeftChild(x))
            x = x->parent;
        return x->parent;
    }

    template<class T>
    TreeNode<T>    *treePrevIter(TreeNode<T> *x)
    {
        if (x->left)
            return findMax(x->left);
        while (isLeftChild(x))
            x = x->parent;
        return x->parent;
    }
}

#endif