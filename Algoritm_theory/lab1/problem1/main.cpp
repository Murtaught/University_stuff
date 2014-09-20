#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#define size(x) int(x.size())

string input;
int N, M, K;

const int ALPHABET_SIZE = 'z' - 'a' + 1;

struct State
{
    bool final;
    int transition[ALPHABET_SIZE];

    State()
    {
        final = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            transition[i] = 0;
    }
};

vector<State> states;
int current_state;

int main()
{
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);

    getline(cin, input);
    cin >> N >> M >> K;

    states.resize(N + 1); // states[0] не используется явно

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

        states[a].transition[c - 'a'] = b;
    }

    current_state = 1;

    // Приступаем к эмуляции автомата
    for (int i = 0; i < size(input); ++i)
    {
        current_state = states[ current_state ].transition[ input[i] - 'a' ];
    }

    if ( states[ current_state ].final )
        printf("Accepts");
    else
        printf("Rejects");

    fclose(stdout);
    return 0;
}
