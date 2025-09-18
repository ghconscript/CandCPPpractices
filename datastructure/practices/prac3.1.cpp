/*题干：
给你一个数组 `nums` 和一个值 `val` ，你需要原地（不借助额外空间）移除所有数值等于 `val` 的元素。
请返回 `nums` 中与 `val` 不同的元素的数量 `k` ，以及删除 `val` 后的 `nums`；
示例 1：
输入：nums = [3,2,2,3], val = 3
输出：2, [2,2,_,_]
解释：你的函数函数应该返回 k = 2, 并且 nums 中的前两个元素均为 2。
你在返回的 k 个元素之外留下了什么并不重要。

示例 2：
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, [0,1,3,0,4,_,_,_]

要求：
时间复杂度O(n)，空间复杂度O(1)
*/
#include<iostream> 
using namespace std;
int main(){
	int nums[5]={1, 2, 3, 4, 5};
	int val;
	int i,j;
	int k=0;
	int len = sizeof(nums)/sizeof(nums[0]);
	cin>>val;
	for(i=0,j=0;i<len;){
		cout<<nums[i]<<endl;
		if (nums[i]!=val){
			nums[j]=nums[i];
			i++;
			j++;
		}
		else{
			k+=1;
			i++;
		}
		
		
	}
	
} 
