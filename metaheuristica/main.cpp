/*  

Metodo: 
Jhon Alex Gaviria
*/
#include <bits/stdc++.h>

using namespace std; 
int MAXVOL;
const int oo = 1e9; 
vector<vector<int>> item; 
vector<bool> used; 
vector<int> cost   { 8,   10,   13,   5,   12,   5,   3,   8,   5,   4,   14,   5,   10,   13,   7,   15,   14,   15,   12,   8,   5,   10,   15,   11,   8,   8,   13,   3,   12,   4,   4,   14,   9,   10,   10,   9,   3,   4,   10,   13 };
vector<int> volume { 6,   9,    4,    4,    7,   5,   8,   9,   4,   3,    5,   4,    5,    2,   3,    3,    7,    4,    7,   9,   2,    4,    8,    3,   5,   6,   10,   5,    8,   4,   7,    3,   4,   10,   10,   2,   5,   8,    3,    2 }; 
queue<vector<int>> maxCostHeuristicQueue; 
queue<vector<int>> minVolumeHeuristicQueue;
queue<vector<int>> costvolumeHeuristicQueue;
int sum; 
int vol; 

    
bool maxCostHeuristic(vector<int> a, vector<int> b){

    if(a[0] == b[0]) {
        return a[1] > b[1]; 
    }   

    return a[0] > b[0]; 
}

bool minVolumeHeuristic(vector<int> a, vector<int> b){
    if(a[1] == b[1]) {
        return a[0] < b[0]; 
    }   

    return a[1] < b[1];
}

bool costvolumeHeuristic(vector<int> a, vector<int> b){
    double avalue = (double)a[0]/a[1]; 
    double bvalue = (double)b[0]/b[1]; 
    return avalue > bvalue; 
}

queue<vector<int>> copytoqueue(vector<vector<int>> vec){

    queue<vector<int>> newQueue; 
    for(int i=0; i<vec.size(); i++){
        newQueue.push(vec[i]); 
    }

    return newQueue; 
}


void initVariables(){


    for(int i=0; i<cost.size(); i++){
        item.push_back({cost[i], volume[i], i }); 
        used.push_back(false);
    }


    int maxVolume = 0; 
    for(int i=0; i<item.size(); i++) maxVolume += item[i][1];  
    MAXVOL = (maxVolume*2)/3; 
    sum = 0; 
    vol = 0; 

    vector<vector<int>> maxCostHeuristicArray = item; 
    vector<vector<int>> minVolumeHeuristicArray = item; 
    vector<vector<int>> costvolumeHeuristicArray = item;
    sort(maxCostHeuristicArray.begin(), maxCostHeuristicArray.end(), maxCostHeuristic); 
    sort(minVolumeHeuristicArray.begin(), minVolumeHeuristicArray.end(), minVolumeHeuristic);
    sort(costvolumeHeuristicArray.begin(), costvolumeHeuristicArray.end(), costvolumeHeuristic);
    maxCostHeuristicQueue = copytoqueue(maxCostHeuristicArray);
    minVolumeHeuristicQueue = copytoqueue(minVolumeHeuristicArray);
    costvolumeHeuristicQueue = copytoqueue(costvolumeHeuristicArray);
}


void schemeMaxCostinit(){
    cout << "\n\n--------Max Cost Heuristic--------\n"; 

    initVariables(); 
    int firstschemevalues = 4; 
    while(firstschemevalues--){
        vector<int> elementtoadd = maxCostHeuristicQueue.front(); 
        sum += elementtoadd[0]; 
        vol += elementtoadd[1]; 
        used[elementtoadd[2]] = true; 

        
        cout << elementtoadd[0] << " " << elementtoadd[1] << " " << elementtoadd[2] << endl; 

        maxCostHeuristicQueue.pop();
    }

    // Init squeme
    cout << "\n\n--------Initial scheme--------\n"; 
    for(int i=0; i<item.size(); i++){
        cout << used[i] << " "; 
    }
    cout << endl;
}

void showused(int except){
    for(int i=0; i<item.size(); i++){
        if(i == except-1) {
            cout << 1 << " ";
            continue; 
        }
        cout << used[i] << " "; 
    }
    cout << endl;
}


void makeMetaheuristic(){
    int ite = 0; 
    while(ite++ < 3){

        vector<pair<int, int>> posibilitis = {{ sum, vol }, { sum, vol }, { sum, vol }, { sum, vol }};

        // maxcost
        while(!maxCostHeuristicQueue.empty() && used[maxCostHeuristicQueue.front()[2]] == 1) maxCostHeuristicQueue.pop(); 
        cout << maxCostHeuristicQueue.front()[0] << " " << maxCostHeuristicQueue.front()[1] << endl; 
        posibilitis[0].first += maxCostHeuristicQueue.front()[0]; 
        posibilitis[0].second += maxCostHeuristicQueue.front()[1]; 

        showused(maxCostHeuristicQueue.front()[2]); 


    }
}


int main() {
    
    ios::sync_with_stdio(0);
    cin.tie(0);

    schemeMaxCostinit();
    makeMetaheuristic();

    




    // ans = solve(); 
}