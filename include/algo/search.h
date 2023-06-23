#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>

// Iterative Binary Search algorithm
template <typename T>
int binary_search(const std::vector<T>& v_nums, const T& target)
{
    int i_ans = -1;
    if (v_nums.empty())
        return i_ans;
    long unsigned int left = 0, mid  = v_nums.size() / 2, right = v_nums.size() - 1;
    while (left <= right)
    {
        if (v_nums.at(mid) == target)
        {
            i_ans = mid;
            break;
        } 
        if (mid == 0 || mid == v_nums.size() - 1)
            return i_ans;
        if (v_nums.at(mid) > target)
        {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
        mid = (left + right) / 2;
    }
    return i_ans;
}

#endif     // _SEARCH_H_