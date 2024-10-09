#include <iostream>
#include <vector>

void merge(std::vector<int> &vec, int low, int high, int mid)
{
    int i = low;     //[low,mid]
    int j = mid + 1; //[mid+1,high]
    std::vector<int> tmp;
    tmp.reserve(high - low + 1);

    //将两个区间进行合并
    while (i <= mid && j <= high)
    {
        if(vec[i] > vec[j])
        {
            tmp.push_back(vec[j++]);
        }
        else
        {
            tmp.push_back(vec[i++]);
        }
    }
    //将区间内剩余的元素添加进临时数组
    while(i <= mid)
    {
        tmp.push_back(vec[i++]);
    }
    while(j <= high)
    {
        tmp.push_back(vec[j++]);
    }
    for(int tmp_i = low;tmp_i <= high;tmp_i++)
    {
        vec[tmp_i] = tmp[tmp_i - low];
    }
}
void mergeSort(std::vector<int> &vec, int i, int j)
{
    if (i >= j)
    {
        // 已经缩到只剩一个元素了，可以向上合并了
        return;
    }
    // 进行规模缩小
    int mid = (i + j) / 2;

    mergeSort(vec, i, mid);
    mergeSort(vec, mid + 1, j);
    // 进行合并
    merge(vec, i, j, mid);
}

int main()
{
    std::vector<int> vec;
    vec.reserve(20);
    for (int i = 0; i < 20; i++)
    {
        vec.push_back(rand() % 100);
    }
    for (auto i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    mergeSort(vec, 0, vec.size() - 1);

    for (auto i : vec)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}