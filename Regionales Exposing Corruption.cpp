#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <stack>
#include <cstdio>
#define mp make_pair
using namespace std;
int matDsp[201][10001];
int matPpp[201][10001];
vector<pair<int,int> > block;
stack<int> pila;
void init(){
	memset(matDsp[0],0,sizeof(matDsp[0]));
	memset(matPpp[0],0,sizeof(matPpp[0]));
}
inline int EntradaRapida(){
	char ch;
	long long valor=0;
	ch=getchar();
	while(ch == '\n' || ch == ' '){
		ch=getchar();
	}
	valor=0;
	while(ch >= '0' && ch <= '9'){
		valor=(valor*10)+(ch-'0');
		ch=getchar();
  }
  return valor;
}
pair<int,int> knapsack(int bud){	
	for(int i = 1; i < block.size()+1; i++){		
		for(int j = 1; j < bud+1; j++){
			if(block[i-1].first > j){
				matDsp[i][j] = matDsp[i-1][j];
				matPpp[i][j] = matPpp[i-1][j];
			}else{
				if(block[i-1].second + matDsp[i-1][j-block[i-1].first] > matDsp[i-1][j]){
					matDsp[i][j] = block[i-1].second + matDsp[i-1][j-block[i-1].first];
				}else{
					matDsp[i][j] = matDsp[i-1][j];
				}
				if((-block[i-1].second) + matPpp[i-1][j-block[i-1].first] > matPpp[i-1][j]){
					matPpp[i][j] = (-block[i-1].second) + matPpp[i-1][j-block[i-1].first];
				}else{
					matPpp[i][j] = matPpp[i-1][j];
				}
			}
		}
	}
	return mp(matDsp[block.size()][bud],matPpp[block.size()][bud]);
}
void bfs(pair<int,vector<int> > *Ad,int dsp,int ppp){
	bool visitados[dsp+ppp+1];
	memset(visitados,0,sizeof(visitados));	
	for(int j = 1; j < dsp+ppp+1;j++){
		if(Ad[j].second.size() == 0){
			if(j < dsp + 1){
				block.push_back(mp(Ad[j].first,-1));
			}else{
				block.push_back(mp(Ad[j].first,1));
			}
		}else{
			if(!visitados[j]){
				if(j > dsp){
					block.push_back(mp(Ad[j].first,1));
				}else{
					block.push_back(mp(Ad[j].first,-1));
				}
				pila.push(j);
				visitados[j] = true;
				while(!pila.empty()){
					int aux = pila.top();	
					pila.pop();
					for(size_t i = 0; i < Ad[aux].second.size();i++){
						if(!visitados[Ad[aux].second.at(i)]){
							block.back().first += Ad[Ad[aux].second.at(i)].first;
							if(Ad[aux].second.at(i) > dsp){
								block.back().second += 1;
							}else{
								block.back().second -= 1;
							}
							pila.push(Ad[aux].second.at(i));
							
							visitados[Ad[aux].second.at(i)] = true;
						}
					}
				}
			}
		}
	}
}	
int main(){
	int dsp,ppp,riv,bud;
	while((dsp = EntradaRapida()) && (ppp = EntradaRapida()) && (riv = EntradaRapida()) && (bud = EntradaRapida())){
		pair<int,vector<int> > Ad[dsp + ppp + 1];
		for(int i = 1; i < dsp + 1; i++){
			Ad[i].first = EntradaRapida();	
		}
		for(int i = dsp + 1; i < dsp+ppp+1; i++){
			Ad[i].first = EntradaRapida();	
		}
		int a,b;		
		for(int i = 0; i < riv ; i++){
			a = EntradaRapida();
			b = EntradaRapida();
			Ad[a].second.push_back(b+dsp);
			Ad[b+dsp].second.push_back(a);
		}
		bfs(Ad,dsp,ppp);
		pair <int,int> result = knapsack(bud);
		cout<<result.first+dsp<<" "<<result.second+ppp<<endl;
		
		block.clear();
	}
	return 0;
}
