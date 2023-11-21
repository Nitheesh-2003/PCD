#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstring>
using namespace std;

int main()
{
    int noOfStates, noOfInputSymbols, initialState, noOfFinalStates, tmp;
    int i, j, k;
    cout << "\n\t********************      NFA WITH EPSILON MOVES to NFA      ********************\n\n";
    cout << "Enter the no of states : ";
    cin >> noOfStates;
    cout << "Enter the no of input symbols including epsilon : ";
    cin >> noOfInputSymbols;
    cout << "(Note: If number of states is 4 then the states are taken as 0, 1, 2, 3.\nSimilarly if number of inputs is 4 then the inputs are taken as 0, 1, 2, epsilon.)\n";
    cout << "If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.\n";
    cout << "Similarly if the input symbols are a,b,c then map the characters to integers as a->0, b->1, c->2\n";
    cout << "Using the above mapping give the following inputs as integer only!!!" << endl;
    cout << "Enter the Initial State : ";
    cin >> initialState;
    cout << "Enter the number of final States : ";
    cin >> noOfFinalStates;

    vector<int> isFinalState(noOfStates, false);
    vector<int> isFinalStateInNFA(noOfStates, false);
    int epsilon = noOfInputSymbols - 1;

    cout << "Enter " << noOfFinalStates << " final States : " << endl;
    for (i = 0; i < noOfFinalStates; i++)
    {
        cout << "Final State " << i + 1 << " : ";
        cin >> tmp;
        isFinalState[tmp] = true;
    }

    //

    vector<vector<string>> enfatt(noOfStates, vector<string>(noOfInputSymbols, "-1"));
    vector<vector<string>> nfatt(noOfStates, vector<string>(noOfInputSymbols - 1, "-1"));
    string tmpstr;

    cout << "\nEnter the values of transition table ( Enter -1 for empty transition and also for terminating the input for a given state and input)\n\n";
    for (i = 0; i < noOfStates; i++)
    {
        cout << "Enter transitions for the state " << i << " : \n";
        for (j = 0; j < noOfInputSymbols; j++)
        {
            tmpstr = "";
            do
            {
                if (j == noOfInputSymbols - 1)
                    cout << "State " << i << " on input (epsilon) takes transition to : ";
                else
                    cout << "State " << i << " on input " << j << " takes transition to : ";
                cin >> tmp;
                if (tmp != -1)
                    tmpstr += to_string(tmp);
            } while (tmp != -1);
            cout << endl;
            if (tmpstr == "")
                tmpstr = "-1";
            enfatt[i][j] = tmpstr;
        }
    }

    unordered_map<int, string> epsilon_closure;
    queue<int> q;
    string eclosure;
    for (i = 0; i < noOfStates; i++)
    {
        eclosure = "";
        q.push(i);

        while (!q.empty())
        {
            tmp = q.front();
            q.pop();
            eclosure += to_string(tmp);
            if (isFinalState[tmp])
                isFinalStateInNFA[i] = true;
            tmpstr = enfatt[tmp][epsilon];
            if (tmpstr != "-1")
            {
                for (j = 0; j < tmpstr.length(); j++)
                {
                    q.push(tmpstr[j] - '0');
                }
            }
        }

        epsilon_closure[i] = eclosure;
    }

    for (i = 0; i < noOfStates; i++)
    {
        for (j = 0; j < noOfInputSymbols - 1; j++)
        {
            eclosure = epsilon_closure[i];
            string transition = "", newTransition = "";
            for (k = 0; k < eclosure.length(); k++)
            {
                if (enfatt[eclosure[k] - '0'][j] != "-1")
                    transition += (enfatt[eclosure[k] - '0'][j]);
            }
            for (k = 0; k < transition.length(); k++)
            {
                if (epsilon_closure[transition[k] - '0'] != "-1")
                    newTransition += (epsilon_closure[transition[k] - '0']);
            }
            string withoutDuplicate = "";
            if (newTransition == "")
                withoutDuplicate = "-1";
            else
            {
                // remove duplicates
                unordered_map<char, bool> isPresent;

                for (k = 0; k < newTransition[k]; k++)
                {
                    if (!isPresent[newTransition[k]])
                        withoutDuplicate += newTransition[k];
                    isPresent[newTransition[k]] = true;
                }
            }
            nfatt[i][j] = withoutDuplicate;
        }
    }

    cout << "\n\n\t--------------------      TRANSITION TABLE OF EQUIVALENT NFA      --------------------\n\n";
    cout << "\t";
    for (i = 0; i < noOfInputSymbols - 1; i++)
    {
        cout << "\t" << i;
    }
    cout << endl;
    for (i = 0; i < noOfStates; i++)
    {
        if (initialState == i)
            cout << "->";
        if (isFinalStateInNFA[i])
            cout << "*";
        cout << "\t" << i;
        for (j = 0; j < noOfInputSymbols - 1; j++)
        {
            cout << "\t";
            if (nfatt[i][j] == "-1")
                cout << "-1";
            else
            {
                for (k = 0; k < nfatt[i][j].length(); k++)
                {
                    cout << nfatt[i][j][k];
                    if (k != nfatt[i][j].length() - 1)
                        cout << ",";
                }
            }
        }
        cout << endl;
    }

    return 0;
}
/*NFA WITH EPSILON MOVES to NFA      ********************


        ********************      NFA WITH EPSILON MOVES to NFA      ********************

Enter the no of states : 4
Enter the no of input symbols including epsilon : 3
(Note: If number of states is 4 then the states are taken as 0, 1, 2, 3.
Similarly if number of inputs is 4 then the inputs are taken as 0, 1, 2, epsilon.)
If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.
Similarly if the input symbols are a,b,c then map the characters to integers as a->0, b->1, c->2
Using the above mapping give the following inputs as integer only!!!
Enter the Initial State : 0
Enter the number of final States : 1
Enter 1 final States :
Final State 1 : 3

Enter the values of transition table ( Enter -1 for empty transition and also for terminating the input for a given state and input)

Enter transitions for the state 0 :
State 0 on input 0 takes transition to : 0
State 0 on input 0 takes transition to : -1

State 0 on input 1 takes transition to : -1

State 0 on input (epsilon) takes transition to : 1
State 0 on input (epsilon) takes transition to : -1

Enter transitions for the state 1 :
State 1 on input 0 takes transition to : 2
State 1 on input 0 takes transition to : -1

State 1 on input 1 takes transition to : -1

State 1 on input (epsilon) takes transition to : 3
State 1 on input (epsilon) takes transition to : -1

Enter transitions for the state 2 :
State 2 on input 0 takes transition to : -1

State 2 on input 1 takes transition to : 1
State 2 on input 1 takes transition to : -1

State 2 on input (epsilon) takes transition to : -1

Enter transitions for the state 3 :
State 3 on input 0 takes transition to : 3
State 3 on input 0 takes transition to : -1

State 3 on input 1 takes transition to : -1

State 3 on input (epsilon) takes transition to : -1


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