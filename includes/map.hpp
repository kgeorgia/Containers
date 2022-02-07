#ifndef FT_MAP_HPP
# define FT_MAP_HPP

# include <memory>
# include "Utils/BidirectionalTreeIterator.hpp"

namespace ft
{
    template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< pair<const Key, T> >
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

            typedef ft::BidirectionalTreeIterator<T>            iterator;
            typedef ft::RevBidirectionalTreeIterator<T>         reverse_iterator;
            typedef ft::BidirectionalTreeIterator<const T>      const_iterator;
            typedef ft::RevBidirectionalTreeIterator<const T>   const_reverse_iterator;

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
            template< class InputIt >
            map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc() );
            map( const map<Key, T> &other );

            ~map() {}

            map &operator=(const map<Key, T> &other);

            //Iterators
            iterator                begin() { return iterator(findMin(this->root)); }
            const_iterator          begin() { return const_iterator(findMin(this->root)); }
            iterator                end() { return iterator(this->rightEnd); }
            const_iterator          end() { return const_iterator(this->rightEnd); }

            reverse_iterator        rbegin() { return reverse_iterator(findMax(this->root)); }
            const_reverse_iterator  rbegin() { return const_reverse_iterator(findMax(this->root))}
            reverse_iterator        rend() { return reverse_iterator(this->leftEnd); }
            const_reverse_iterator  rend() { return const_reverse_iterator(this->leftEnd); }

            //Capacity

            bool        empty() const { return (this->length == 0); }
            size_type   size() const { return this->length; }
            size_type   max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(TreeNode< pair<Key, T> >))}

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
					this->insert(*first);
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
    }

    template <class Key, class T, class Compare, class Alloc >
    map<Key, T, Compare, Alloc>::map(const map<Key, T> &other)
    {
	    this->alloc = other.alloc;
        this->comp = other.alloc;
        this->insert(other.begin(), other.end())
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
        this->insert(other.begin(), other.end())
    }

    template <class Key, class T, class Compare, class Alloc >
    typename map<Key, T, Compare, Alloc>::mapped_type &map<Key, T, Compare, Alloc>::operator[](const key_type& k)
    {
	    iterator tmp = this->find(k);
	    if (tmp != this->end())
	    {
		    return tmp->second;
	    }
	    return (this->insert(std::make_pair(k, mapped_type())).first->second);
    }

    template <class Key, class T, class Compare, class Alloc >
    std::pair<typename map<Key, T, Compare, Alloc>::iterator, bool> map<Key, T, Compare, Alloc>::insert(const value_type &value)
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
            if ((temp != this->end())
		        return (std::make_pair(temp, false));
            minNode = findMin(this->root);
            maxNode = findMax(this->root);
            minNode->left = NULL;
            maxNode->right = NULL;
        }
	    this->_length++;
        this->root = insertNode(this->root, value);
        minNode = findMin(this->root);
        maxNode = findMax(this->root);
        minNode->left = this->leftEnd;
        maxNode->right = this->rightEnd;
	    return (std::make_pair(iterator(this->find(value.first)), true));
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
        this->_length--;
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
	    this->erase(this->begin(), this->end());
    }



}

#endif