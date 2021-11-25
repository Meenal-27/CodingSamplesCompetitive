#include <bits/stdc++.h>

void solve(vector <vector<char>> &sol,vector <vector <char>> A, vector <vector<int>> rows, vector <vector<int>> cols, vector <vector<int>> boxes, int cur_row, int cur_col  )
{
    if(cur_row==9) {sol = A;}
    else
    {
        if(A[cur_row][cur_col]!='.')
        {
            if(cur_col==8)
            {
                solve(sol,A, rows, cols, boxes, cur_row+1,0);
            }
            else 
            {
                solve(sol,A, rows, cols, boxes,cur_row, cur_col+1);
            }
        }
        else
        {
            for(int i=0;i<9;i++)
            {
                if(rows[cur_row][i]!= 1) continue;
                else if(cols[cur_col][i]!=1) continue;
                else if(boxes[(cur_row/3)*3 + cur_col/3][i]!=1) continue;
                else
                {
                    //cout<<"HI"<<" "<<cur_row<<" "<<cur_col<<endl;
                    rows[cur_row][i]= 0;
                    cols[cur_col][i]=0;
                    boxes[(cur_row/3)*3 + cur_col/3][i] =0;
                    A[cur_row][cur_col]= (char)(i + 49);
                    if(cur_col==8)
                    {
                        solve(sol,A, rows, cols, boxes, cur_row+1,0);
                    }
                    else 
                    {
                        solve(sol,A, rows, cols, boxes,cur_row, cur_col+1);
                    }
                    A[cur_row][cur_col]= '.';
                    rows[cur_row][i]= 1;
                    cols[cur_col][i]=1;
                    boxes[(cur_row/3)*3 + cur_col/3][i] =1;
                }
            }
        }
    }
}




void Solution::solveSudoku(vector<vector<char> > &A) {

    
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details

    vector <vector <int>> rows;
    vector <vector <int>> cols;
    vector <vector<int>> boxes;
    for(int i=0;i<9;i++)
    {
        vector <int> r(9,1);
        for(int j=0;j<9;j++)
        {
            if(A[i][j] != '.')
            {
                int num = A[i][j]- 48;
                r[num-1] =0;
            }
        }
        rows.push_back(r);
    }
    //cout<<"Hello"<<endl;
    for(int i=0;i<9;i++)
    {
        vector <int> c(9,1);
        for(int j=0;j<9;j++)
        {
            if(A[j][i] != '.')
            {
                int num = A[j][i]- 48;
                c[num-1] =0;
            }
        }
        cols.push_back(c);
    }
    //cout<<"Hello"<<endl;
    for(int i=0;i<9;i++)
    {
        vector <int> box(9,1);
        boxes.push_back(box);
    }
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(A[i][j]!= '.')
            {
                int r1 = i/3;
                int c1 = j/3;
                int index = r1*3+ c1;
                int num = A[i][j]-48;
                boxes[index][num-1]= 0;
            }
        }
    }
    //cout<<"Hello"<<endl;

    vector <vector<char>> sol;
    solve(sol,A, rows, cols, boxes, 0, 0);
    A = sol;
    //9 9 .8.5..... ....3.2.. ..9.2.7.. ..7.....6 .4.....5. 1..2....7 ..8.6...3 ...3.16.4 ..1..9...

}
