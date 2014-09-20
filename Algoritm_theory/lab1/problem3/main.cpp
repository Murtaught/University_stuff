#include <QFile>
#include <QTextStream>
#include <QList>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QDebug>

QTextStream in, out;

// 10e9 + 7 неожиданно не сработало, так надежнее
const int MODULO =  1000000007;

enum DFSColor { WHITE = 0, GREY = 1, BLACK = 2 };

struct State
{
    bool final;
    DFSColor dfs_color;
    QMap<int, int> ways; // количество путей отсюда в другое состояние по его номеру
    int answer;
};

QVector<State> states;
QSet<int> loops;
bool answer_is_infinity;

void openFiles()
{
    QFile *in_file = new QFile("problem3.in");
    if (!in_file->open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open input file!";
    }
    in.setDevice(in_file);

    QFile *out_file = new QFile("problem3.out");
    out_file->open(QFile::WriteOnly | QFile::Text);
    out.setDevice(out_file);
}

void readInput()
{
    int N, M, K;
    in >> N >> M >> K;

    states.resize(N + 1);
    for (int k = 0; k < K; ++k)
    {
        int final_state;
        in >> final_state;

        states[final_state].final = true;
    }

    for (int m = 0; m < M; ++m)
    {
        int a, b;
        in >> a >> b;

        states[a].ways[b] += 1;

        char c = '#';
        while (c != '\n')
            in >> c;
    }
}

void dfs(int this_state_idx)
{
    State &this_state = states[this_state_idx];

    if ( this_state.dfs_color == WHITE )
    {
        this_state.dfs_color = GREY;

        this_state.answer = (this_state.final) ? 1 : 0;

        foreach (int idx, this_state.ways.keys())
        {
            dfs(idx);

            long long int temp = states[idx].answer;
            temp *= this_state.ways[idx];
            temp %= MODULO;

            this_state.answer += temp;
        }

        if ( loops.contains(this_state_idx) && this_state.answer != 0 )
            answer_is_infinity = true;

        this_state.dfs_color = BLACK;
    }
    else if ( this_state.dfs_color == GREY )
    {
        // мы нашли цикл
        loops.insert( this_state_idx );
    }
}

void computeAnswers()
{
    answer_is_infinity = false;
    dfs(1);
}

void printAnswer()
{
    if ( answer_is_infinity )
        out << "-1";
    else
        out << states[1].answer;
}

int main()
{
    openFiles();
    readInput();
    computeAnswers();
    printAnswer();

    return 0;
}
