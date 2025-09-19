/*题干：
给你一个非空整数数组 `nums` ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
示例 1 ：
输入：nums = [2,2,1]
输出：1

示例 2 ：
输入：nums = [4,1,2,1,2]
输出：4

要求：
时间复杂度O(n)，空间复杂度O(1)

*/
#include<iostream>
using namespace std;
int main (){
	int nums[5]= {4,1,2,1,2};
	int i;
	int result=nums[0]; 
	int len =sizeof(nums)/sizeof(nums[0]);
	for(i=1;i<len;i++){
		//根据结合律和异或的特点
		result=result^nums[i];
	}
	cout<<"重复的元素是"<<result; 
	return 0;
} 
