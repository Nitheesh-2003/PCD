#include <iostream>
#include <vector>
#include <map>
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
    int i;
    cout << "Enter a production of the grammer : " << endl;
    string s;
    // Input is of the form A->Ax/y
    cin >> s;
    string leftSide, rightSide = "";
    leftSide = s[0];
    for (i = 3; i < s.length(); i++)
    {
        rightSide += s[i];
    }
    vector<string> rightSideOfProduction = splitBy(rightSide, '/');
    bool isLeftRecursionPresent = false;
    for (i = 0; i < rightSideOfProduction.size(); i++)
    {
        if (rightSideOfProduction[i][0] == leftSide[0])
        {
            isLeftRecursionPresent = true;
            break;
        }
    }
    if (!isLeftRecursionPresent)
    {
        cout << "Left Recursion is not present in the given grammer";
        return 0;
    }

    vector<string> alphas;
    vector<string> betas;
    for (i = 0; i < rightSideOfProduction.size(); i++)
    {
        if (rightSideOfProduction[i][0] == leftSide[0])
        {
            alphas.push_back(rightSideOfProduction[i].substr(1));
        }
        else
        {
            betas.push_back(rightSideOfProduction[i]);
        }
    }

    map<string, vector<string>> resultantProductions;

    for (i = 0; i < betas.size(); i++)
    {
        betas[i] += (leftSide + "'");
    }
    for (i = 0; i < alphas.size(); i++)
    {
        alphas[i] += (leftSide + "'");
    }
    alphas.push_back("Epsilon");
    resultantProductions[leftSide] = betas;
    resultantProductions[leftSide + "'"] = alphas;
    cout << "Resultant production after eliminating Left Recursion : \n";
    for (auto &x : resultantProductions)
    {
        cout << x.first << " -> ";
        for (i = 0; i < x.second.size(); i++)
        {
            cout << x.second[i] << " ";
            if (i != x.second.size() - 1)
                cout << " / ";
        }
        cout << endl;
    }
    return 0;
}
/*
Enter a production of the grammer : 
E->E+T/T
Resultant production after eliminating Left Recursion : 
E -> TE' 
E' -> +TE'  / Epsilon 

Prompt the user for a production of the grammar.
: Check whether left recursion is present in the given grammar.
: If not present then display, “Left Recursion is not present in the given
grammar” and terminate the program.
: Else, Compare the given grammar with the general form ‘A->Ax/y’ and find
the value of x and the value of y.
: Find the new productions after the elimination of left recursion. The new
productions will be of the form,
A->yA’
A’->xA’/Epsilon
: Display the new productions after the elimination of the left recursion.
*/