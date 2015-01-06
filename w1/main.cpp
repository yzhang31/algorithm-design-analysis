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

void split_array(vector<int>& source, vector<int>& left, vector<int>& right)
{
        size_t array_size = source.size();

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


void merge_sort(vector<int>& input)
{
    recursive_count++;
    if (!is_sorted_array(input))
    {
        vector<int> left, right;
        split_array(input, left, right );
        merge_sort(left);
        merge_sort(right);
        merge_sorted_array(input, left, right);
    }
}

int main()
{
    vector<int> numbers = read_int_array_from_file("IntegerArray.txt");

    cout << "Input random order integer array size:" << numbers.size() << endl;

    merge_sort(numbers);

    cout << "Array has been sorted: " << is_sorted_array(numbers) << endl;
    cout << "Recursive Call count:" << recursive_count << endl;
    cout << "Inversion count:" << inversion_count << endl;

    return 0;
}


