#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX=10+1;

int N,M,K=0;

int dy[8]={-1,-1,0,1,1,1,0,-1};
int dx[8]={0,1,1,1,0,-1,-1,-1};
//좌표 기준 8방향

vector<int> MAP[MAX][MAX]; //칸의 나무 나이 저장
int A[MAX][MAX]={0,}; //매 seg마다 추가되는 양분
int food[MAX][MAX]={0,}; //현재 양분

int x,y,z=0; //입력받는 초기 x y z값

bool isRange(int y, int x){
	return (y>=0 && x>=0 && y<N && x<N);
}
//8방향 탐색 시 범위를 벗어났는지 check

void Input(){
	cin>>N>>M>>K;
	
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			cin>>A[i][j];
			food[i][j]=5; //초기 양분은 5
		}
	}
	
	for(int i=0;i<M;++i){
		cin>>x>>y>>z;
		MAP[x-1][y-1].push_back(z);
	}
}

void spring_summer(){ // 봄에서 여름까지

	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(MAP[i][j].size()==0) continue;
			sort(MAP[i][j].begin(),MAP[i][j].end()); 
			vector<int> live_tree; //살아있는 tree 저장
			int die_tree_food=0; //칸 검사 후 그 칸에 추가되어야 할 양분의 누적값
			
			for(int k=0;k<MAP[i][j].size();++k){
				int curAge=MAP[i][j][k];
				if(curAge>food[i][j]){
					int c=curAge/2;
					die_tree_food+=c;
				}else{
					food[i][j]-=curAge;
					live_tree.push_back(curAge+1);
					
				}
			}
			MAP[i][j].clear(); //MAP[i][j] 초기화
			for(int k=0;k<live_tree.size();++k){
				MAP[i][j].push_back(live_tree[k]); //살아있는 나무의 나이만 push_back
			}
			food[i][j]+=die_tree_food; //양분 추가
			
		}
	}

}



void fall(){ // 가을
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(MAP[i][j].size()==0) continue;
			for(int k=0;k<MAP[i][j].size();++k){
				int curAge=MAP[i][j][k];
				if(curAge%5==0){
					for(int m=0;m<8;++m){
						int ny=i+dy[m];
						int nx=j+dx[m];
						if(isRange(ny,nx)){
							MAP[ny][nx].push_back(1);
						}
					}
				}
			}
		}
	}
	
	
	
}

void winter(){
	//겨울
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			food[i][j]+=A[i][j];
			//현재 땅에 양분 추가로 지급
		}
	}
}
void season(){
	//한 계절
	spring_summer();
	fall();
	winter();
	
	
}

void solve(){
	Input();
	for(int i=0;i<K;++i){
		//K년 후
		season();
	}
	//남아있는 나무의 숫자
	int ret=0;
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			ret+=MAP[i][j].size();
		}
	}
	cout<<ret;
	
}


int main() {
	// your code goes here
	solve();
	return 0;
}