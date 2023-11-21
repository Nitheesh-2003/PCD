#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

string CPof(string a, string b)
{
    string cp = "";
    int minLen = min(a.length(), b.length()), i = 0;
    while (i < minLen && a[i] == b[i])
    {
        cp += a[i];
        i++;
    }
    return cp;
}

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
    string s;
    cout << "Enter a production of the grammer : \n";
    // Input is of the form A->Ax/y
    cin >> s;
    string leftSide, rightSide = "";
    leftSide = s[0];
    for (i = 3; i < s.length(); i++)
    {
        rightSide += s[i];
    }
    vector<string> rightSideOfProduction = splitBy(rightSide, '/');
    sort(rightSideOfProduction.begin(), rightSideOfProduction.end());

    vector<int> mergingProducts;
    string commonPrefix = "", tmpcp;
    map<vector<int>, string> productsCPmapping;
    for (i = 0; i < rightSideOfProduction.size(); i++)
    {
        if (commonPrefix == "" && (i != rightSideOfProduction.size() - 1))
        {
            tmpcp = CPof(rightSideOfProduction[i], rightSideOfProduction[i + 1]);
            if (tmpcp == "")
            {
                if (commonPrefix == "")
                    continue;
                productsCPmapping[mergingProducts] = commonPrefix;
                mergingProducts.clear();
                commonPrefix = "";
            }
            else
            {
                mergingProducts.push_back(i);
                mergingProducts.push_back(i + 1);
                commonPrefix = tmpcp;
                i++;
            }
        }
        else
        {
            tmpcp = CPof(commonPrefix, rightSideOfProduction[i]);
            if (tmpcp == "")
            {
                productsCPmapping[mergingProducts] = commonPrefix;
                mergingProducts.clear();
                commonPrefix = "";
                i--;
            }
            else
            {
                mergingProducts.push_back(i);
                commonPrefix = tmpcp;
            }
        }
    }
    if (commonPrefix != "")
    {
        productsCPmapping[mergingProducts] = commonPrefix;
    }

    vector<string> alphas;
    vector<string> betas;
    vector<bool> isMerged(rightSideOfProduction.size(), false);
    for (auto &x : productsCPmapping)
    {
        alphas.push_back(x.second);
    }

    for (auto &x : productsCPmapping)
    {
        for (i = 0; i < x.first.size(); i++)
        {
            isMerged[x.first[i]] = true;
            if (rightSideOfProduction[x.first[i]].size() <= x.second.length())
                betas.push_back("Epsilon");
            else
                betas.push_back(rightSideOfProduction[x.first[i]].substr(x.second.length()));
        }
    }

    for (i = 0; i < alphas.size(); i++)
    {
        alphas[i] += (leftSide + "'");
    }

    for (i = 0; i < isMerged.size(); i++)
    {
        if (!isMerged[i])
        {
            alphas.push_back(rightSideOfProduction[i]);
        }
    }

    map<string, vector<string>> resultantProductions;

    resultantProductions[leftSide] = alphas;
    resultantProductions[leftSide + "'"] = betas;
    cout << "Resultant Productions after performing Left Factoring : \n";
    for (auto &x : resultantProductions)
    {
        cout << x.first << " -> ";
        for (i = 0; i < x.second.size(); i++)
        {
            cout << x.second[i];
            if (i != x.second.size() - 1)
                cout << " / ";
        }
        cout << endl;
    }
    return 0;
}



// Enter a production of the grammer : 
// E->i+T/i-T
// Resultant Productions after performing Left Factoring :
// E -> iE'
// E' -> +T / -T

// Prompt the user for a production of the grammar.
// : Find the common prefix present in the right side of the productions of the
// grammar(say c).
// : Compute the new productions using the following condition. If the production
// is of the form X->ca/cb/d/e, then the new productions after performing left
// factoring will be
// A->cA’/d/e
// A’->a/b
// : Repeat steps 2 and 3 until all the common prefixes are not removed from the
// given grammar.
// : Display the new productions after performing Left Factoring in the given
// Context Free Grammar.