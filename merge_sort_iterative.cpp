#include <iostream>
#include <vector>
#include <random>

unsigned long log2_rem(unsigned long x,unsigned long rem = 1){
    unsigned long count=0;
    unsigned long target = x/rem;
    while((2<<count++) < target);
    return count;
}

void insertion_sort(std::vector<int>& a,unsigned long left,unsigned long right){
    unsigned long ptr = left+1;
    unsigned long index;
    while(ptr <= right){
        index = ptr;
        while(index>left && a[index]<a[index-1]){
            std::swap(a[index],a[index-1]);
            --index;
        }
        ++ptr;
    }
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

void merge_sort(std::vector<int>& arr_read, unsigned long window = 45){
    std::vector<int> arr_write(arr_read.size());
    auto n = log2_rem(arr_read.size(),window);
    unsigned long left = 0;
    while (left + window <= arr_read.size()){
        insertion_sort(arr_read,left,left+window-1);
        left += window;
    }
    insertion_sort(arr_read,left,arr_read.size()-1);
    unsigned long merged_size = window*2;
    for(unsigned long i=0;i<n;++i){
        left = 0;
        while (left + merged_size <= arr_read.size()){
            merge(arr_read,arr_write,left,left+window-1,left+merged_size-1);
            left += merged_size;
        }
        if (arr_read.size()-left > 0){
            merge(arr_read,arr_write,left,std::min(left+window-1,arr_read.size()-1),arr_read.size()-1);
        }
        std::swap(arr_read,arr_write);
        window *= 2;
        merged_size *= 2;
    }
    if((n&1)==1)
        std::copy(arr_read.begin(),arr_read.end(),arr_write.begin());
}


int main(){

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    int n = 100000;

    // Define a distribution range for integers
    std::uniform_int_distribution<int> dist(1, n);

    std::vector<int> a(n);
    for (auto &val:a){
        val = dist(gen);
    }
    std::vector<int> b = a;
    std::sort(b.begin(), b.end());
    merge_sort(a);

    for (int i=0;i<n;i++){
        if(a[i]!=b[i])
            std::cout<<"wrong\n";
    }


    return 0;
}

