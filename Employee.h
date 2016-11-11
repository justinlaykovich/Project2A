#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

class Employee {
public:
   string name;
   int waiting_time;
   int retaining_time;
   unsigned int books_possessed = 0;
   operator int() const {
      return waiting_time - (retaining_time + books_possessed*1000);
   }
   bool operator==(const Employee& rhs) const {
      return name == rhs.name;
   }
   Employee(string new_name = "") {
      name = new_name;
      waiting_time = 0;
      retaining_time = 0;
   }
};

#endif
