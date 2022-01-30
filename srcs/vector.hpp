#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include "Utils/RandomAccessIterator.hpp"

namespace ft {

    template<class T, class Alloc = std::allocator<T> >
    class vector {
        public:
            typedef T                       value_type;
            typedef Allocator               allocator_type;
            typedef size_t                  size_type;
            typedef ptrdiff_t               difference_type;
            typedef value_type&             reference;
            typedef const value_type&       const_reference;
            typedef value_type*             pointer;
            typedef const value_type*       const_pointer;
            typedef RandomAccessIterator<value_type, pointer, reference>                iterator;
            typedef RandomAccessIterator<value_type, const_pointer, const_reference>    const_iterator;
            


        private:
            pointer             ptr;
            allocator_type      alloc;
            size_type           len_size;
            size_type           capacity;

        public:
            explicit    vector(const allocator_type &alloc = allocator_type());
            explicit    vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
            vector(const vector &x);
            ~vector();

            vector &operator=(const vector &x);

            // --- Capacity ---

            size_type   size() const { return this->len_size; }
            size_type   max_size() const { return ( std::numeric_limits<size_type>::max() / (sizeof(value_type)));}
            size_type   capacity() const { return this->capacity; }
            bool        empty() const { return !this->len_size; }

            void        resise(size_type n, value_type val = value_type());
            void        reserve(size_type n);

            // --- Element access ---

            reference           operator[](size_type n) { return this->ptr[n]; }
            const_reference     operator[](size_type n) { return this->ptr[n]; }
            reference           front() { return this->ptr[0]; }
            const_reference     front() { return this->ptr[0]; }
            reference           back() { return this->ptr[this->len_size - 1]; }
            const_reference     back() { return this->ptr[this->len_size - 1]; }
            reference           at(size_type n)
            {
                if (n < this->len_size)
                    return this->ptr[n];
                return NULL;
            }

            const_reference     at(size_type n)
            {
                if (n < this->len_size)
                    return this->ptr[n];
                return NULL;
            }


            // --- Modifiers ---

            void                assign(size_type n, const value_type &val);
            void                push_back(const value_type &val);
            void                pop_back();
            void                swap(vector &x);
            void                clear();
    };

    template< typename T, typename Alloc >
    vector<T, Alloc>::vector(const allocator_type &alloc = allocator_type()):
    ptr(NULL), alloc(alloc), len_size(0), capacity(0) {}

    template< typename T, typename Alloc >
    vector<T, Alloc>::vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):
    alloc(alloc), len_size(n), capacity(n) { this->ptr = new value_type[n](); }

    template< typename T, typename Alloc >
    vector<T, Alloc>::vector(const vector &x):
    ptr(x.ptr), alloc(x.alloc), len_size(x.len_size), capacity(x.capacity) { *this = x; }

    template< typename T, typename Alloc >
    vector<T, Alloc>::~vector()
    {
        if (this->ptr)
        {
            delete[] this->ptr;
            this->ptr = NULL;
        }
    }

    template< typename T, typename Alloc >
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc> &x)
    {
        if (this->ptr)
        {
            delete[] this->ptr;
            this->ptr = NULL;
        }
        this->ptr = new value_type[x.capacity]();
        this->capacity = x.capacity;
        this->len_size = x.len_size;
        
    }
}

#endif