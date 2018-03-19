#include<bits/stdc++.h>
using namespace std;

#define si 16

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


vector<int> get_random_successor_amoung_the_uphill_moves(vector<int> current){

    vector<int> random_successor,new_succ;

    vector<vector<int>>uphill_successors;

    int current_h = h(current);

    int row,col;

    int size_of_succ = 0;

    for(int i=0;i<current.size();i++){

        row = current[i];
        col = i;


        for(int j=0;j<si;j++){

            if(row == j) continue;

            current[i] = j;

            new_succ = current;

            current[i] = row;

            int now = h(new_succ);

            if(now<current_h){
                uphill_successors.push_back(new_succ);
                size_of_succ++;
            }

        }

    }

    if(size_of_succ==0) return current;

    srand(time(0));

    int k = rand() % size_of_succ + 0;

    random_successor = uphill_successors[k];

    return random_successor;

}



vector<int> stochastic_hill_climbing(){

    vector<int> current = make_node();

    vector<int> neighbor;

    while(1){

        neighbor = get_random_successor_amoung_the_uphill_moves(current);

        if(h(neighbor)>=h(current)) return current;

        current = neighbor;

    }

}

int main(){

    vector<int> result = stochastic_hill_climbing();

    cout<<"number of conflict on final board : "<<h(result)<<"\n";

    cout<<"board: \n";

    show_board(result);


}

