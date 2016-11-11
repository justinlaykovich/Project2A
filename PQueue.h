#ifndef PQueue_H
#define PQueue_H

#include<vector>
#include"omp.h"

template <class T>
class PriorityQueue {
public:
   PriorityQueue();
   PriorityQueue(const std::vector<T>&);
   void insert(const T& item);
   void invalidate(const T&);
   bool is_empty() const;
   T extract_max();
   T top() const;
   void pop();
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
   int index_of(const T&) const;
};

#endif
