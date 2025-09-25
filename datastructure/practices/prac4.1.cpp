/*第四周
第一题
题干：
给定两个有序数组 `nums1` 和 `nums2` ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。
示例 1：
输入：nums1 = [1，1,2,2], nums2 = [2,2]
输出：[2]

示例 2：
输入：nums1 = [4,5,9], nums2 = [4,4,8,8,9]
输出：[4,9]
*/
#include<stdlib.h>
#include<algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int length1 = nums1.size(), length2 = nums2.size();
		int index1 = 0, index2 = 0;
		vector<int> intersection;
		while (index1 < length1 && index2 < length2) {
			int num1 = nums1[index1], num2 = nums2[index2];
			if (num1 == num2) {
				// 保证加入元素的唯一性
				if (!intersection.size() || num1 != intersection.back()) {//.back 访问最后一个元素
					intersection.push_back(num1);//尾插一个元素
				}
				index1++;
				index2++;
			} else if (num1 < num2) {
				index1++;
			} else {
				index2++;
			}
		}
		return intersection;
	}
};
//c++风格代码



int main(){
	vector <int> nums1 = {1,1,3,4,5,};
	vector <int> nums2 = {4,2,4,4,4,6,3,2,};
	Solution sol ;
	vector <int> res = sol.intersection(nums1,nums2);
	for(int i=0;i<res.size();i++){
		cout<<res[i]<<endl;
	}
	
}
