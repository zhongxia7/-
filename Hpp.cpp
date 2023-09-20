#include<iostream>
#include<cstring>
using namespace std;

int power(int* r, int n, int len_r) {
    int t1[1300] = { 0 };
    int len_t1 = len_r;
    for (int i = 0; i < len_r; i++)t1[i] = r[i];
    //t1复制r用来做高精度乘法不变的一个乘数
    //t2用来存放乘法中的临时数据
    for (int i = 1; i < n; i++) {
        //注意这里从1开始，且i也不能<=n而是<n
        //因为n=1时不计算，n=2时自乘1次……
        //n=n时自乘n-1次
        int t2[1300] = { 0 };
        for (int j = 0; j < len_t1; j++) {
            for (int k = 0; k < len_r; k++) {
                t2[j + k] += r[k] * t1[j];
                t2[j + k + 1] += t2[j + k] / 10;
                t2[j + k] %= 10;
            }//高精度乘法步骤
        }
        int len_t2 = len_t1 + len_r;
        for (int j = 0; j < len_t2; j++)r[j] = t2[j];
        len_r = len_t2;
        //更新乘数r并删除前导零
    }
    return len_r;
}
 
int main() {
    char s[1300];
    int r[1300] = { 0 };
    //一定要初始化为0
    //测试数据2可以说明原因
    //前导零去除不够小数部分位数的情况
    int n;
    //幂次次数
    while (scanf("%s %d", s, &n) == 2) {
        int point = 0;
        for (int key = 0; key < strlen(s); key++) {
            if (s[key] == '.') {
                point = key;
                break;
            }
        }//找到小数点的位置point；
        //用key主要防止输入的s是2不是2.0
        //但是在这一题中没有所以也可以不用key直接用point
        int Ans_FracPart = (strlen(s) - 1 - point) * n;
        //答案中小数的位数
        int len_r = 0;
        for (int i = strlen(s) - 1; i >= 0; i--) {
            if (i == point && s[i] == '.')continue;
            r[len_r] = s[i] - '0';
            len_r++;
        }//将输入的小数s去掉小数点后倒排存入数组r
        len_r = power(r, n, len_r);
        while (r[len_r - 1] == 0)len_r--;
        //删除前导零
        int zero = 0;
        //zero为尾0个数
        while (r[zero] == 0)zero++;
        int i;
        for (i = len_r - 1; i >= Ans_FracPart; i--)printf("%d", r[i]);
        //输出整数部分
        if ((i == Ans_FracPart - 1 && Ans_FracPart - 1 >= zero) || i == len_r - 1)printf(".");
        //输出小数点(避免无小数部分时输出.以及无整数部分时要输出.)
        for (int i = Ans_FracPart - 1; i >= zero; i--)printf("%d", r[i]);
        //输出小数部分
        printf("\n");
    }
    return 0;
}