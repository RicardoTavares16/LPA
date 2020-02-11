#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOR_ITERATOR(i,n) for(vector<int>::iterator i = adj[n].begin(); i!= adj[n].end();i++)
#define println(v) cout << v << endl

double distance(int x1, int x2, int y1, int y2){
    return sqrt( pow(x1-x2,2) + pow(y1-y2,2));
}

int main(){
    int number_tests, number_swarms, number_robots,number_technicians, w,z;
    int x_tech, x_robot, y_tech, y_robot;

    FOR(i,number_tests){
        vector < pair < int, int > > tech_location(number_technicians);
        vector < vector < pair <  int, int > > > swarm_location(number_swarms);
        cin >> number_swarms >> number_technicians >> w >> z;

        FOR(j,number_technicians){
            cin >> x_tech >> y_tech;
            tech_location.push_back(make_pair(x_tech,y_tech));
        }
        FOR(j,number_swarms){
            cin >> number_robots;
            FOR(k,number_robots){
                cin >> x_robot >> y_robot;
                swarm_location[j].push_back(make_pair(x_robot,y_robot));
            }
        }

    }
}
