// ComparingSorts2.cpp
// Created 10/31/2018 9:23:21 AM

#include <iostream>
#include <iomanip>
#include <vector>

#include "sorts.h"
#include "stopwatch.h"
#include "uniformrandom.h"

// Displays the elements of a vector using an output stream object.
// Returns the output stream object so operator<< can be chained naturely.
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << '{';
	int n = vec.size();
	if (n > 0) {
		os << vec[0];
		for (int i = 1; i < n; i++)
			os << ", " << vec[i];
	}
	os << '}';
	return os;
}

template <typename Func>
void test_sort(const char *name, Func sort, const std::vector<int>& vec) {
	std::cout << std::right << std::fixed << std::showpoint
		<< std::setprecision(3);
	std::cout << std::setw(20) << name;
	auto working = vec;
	// Make an answer key
	auto sorted = vec;
	std::sort(sorted.begin(), sorted.end());

	//std::cout << "Before: " << working <<  '\n';
	Stopwatch timer;
	timer.start();
	sort(working.begin(), working.end());
	timer.stop();
	//std::cout << "After:  " << working << '\n';
	std::cout << std::setw(10) << timer.elapsed() << " sec  ";
	if (working == sorted)
		std::cout << "Sorted correctly\n";
	else
		std::cout << "**** Sort INCORRECT ****\n";
}



int main() {
	const int SIZE = 100;   // Size of the sequence
	UniformRandomGenerator rng(0, 3 * SIZE);
	std::vector<int> original;
	for (int i = 0; i < SIZE; i++)
		original.push_back(rng());  // Add a pseudorandom integer
	//std::cout << original << '\n';

	// Specify the exact type of the sorting functions
	using func_type = decltype(selection_sort<decltype(original.begin())>);

	test_sort<func_type>("Selection sort", selection_sort, original);
	test_sort<func_type>("Insertion sort", insertion_sort, original);
	test_sort<func_type>("Exchange sort", exchange_sort, original);
	test_sort<func_type>("Heapsort", heapsort, original);
	test_sort<func_type>("Quicksort", quicksort, original);
	test_sort<func_type>("Standard C++ sort", standard_sort, original);
	test_sort<func_type>("Standard C sort", standard_qsort, original);
	system("pause");
}