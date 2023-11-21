#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, tmp;
    cout << "Enter an arithmetic expression : \n";
    cin >> s;
    char tempVariable = 'a';
    char operators[] = {'/', '*', '+', '-'};
    cout << "Operator\tArgument 1\tArgument 2\tResult\n";
    int i, j;
    for (i = 0; i < s.length(); i++)
    {
        if (s[i] == '-' && (s[i - 1] < 'a' || s[i - 1] > 'z'))
        {
            cout << "-\t\t" << s[i + 1] << "\t\t\t\t" << tempVariable << endl;
            s = s.substr(0, i) + tempVariable + s.substr(i + 2);
            tempVariable++;
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < s.length(); j++)
        {
            if (s[j] == operators[i])
            {
                cout << operators[i] << "\t\t" << s[j - 1] << "\t\t" << s[j + 1] << "\t\t" << tempVariable << endl;
                s = s.substr(0, j - 1) + tempVariable + s.substr(j + 2);
                tempVariable++;
            }
        }
    }

    for (i = 0; i < s.length(); i++)
    {
        if (s[i] == '=')
        {
            cout << "=\t\t" << s[i + 1] << "\t\t\t\t" << s[i - 1] << endl;
            s = s.substr(0, i - 1) + s[i - 1] + s.substr(i + 2);
        }
    }
    return 0;
}

/*  Enter a arithmetic expression : 
A=-B*C+B*C

Prompt the user for an arithmetic expression.
: Traverse the expression for finding the negation operation.
: If found, perform negation operation and store the result in a temporary
variable and use that variable instead of that negation operation. Display the
intermediate code.
: Repeat Steps 2 and 3 until all the negation operations are not eliminated from
the expression.
: Traverse the expression for division operation. If found, perform division
operation and store the result in a temporary variable and use that variable
instead of that operation. Display the intermediate code.
: Repeat step 5 until all the division operations are not eliminated.
: Repeat step 5 and 6 for the operators *, + and - respectively.
: Traverse the expression for the assignment operator, if present store the
value of right side variable in the left side variable. Display the intermediate
code.
: Thus the intermediate code for the given arithmetic expression is generated
successfully.
*/
