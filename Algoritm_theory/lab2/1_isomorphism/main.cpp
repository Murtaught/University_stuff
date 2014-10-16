#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct DFA
{
    struct State
    {
        void addTransition(char c, int where)
        {
            transitions_[c] = where;
        }

        bool final_;
        std::map<char, int> transitions_;
    };

    int n_, m_, k_;
    std::vector<State> states_;

public:
    void readAutomaton(istream &in)
    {
        in >> n_ >> m_ >> k_;

        states_.resize(n_ + 1);

        for (int i = 0; i < k_; ++i)
        {
            int idx; in >> idx;
            states_[idx].final_ = true;
        }

        for (int i = 0; i < m_; ++i)
        {
            int a, b;
            char c;
            in >> a >> b >> c;

            states_[a].addTransition(c, b);
        }
    }
};

struct IsomorphismChecker
{
    IsomorphismChecker(const DFA &a, const DFA &b)
        : a_(a),
          b_(b),
          permutation_(a_.n_ + 1, -1),
          was_(a_.n_ + 1, false),
          solved_(false),
          answer_(false)
    {
        permutation_[0] = 0;
        permutation_[1] = 1;
    }

    void dfs(int a_idx)
    {
        if (was_[a_idx] || solved_)
            return;
        was_[a_idx] = true;

        int b_idx = permutation_[a_idx];
        std::map<char, int> const& a_map = a_.states_[a_idx].transitions_;
        std::map<char, int> b_map_copy = b_.states_[b_idx].transitions_;

        for (std::map<char, int>::const_iterator it = a_map.begin(); it != a_map.end(); ++it)
        {
            char cur_char = it->first;
            int a_dest = it->second;
            int b_dest = b_map_copy[cur_char];

            if (b_dest == 0 || (permutation_[a_dest] != -1 && permutation_[a_dest] != b_dest))
            {
                solved_ = true;
                answer_ = false;
                return;
            }

            b_map_copy.erase(cur_char);
            permutation_[a_dest] = b_dest;
            dfs(a_dest);
        }

        if (!b_map_copy.empty() || a_.states_[a_idx].final_ != b_.states_[a_idx].final_)
        {
            solved_ = true;
            answer_ = false;
        }
    }

    bool isIsomorphic()
    {
        if (!solved_)
        {
            if (a_.n_ != b_.n_ || a_.m_ != b_.m_ || a_.k_ != b_.k_)
                answer_ = false;
            else
            {
                answer_ = true;
                dfs(1);
            }

            solved_ = true;
        }

        return answer_;
    }

    const DFA &a_;
    const DFA &b_;
    std::vector<int> permutation_;
    std::vector<bool> was_;
    bool solved_;
    bool answer_;
};

int main()
{
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);

    DFA a1, a2;
    a1.readAutomaton(cin);
    a2.readAutomaton(cin);

    IsomorphismChecker checker(a1, a2);

    if ( checker.isIsomorphic() )
        cout << "YES";
    else
        cout << "NO";

    return 0;
}

