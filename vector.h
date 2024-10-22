/*
 * Author: andreyxaxa
 * Date: 2024-10-19
 */

#pragma once

#include <memory>
#include <stdexcept>

template <typename T, typename Alloc = std::allocator<T>>
class vector {

    // CLASS base_iterator

    template <bool IsConst> 
    class base_iterator {
    public:
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;

    private:
        pointer ptr;
        friend class vector<T>;

    public:
        base_iterator(T* ptr) : ptr(ptr) {}
        base_iterator(const base_iterator&) = default;
        base_iterator& operator=(const base_iterator&) = default;

        operator base_iterator<true>() const { return ptr; }
        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }

        base_iterator& operator++() {
            ++ptr;
            return *this;
        }

        base_iterator operator++(int) {
            base_iterator copy = *this;
            ++ptr;
            return copy;
        }

        base_iterator& operator+=(difference_type n) {
            ptr = ptr + n;
            return *this;
        }

        base_iterator operator+(difference_type n) {
            base_iterator temp = *this;
            temp += n;
            return temp;
        }

        base_iterator& operator--() {
            --ptr;
            return *this;
        }

        base_iterator operator--(int) {
            base_iterator copy = *this;
            --ptr;
            return copy;
        }

        base_iterator& operator-=(difference_type n) {
            ptr = ptr - n;
            return *this;
        }

        base_iterator operator-(difference_type n) {
            base_iterator temp = *this;
            temp -= n;
            return temp;
        }

        difference_type operator-(const base_iterator& other) const { return ptr - other.ptr; }

        reference operator[](difference_type n) const { return *(ptr + n); }


        bool operator==(const base_iterator& other) const { return ptr == other.ptr; }

        bool operator!=(const base_iterator& other) const { return !(ptr == other.ptr); }

        bool operator<(const base_iterator& other)  const { return ptr < other.ptr; }

        bool operator>(const base_iterator& other)  const { return ptr > other.ptr; }

        bool operator<=(const base_iterator& other) const { return ptr <= other.ptr; }

        bool operator>=(const base_iterator& other) const { return ptr >= other.ptr; }

    }; // END OF base_iterator


public:

    // +++++++++++++++++++ MEMBER TYPES +++++++++++++++++++

    using value_type = T;

    using allocator_type = Alloc;

    using size_type = std::size_t;

    using difference_type = std::ptrdiff_t;

    using reference = value_type&;

    using const_reference = const value_type&;

    using pointer = value_type*;

    using const_pointer = const value_type*;

    using iterator = base_iterator<false>;

    using const_iterator = base_iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //  ITERATORS

    // returns a read / write iterator that points to the first element in the vector
    [[nodiscard]] iterator begin() { return arr_; }

    // returns a read / write iterator that points one past the last element in the vector
    [[nodiscard]] iterator end() { return arr_ + sz_; }

    // returns a read - only (constant) iterator that points to the first element in the vector
    [[nodiscard]] const_iterator begin()   const { return arr_; }

    // returns a read - only (constant) iterator that points one past the last element in the vector
    [[nodiscard]] const_iterator end()     const { return arr_ + sz_; }

    // returns a read - only (constant) iterator that points to the first element in the vector
    [[nodiscard]] const_iterator cbegin()  const { return arr_; }

    // returns a read - only (constant) iterator that points one past the last element in the vector
    [[nodiscard]] const_iterator cend()    const { return arr_ + sz_; }

    // returns a read / write reverse iterator that points to the last element in the vector
    [[nodiscard]] reverse_iterator rbegin() { return reverse_iterator(end()); }

    // returns a read / write reverse iterator that points to one before the first element in the vector
    [[nodiscard]] reverse_iterator rend() { return reverse_iterator(begin()); }

    // returns a read - only (constant) reverse iterator that points to the last element in the vector.
    [[nodiscard]] const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

    // returns a read - only (constant) reverse iterator that points to one before the first element in the vector.
    [[nodiscard]] const_reverse_iterator rend() const { return reverse_iterator(begin()); }

    // returns a read - only (constant) reverse iterator that points to the last element in the vector
    [[nodiscard]] const_reverse_iterator crbegin() const { return reverse_iterator(end()); }

    // returns a read - only (constant) reverse iterator that points to one before the first element in the vector
    [[nodiscard]] const_reverse_iterator crend() const { return reverse_iterator(begin()); }
        
    // +++++++++++++++++++ CONSTRUCTORS, DTOR +++++++++++++++++++
    // strong exception guarantee

    // Default constructor. Constructs an empty container
    vector();

    //  Constructs the container with 'sz' default-inserted instances of T
    explicit vector(size_type sz);

    // Constructs the container with the contents of the initializer list
    vector(std::initializer_list<T>);

    // Constructs the container with 'sz' copies of elements with value 'value'
    explicit vector(size_type sz, const_reference value);

    // Constructs the container with the contents of the range [first, last]
    template <typename InputIt>
    vector(InputIt first, InputIt last);

    // Copy constructor. Constructs the container with the copy of the contents of 'other'
    vector(const vector&);

    // Move constructor. Constructs the container with the contents of 'other' using move semantics.
    vector(vector&&) noexcept;

    // A Destructor. Destructs the vector
    ~vector() noexcept;

    // +++++++++++++++++++ ELEMENT ACCESS +++++++++++++++++++

    // Returns a read - write reference to the element at specified location 'index'. No bounds checking is performed.
    reference operator[](size_type index) noexcept;

    // Returns a read - only reference to the element at specified location 'index'. No bounds checking is performed.
    const_reference operator[](size_type index) const noexcept;

    // Returns a read - write reference to the element at specified location 'index', with bounds checking.
    reference at(size_type index);

    // Returns a read - only reference to the element at specified location 'index', with bounds checking.
    const_reference at(size_type index) const;

    // Returns a read - write reference to the first element in the container.
    reference front();

    // Returns a read - only reference to the first element in the container.
    const_reference front() const;

    // Returns a read - write reference to the last element in the container.
    reference back();

    // Returns a read - only reference to the last element in the container.
    const_reference back() const;

    // +++++++++++++++++++ CAPACITY +++++++++++++++++++

    // Returns the number of elements in the container
    const size_type size() const noexcept;

    // Returns the number of elements that the container has currently allocated space for
    const size_type capacity() const noexcept;

    /* Increase the capacity of the vector to a 'newcap' 
    * If 'newcap' is greater than capacity(), all iterators and all references to the elements are invalidated */
    void reserve(size_type newcap);

    // Checks if the container has no elements
    bool empty() const;

    // Reduces memory usage by freeing unused memory
    void shrink_to_fit();

    // Returns the maximum possible number of elements
    size_type max_size() const noexcept;

    // +++++++++++++++++++ MODIFIERS +++++++++++++++++++

    // Appends a new element to the end of the container
    template <typename... Args>
    void emplace_back(Args&&... args);

    // Appends the given element 'value' to the end of the container. Copy
    void push_back(const value_type& value);

    // Appends the given element 'value' to the end of the container. Move
    void push_back(value_type&& value);

    // Inserts a copy of 'value' before 'pos'
    iterator insert(const_iterator pos, const T& value);

    // Inserts 'value' before 'pos', possibly using move-semantics
    iterator insert(const_iterator pos, T&& value);

    // Inserts 'count' copies of the 'value' before 'pos'
    iterator insert(const_iterator pos, size_type count, const T& value);

    // Inserts elements from range [first, last] before 'pos'
    template< class InputIt >
    iterator insert(const_iterator pos, InputIt first, InputIt last);

    // Inserts elements from initializer list 'ilist' before 'pos'
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);

    // Removes the last element
    void pop_back() noexcept;
    
    // Clears the contents
    void clear();

    // Swaps the contents
    void swap(vector&) noexcept;

    // Changes the number of elements stored
    void resize(size_type);

    // Changes the number of elements stored. Additional copies of 'value' are appended
    void resize(size_type, const value_type& value);

    // Removes the element at 'pos'
    iterator erase(iterator pos);

    // Removes the element at 'pos'
    const_iterator erase(const_iterator pos);

    // Removes the elements in the range [first, last]
    iterator erase(iterator first, iterator last);

    // Removes the elements in the range [first, last]
    const_iterator erase(const_iterator first, const_iterator last);

    // MEMBER FUNCTIONS

    // Copy assignment operator
    vector& operator=(const vector&);

    // Move assignment operator
    vector& operator=(vector&&) noexcept;

    // Returns the allocator associated with the container
    allocator_type get_allocator() const noexcept;

    // Replaces the contents of the container
    void assign(size_type count, const T& value);

    // OTHER

private:
    // helper insert method
    iterator insert_impl(const_iterator, T&&);

    // different iterator categories version
    template <typename InputIt>
    iterator insert_dispatch(const_iterator, InputIt, InputIt, float); 

    // same iterator categories version
    template <typename InputIt>
    iterator insert_dispatch(const_iterator, InputIt, InputIt, int);

private:
    T* arr_;
    size_t sz_;
    size_t cap_;
    [[no_unique_address]] Alloc alloc_;
    using alloc_traits = std::allocator_traits<Alloc>;
};

// +++++++++++++++++++ CLASS vector IMPLEMENTATION +++++++++++++++++++

    // +++++++++++++++++++ CONSTRUCTORS +++++++++++++++++++

    // default ctor
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector() : arr_(nullptr), sz_(0), cap_(0) {}

    // ctor from size
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector(size_type sz) : sz_(sz), cap_(sz) {
    arr_ = alloc_traits::allocate(alloc_, cap_);
    size_type index = 0;
    try {
        for (; index < sz_; ++index) {
            alloc_traits::construct(alloc_, arr_ + index);
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, arr_ + new_index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        throw;
    }
}

    // ctor from std::initializer_list
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector(std::initializer_list<T> init_list) : arr_(nullptr), sz_(init_list.size()), cap_(init_list.size()) {
    arr_ = alloc_traits::allocate(alloc_, cap_);
    size_type index = 0;
    try {
        for (const_reference value : init_list) {
            alloc_traits::construct(alloc_, arr_ + index, value);
            ++index;
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, arr_ + new_index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        throw;
    }
}

    // ctor from size and value
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector(size_type sz, const_reference value) : arr_(nullptr), sz_(sz), cap_(sz) {
    arr_ = alloc_traits::allocate(alloc_, cap_);
    size_type index = 0;
    try {
        for (; index < sz_; ++index) {
            alloc_traits::construct(alloc_, arr_ + index, value);
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, arr_ + new_index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        throw;
    }
}

    // ctor from iterators. !!! remember - iterators must be from the same container.
template<typename T, typename Alloc> 
template<typename InputIt>
inline vector<T, Alloc>::vector(InputIt first, InputIt last) : arr_(nullptr), sz_(0), cap_(0) {
    size_type count = std::distance(first, last);
    cap_ = count;
    arr_ = alloc_traits::allocate(alloc_, cap_);
    size_type index = 0;

    try {
        for (; first != last; ++first, ++index) {
            alloc_traits::construct(alloc_, arr_ + index, *first);
        }
        sz_ = index;
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, arr_ + new_index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        throw;
    }
};

    // copy ctor;
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector(const vector& other)
    : sz_(other.sz_), cap_(other.cap_), alloc_(alloc_traits::select_on_container_copy_construction(other.alloc_)) {
    arr_ = alloc_traits::allocate(alloc_, cap_);
    size_type index = 0;
    try {
        for (; index < sz_; ++index) {
            alloc_traits::construct(alloc_, arr_ + index, other.arr_[index]);
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, arr_ + new_index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        throw;
    }
}

    // move ctor
template<typename T, typename Alloc> 
inline vector<T, Alloc>::vector(vector&& other) noexcept {
    if (arr_ != nullptr) alloc_traits::deallocate(alloc_, arr_, cap_);
    arr_ = other.arr_; other.arr_ = nullptr;
    sz_ = other.sz_;   other.sz_ = 0;
    cap_ = other.cap_; other.cap_ = 0;
}

    // +++++++++++++++++++ ELEMENT ACCESS +++++++++++++++++++

template<typename T, typename Alloc> 
inline T& vector<T, Alloc>::operator[](size_type index) noexcept {
    return arr_[index];
}

template<typename T, typename Alloc>
inline const T& vector<T, Alloc>::operator[](size_type index) const noexcept {
    return arr_[index];
}

template<typename T, typename Alloc>
inline T& vector<T, Alloc>::at(size_type index) {
    if (index >= sz_) {
        throw std::out_of_range("index out of range!");
    }
    return arr_[index];
}

template<typename T, typename Alloc>
inline const T& vector<T, Alloc>::at(size_type index) const {
    if (index >= sz_) {
        throw std::out_of_range("index out of range!");
    }
    return arr_[index];
}

template<typename T, typename Alloc>
inline T& vector<T, Alloc>::front() {
    if (arr_ != nullptr) {
        return *arr_;
    }
}

template<typename T, typename Alloc>
inline const T& vector<T, Alloc>::front() const {
    if (arr_ != nullptr) {
        return *arr_;
    }
}

template<typename T, typename Alloc>
inline T& vector<T, Alloc>::back() {
    if (arr_ != nullptr) {
        return *(arr_ + sz_ - 1);
    }
}

template<typename T, typename Alloc>
inline const T& vector<T, Alloc>::back() const {
    if (arr_ != nullptr) {
        return *(arr_ + sz_ - 1);
    }
}

    // +++++++++++++++++++ CAPACITY +++++++++++++++++++

template<typename T, typename Alloc>
inline const std::size_t vector<T, Alloc>::size() const noexcept {
    return sz_;
}

template<typename T, typename Alloc>
inline const std::size_t vector<T, Alloc>::capacity() const noexcept {
    return cap_;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::clear() {
    for (size_type i = 0; i < sz_; ++i) {
        alloc_traits::destroy(alloc_, arr_ + i);
    }
    sz_ = 0;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::reserve(size_type newcap) {
    size_type index = 0;
    pointer newarr = alloc_traits::allocate(alloc_, newcap);
    try {
        for (; index < sz_; ++index) {
            alloc_traits::construct(alloc_, newarr + index, 
                std::move_if_noexcept(arr_[index]));
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(alloc_, newarr + new_index);
        }
        alloc_traits::deallocate(alloc_, newarr, newcap);
        throw;
    }

    for (size_type index = 0; index < sz_; ++index) {
        alloc_traits::destroy(alloc_, arr_ + index);
    }
    alloc_traits::deallocate(alloc_, arr_, cap_);

    arr_ = newarr;
    cap_ = newcap;
}

template<typename T, typename Alloc>
inline bool vector<T, Alloc>::empty() const {
    if (arr_ == nullptr) return true;
    return false;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::shrink_to_fit() {
    if (sz_ < cap_) {
        pointer newarr = alloc_traits::allocate(alloc_, sz_);
        size_type index = 0;
        try {
            for (; index < sz_; ++index) {
                alloc_traits::construct(alloc_, newarr + index, 
                    std::move_if_noexcept(arr_[index]));
            }
        }
        catch (...) {
            for (size_type newindex = 0; newindex < index; ++newindex) {
                alloc_traits::destroy(alloc_, newarr + newindex);
            }
            alloc_traits::deallocate(alloc_, newarr, sz_);
            throw;
        }
        for (size_type index = 0; index < sz_; ++index) {
            alloc_traits::destroy(alloc_, arr_ + index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);
        arr_ = newarr;
        cap_ = sz_;
    }
}

template<typename T, typename Alloc>
inline std::size_t vector<T, Alloc>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(T);
}

    // OTHER (private methods - helpers)

template<typename T, typename Alloc>
template<typename InputIt>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert_dispatch(const_iterator pos, InputIt first, InputIt last, float) {

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type count = std::distance(first, last);
    size_type index = pos - begin();

    if (count == 0) {
        return begin() + index;
    }

    if (sz_ + count > cap_) {
        reserve(std::max(cap_ * 2, sz_ + count));
    }

    try {
        for (size_type i = sz_; i > index; --i) {
            alloc_traits::construct(alloc_, arr_ + i + count - 1,
                std::move_if_noexcept(arr_[i - 1]));
            alloc_traits::destroy(alloc_, arr_ + i - 1);
        }
        for (size_type i = 0; i < count; ++i) {
            alloc_traits::construct(alloc_, arr_ + index + i, *first++);
        }
        sz_ += count;
    }
    catch (...) {
        for (size_type i = index + count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
        throw;
    }

    return begin() + index;

}

template<typename T, typename Alloc>
template<typename InputIt>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert_dispatch(const_iterator pos, InputIt first, InputIt last, int) {

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type count = std::distance(first, last);
    size_type index = pos - begin();

    if (count == 0) {
        return begin() + index;
    }

    if (first >= begin() && first < end() && last > begin() && last <= end()) {
        vector<T> temp(first, last);
        first = temp.begin();
        last = temp.end();

        if (sz_ + count > cap_) {
            reserve(std::max(cap_ * 2, sz_ + count));
        }

        try {
            for (size_type i = sz_; i > index; --i) {
                alloc_traits::construct(alloc_, arr_ + i + count - 1,
                    std::move_if_noexcept(arr_[i - 1]));
                alloc_traits::destroy(alloc_, arr_ + i - 1);
            }
            for (size_type i = 0; i < count; ++i) {
                alloc_traits::construct(alloc_, arr_ + index + i, *first++);
            }
            sz_ += count;
        }
        catch (...) {
            for (size_type i = index + count; i < sz_; ++i) {
                alloc_traits::destroy(alloc_, arr_ + i);
            }
            throw;
        }

        return begin() + index;
    }

    if (sz_ + count > cap_) {
        reserve(std::max(cap_ * 2, sz_ + count));
    }

    try {
        for (size_type i = sz_; i > index; --i) {
            alloc_traits::construct(alloc_, arr_ + i + count - 1,
                std::move_if_noexcept(arr_[i - 1]));
            alloc_traits::destroy(alloc_, arr_ + i - 1);
        }
        for (size_type i = 0; i < count; ++i) {
            alloc_traits::construct(alloc_, arr_ + index + i, *first++);
        }
        sz_ += count;
    }
    catch (...) {
        for (size_type i = index + count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
        throw;
    }

    return begin() + index;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert_impl(const_iterator pos, T&& value) {

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }
    if (pos == end()) {
        push_back(value);
        return --end();
    }

    size_type index = pos - begin();

    if (sz_ == cap_) {
        reserve(cap_ > 0 ? cap_ * 2 : 1);
    }

    try {
        for (size_type i = sz_; i > index; --i) {
            alloc_traits::construct(alloc_, arr_ + i,
                std::move_if_noexcept(arr_[i - 1]));
            alloc_traits::destroy(alloc_, arr_ + i - 1);
        }
        alloc_traits::construct(alloc_, arr_ + index, std::forward<T>(value));
        ++sz_;
    }
    catch (...) {
        for (size_type i = index + 1; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
        throw;
    }
    return begin() + index;
}

    // +++++++++++++++++++ MODIFIERS +++++++++++++++++++

template<typename T, typename Alloc>
template<typename ...Args>
inline void vector<T, Alloc>::emplace_back(Args && ...args) {
    if (sz_ == cap_) {
        size_type newcap = cap_ > 0 ? cap_ * 2 : 1;
        size_type index = 0;
        pointer newarr = alloc_traits::allocate(alloc_, newcap);
        try {
            alloc_traits::construct(alloc_, newarr + sz_, std::forward<Args>(args)...);
            for (; index < sz_; ++index) {
                alloc_traits::construct(alloc_, newarr + index,
                    std::move_if_noexcept(arr_[index]));
            }
        }
        catch (...) {
            for (size_type new_index = 0; new_index < index; ++new_index) {
                alloc_traits::destroy(alloc_, newarr + new_index);
            }
            alloc_traits::deallocate(alloc_, newarr, newcap);
            throw;
        }

        for (size_type index = 0; index < sz_; ++index) {
            alloc_traits::destroy(alloc_, arr_ + index);
        }
        alloc_traits::deallocate(alloc_, arr_, cap_);

        arr_ = newarr;
        cap_ = newcap;
        ++sz_;
    }

    else {
        try {
            alloc_traits::construct(alloc_, arr_ + sz_,
                std::forward<Args>(args)...);
        }
        catch (...) { throw; }
        ++sz_;
    }
};

template<typename T, typename Alloc> // push_back copying
inline void vector<T, Alloc>::push_back(const value_type& value) {
    emplace_back(value);
}

template<typename T, typename Alloc> // push_back from moving
inline void vector<T, Alloc>::push_back(value_type&& value) {
    emplace_back(std::move(value));
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, const T& value) {

    return insert_impl(pos, value);
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, T&& value) {

    return insert_impl(pos, std::move(value));
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, size_type count, const T& value) {

    size_type index = pos - begin();

    if (count == 0) {
        return begin() + index;
    }

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    if (sz_ + count > cap_) {
        reserve(std::max(cap_ * 2, sz_ + count));
    }

    try {
        for (size_type i = sz_; i > index; --i) {
            alloc_traits::construct(alloc_, arr_ + i + count - 1,
                std::move_if_noexcept(arr_[i - 1]));
            alloc_traits::destroy(alloc_, arr_ + i - 1);
        }
        for (size_type i = 0; i < count; ++i) {
            alloc_traits::construct(alloc_, arr_ + index + i, value);
        }
        sz_ += count;
    }
    catch (...) {
        for (size_type i = index + count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
        throw;
    }

    return begin() + index;
}

template<typename T, typename Alloc>
template<class InputIt>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, InputIt first, InputIt last) {

    using category1 = typename std::iterator_traits<InputIt>::iterator_category;
    using category2 = typename std::iterator_traits<const_iterator>::iterator_category;
    if constexpr (std::is_same_v<category1, std::random_access_iterator_tag>) {
        return insert_dispatch(pos, first, last, 1);
    }
    else {
        return insert_dispatch(pos, first, last, 1.0f);
    }
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos, std::initializer_list<T> ilist) {

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    auto first = ilist.begin();
    auto last = ilist.end();
    size_type count = std::distance(first, last);
    size_type index = pos - begin();

    if (count == 0) {
        return begin() + index;
    }

    if (sz_ + count > cap_) {
        reserve(std::max(cap_ * 2, sz_ + count));
    }

    try {
        for (size_type i = sz_; i > index; --i) {
            alloc_traits::construct(alloc_, arr_ + i + count - 1,
                std::move_if_noexcept(arr_[i - 1]));
            alloc_traits::destroy(alloc_, arr_ + i - 1);
        }
        for (size_type i = 0; i < count; ++i) {
            alloc_traits::construct(alloc_, arr_ + index + i, *first++);
        }
        sz_ += count;
    }
    catch (...) {
        for (size_type i = index + count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
        throw;
    }

    return begin() + index;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::pop_back() noexcept {
    if (sz_ > 0) {
        --sz_;
        alloc_traits::destroy(alloc_, arr_ + sz_);
    }
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::swap(vector& other) noexcept {
    std::swap(sz_, other.sz_);
    std::swap(cap_, other.cap_);
    std::swap(arr_, other.arr_);
    std::swap(alloc_, other.alloc_);
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::resize(size_type count) {
    if (sz_ > count) {
        for (size_type i = count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
    }
    else if (sz_ < count) {
        if (count > cap_) {
            reserve(count);
        }
        size_type i = sz_;
        try {
            for (; i < count; ++i) {
                alloc_traits::construct(alloc_, arr_ + i, T());
            }
        }
        catch (...) {
            for (size_type new_i = sz_; new_i < i; ++new_i) {
                alloc_traits::destroy(alloc_, arr_ + new_i);
            }
            throw;
        }
    }

    sz_ = count;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::resize(size_type count, const value_type& value) {
    if (sz_ > count) {
        for (size_type i = count; i < sz_; ++i) {
            alloc_traits::destroy(alloc_, arr_ + i);
        }
    }
    else if (sz_ < count) {
        if (count > cap_) {
            reserve(count);
        }
        size_type i = sz_;
        try {
            for (; i < count; ++i) {
                alloc_traits::construct(alloc_, arr_ + i, value);
            }
        }
        catch (...) {
            for (size_type new_i = sz_; new_i < i; ++new_i) {
                alloc_traits::destroy(alloc_, arr_ + new_i);
            }
            throw;
        }
    }

    sz_ = count;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos) {

    if (pos < begin() || pos > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type index = pos - begin();
    alloc_traits::destroy(alloc_, arr_ + index);

    for (size_type i = index; i < sz_ - 1; ++i) {
        alloc_traits::construct(alloc_, arr_ + i, std::move_if_noexcept(arr_[i + 1]));
        alloc_traits::destroy(alloc_, arr_ + i + 1);
    }

    --sz_;

    return begin() + index;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::const_iterator vector<T, Alloc>::erase(const_iterator pos) {

    if (pos < cbegin() || pos > cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type index = pos - cbegin();
    alloc_traits::destroy(alloc_, arr_ + index);

    for (size_type i = index; i < sz_ - 1; ++i) {
        alloc_traits::construct(alloc_, arr_ + i, std::move_if_noexcept(arr_[i + 1]));
        alloc_traits::destroy(alloc_, arr_ + i + 1);
    }

    --sz_;

    return cbegin() + index;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
{
    if (first < begin() || last > end() || first > end()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type index_first = first - begin();
    size_type index_last = last - begin();
    size_type count = index_last - index_first;

    for (size_type i = index_first; i < index_last; ++i) {
        alloc_traits::destroy(alloc_, arr_ + i);
    }

    for (size_type i = index_last; i < sz_; ++i, ++index_first) {
        alloc_traits::construct(alloc_, arr_ + index_first, std::move_if_noexcept(arr_[i]));
        alloc_traits::destroy(alloc_, arr_ + i);
    }

    sz_ -= count;

    return begin() + index_first;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::const_iterator vector<T, Alloc>::erase(const_iterator first, const_iterator last)
{
    if (first < cbegin() || last > cend() || first > cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type index_first = first - cbegin();
    size_type index_last = last - cbegin();
    size_type count = index_last - index_first;

    for (size_type i = index_first; i < index_last; ++i) {
        alloc_traits::destroy(alloc_, arr_ + i);
    }

    for (size_type i = index_last; i < sz_; ++i, ++index_first) {
        alloc_traits::construct(alloc_, arr_ + index_first, std::move_if_noexcept(arr_[i]));
        alloc_traits::destroy(alloc_, arr_ + i);
    }

    sz_ -= count;

    return cbegin() + index_first;
}

    // +++++++++++++++++++ MEMBER FUNCTIONS +++++++++++++++++++

// copy assignment
template<typename T, typename Alloc> 
inline vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& other) {
    Alloc newalloc = alloc_traits::propagate_on_container_copy_assignment::value ?
        other.alloc_ : alloc_;

    if (this == &other) return *this;
    size_type index = 0;
    pointer newarr = alloc_traits::allocate(newalloc, other.cap_);
    try {
        for (; index < other.sz_; ++index) {
            alloc_traits::construct(newalloc, newarr + index, other[index]);
        }
    }
    catch (...) {
        for (size_type new_index = 0; new_index < index; ++new_index) {
            alloc_traits::destroy(newalloc, newarr + new_index);
        }
        alloc_traits::deallocate(newalloc, newarr, other.cap_);
        throw;
    }
    for (size_type i = 0; i < sz_; ++i) {
        alloc_traits::destroy(alloc_, arr_ + i);
    }
    alloc_traits::deallocate(alloc_, arr_, cap_);

    alloc_ = newalloc;
    arr_ = newarr;
    sz_ = other.sz_;
    cap_ = other.cap_;

    return *this;
}

// move assignment
template<typename T, typename Alloc> 
inline vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& other) noexcept {
    if (this == &other) return *this;

    if (arr_ != nullptr)alloc_traits::deallocate(alloc_, arr_, cap_);
    Alloc newalloc = alloc_traits::propagate_on_container_move_assignment::value ?
        other.alloc_ : alloc_;
    alloc_ = newalloc;
    arr_ = other.arr_; other.arr_ = nullptr;
    sz_ = other.sz_;   other.sz_ = 0;
    cap_ = other.cap_; 

    return *this;
}

template<typename T, typename Alloc>
inline vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const noexcept {
    return alloc_;
}

template<typename T, typename Alloc>
inline void vector<T, Alloc>::assign(size_type count, const T& value) {

    if (count <= 0) {
        if (arr_ != nullptr) {
            clear();
        }
        return;
    }

    if (count > cap_) {
        pointer newarr = alloc_traits::allocate(alloc_, count);
        try {
            for (size_type i = 0; i < count; ++i) {
                alloc_traits::construct(alloc_, newarr + i, value);
            }
        }
        catch (...) {
            alloc_traits::deallocate(alloc_, newarr, count);
            throw;
        }

        if (arr_ != nullptr) {
            clear();
            alloc_traits::deallocate(alloc_, arr_, cap_);
        }

        arr_ = newarr;
        cap_ = count;
    }

    else {
        clear();
        size_type index = 0;
        try {
            for (; index < count; ++index) {
                alloc_traits::construct(alloc_, arr_ + index, value);
            }
        }
        catch (...) {
            for (size_type new_index = 0; new_index < index; ++new_index) {
                alloc_traits::destroy(alloc_, arr_ + new_index);
            }
            throw;
        }
    }

    sz_ = count;
}

    // +++++++++++++++++++ NON-MEMBER FUNCTIONS +++++++++++++++++++

template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

// based on operator==
template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs == rhs);
}

template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    if (lhs.size() != rhs.size()) {
        return lhs.size() < rhs.size();
    }
    return std::lexicographical_compare(lhs.begin(), lhs.end(),
        rhs.begin(), rhs.end());
}

// based on operator<
template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (rhs < lhs);
}

// based on operator<
template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(rhs < lhs);
}

// based on operator<
template<typename T, typename Alloc>
[[nodiscard]]
inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return !(lhs < rhs);
}

    // DTOR
template<typename T, typename Alloc>
inline vector<T, Alloc>::~vector() noexcept {
    clear();
    if (arr_ != nullptr) alloc_traits::deallocate(alloc_, arr_, cap_);
}
