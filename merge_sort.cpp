#include <iostream>
#include <vector>

void merge(std::vector<int> &read,std::vector<int> &write,int left ,int mid ,int right){
    int ptr_left = left;
    int ptr_right = mid+1;
    int ptr_write = left;

    while (ptr_left <= mid && ptr_right<= right){
        if (read[ptr_left] < read[ptr_right])
            write[ptr_write] = read[ptr_left++];
        else
            write[ptr_write] = read[ptr_right++];
        ++ptr_write;
    }

    while (ptr_left <= mid)
        write[ptr_write++] = read[ptr_left++];

    while (ptr_right <= right)
        write[ptr_write++] = read[ptr_right++];

}




int main(){

    std::vector<int> a = {1,3,7,9,11,0,3,5,6,10};
    std::vector<int> b(10);
    merge(a,b,0,4,9);

    for (const auto &val :b)
        std::cout << val <<"\n";


    return 0;
}
