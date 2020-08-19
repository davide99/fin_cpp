#ifndef SRUCTURES_MAXFIXEDHEAP_H
#define SRUCTURES_MAXFIXEDHEAP_H

#include <vector>
#include <cstdint>
#include <functional>

namespace Structures {
    template<typename T, typename Compare = std::less<T>>
    class MaxFixedHeap {
    public:
        explicit MaxFixedHeap(size_t max_size) : maxSize(max_size) {}

        typename std::vector<T>::iterator begin() {
            return this->c.begin();
        }

        typename std::vector<T>::iterator end() {
            return this->c.end();
        }

        void push(const T &x) {
            if (this->c.size() == maxSize) {
                typename std::vector<T>::iterator iterator_min = std::min_element(this->c.begin(), this->c.end(),
                                                                                  this->cmp);
                if (*iterator_min < x) {
                    *iterator_min = x;
                    std::make_heap(this->c.begin(), this->c.end(), this->cmp);
                }
            } else {
                this->c.push_back(x);
                std::make_heap(this->c.begin(), this->c.end(), this->cmp);
            }
        }

        void pop() {
            if (this->c.empty())
                return;
            std::pop_heap(this->c.begin(), this->c.end(), this->cmp);
            this->c.pop_back();
        }

        inline const T &top() const {
            return c.front();
        }

        [[nodiscard]] inline bool empty() const {
            return c.empty();
        }

        [[nodiscard]] inline size_t size() const {
            return c.size();
        }

    protected:
        std::vector<T> c;
        size_t maxSize;
        Compare cmp;
    };
}

#endif
