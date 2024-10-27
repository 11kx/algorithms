#include <iostream>

void ShelltSort(int arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        //i 从gap开始。
        for (int i = gap; i < size; i++)
        {
            int value = arr[i];
            int j = i - gap;
            for (; j >= 0; j -= gap)
            {
                if (arr[j] <= value)
                {
                    break;
                }
                arr[j + gap] = arr[j];
            }
            arr[j + gap] = value;
        }
    }
}

int main()
{
    int arr[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = (rand() % 100);
    }
    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    ShelltSort(arr, sizeof(arr) / sizeof(arr[0]));

    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}