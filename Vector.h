
#include <iostream>
#include <stdexcept>

template <typename T>

class Vector {
   public:
    typedef T&& rvalue;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;
    typedef T* pointer;
    typedef T* iterator;
    typedef const T* const_iterator;

   private:
    pointer vData;
    size_type vSize;
    size_type vCapacity;

   public:
    // constructors
    Vector() : vSize{0}, vCapacity{0}, vData{nullptr} {}

    Vector(size_type s, value_type val) {
        if (s < 0)
            throw std::out_of_range{
                "class Vector cannot contain negative amount of values"};
        vSize = s;
        vCapacity = vSize;
        vData = new value_type[vCapacity];

        std::fill_n(vData, s, val);
    }

    Vector(const Vector& vec)
        : vSize{vec.vSize},
          vCapacity{vec.vSize},
          vData{new value_type[vec.vSize]} {
        for (int i = 0; i != vSize; ++i) {
            vData[i] = vec.vData[i];
        }
    }

    Vector(std::initializer_list<value_type> il)
        : vSize{il.size()},
          vCapacity{il.size()},
          vData{new value_type[il.size()]} {
        std::copy(il.begin(), il.end(), vData);
    }

    Vector(Vector&& vec)
        : vSize{vec.vSize}, vCapacity{vec.vSize}, vData{vec.vData} {
        vec.vData = nullptr;
        vec.vSize = 0;
        vec.vCapacity = 0;
    }

    // destructor
    ~Vector() { delete[] vData; }

    // getters
    iterator begin() { return vData; }
    iterator back() { return vData[size() - 1]; }
    iterator end() { return vData + vSize; }
    size_type size() const { return vSize; }
    size_type capacity() { return vCapacity; }
    size_type size() { return vSize; }

    // operators
    reference operator[](size_type a) {
        if (a > vSize or a < 0) {
            throw std::out_of_range{"ref operator []"};
        }
        return vData[a];
    }

    const_reference operator[](size_type i) const {
        if (i < 0 or capacity() <= i) {
            throw std::out_of_range{"const ref operator []"};
        }
        return vData[i];
    }

    Vector<value_type>& operator=(Vector&& v) {
        if (&v == this) {
            return *this;
        }
        delete[] vData;
        vData = v.vData;
        vCapacity = vSize;
        vSize = v.vSize;
        v.vData = nullptr;
        v.vCapacity = 0;
        v.vSize = 0;
        return *this;
    }

    // copy assigment
    Vector<value_type>& operator=(const Vector& v) {
        if (&v == this) {
            return *this;
        }
        delete[] vData;
        vData = new value_type[v.vSize];
        for (auto i = 0; i != v.vSize; ++i) {
            vData[i] = v.vData[i];
        }
        vCapacity = v.vCapacity;
        vSize = v.vSize;

        return *this;
    }

    void resize(size_type rsize) {
        if (rsize < 0) {
            throw std::out_of_range{"in function Vector::resize"};
        }
        pointer temp;
        temp = new value_type[rsize];
        if (rsize < vSize) {
            for (auto i = 0; i < rsize; i++) {
                temp[i] = vData[i];
            }
        } else if (rsize == vCapacity) {
            for (auto i = 0; i < vSize; i++) {
                temp[i] = vData[i];
            }
            delete[] vData;
        }
        if (rsize > vCapacity) {
            reserve(vCapacity);
            for (auto i = 0; i < vSize; i++) {
                temp[i] = vData[i];
            }
            for (auto i = vSize; i < vCapacity; i++) {
                temp[i] = value_type();
            }
            delete[] vData;
        }
        vSize = rsize;
        vData = temp;
        temp = nullptr;
    }

    iterator erase(iterator pointer) {
        size_type deletePos;
        for (size_type i = 0; i < vSize; ++i) {
            if (&vData[i] == pointer) {
                deletePos = i;
            }
        }
        for (size_type i = deletePos; i < vSize; i++) {
            vData[i] = vData[i + 1];
        }
        vData[vSize].~value_type();
        vSize = vSize - 1;
        return &vData[deletePos];
    }

    iterator erase(iterator start, iterator end) {
        size_type startPos;
        size_type endPos;

        for (size_type i = 0; i < vSize; ++i) {
            if (&vData[i] == start) {
                startPos = i;
            }
            if (&vData[i] == end - 1) {
                endPos = i;
            }
        }

        if (endPos > vSize) {
            throw std::out_of_range("out of range erasing");
        }

        for (size_type i = startPos; i <= endPos; i++) {
            int z = 1;
            if (endPos + z < vSize) {
                vData[i] = vData[endPos + z];
                vData[endPos + z].~value_type();
            } else {
                vData[i].~value_type();
            }
            z++;
        }
        vSize = vSize - (endPos - startPos + 1);
        return &vData[vSize - 1];
    }

    void reserve(size_type rcapacity) {
        if (vCapacity < rcapacity) {
            vCapacity = rcapacity;
            value_type* temp = new value_type[vCapacity];

            for (auto i = 0; i < vSize; i++) {
                temp[i] = vData[i];
            }

            delete[] vData;
            vData = temp;
            temp = nullptr;
        }
    }

    void push_back(const_reference value) {
        if (vCapacity == 0) {
            vCapacity++;
            vSize++;
            vData = new value_type[vSize];
            vData[0] = value;
        } else {
            if (vSize >= vCapacity) {
                reserve(vCapacity * 2);
            }
            vData[vSize++] = value;
        }
    }

    void push_back(rvalue value) {
        if (vCapacity == 0) {
            vCapacity++;
            vSize++;
            vData = new value_type[vSize];
            vData[0] = value;
        } else {
            if (vSize >= vCapacity) {
                reserve(vCapacity * 2);
            }

            vData[vSize++] = value;
        }
    }

    iterator insert(iterator pos, const_reference value) {
        iterator temp = begin();
        size_type i = 0;
        while (temp != pos) {
            i++;
            temp++;
        }
        temp = nullptr;

        if (vSize + 1 > vCapacity) {
            reserve(vCapacity * 2);
        }
        for (auto j = vSize; j > i; j--) {
            vData[j] = vData[j - 1];
        }
        vData[i] = value;
        vSize++;

        return &vData[i];
    }

    void pop_back() {
        if (vSize == 0) {
            throw std::out_of_range{"pop_back"};
        }
        vData[vSize - 1].~value_type();
        vSize--;
    }

    void shrink_to_fit() {
        if (vCapacity > vSize) {
            value_type* temp = new value_type[vSize];
            for (auto i = 0; i < vSize; i++) {
                temp[i] = vData[i];
            }
            delete[] vData;
            vData = temp;
            temp = nullptr;
            vCapacity = vSize;
        }
    }
};