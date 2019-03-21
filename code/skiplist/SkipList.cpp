/*************************************************************************
 > File Name: SkipList.cpp
 > Author: tiankonguse(skyyuan)
 > Mail: i@tiankonguse.com
 > Created Time: Sat 15 Sep 2018 02:14:42 PM UTC
 ***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<cmath>
#include<stack>
#include<algorithm>
#include<functional>
#include<stdarg.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif

const int MAXLEVEL= 32;

class SkipListNode {
    class SkipListLevel {
    public:
        SkipListLevel():next(NULL),num(1) {
        }
        SkipListNode* next;
        int num;//��ǰnext���������ٸ��ڵ�,������ǰ�ڵ�
    };
public:
    SkipListNode(int v = -1, int l = -1):value(v),maxlevel(l) {
    }
    int value;
    int maxlevel;
    SkipListLevel level[MAXLEVEL];
};

class SkipList {
    int level;
    unsigned long length;
    SkipListNode _header;
public:
    SkipList():level(1),length(0) {
    }

    //����ֵ��λ�ã������ڷ���-1
    int findByValue(int value) {
        SkipListNode* head = &_header;
        int pos = -1;
        //����С�ڵ���value�����һ���ڵ�
        for(int i=MAXLEVEL-1; i>=0; i--) {
            //next����NULL, �Ҵ�����߽磬��߽�����
            while(head->level[i].next && head->level[i].next->value <= value) {
                pos += head->level[i].num; //��߽����ƣ�����ƫ����
                head = head->level[i].next;
            }
        }
        //���value����Сֵ���������-1�����value������Сֵ����϶���һ��
        if(head->value != value) {
            pos = -1;
        }
        return pos;
    }

    //����λ�ò�ֵ���϶�����
    int getByPos(int rank) {
        SkipListNode* head = &_header;
        int pos = 0;
        //����С�ڵ���value�����һ���ڵ�
        for(int i=MAXLEVEL-1; i>=0; i--) {
            //next����NULL, �������ڵ��û����Ŀ��λ��
            while(head->level[i].next && head->level[i].num + pos <= rank) {
                pos += head->level[i].num; //��߽����ƣ�����ƫ����
                head = head->level[i].next;
            }
        }
        return pos;
    }
    void insert(int value) {
        SkipListNode* head = &_header;
        SkipListNode *pre[MAXLEVEL]; //����ʱ��������Ҫ���µı�ͷ
        int preNum[MAXLEVEL];//��Ҫ���µı�ͷ֮ǰ�ж��ٽڵ�

        int pos = -1;
        for(int i=MAXLEVEL-1; i>=0; i--) {
            //next����NULL, �Ҵ�����߽磬��߽�����
            preNum[i] = i == (MAXLEVEL-1) ? 0 : preNum[i+1];//���ڼ���֮ǰ�ģ��̳���һ���
            while(head->level[i].next && head->level[i].next->value <= value) {
                preNum[i] += head->level[i].num;//��߽����ƣ��ۼ���ƫ����
                head = head->level[i].next;
            }
            pre[i] = head;
        }

        SkipListNode* node = new SkipListNode();
        node->maxlevel = rand()%MAXLEVEL;
        node->value = value;

        //��update��update���¸��ڵ�֮�����node
        for(int i=0; i< node->maxlevel; i++) {
            node->level[i].next = pre[i]->level[i].next;
            pre[i]->level[i].next = node;
            //����λ�õ��¸�λ��֮��ĸ��� ��ȥ �����ռ�õĸ��� �����µ�֮��ĸ���
            node->level[i].num = pre[i]->level[i].num - (preNum[0] - preNum[i]);
            //����λ��֮ǰ�Ľڵ��� ��ȥ ��i��֮ǰ�Ľڵ��� + 1 ���ǲ���λ�õ��¸�λ��֮��ĸ���
            pre[i]->level[i].num = (preNum[0] - preNum[i]) + 1;
        }

        for (int i = node->maxlevel; i < MAXLEVEL; i++) {
            pre[i]->level[i].num++; //�½ڵ�ĸ߶Ȳ�����û���µ�
        }
    }
};



int main() {

    return 0;
}
