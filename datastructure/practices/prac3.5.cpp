/*第五题
题干：
给你一个字符串 `s` ，请你统计并返回这个字符串中回文子串的数目。回文字符串是正着读和倒过来读一样的字符串。子字符串是字符串中的由连续字符组成的一个序列。
示例 1：

输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"
abcba
示例 2：
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
aabbaa
要求：
时间复杂度O()，空间复杂度O(1)
*/
//用函数编程
#include<string>
#include<stdlib.h>
using namespace std;
int Cntrvssub(string &str) {
	int i, j;
	int cnt = 0;
	int len = str.size();
	for (i = 0; i < len ; i++) {
		for (j = 1; i - j >= 0 && i + j < len;) {
			if (str[i - j] == str[i + j]) {
				cnt++;
				j++;
			} else break;
		}//奇

	}

	for (i = 0; i < len - 1; i++) {
		for (j = 0; i - j >= 0 && i + j < len; ) {
			if (str[i - j] == str [i + 1 + j]) {
				cnt++;
				j++;
			} else break;
		}///偶数
	}
	return cnt;
}

int main () {
	string str = "aabbaa";
	printf("%d", Cntrvssub(str));
	return 0;
}
