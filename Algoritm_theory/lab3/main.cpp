//#define DEBUG_MODE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <tuple>
#include <cstdlib>
using namespace std;

string start_state;
set<string> accepting_states, rejecting_states;
map< pair<string, char>, tuple<string, char, int> > sigma;
vector<char> alphabet;
string tape;

int steps_count = 0;
bool accepted;

char stringToChar(string s)
{
    return s[0];
}

int stringToInt(string s)
{
    stringstream ss;
    ss << s;
    int i;
    ss >> i;
    return i;
}

char getCharOnTape(int idx)
{
    if (idx >= int(tape.size()))
        tape += string(idx - tape.size() + 1, '_');

    return tape[idx];
}

vector<string> split(string str)
{
    vector<string> vec;

    stringstream ssin(str);
    while ( ssin.good() )
    {
        string s;
        ssin >> s;

        vec.push_back(s);
    }

    return vec;
}

int stringArrowToStep(string s)
{
    if (s == ">")
    {
        return +1;
    }
    else if (s == "<")
    {
        return -1;
    }
    else if (s == "^")
    {
        return 0;
    }
    else
    {
        cout << "Syntax error in program! Symbol \"" << s[0] << "\" is not in set [>, <, ^]." << endl;

        exit(-1); // выходим из программы прямо тут с ненулевым exit code
    }
}


void addTransition(const string &st1, char c,
                   const string &st2, char nc, int step)
{
    sigma[ make_pair(st1, c) ] = make_tuple(st2, nc, step);
}

void readProgram()
{
    ifstream in("program.txt");

    while (in)
    {
        string line;
        getline(in, line);

        if (line == "" || line[0] == '#')
            continue;

        vector<string> words = split(line);

        if ( words[0] == "alphabet:" )
        {
            for (size_t i = 1; i < words.size(); ++i)
                alphabet.push_back( stringToChar(words[i]) );
        }
        else if ( words[0] == "start:" )
        {
            start_state = words[1];
        }
        else if ( words[0] == "accept:" )
        {
            for (size_t i = 1; i < words.size(); ++i)
                accepting_states.insert( words[i] );
        }
        else if ( words[0] == "reject:" )
        {
            for (size_t i = 1; i < words.size(); ++i)
                rejecting_states.insert( words[i] );
        }
        else if ( words.size() >= 6 && words[2] == "->" )
        {
            if (words[1] == "any")
            {
                for (size_t i = 0; i < alphabet.size(); ++i)
                    if (words[4] == "same")
                    {
                        addTransition(words[0], alphabet[i],
                                words[3], alphabet[i], stringArrowToStep(words[5]));
                    }
                    else
                    {
                        addTransition(words[0], alphabet[i],
                                words[3],  stringToChar(words[4]), stringArrowToStep(words[5]));
                    }
            }
            else
            {
                addTransition(words[0], stringToChar(words[1]),
                        words[3], stringToChar(words[4]), stringArrowToStep(words[5]));
            }
        }
        else
        {
            cout << "Warning: could not parse line \"" << line << "\"! " << endl;
        }
    }
}

void readTape()
{
    ifstream in("tape.txt");
    getline(in, tape);
}

void run()
{
    string cur_state = start_state;
    int cur_tape_idx = 0;

    for (;;)
    {
        ++steps_count;

#ifdef DEBUG_MODE
        cout << "Cur state: " << cur_state << "; cur_tape_idx: " << cur_tape_idx << "; ";
#endif

        if ( accepting_states.find(cur_state) != accepting_states.end() )
        {
            cout << "Program reached accepting state." << endl;
            accepted = true;
            break; // stop the machine
        }

        if ( rejecting_states.find(cur_state) != rejecting_states.end() || cur_tape_idx < 0 )
        {
            cout << "Program reached rejecting state." << endl;
            accepted = false;
            break;
        }

        char cur_char_on_tape = getCharOnTape(cur_tape_idx);

#ifdef DEBUG_MODE
        cout << "cur_char = \"" << cur_char_on_tape << "\"; ==> ";
#endif

        if ( sigma.find(make_pair(cur_state, cur_char_on_tape)) == sigma.end() )
        {
            accepted = false;
            cout << "Warning: there is no transaction of type"
                    " [\"" << cur_state << "\"][" << cur_char_on_tape << "]! "
                    "Check your program.txt!" << endl;
            break;
        }

        auto tpl = sigma[make_pair(cur_state, cur_char_on_tape)];

#ifdef DEBUG_MODE
        cout << "new_state = " << std::get<0>(tpl) << "; new_char = " << std::get<1>(tpl) << ";" << endl;
#endif

        cur_state          = std::get<0>(tpl); // new state
        tape[cur_tape_idx] = std::get<1>(tpl); // new char

        cur_tape_idx      += std::get<2>(tpl); // step
    }
}

void printResults()
{
    ofstream out("output.txt");

    if (accepted)
        out << "accepted" << endl;
    else
        out << "rejected" << endl;

    while (tape.size() > 0 && tape[tape.size() - 1] == '_')
        tape = tape.substr(0, tape.size() - 1);

    for (int i = tape.size(); i >= 0; --i)
        if (tape[i] == '>')
        {
            tape = tape.substr(i);
            break;
        }

    out << tape << endl;

    out << "Program finished in " << steps_count << " iterations." << endl;
}

int main()
{
    readProgram();
    readTape();
    run();
    printResults();

    return 0;
}

