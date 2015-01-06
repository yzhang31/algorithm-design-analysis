#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

static int recursive_count = 0;
static unsigned long inversion_count = 0;

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

bool split_array(vector<int>& source, vector<int>& left, vector<int>& right)
{
        size_t array_size = source.size();

        if(array_size <= 1)
            return false;

        left.resize(array_size / 2);

        for(size_t i = 0; i < left.size(); i++)
        {
            left[i] = source[i];
        }

        right.resize(array_size - left.size());
        for(size_t i = 0; i < right.size(); i++)
        {
            right[i] = source[left.size() + i];
        }
        return true;
}

void merge_sorted_array(vector<int>& dest, vector<int>& left, vector<int>& right)
{
    assert(dest.size() == left.size() + right.size());
    size_t length = dest.size();
    size_t i = 0, j = 0;
    for (size_t k = 0; k < length; ++k) {
        if( i < left.size() && j >= right.size())
        {
            dest[k] = left[i];
            i++;
        }
        else if( j < right.size() && i >= left.size())
        {
            dest[k] = right[j];
            j++;
        }
        else if (left[i] < right[j]) {
            dest[k] = left[i];
            i++;
        }
        else
        {
            dest[k] = right[j];
            inversion_count += (long)(left.size() - i);
            j++;
        }

    }
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


void merge_sort_v1(vector<int>& input)
{
    recursive_count++;
    if (!is_sorted_array(input))
    {
        vector<int> left, right;
        split_array(input, left, right );
        merge_sort_v1(left);
        merge_sort_v1(right);
        merge_sorted_array(input, left, right);
    }
}

void merge_sort_v2(vector<int>& input)
{
    recursive_count++;
    vector<int> left, right;
    if (split_array(input, left, right ))
    {
        merge_sort_v2(left);
        merge_sort_v2(right);
        merge_sorted_array(input, left, right);
    }
}

void bubble_sort(vector<int>& input)
{
    for(size_t i = 0; i < input.size()- 1; i++)
    {
        for (size_t j = i + 1; j < input.size(); j++)
        {
            if (input[i] >  input[j])
            {
                int temp = input[i];
                input[i] = input[j];
                input [j] = temp;
            }
        }
    }
}

int main()
{
    vector<int> numbers = read_int_array_from_file("IntegerArray.txt");  // cost 0.1s

    cout << "Input random order integer array size:" << numbers.size() << endl;

    //bubble_sort(numbers);   // 124 s
    merge_sort_v1(numbers);     // 0.78 s 154893 recursive call.
    //merge_sort_v2(numbers);   // 1.0 s, 199999 recursive call.

    cout << "Array has been sorted: " << is_sorted_array(numbers) << endl;
    cout << "Recursive Call count:" << recursive_count << endl;
    cout << "Inversion count:" << inversion_count << endl;

    return 0;
}


