#ifndef PQueue_H
#define PQueue_H

#include<stdexcept>
#include<vector>
#include"omp.h"

template <class T>
class PriorityQueue {
public:
   PriorityQueue();
   PriorityQueue(const std::vector<T>&);
   void insert(const T& item);
   void invalidate(const T&);
   bool is_empty();
   T extract_max();
   T top();
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
   int find(const T& item);
};

#endif
