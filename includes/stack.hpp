/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:20:17 by kgeorgia          #+#    #+#             */
/*   Updated: 2022/02/08 16:27:31 by kgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include <vector>
# include <stack>

namespace ft {
    template <class T, class Container = std::vector<T> >
    class stack {
        public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef std::size_t      size_type;

        protected:
            container_type      cont;

        public:
            explicit stack(const container_type &container = container_type()): cont(container) {}
            ~stack() {}

            bool                empty() const { return this->cont.empty(); }
            size_type           size() const { return this->cont.size(); }
            value_type          &top() { return this->cont.back(); }
            const value_type    &top() const { return this->cont.back(); }
            void                push( const value_type &value ) { this->cont.push_back(value); }
            void                pop() { this->cont.pop_back(); }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &first, const stack<T, Container> &second) { return first == second; }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &first, const stack<T, Container> &second) { return first != second; }
    
    template <class T, class Container>
    bool operator>(const stack<T, Container> &first, const stack<T, Container> &second) { return first > second; }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &first, const stack<T, Container> &second) { return first < second; }
    
    template <class T, class Container>
    bool operator>=(const stack<T, Container> &first, const stack<T, Container> &second) { return first >= second; }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &first, const stack<T, Container> &second) { return first <= second; }
    
}

#endif