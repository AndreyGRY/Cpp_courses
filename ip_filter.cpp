#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

 #include "ip_filter.h"

#define UNUSED(variable) (void)variable
#define COLUMNS_NUMBER  4 //  number of fields in ip address

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


void convert_to_int(std::vector<std::vector<std::string>> *_ip_pool, std::vector<std::vector<int>> *_intVec)
{
    std::vector<std::vector<std::string>> __ip_pool= *_ip_pool;

    for (size_t i=0; i<__ip_pool.size(); i++)
    {
        std::vector<int> _intRow;
        for (size_t j=0; j<__ip_pool[i].size(); j++)
        {
            _intRow.push_back(std::stoi(__ip_pool[i][j]));
        }
        _intVec->push_back(_intRow);
    }
}

void ip_sort(std::vector<std::vector<int>> *_intVec)
{
    std::sort(_intVec->begin(), _intVec->end(),
    [](const auto& v1, const auto& v2) 
    { return v1 > v2; });
}

void out_sorted(std::vector<std::vector<int>> *_intVec)
{
    for(std::vector<std::vector<int> >::const_iterator ip = _intVec->cbegin(); ip != _intVec->cend(); ++ip)
    {
        for(std::vector<int>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void out_sorted(std::vector<std::vector<int>> *_intVec, int byte_1st)
{
    for(std::vector<std::vector<int> >::const_iterator ip = _intVec->cbegin(); ip != _intVec->cend(); ++ip)
    {
        for(std::vector<int>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend() + 1; ++ip_part)
        {
            if (*ip->cbegin() == byte_1st)
            {
                if (ip_part == ip->cend())
                {
                    std::cout << std::endl;
                }
                else 
                {
                   if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                std::cout << *ip_part;  
                }
            }
        }
    }
}

void out_sorted(std::vector<std::vector<int>> *_intVec, int byte_1st, int byte_2st)
{
    for(std::vector<std::vector<int> >::const_iterator ip = _intVec->cbegin(); ip != _intVec->cend(); ++ip)
    {
        for(std::vector<int>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend() + 1; ++ip_part)
        {
            if (*ip->cbegin() == byte_1st && *(ip->cbegin() + 1) == byte_2st)
            {
                if (ip_part == ip->cend())
                {
                    std::cout << std::endl;
                }
                else 
                {
                   if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                std::cout << *ip_part;  
                }
            }
        }
    }
}

void out_sorted_any(std::vector<std::vector<int>> *_intVec, int byte)
{
    bool filter_condition = false;
    for(std::vector<std::vector<int> >::const_iterator ip = _intVec->cbegin(); ip != _intVec->cend(); ++ip)
    {
        for(std::vector<int>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend() + 1; ++ip_part)
        {
            if (filter_condition == true)
            {
                if (ip_part == ip->cend())
                {
                    std::cout << std::endl;
                    filter_condition = false;
                }
                else 
                {
                   if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                std::cout << *ip_part;  
                }
            }
            else
            {
                if (*ip_part == byte)
                {
                    filter_condition = true;
                    ip_part = ip->cbegin()-1;
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
     try
    {
        std::vector<std::vector<std::string>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // ! On Windows stoi() doesn't work properly on [0][0]'st element,
        // however cout() prints valid "113" value (?). Working good on Linux.

        std::vector<std::vector<int>> intVec;

        // TODO reverse lexicographically sort

        convert_to_int(&ip_pool, &intVec);

        ip_sort(&intVec);

       out_sorted(&intVec);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
       out_sorted(&intVec, 1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
       out_sorted(&intVec, 46, 70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
       out_sorted_any(&intVec, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46

        UNUSED(argc);
        UNUSED(argv);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
