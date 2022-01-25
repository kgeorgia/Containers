#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

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
        RandomAccessIterator();
        ~RandomAccessIterator();
};

#endif