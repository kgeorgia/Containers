#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <memory>
# include "Utils/BidirectionalTreeIterator.hpp"

namespace ft
{

    template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                         key_type;
            typedef T                           mapped_type;
            typedef pair<const Key, T>          value_type;
            typedef Alloc                       allocator_type;
            typedef Compare                     key_compare;
            typedef T&                          reference;
            typedef const T&                    const_reference;
            typedef T*                          pointer;
            typedef const T*                    const_pointer;
            typedef std::size_t                 size_type;
            typedef std::ptrdiff_t              difference_type;
            typedef TreeNode<value_type>*       node;

            typedef ft::BidirectionalTreeIterator<TreeNode<value_type> >            iterator;
            typedef ft::RevBidirectionalTreeIterator<TreeNode<value_type> >         reverse_iterator;
            typedef ft::BidirectionalTreeIterator<const TreeNode<value_type> >      const_iterator;
            typedef ft::RevBidirectionalTreeIterator<const TreeNode<value_type> >   const_reverse_iterator;

            class value_compare
            {
                friend class map;

                protected:
                    Compare     comp;
                    value_compare(Compare c) : comp(c) {}

                public:
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;

                    bool operator() (const value_type &x, const value_type &y) const
                    {
                        return comp(x.first, y.first);
                    }
            };

        private:
            allocator_type      alloc;
            key_compare         comp;
            node                root;
            node                leftEnd;
            node                rightEnd;
            size_type           length;

        public:
            explicit map( const Compare& comp = Compare(), const Alloc& alloc = Alloc() );
            map( const map<Key, T> &other );

            template< class InputIt >
            map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc() )
            {
                this->alloc = alloc;
                this->comp = comp;
                this->root = NULL;
                this->leftEnd = NULL;
                this->rightEnd = NULL;
                this->length = 0;
                this->insert(first, last);
            }

            ~map();

            map &operator=(const map<Key, T> &other);

            //Iterators
            iterator                begin() { return iterator(findMin(this->root)); }
            const_iterator          begin() const { return const_iterator(findMin(this->root)); }
            iterator                end() { return iterator(this->rightEnd); }
            const_iterator          end() const { return const_iterator(this->rightEnd); }

            reverse_iterator        rbegin() { return reverse_iterator(findMax(this->root)); }
            const_reverse_iterator  rbegin() const { return const_reverse_iterator(findMax(this->root)); }
            reverse_iterator        rend() { return reverse_iterator(this->leftEnd); }
            const_reverse_iterator  rend() const { return const_reverse_iterator(this->leftEnd); }

            //Capacity

            bool        empty() const { return (this->length == 0); }
            size_type   size() const { return this->length; }
            size_type   max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(TreeNode< pair<Key, T> >)); }

            //Element access
			mapped_type &operator[](const key_type& k);
			
			//Modifiers
			pair<iterator, bool>    insert(const value_type &value);
			iterator                insert(iterator position, const value_type &value);
			void                    erase(iterator position);
			size_type               erase(const key_type &value);
			void                    erase(iterator first, iterator last);
			void                    swap(map &x);
			void                    clear();

            template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
                    value_type  tmp = *first;
					this->insert(tmp);
					++first;
				}
			}

			//Observers
			key_compare         key_comp(void) const	{ return (comp);}
			value_compare       value_comp(void) const	{ return (value_compare(this->comp));}

			//Operations
			iterator            find(const key_type &value);
			const_iterator      find(const key_type &value) const;
			size_type           count(const key_type &value) const;
			iterator            lower_bound(const key_type &key);
			const_iterator      lower_bound(const key_type &key) const;
			iterator            upper_bound(const key_type &key);
			const_iterator      upper_bound(const key_type &key) const;

			pair<const_iterator, const_iterator> equal_range(const key_type &k) const
			{
				return (pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
			}
			pair<iterator, iterator> equal_range(const key_type &k)
			{
				return (pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
			}

    };

    template<class Key, class T, class Compare, class Alloc >
    map<Key, T, Compare, Alloc>::map(const Compare& comp, const Alloc& alloc)
    {
        this->alloc = alloc;
        this->comp = comp;
        this->root = NULL;
        this->leftEnd = NULL;
        this->rightEnd = NULL;
        this->length = 0;
    }

    template <class Key, class T, class Compare, class Alloc >
    map<Key, T, Compare, Alloc>::map(const map<Key, T> &other)
    {
	    this->alloc = other.alloc;
        this->comp = other.comp;
        this->root = NULL;
        this->leftEnd = NULL;
        this->rightEnd = NULL;
        this->length = 0;
        this->insert(other.begin(), other.end());
    }

    template <class Key, class T, class Compare, class Alloc >
    map<Key, T, Compare, Alloc>::~map()
    {
        this->clear();
    }

    template <class Key, class T, class Compare, class Alloc >
    map<Key, T, Compare, Alloc> &map<Key, T, Compare, Alloc>::operator=(const map<Key, T> &other)
    {
        if (this->root)
            this->clear();
        this->insert(other.begin(), other.end());
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::mapped_type &map<Key, T, Compare, Alloc>::operator[](const key_type& k)
    {
	    iterator tmp = this->find(k);
	    if (tmp != this->end())
	    {
		    return tmp->second;
	    }
	    return (this->insert(make_pair(k, mapped_type())).first->second);
    }

    template <class Key, class T, class Compare, class Alloc >
    pair<typename map<Key, T, Compare, Alloc>::iterator, bool> map<Key, T, Compare, Alloc>::insert(const value_type &value)
    {
        node    minNode;
        node    maxNode;

        if (this->root == NULL)
        {
            this->leftEnd = new TreeNode<value_type>(value_type(), true);
            this->rightEnd = new TreeNode<value_type>(value_type(), true);
        }
        else
        {
            iterator temp = this->find(value.first);
            if (temp != this->end())
		        return (make_pair(temp, false));
            minNode = findMin(this->root);
            maxNode = findMax(this->root);
            minNode->left = NULL;
            maxNode->right = NULL;
        }
	    this->length++;
        this->root = insertNode(this->root, value);
        this->root = findAllParents(this->root);
        minNode = findMin(this->root);
        maxNode = findMax(this->root);
        minNode->left = this->leftEnd;
        maxNode->right = this->rightEnd;
	    return (make_pair(iterator(this->find(value.first)), true));
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::iterator  map<Key, T, Compare, Alloc>::insert(iterator position, const value_type &value)
    {
	    (void)position;
        this->insert(value);
        return this->find(value.first);
    }

    template <class Key, class T, class Compare, class Alloc >
    void map<Key, T, Compare, Alloc>::erase(iterator position)
    {
        if (this->root == NULL)
            return;
        node    minNode = findMin(this->root);
        node    maxNode = findMax(this->root);
        minNode->left = NULL;
        maxNode->right = NULL;
	    this->root = removeNode(this->root, *position);
        this->length--;
        this->root = findAllParents(this->root);
        minNode = findMin(this->root);
        maxNode = findMax(this->root);
        minNode->left = this->leftEnd;
        maxNode->right = this->rightEnd;
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::erase(const key_type &value)
    {
	    size_type i = 0;
	    iterator item;
	    while ((item = this->find(value)) != this->end())
	    {
		    this->erase(item);
		    ++i;
	    }
	    return (i);
    }

    template <class Key, class T, class Compare, class Alloc >
    void map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
    {
	    while (first != last)
		    this->erase(first++);
    }

    template <class Key, class T, class Compare, class Alloc >
    void map<Key, T, Compare, Alloc>::swap(map &x)
    {
	    map<Key, T, Compare, Alloc> temp = *this;
	    *this = x;
	    x = temp;
    }

    template <class Key, class T, class Compare, class Alloc >
    void map<Key, T, Compare, Alloc>::clear()
    {
        if (this->root)
	        this->erase(this->begin(), this->end());
        if (this->leftEnd)
            delete this->leftEnd;
        if (this->rightEnd)
            delete this->rightEnd;
        this->root = NULL;
        this->leftEnd = NULL;
        this->rightEnd = NULL;
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::find(const key_type &value)
    {
        node    tempNode = this->root;

	    while (tempNode != NULL)
        {
            if (value < tempNode->value.first)
                tempNode = tempNode->left;
            else if (value > tempNode->value.first)
                tempNode = tempNode->right;
            else
                return iterator(tempNode);
        }
	    return (this->end());
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::find(const key_type &value) const
    {
        node    tempNode = this->root;

	    while (tempNode != NULL)
        {
            if (value < tempNode->value.first)
                tempNode = tempNode->left;
            else if (value > tempNode->value.first)
                tempNode = tempNode->right;
            else
                return const_iterator(tempNode);
        }
	    return (this->end());
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::count(const key_type &value) const
    {
	    const_iterator it_begin = this->begin();
	    const_iterator it_end = this->end();

	    while (it_begin != it_end)
	    {
		    if ((*it_begin).first == value)
			    return (1);
		    ++it_begin;
	    }
	    return (0);
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &key)
    {
	    iterator it_begin = this->begin();
	    iterator it_end = this->end();
	    while (it_begin != it_end)
	    {
		    if (this->_comp((*it_begin).first, key) <= 0)
			    return (it_begin);
		    ++it_begin;
	    }
	    return (it_end);
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &key) const
    {
	    const_iterator it_begin = this->begin();
	    const_iterator it_end = this->end();
	    while (it_begin != it_end)
	    {
		    if (this->_comp((*it_begin).first, key) <= 0)
			    return (it_begin);
		    ++it_begin;
	    }
	    return (it_end);
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &key)
    {
	    iterator it_begin = this->begin();
	    iterator it_end = this->end();
	    while (it_begin != it_end)
	    {
		    if ((*it_begin).first != key && this->_comp((*it_begin).first, key) <= 0)
			    return (it_begin);
		    ++it_begin;
	    }
	    return (it_end);
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &key) const
    {
	    const_iterator it_begin = this->begin();
	    const_iterator it_end = this->end();
	    while (it_begin != it_end)
	    {
		    if ((*it_begin).first != key && this->_comp((*it_begin).first, key) <= 0)
			    return (it_begin);
		    ++it_begin;
	    }
	    return (it_end);
    }

}

#endif