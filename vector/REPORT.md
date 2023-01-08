# Vector Report

In order to promote a more expansive understanding of this assignment and the programming concepts you practiced, we will be conducting oral reports. For the vector report, you will be asked three questions to test your conceptual understanding of the assignment. Some questions will expand on the concepts you learned.

You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each is sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient" or "insufficient" (0 points). The point value for "mostly sufficient" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

### Example report:

**Question 1:** What is the worst-case runtime of the following function?

```C++
int & find(const std::vector<int> & vec, int item) { 
	auto it = vec.begin()
	for(; it != vec.end(); it++)
		if(*it == item)
			break;

	return *it;
}
```

Exemplary: In the worst case, the target `item` would not be contained in the `vector`. The algorithm has to check every `item` in the `vector`. Each check takes a constant number of instructions. Thus, the algorithm is O(n) where n is the length of the `vector`.

Insufficient: The algorithm is O(n) because there is one loop.

**Question 2:** What are pointers? Why are pointers used?

Exemplary: Pointers are variables which store memory addresses. Pointers allow the programmer to reference memory without having to maintain a copy.

Insufficient: Pointers are created with the new operator and are special objects.

**Question 3:** Consider the following code:

```C++
int main() {
	int * pa = nullptr; //invalid bc a goes out of scope
	int ** pb = &pa; //valid

	{
		int a = 4; //a becomes out of scope
		pa = &a;
	}

	do_something_with(pa, pb);
}
```

Explain the issue with the code. Which pointers reference valid memory - `pa`, `pb`, neither, or both?

Exemplary: The pointer `pa` stores the memory address of `a` but it outlasts `a`s lifetime and is reused. This references arbitrary stack memory which could have implications for the program. `pb` remains valid since it points to `pa` during `pa`'s lifetime.

Insufficient: `pa` is not valid because it points to `4` and `pb` is valid because it is not modified.

### Here is the list of conceptual questions we may ask:

1. You were required use `std::move` when copying elements from the previous array into the reallocated array. What is the purpose of `std::move`? Explain the effect on a reallocation with `Vector<double>` and `Vector<std::string>`.
//move changes ownership of object. efficient because it doesn't create a new copy

2. What is wrong with the following code? Explain what happens to the memory and pointers at points (1), (2), and (3).

```C++
Vector<int> vec(4);

using iter = Vector<int>::iterator;
iter begin = vec.begin();       // 1 stores the address of first element of vec into begin

for(iter it = begin; it != vec.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;

for(int i = 0; i < 3; i++)
	vec.push_back(4);        // 2 appends 4 onto the vector

for(iter it = begin; it != vec.end(); it++)
	std::cout << *it << " "; // 3 prints each element of vector onto console
std::cout << std::endl;
```

3. The following is a potential solution for `erase_multiple`. Explain why this solution is suboptimal in terms of asymptotic complexity:

```C++
iterator erase(iterator first, iterator last) { //recursion is suboptimal compared to a for loop
	difference_type diff = last - first;
	if (diff <= 0)
		return last;
	iterator cur = first;
	while(diff--)
		cur = erase(cur);
	return cur;
}
```

4. Steven's copy assignment operator makes a shallow copy of the array. Explain why this is problematic. Provide a scenario which could lead the program to fault.
//copy assignment operator should create a deep copy. If shallow copy, lhs & rhs will point to same object. change one, change other. 

5. What is the difference between the move and copy operator? Why would you use one or the other? What is the asymptotic complexity of each?
//move changes ownership of object, copy operator creates new copy. 

6. You've allocated a `Vector<int>` on the stack. Twenty integers are addded to a vector. In which regions of memory are `_capacity`, `_size`, and `array` stored (stack, heap, bss, text)? Where are the integers themselves stored? Why?
//cap, size, array on stack. array points to array of ints on heap. 

7. What is `difference_type`? Explain the purpose of the type it is aliased to and why the alias is needed in the vector iterator.
//distance between two iterators of the same array. used to find index of pos in insert function. 

8. Assume we have a `Vector<std::string>` with `_size = 9` and `_capacity = 16`. Explain how many copies are made when a `push_back` function is called with the following signatures. Why is each copy made? Assume move semantics are used optimally.

```C++
void push_back(T value); //new copy 1-3
void push_back(const T& value); 
void push_back(const T value); 
void push_back(T&& value); //moves value onto the vector. no new copy
```

9. What is the runtime of the `erase(iterator pos)` function? Please explain your reasoning. //O(end() - pos)

10. Explain the concept of templating. Why are template definitions required to be placed in a `.h` file instead of a `.cpp` file?
//allows for any data type to be used. compiler needs to know how to make classes