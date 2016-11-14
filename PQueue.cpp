#include"PQueue.h"

template<class T, class Compare>
PriorityQueue<T,Compare>::PriorityQueue() {
   size = 0;
}

template<class T, class Compare>
PriorityQueue<T,Compare>::PriorityQueue(const std::vector<T>& inserted) {
   size = 0;

   /*
      Each insert is log(n) individually.
      Results in nlog(n).
      Cannot be parallelized -- interdependent.
   */

   int insertSize = inserted.size();
   for(int i = 0; i < insertSize; i++)
      insert(inserted[i]);
}

template<class T, class Compare>
void PriorityQueue<T,Compare>::insert(const T& item) {
   data.push_back(item);

   /* log(n) insert */
   for(int i = size; i > 0; i = parent_of(i))
      if(!compare(data[parent_of(i)],data[i]))
         std::swap(data[parent_of(i)],data[i]);
      else
         break;

   size++;
}

template<class T, class Compare>
void PriorityQueue<T,Compare>::max_heapify() {
   max_heapify(0);
}

template<class T, class Compare>
void PriorityQueue<T,Compare>::max_heapify(int i) {
   int largest = i;

   /*
      This is the abstracted max_heapify referred to in the MIT 6.004 Lecture Series.
      series and put in a non-abstracted way in this CS303.
   */

   while(true) {
      int left = left_child_of(i);
      int right = right_child_of(i);

      if(left >= size || right >= size)
         break;

      if (compare(data[left],data[largest]))
          largest = left;
      if (compare(data[right],data[largest]))
          largest = right;

      if (largest != i) {
         std::swap(data[largest],data[i]);
         i = largest;
      }
      else
         break;
   }
}

template<class T,class Compare>
T PriorityQueue<T,Compare>::extract_max() {
   /* pop is log(n) and so the function in total is log(n) */
   T item = top();
   pop();
   return item;
}

template<class T,class Compare>
const T& PriorityQueue<T,Compare>::top() const {
   /* Constant time, O(1) */

   if(size == 0)
      throw runtime_error("No item in queue.");

   return data[0];
}

template<class T,class Compare>
void PriorityQueue<T,Compare>::pop() {
   if(size == 0)
      throw runtime_error("No item in queue.");

   /* Remove is log(n) and so this is log(n) */
   remove(0);
}

template<class T, class Compare>
void PriorityQueue<T,Compare>::remove(const int& index){
   if(index >= size || index < -1)
      throw invalid_argument("Index out of bounds." );

   size--;
   if(size == 0) {
      /* Not much to do if there's nothing to do it on */
      data.pop_back();
      return;
   }

   /* This is sort of the inverse reasoning to insert */
   data[index] = data[size];
   data.pop_back();

   /* max_heapify only if there is more than 1 item.
      Otherwise it's pointless. */
   if(size > 1)
      max_heapify(index);
}

template<class T, class Compare>
bool PriorityQueue<T,Compare>::is_empty() const {
   return size == 0;
}

template<class T, class Compare>
int PriorityQueue<T,Compare>::find(const T& item) const {
   int index = -1;
   /*
      Find can be parallelized, and it's good to do so
      when searching for items based on things orthogonal to
      how they are sorted.

      Two threads. Otherwise linear.
   */
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
   /* -1 is a valid value. */
   return index;
}

template<class T, class Compare>
void PriorityQueue<T,Compare>::invalidate(const T& item) {
   int index = find(item);
   /* Don't throw error if item not in list -- just return */
   if(index == -1)
      return;

   data[index] = item;

   /* This is the algorithm expressed in class, + max_heapify below. */
   if((index > 0) && (compare(data[index],data[parent_of(index)]))) {
      for(data[index] = item; index > 0; index = parent_of(index))
         if(compare(data[index],data[parent_of(index)]))
            std::swap(data[index],data[parent_of(index)]);
         else
            /*
               Presumably no reason to max_heapify since
               employee would be greater than root and root
               has to this point retained max_heap property.
            */
            return;
   }

   max_heapify(index);
}
