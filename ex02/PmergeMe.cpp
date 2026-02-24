#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe() : arr1(), arr2(){}
PmergeMe::PmergeMe(const std::vector<int> arr1) : arr1(arr1), arr2(){}
PmergeMe::PmergeMe(const std::deque<int> arr2) : arr1(), arr2(arr2){}
PmergeMe::PmergeMe(const PmergeMe &other) : arr1(other.arr1), arr2(other.arr2){}
PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        arr1 = other.arr1;
        arr2 = other.arr2;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

void PmergeMe::make_pairs(std::vector<int> &arr, std::vector<std::pair<int, int> > &pairs, int &leftover, bool &has_leftover)
{
    has_leftover = false;
    size_t i = 0;
    while (i + 1 < arr.size())
    {
        pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        i += 2;
    }
    if (i < arr.size())
    {
        leftover = arr[i];
        has_leftover = true;
    }
}

void PmergeMe::sort_pairs(std::vector<std::pair<int, int> > &pairs)
{
    size_t i = 0;
    while (i < pairs.size())
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
        i++;
    }
}

static bool compare_by_second(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.second < b.second;
}

void PmergeMe::extract_bigger_smaller(std::vector<std::pair<int, int> > &pairs, std::vector<int> &bigger, std::vector<int> &smaller)
{
    // [1 8] [2 6]
    std::sort(pairs.begin(), pairs.end(), compare_by_second);

    size_t i = 0;
    while (i < pairs.size())
    {
        bigger.push_back(pairs[i].second);
        smaller.push_back(pairs[i].first);
        i++;
    }
}

static std::vector<int> build_insertion_order(int n)
{
    // Generate Jacobsthal numbers: 0, 1, 1, 3, 5, 11, 21, 43, ...
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while (jacob.back() < n)
        jacob.push_back(jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2]);

    // Build the insertion order from the Jacobsthal groups
    std::vector<int> order;
    for (size_t k = 1; k < jacob.size(); k++)
    {
        int high = jacob[k];
        if (high > n)
            high = n;
        int low = jacob[k - 1];
        // Insert from high down to low+1 (descending within each group)
        for (int i = high; i > low; i--)
            order.push_back(i - 1); // convert to 0-indexed
    }
    return order;
}

void PmergeMe::insert_smaller_into_bigger(std::vector<int> &bigger, std::vector<int> &smaller, int &leftover, bool has_leftover)
{
    if (smaller.empty())
        return;

    bigger.insert(bigger.begin(), smaller[0]);

    std::vector<int> order = build_insertion_order(static_cast<int>(smaller.size()));

    size_t i = 0;
    while (i < order.size())
    {
        int idx = order[i];
        if (idx == 0)
        {
            i++;
            continue; // already inserted
        }
        if (idx >= static_cast<int>(smaller.size()))
        {
            i++;
            continue; // safety bounds check
        }
        int value = smaller[idx];
        std::vector<int>::iterator pos = std::lower_bound(bigger.begin(), bigger.end(), value);
        bigger.insert(pos, value);
        i++;
    }
    if (has_leftover)
    {
        int value = leftover;
        std::vector<int>::iterator pos = std::lower_bound(bigger.begin(), bigger.end(), value);
        bigger.insert(pos, value);
    }
}

void PmergeMe::print_array(const std::vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::make_pairs(std::deque<int> &arr, std::deque<std::pair<int, int> > &pairs, int &straggler, bool &has_straggler){
    has_straggler = false;
    size_t i = 0;
    while (i + 1 < arr.size())
    {
        pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        i += 2;
    }
    if (i < arr.size())
    {
        straggler = arr[i];
        has_straggler = true;
    }
}
void PmergeMe::sort_pairs(std::deque<std::pair<int, int> > &pairs){
    size_t i = 0;
    while (i < pairs.size())
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
        i++;
    }
}
void PmergeMe::extract_bigger_smaller(std::deque<std::pair<int, int> > &pairs, std::deque<int> &bigger, std::deque<int> &smaller){
    std::sort(pairs.begin(), pairs.end(), compare_by_second);

    size_t i = 0;
    while (i < pairs.size())
    {
        bigger.push_back(pairs[i].second);
        smaller.push_back(pairs[i].first);
        i++;
    }
}
void PmergeMe::insert_smaller_into_bigger(std::deque<int> &bigger, std::deque<int> &smaller, int &leftover, bool has_leftover){
    if (smaller.empty())
        return;

    bigger.push_front(smaller[0]);

    std::vector<int> order = build_insertion_order(static_cast<int>(smaller.size()));

    size_t i = 0;
    while (i < order.size())
    {
        int idx = order[i];
        if (idx == 0)
        {
            i++;
            continue; // already inserted
        }
        if (idx >= static_cast<int>(smaller.size()))
        {
            i++;
            continue; // safety bounds check
        }
        int value = smaller[idx];
        std::deque<int>::iterator pos = std::lower_bound(bigger.begin(), bigger.end(), value);
        bigger.insert(pos, value);
        i++;
    }
    if (has_leftover)
    {
        int value = leftover;
        std::deque<int>::iterator pos = std::lower_bound(bigger.begin(), bigger.end(), value);
        bigger.insert(pos, value);
    }
}
void PmergeMe::print_array(const std::deque<int> &arr){
    for (size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}