#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <string>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <ctime>

using namespace std;


vector<int> read_int_array_from_file(const std::string& file_name)
{
    std::vector<int> values;
    std::ifstream fs(file_name);

    if (fs.is_open())
    {
        cout << "Open file successfully!" << endl;
    }
    else
    {
        cout << "Failed to open file!" << file_name << endl;
        return values;
    }

    for (array<char,7>a; fs.getline(&a[0], 7);)
    {
        values.push_back(atoi(&a[0]));
    }

    fs.close();
    return values;
}

bool is_sorted_array(vector<int> & array)
{
    for (size_t i = 0; i < array.size() - 1 ; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}


typedef vector<int>::iterator ArrayIter;

ArrayIter partition(ArrayIter begin, ArrayIter end)
{
    ArrayIter pivot = begin;
    ArrayIter i = begin + 1;
    for(ArrayIter j = begin + 1; j < end; j++)
    {
        if (*j < *pivot)
        {
            iter_swap(i,j);
            i++;
        }
    }
    iter_swap(pivot, i - 1);
    return i - 1;
}

ArrayIter pivot_with_first(ArrayIter begin, ArrayIter end)
{
    return begin;
}

ArrayIter pivot_with_last(ArrayIter begin, ArrayIter end)
{
    return end - 1;
}

ArrayIter pivot_with_random(ArrayIter begin, ArrayIter end)
{
    double random = (double)rand() / (double)RAND_MAX;
    int pos = (int) ((end - begin) * random);
    return begin + pos;
}

ArrayIter pivot_with_mean_in_three(ArrayIter begin, ArrayIter end)
{

    long length = end - begin;
    ArrayIter first = begin;
    ArrayIter last = end - 1;
    ArrayIter mean = length % 2 == 0 ? begin + length / 2 - 1 : begin + length / 2;

    vector<int> v;
    v.push_back(*first);
    v.push_back(*last);
    v.push_back(*mean);
    std::sort(v.begin(),v.end());

    if(*first == v[1])
        return first;
    else if(*last == v[1])
        return last;
    else if(*mean == v[1])
        return mean;
    else
        assert(false);
}

int quicksort(ArrayIter begin, ArrayIter end,
               ArrayIter(*select_pivot_func)(ArrayIter, ArrayIter))
{
    int comparison_number = 0;
    if (end - begin > 1)
    {
       comparison_number += end - begin - 1;
       ArrayIter pivot = select_pivot_func(begin, end);
       iter_swap(pivot, begin);
       ArrayIter partition_positon = partition(begin,end);
       comparison_number += quicksort(begin, partition_positon, select_pivot_func);
       comparison_number += quicksort(partition_positon + 1, end, select_pivot_func);
    }
    return comparison_number;
}

int main()
{
    vector<int> origin_array = read_int_array_from_file("QuickSort.txt");
    cout << "Input random order integer array size:" << origin_array.size() << endl;

    vector<int> numbers;

    numbers = origin_array;
    int comparison_number_fisrt_pivot =
        quicksort(numbers.begin(), numbers.end(), &pivot_with_first);
    assert(is_sorted_array(numbers));

    numbers = origin_array;
    int comparison_number_last_pivot =
        quicksort(numbers.begin(), numbers.end(), &pivot_with_last);
    assert(is_sorted_array(numbers));

    numbers = origin_array;
    int comparison_number_mean_in_three_pivot =
        quicksort(numbers.begin(), numbers.end(), &pivot_with_mean_in_three);
    assert(is_sorted_array(numbers));

    // Set a random see with system elapse time, in order that
    // get different random number sequence every time.
    srand((unsigned)time(0));
    
    numbers = origin_array;
    int comparison_number_random =
        quicksort(numbers.begin(), numbers.end(), &pivot_with_random);
    assert(is_sorted_array(numbers));

    cout << "Array has been sorted: " << is_sorted_array(numbers) << endl;
    cout << "Use first as pivot, comparison count:" << comparison_number_fisrt_pivot << endl;
    cout << "Use last as pivot, comparison count:" << comparison_number_last_pivot << endl;
    cout << "Use mean in three as pivot, comparison count:" << comparison_number_mean_in_three_pivot << endl;
    cout << "Use random as pivot, comparison count:" << comparison_number_random << endl;
    return 0;
}
