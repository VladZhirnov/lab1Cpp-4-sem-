#include <iostream>
#include <iomanip>
#include <functions/header.h>


void main() {
    std::vector<int> old_vector = { 3, 2, 2, 4, 4 };
    std::vector<int> new_vector = create_vector_with_dublicates(old_vector);
    for (int val : new_vector) std::cout << val << " ";

    //Tree
    //Tree tree;
    //std::cout << "Average time to fill tree with 1000 elements: " << tree.measure_fill_time(1000) << std::endl;
    //std::cout << "Average time to fill tree with 10000 elements: " << tree.measure_fill_time(10000)  << std::endl;
    //std::cout << "Average time to fill tree with 100000 elements: " << tree.measure_fill_time(100000) << std::endl;

    //std::cout << "Average time to search in tree with 1000 elements: " << std::fixed << std::setprecision(8) << tree.measure_search_time(1000) << std::endl;
    //std::cout << "Average time to search in tree with 10000 elements: " << std::fixed << std::setprecision(8) << tree.measure_search_time(10000) << std::endl;
    //std::cout << "Average time to search in tree with 100000 elements: " << std::fixed << std::setprecision(8) << tree.measure_search_time(100000) << std::endl;

    //std::cout << "Average time to insert and delete in tree with 1000 elements: " << std::fixed << std::setprecision(8) << tree.measure_insert_and_erase_time(1000) << std::endl;
    //std::cout << "Average time to insert and delete in tree with 10000 elements: " << std::fixed << std::setprecision(8) << tree.measure_insert_and_erase_time(10000) << std::endl;
    //std::cout << "Average time to insert and delete in tree with 100000 elements: " << std::fixed << std::setprecision(8) << tree.measure_insert_and_erase_time(100000) << std::endl;

    ////Vector
    //std::cout << "Average time to fill vector with 1000 elements: " << std::fixed << std::setprecision(8) << measure_fill_time_vector(1000) << std::endl;
    //std::cout << "Average time to fill vector with 10000 elements: " << std::fixed << std::setprecision(8) << measure_fill_time_vector(10000) << std::endl;
    //std::cout << "Average time to fill vector with 100000 elements: " << std::fixed << std::setprecision(8) << measure_fill_time_vector(100000) << std::endl;

    //std::cout << "Average time to search in vector with 1000 elements: " << std::fixed << std::setprecision(8) << measure_search_time_vector(1000) << std::endl;
    //std::cout << "Average time to search in vector with 10000 elements: " << std::fixed << std::setprecision(8) << measure_search_time_vector(10000) << std::endl;
    //std::cout << "Average time to search in vector with 100000 elements: " << std::fixed << std::setprecision(8) << measure_search_time_vector(100000) << std::endl;

    //std::cout << "Average time to insert and delete in vector with 1000 elements: " << std::fixed << std::setprecision(8) << measure_insert_and_erase_time_vector(1000) << std::endl;
    //std::cout << "Average time to insert and delete in vector with 10000 elements: " << std::fixed << std::setprecision(8) << measure_insert_and_erase_time_vector(10000) << std::endl;
    //std::cout << "Average time to insert and delete in vector with 100000 elements: " << std::fixed << std::setprecision(8) << measure_insert_and_erase_time_vector(100000) << std::endl;
}