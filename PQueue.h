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
   bool is_empty() const;
   T extract_max();
   const T& top() const;
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
   int find(const T& item) const;
   inline const int parent_of(int index) { return (index-1)/2; };
   inline const int left_child_of(int index) { return index*2+1; };
   inline const int right_child_of(int index) { return index*2+2; };
};

#endif
