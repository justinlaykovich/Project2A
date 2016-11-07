#ifndef LIBRARY_H
#define LIBRARY_H
#include<string>
#include<list>
#include"Date.h"
#include"PQueue.cpp"

struct Employee {
   string name;
   int waiting_time;
   int retaining_time;
   bool operator<(const Employee& rhs) {
      return (waiting_time - retaining_time) < (rhs.waiting_time - rhs.retaining_time);
   }
   bool operator>(const Employee& rhs) {
      return (waiting_time - retaining_time) > (rhs.waiting_time - rhs.retaining_time);
   }
   bool operator==(const Employee& rhs) {
      return name == rhs.name;
   }
   bool operator==(const string& rhs) {
      return name == rhs;
   }
   Employee(string new_name = "", int new_waiting_time = 0, int new_retaining_time = 0) {
      name = new_name;
      waiting_time = new_waiting_time;
      new_retaining_time = new_retaining_time;
   }
};

struct Book {
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   Employee current_employee;
   bool archived;
   PriorityQueue<Employee> waiting_list;
   bool operator==(const string& rhs) {
      return name == rhs;
   }
   bool operator==(const Book& rhs) {
      return name == rhs.name;
   }
};

class Library {
public:
   void add_employee(const std::string&);
   void add_book(const std::string&);
   void circulate_book(const std::string&, Date);
   void pass_on(const std::string&, Date);
private:
   std::list<Employee> employees;
   std::list<Book> books;
   std::list<Book> archived_books;
};

#endif
