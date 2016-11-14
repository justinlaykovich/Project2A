#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

class Employee {
public:
   Employee(const string&);
   const string& get_name() const;
   void receive_book(const int&);
   void pass_on(const int&);
   const int& get_retaining_time() const;
   const int& get_waiting_time() const;

   /*
      Priority is waiting_time - retaining_time - books_possessed*1000
      so that a person who holds a book already is not prioritized to get it
      again, but they can if everyone else is holding a book.
   */

   int priority() const{
      return waiting_time - (retaining_time + books_possessed*1000);
   }

   /* Compare Employee by name only */
   bool operator==(const Employee& rhs) const {
      return name == rhs.name;
   }
private:
   string name;
   int waiting_time;
   int retaining_time;
   unsigned int books_possessed;
};

class CompareEmployee {
public:
   bool operator () (const Employee& lhs, const Employee& rhs) const {
      return lhs.priority() > rhs.priority();
   }
};

#endif
