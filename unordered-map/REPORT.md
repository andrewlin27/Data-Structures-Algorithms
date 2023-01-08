# Priority Queue and Unordered map Report

Reports for Programming Assignment 5 and 6 (Priority Queue and Unordered Map) have been combined into this one report. There will be one question on Priority Queues and one question on Unordered Maps. 

You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each is sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient" or "insufficient" (0 points). The point value for "mostly sufficient" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

Priority Queue Questions:
=========================

Question 1
----------
Explain the Process of `Upheap` and `Downheap` with respect to the `push()` and `pop()` functions. How do these functions help keep the internal heap perfectly balanced? 

If you have 1000 elements (numbered 0...999) that you want to insert into a heap, what permutation of these elements will insert into the heap in the shortest amount of time? What permutations will insert in the most amount of time? Explain your reasoning. 

upheap swaps an element with its ancestor until it's in a valid location. downheap swaps an element with its greater child(for max heap) until it's in a valid location. They both are used to keep the heap balanced. For a max heap, inserting the elements from greatest to least would be the fastest because upheap/downheap would not have to be called. Inserting the elements from least to greatest would take the most time because upheap would have to be called for every element to reach the top. 

Question 2
----------
In your priority queue implementation, you used a maximum binary heap as your internal data structure. Why is this internal data structure preferable to a sorted linked list (sorted in reverse, with max element at the head)? In your answers, discuss how the time complexities of push(), pop(), and top() would change, if at all. Let the number of elements in the heap be n.

Binary heap is preferred over a sorted linked list becuase the height is log(n) compared to n. top() would stay the same at O(1). push() and pop() would change from O(logn) to O(n) assuming a singly linked list. 

Question 3
----------
Programming assignment 2 was on sorting vectors. How can we sort a vector from lowest to highest using a minimum priority queue? Describe the implementation and the runtime. Let the number of elements in the vector be `n`. Compare its runtime and the number of comparisons to another comparison based algorithm. 

Initialize a min priority queue and then push all 'n' elements O(nlogn). In comparison, bubble sort takes O(n^2) to sort the array on average and n(n-1)/2 number of comparisons. 

Question 4
----------
Discuss the algorithm you used for `push()` and `pop()` operations. Describe an alternate implementation (For example, if you implemented it recursively, explain how you it could be written iteratively. If you did it iterativey, explain how you could have written in recursively). Analyze any differences in the time and space complexity that may exist between the two implementations (iterative and recursive).

push() first used push_back to push the value to the end of vector c. then upheap() was called on that last element. pop() first moved the last element to the top, then pop_back() was called, then downheap() was called on the top element. I implemented upheap iteratively and downheap recursively. Alternatively, I could've implemented upheap recursively by using the while condition as the base case, and i could've implemented downheap iteratively by using the base case as my while condition. Time complexity for both are the same. Space complexity for recursive is greater because you make copy of index every time. 

Unordered Map Questions:
========================

Question 5
----------

You have an Unordered Map with b buckets. Explain your implementation of the find() function and how its runtime changes when the only elements present in your Unordered Map have hash values that are multiples of b/c, where c is some factor of b. Let there be n elements in your Unordered Map.

For example, let's say that our unordered map contains 10 buckets. What will each bucket look like if every element inserted has a hash value that is a multiple of 10? What if each hash value is a multiple of 5? A multiple of 2? Use these examples to formulate a general answer for the runtime of find() in terms of n and c.

How could we change the _hash data member to improve the performance of the find() function given the same elements as input? Alternatively, how could we change _bucket_count to see a similar improvement? Hint: Think about how _bucket() is implemented and how you initialized _bucket_count in your "default" constructor.

In my implementation of find, first find the bucket, then iterate through the list in the bucket until the correct node is found. If all elements have hash values that are multiples of b/c, then runtime would be O(n/c) since all n elements would reside in c buckets. We could change _hash by having more unique hash codes in order to spread out the elements. We could change _bucket_count to be a larger prime number so that the elements are more evenly distributed within the map. 

Question 6
----------

Where are the `_size`, `_buckets[]`, `_head`, and `HashNodes` of our unordered map implementation stored (stack, heap, bss, text)? Explain the Copy and Move Operators and how each of these instance fields are copied/moved in these operators. 

_size, _buckets[], _head are all on stack, but _head points to a HashNode on the heap, and _buckets[] points to an array of HashNode*'s on the heap. 

copy operator: memory was allocated for _buckets[], and the insert function was used in a for loop to copy over _size, _head, and all the HashNodes. 
move operator: _size, _buckets[], and _head are all moved using the equal operator, and all of other's values were set back to default. This means that all the HashNodes are also moved. 

Question 7
----------

In your implementation, your iterator classes had these instance fields:
```C++
class iterator {
    ...
    UnorderedMap* _map;
    HashNode* _node;
    ...
}
class local_iterator {
    ...
    HashNode* _node;
    ...
}
```
Why do these two different iterators require different instance fields? Make sure to discuss the 'operator++' in your answer.

The difference between these two iterators is that the global iterator has _map as an instance field. This is because the local_iterator only iterates through a specific bucket, while the global iterator has the chance of iterating to another bucket. This can happen when calling operator++ on a global iterator who's next node is nullptr. In this case, the global iterator class will use the _map instance field to find the next bucket with a present node. 

Question 8
----------

In our implementation, we stored an individual list in each bucket. But we can utilize other data structures in each bucket. What would be the runtime of the find() function given there is a linked list at every bucket (our implementation)? Let the number of elements in a the unordered map be n and the number buckets be b. Additionally, assume that our hash function evenly distributes the n elements among the b buckets.

What is the runtime of the find() function given there is a binary search tree at every bucket (assuming the binary search tree is balanced)?

What is the runtime of the find() function given there is another unordered map at every bucket of the overall unordered map. Assume that the bucket count of the second unordered map is large enough that every element is in its own bucket. Is this implementation faster than a single, larger unordered map?

find() runtime in our implementation would be O(n/b) since it takes O(1) time to find the bucket, and there are n/b nodes in each bucket.
find() runtime if BST at every bucket would be O(log(n/b)) since it takes O(1) time to find the bucket, and the height of each BST is log(n/b). 
find() funtime if there is another unordered map at every bucket would be O(n/b) since O(1) to find bucket, and at every bucket there is an unordered map of size n/b elements. Iterate bucket to bucket in second map to find node. This would be the same runtime as a single, larger map. 