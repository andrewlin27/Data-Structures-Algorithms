# Vectors
The overall goal of this assignment is to begin programming data structures by implementing your own slimmed-down [`vector`](https://en.cppreference.com/w/cpp/container/vector).
## Getting Started
Download this code by running the following command in the directory of your choice:

`git clone git@github.com:tamu-edu-students/vector.git`

Open the code in your editor of choice. For instance, if you use VS Code:

`code .`

*Note* on On OSX you may need to enable the `code` command in VS Code with `Cmd+Shift+P` and typing "shell command." You can select the option to install the command, and then the above command will work.
## Assignment
### Implement Vector
You are to implement `Vector`. A `Vector` is a dynamic array as it is a continuous structure that dynamically updates its capacity as needed. As a result, most operations take constant time to complete. However, the amount of wasted space is often equivalent to the amount used. Therefore, `Vector` is not a particularly spatially efficient storage structure.

You may have already used `std::vector` in previous assignments, so your `Vector` should behave similarly. The big difference is that `std::vector` decreases its capacity when enough `pop_back` operations occur, whereas your `Vector` does not ever need to reduce its capacity.

**HINT:** Do the following functions first.
- `Vector()`
- `Vector(size_t count)`
- `~Vector()`
- `size_t size() const noexcept`
- `size_t capacity() const noexcept`
- `T& operator[](size_t pos)`
- `const T& operator[](size_t pos)`
- Complete the `iterator` class

More info about the above functions can be seen below. If you complete the above functions, you should be able to complete any other function and it should pass. The above are the only functions which are "depended on." *Please note that there may be minor exceptions to this rule.*

#### You must implement the following functions for `Vector`:
----

`Vector() noexcept` &ndash; Default constructor.

**Description:**  Create an empty vector

**Complexity: O(1)**

**Tests:** *vector_constructor*, *vector_empty*, *vector_pop_back*, *vector_push_back_move*, *vector_push_back*

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

`Vector(size_t count, const T& value)` &ndash; Parameterized Constructor

**Description:** Constructs the container with `count` copies of elements with value `value`.  

**Complexity: O(`count`)**

**Tests:** *vector_erase_multiple*, *vector_initialization_constructor*, *vector_iterator_io*

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

`explicit Vector(size_t count)` &ndash; Parameterized Constructor

**Description:** Constructs the container with count *default-inserted* instances of T. No copies are made.  

**Complexity: O(`count`)**

**Tests:** Frequently tested (*vector_default_inserted* is dedicated one)

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

`Vector(const Vector& other)` &ndash; Copy constructor

**Description:** Constructs the container with the copy of the contents of `other`.

**Complexity: O(`other.size()`)**

**Tests:** *datum_bad_data_entries*, *datum_good*, *datum_read_data*, *vector_copy_constructor*

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

`Vector(Vector&& other) noexcept` &ndash; Move constructor

**Description:** Constructs the container with the contents of `other` using move semantics. After the move, `other` is guaranteed to be `empty()`.  

**Complexity: O(1)**

**Tests:** *vector_move_constructor*

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

`~Vector()` &ndash; Destructor

**Description:** Destructs the vector. The destructors of the elements are called, and the used storage is deallocated. Note that if the elements are pointers, the pointed-to objects are not destroyed. 

**Complexity: O(n)\*** 

**Tests:** Frequently Tested

**Link:** https://en.cppreference.com/w/cpp/container/vector/~vector

**\*** Depends on the element's destructor, we are assuming each element's destructor is O(1)

----

`Vector& operator=(const Vector& other)` &ndash; Copy assignment operator

**Description:** Replaces the contents with a copy of the contents of `other`. 

**Complexity: O(`size() + other.size()`)**

**Tests:** *vector_copy_operator*

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator%3D

----

`Vector& operator=(Vector&& other) noexcept` &ndash; Move assignment operator

**Description:** Replaces the contents with those of `other` using move semantics (i.e. the data in other is moved from other into this container). After the move, `other` is guaranteed to be `empty()`.  

**Complexity: O(`size()`)**

**Tests:** *vector_move_operator*

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator%3D

----

`begin()` 

**Description:** Returns an iterator to the beginning.

**Complexity: O(1)**

**Tests:** *vector_begin*, *vector_erase_multiple*, *vector_erase_multiple*, *vector_erase*, *vector_insert_move*, *vector_insert_multiple*, *vector_insert*, *vector_iterator_arithmetic*, *vector_iterator_comparison*, *vector_iterator_forward*, *vector_iterator_io*

**Link:** https://en.cppreference.com/w/cpp/container/vector/begin

----

`end()`

**Description:** Returns an iterator to the end.

**Complexity: O(1)**

**Tests:** *vector_end*, *vector_iterator_arithmetic*, *vector_iterator_reverse*

**Link:** https://en.cppreference.com/w/cpp/container/vector/end

----

`empty()`

**Description:** Checks whether the container is empty.

**Complexity: O(1)**

**Tests:** *vector_empty*

**Link:** https://en.cppreference.com/w/cpp/container/vector/empty

----

`size()`

**Description:** Returns the number of elements in the vector.

**Complexity: O(1)**

**Tests:** Frequently Tested

**Link:** https://en.cppreference.com/w/cpp/container/vector/size

----

`capacity()`

**Description:** Returns the number of elements that can be held in currently allocated storage

**Complexity: O(1)**

**Tests:** Frequently Tested

**Link:** https://en.cppreference.com/w/cpp/container/vector/capacity

----

`at(size_T pos)`

**Description:** Access element at index `pos` with bounds checking.

**Complexity: O(1)** 

**Tests:** *vector_at*

**Link:** https://en.cppreference.com/w/cpp/container/vector/at

----

`operator[](size_t pos)` 

**Description:** Access element at index `pos` **without** bounds checking.

**Complexity: O(1)**

**Tests:** Frequently Tested (*vector_access_operator* is dedicated one)

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator_at

----

`front()`

**Description:** Access the first element.

**Complexity: O(1)**

**Tests:** *vector_front_back*

**Link:** https://en.cppreference.com/w/cpp/container/vector/front

----

`back()`

**Description:** Access the last element.

**Complexity: O(1)**

**Tests:** *vector_front_back*

**Link:** https://en.cppreference.com/w/cpp/container/vector/back

----

`push_back(const T& value)`

**Description:** Adds `value` to the end.

**Complexity: O(1) amortized**

**Tests:** *vector_move_constructor*, *vector_pop_back*, *vector_push_back*

**Link:** https://en.cppreference.com/w/cpp/container/vector/push_back

----

`push_back(T&& value)`

**Description:** Adds `value` to the end.

**Complexity: O(1) amortized**

**Tests:** *vector_push_back_move*

**Link:** https://en.cppreference.com/w/cpp/container/vector/push_back

----

`pop_back()`

**Description:** Removes the last element.

**Complexity: O(1)**

**Tests:** *vector_pop_back*

**Link:** https://en.cppreference.com/w/cpp/container/vector/pop_back

----

`insert(iterator pos, const T& value)`

**Description:** Inserts `value` at position `pos`.

**Complexity: O(`end() - pos`)**

**Tests:** *vector_insert*

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

`insert(iterator pos, T&& value)`

**Description:** Inserts `value` at position `pos`.

**Complexity: O(`end() - pos`)**

**Tests:** *vector_insert_move*

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

`insert(iterator pos, size_t count, const T& value)`

**Description:** Inserts `count` copies of `value` at position `pos`.

**Complexity: O(`count + end() - pos`)**

**Tests:** *vector_insert_multiple*

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

`erase(iterator pos)`

**Description:** Erases element at position `pos`.

**Complexity: O(`end() - pos`)**

**Tests:** *vector_erase*

**Link:** https://en.cppreference.com/w/cpp/container/vector/erase

----

`erase(iterator first, iterator second)`

**Description:** Erases elements in the range \[`first`, `second`\), including `first` and excluding `second`. 

**Complexity: O(`end() - first`)**

**Tests:** *vector_erase_multiple*

**Link:** https://en.cppreference.com/w/cpp/container/vector/erase

----

`clear()`

**Description:** Clears the contents.

**Complexity: O(n)**

**Tests:** *vector_clear*

**Link:** https://en.cppreference.com/w/cpp/container/vector/clear

----

### Implement the Vector's Iterator

You must also implement an inner class `iterator` in `Vector`, which can iterate through the elements of the vector forwards and backwards. 

#### You must implement the following functions for `iterator`:

----

`operator*()`

**Description:** Access a reference to the data at the location of the current iterator.

**Complexity: O(1)**

**Tests:** *vector_begin*, *vector_end*, *vector_iterator_arithmetic*, *vector_iterator_forward*, *vector_iterator_io*, *vector_iterator_reverse*

----

`operator->()`

**Description:** Access a member or method of the data at the location of the current iterator.

**Complexity: O(1)**

**Tests:** *vector_iterator_io*

----

`operator++()`

**Description:** Increment an iterator. **Prefix** increment.

**Complexity: O(1)**

**Tests:** *vector_iterator_forward*

----

`operator++(int)`

**Description:** Increment an iterator. **Postfix** increment.

**Complexity: O(1)**

**Tests:** *vector_iterator_arithmetic*, *vector_iterator_comparison*, *vector_iterator_forward*

----

`operator--()`

**Description:** Decrement an iterator. **Prefix** decrement.

**Complexity: O(1)** 

**Tests:** *vector_iterator_reverse*

----

`operator--(int)`

**Description:** Decrement an iterator. **Postfix** decrement.

**Complexity: O(1)** 

**Tests:** *vector_iterator_reverse*

----

`operator+=(difference_type offset)`

**Description:** Advances the iterator by `offset` elements.

**Complexity: O(1)**

**Tests:** *vector_iterator_arithmetic*

----

`operator+(difference_type offset)`

**Description:** Returns a copy of the iterator advanced by `offset` elements.

**Complexity: O(1)**

**Tests:** *vector_erase_multiple*, *vector_erase*, *vector_insert_move*, *vector_insert_multiple*, *vector_insert*, *vector_iterator_arithmetic*

----

`operator-=(difference_type offset)`

**Description:** Regresses the iterator by `offset` elements.

**Complexity: O(1)**

**Tests:** *vector_iterator_arithmetic*

----

`operator-(difference_type offset)`

**Description:** Returns a copy of the iterator regressed by `offset` elements.

**Complexity: O(1)**

**Tests:** *vector_end*, *vector_iterator_arithmetic*

----

`operator-(const iterator& rhs)`

**Description:** Computes the distance between two iterators.

**Complexity: O(1)**

**Tests:** *vector_erase_multiple*, *vector_erase*, *vector_insert_move*, *vector_insert_multiple*, *vector_insert*, *vector_iterator_arithmetic*

----

`operator[](difference_type offset)`

**Description:** Accesses the element offset from the iterator by `offset` elements.

**Complexity: O(1)**

**Tests:** *vector_iterator_arithmetic*

----

`operator==(const iterator& rhs)`

**Description:** Returns true if both iterators point to the same memory. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

`operator!=(const iterator& rhs)`

**Description:** Returns true if both iterators **don't** point to the same memory. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

`operator<(const iterator& rhs)`

**Description:** Returns true if the iterator comes **before** `rhs`. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

`operator>(const iterator& rhs)`

**Description:** Returns true if the iterator comes **after** `rhs`. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

`operator<=(const iterator& rhs)`

**Description:** Returns true if the iterator comes **before** `rhs` **or** points to the same memory as `rhs`. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

`operator>=(const iterator& rhs)`

**Description:** Returns true if the iterator comes **after** `rhs` **or** points to the same memory as `rhs`. Compares the underlying pointers of the iterators.

**Complexity: O(1)**

**Tests:** *vector_iterator_comparison*

----

Feel free to read about `const_iterator` and `reverse_iterator` in C++. However, you need only implement `iterator` for this assignment.

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Vector Begin: https://en.cppreference.com/w/cpp/container/vector/begin
- Reference for Vector End: https://en.cppreference.com/w/cpp/container/vector/end
- Reference for List Begin: https://en.cppreference.com/w/cpp/container/list/begin
- Reference for List End: https://en.cppreference.com/w/cpp/container/list/end

----

### Use Vector (`Datum`)
We have provided a few data files in Comma Separated Values (CSV) format. These files contain data representing COVID-19 at Texas A&M University. 

> The COVID data was obtained from [TAMU's historical records](https://covid.tamu.edu/dashboard/historical.html) in mid January 2020. The original data was accurate as asserted by A&M and affiliated testing providers. **We have intentionally added inaccuracies you must identify as part of this programming exercise.** We also generate random data for testing purposes. Please refer to TAMU for accurate data.

There is a struct, `Datum` in [Datum.h](./src/Datum.h) as well as a few simple function declarations. You are to write these functions in [Datum.cpp](./src/Datum.cpp).

#### You must implement the following functions for `Datum`:

----

`unsigned int Datum::compute_total()`

**Description:** Compute the total number of tests given (sum of positive and negative tests).

**Complexity: O(1)**

**Tests:** *datum_total_positivity*

----

`float Datum::compute_positivity()`

**Description:** Compute the positivity rate (positive tests divided by computed total).

**Complexity: O(1)**

**Tests:** *datum_total_postitivity*

----

`std::ostream& operator<<(std::ostream& out, const Datum& datum)`

**Description:** Prints `datum` to `out`. This is only for debugging purposes and we do not test this method.

**Complexity: O(1)**

**Tests:** Not Tested

----

`std::istream& operator>>(std::istream& in, Datum& datum)`

**Description:** Sets the fields of `datum` to represent the values stored in `in`.

**Complexity: O(1)**

**Tests:** *datum_extraction*

----

`Vector<Datum> readData(std::istream & file)`

**Description:** Assume `file` argument corresponds to a input file which is open as an `ifstream`.  Read the data line-by-line into a `Vector<Datum>` and return the result. Do not read the header. 

**Complexity: O(`size()`)**

**Tests:** *datum_read_data*

----

`Vector<Datum> badDataEntries(const Vector<Datum>& data) noexcept`

**Description:** Return a `Vector` containing only the entries whose `total` does not match the computed total or whose `positivity` does not match the computed `positivity` to within `0.1`. 

**Complexity: O(`size()`)**

**Tests:** *datum_bad_data_entries*

----

`bool goodData(const Vector<Datum>& data) noexcept` 

**Description:** Returns `true` if there is no bad data, i.e. if `badDataEntries(data).empty()` is `true`. Returns `false` otherwise. 

**Complexity: O(`size()`)**

**Tests:** *datum_good*
