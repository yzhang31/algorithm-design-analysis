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

static unsigned int comparison_number = 0;

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

ArrayIter partition_use_first(ArrayIter begin, ArrayIter end)
{
    if (end - begin == 1)
        return begin;

    return partition( begin,  end);
}

ArrayIter partition_use_last(ArrayIter begin, ArrayIter end)
{
    if (end - begin == 1)
        return begin;

    iter_swap(end - 1, begin);

    return partition( begin,  end);
}


ArrayIter get_mean_in_three(ArrayIter begin, ArrayIter end)
{

    int length = end - begin;
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


ArrayIter partition_use_mean_in_three(ArrayIter begin, ArrayIter end)
{
    if (end - begin == 1)
        return begin;

    iter_swap(get_mean_in_three(begin, end), begin);

    return partition( begin,  end);
}

void quicksort(ArrayIter begin, ArrayIter end)
{
    if (end - begin > 1)
    {
       comparison_number += end - begin - 1;
       //ArrayIter pivotPos = partition_use_first(begin, end);
       //ArrayIter pivotPos = partition_use_last(begin, end);
       ArrayIter pivotPos = partition_use_mean_in_three(begin, end);
       quicksort(begin, pivotPos);
       quicksort(pivotPos + 1, end);
    }
}



int main()
{
    vector<int> numbers = read_int_array_from_file("QuickSort.txt");
    cout << "Input random order integer array size:" << numbers.size() << endl;

    quicksort(numbers.begin(), numbers.end());

    cout << "Array has been sorted: " << is_sorted_array(numbers) << endl;
    cout << "comparison count:" << comparison_number << endl;
    return 0;
}
