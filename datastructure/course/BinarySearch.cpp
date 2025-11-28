#include<iostream>
#define MAX 1000
using namespace std;

int arr[MAX]={0};
int binarySearch(int start,int end,int key){
	int ret=-1;
	int mid;
	while(start<=end){
		mid=start+((end-start)>>1);
		if(arr[mid]<key){
			start=mid+1;
		}else if(arr[mid]>key){
			end=mid-1;
		}else{
			ret=mid;
			break;
		}
	}
	return ret;
}
