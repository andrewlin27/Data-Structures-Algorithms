List Oral Report
================

For the list report, you will be asked three questions to test your conceptual understanding of the assignment. Some questions will expand on the concepts you learned. You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each are sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient," "incomplete," or "insufficient" (0 points). The point value for "mostly sufficient" and "incomplete" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

Questions seven and five require you to present your code.

Question 1
----------

Consider the following code snippet:

```c++
void f1() {
    List<int> ll;
    ll.push_front(20);
    ll.push_back(30);
}
```

Four nodes are created by the `List` class. (1) Briefly describe the purpose of each node and (2) identify what region of memory where it is stored (stack, heap, text, uninitialized data, or initialized data).

The head and tail nodes are sentinel nodes (dummy nodes) and are stored as a Node reference in the List class. The 20 and 30 nodes are the actual nodes of the list that contribute to the _size and are stored as Node pointers in the List class. head and tail in stack, 20 and 30 in heap.

Question 2
----------

Consider the following code snippet, which implements the `List` destructor:

```c++
template <class T>
List<T>::~List() { 
    Node * cursor = head.next;
    while(cursor != &tail) {
        // Node* temp = cursor;
        delete cursor;
        cursor = cursor->next; //temp->next
    }
}
```

This code contains an error. What is the error? How would you fix it?

You cannot update the cursor variable after deleting it because you no longer have access to cursor->next. To fix this, create a temporary variable that temporarily stores cursor. Then use temp->next instead of cursor->next when updating cursor. 

Question 3
----------

A student is attempting to delete a node from the doubly linked list and writes the following code:

```c++
node->next->prev = node->next;
node->prev->next = node->prev;
delete node;
```
Is this scheme correct? If so, justify why it works. If not, explain the issue with their methodology.

This is not correct because node->next->prev shouldn't point to node->next itself. Rather, it sould point to node->prev. Same concept with the line below it too. 

Question 4
----------

A student implements the following move constructor:

```c++
template <class T>
List<T>::List(List && ll) : head{}, tail{}, _size{0} {
    _size = ll._size;
    if(!ll.empty()) {
        head.next = ll.head.next;
        tail.prev = ll.tail.prev;

        ll.head.next = &ll.tail;
        ll.tail.prev = &ll.head;
    } else {
        head.next = &tail;
        tail.prev = &head;
    }
    ll._size = 0;
}
```

The code contains an error. What is the source of this error? Provide a sequence of iterator operations which demonstrate the incorrect behavior.

The code needs to set ll.head.next->prev = &head and ll.tail.prev->next = &tail. 
Node* it = &head
it++; //goes to correct next.
it--; //incorrectly goes back to ll.head instead of head. 

Question 5
----------

The `List` was implemented with head and tail sentinel nodes that bookend the list. We could have implemented it in a similar (and possibly simpler) fashion using `head` and `tail` pointers as follows:

```c++
template <class T>
class List {
    // Imagine that Node class is defined here
    Node *head, *tail;
    // ...
};
```

What benefit do the `head` and `tail` nodes provide over the above implementation?

reduces risk of segmentation faults for edge cases like inserting/erasing at beginning/end of linked list. 

Question 6
----------

When dealing with the `Card`s, you shuffled the `deck` using the `shuffle` function. What is the asymptotic running time of the `shuffle` function? You may assume that `rand221` runs in constant time. Justify the running time you suggest. After the deck is shuffled, assuming that it contains *n* cards, what is the time complexity to find the card that was at the **front** of the deck before it was shuffled? What is the time complexity to find the card that was at the **back** of the deck before it was shuffled? Justify these time complexities.

-The asymptotic running time of shuffle is f(n) = 1 + 3n where n is the size of deck. Initialize deck (1), call random, compare to zero, push_back/front (3n). 
-The best case to find front in a shuffled deck is O(1) if every call to rand221 returns an odd number, pushing every card to the back. The front card would be the same in the new deck. The worst case is O(n) if the front card is directly in the middle of the new deck. Average case O(n). 
-The time complexity for finding back in a shuffle deck is O(1) because it is always in either the front or back of the new deck. 

Question 7
----------

What is the runtime of the `pop_back` and `pop_front` functions? If we implemented a singly linked list with a single head pointer, would either of these runtimes change? If not, describe why. If so, describe which runtimes will change and what the new runtime would be.

O(1) for both pop_back and pop_front. If using a singly linked list with a single head pointer, pop_back would take O(n) because you would have to traverse through the entire list to get to the last element. pop_front would still be O(1) because you could just insert after the head pointer. 

Question 8
----------

Name at least three functions (or constructors) that call (directly or indirectly) the `insert` function variants. If you do not have three such functions in your code, name three functions that you *could* have implemented in such a manner. Describe an alternate implementation where if you used `insert` (or a derivative of `insert`, e.g. `push_back`), you do not use it and vice-versa.

Name at least two functions that call (directly or indirectly) the `erase` function (or its derivatives, i.e. `pop_back`). If you do not have two such functions in your code, name two functions that you could have implemented in such a manner. Describe an alternate implementation where if you used `erase` (or a derivative of `erase`, e.g. `pop_back`), you do not use it and vice-versa.

The goal of this question is to get you thinking about alternate implementations for the functions in your program.

-list constructor, push_front, push_back all directly call the insert function. An alternate implementation to push_front without using insert would be to create a new node and manually change the head.next pointer and the head.next->prev pointer to insert a node at the front. Then change the new node's prev and next to point to the correct nodes. 
-pop_front and pop_back directly call the erase function. An alternate implementation to pop_front without using erase would be to manually change the nodes before and after the erase node to point at each other. 

Question 9
----------

During the report for `assignment-vector` you were provided an example of iterator invalidation. That is when using `Vector`, an `Vector` iterator would point to invalid memory if an operation was performed to reallocate the underlying array. Now consider your implementation of `List`. Which of the following `List` methods *can* result in iterator invalidation? For each method that can result in iterator invalidation, describe the *conditions under which this occurs*.

- `push_back`
- `erase` 1
- `insert`
- `clear` 1
- `List& operator=( const List& other );` 1
- `List& operator=( List&& other ) noexcept;`

If you have an iterating pointing to a node, after calling erase to that node, that iterator is invalidated because you will not be able to access it anymore. This is the case for other functions that call erase. Specifically, clear, copy assignment operator. 