# Sorting Vectors - Oral Report

For the sorting vectors report, you will be asked three questions to test your conceptual understanding of the assignment. Some questions will expand on the concepts you learned. You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each are sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient," "incomplete," or "insufficient" (0 points). The point value for "mostly sufficient" and "incomplete" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

Questions seven and five require you to present your code. Finally, question eight require you to prepare results from running the `main.cpp`.

## Question 1

What is the time complexity of swap when using type `std::string`? Now assume `std::move` was **not** used to implement swap. What is the time complexity on `std::string`? Explain your reasoning.

O(1) because only moving same number of objects every time. 
Still O(1) because only difference is to make temporary variables.

## Question 2

Consider the statement: 
```C++
using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>
```
What is the purpose of `std::less` in the STL? Provided a `std::vector<char>` iterator, to which type does `typename std::iterator_traits<RandomIter>::value_type` resolve? What default behavior does `sort::less_for_iter` define for the comparator `comp`?

std::less compares two objects. value_type resolves char's because that is what is contained in the vector. less_for_iter returns a boolean on whether the first element is less than the second. 

## Question 3

What is a comparator? What are the parameters for a comparator and the return type? How did you use the comparator to determine the relative ordering of two elements?

A comparator compares two objects. In this case, it also keeps track of total number of comparisons. Parameters are two things being compared and it returns a boolean. Comparator was used in an if statement to determine when a swap was necessary. 

## Question 4

Without providing an alternative comparator, `sort::insertion` will sort elements in ascending order. How would you call `sort::insertion` to sort elements in descending order (greatest to least)? (Be prepared to provide implementation details, including how to call `sort::insertion`.)

First, call 'sort::insertion' to sort elements in ascending order. Then use a stack to reverse order since it is LIFO. Push all elements to stack, then pop all back. 

## Question 5

Each algorithm you implemented gradually grows a sorted subarray. In each algorithm, there is a contiguous set of elements within the list that is guaranteed to be sorted on each iteration.

Provided your implementation, where is the sorted subarray located within the input array? Between successive iterations, how does the sorted subarray grow?

Bubble sort - end is sorted first
Selection sort - beginning is sorted first
Insertion sort - beginning is sorted after elements are inserted to the beginning

## Question 6

How many comparisons does each algorithm perform in the best case? (Provide a formula based on the length `n` of the input array.) For each algorithm, what is the configuration of the input array which produces the best-case outcome?

Selection O(n^2) always
Bubble and insertion O(n) if array is already sorted and no switches have to be made. 

## Question 7

Would your sorts still work if `RandomIter` was not a random iterator, but instead a "bidirectional" iterator that can only go forward or backward one element at a time (e.g. `typename std::list<T>::iterator`)?

Yes. All 3 of my sorting algorithms only went forward or backwards one element at a time. This is not true for algorithms that go forward or backwards multiple elements at a time. 

## Question 8

Use `main.cpp` to test the number of comparisons performed by bubble, insertion, and selection on randomly generated data. (Save your results to discuss them during the report.) Which algorithm performs the fewest comparisons? What mechanism causes this algorithm to perform many fewer comparisons when sorting randomly generated data?

Insertion sort sorts the array in the fewest comparisons if it is already sorted. Insertion sort when perfomed with randomly generated data sorts the array at almost half the number of comparisons as bubble and selection sort. The while loop causes this to happen because it allows for the algorithm to break out of the loop earlier compared to just iterating from beginning to end. 

## Question 9

How might you write a `CustomComparator` that, when used by any of the sorts, will rearrange all of the even numbers to the beginning of the container and the odd numbers to the end?

*Hint*: You do not have to sort the even or the odd numbers with respect to themselves; you only need to ensure that every even number precedes all odd numbers.

*Hint*: Look at the `CustomComparator` class written in [`main.cpp`](src/main.cpp).

The CustomComparator should return true if the first parameter is odd and the second parameter is even. By doing this, the algorithm will only switch the two parameters are odd and even.  