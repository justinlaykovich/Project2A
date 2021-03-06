#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include<string>
#include<stdexcept>
#include<vector>

#include"Date.h"
#include"PQueue.cpp"
#include"Employee.cpp"
#include"Book.cpp"

#include"omp.h"

class Library {
public:
   void add_employee(const std::string&);
   void add_book(const std::string&);
   void circulate_book(const std::string&, const Date&);
   void pass_on(const std::string&, const Date&);
private:
   std::vector<Employee> employees;
   std::vector<Book> books;
   std::vector<Book> archived_books;

   void update_employee(const Employee&);

   template<typename T>
   int find(const string&,const std::vector<T>&) const;
};

#endif
