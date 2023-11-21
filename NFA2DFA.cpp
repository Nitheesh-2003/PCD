#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;

int main()
{
    int noOfStates, noOfInputSymbols, initialState, noOfFinalStates, tmp;
    int i, j;

    cout << "\n\t********************      NFA to DFA      ********************\n\n";
    cout << "Enter the no of states : ";
    cin >> noOfStates;
    cout << "Enter the no of input symbols : ";
    cin >> noOfInputSymbols;
    cout << "(Note: If number of states is 4 then the states are taken as 0, 1, 2, 3.\nSimilarly if number of inputs is 4 then the inputs are taken as 0, 1, 2, epsilon.)\n";
    cout << "If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.\n";
    cout << "Similarly if the input symbols are a,b,c then map the characters to integers as a->0, b->1, c->2\n";
    cout << "Using the above mapping give the following inputs as integer only!!!\n"
         << endl;
    cout << "Enter the Initial State : ";
    cin >> initialState;
    cout << "Enter the number of final States : ";
    cin >> noOfFinalStates;

    vector<int> isFinalState(noOfStates, false);

    cout << "Enter " << noOfFinalStates << " final States : " << endl;
    for (i = 0; i < noOfFinalStates; i++)
    {
        cout << "Final State " << i + 1 << " : ";
        cin >> tmp;
        isFinalState[tmp] = true;
    }

    vector<vector<vector<int>>> nfatt(noOfStates, vector<vector<int>>(noOfInputSymbols));

    cout << "Enter the transition table (Enter '-1' for null transition and also for terminating a transition for a given state and a given input)\n\n";

    for (i = 0; i < noOfStates; i++)
    {
        cout << "Enter the transitions for the state " << i << " : " << endl
             << endl;
        for (j = 0; j < noOfInputSymbols; j++)
        {
            cout << "State " << i << " on input " << j << " takes transition to \n";
            do
            {
                cin >> tmp;
                if (tmp != -1)
                    nfatt[i][j].push_back(tmp);
            } while (tmp != -1);
            if (nfatt[i][j].size() == 0)
                nfatt[i][j].push_back({-1});
            cout << endl;
        }
    }

    queue<set<int>> q;
    map<set<int>, bool> visited;
    set<int> currState;
    map<set<int>, map<int, set<int>>> dfatt;
    map<set<int>, bool> isFinalStateInDfa;
    bool finalInDfa;
    set<int> initialStateInDfa = {initialState};
    int newState = noOfStates;

    q.push(initialStateInDfa);

    while (!q.empty())
    {
        currState = q.front();
        q.pop();
        if (!visited[currState])
        {
            visited[currState] = true;
            for (i = 0; i < noOfInputSymbols; i++)
            {
                set<int> s;
                finalInDfa = false;
                for (auto &x : currState)
                {
                    if (x == newState)
                        continue;
                    for (auto &y : nfatt[x][i])
                    {
                        if (y == -1)
                            continue;
                        if (isFinalState[y])
                            finalInDfa = true;
                        s.insert(y);
                    }
                }
                if (s.empty())
                    s.insert(newState);
                if (finalInDfa)
                {
                    isFinalStateInDfa[s] = true;
                }
                dfatt[currState][i] = s;
                q.push(s);
            }
        }
    }

    cout << "\n\t-------------------       TRANSITION TABLE OF EQUIVALENT DFA        -------------------\n\n";
    cout << "\t";
    for (i = 0; i < noOfInputSymbols; i++)
    {
        cout << "\t" << i;
    }
    cout << endl;
    set<int> transitions;
    for (auto &x : dfatt)
    {
        currState = x.first;
        if (currState == initialStateInDfa)
            cout << "->";
        if (isFinalStateInDfa[currState])
            cout << "*";
        cout << "\t";
        for (auto &y : currState)
            cout << y;
        for (i = 0; i < noOfInputSymbols; i++)
        {
            transitions = dfatt[x.first][i];
            cout << "\t";
            for (auto &z : transitions)
            {
                cout << z;
            }
        }
        cout << endl;
    }

    return 0;
}

/*
Enter the no of states : 4
Enter the no of input symbols : 2
(Note: If number of states is 4 then the states are taken as 0, 1, 2, 3.
Similarly if number of inputs is 4 then the inputs are taken as 0, 1, 2, epsilon.)
If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.
Similarly if the input symbols are a,b,c then map the characters to integers as a->0, b->1, c->2
Using the above mapping give the following inputs as integer only!!!

Enter the Initial State : 0
Enter the number of final States : 2
Enter 2 final States : 
Final State 1 : 2
Final State 2 : 3
Enter the transition table (Enter '-1' for null transition and also for terminating a transition for a given state and a given input)

Enter the transitions for the state 0 : 

State 0 on input 0 takes transition to 
0
-1
State 0 on input 1 takes transition to 
3
1
-1
Enter the transitions for the state 1 : 

State 1 on input 0 takes transition to 
1
-1
State 1 on input 1 takes transition to 
2
1
-1
Enter the transitions for the state 2 : 

State 2 on input 0 takes transition to 
2
-1
State 2 on input 1 takes transition to 
3
2
-1
Enter the transitions for the state 3 : 

State 3 on input 0 takes transition to 
2
-1
State 3 on input 1 takes transition to 
-1

Prompt the user for the number of states, number of input symbols, initial and
final states and the transition table of the NFA with epsilon moves.
: Find epsilon closure of each states given and store it in a variable.
: For each given state and for each given input find its transition in NFA without
epsilon moves using the below formula.
Transition_In_NFA_Without_Epsilon_Moves(q,a)=
epsilon closure(TransitionInNFAWithEpsilonMoves(epsilon closure(q), a))
: The number of states, the states and the initial state will be the same.
: The Input Symbols will also be the same excluding the epsilon.
: If the epsilon closure of a state contains a final state then mark that state as a
final state.
: Display the transition table of NFA and display the initial and final states of it.

*/