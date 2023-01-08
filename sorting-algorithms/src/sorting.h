#pragma once

#include <functional> // std::less
#include <iterator> // std::iterator_traits

namespace sort {

	// This is C++ magic which will allows our function
	// to default to using a < b if the comparator arg
	// is unspecified. It uses defines std::less<T>
	// for the iterator's value_type.
	//
	// For example: if you have a vector<float>, the 
	// iterator's value type will be float. std::less 
	// will select the < for sorting floats as the 
	// default comparator.
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept {
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
		using value_type      = typename _it::value_type;
		using reference       = typename _it::reference;
		using pointer         = typename _it::pointer;

		for (RandomIter i = begin; i != end; i++) {
			for (RandomIter j = begin; j < i; j++) {
				if (comp(*i, *j)) {
		 			swap(*i, *j);}
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		if (begin - end == 0) {
			return;
		}
		for (RandomIter i = begin + 1; i != end; i++) {
			RandomIter curr = i;
			RandomIter prev = i - 1;
			while (prev >= begin && comp(*curr, *prev)) {
				swap(*curr, *prev);
				curr--;
				prev--;
			}
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		if (begin - end == 0) {
			return;
		}
		for (RandomIter i = begin; i != end; i++) {
			RandomIter min = i;
			for (RandomIter j = i + 1; j != end; j++) {
				if (comp(*j, *min)) {
					swap(*j, *min);
				}
			}
		}
	}
}
