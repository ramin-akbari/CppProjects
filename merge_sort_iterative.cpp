#include <iostream>
#include <vector>

unsigned long log2_rem(unsigned long x,unsigned long rem = 1){
    unsigned long count=0;
    unsigned long target = x/rem;
    while((2<<count++) < target);
    return count;
}

void merge(std::vector<int> &arr_read,std::vector<int>& arr_write, unsigned long left ,unsigned long mid ,unsigned long right){
    unsigned long ptr_left = left;
    unsigned long ptr_right = mid+1;
    unsigned long index = left;

    while (ptr_left <= mid && ptr_right<= right){
        if (arr_read[ptr_left] < arr_read[ptr_right])
            arr_write[index] = arr_read[ptr_left++];
        else
            arr_write[index] = arr_read[ptr_right++];
        ++index;
    }

    while (ptr_left <= mid)
        arr_write[index++] = arr_read[ptr_left++];

    while (ptr_right <= right)
        arr_write[index++] = arr_read[ptr_right++];
}

void merge_sort(std::vector<int>& arr_read){
    std::vector<int> arr_write(arr_read.size());
    auto n = log2_rem(arr_read.size());
    unsigned long window = 2;
    unsigned long mid = 1;
    for(unsigned long i=0;i<n;++i){
        unsigned long left = 0;
        while (left + window <= arr_read.size()){
            merge(arr_read,arr_write,left,left+mid-1,left+window-1);
            left += window;
        }
        if (arr_read.size()-left > 0){
            merge(arr_read,arr_write,left,left+mid-1,arr_read.size()-1);
        }
        std::swap(arr_read,arr_write);
        window *= 2;
        mid *= 2;
    }
    if((n&1)==1)
        std::copy(arr_read.begin(),arr_read.end(),arr_write.begin());
}


int main(){

    std::vector<int> a={11,4,6,9,17,8,1,3,5,2,13,7};
    merge_sort(a);
    for (auto val:a){
        std::cout << val << "\n";
    }

    return 0;
}

