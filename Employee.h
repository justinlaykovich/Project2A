#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
public:
   string name;
   int waiting_time;
   int retaining_time;
   operator int() {
      return (waiting_time - retaining_time);
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
