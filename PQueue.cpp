#include"PQueue.h"
#include<stdexcept>
#include<algorithm>
#include<iostream>

using std::cout;
using std::endl;

template<class T>
PriorityQueue<T>::PriorityQueue() {
   size = 0;
}

template<class T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& inserted) {
   size = 0;
   int insertSize = inserted.size();
   for(int i = 0; i < insertSize; i++)
      insert(inserted[i]);
}

template<class T>
void PriorityQueue<T>::insert(const T& item) {
   data.push_back(item);
   size++;

   for(int i = (size-1); i > 0; i = (i-1)/2)
      if(!(data[(i-1)/2] > data[i]))
         std::swap(data[(i-1)/2],data[i]);
      else
         break;
}

template<class T>
void PriorityQueue<T>::max_heapify() {
   max_heapify(0);
}

template<class T>
void PriorityQueue<T>::max_heapify(int i) {
   int left = 2*i + 1;
   int right = 2*i + 2;
   int largest = i;

   if ((left <= size) &&
       (data[left] > data[largest]))
       largest = left;
   if ((right <= size) &&
       (data[right] > data[largest]))
       largest = right;

   if (largest != i) {
      std::swap(data[largest],data[i]);
      max_heapify(largest);
   }
}

template<class T>
T PriorityQueue<T>::extract_max() {
   T item = data[0];
   remove(0);
   return item;
}

template<class T>
T PriorityQueue<T>::top() {
   return data[0];
}

template<class T>
void PriorityQueue<T>::remove(const int& index){
   if(index >= size || index < -1)
      throw;

   data[index] = data[size-1];
   data.pop_back();
   size--;
   max_heapify(index);
}

template<class T>
bool PriorityQueue<T>::is_empty() {
   return size == 0;
}

template<class T>
void PriorityQueue<T>::invalidate(const T& item) {
   for(int i = 0; i < size; i++)
      if(data[i] == item) {
         cout << "Invalidated." << endl;
         remove(i);
         insert(item);
         break;
      }
}
