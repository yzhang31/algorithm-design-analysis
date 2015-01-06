#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <string>
#include <cstdlib>

using namespace std;

vector<int> read_int_array_from_file(const std::string& file_name)
{
    std::ifstream fs(file_name);

    if (fs.is_open())
        cout << "Open file successfully" << endl;
    else
        cout << "Failed to open file" << file_name << endl;
        
    std::vector<int> values;
    for (array<char,7>a; fs.getline(&a[0], 7);)
    {
        values.push_back(atoi(&a[0]));
    }

    cout << "Array size:" << values.size() << endl;

    fs.close();
    return values;
}

void split_vector(vector<int>& source, vector<int>& left, vector<int>& right)
{
        size_t array_size = source.size();
        size_t left_array_size = array_size / 2;
        size_t right_array_size = array_size - left_array_size;

        vector<int> left_array;
        left_array.resize(left_array_size);

        vector<int> right_array;
        right_array.resize(right_array_size);

        for(size_t i = 0; i < left_array_size; i++)
        {
            left_array[i] = source[i];
        }

        for(size_t i = 0; i < right_array_size; i++)
        {
            right_array[i] = source[left_array_size + i];
        }
}

long merge_sort(vector<int>& input_array)
{
    size_t array_size = input_array.size();
    if (array_size > 1)
    {
        vector<int> left, right;
        split_vector(input_array, left, right );
        merge_sort(left);
        merge_sort(right);
    }
    return 0L;
}

int main()
{
    read_int_array_from_file("IntegerArray.txt");
    return 0;
}


