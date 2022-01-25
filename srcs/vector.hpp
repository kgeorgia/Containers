#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>

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

            // Capacity

            size_type   size() const { return this->len_size; }
            size_type   max_size() const { return ( std::numeric_limits<size_type>::max() / (sizeof(value_type)));}
            size_type   capacity() const { return this->capacity; }
            bool        empty() const { return !this->len_size; }

            void        resise(size_type n, value_type val = value_type());
            void        reserve(size_type n);

            //Element access

            reference           operator[](size_type n) { return this->ptr[n]; }
            const_reference     operator[](size_type n) { return this->ptr[n]; }
            reference           front() { return this->ptr[0]; }
            const_reference     front() { return this->ptr[0]; }
            reference           back() { return this->ptr[this->len_size - 1]; }
            const_reference     back() { return this->ptr[this->len_size - 1]; }
            reference           at(size_type n) {
                if (n < this->len_size)
                    return this->ptr[n];
                return NULL;
            }

            const_reference     at(size_type n) {
                if (n < this->len_size)
                    return this->ptr[n];
                return NULL;
            }


            //Modifiers

            void                assign(size_type n, const value_type &val);
            void                push_back(const value_type &val);
            void                pop_back();
            void                swap(vector &x);
            void                clear();
    };
}

#endif