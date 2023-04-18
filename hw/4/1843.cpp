#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std; // NOLINT

const int MAXN = 3e6 + 5;

struct Edge {
    int v_, next_;
} edge[MAXN];

// NOLINTBEGIN
template <typename T, class Allocator = std::allocator<T>> class vector {
  public:
    /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using reference = value_type &;
    using const_reference = const value_type &;
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator {
        // The following code is written for the C++ type_traits library.
        // Type traits is a C++ feature for describing certain properties of a type.
        // For instance, for an iterator, iterator::value_type is the type that the
        // iterator points to.
        // STL algorithms and containers may use these type_traits (e.g. the following
        // typedef) to work properly. In particular, without the following code,
        // @code{std::sort(iter, iter1);} would not compile.
        // See these websites for more information:
        // https://en.cppreference.com/w/cpp/header/type_traits
        // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
        // About iterator_category: https://en.cppreference.com/w/cpp/iterator
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::output_iterator_tag;

      private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        const vector<T> *iter;
        pointer ptr;

        friend class vector;
        friend class const_iterator;

      public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator() : ptr(nullptr) {}
        iterator(T *_ptr, const vector<T> *_iter) : ptr(_ptr), iter(_iter) {}
        iterator(const iterator &rhs) : ptr(rhs.ptr), iter(rhs.iter) {}

        iterator operator+(const int &n) const { return iterator(ptr + n, iter); }
        iterator operator-(const int &n) const { return iterator(ptr - n, iter); }

        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const {
            return ptr - rhs.ptr;
        }
        iterator &operator+=(const int &n) {
            ptr += n;
            return *this;
        }
        iterator &operator-=(const int &n) {
            ptr -= n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            ptr++;
            return iterator(ptr - 1, iter);
        }
        /**
         * TODO ++iter
         */
        iterator &operator++() {
            ptr++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            ptr--;
            return iterator(ptr + 1, iter);
        }
        /**
         * TODO --iter
         */
        iterator &operator--() {
            ptr--;
            return *this;
        }
        /**
         * TODO *it
         */
        reference operator*() const { return *ptr; }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
        bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
        bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     */
    class const_iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::output_iterator_tag;

      private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        const vector<T> *iter;
        pointer ptr;

        friend class vector;
        friend class iterator;

      public:
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const_iterator(T *_ptr, const vector<T> *_iter) : ptr(_ptr), iter(_iter) {}
        const_iterator(const iterator &rhs) : ptr(rhs.ptr), iter(rhs.iter) {}
        const_iterator(const const_iterator &rhs) : ptr(rhs.ptr), iter(rhs.iter) {}

        const_iterator operator+(const int &n) const { return const_iterator(ptr + n, iter); }
        const_iterator operator-(const int &n) const { return const_iterator(ptr - n, iter); }

        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const {
            return ptr - rhs.ptr;
        }
        const_iterator &operator+=(const int &n) {
            ptr += n;
            return *this;
        }
        const_iterator &operator-=(const int &n) {
            ptr -= n;
            return *this;
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            ptr++;
            return const_iterator(ptr - 1, iter);
        }
        /**
         * TODO ++iter
         */
        const_iterator &operator++() {
            ptr++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            ptr--;
            return const_iterator(ptr + 1, iter);
        }
        /**
         * TODO --iter
         */
        const_iterator &operator--() {
            ptr--;
            return *this;
        }
        /**
         * TODO *it
         */
        const_reference operator*() const { return *ptr; }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }
        bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
        bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
    };
    /**
     * TODO Constructs
     * At least two: default constructor, copy constructor
     */
    vector() noexcept {
        start = iterator(alloc.allocate(1), this);
        finish = start;
        end_of_storage = start + 1;
    }
    vector(const vector &other) noexcept {
        start = iterator(alloc.allocate(other.capacity()), this);
        finish = start + other.size();
        end_of_storage = start + other.capacity();
        for (iterator it1 = start, it2 = other.start; it2 != other.finish; it1++, it2++)
            alloc.construct(it1.ptr, *it2);
    }
    vector(vector &&other) noexcept = default;
    explicit vector(size_type count, const T &value = T()) noexcept {
        int new_size = pow(2, ceil(log2(count)));
        start = iterator(alloc.allocate(new_size), this);
        finish = start + count;
        end_of_storage = start + new_size;
        for (iterator it = start; it != finish; it++)
            alloc.construct(it.ptr, value);
    }
    /**
     * TODO Destructor
     */
    ~vector() {
        clear();
        alloc.deallocate(start.ptr, capacity());
        start = finish = end_of_storage = iterator(nullptr, this);
    }
    /**
     * TODO Assignment operator
     */
    vector &operator=(const vector &other) {
        if (this == &other)
            return *this;
        if (start.ptr != nullptr)
            alloc.deallocate(start.ptr, capacity());
        start.ptr = alloc.allocate(other.capacity());
        finish = start + other.size();
        end_of_storage = start + other.capacity();
        std::copy(other.start, other.finish, start);
        return *this;
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    reference at(const size_type &pos) {
        return *(begin() + pos);
    }
    const_reference at(const size_type &pos) const {
        return *(cbegin() + pos);
    }
    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    reference operator[](const size_type &pos) {
        return *(begin() + pos);
    }
    const_reference operator[](const size_type &pos) const {
        return *(cbegin() + pos);
    }
    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const_reference front() const {
        return *cbegin();
    };
    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const_reference back() const {
        return *std::prev(cend().ptr);
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() noexcept { return start; }
    const_iterator cbegin() const noexcept { return start; }
    /**
     * returns an iterator to the end.
     */
    iterator end() { return finish; }
    const_iterator cend() const noexcept { return finish; }
    /**
     * checks whether the container is empty
     */
    bool empty() const noexcept { return start == finish; }
    /**
     * returns the number of elements
     */
    size_t size() const noexcept { return finish - start; }
    size_t capacity() const noexcept { return end_of_storage - start; }
    /**
     * clears the contents
     */
    void clear() {
        while (--finish != start)
            alloc.destroy(finish.ptr);
        alloc.destroy(start.ptr);
    }
    /**
     * reserve the space
     */
    void reserve(const size_type &new_cap) {
        if (new_cap <= capacity())
            return;
        int new_size = pow(2, ceil(log2(new_cap)));
        iterator new_start = iterator(alloc.allocate(new_size), this);
        iterator new_finish = new_start + size();
        iterator new_end_of_storage = new_start + new_size;
        try {
            for (iterator it1 = new_start, it2 = start; it2 != finish; it1++, it2++)
                alloc.construct(it1.ptr, *it2);
        } catch (...) {
            alloc.deallocate(new_start.ptr, new_size);
            throw;
        }
        clear();
        alloc.deallocate(start.ptr, capacity());
        start = new_start;
        finish = new_finish;
        end_of_storage = new_end_of_storage;
    }
    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const value_type &value) {
        if (pos.ptr < start.ptr || pos.ptr > finish.ptr)
            throw std::out_of_range("");
        int index = pos - start;
        if (finish == end_of_storage)
            reserve(capacity() << 1);
        pos = start + index;
        alloc.construct(finish.ptr, *(finish - 1));
        finish++;
        std::copy_backward(pos, finish - 2, finish - 1);
        *pos = value;
        return pos;
    }
    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will
     * increase 1.)
     */
    iterator insert(const size_t &pos, const T &data) {
        return insert(begin() + pos, data);
    }
    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos) {
        if (pos.ptr < start.ptr || pos.ptr >= finish.ptr)
            throw std::out_of_range("");
        if (pos + 1 != finish)
            std::copy(pos + 1, finish, pos);
        --finish;
        alloc.destroy(finish.ptr);
        return pos;
    }
    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &pos) { return erase(begin() + pos); }
    /**
     * adds an element to the end.
     */
    void push_back(const value_type &value) {
        if (finish == end_of_storage)
            reserve(capacity() << 1);
        alloc.construct(finish.ptr, value);
        finish++;
    }
    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back() {
        finish--;
        alloc.destroy(finish.ptr);
    }

  private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
    allocator_type alloc;
};

// NOLINTEND

int n, cnt, q, lim;
int a[MAXN], fa[MAXN], head[MAXN], depth[MAXN], mson[MAXN];
long long siz[MAXN], buf[MAXN], ans[MAXN];
long long *cur = buf, *f[MAXN];

int qcnt, headq[MAXN];
struct {
    int k_, i_, next_;
} query[MAXN];

void Print() {
    for (int i = 1; i <= q;) {
        long long res = 0;
        for (int j = i; j <= min(q, i + lim - 1); j++) {
            res ^= ans[j];
        }
        i += lim;
        cout << res << endl;
    }
}

void AddEdge(int u, int v) {
    edge[++cnt] = {v, head[u]};
    head[u] = cnt;
}

void Build(int u) {
    depth[u] = 1;
    siz[u] = a[u];
    for (int i = head[u]; i != 0; i = edge[i].next_) {
        int v = edge[i].v_;
        Build(v);
        if (depth[v] + 1 > depth[u]) {
            mson[u] = v;
            depth[u] = depth[v] + 1;
        }
        siz[u] += siz[v];
    }
}

void Dfs(int u, int tp) {
    if (tp == u) {
        f[u] = cur;
        cur += depth[u];
    }
    f[u][0] = siz[u];
    if (mson[u] != 0) {
        f[mson[u]] = f[u] + 1;
        Dfs(mson[u], tp);
    }
    for (int i = head[u]; i != 0; i = edge[i].next_) {
        int v = edge[i].v_;
        if (v == mson[u]) {
            continue;
        }
        Dfs(v, v);
        for (int j = 0; j < depth[v]; j++) {
            f[u][j + 1] += f[v][j];
        }
    }
    for (int i = headq[u]; i != 0; i = query[i].next_) {
        ans[query[i].i_] = f[u][query[i].k_];
    }
        
}

auto main() -> int {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        AddEdge(fa[i], i);
    }
    Build(1);
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int x;
        int k;
        cin >> x >> k;
        if (depth[x] > k) {
            query[++qcnt] = {k, i, headq[x]};
            headq[x] = qcnt;
        }
    }
    Dfs(1, 1);
    cin >> lim;
    Print();
    return 0;
}