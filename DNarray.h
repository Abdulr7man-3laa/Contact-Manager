#ifndef DNARRAY_H
#define DNARRAY_H

#include <cstddef>
#include <iostream>
#include <stdexcept>
template <typename DT>
class DNarray
{
private:
    size_t size;     // Current size of the array
    size_t capacity; // Maximum capacity of the array
    DT *arr;

public:
    DNarray(){
        size = 0;
        capacity = 10;          // Set initial capacity
        arr = new DT[capacity]; // Allocate memory for the array
    }
    ~DNarray(){
        delete[] arr;
    }
    void resize(){
        int newCapacity = capacity * 2;   // Double the capacity
        DT *newArr = new DT[newCapacity]; // Allocate memory for the new array
        for (int i = 0; i < size; i++)    // Copy the elements from the old array to the new array
        {
            newArr[i] = arr[i];
        }
        delete[] arr;           // Free the memory allocated for the old array
        arr = newArr;           // Set the new array as the current array
        capacity = newCapacity; // Update the capacity
    }
    void append(DT &element){
        if (isFull())
        {
            throw out_of_range("Array is Full");
        }
        arr[size] = element; // Insert the element at the end
        size++;              // Increment the size of the array
    }
    void remove(size_t index){
        if (isEmpty())
        {
            throw out_of_range("Array is empty");
        }
        if (index >= size || index < 0)
        {
            throw out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; i++) // Shift elements left to remove the element at index
        {
            arr[i] = arr[i + 1];
        }
        size--; // Decrement the size of the array
    }
    void reverse(){
        
        if (isEmpty())
        {
            cout << "Array is empty" << endl;
        }
        for (int i = 0; i < size / 2; i++) // Swap the elements of the array
        {
            DT temp = arr[i];           // Temporary variable to hold value of the current element
            arr[i] = arr[size - i - 1]; // Swap the current element with the element at the end of the array
            arr[size - i - 1] = temp;   // Swap the element at the end of the array with the temporary variable
        }
    }
    void update(size_t index, DT &newElement){
        if (isEmpty())
        {
            throw out_of_range("Array is empty");
        }
        if (index >= size || index < 0)
        {
            throw out_of_range("Index out of range");
        }
        arr[index] = newElement; // Update the element at the specified index with the new element
    }
    DT &getElement(size_t index){
        if (isEmpty())
        {
            throw out_of_range("Array is empty");
        }
        if (index >= size || index < 0)
        {
            throw out_of_range("Index out of range");
        }

        return arr[index]; // Return the element at the specified index
    }
    void clear(){
        size = 0; // Set the size of the array to 0 to clear it
    }
    int getSize(){
        return size;
    }
    int getCapacity(){
        return capacity;
    }
    bool isFull(){
        return size == capacity;
    }
    bool isEmpty(){
        return size == 0;
    }
};

#endif