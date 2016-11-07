#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include<string>
#include<vector>
#include"Date.h"
#include"PQueue.cpp"
#include"Employee.h"
#include"Book.h"

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
