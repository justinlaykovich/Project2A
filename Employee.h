#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

class Employee {
public:
   string name;
   int waiting_time;
   int retaining_time;
   unsigned int books_possessed = 0;

   /*
      Rather than overloading comparison operators, this
      overloads int operator, which is used by comparison by default.
      Also allows for one to cout << employee to get its priority.

      Priority is waiting_time - retaining_time - books_possessed*1000
      so that a person who holds a book already is not prioritized to get it
      again, but they can if everyone else is holding a book.
   */
   operator int() const {
      return waiting_time - (retaining_time + books_possessed*1000);
   }

   /* Compare Employee by name only */
   bool operator==(const Employee& rhs) const {
      return name == rhs.name;
   }

   /* Constructor for Employee */
   Employee(string new_name = "") {
      name = new_name;
      waiting_time = 0;
      retaining_time = 0;
   }
};

#endif
