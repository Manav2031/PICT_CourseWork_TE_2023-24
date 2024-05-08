#include<bits/stdc++.h>
using namespace std;
class cal {
    int n;
    public:
    cal(int p) {
        n=p;
    }
    bool safe(vector<vector<int>>&input,int r,int c) {
        int x=r;
        int y=c;
        while (y>=0) {
            if (input[x][y]==1) {
                return false;
            }
            y--;
        }
        x=r;
        y=c;
        while (y>=0 && x>=0) {
            if (input[x][y]==1) {
                return false;
            }
            x--;
            y--;
        }
        x=r;
        y=c;
        while (y>=0 && x<n) {
            if (input[x][y]==1) {
                return false;
            }
            x++;
            y--;
        }
        return true;
    }
    bool backtrack(int c,vector<vector<int>>&input) {
        if (c>=n)
        return true;
        for (int i=0;i<n;i++) {
            if (safe(input,i,c)) {
                input[i][c]=1;
                if( backtrack(c+1,input) ) 
                return true;
                input[i][c]=0;
            }
        }
        return false;
    }
    void back() {
        vector<vector<int>>input(n,vector<int>(n,0));

            if (backtrack(0,input)) {
             for (int i=0;i<n;i++) {
             for (int j=0;j<n;j++) {
                cout<<input[i][j]<<" ";
            }
            cout<<endl;
        }
            }
    }

    bool safe2(vector<int>row,vector<int>&left,vector<int>&right,int x,int y) {
        if (row[x]==1 || left[x+y]==1 || right[y-x+n-1])
        return false;
        return true;
    }

    bool branch(int c,vector<vector<int>>&input,vector<int>&left,vector<int>&right,vector<int>&row) {
        if (c>=n) {
            return true;
        }
        for (int i=0;i<n;i++) {
            if (safe2(row,left,right,i,c)) {
                input[i][c]=1;
                row[i]=1;
                left[i+c]=1;
                right[c-i+n-1]=1;
                if (branch(c+1,input,left,right,row)) {
                    return true;
                }
                 input[i][c]=0;
                 row[i]=0;
                left[i+c]=0;
                right[c-i+n-1]=0;
            }
        }
        return false;
    }
    
    void bound() {
        vector<int>left(2*n-1,0);
        vector<int>right(2*n-1,0);
        vector<vector<int>>input(n,vector<int>(n,0));
        int c=0;
        vector<int>row(n,0);
        if (branch(c,input,left,right,row)) {

            for (int i=0;i<n;i++) {
             for (int j=0;j<n;j++) {
                cout<<input[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    }
};
int main() {
    int n;
    cout<<"Enter number of columns :- ";
    cin>>n;
    cal g(n);
    g.back();
    cout<<"-----------------------------------"<<endl;
    g.bound();
}