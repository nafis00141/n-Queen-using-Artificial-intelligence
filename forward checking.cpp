#include<bits/stdc++.h>
using namespace std;

#define si 8


int solution = 0;

vector< vector<int> > initialize_board(){

    vector< vector<int> >board;
    vector<int> p;

    for(int i=0;i<si;i++){
        p.push_back(0);
    }

    for(int i=0;i<si;i++){
        board.push_back(p); ///each p is a row
    }

    return board;

}

void print_board(vector< vector<int> >board){

    for(int i=0;i<si;i++){

        for(int j=0;j<si;j++){

            if(board[i][j]>=0)cout<<board[i][j]<<"   ";
            else cout<<"X"<<"   ";

        }

        cout<<"\n";
    }

}


vector< vector<int> > crossing_out(vector< vector<int> >board,int row,int col){

    ///crossing out the lower row indexes
    for(int i=row+1;i<si;i++){
        board[i][col] = board[i][col] - 1;
    }

    ///crossing out the lower diagonal indexes

    int x = row+1,y = col+1;

    while(x<si && y<si){
        board[x][y] = board[x][y] - 1;
        x++;
        y++;
    }

    x = row+1;
    y = col-1;

    while(x<si && y>-1){
        board[x][y] = board[x][y] - 1;
        x++;
        y--;
    }

    return board;

}



int solve(vector< vector<int> >board,int row){


    if(row==si){

        cout<<"solution "<<++solution<<"\n";
        //cerr<<"solution "<<solution<<"\n";

        print_board(board);

        return 1;
    }

    ///forward checking

    for(int i=row+1;i<si;i++){

        bool flag = false;

        for(int j=0;j<si;j++){
            if(board[i][j]==0){
                flag = true;
                break;
            }
        }

        if(flag==false) return -1;

    }


    ///placing the queen

    int ans = -1;

    for(int i=0;i<si;i++){
        if(board[row][i]==0){
            board[row][i]=1;
            vector< vector<int> > new_board = crossing_out(board,row,i);
            ans = max(solve(new_board ,row+1),ans);
            //if(ans==1) return ans;
            board[row][i]=0;
        }
    }

    return ans;


}



int main(){

    //freopen("out.txt","w",stdout);

    auto st = clock();

    vector< vector<int> >board = initialize_board();

    cout<<"Board:\n";

    solve(board,0);

    auto en = clock();

    cout<<"TIME :"<<(en-st)/double(CLOCKS_PER_SEC)*1000<<" ms\n";


}
