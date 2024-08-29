#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(const std::string &str, char d);
void convert_to_int(std::vector<std::vector<std::string>> *_ip_pool, std::vector<std::vector<int>> *_intVec);
void ip_sort(std::vector<std::vector<int>> *_intVec);
void out_sorted(std::vector<std::vector<int>> *_intVec);
void out_sorted(std::vector<std::vector<int>> *_intVec, int byte_1st);
void out_sorted(std::vector<std::vector<int>> *_intVec, int byte_1st, int byte_2st);
void out_sorted_any(std::vector<std::vector<int>> *_intVec, int byte);
