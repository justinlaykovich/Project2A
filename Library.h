#ifndef LIBRARY_H
#define LIBRARY_H
#include<string>
#include<vector>
#include"EmployeePQueue.cpp"
#include"Book.h"
#include"Date.h"

class Library {
public:
   void add_employee(const std::string&);
   void add_book(const std::string&);
   void circulate_book(const std::string&, Date);
   void pass_on(const std::string&, Date);
private:
   std::vector<Employee> employees;
   std::vector<Book> books;
   std::vector<Book> archived_books;
   int find_book(const string&,std::vector<Book>);
   int find_employee(const string&);
};

#endif
