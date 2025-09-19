/*第二题
题干：
给你一个非严格递增排列的数组 `nums` ，请你原地删除重复出现的元素，使每个元素只出现一次,且元素的相对顺序应该保持一致 。返回删除后的数组长度以及数组本身。
示例 1：
输入：nums = [1,1,2]
输出：2, nums = [1,2,_]
解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2 。不需要考虑数组中超出新长度后面的元素。

示例 2：
输入：nums = [0,0,1,1,1,2,2,3,3,4]
输出：5, nums = [0,1,2,3,4]
解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4 。不需要考虑数组中超出新长度后面的元素。

要求：
时间复杂度O(n)，空间复杂度O(1)
*/

#include<iostream>
using namespace std; 
int main(){
	int nums[10]={0,0,1,1,1,2,2,3,3,4};
	int len = sizeof(nums)/sizeof(nums[0]);
	int i,j=0;
	int temp=-1;
	for (i=0;i<len;i++){
		if (temp!=nums[i]){
			temp=nums[i];
			nums[j]=nums[i];
			j++;
		}
	}
	cout<<"个数"<<j<<endl; 
	for(i=0;i<len;i++){
		if(i<j) 
		cout<<nums[i]<<",";
		else cout<<",_";

	}
} 
