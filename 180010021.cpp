#include<bits/stdc++.h>

using namespace std;

ofstream filo;
ofstream milo;
struct node{
	int data;
	node *prev=NULL;
	char color;
	int d;
	int dis;
	int fis;
};
vector<vector<node>> adj;
vector<node>topo;
void BFS(int temp);
void DFS(int temp);
void DFS_VISIT(int* time,int i);
void adlist(int u, int v);

int main(int argc, char**argv){
	int a;
	int b;
	ifstream file;
	filo.open("sd.txt");
	milo.open("ts.txt");
	file.open(argv[1]);
	int s;
	s= atoi(argv[2]);
	while(!file.eof()){
		file>>a;
		file>>b;
		adlist(a,b);
	}
	BFS(s);
	DFS(s);
	for(int i=0;i<adj.size();i++){
	    filo<<adj[i][0].data<<" "<<adj[i][0].d<<endl;
	}
	for(int i=topo.size()-1; i>=0; i--){
		milo<<topo[i].data<<endl;
	}
	return 0;
}

void adlist( int u, int v){ 
    node temp;
    temp.data = u;
    node temp1;
    temp1.data = v;
    adj.resize(max(max(u,v)+1,(int)adj.size()));
    if (adj[u].size() == 0) {
    	adj[u].push_back(temp);
    }
    if (adj[v].size() == 0) {
    	adj[v].push_back(temp1);
    }
    adj[u].push_back(temp1); 
}

void BFS(int temp){
	vector<int> v;
	for(int i=0;i<adj.size();i++){
	    for(int j=0;j<adj[i].size();j++){
			adj[i][j].color='w';
			adj[i][j].d=-1;
			adj[i][j].prev=NULL;
	    }
	}
	adj[temp][0].d = 0;
	adj[temp][0].color='g';
	adj[temp][0].prev=NULL;
	v.push_back(adj[temp][0].data);
	while(v.empty() == false){
		vector<int>:: iterator it;
		it = v.begin();
		int x= v[0];
		v.erase(it);
		for(int i=1; i<adj[x].size(); i++){
			int naam= adj[x][i].data;
			if(adj[naam][0].color=='w'){
				adj[naam][0].color='g';
				adj[naam][0].d = adj[x][0].d + 1;
				adj[naam][0].prev = &adj[x][0];
				v.push_back(adj[naam][0].data);
			}
		}
	}
}
void DFS(int temp){
	for(int i=0;i<adj.size();i++){
	    for(int j=0;j<adj[i].size();j++){
			adj[i][j].color='w';
			adj[i][j].prev=NULL;
	    }
	}
	int time = 0;
	for(int i=0;i<adj.size();i++){
	    	if(adj[i][0].color=='w'){
	    		DFS_VISIT(&time, i);
	    	}
	    }
}
void DFS_VISIT(int* time, int i){
	*time = *time + 1;
	adj[i][0].dis = *time;
	adj[i][0].color = 'g';
	for(int j=1; j<adj[i].size(); j++){
		int naam= adj[i][j].data;
		if(adj[naam][0].color=='w'){
			adj[naam][0].prev= &adj[i][0];
			DFS_VISIT(time,naam);
		}
	}
	*time= *time+1;
	adj[i][0].color= 'b';
	adj[i][0].fis = *time;
	topo.push_back(adj[i][0]);
}