#include <bits/stdc++.h>

using namespace std;

#define INF 0x3f3f3f3f
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define println(v) cout << v << endl

int main(){
    int number_elevators, destination, elevator_travel_speed, floor;

    while(cin >> number_elevators >> destination){
        vector < int > time(number_elevators);
        vector < vector < int > > all_stops(number_elevators);
        vector < vector < pair < int, int > > > adj(number_elevators*100);
        FOR(i,number_elevators){
            cin >> elevator_travel_speed;
            time[i] = elevator_travel_speed;
        }
        FOR(i,number_elevators){
            string line;
            getline(cin, line);
            istringstream iss(line);

            for(int j = i ; j >= 0; --j){
                while (iss >> floor){
                    println(floor);
                    if(i==0){
                        all_stops[i-j].push_back(floor);
                    }else{
                        all_stops[i-j].push_back(floor+100*(j+1));
                    }

                }
            }
        }
        FOR(i,(int)all_stops.size()){

            FOR(j,(int)all_stops[i].size()){
                //println(j);
                //printf("o elevador %d está ligado aos pisos %d com valor %d\n",i,all_stops[i][j],0);
            }

        }

    }
}