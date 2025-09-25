/*第二题
题干：
给定一个包含 `n + 1` 个整数的数组 `nums` ，其数字都在 `[1, n]` 范围内（包括 `1` 和 `n`），可知至少存在一个重复的整数。假设 `nums` 只有 一个重复的整数 ，
返回 这个重复的数 。你设计的解决方案必须 不修改 数组 `nums` 且只用常量级 `O(1)` 的额外空间。
示例 1：
输入：nums = [1,3,4,2,2]
输出：2

示例 2：
输入：nums = [3,1,3,4,2]
输出：3


*/
//不可以用异或 异或适用于 所有都S出现两次 只有一个出现一次 这个是只有一个出现两次
//二分查找或者循环检测:将数组作为一个静态链表看待
#include<iostream>
#include<algorithm>
using namespace std;
class Solution {
public:
	int cirdet(vector<int> &num) {
		int fast = 0;
		int slow = 0;
		do{
			slow = num[slow];
			fast = num[num[fast]];
		}while(slow != fast);
		fast = 0;
		while (fast != slow) {
			slow = num[slow];
			fast = num[fast];
		}
		return fast;
	}
};

int main() {
	vector <int> nums = {1, 4, 3, 4, 5, 8, 6, 7, 2};
	Solution sol;
	cout << sol.cirdet(nums) << endl;
	return 0;
}
