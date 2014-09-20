#include <QFile>
#include <QTextStream>
#include <QString>
#include <QChar>
#include <QList>
#include <QVector>
#include <QMap>
#include <QHash>
#include <QPair>
#include <QSet>
#include <QQueue>
#include <QDebug>
#include <QtAlgorithms>

// 10e9 + 7 неожиданно не сработало, так надежнее
const int MODULO = 1000000007;
int L;

QTextStream in, out;

void openFiles()
{
    QFile *in_file = new QFile("problem5.in");
    if (!in_file->open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Could not open input file!";
    }
    in.setDevice(in_file);

    QFile *out_file = new QFile("problem5.out");
    out_file->open(QFile::WriteOnly | QFile::Text);
    out.setDevice(out_file);
}

uint qHash(const QSet<int> &set)
{
    uint seed = 0;

    QList<int> list = set.toList();
    qSort(list);

    foreach (int x, list)
        seed ^= qHash(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
}

// Эта структура подходит как для НКА, так и для ДКА
struct Automaton
{
    typedef QMap<QChar, int> StateT;

    QVector< StateT > states;
    QSet<int> final_states;


    void print()
    {
        out << (states.size() - 1) << " states\n";

        out << "final states: ";
        foreach (int final_state, final_states)
        {
            out << final_state << " ";
        }
        out << "\n";

        for (int i = 1; i < states.size(); ++i)
            foreach (QChar c, states[i].uniqueKeys())
            {
                foreach (int b, states[i].values(c))
                    out << i << " --" << c << "--> " << b << "\n";
            }
    }
};

Automaton nfa, dfa;

void readInput()
{
    int N, M, K;
    in >> N >> M >> K >> L;

    nfa.states.resize(N + 1);
    for (int k = 0; k < K; ++k)
    {
        int final_idx;
        in >> final_idx;

        nfa.final_states.insert( final_idx );
    }

    for (int m = 0; m < M; ++m)
    {
        int a, b;
        in >> a >> b;

        char c = ' ';
        while (c == ' ')
            in >> c;

        nfa.states[a].insertMulti(c, b);
    }
}

// Алгоритм Томпсона
Automaton transformNFAtoDFA(const Automaton &nfa)
{
    Automaton dfa;
    {
        // Здесь мы будем для множества состояний НКА хранить
        // соответствующий им номер состояния ДКА, а заодно
        // помнить какие множества мы уже обработали
        QHash< QSet<int>, int >  congruence;

        QQueue< QSet<int> >  queue;
        {
            // Предварительная настройка нулевого (пустого) и первого стояния ДКА
            dfa.states.resize(2);

            QSet<int> one_set; one_set << 1;
            queue.enqueue(one_set);
            congruence[one_set] = 1;
            if ( nfa.final_states.contains(1) )
                dfa.final_states.insert(1);

            congruence[QSet<int>()] = 0; // пустое множество состояний НКА
        }

        while ( !queue.isEmpty() )
        {
            QSet<int> cur_set = queue.head();
            queue.dequeue();

            for (int c = 'a'; c <= 'z'; ++c)
            {
                QSet<int> next_set;

                foreach (int a, cur_set)
                    if ( nfa.states[a].contains(c) )
                        next_set += QSet<int>::fromList(nfa.states[a].values(c));

                // Если мы такого набора состояний НКА еще не встречали...
                if ( !congruence.contains(next_set) )
                {
                    // ...нужно создать ему эквивалент в ДКА
                    dfa.states.resize( dfa.states.size() + 1 );
                    congruence[next_set] = dfa.states.size() - 1;

                    // проверить не будет ли новое состояние ДКА допускающим
                    // буквально: если пересечение текущего множества состояний НКА и
                    // множества его допускающих состояний не пусто, то...
                    QSet<int> temp = nfa.final_states;
                    if ( !temp.intersect(next_set).isEmpty() )
                        dfa.final_states.insert( dfa.states.size() - 1 );

                    // и поместить такой набор в очередь на обработку
                    queue.enqueue( next_set );
                }

                if ( !next_set.isEmpty() )
                    dfa.states[ congruence[cur_set] ][c] = congruence[next_set];
            }
        }
    }
    return dfa;
}

QMap<QPair<int, int>, int> hash;
QString current_word;

int dfs(int this_state_idx, int l)
{
    // Это немного измененный кусок из решения задачи №4
    // Здесь ради разнообразия я включил вывод в файл всех найденных строк
    //if ( !hash.contains(qMakePair(this_state_idx, l)) )
    {
        Automaton::StateT &this_state = dfa.states[this_state_idx];
        int answer = 0;

        if (l == 0)
        {
             if ( dfa.final_states.contains(this_state_idx) )
             {
                 answer = 1;
                   out << current_word << '\n';
             }
        }
        else
        {
            foreach (QChar c, this_state.keys())
            {
                  current_word += c;
                answer += dfs(this_state[c], l - 1);
                answer %= MODULO;
                  current_word.chop(1); // remove last character (it is c)
            }
        }

        //hash[ qMakePair(this_state_idx, l) ] = answer;
        return answer;
    }
    //return hash[ qMakePair(this_state_idx, l) ];
}

int main()
{
    openFiles();
    readInput();
    dfa = transformNFAtoDFA(nfa);

    //nfa.print();
    //dfa.print();

    // Задача сведена к предыдущей
    out << dfs(1, L);

    return 0;
}
