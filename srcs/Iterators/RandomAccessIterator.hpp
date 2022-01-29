#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include <memory>

template< typename T, typename Reference, typename Pointer >
class RandomAccessIterator
{
    public:
        typedef Pointer                                         pointer;
        typedef Reference                                       reference;
        typedef size_t                                          size_type;
        typedef RandomAccessIterator<T, Reference, Pointer>     iterator;

    private:
        pointer     ptr;

    public:
        RandomAccessIterator() { this->ptr = NULL; }
        RandomAccessIterator(const pointer ptr) { this->ptr = ptr; }
        RandomAccessIterator(const iterator &it) { *this = it; }
        ~RandomAccessIterator() {}

        iterator    &operator=(const iterator &other)
        {
            this->ptr = other.ptr;
            return *this;
        }

        iterator    operator++(int)
        {
            iterator temp = *this;
            this->ptr++;
            return temp;
        }

        iterator    &operator++()
        {
            this->ptr++;
            return *this;
        }

        iterator    operator--(int)
        {
            iterator temp = *this;
            this->ptr--;
            return temp;
        }

        iterator    &operator--()
        {
            this->ptr--;
            return *this;
        }

        iterator    operator+(size_type n)
        {
            this->ptr = this->ptr + n;
            return this;
        }

        iterator    operator-(size_type n)
        {
            this->ptr = this->ptr - n;
            return this;
        }

        size_type   operator-(iterator it)
        {
            return (this->ptr - it.ptr);
        }

        iterator    &operator+=(size_type n)
        {
            this->ptr = this->ptr + n;
            return *this;
        }

        iterator    &operator-=(size_type n)
        {
            this->ptr = this->ptr - n;
            return *this;
        }

        reference   operator*() { return *this->ptr; }
        pointer     operator->() { return this->ptr; }
        reference   operator[](size_type n) { return *(this->ptr + n); }

        bool        operator==(const iterator &other) const { return (this->ptr == other.ptr); }
        bool        operator!=(const iterator &other) const { return (this->ptr != other.ptr); }
};


template< typename T, typename Reference, typename Pointer >
class ReverseRandomAccessIterator
{
    public:
        typedef Pointer                                         pointer;
        typedef Reference                                       reference;
        typedef size_t                                          size_type;
        typedef RandomAccessIterator<T, Reference, Pointer>     iterator;

    private:
        pointer     ptr;

    public:
        RandomAccessIterator() { this->ptr = NULL; }
        RandomAccessIterator(const pointer ptr) { this->ptr = ptr; }
        RandomAccessIterator(const iterator &it) { *this = it; }
        ~RandomAccessIterator() {}

        iterator    &operator=(const iterator &other)
        {
            this->ptr = other.ptr;
            return *this;
        }

        iterator    operator++(int)
        {
            iterator temp = *this;
            this->ptr--;
            return temp;
        }

        iterator    &operator++()
        {
            this->ptr--;
            return *this;
        }

        iterator    operator--(int)
        {
            iterator temp = *this;
            this->ptr++;
            return temp;
        }

        iterator    &operator--()
        {
            this->ptr++;
            return *this;
        }

        iterator    operator+(size_type n)
        {
            this->ptr = this->ptr - n;
            return this;
        }

        iterator    operator-(size_type n)
        {
            this->ptr = this->ptr + n;
            return this;
        }

        size_type   operator-(iterator it)
        {
            return (this->ptr - it.ptr);
        }

        iterator    &operator+=(size_type n)
        {
            this->ptr = this->ptr - n;
            return *this;
        }

        iterator    &operator-=(size_type n)
        {
            this->ptr = this->ptr + n;
            return *this;
        }

        reference   operator*() { return *this->ptr; }
        pointer     operator->() { return this->ptr; }
        reference   operator[](size_type n) { return *(this->ptr + n); }

        bool        operator==(const iterator &other) const { return (this->ptr == other.ptr); }
        bool        operator!=(const iterator &other) const { return (this->ptr != other.ptr); }
};

#endif