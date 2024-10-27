#include <iostream>

void insertSort(int arr[],int size)
{
    for(int i = 1;i <= size;i++)
    {
        int value = arr[i];
        int j = i - 1;
        for(;j >= 0;j--)
        {
            if(arr[j] <= value)
            {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = value;
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

    insertSort(arr, sizeof(arr)/sizeof(arr[0]));

    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}