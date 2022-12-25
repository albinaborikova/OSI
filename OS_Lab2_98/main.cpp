#include <iostream>
#include <windows.h>


volatile int min_index, max_index, min, max, mean;
int size;


void min_max_t(LPVOID* param) {

    int* arr = (int*)param;
    min = arr[0];
    max = arr[0];

    for (int i = 0; i < size; i++) {
        if (arr[i] >= arr[0]) {
            max = arr[i];
            max_index = i;
        }
        else {
            min = arr[i];
            min_index = i;
        }
        Sleep(7);
    }


    printf("\nMinimum array element:%d", min);
    printf("\nMaximum array element:%d", max);
    printf("\nThread1 done\n");
}

void average_t(LPVOID* param) {

    int* arr = (int*)param;
    mean = 0;

    for (int i = 0; i < size; i++) {
        mean += arr[i];
        Sleep(12);
    }

    mean /= size;

    arr[min_index] = mean;
    arr[max_index] = mean;

    printf("\nArithmetic mean of array elements:%d", mean);
    printf("\nThread2 done\n");
}

void main_t() {

    HANDLE min_max, average;
    DWORD IDmin_max, IDaverage;

    printf("\nEnter the size of the array:");
    //std::cin >> size;
    scanf("%d", &size);
    int* arr = new int[size];
    //std::cout << "Enter array elements: "<< std:: endl;
    printf("\nEnter array elements:");

    for (int i = 0; i < size; i++) {
      //  std::cin >> arr[i];
        scanf("%d", &arr[i]);
    }


    min_max = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max_t, (void*)arr, 0, &IDmin_max);
    if (min_max == NULL)
        return (void)GetLastError();
    WaitForSingleObject(min_max, INFINITE);
    CloseHandle(min_max);

    average = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average_t, (void*)arr, 0, &IDaverage);
    if (average == NULL)
        return (void)GetLastError();
    WaitForSingleObject(average, INFINITE);
    CloseHandle(average);

  //  std::cout << "The result of the threads:" << std:: endl;
    printf("\nThe result of the threads:");
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
   // std::cout <<std:: endl<< " Thread3 done " << std::endl;
    printf("\nThread3 done:");
}

int main() {
    HANDLE main;
    DWORD IDmain;

    main = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main_t, NULL, 0, &IDmain);
    if (main == NULL)
        return GetLastError();
    WaitForSingleObject(main, INFINITE);
    CloseHandle(main);
}