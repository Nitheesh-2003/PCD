#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<string> splitBy(string s, char x)
{
    vector<string> result;
    string tmp = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '/')
        {
            result.push_back(tmp);
            tmp = "";
        }
        else
        {
            tmp += s[i];
        }
    }
    result.push_back(tmp);
    return result;
}

int main()
{
    int i, j, k, n;
    cout << "Enter the number of productions in the Grammer (The grammer must not contain Left Recursion): ";
    cin >> n;
    cout << "Enter the productions of the Grammer :\nOnly Use Capital alphabets for Non-Terminals(Ex: A, B, E). Don't use A', B', E'\nFor denoting the epsilon use '?'.\nUse any characters other than 'id' for terminals.\n";
    map<char, vector<string>> productions;
    vector<char> nonTerminals;
    string s;
    for (i = 0; i < n; i++)
    {
        cin >> s;
        string rightSide = "";
        for (j = 3; j < s.length(); j++)
        {
            rightSide += s[j];
        }
        vector<string> rightSideOfProduction = splitBy(rightSide, '/');
        productions[s[0]] = rightSideOfProduction;
        nonTerminals.push_back(s[0]);
    }

    vector<string> firstPass(n);
    vector<string> followPass(n);
    cout << "\nEnter First Values :\n";
    for (i = 0; i < nonTerminals.size(); i++)
    {
        cout << "First [" << nonTerminals[i] << "] : ";
        cin >> firstPass[i];
    }
    cout << "\nEnter Follow Values :\n";
    for (i = 0; i < nonTerminals.size(); i++)
    {
        cout << "Follow [" << nonTerminals[i] << "] : ";
        cin >> followPass[i];
    }
    string first, follow;
    bool isEpsilonPresent;
    cout << "\nPredictive Parser - Parse Table : \n";
    for (i = 0; i < nonTerminals.size(); i++)
    {
        first = firstPass[i];
        isEpsilonPresent = false;
        for (j = 0; j < first.length(); j++)
        {
            if (first[j] == '?')
                isEpsilonPresent = true;
            else
            {
                cout << "M[" << nonTerminals[i] << "," << first[j] << "] = " << nonTerminals[i] << "->";
                bool flag = false;
                for (k = 0; k < productions[nonTerminals[i]].size(); k++)
                {
                    if (productions[nonTerminals[i]][k][0] == first[j])
                    {
                        cout << productions[nonTerminals[i]][k] << endl;
                        flag = true;
                        break;
                    }
                }
                if (!flag)
                {
                    cout << productions[nonTerminals[i]][0] << endl;
                }
            }
            if (isEpsilonPresent)
            {
                follow = followPass[i];
                for (k = 0; k < follow.length(); k++)
                {
                    cout << "M[" << nonTerminals[i] << "," << follow[k] << "] = " << nonTerminals[i] << "->?" << endl;
                }
            }
        }
    }
    return 0;
}


/* OUTPUT
Enter the number of productions in the Grammer (The grammer must not contain Left Recursion): 5
Enter the productions of the Grammer :
Only Use Capital alphabets for Non-Terminals(Ex: A, B, E). Don't use A', B', E'
For denoting the epsilon use '?'.
Use any characters other than 'id' for terminals.
E->TX
X->+TX/?
T->FY
Y->*FY/?
F->(E)/i
Enter First Values :
First [E] : (i
First [X] : +?
First [T] : (i
First [Y] : *?
First [F] : (i
Enter Follow Values :
Follow [E] : $)
Follow [X] : $)
Follow [T] : +$)
Follow [Y] : +$)
Follow [F] : *+$)

Prompt the user for number of productions of the grammar.
: Prompt the user for the productions of the grammar.
: Prompt the user for the values of first pass and follow pass of all the non
terminals present in the given grammar.
: Declare a variable for storing the parse table M.
: Traverse all the non terminals one by one and store the values of parse table
M according to the following conditions.
: For all the terminals 't', present in the first pass of a non terminal 'X' store
M(X,t) = "production of X containing t".
: If the first pass of the non terminal consist of epsilon then for all the terminals
'a' present in the follow pass of the non terminal 'X', store M(X, a) = "X-
>epsilon".
: Display the values of the parse table M.
*/