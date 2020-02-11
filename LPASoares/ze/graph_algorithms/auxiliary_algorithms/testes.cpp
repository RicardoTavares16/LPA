#include <bits/stdc++.h>
using namespace std;

/*#define pb push_back

int main()
{
    vector<string> vec;

    // 5 string are inserted
    string input;
    for(int i = 0 ; i < 5 ; i++){
        cin >> input;
        vec.pb(input);
    }
    // displaying the contents
    cout << "Contents of the vector ascending:" << endl;
    vector<string>::iterator itr;
    for (itr = vec.begin(); itr != vec.end(); ++itr)
        cout << *itr << endl;

    cout << "Contents of the vector descending:" << endl;
    vector<string>::reverse_iterator ritr;
    for(ritr = vec.rbegin(); ritr != vec.rend(); ++ritr)
        cout << *ritr << endl;

    return 0;
}*/

bool myfunction (int i,int j) { return (i<j); }

int main () {
    int myints[] = {1,2,3,4,5,4,3,2,1};
    vector<int> v(myints,myints+9);                         // 1 2 3 4 5 4 3 2 1

    // using default comparison:
    sort (v.begin(), v.end());

    cout << "looking for a 3... ";
    if (binary_search (v.begin(), v.end(), 3))
        cout << "found!\n"; else cout << "not found.\n";

    // using myfunction as comp:
    sort (v.begin(), v.end(), myfunction);

    cout << "looking for a 6... ";
    if (binary_search (v.begin(), v.end(), 6))
        cout << "found!\n"; else cout << "not found.\n";

    return 0;
}

