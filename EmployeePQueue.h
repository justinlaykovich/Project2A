#ifndef EmployeePQueue_H
#define EmployeePQueue_H

#include<vector>
#include"Employee.h"

class EmployeePQueue {
public:
   PriorityQueue();
   PriorityQueue(const std::vector<Employee>&);
   void insert(const Employee& item);
   void invalidate(const Employee&);
   bool is_empty();
   Employee extract_max();
   Employee top();
private:
   std::vector<Employee> data;
   int size;
   void max_heapify();
   void max_heapify(int i);
   void remove(const int& index);
};

#endif
