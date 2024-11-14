#include <iostream>
#include <vector>
#include <random>

void merge(std::vector<int> &arr,unsigned long left ,unsigned long mid ,unsigned long right){
    unsigned long ptr_left = left;
    unsigned long ptr_right = mid+1;
    unsigned long index = 0;
    std::vector<int> temp(right-left+1);

    while (ptr_left <= mid && ptr_right<= right){
        if (arr[ptr_left] < arr[ptr_right])
            temp[index] = arr[ptr_left++];
        else
            temp[index] = arr[ptr_right++];
        ++index;
    }

    while (ptr_left <= mid)
        temp[index++] = arr[ptr_left++];

    while (ptr_right <= right)
        temp[index++] = arr[ptr_right++];

    std::copy(temp.begin(),temp.end(),arr.begin()+left);

}

void merge_sort(std::vector<int>& arr,unsigned long left,unsigned long right){
    if (left >= right)
        return;
    unsigned long mid = (left + right)/2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge(arr,left,mid,right);
}


int main(){

    std::random_device rd;
    std::mt19937 gen(rd());
    int n = 10000000;

    // Define a distribution range for integers
    std::uniform_int_distribution<int> dist(1, 10000);

    std::vector<int> a(n);
    for (auto &val:a){
        val = dist(gen);
    }

    merge_sort(a,0,a.size()-1);


    return 0;
}
