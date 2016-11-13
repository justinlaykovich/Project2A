#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

class Employee {
public:
   Employee(const string&);
   const string& get_name() const;
   void receive_book(const int&);
   void pass_on(const int&);
   string name;
   int waiting_time;
   int retaining_time;
   unsigned int books_possessed;

   /*
      Rather than overloading comparison operators, this
      overloads int operator, which is used by comparison by default.
      Also allows for one to cout << employee to get its priority.

      Priority is waiting_time - retaining_time - books_possessed*1000
      so that a person who holds a book already is not prioritized to get it
      again, but they can if everyone else is holding a book.
   */
   operator int() {
      return waiting_time - (retaining_time + books_possessed*1000);
   }

   /* Compare Employee by name only */
   bool operator==(const Employee& rhs) const {
      return name == rhs.name;
   }
};

Employee::Employee(const string& name = "") {
   this->name = name;
   waiting_time = 0;
   retaining_time = 0;
   books_possessed = 0;
}

const string& Employee::get_name() const {
   return name;
}

void Employee::receive_book(const int& waiting_time) {
   books_possessed += 1;
   this->waiting_time += waiting_time;
}

void Employee::pass_on(const int& retaining_time) {
   books_possessed -= 1;
   this->retaining_time += retaining_time;
}

#endif
