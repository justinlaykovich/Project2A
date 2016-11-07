#ifndef PQueue_H
#define PQueue_H

#include<vector>

template <class T>
class PriorityQueue {
public:
   PriorityQueue();
   PriorityQueue(const std::vector<T>&);
   void insert(const T& item);
   void invalidate(const int&);
   void invalidate(T&);
   bool is_empty();
   T extract_max();
   T top();
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
};

#endif
