#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <iostream>
using namespace std;

const int maxm = 300;
int n, m;
long long a, b;
char mat[maxm][maxm];
long long ans[maxm][maxm];

struct p {
	int x,y,val;
};
int dirx[] = {0,0,1,-1};
int diry[] = {1,-1,0,0};
bool vis[maxm][maxm];

vector<p> vis_buf;

void gao(int a,int b, int val) {
	queue<p> q;
	vis_buf.resize(0);
	q.push(p{a,b,val});
	vis_buf.push_back(p{a,b,val});
	vis[a][b] = true;
    ans[a][b] += val;
	while(!q.empty()) {
		p buf = q.front();
		q.pop();
		if(buf.val==0) continue;
		for(int dir = 0;dir<4;dir++) {
			int x = buf.x + dirx[dir];
			int y = buf.y + diry[dir];
			if(x<0||y<0||x>=n||y>=m) continue;
			if(mat[x][y]=='*') continue;
			if(vis[x][y]) continue;
			vis[x][y] = true;
			vis_buf.push_back(p{x,y,0});
			ans[x][y] += buf.val>>1;
			q.push(p{x,y,buf.val>>1});
		}
	}
	for(auto i:vis_buf) {
	    vis[i.x][i.y] = false;
	}
}



int main() {
    scanf("%d%d%lld%lld", &n, &m, &a, &b);
    for (int i = 0; i < n; i++) scanf("%s", mat[i]);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == '*') continue;
			int val = mat[i][j] == '.' ? 0 : (mat[i][j] - 'A' + 1) * a;
			if(val==0) continue;
			gao(i,j,val);
        }
    }
	int rans = 0;
	for(int i = 0;i<n;i++) for(int j = 0;j<m;j++) if(ans[i][j]>b) rans++;
	printf("%d\n", rans);
    return 0;
}
