#include<bits/stdc++.h>
using namespace std;
#define a 8

int solution = 0;

bool check(int b[a][a]){

    vector<int>r,c;

    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
           if(b[i][j]==1){
            r.push_back(i);
            c.push_back(j);
           }
        }
    }

    for(int i=0;i<r.size();i++){

        int r1 = r[i];
        int c1 = c[i];

        for(int j=i+1;j<r.size();j++){
            int r2 = r[j];
            int c2 = c[j];

            if((r1==r2) || (c1==c2) || (abs(r1-r2)==abs(c1-c2)) ){
                return false;
            }

        }

    }

    return true;


}

int backtrack(int b[a][a], int col){

    if(col==a){

        cout<<"solution "<<++solution<<"\n";

        for(int i=0;i<a;i++){
            for(int j=0;j<a;j++){
                cout<<b[i][j]<<" ";
            }
            cout<<"\n";
        }

        return 1;

    }


    for(int i=0;i<a;i++){
        b[i][col] = 1;
        if(check(b)==false){
            b[i][col] = 0;
            continue;
        }
        backtrack(b,col+1);
        b[i][col] = 0;
    }

    return -1;


}

int main(){

    //freopen("outbf.txt","w",stdout);

    auto st = clock();

    int b[a][a];

    memset(b,0,sizeof(b));

    backtrack(b,0);

    auto en = clock();

    cout<<"TIME :"<<(en-st)/double(CLOCKS_PER_SEC)*1000<<" ms\n";

}
