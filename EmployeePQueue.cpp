#include"EmployeePQueue.h"
#include<stdexcept>
#include<algorithm>
#include<iostream>

using std::cout;
using std::endl;

EmployeeEmployeePQueue::EmployeePQueue() {
   size = 0;
}

EmployeePQueue::EmployeePQueue(const std::vector<Employee>& inserted) {
   size = 0;
   int insertSize = inserted.size();
   for(int i = 0; i < insertSize; i++)
      insert(inserted[i]);
}

void EmployeePQueue::insert(const Employee& item) {
   data.push_back(item);
   size++;

   for(int i = (size-1); i > 0; i = (i-1)/2)
      if(!(data[(i-1)/2] > data[i]))
         std::swap(data[(i-1)/2],data[i]);
      else
         break;
}

void EmployeePQueue::max_heapify() {
   max_heapify(0);
}

void EmployeePQueue::max_heapify(int i) {
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

Employee EmployeePQueue::extract_max() {
   Employee item = data[0];
   remove(0);
   return item;
}

Employee EmployeePQueue::top() {
   return data[0];
}

void EmployeePQueue::remove(const int& index){
   if(index >= size || index < -1)
      throw;

   data[index] = data[size-1];
   data.pop_back();
   size--;
   max_heapify(index);
}

bool EmployeePQueue::is_empty() {
   return size == 0;
}

void EmployeePQueue::invalidate(const Employee& item) {
   for(int i = 0; i < size; i++)
      if(data[i] == item) {
         cout << "Invalidated." << endl;
         remove(i);
         insert(item);
         break;
      }
}
