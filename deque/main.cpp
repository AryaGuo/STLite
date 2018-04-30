//
// Created by 郭文轩 on 2018/4/29.
//

#include "deque.hpp"
#include <iostream>
#include <cstdio>
#include <deque>
using namespace std;

int main()
{
    sjtu::deque <int> q;
    deque <int> st;
    int n = 100;
    for(int i = 1; i <= n; i++) {
        int val = rand();
        q.push_back(val);
        st.push_back(val);
    }
    for(int i = 1; i <= n; i++) {
        if(i & 1)
        {
            assert(q.front() == st.front());
            cout << i << endl;
            q.pop_front();
            st.pop_front();
        }
        else
        {
            assert(q.back() == st.back());
            cout << i << endl;
            q.pop_back();
            st.pop_back();
        }
    }
    return 0;
}