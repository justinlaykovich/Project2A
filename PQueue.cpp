#include"PQueue.h"

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

   for(int i = size; i > 0; i = parent_of(i))
      if(data[parent_of(i)] <= data[i])
         std::swap(data[parent_of(i)],data[i]);
      else
         break;

   size++;
}

template<class T>
void PriorityQueue<T>::max_heapify() {
   max_heapify(0);
}

template<class T>
void PriorityQueue<T>::max_heapify(int i) {
   int largest = i;
   while(true) {
      int left = left_child_of(i);
      int right = right_child_of(i);

      if(left >= size || right >= size)
         break;

      if (data[left] > data[largest])
          largest = left;
      if (data[right] > data[largest])
          largest = right;

      if (largest != i) {
         std::swap(data[largest],data[i]);
         i = largest;
      }
      else
         break;
   }
}

template<class T>
T PriorityQueue<T>::extract_max() {
   T item = top();
   remove(0);
   return item;
}

template<class T>
const T& PriorityQueue<T>::top() const {
   if(size == 0)
      throw runtime_error("No item in queue.");

   return data[0];
}

template<class T>
void PriorityQueue<T>::remove(const int& index){
   if(index >= size || index < -1)
      throw invalid_argument("Index out of bounds." );

   size--;
   if(size == 0) {
      data.pop_back();
      return;
   }

   data[index] = data[size];
   data.pop_back();

   if(size > 1)
      max_heapify(index);
}

template<class T>
bool PriorityQueue<T>::is_empty() const {
   return size == 0;
}

template<class T>
int PriorityQueue<T>::find(const T& item) const {
   int index = -1;
   #pragma omp parallel sections
   {
      #pragma omp section
         for(int i = 0; i < size/2; i++)
            if(index != -1)
               break;
            else if(data[i] == item)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(data[j] == item)
               index = j;
   }
   return index;
}

template<class T>
void PriorityQueue<T>::invalidate(const T& item) {
   int index = find(item);
   if(index == -1)
      return;

   for(data[index] = item; index > 0; index = parent_of(index))
      if(data[parent_of(index)] < data[index])
         std::swap(data[parent_of(index)],data[index]);
      else
         break;

   max_heapify(index);
}
