/*************************************************************************
    > File Name: kmp.cpp
    > Author: tiankonguse
    > Mail: shen10000shen@gmail.com
    > Created Time: 2013/5/7 19:45:37
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<functional>
#include<algorithm>
using namespace std;
const int P=100;
int next[P];

//next[i]的意义
//s为匹配串,t为s的前i个字符组成的子串
//t = s[0]s[1]...s[i-1]
//设串s[0]s[1]...s[k]和串s[i-1-k]s[i-1-(k-1)]...s[i-1]相等，
//next[i]就是这样的k的最大值
//

void get_next(char *pat){
	memset(next,-1,sizeof(next));
	for(int i=1,k;pat[i];++i){
		for(k=next[i-1];k>=0 && pat[i]!=pat[k+1];k=next[k]);
		if(pat[k+1] == pat[i])next[i]=k+1;
	}
}

//返回匹配的第一个位置
//返回匹配的个数  ans
int kmp(char* str, char* pat){
	get_next(pat);
	int i=0, j=0,ans=0;

	while( str[i] && pat[j] ){
		if( pat[j] == str[i] ){
			 ++i;
			if(!pat[++j])ans++;
		}
		else if(j == 0)++i;
		else j = next[j-1]+1;
	}
	// return ans;
	if( pat[j] ) return -1;
	else return i-j;
}
int main() {

    return 0;
}
