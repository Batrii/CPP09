#include "PmergeMe.hpp"
#include <sstream>
#include <time.h>

static int put_args_in_vector_deque(int argc, char **argv, std::vector<int> &numbers, std::deque<int> &numbers_deque)
{
    for (int i = 1; i < argc; i++)
    {
        std::stringstream ss(argv[i]);
        int num;
        if (ss >> num)
        {
            if (num < 0)
            {
                std::cerr << "Error" << std::endl;
                return 1;
            }
            numbers.push_back(num);
            numbers_deque.push_back(num);
        }
        else
        {
            std::cerr << "Invalid number: " << argv[i] << std::endl;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <numbers...>" << std::endl;
        return 1;
    }
    std::vector<int> numbers;
    std::deque<int> numbers_deque;
    if (put_args_in_vector_deque(argc, argv, numbers, numbers_deque) != 0)
        return 1;
    clock_t start, end;
    start = clock();
    PmergeMe pmergeMe(numbers);

    std::vector<std::pair<int, int> > pairs;
    std::deque<std::pair<int, int> > pairs1;
    std::vector<int> bigger, smaller;
    std::deque<int> bigger1, smaller1;
    int leftover = 0;
    bool has_leftover = false;
    std::cout << "Before: ";
    pmergeMe.print_array(numbers); 
    pmergeMe.make_pairs(numbers, pairs, leftover, has_leftover);
    pmergeMe.sort_pairs(pairs);
    pmergeMe.extract_bigger_smaller(pairs, bigger, smaller);
    pmergeMe.insert_smaller_into_bigger(bigger, smaller, leftover, has_leftover);
    std::cout << "After: ";
    pmergeMe.print_array(bigger);
    end = clock();
    // the result in us
    double time_taken = double(end - start) * 1000000 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << time_taken << " us" << std::endl;

    start = clock();
    pmergeMe.make_pairs(numbers_deque, pairs1, leftover, has_leftover);
    pmergeMe.sort_pairs(pairs1);
    pmergeMe.extract_bigger_smaller(pairs1, bigger1, smaller1);
    pmergeMe.insert_smaller_into_bigger(bigger1, smaller1, leftover, has_leftover);

    end = clock();
    time_taken = double(end - start) * 1000000 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << numbers_deque.size() << " elements with std::deque : " << time_taken << " us" << std::endl;
    return 0;
}