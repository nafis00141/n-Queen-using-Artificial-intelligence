#include<bits/stdc++.h>
using namespace std;

#define si 4

///for generating random numbers
random_device rseed;
mt19937 rgen(rseed()); // mersenne_twister
uniform_int_distribution<int> idist(0,si-1); // [0,15]

void show_board(vector<int> a){

    int b[si][si];

    memset(b,0,sizeof(b));

    for(int i=0;i<a.size();i++){
        b[a[i]][i] = 1;
    }

    for(int i=0;i<si;i++){
        for(int j=0;j<si;j++){
            cerr<<b[i][j]<<"   ";
        }
        cerr<<"\n";
    }

}

vector<int> make_node(){

    vector<int> board;

    bool vis[20];

    memset(vis,false,sizeof(vis));

    srand(time(0));

    for(int i=1;i<=si;i++){
        int num = idist(rgen);

        while(vis[num]==true)
            num = idist(rgen);

        board.push_back(num);
        vis[num] = true;
    }

    return board;

}


int h(vector<int> current){

    int val,row1,col1,row2,col2;

    val = 0;

    for(int i=0;i<current.size();i++){
        row1 = current[i];
        col1 = i;

        for(int j=i+1;j<current.size();j++){
            row2 = current[j];
            col2 = j;

            if((row1==row2) || (col1==col2) || (abs(row1-row2)==abs(col1-col2)) ){
                val++;
            }

        }

    }

    return val;
}


vector<int> get_highest_valued_successor_of_current(vector<int> current){

    vector<int> successor,best_successor;

    int best_h = INT_MAX;

    int row,col;

    for(int i=0;i<current.size();i++){

        row = current[i];
        col = i;

        for(int j=0;j<si;j++){

            if(row == j) continue;

            current[i] = j;

            successor = current;

            current[i] = row;

            int now = h(successor);

            if(now<best_h){
                best_successor = successor;
                best_h = now;
            }

        }

    }


    return best_successor;


}



vector<int> hill_climbing(){

    vector<int> current = make_node(); /// index is the column number of the queen and the value is the row number


    vector<int> neighbor;

    while(1){

        neighbor = get_highest_valued_successor_of_current(current);

        if(h(neighbor)>=h(current)) return current;

        current = neighbor;

    }

}

int main(){

    vector<int> result = hill_climbing();

    cout<<"number of conflict on final board : "<<h(result)<<"\n";

    cout<<"board: \n";

    show_board(result);


}
