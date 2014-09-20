#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QList>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QDebug>

QTextStream in, out;

// 10e9 + 7 неожиданно не сработало, так надежнее
const int MODULO = 1000000007;

struct State
{
    bool final;
    QMap<QChar, int> transitions;
};

QVector<State> states;
QMap<QPair<int, int>, int> hash;
QString current_word;
int L;


void openFiles()
{
    QFile *in_file = new QFile("problem4.in");
    if (!in_file->open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open input file!";
    }
    in.setDevice(in_file);

    QFile *out_file = new QFile("problem4.out");
    out_file->open(QFile::WriteOnly | QFile::Text);
    out.setDevice(out_file);
}

void readInput()
{
    int N, M, K;
    in >> N >> M >> K >> L;

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

        char c = ' ';
        while (c == ' ')
            in >> c;

        states[a].transitions[c] = b;
    }
}

int dfs(int this_state_idx, int l)
{
    if ( !hash.contains(qMakePair(this_state_idx, l)) )
    {
        State &this_state = states[this_state_idx];
        int answer = 0;

        if (l == 0)
        {
             if (this_state.final)
             {
                 answer = 1;
                 //out << current_word << '\n';
             }
        }
        else
        {
            foreach (QChar c, this_state.transitions.keys())
            {
                //current_word += c;
                answer += dfs(this_state.transitions[c], l - 1);
                answer %= MODULO;
                //current_word.chop(1); // remove last character (it is c)
            }
        }

        hash[ qMakePair(this_state_idx, l) ] = answer;
    }
    return hash[ qMakePair(this_state_idx, l) ];
}

int main()
{
    openFiles();
    readInput();

    out << dfs(1, L);

    return 0;
}
