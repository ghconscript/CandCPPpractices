/*设计要求是将两个集合的元素个数差最小，两个元素和差最大。
先进行排序 选取前一半元素放入集合A，后一半元素放入集合B，
从而使得两个集合的元素和差最大。 该算法的时间复杂度为O(n log n)，主要是排序的时间复杂度。*/
#include <iostream>
using namespace std;
void heapsort(int arr[], int n) {
    // 构建大根堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        int child = 2 * parent + 1;
        while (child < n) {
            if (child + 1 < n && arr[child + 1] > arr[child]) {
                child++;
            }
            if (arr[parent] < arr[child]) {
                swap(arr[parent], arr[child]);
                parent = child;
                child = 2 * parent + 1;
            } else {
                break;
            }
        }
    }
    // 排序
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        int parent = 0;
        int child = 2 * parent + 1;
        while (child < i) {
            if (child + 1 < i && arr[child + 1] > arr[child]) {
                child++;
            }
            if (arr[parent] < arr[child]) {
                swap(arr[parent], arr[child]);
                parent = child;
                child = 2 * parent + 1;
            } else {
                break;
            }
        }
    }

}

int main() {

    return 0;
}