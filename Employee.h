#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>

struct Employee {
   string name;
   int waiting_time;
   int retaining_time;
   int priority() const {
      return (waiting_time - retaining_time);
   }
   bool operator>(const Employee& rhs) {
      return (priority() > rhs.priority());
   }
   bool operator<(const Employee& rhs) {
      return (priority() < rhs.priority());
   }
   bool operator==(const Employee& rhs) {
      return name == rhs.name;
   }
   Employee(string new_name = "", int new_waiting_time = 0, int new_retaining_time = 0) {
      name = new_name;
      waiting_time = new_waiting_time;
      new_retaining_time = new_retaining_time;
   }
};

#endif
