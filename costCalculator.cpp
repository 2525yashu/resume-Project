#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<list>
#include<queue>
#include<algorithm>
#include<climits>
#include<tuple>

using namespace std;

tuple<int, int, vector<string>> dijkstra(string start, string end, unordered_map<string, list<pair<string, pair<int, int>>>> &adjlist){

    unordered_map<string, int> distance;
    unordered_map<string, int> cost;
    unordered_map<string, string> parent;

    for (auto &node : adjlist) {
        distance[node.first] = INT_MAX;
        cost[node.first] = INT_MAX;
    }

    distance[start] = 0;
    cost[start] = 0;
    parent[start] = "-1";

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>> > mini; // <distane to reach that node, node name>
    
    mini.push(make_pair(0, start));

    while(!mini.empty()){
        pair<int, string> ontop = mini.top();
        mini.pop();

        string node = ontop.second;

        for (auto neigh : adjlist[node]) {
            string neighborNode = neigh.first;
            int edgeDist = neigh.second.first;
            int edgeCost = neigh.second.second;

            if (distance[node] + edgeDist < distance[neighborNode] ||
                (distance[node] + edgeDist == distance[neighborNode] && cost[node] + edgeCost < cost[neighborNode])) {
                distance[neighborNode] = distance[node] + edgeDist;
                cost[neighborNode] = cost[node] + edgeCost;
                parent[neighborNode] = node;
                mini.push({distance[neighborNode], neighborNode});
            }
        }
    }
    
    if(distance[end] == INT_MAX){
        distance[end] = -1;
        cost[end] = -1;
    }

    vector<string> path;

    string currnode = end;

    while(currnode != "-1"){
        path.push_back(currnode);
        currnode = parent[currnode];
    }

    reverse(path.begin(), path.end());

    return {distance[end], cost[end], path};
}


unordered_map<string, list<pair<string, pair<int, int>>>> buildgraph(vector<vector<string>> &edges){

    unordered_map<string, list<pair<string, pair<int, int>>>> adjlist;

    for(auto route: edges){
            string stop1 = route[0];
            string stop2 = route[1];
            int currdist = stoi(route[2]);        // converting distance into integer form
            int currcost = stoi(route[3]);    // converting cost

            adjlist[stop1].push_back(make_pair(stop2, make_pair(currdist, currcost)));
            adjlist[stop2].push_back(make_pair(stop1, make_pair(currdist, currcost)));

    }

    return adjlist;

}

int main(){

    vector<string> addresses;

    //{"start", "end", "distance", "cost"}
    vector<vector<string>> edges = {{"delhi bazaar", "mumbai", "500", "5000"}, {"patna", "kolkata", "80", "100"},
                                 {"kolkata", "delhi bazaar", "800","8000"}, {"mumbai", "kolkata","1000","10000"}};

    bool end = false;

    int count = 0;

    while(!end){

        if(count == 0){
            cout<<"Enter the starting address -> ";
        }

        else{
            cout<<"Enter the address or type 'done' for cost calculation -> ";
        }
        
        string stop;
        getline(cin, stop);
        transform(stop.begin(), stop.end(), stop.begin(), ::tolower);

        if(stop == "done"){
            end = true;
        }

        else{
            addresses.push_back(stop);
            count++;
        }
    }

    if(count < 2){
        cout<< "Invalid input";
    }

    
    else{
        
        cout<<endl;

        unordered_map<string, list<pair<string, pair<int, int>>>> adjlist = buildgraph(edges);     //(start, end, distance, cost)
        
        int totalCost = 0;
        int totalDistance = 0;

        for(int i = 0; i < addresses.size() - 1; i++){

            if(adjlist.find(addresses[i]) == adjlist.end() || adjlist.find(addresses[i + 1]) == adjlist.end()){
                cout << "Invalid address: One or both locations not found in the database: "<< addresses[i] << " or " << addresses[i + 1] << endl;
                continue;
            }

            if (addresses[i] == addresses[i + 1]) {
                cout << "Start and end locations are the same: " << addresses[i] << endl;
                continue;
            }

            tuple<int, int, vector<string>> travelDetails = dijkstra(addresses[i], addresses[i + 1], adjlist);   // (distance, cost, path)
            
            int pathdistance = get<0>(travelDetails);
            int pathexpense = get<1>(travelDetails);
            vector<string> path = get<2>(travelDetails);

            if(pathdistance == -1){
                cout<<"No path found from "<<addresses[i]<<" to "<<addresses[i + 1]<<endl;
                continue;
            }

            else{ 
                cout<<"path from "<< addresses[i] <<" to "<< addresses[i+1]<<" : ";
                for(int j = 0; j < path.size(); j++){
                    cout<< path[j]<<" ";
                    if(j < path.size() - 1){
                        cout<<"-> ";
                    }
                }
                cout<<endl;
                cout<< "cost -> "<<pathexpense<< "  ||  "<<"distance -> "<< pathdistance;
                cout<<endl;

                totalDistance += pathdistance;
                totalCost += pathexpense;
                cout<<endl;
            }

        }
        
        cout<<endl;
        cout<<"Total cost for journey -> "<< totalCost<<endl;
        cout<<"Total distance for journey -> "<< totalDistance<<endl;
    
    }

    return 0;
}
