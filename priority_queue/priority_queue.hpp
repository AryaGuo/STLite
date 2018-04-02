#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"
#include <set>

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 * it should be based on the vector written by yourself.
 */

template <class T>
void swap(T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
}

template<typename T, class Compare = std::less<T>>
class priority_queue {
private:

	struct node {
		T data;
		int len;
		node *ch[2];
        int id;

		node() = default;

        explicit node(T data) : data(data), len(0) {
            ch[0] = ch[1] = nullptr;
        }

		node(const node &other): data(other.data), len(other.len){
            if(other.ch[0] != nullptr)
			    ch[0] = new node(*other.ch[0]);
            else
                ch[0] = nullptr;
            if(other.ch[1] != nullptr)
                ch[1] = new node(*other.ch[1]);
            else
                ch[1] = nullptr;
		}

        node &operator=(const node &other) {
            if(this == &other)
                return *this;
            data = other.data;
            len = other.len;
            delete ch[0];
            delete ch[1];
            if(other.ch[0] != nullptr)
                ch[0] = new node(*other.ch[0]);
            else
                ch[0] = nullptr;
            if(other.ch[1] != nullptr)
                ch[1] = new node(*other.ch[1]);
            else
                ch[1] = nullptr;
            return *this;
        }

        ~node() {
            delete ch[0];
            delete ch[1];
            ch[0] = ch[1] = nullptr;
        }

	};

	size_t sz;
	node *head;

	void mergeNode(node* &a, node* &b) {
		if(a == nullptr)
		{
			a = b;
            b = nullptr;
			return;
		}
		if(b == nullptr)
			return;
		if(Compare()(a->data, b->data))
			swap(a, b);
		mergeNode(a -> ch[1], b);	//b > a
		if(a->ch[0] == nullptr || (a->ch[1] != nullptr && a->ch[0]->len < a->ch[1]->len))
			swap(a->ch[0], a->ch[1]);
		a->len = a->ch[1] == nullptr ? 0: a->ch[1]->len + 1;
		b = nullptr;
	}

public:

	priority_queue() {
		sz = 0;
		head = nullptr;
	}

	priority_queue(const priority_queue &other): sz(other.sz) {
        if(other.head != nullptr)
            head = new node(*other.head);
        else
            head = nullptr;
    }

	~priority_queue() {
        //remove(head);
        delete head;
        head = nullptr;
    }

	priority_queue &operator=(const priority_queue &other) {
        if(this == &other)
            return *this;
        sz = other.sz;
        //remove(head);
        delete head;
        if(other.head != nullptr)
            head = new node(*other.head);
        else
            head = nullptr;
        return *this;
    }
	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const {
        if(this->empty())
            throw container_is_empty();
        return head->data;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) {
		sz++;
		auto tmp = new node(e);
		mergeNode(head, tmp);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() {
		if(this->empty())
            throw container_is_empty();
		sz--;
        mergeNode(head->ch[0], head->ch[1]);
        auto t1 = head->ch[0];
        head->ch[0] = head->ch[1] = nullptr;
        delete head;
        head = t1;
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const {
        return sz;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const {
        return sz == 0;
	}

	/**
	 * return a merged priority_queue with at least O(logn) complexity.
	 */
	void merge(priority_queue &other) {
		mergeNode(head, other.head);
		sz += other.sz;
        other.sz = 0;
	}

};

}

#endif
