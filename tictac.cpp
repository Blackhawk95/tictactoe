#include <iostream>
#include <deque>
#include <algorithm>
#include <map>

using namespace std;

#define N 3
#define K 3
struct object{
    char c;
    int x;
    int y;
};

void printBoard(object board[][N]){

for(int i = 0;i<N;i++){
    for(int j = 0;j<N;j++){
    cout<<board[i][j].c;
    if(j!= N-1)
        cout<<" | ";
}
if(i!= N-1)
        cout<<"\n---------\n";

}

cout<<"\n__________________________________\n";
}


int turn(deque<object> *Player,object board[][N],object move){
	//check condition and place in board
	object top = Player->front();		
	if((board[move.x][move.y]).c == ' '){
		board[move.x][move.y] = move;
	}else if(move.x == top.x && move.y == top.y && move.c == top.c){
			
		
		
	}else{  cout<<"cant perform the move, already occupied\n";
		return -1;		
	}

	//insert into player queue, and perform the twist
	if(Player->size() < K){
		//cout<<"entered if statement\n";
		Player->push_back(move);
		
	}else{
		Player->push_back(move);
		//object top = Player->front();
		Player->pop_front();
		if(move.x != top.x && move.y != top.y )
			board[top.x][top.y]={' ',top.x,top.y};
		

		//cout<<"entered greater than 3\n";
	}

	//checking the condition
	map<int,int> tempx,tempy;
	int countDiag = 0;
	int win = 0;
	if(Player->size() >= N){
		for(auto &deq: *Player){
			//cout<<"x :"<<deq.x<<"y :"<<deq.y<<"\n";
			if(deq.x == deq.y){
				countDiag++;	
			}
			tempx[deq.x]++;
			tempy[deq.y]++;
		}
		//cout<< countDiag <<"\n";
		//the dramatic comparison using lambdas
		if(countDiag >=N || find_if(tempx.begin(),tempx.end(),[] (const pair<int,int> &t1 ) -> bool { return t1.second == N; }) != tempx.end() || find_if(tempy.begin(),tempy.end(),[] (const pair<int,int> &t2) ->bool { return t2.second == N;} ) != tempy.end()){
			win = 1;	
		}	
	}
	//cout<<win<<"\n";
	return win;
}


int main(){

deque<object> X;
deque<object> O;
object B = {' ',0,0}; // Blank
object board[N][N];
//at first element vanishes ,the element gets added , then winning conditions are checked
for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
        board[i][j] = {' ',i,j};


printBoard(board);
//if(turn(&X,board,{'X',2,1}) == 1) cout<<"win\n"; 
//if(turn(&X,board,{'X',1,1}) == 1) cout<<"win\n"; 
//if(turn(&X,board,{'X',0,1}) == 1) cout<<"win\n"; 
//if(turn(&X,board,{'X',2,2}) == 1) cout<<"win\n"; 
//turn(&X,board,{'X',1,1});
//turn(&X,board,{'X',2,2});
//turn(&O,board,{'Y',0,0});

int x,y,check;
bool trn = true;
int win = 1;
while(win){
	if(trn){
		while(1){
			cout<<"Player 1 turn (x y)\n";
			cin>>x>>y;
			check = turn(&X,board,{'X',x,y});
			if(check != -1)
				break;
			cout<<"retry\n";	
		}
		if(check){ cout<<" Player 1 win\n"; 
			win = 0;	
		}
	}else{

		//if(turn(&O,board,{'O',x,y}) == -1) cout<<"win\n"; 
		while(1){
			cout<<"Player 2 turn (x y)\n";	
			cin>>x>>y;
			check = turn(&O,board,{'O',x,y});
			if(check != -1)
				break;	
			cout<<"retry\n";
		}
		if(check){ cout<<" Player 2 win\n"; 
			win = 0;	
		}	
	}

	printBoard(board);
	trn = !trn;	
	
}


cout<<"\n";
//printBoard(board);

return 0;
}
