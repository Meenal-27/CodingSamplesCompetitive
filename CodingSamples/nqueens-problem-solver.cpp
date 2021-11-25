#include <bits/stdc++.h>



void add(vector <vector<string>> &sol,vector<string> str, int i, vector <int> leftdiag, vector<int> rightdiag, vector <int> cols,int A)
{
    if(i==A) {sol.push_back(str);return;}
    else
    {
        for(int j=0;j<A;j++)
        {
            if(cols[j]!=1)continue;
            else if(leftdiag[i-j+A-1]!=1) continue;
            else if(rightdiag[i+j]!=1)continue;
            else
            {
                //cout<<"hi"<<" "<<i<<" "<<j<<endl;
                string g;
                for(int k=0;k<j;k++)
                {
                    g.push_back('.');    
                }
                g.push_back('Q');
                for(int k=j+1;k<A;k++)
                {
                    g.push_back('.');
                }
                cols[j]=0;
                leftdiag[i-j+A-1]=0;
                rightdiag[i+j]=0;
                str.push_back(g);
                add(sol,str,i+1,leftdiag,rightdiag,cols, A);
                str.pop_back();
                cols[j]=1;
                leftdiag[i-j+A-1]=1;
                rightdiag[i+j]=1;
            }
        }
    }
}


vector<vector<string> > Solution::solveNQueens(int A) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

    vector <vector<string>> sol;
    vector <string> empty;
    vector <int> left(2*A-1,1);
    vector <int> right(2*A-1,1);
    vector <int> cols(A, 1);
    add(sol, empty, 0, left, right, cols, A);
    return sol;

//     [..Q. Q... ...Q .Q.. ] [.Q.. ...Q Q... ..Q. ]



}
