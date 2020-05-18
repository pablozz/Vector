# Vector class

## Functions

### push_back(rvalue value)

```
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
```

_push_back_ function inserts given value to the back of the vector and increases its size by 1.

### pop_back()

```
    void pop_back() {
        if (vSize == 0) {
            throw std::out_of_range{"pop_back"};
        }
        vData[vSize - 1].~value_type();
        vSize--;
    }
```

_pop_back_ function removes the last element of the vector and shrinks its size by 1.

### shrink_to_fit()

```
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
```

_shrink_to_fit_ function resizes the capacity to size of vector if the capaciity is bigger than size. It is used when new object is created and values are copied.

### erase(iterator start, iterator end)

```
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
```

this _erase_ function erases a range of elements from start iterator to end iterator and shrinks the size of the vector by size of how much elements were erased.

### insert(iterator pos, const_reference value)

```
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
```

_insert_ function inserts a given value to a given position and expands the size of the vector by 1.

### Test 2

**push_back**

| Capacity  | Vector (s) | std::vector (s) |
| --------- | ---------- | --------------- |
| 10000     | 0          | 0               |
| 100000    | 0.002      | 0.004           |
| 1000000   | 0.018      | 0.035           |
| 10000000  | 0.148      | 0.266           |
| 100000000 | 1.281      | 2.136           |

### Test 3

| Container   | Capacity  | capacity() == size() |
| ----------- | --------- | -------------------- |
| std::vector | 100000000 | 28                   |
| Vector      | 100000000 | 28                   |

[v1.0](https://github.com/Andriusjok/Objektinis3uzd/releases/tag/v1.0)
