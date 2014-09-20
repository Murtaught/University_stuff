#include <cstdio>
#include <iostream>
#include <string>
#include <QVector>
#include <QList>
#include <QMultiMap>
#include <QSet>
using namespace std;
#define size(x) int(x.size())

string input;
int N, M, K;

struct State
{
    bool final;
    QMultiMap<char, int> transitions;
};

QVector<State> states;
QSet<int> current_states, next_step_states;

int main()
{
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);

    getline(cin, input);
    cin >> N >> M >> K;

    states.resize(N + 1); // states[0] isn't used

    for (int k = 0; k < K; ++k)
    {
        int final_state;
        cin >> final_state;

        states[final_state].final = true;
    }
    scanf("\n");

    for (int m = 0; m < M; ++m)
    {
        int a, b;
        char c;
        scanf("%d %d %c", &a, &b, &c);

        states[a].transitions.insertMulti(c, b);
    }

    current_states.insert( 1 );

    // everything is ready!
    for (int i = 0; i < size(input); ++i)
    {
        char c = input[i];

        foreach (int idx, current_states)
        {
            next_step_states += QSet<int>::fromList(states[idx].transitions.values( c ));
        }

        current_states.swap( next_step_states );
        next_step_states.clear();
    }

    foreach (int idx, current_states)
    {
        if ( states[ idx ].final )
        {
            printf("Accepts");
            return 0;
        }
    }

    printf("Rejects");
    return 0;
}
