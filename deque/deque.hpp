#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu {
    const int N = 550;

    template<class T>
    class deque {
    private:
        struct bar;
        struct node {
            node *pre, *nxt;
            bar *Bar;
            T *data;

            node():pre(nullptr), nxt(nullptr), Bar(nullptr), data(nullptr) {}
            node(const T &value): pre(nullptr), nxt(nullptr), Bar(nullptr) {
                data = new T(value);
            }
            node(const node &other): pre(pre), nxt(nxt), Bar(Bar) {
                data = new T(other.data);
            }
            node& operator=(const node &other) {
                if(this == &other)
                    return *this;
                pre = other.pre;
                nxt = other.nxt;
                Bar = other.Bar;
                data = new T(other.data);
            }
            node* operator+(const int &n) const{
                auto pos = this->pos();
                node* res = const_cast<node*>(this);
                if(pos + n <= this->Bar->sz) {
                    for(int i = 0; i < n; i++)
                        res = res->nxt;
                    return res;
                }
                auto cnt = n - this->Bar->sz + pos - 1;
                auto newBar = Bar->nxt;
                if(!newBar)
                    throw invalid_iterator();
                res = newBar->head;
                while(cnt && newBar->sz <= cnt) {
                    cnt -= newBar->sz;
                    newBar = newBar->nxt;
                    if(!newBar)
                        throw invalid_iterator();
                    res = newBar->head;
                }
                for(int i = 0; i < cnt; i++)
                    res = res->nxt;
                return res;
            }
            node* operator-(const int &n) const{
                auto pos = this->pos();
                node* res = const_cast<node*>(this);
                if(pos - n >= 1) {
                    for(int i = 0; i < n; i++)
                        res = res->pre;
                    return res;
                }
                auto cnt = n - pos;
                auto newBar = Bar->pre;
                if(!newBar)
                    throw invalid_iterator();
                res = newBar->tail;
                while(cnt && newBar->sz <= cnt) {
                    cnt -= newBar->sz;
                    newBar = newBar->pre;
                    if(!newBar)
                        throw invalid_iterator();
                    res = newBar->tail;
                }
                for(int i = 0; i < cnt; i++)
                    res = res->pre;
                return res;
            }
            ~node() {
                delete data;
            }

            int pos() const{
                int cnt = 1;
                auto tmp = this->Bar->head;
                while(tmp != this) {
                    tmp = tmp->nxt;
                    cnt++;
                }
                return cnt;
            }
        };

        struct bar {
            size_t sz;
            node *head, *tail;
            bar *pre, *nxt;

            bar(): sz(0), head(nullptr), tail(nullptr), pre(nullptr), nxt(nullptr) {}
        };

        size_t sz;
        bar *head, *tail;
        node* _end;

        void copyNode(node* &cur, node* other) {
            if(other == nullptr)
                return;
            cur = new node(*other->data);
        }

        void copyBar(bar* &cur, bar* other) {
            if(other == nullptr)
                return;
            cur = new bar();
            cur->sz = other->sz;
            if(!other->head->data) {
                return;
            }
            copyNode(cur->head, other->head);
            cur->head->Bar = cur;
            auto last = cur->head, oth = other->head;
            while(oth->nxt && oth->nxt->data) {
                copyNode(last->nxt, oth->nxt);
                last->nxt->pre = last;
                last = last->nxt;
                last->Bar = cur;
                oth = oth->nxt;
            }
            cur->tail = last;
        }

        void removeBar(bar* Bar) {
            auto now = Bar->head;
            while(now && now->data) {
                auto tmp = now->nxt;
                delete now;
                now = tmp;
            }
            delete Bar;
        }

    public:
        class const_iterator;
        class iterator {
            friend const_iterator;
            friend deque;
        private:
            deque* Deq;
            node* p;

        public:
            iterator() {}
            iterator(deque* Deq, node* p): Deq(Deq), p(p) {}
            /**
             * return a new iterator which pointer n-next elements
             *   even if there are not enough elements, the behaviour is **undefined**.
             * as well as operator-
             */
            iterator operator+(const int &n) const {
                if(n < 0)
                    return this->operator-(-n);
                try {
                    iterator res = *this;
                    return iterator(this->Deq, *res.p + n);
                }
                catch(...) {
                    throw invalid_iterator();
                }
            }
            iterator operator-(const int &n) const {
                if(n < 0)
                    return this->operator+(-n);
                try {
                    iterator res = *this;
                    return iterator(this->Deq, *res.p - n);
                }
                catch(...) {
                    throw invalid_iterator();
                }
            }
            // return the distance between two iterator,
            // if these two iterators points to different vectors, throw invalid_iterator.
            int operator-(const iterator &rhs) const {
                if(Deq != rhs.Deq)
                    throw invalid_iterator();
                int cnt = 0;
                bar* Bar = p->Bar;
                node* nd = p;
                try {
                    if(p->Bar != rhs.p->Bar) {
                        while(nd->nxt)
                            cnt++, nd = nd->nxt;
                        cnt++;
                        Bar = Bar->nxt;
                        if(!Bar)
                            throw -1;
                        nd = Bar->head;
                        while(Bar != rhs.p->Bar && Bar->nxt) {
                            cnt += Bar->sz;
                            Bar = Bar->nxt;
                            nd = Bar->head;
                        }
                    }
                    if(Bar == rhs.p->Bar) {
                        while(nd != rhs.p && nd->nxt) {
                            cnt++;
                            nd = nd->nxt;
                        }
                        if(nd == rhs.p)
                            return -cnt;
                    }
                    throw -1;
                }
                catch (...) {
                    cnt = 0;
                    Bar = p->Bar;
                    nd = p;
                    if(p->Bar != rhs.p->Bar) {
                        while(nd->pre)
                            cnt++, nd = nd->pre;
                        cnt++;
                        Bar = Bar->pre;
                        nd = Bar->tail;
                        while(Bar != rhs.p->Bar && Bar->pre) {
                            cnt += Bar->sz;
                            Bar = Bar->pre;
                            nd = Bar->tail;
                        }
                    }
                    if(Bar == rhs.p->Bar) {
                        while(nd != rhs.p && nd->pre) {
                            cnt++;
                            nd = nd->pre;
                        }
                        if(nd == rhs.p)
                            return cnt;
                    }
                }
                throw runtime_error();
            }

            iterator operator+=(const int &n) {
                *this = this->operator+(n);
                return *this;
            }
            iterator operator-=(const int &n) {
                *this = this->operator-(n);
                return *this;
            }
            /**
             * iter++
             */
            iterator operator++(int) {
                auto tmp = *this;
                this->operator+=(1);
                return tmp;
            }
            /**
             * ++iter
             */
            iterator& operator++() {
                this->operator+=(1);
                return *this;
            }
            /**
             * iter--
             */
            iterator operator--(int) {
                auto tmp = *this;
                this->operator-=(1);
                return tmp;
            }
            /**
             * --iter
             */
            iterator& operator--() {
                this->operator-=(1);
                return *this;
            }
            /**
             * *it
             */
            T& operator*() const {
                if(!p->data)
                    throw invalid_iterator();
                return *p->data;
            }
            /**
             * it->field
             */
            T* operator->() const noexcept {
                if(!p->data)
                    throw invalid_iterator();
                return p->data;
            }
            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                return Deq == rhs.Deq && p == rhs.p;
            }
            bool operator==(const const_iterator &rhs) const {
                return Deq == rhs.Deq && p == rhs.p;
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !(this->operator==(rhs));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(this->operator==(rhs));
            }
        };
        class const_iterator {
            friend iterator;
        private:
            const deque * Deq;
            const node* p;

        public:
            const_iterator(): Deq(nullptr), p(nullptr) {}
            const_iterator(const deque* Deq, const node* p): Deq(Deq), p(p) {}
            const_iterator(const const_iterator &other): Deq(other.Deq), p(other.p) {}
            const_iterator(const iterator &other): Deq(other.Deq), p(other.p) {}

            const_iterator operator+(const int &n) const {
                if(n < 0)
                    return this->operator-(-n);
                try {
                    const_iterator res = *this;
                    return const_iterator(this->Deq, *res.p + n);
                }
                catch(...) {
                    throw invalid_iterator();
                }
            }
            const_iterator operator-(const int &n) const {
                if(n < 0)
                    return this->operator+(-n);
                try {
                    const_iterator res = *this;
                    return const_iterator(this->Deq, *res.p - n);
                }
                catch(...) {
                    throw invalid_iterator();
                }
            }

            int operator-(const const_iterator &rhs) const {
                if(Deq != rhs.Deq)
                    throw invalid_iterator();
                int cnt = 0;
                bar* Bar = p->Bar;
                const node* nd = p;
                try {
                    if(p->Bar != rhs.p->Bar) {
                        while(nd->nxt)
                            cnt++, nd = nd->nxt;
                        cnt++;
                        Bar = Bar->nxt;
                        if(!Bar)
                            throw -1;
                        nd = Bar->head;
                        while(Bar != rhs.p->Bar && Bar->nxt) {
                            cnt += Bar->sz;
                            Bar = Bar->nxt;
                            nd = Bar->head;
                        }
                    }
                    if(Bar == rhs.p->Bar) {
                        while(nd != rhs.p && nd->nxt) {
                            cnt++;
                            nd = nd->nxt;
                        }
                        if(nd == rhs.p)
                            return -cnt;
                    }
                    throw -1;
                }
                catch (...) {
                    cnt = 0;
                    Bar = p->Bar;
                    nd = p;
                    if(p->Bar != rhs.p->Bar) {
                        while(nd->pre)
                            cnt++, nd = nd->pre;
                        cnt++;
                        Bar = Bar->pre;
                        nd = Bar->tail;
                        while(Bar != rhs.p->Bar && Bar->pre) {
                            cnt += Bar->sz;
                            Bar = Bar->pre;
                            nd = Bar->tail;
                        }
                    }
                    if(Bar == rhs.p->Bar) {
                        while(nd != rhs.p && nd->pre) {
                            cnt++;
                            nd = nd->pre;
                        }
                        if(nd == rhs.p)
                            return cnt;
                    }
                }
                throw runtime_error();
            }


            const_iterator operator+=(const int &n) {
                *this = this->operator+(n);
                return *this;
            }
            const_iterator operator-=(const int &n) {
                *this = this->operator-(n);
                return *this;
            }

            const_iterator operator++(int) {
                auto tmp = *this;
                this->operator+=(1);
                return tmp;
            }

            const_iterator& operator++() {
                this->operator+=(1);
                return *this;
            }

            const_iterator operator--(int) {
                auto tmp = *this;
                this->operator-=(1);
                return tmp;
            }

            const_iterator& operator--() {
                this->operator-=(1);
                return *this;
            }

            T& operator*() const {
                if(!p->data)
                    throw invalid_iterator();
                return *p->data;
            }

            T* operator->() const noexcept {
                if(!p->data)
                    throw invalid_iterator();
                return p->data;
            }

            bool operator==(const iterator &rhs) const {
                return Deq == rhs.Deq && p == rhs.p;
            }
            bool operator==(const const_iterator &rhs) const {
                return Deq == rhs.Deq && p == rhs.p;
            }

            bool operator!=(const iterator &rhs) const {
                return !(this->operator==(rhs));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !(this->operator==(rhs));
            }
        };

        deque(): sz(0){
            _end = new node();
            auto newBar = new bar();
            newBar->head = newBar->tail = _end;
            newBar->sz = 1;
            _end->Bar = head = tail = newBar;
        }

        deque(const deque &other): sz(other.sz) {
            _end = new node();
            copyBar(head, other.head);
            auto last = head, oth = other.head;
            while(oth->nxt) {
                copyBar(last->nxt, oth->nxt);
                last->nxt->pre = last;
                last = last->nxt;
                oth = oth->nxt;
            }
            tail = last;
            if(tail->tail) {
                tail->tail->nxt = _end;
                _end->pre = tail->tail;
                _end->nxt = nullptr;
                _end->Bar = tail;
                tail->tail = _end;
            }
            else {
                tail->head = tail->tail = _end;
                _end->pre = _end->nxt = nullptr;
                _end->Bar = tail;
            }
        }

        ~deque() {
            clear();
            delete head;
            delete _end;
        }

        deque &operator=(const deque &other) {
            if(this == &other)
                return *this;
            sz = other.sz;
            while(head != tail) {
                auto tmp = head->nxt;
                removeBar(head);
                head = tmp;
            }
            removeBar(head);
            copyBar(head, other.head);
            auto last = head, oth = other.head;
            while(oth->nxt) {
                copyBar(last->nxt, oth->nxt);
                last->nxt->pre = last;
                last = last->nxt;
                oth = oth->nxt;
            }
            tail = last;
            if(tail->tail) {
                tail->tail->nxt = _end;
                _end->pre = tail->tail;
                _end->nxt = nullptr;
                _end->Bar = tail;
                tail->tail = _end;
            }
            else {
                tail->head = tail->tail = _end;
                _end->pre = _end->nxt = nullptr;
                _end->Bar = tail;
            }
            return *this;
        }
        /**
         * access specified element with bounds checking
         * throw index_out_of_bound if out of bound.
         * complexity: O(sqrt(N))
         */
        T & at(const size_t &pos) {
            if(pos < 0 || pos >= sz)
                throw index_out_of_bound();
            size_t tmp = pos + 1;
            auto pt = head;
            while(tmp > pt->sz) {
                tmp -= pt->sz;
                pt = pt->nxt;
            }
            if(tmp < pt->sz / 2) {
                auto res = pt->head;
                for(auto i = 1; i < tmp; i++)
                    res = res->nxt;
                return *res->data;
            }
            else {
                auto res = pt->tail;
                for(auto i = pt->sz; i > tmp; i--)
                    res = res->pre;
                return *res->data;
            }
        }

        const T & at(const size_t &pos) const {
            if(pos < 0 || pos >= sz)
                throw index_out_of_bound();
            size_t tmp = pos + 1;
            auto pt = head;
            while(tmp > pt->sz) {
                tmp -= pt->sz;
                pt = pt->nxt;
            }
            if(tmp < pt->sz / 2) {
                auto res = pt->head;
                for(auto i = 1; i < tmp; i++)
                    res = res->nxt;
                return *res->data;
            }
            else {
                auto res = pt->tail;
                for(auto i = pt->sz; i > tmp; i--)
                    res = res->pre;
                return *res->data;
            }
        }

        T & operator[](const size_t &pos) {
            return this->at(pos);
        }
        const T & operator[](const size_t &pos) const {
            return this->at(pos);
        }
        /**
         * access the first element
         * throw container_is_empty when the container is empty.
         */
        const T & front() const {
            if(sz == 0)
                throw container_is_empty();
            return *head->head->data;
        }
        /**
         * access the last element
         * throw container_is_empty when the container is empty.
         */
        const T & back() const {
            if(sz == 0)
                throw container_is_empty();
            if(tail->tail->pre)
                return *tail->tail->pre->data;
            return *tail->pre->tail->data;
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(this, head->head);
        }
        const_iterator cbegin() const {
            return const_iterator(this, head->head);
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(this, tail->tail);
        }
        const_iterator cend() const {
            return const_iterator(this, tail->tail);
        }
        /**
         * checks whether the container is empty.
         */
        bool empty() const {
            return sz == 0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return sz;
        }
        /**
         * clears the contents
         */
        void clear() {
            while(head != tail) {
                auto tmp = head->nxt;
                removeBar(head);
                head = tmp;
            }
            removeBar(head);
            sz = 0;
            auto newBar = new bar();
            newBar->head = newBar->tail = _end;
            newBar->sz = 1;
            _end->Bar = head = tail = newBar;
            _end->pre = _end->nxt = nullptr;
        }
        /**
         * inserts elements at the specified location in the container.
         * inserts value before pos
         * returns an iterator pointing to the inserted value
         *     throw if the iterator is invalid or it point to a wrong place.
         */
        iterator insert(iterator pos, const T &value) {
            if(pos.Deq != this)
                throw invalid_iterator();
            auto Bar = pos.p->Bar;
            Bar = split(Bar, pos.p);
            auto res = new node(value);
            auto tmp = Bar->head;
            tmp->pre = res;
            res->nxt = tmp;
            Bar->head = res;
            res->Bar = Bar;
            ++sz;
            ++Bar->sz;
            maintain();
            return iterator(this, res);
        }
        /**
         * removes specified element at pos.
         * removes the element at pos.
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid or it points to a wrong place.
         */
        iterator erase(iterator pos) {
            if(sz == 0)
                throw container_is_empty();
            if(pos.Deq != this || pos == this->end())
                throw invalid_iterator();
            auto Bar = pos.p->Bar;
            Bar = split(Bar, pos.p);

            auto tmp = Bar->head;
            auto res = tmp->nxt;
            if(res)
                res->pre = nullptr;
            else
                Bar->tail = nullptr;
            Bar->head = res;
            delete tmp;
            --sz;
            --Bar->sz;
            if(Bar->sz == 0) {
                res = Bar->nxt->head;
                if(Bar->pre)
                    Bar->pre->nxt = Bar->nxt;
                else
                    head = Bar->nxt;
                if(Bar->nxt)
                    Bar->nxt->pre = Bar->pre;
                else
                    tail = Bar->pre;
                delete Bar;
            }
            maintain();
            return iterator(this, res);
        }
        /**
         * adds an element to the end
         */
        void push_back(const T &value) {
            auto res = new node(value);
            auto Bar = tail;
            auto pos = Bar->tail;
            if(pos->pre) {
                pos->pre->nxt = res;
                res->pre = pos->pre;
            }
            else
                Bar->head = res;
            pos->pre = res;
            res->nxt = pos;
            res->Bar = Bar;
            ++sz;
            ++Bar->sz;
            if(Bar->sz > N) {
                split(Bar, Bar->sz / 2 + 1);
                maintain();
            }
        }
        /**
         * removes the last element
         *     throw when the container is empty.
         */
        void pop_back() {
            if(sz == 0)
                throw container_is_empty();
            auto Bar = tail;
            auto pos = Bar->tail;
            if(pos->pre)
                pos = pos->pre;
            else {
                Bar = Bar->pre;
                pos = Bar->tail;
            }

            if(pos->pre)
                pos->pre->nxt = pos->nxt;
            else
                Bar->head = pos->nxt;
            if(pos->nxt)
                pos->nxt->pre = pos->pre;
            else
                Bar->tail = pos->pre;
            delete pos;
            --sz;
            --Bar->sz;
            if(Bar->sz == 0) {
                if(Bar->pre)
                    Bar->pre->nxt = Bar->nxt;
                else
                    head = Bar->nxt;
                if(Bar->nxt)
                    Bar->nxt->pre = Bar->pre;
                else
                    tail = Bar->pre;
                delete Bar;
                Bar = nullptr;
            }

            if(Bar && Bar->pre && Bar->sz + Bar->pre->sz <= N)
                merge(Bar->pre, Bar);
        }
        /**
         * inserts an element to the beginning.
         */
        void push_front(const T &value) {
            auto res = new node(value);
            auto Bar = head;
            auto pos = Bar->head;
            Bar->head = res;
            pos->pre = res;
            res->nxt = pos;
            res->Bar = Bar;
            ++sz;
            ++Bar->sz;
            if(Bar->sz > N) {
                split(Bar, Bar->sz / 2);
                maintain();
            }
        }
        /**
         * removes the first element.
         *     throw when the container is empty.
         */
        void pop_front() {
            if(sz == 0)
                throw container_is_empty();
            auto Bar = head;
            auto pos = Bar->head;
            if(pos->nxt)
                pos->nxt->pre = pos->pre;
            else
                Bar->tail = pos->pre;
            Bar->head = pos->nxt;
            delete pos;
            --sz;
            --Bar->sz;
            if(Bar->sz == 0) {
                if(Bar->nxt)
                    Bar->nxt->pre = Bar->pre;
                else
                    tail = Bar->pre;
                head = Bar->nxt;
                delete Bar;
                Bar = nullptr;
            }

            if(Bar && Bar->nxt && Bar->sz + Bar->nxt->sz <= N)
                merge(Bar, Bar->nxt);
        }

    private:
        bar* split(bar* const Bar, node* const &pos) {
            if(pos == Bar->head)
                return Bar;
            auto res = Bar->head;
            size_t cnt = 0;
            while(res != pos) {
                cnt++;
                res = res->nxt;
            }
            auto newBar = new bar();
            newBar->sz = Bar->sz - cnt;
            newBar->head = res;
            newBar->tail = Bar->tail;
            newBar->nxt = Bar->nxt;
            newBar->pre = Bar;
            Bar->sz = cnt;
            Bar->tail = res->pre;
            Bar->nxt = newBar;
            res->pre->nxt = nullptr;
            res->pre = nullptr;
            if(tail == Bar)
                tail = newBar;
            else
                newBar->nxt->pre = newBar;
            for(auto i = newBar->head; i; i = i->nxt)
                i->Bar = newBar;
            return newBar;
        }

        bar* split(bar* const Bar, const size_t &pos) {
            if(pos == 1)
                return Bar;
            auto res = Bar->head;
            for(auto i = 1; i < pos; i++)
                res = res->nxt;
            auto newBar = new bar();
            newBar->sz = Bar->sz - pos + 1;
            newBar->head = res;
            newBar->tail = Bar->tail;
            newBar->nxt = Bar->nxt;
            newBar->pre = Bar;
            Bar->sz = pos - 1;
            Bar->tail = res->pre;
            Bar->nxt = newBar;
            res->pre->nxt = nullptr;
            res->pre = nullptr;
            if(tail == Bar)
                tail = newBar;
            else
                newBar->nxt->pre = newBar;
            for(auto i = newBar->head; i; i = i->nxt)
                i->Bar = newBar;
            return newBar;
        }

        void merge(bar* a, bar* b) {
            for(auto i = b->head; i; i = i->nxt)
                i->Bar = a;
            a->sz += b->sz;
            a->tail->nxt = b->head;
            b->head->pre = a->tail;
            a->tail = b->tail;
            a->nxt = b->nxt;
            if(tail == b)
                tail = a;
            else
                a->nxt->pre = a;
            delete b;
        }

        void maintain() {
            auto tmp = head;
            while(tmp && tmp ->nxt) {
                if(tmp->sz + tmp->nxt->sz <= N)
                    merge(tmp, tmp->nxt);
                tmp = tmp->nxt;
            }
        }

    };

}

#endif
