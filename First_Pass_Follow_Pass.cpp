#include <stdio.h>
#include <string.h>
#include <ctype.h>
int nop, m = 0, n=0, p, i = 0, j = 0;
char prod[10][10], res[10], firstRes[10];
void FOLLOW(char c);
void first(char c);
void result(char);
void firstResult(char);
int main()
{
    int i;
    int choice;
    char c, ch;
    printf("Enter the production string like E=E+T\nIf the production is of the form A->aX/b then consider it as two productions and give input as\nA->aX and A->b\n");
    printf("Enter the no.of productions: ");
    scanf("%d", &nop);
    
    for (i = 0; i < nop; i++)
    {
        printf("Enter productions Number %d : ", i + 1);
        scanf(" %s", prod[i]);
    }
    
        n = 0;
        printf("\nFind FIRST of --> ");
        scanf(" %c", &c);
        first(c);
        printf("FIRST(%c) = { ", c);
        for (i = 0; i < n; i++)
        {
            printf("%c ", res[i]);
            if(i+1 != n) printf(" , ");
        }
        printf(" }\n");

		for(i=0;i<n;i++)
		{
			res[i] = '\0';
		}

		m = 0;
        printf("\nFind FOLLOW of --> ");
        scanf(" %c", &c);
        res[m++] = '*';
        FOLLOW(c);
        printf("FOLLOW(%c) = { ", c);
        for (i = 0; i < m; i++)
        {
            printf("%c ", res[i]);
            if(i+1 != m) printf(" , ");
        }
        printf(" }\n");
        
    
}
void FOLLOW(char c)
{
    if (prod[0][0] == c)
        result('$');
    for (i = 0; i < nop; i++)
    {
        for (j = 2; j < strlen(prod[i]); j++)
        {
            if (prod[i][j] == c)
            {
                if (prod[i][j + 1] != '\0')
                    first(prod[i][j + 1]);
                if (prod[i][j + 1] == '\0' && c != prod[i][0])
                    FOLLOW(prod[i][0]);
            }
        }
    }
}
void first(char c)
{
    int k;
    if (!(isupper(c)))
    {
    	firstResult(c);
        result(c);
    }
    for (k = 0; k < nop; k++)
    {
        if (prod[k][0] == c)
        {
            if (prod[k][2] == '$')
            {
                FOLLOW(prod[i][0]);
            }
            else if (islower(prod[k][2]))
            {
            	firstResult(prod[k][2]);
                result(prod[k][2]);
            }
            else if(prod[k][2] == prod[k][0])
            {
            	continue;
			}
            else
            {
                first(prod[k][2]);
            }
        }
    }
}
void result(char c)
{
    int i;
    for (i = 0; i <= m; i++)
        if (res[i] == c)
            return;
    res[m++] = c;
}

void firstResult(char c)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(firstRes[i] == c)
			return;
	}
	firstRes[n++] = c;
}

/*
Enter the production string like E=E+T
If the production is of the form A->aX/b then consider it as two productions and give input as
A->aX and A->b
Enter the no.of productions: 6
Enter productions Number 1 : E=E+T
Enter productions Number 2 : E=T
Enter productions Number 3 : T=T*F
Enter productions Number 4 : T=F
Enter productions Number 5 : F=(E)
Enter productions Number 6 : F=i

Find FIRST of --> E
FIRST(E) = { (  , i  }

Find FOLLOW of --> F
FOLLOW(F) = { *  , $  , +  , )  }

Prompt the user for the number of productions in the grammar. 
Prompt the user for the productions of the grammar. 
First Pass(x)=x, where x is a terminal or where x is epsilon. 
Traverse the productions one by one and calculate the values of First Passusing the below conditions. 
If the production is of the form X->aB then FirstPass(X) = a, where“a” isaterminal. 
If the production is of the form X->ABC, then FirstPass(X) = FirstPass(A)ifFirstPass(A) doesn’t have epsilon , else FirstPass(X) =     
 FirstPass(A) unionFirstPass(B) if FirstPass(B) doesn’t have epsilon, else FirstPass(X)=FirstPass(A) union FirstPass(B) union FirstPass(C). 
If first pass of all the non terminals is not computed, then goto Step-4. 
Display the computed values of first pass for all the non terminalspresent inthe given grammar.
*/