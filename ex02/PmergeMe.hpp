#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>

class PmergeMe{
    private:
        std::vector<int> arr1;
        std::deque<int> arr2;
    public:
        PmergeMe();
        PmergeMe(const std::vector<int> arr1);
        PmergeMe(const std::deque<int> arr1);
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();
        // vector sort part
        void make_pairs(std::vector<int> &arr, std::vector<std::pair<int, int> > &pairs, int &straggler, bool &has_straggler);
        void sort_pairs(std::vector<std::pair<int, int> > &pairs);
        void insert_smaller_into_bigger(std::vector<int> &bigger, std::vector<int> &smaller, int &leftover, bool has_leftover);
        void ford_johnson_sort(std::vector<int> &arr);
        void print_array(const std::vector<int> &arr);

        // deque sort part
        void make_pairs(std::deque<int> &arr, std::deque<std::pair<int, int> > &pairs, int &straggler, bool &has_straggler);
        void sort_pairs(std::deque<std::pair<int, int> > &pairs);
        void insert_smaller_into_bigger(std::deque<int> &bigger, std::deque<int> &smaller, int &leftover, bool has_leftover);
        void ford_johnson_sort(std::deque<int> &arr);
        void print_array(const std::deque<int> &arr);
};


#endif