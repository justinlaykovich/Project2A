#ifndef HEAP_H
#define HEAP_H

#include<vector>

template <class T>
class MaxHeap {
public:
   MaxHeap():MaxHeap({}){};
   MaxHeap(const std::vector<T>&);
   void insert(const T& item);
   T extract_max();
   int get_size();

   const std::vector<T>& as_vector();
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
};

#endif
