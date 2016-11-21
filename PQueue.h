#ifndef PQueue_H
#define PQueue_H

#include<stdexcept>
#include<vector>
#include"omp.h"

/*
   The custom PriorityQueue as specified by the project spec.
   Not instantiated on any particular structure.
   Implemented by max_heap.
*/

template <class T, class Compare = std::greater<T> >
class PriorityQueue {
public:
   PriorityQueue();
   PriorityQueue(const std::vector<T>&);
   void insert(const T&);
   /*
      update updates list by specifying that a value has been modified
      and is no longer valid.
      Effectively O(log n)
   */
   void update(const T&);
   bool is_empty() const;
   /* Extract max, O(log n), is simply a top and pop combined. */
   T extract_max();
   const T& top() const;
   void pop();
private:
   std::vector<T> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int&);
   int find(const T&) const;
   inline const int parent_of(int index) { return (index-1)/2; };
   inline const int left_child_of(int index) { return index*2+1; };
   inline const int right_child_of(int index) { return index*2+2; };
   Compare compare;
};

#endif
