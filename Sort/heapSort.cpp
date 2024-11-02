#include <iostream>


// shiftDown 元素下沉操作
void shiftDown(int arr[],int size,int i)
{
    int value = arr[i];
    // i下沉不能超过最后一个有孩子的节点
    while (i < size / 2)
    {
        // 与左右孩子分别相比，将大的那个上浮。然后跟新i
        int child = i * 2 + 1;
        if (child < size - 1 && arr[child + 1] > arr[child])
        {
            // 右孩子大
            child = child + 1;
        }

        if (arr[child] > value)
        {
            arr[i] = arr[child];
            i = child;
        }
        else
        {
            break;
        }
    }
    arr[i] = value;
}
void shiftUp(int arr[],int size,int i) 
{
    int value = arr[i];
    while (i > 0)
    {
        int father = (i - 1)/2;
        if(arr[i] > arr[father]) {
            arr[father] = arr[i];
            i = father;
        } else {
            break;
        }
    }
    arr[i] = value;    
}
void heapSort(int arr[], int size)
{
    int n = size - 1;
    // 就是从第一个非叶子节点开始
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        // 先进行下沉操作，循环往复后，这就是大根堆了
        shiftDown(arr,size,i);
    }
    //将最大的元素与末尾元素交换，然后下沉操作。最后就能变成从小到大排序了。
    for(int i = n; i > 0; i--) {
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        shiftDown(arr,i,0);
    }
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

    heapSort(arr, sizeof(arr) / sizeof(arr[0]));

    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}