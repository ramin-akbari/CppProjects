#include <iostream>
#include <vector>

void merge(std::vector<int> &arr,int left ,int mid ,int right){
    int ptr_left = left;
    int ptr_right = mid+1;
    int index = left;
    std::vector<int> temp(right-left+1);
    std::copy(arr.begin()+left,arr.begin()+right+1,temp.begin());

    while (ptr_left <= mid && ptr_right<= right){
        if (temp[ptr_left] < temp[ptr_right])
            arr[index] = temp[ptr_left++];
        else
            arr[index] = temp[ptr_right++];
        ++index;
    }

    while (ptr_left <= mid)
        arr[index++] = temp[ptr_left++];

    while (ptr_right <= right)
        arr[index++] = temp[ptr_right++];

}

void merge_sort(std::vector<int>& arr,int left,int right){
    if (left >= right)
        return;

    int mid = (left+right)/2;
    merge_sort(arr,left,mid);
    merge_sort(arr,mid+1,right);
    merge(arr,left,mid,right);
}




int main(){

    std::vector<int> a = {1,5,3,6,10};
    merge_sort(a,0,4);

    for(const auto &val:a){
        std::cout << val << "\n";
    }

    return 0;
}
