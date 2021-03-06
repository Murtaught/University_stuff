#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

struct Automaton
{
    int n, m, k;
    map< pair<int, char>, int >  transition;
    map< int, bool > is_accepting;

    void read()
    {
        cin >> n >> m >> k;

        for (int i = 0; i < k; ++i)
        {
            int accepting_idx;
            cin >> accepting_idx;

            is_accepting[accepting_idx] = true;
        }

        for (int i = 0; i < m; ++i)
        {
            int a, b;
            char c;
            cin >> a >> b >> c;

            transition[make_pair(a, c)] = b;
        }
    }

    int getTransition(int st, char tr)
    {
        return transition[make_pair(st, tr)];
    }

    bool haveTransition(int st, char tr)
    {
        return getTransition(st, tr) != 0;
    }

};

Automaton A, B;
map<int, int> isomorph_state;
map<int, bool> was;

void check(int a, int b)
{
    if ( isomorph_state[a] == 0 )
    {
        isomorph_state[a] = b;
    }
    else
    {
        if ( isomorph_state[a] != b )
        {
            cout << "NO" << endl;
            exit(0);
        }
    }
}

void f(int a_idx, int b_idx)
{
    if ( !was[a_idx] )
    {
        was[a_idx] = true;

        for (char tr = 'a'; tr <= 'z'; ++tr)
        {
            if ( A.haveTransition(a_idx, tr) )
            {
                int a_where = A.getTransition(a_idx, tr);
                int b_where = B.getTransition(b_idx, tr);

                check(a_where, b_where);
                check(b_where, a_where);

                f(a_where, b_where);
            }
        }
    }
}

int main()
{
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);

    A.read();
    B.read();

    isomorph_state[1] = 1;
    f(1, 1);

    for (int i = 1; i <= A.n; ++i)
    {
        if ( A.is_accepting[i] != B.is_accepting[ isomorph_state[i] ] )
        {
            cout << "NO" << endl;
            exit(0);
        }
    }

    cout << "YES" << endl;
    return 0;
}

