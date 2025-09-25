/*题干：
以数组 `intervals` 表示 `n` 个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

要求：
时间复杂度O(n2)，空间复杂度O(n)
进阶要求：
时间复杂度O(n2)，空间复杂度O(n) (对数组原地操作)
*/
#include<iostream>
#include<algorithm>
using namespace std;
bool isOverlap(int arr1[2],int arr2[2]){
	if(arr1[1]>=arr2[0]){
		return true;
	}
	else return false;
}
bool compare(const int *inter1,const int *inter2){
	return inter1[0]<inter2[0];
}

void combine(int inter1[2],int inter2[2],int des[2]){
	des[0]=min(inter1[0],inter2[0]);
	des[1]=max(inter1[1],inter2[1]);
}
int main (){
	int intervals[][2]={{1,3},{2,6},{8,10},{15,18}};
	int len = sizeof (intervals)/sizeof(intervals[0]);
	int results[len][2]={0};
	//假设按照start升序排列
	//sort(intervals,intervals+len,compare);
	int i;
	int j=0;
	results[j][0] = intervals[0][0];
	results[j][1] = intervals[0][1];
	for (i=1;i<len;i++){
		if(isOverlap(results[j],intervals[i])){
			combine(intervals[i],results[j],results[j]);
		}else {
			j++;
			results[j][0] = intervals[i][0];
			results[j][1] = intervals[i][1];
		}
	} 
	for (int i = 0; i <= j; i++) {
		cout << "[" << results[i][0] << ", " << results[i][1] << "] ";
	}
} 
