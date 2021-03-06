#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
using namespace std;

struct B {
	double x1, y1, x2, y2;
	void init() {
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		if(x1 > x2) {
			swap(x1, x2);
		}
		if(y1 > y2) {
			swap(y1, y2);
		}
	};
};


int const inf = 0x3f3f3f3f, maxn = 510;
int x1, y1, x2, y2, n, mx, my;
int m[maxn][maxn];
set<double> x, y;
set<double>::iterator si;
map<double, int> hx, hy;
map<int, double> hhx, hhy;
B b[maxn];

double get(int i,int j){
	//printf("%lf %lf  %lf  %lf\n",hhx[i-1],hhy[j-1],hhx[i],hhy[j]);
	return (hhx[i]-hhx[i-1])*(hhy[j]-hhy[j-1]);

}

int main() {
	const bool debug = false;
	int i, j, k,cs=1;
	while(scanf("%d", &n),n) {

		x.clear();y.clear();

		for(i = 0; i < n; i++) {
			b[i].init();
			x.insert(b[i].x1);
			x.insert(b[i].x2);
			y.insert(b[i].y1);
			y.insert(b[i].y2);
		}
		hx.clear();
		hy.clear();

		//把地图扩大二倍后，矩阵内部就可以被填充，矩阵边界就可以走了

		//对x离散化
		for(si = x.begin(), mx = 1; si != x.end(); hx[*si] = mx, hhx[mx] = *si, si++,mx+=1) ;


		//对y离散化
		for(si = y.begin(), my = 1; si != y.end(); hy[*si] = my, hhy[my] = *si, si++,my+=1);


		for(i = 0; i < mx; ++i){
			fill(m[i], m[i] + my, 0);
		}

		//填充矩阵，填充为1
		for(i = 0; i < n; i++) {
			int xuper = hx[b[i].x2];
			int yuper = hy[b[i].y2];
			//填充矩阵
			for(j = hx[b[i].x1] ; j <= xuper; j++) {
				for(k = hy[b[i].y1] ; k <= yuper; k++) {
					m[j][k]=1;
				}
			}
		}



		if(debug) {
			puts("---- stp ----");
			for(i = 0; i < mx; i++) {
				for(j = 0; j < my; j++) {
					printf(" %2d",m[i][j]);
				}
				puts("");
			}
			puts("---- stp ----\n\n");
		}

		double ans = 0;
		for(i=1;i<mx;i++){
			for(j=1;j<my;j++){
				if(m[i][j] && m[i-1][j-1]&&m[i-1][j] && m[i][j-1]){
					ans += get(i,j);
				}
			}
		}
		printf("Test case #%d\nTotal explored area: 180.00 %.2f\n",cs++,ans);


	}
	return 0;
}
