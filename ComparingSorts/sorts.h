#ifndef SORTS_H_INCLUDED
#define SORTS_H_INCLUDED

#include <algorithm>  
//Adam Angel and Rick Halterman
// Performs a selection sort on the sequence [begin...end).
template <typename Iter>
void selection_sort(Iter begin, Iter end) {
	// Add your code here . . .
	if (begin != end) {
		for (auto iter = begin; iter != end - 1; iter++) {
			Iter small = iter;
			for (auto rest = iter + 1; rest != end; rest++)
				if (*rest < *small)
					small = rest;
			if (iter != small)
				std::swap(*iter, *small);
		}
	}
}

// Performs an insertion sort on the sequence [begin...end).
template <typename Iter>
void insertion_sort(Iter begin, Iter end) {
	if (begin != end) {
		for (auto iter = begin + 1; iter != end; iter++) {
			auto key = *iter;
			Iter pos = iter;
			while (pos > begin && *(pos - 1) > key) {
				*pos = *(pos - 1);
				pos--;
			}
			*pos = key;
		}
	}
}

// Performs an exchange (bubble) sort on the sequence [begin...end).
template <typename Iter>
void exchange_sort(Iter begin, Iter end) {
	// Add your code here . . .
	int n = std::distance(begin, end);
	int k = 0;
	bool sorted = false;
	while (k < n - 1 && !sorted) {
		sorted = true;
		for (auto iter = begin; iter != end - k - 1; iter++) {
			if (*iter > *(iter + 1)){
			std::swap(*iter, *(iter + 1));
			sorted = false;
			}
		}
	}
}

// Performs a Heapsort on the sequence [begin...end).
template <typename Iter>
void heapsort(Iter begin, Iter end) {
	std::make_heap(begin, end);
	std::sort_heap(begin, end);
}

// Partitions the sequence [p...r] to move the pivot (last element of the 
// sequence) to its proper place.
template <typename Iter>
static Iter partition(Iter p, Iter r) {
	// Add your code here . . .
	auto x = *r;
	Iter i = p;
	for (Iter j = p; j <= r - 1; j++) {
		if (*j <= x) {
			std::swap(*i, *j);
			i++;
		}
	}
	std::swap(*i, *r);
	return i;  // You will need to change the return value
}

// Performs Quicksort on the sequence [p...r]
template <typename Iter>
static void qsort(Iter p, Iter r) {
	if (p != r) {
		Iter j = partition(p, r);
		if (j != p) qsort(p, j - 1);
		if (j != r) qsort(j + 1, r);
	}
	
}

// Performs a Quicksort on the sequence [begin...end).
// (No need to change this code)
template <typename Iter>
void quicksort(Iter begin, Iter end) {
	//  Nothing to do if the sequence has fewer than two elements
	if (distance(begin, end) > 1)
		qsort(begin, end - 1); // Iterators set to first and last elements
}

// Calls the C++ STL std::sort function.
// (No need to change this code)
template <typename Iter>
inline void standard_sort(Iter begin, Iter end) {
	std::sort(begin, end);
}


// Calls the C qsort function.
// (No need to change this code)
template <typename Iter>
inline void standard_qsort(Iter begin, Iter end) {
	// Some C++ voodoo to determine the type of values
	// stored in the sequence to which the iterators point.
	using ElementType = typename std::iterator_traits<Iter>::value_type;
	// Supply C's qsort function with the arguments it expects
	qsort(&*begin, std::distance(begin, end), sizeof(ElementType),
		[](const void *a, const void *b) { // Comparer function expected by C's qsort
		ElementType m = *static_cast<const ElementType *>(a);
		ElementType n = *static_cast<const ElementType *>(b);
		if (m < n)
			return -1;
		else if (m > n)
			return 1;
		else
			return 0;
	});
}


#endif
