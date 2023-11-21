#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int noOfStates, noOfInputSymbols, initialState, noOfFinalStates;
    int i, j, tmp;
    cout << "\n\t*********************      ACCEPTENCE OF STRING BY DFA      *********************\n\n";
    cout << "Enter the number of states : ";
    cin >> noOfStates;
    cout << "Enter the number of input symbols : ";
    cin >> noOfInputSymbols;

    cout << "(Note: If number of states are 4 then the states are taken as 0, 1, 2, 3\n";
    cout << "Similarly if number of inputs are 4 then the inputs are taken as 0, 1, 2, 3.)\n";
    cout << "If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.\n";
    cout << "Similarly if the inputs are a,b,c then map the characters to integers as a->0, b->1, c->2\n";
    cout << "Using the above mapping give the following inputs as integer only!!!\n"
         << endl;

    cout << "Enter the Initial State : ";
    cin >> initialState;
    cout << "Enter the number of final states : ";
    cin >> noOfFinalStates;
    vector<bool> isFinal(noOfFinalStates, false);
    for (i = 0; i < noOfFinalStates; i++)
    {
        cout << "Enter final state " << i + 1 << " : ";
        cin >> tmp;
        isFinal[tmp] = true;
    }
    vector<vector<int>> transitionTable(noOfStates, vector<int>(noOfInputSymbols));
    cout << endl;
    for (i = 0; i < noOfStates; i++)
    {
        cout << "Enter transitions for the state " << i << " : \n";
        for (j = 0; j < noOfInputSymbols; j++)
        {
            cout << "The state " << i << " on input " << j << " takes transition to ";
            cin >> transitionTable[i][j];
        }
        cout << endl;
    }

    string s;
    cout << "Enter the string to be validated : ";
    cin >> s;

    int currState = initialState;
    for (i = 0; i < s.length(); i++)
    {
        currState = transitionTable[currState][s[i] - '0'];
    }
    cout << endl;
    if (isFinal[currState])
    {
        cout << "The string " << s << " is ACCEPTED by the given DFA";
    }
    else
    {
        cout << "The string " << s << " is NOT ACCEPTED by the given DFA";
    }

    return 0;
}

// /tmp/deISrI4fg9.o
// *********************      ACCEPTENCE OF STRING BY DFA      *********************

/*
Enter the number of states : 3
Enter the number of input symbols : 2
(Note: If number of states are 4 then the states are taken as 0, 1, 2, 3
Similarly if number of inputs are 4 then the inputs are taken as 0, 1, 2, 3.)
If the states are A,B,C then map the characters to integers as A->0, B->1, C->2.
Similarly if the inputs are a,b,c then map the characters to integers as a->0, b->1, c->2
Using the above mapping give the following inputs as integer only!!!

Enter the Initial State : 0
Enter the number of final states : 1
Enter final state 1 : 1
Enter transitions for the state 0 : 
The state 0 on input 0 takes transition to 0
The state 0 on input 1 takes transition to 1
Enter transitions for the state 1 : 
The state 1 on input 0 takes transition to 2
The state 1 on input 1 takes transition to 0
Enter transitions for the state 2 : 
The state 2 on input 0 takes transition to 0
The state 2 on input 1 takes transition to 2
Enter the string to be validated : 101101
The string 101101 is ACCEPTED by the given DFA

Enter the Initial State : 0
Enter the number of final states : 1
Enter final state 1 : 1
Enter transitions for the state 0 : 
The state 0 on input 0 takes transition to 0
The state 0 on input 1 takes transition to 1
Enter transitions for the state 1 : 
The state 1 on input 0 takes transition to 2
0The state 1 on input 1 takes transition to 0
Enter transitions for the state 2 : 
The state 2 on input 0 takes transition to 0
The state 2 on input 1 takes transition to 2
Enter the string to be validated : 111111
The string 111111 is NOT ACCEPTED by the given DFA */

/* Prompt the user for the number of states, number of input symbols, the initial
and final states and the transition table of DFA.
: Prompt the user for the string to be validated for recognition by the DFA.
: Start from the initial state.
: Determine the transition state by applying the input symbol from the string to
the current state and move to that state.
: Repeat Step 4 for each input symbol in the given string, following the order
as presented in the string.
: If the current state is a final state then display, “The given string is accepted
by the given DFA”.
: If the current state is a non final state then display, “The given string is not
accepted by the given DFA”.*/