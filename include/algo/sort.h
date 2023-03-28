#ifndef SORT_H_
#define SORT_H_

#include <vector>
#include <deque>


template <typename E>
void merge(std::vector<E>& v,
            const int& start, const int& mid, const int& end)
{
    auto n1 = mid - start, n2 = end - mid;
    std::deque<int> d1, d2;
    for (int i = 0; i <= n1; ++i)
        d1.push_back(v.at(start + i));
    for (int i = 1; i <= n2; ++i)
        d2.push_back(v.at(mid + i));

    auto k = 0;
    while (!d1.empty() && !d2.empty())
    {
        if (d1.front() < d2.front())
        {
            v.at(start + k) = d1.front();
            d1.pop_front();
        } else {
            v.at(start + k) = d2.front();
            d2.pop_front();
        }
        ++k;
    }

    while (!d1.empty())
    {
        v.at(start + k) = d1.front();
        d1.pop_front();
        ++k;
    }

    while (!d2.empty())
    {
        v.at(start + k) = d2.front();
        d2.pop_front();
        ++k;
    }

    return;
}

template <typename E>
void _merge_sort(std::vector<E>& v, const int& start, const int& end)
{
    if (start >= end)
        return;
    auto mid = (start + end) / 2;
    _merge_sort(v, start, mid);
    _merge_sort(v, mid + 1, end);
    merge(v, start, mid, end);
    return;
}

template <typename E>
void merge_sort(std::vector<E>& v)
{
    if (v.size() < 2)
        return;
    _merge_sort(v, 0, v.size() - 1);
    return;
}

#endif  // SORT_H_