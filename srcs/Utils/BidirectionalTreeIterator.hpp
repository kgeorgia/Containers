#ifndef BIDIRECTIONAL_TREE_ITERATOR
# define BIDIRECTIONAL_TREE_ITERATOR

# include "Tree.hpp"

namespace ft
{

    template<class T>
    class BidirectionalTreeIterator
    {
        public:
            typedef T               value_type;
            typedef TreeNode<T>     *node_ptr;
            typedef value_type      &reference;
            typedef value_type      *pointer;

        private:
            node_ptr    ptr;

        public:
            BidirectionalTreeIterator(): ptr() {}
            BidirectionalTreeIterator(node_ptr p): ptr(p) {}
            BidirectionalTreeIterator(const BidirectionalTreeIterator &other): ptr(other.ptr) {}
            ~BidirectionalTreeIterator() {}

            const BidirectionalTreeIterator     &operator=(const BidirectionalTreeIterator &other)
            {
                this->ptr = other.ptr;
                return *this;
            }

            reference   operator*() const
            {
                return this->value;
            }

            pointer     operator->() const
            {
                return &(ptr->value);
            }

            BidirectionalTreeIterator   &operator++()
            {
                this->ptr = treeNextIter<T>(this->ptr);
                return *this;
            }

            BidirectionalTreeIterator   operator++(int)
            {
                BidirectionalTreeIterator   temp(*this);

                ++(*this);
                return temp;
            }

            BidirectionalTreeIterator   &operator--()
            {
                this->ptr = treePrevIter<T>(this->ptr);
                return *this;
            }

            BidirectionalTreeIterator   operator--(int)
            {
                BidirectionalTreeIterator   temp(*this);

                --(*this);
                return temp;
            }

            bool operator==(const BidirectionalTreeIterator &other)
            {
                return this->ptr == other.ptr;
            }

            bool operator!=(const BidirectionalTreeIterator &other)
            {
                return this->ptr != other.ptr;
            }
    };

    template<class T>
    class RevBidirectionalTreeIterator
    {
        public:
            typedef T               value_type;
            typedef TreeNode<T>     *node_ptr;
            typedef value_type      &reference;
            typedef value_type      *pointer;

        private:
            node_ptr    ptr;

        public:
            RevBidirectionalTreeIterator(): ptr() {}
            RevBidirectionalTreeIterator(node_ptr p): ptr(p) {}
            RevBidirectionalTreeIterator(const RevBidirectionalTreeIterator &other): ptr(other.ptr) {}
            ~RevBidirectionalTreeIterator() {}

            const RevBidirectionalTreeIterator     &operator=(const RevBidirectionalTreeIterator &other)
            {
                this->ptr = other.ptr;
                return *this;
            }

            reference   operator*() const
            {
                return this->value;
            }

            pointer     operator->() const
            {
                return &(ptr->value);
            }

            RevBidirectionalTreeIterator   &operator++()
            {
                this->ptr = treePrevIter<T>(this->ptr);
                return *this;
            }

            RevBidirectionalTreeIterator   operator++(int)
            {
                RevBidirectionalTreeIterator   temp(*this);

                ++(*this);
                return temp;
            }

            RevBidirectionalTreeIterator   &operator--()
            {
                this->ptr = treeNextIter<T>(this->ptr);
                return *this;
            }

            RevBidirectionalTreeIterator   operator--(int)
            {
                RevBidirectionalTreeIterator   temp(*this);

                --(*this);
                return temp;
            }

            bool operator==(const RevBidirectionalTreeIterator &other)
            {
                return this->ptr == other.ptr;
            }

            bool operator!=(const RevBidirectionalTreeIterator &other)
            {
                return this->ptr != other.ptr;
            }
    };

}

#endif