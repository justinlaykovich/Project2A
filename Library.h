#ifndef LIBRARY_H
#define LIBRARY_H
#include"Date.h"
#include<vector>
#include<string>

struct Employee {
   string name;
   int waiting_time;
   int retaining_time;
};

struct Book {
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   bool archived;
};

class Library {
public:
   void add_employee(const std::string&);
   void add_book(const std::string&);
   void circulate_book(const std::string&, Date);
   void pass_on(const std::string&, Date);
private:
   std::vector<Employee> employees;
   std::vector<Book> books;
};

#endif
