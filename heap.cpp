#include"heap.h"
#include<stdexcept>
#include<algorithm>

template<class T>
MaxHeap<T>::MaxHeap(const std::vector<T>& inserted) {
   /* To modify later */
   size = 0;
   int insertSize = inserted.size();
   for(int i = 0; i < insertSize; i++)
      insert(inserted[i]);
}

template<class T>
void MaxHeap<T>::insert(const T& item) {
   data.push_back(item);
   size++;

   for(int i = (size-1); i > 0; i = (i-1)/2)
      if(data[(i-1)/2] < data[i])
         std::swap(data[(i-1)/2],data[i]);
      else
         break;
}

template<class T>
T MaxHeap<T>::extract_max() {
   T val = data[0];
   remove(0);
   return val;
}

template<class T>
void MaxHeap<T>::remove(const int& index){
   if(index >= size || index < -1)
      throw;

   data[index] = data[size-1];
   data.pop_back();
   size--;
   max_heapify(index);
}

template<class T>
void MaxHeap<T>::max_heapify() {
   max_heapify(0);
}

template<class T>
void MaxHeap<T>::max_heapify(int i) {
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
const std::vector<T>& MaxHeap<T>::as_vector() {
   return data;
}

template<class T>
int MaxHeap<T>::get_size() {
   return size;
}
