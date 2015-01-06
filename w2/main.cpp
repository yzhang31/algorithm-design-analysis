#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <string>
#include <cstdlib>
#include <cassert>

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

using namespace std;

int main()
{
    vector<int> numbers = read_int_array_from_file("QuickSort.txt");
    cout << "Input random order integer array size:" << numbers.size() << endl;
    return 0;
}
