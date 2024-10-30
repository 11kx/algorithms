#include <iostream>

int partation(int arr[], int begin, int end)
{
    int value = arr[begin];
    int l = begin;
    int r = end;
    while (l < r)
    {
        // 从右往左找一个比基准数小的
        while (l < r && arr[r] > value)
        {
            r--;
        }
        if (l < r)
        {
            arr[l] = arr[r];
            l++;
        }

        // 从左往右找一个比基准数大的
        while (l < r && arr[l] < value)
        {
            l++;
        }
        if (l < r)
        {
            arr[r] = arr[l];
            r--;
        }
    }
    arr[l] = value;
    return l;
}
// 快排，递归版
void quickSort(int arr[], int begin, int end)
{
    // 递归的退出条件
    if (begin >= end)
    {
        return;
    }
    /*
    快排优化1
    如果数组趋于有序了，或者数组元素已经比较少了（这时候就比较有序了）。
    使用快排就不能很好的分成二叉树了，就变成一个一维数组了，此时时间复杂度也就从n * logn 变成 n * n了
    趋于有序直接使用插入排序，最快的排序。
    */
    if ((end - begin) <= 100)
    {
        // insertSort();
        // return;
    }
    /*
    快排优化2
    其实就是想让快排很好的分成二叉树，这时候选择合适的基准数，可以让二叉树分开来。
    三数取中法，arr[l],arr[r],arr[(l + r)/2],他们三个当中数值是中间的那个做基准数，不就很好的分开来了。
    */
    // 在[begin,end]区间进行一次分割
    int pos = partation(arr, begin, end);
    // 此时pos相当于父节点
    //  对分割出来的左子树继续递归
    quickSort(arr, begin, pos - 1);
    // 对分割出来的右子树继续递归
    quickSort(arr, pos + 1, end);
}
void quickSort(int arr[], int size)
{
    // 封装一个可递归的接口
    quickSort(arr, 0, size - 1);
}
int main()
{
    int arr[20];
    for (int i = 0; i < 20; i++)
    {
        arr[i] = (rand() % 100);
    }
    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    quickSort(arr, sizeof(arr) / sizeof(arr[0]));

    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}