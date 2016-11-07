#include"Library.h"
#include<iostream>
using std::cout;
using std::endl;

void Library::add_book(const string& book_name) {
   Book book;
   book.name = book_name;
   archived_books.push_back(book);
}

void Library::add_employee(const string& employee_name) {
   employees.push_back(Employee(employee_name,0,0));
}

void Library::circulate_book(const string& book_name, Date date) {
   int index = find_book(book_name,archived_books);
   if(index == -1)
      throw runtime_error("No book found in archives: " + book_name);

   Book book = archived_books[index];
   archived_books.erase(archived_books.begin() + index);
   book.circulation_start_date = date;
   book.waiting_list = PriorityQueue<Employee>(employees);

   Employee employee = book.waiting_list.extract_max();
   employee.waiting_time = 0;
   book.current_employee = employee;

   int size = books.size();
   for(int i = 0; i < size; i++)
      books[i].waiting_list.invalidate(employee);

   books.push_back(book);
}

void Library::pass_on(const string& book_name, Date date) {
   int index = find_book(book_name, books);
   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   Book book = books[index];
   Employee employee = book.current_employee;
   employee.retaining_time = (date - book.circulation_start_date);
   employees[find_employee(employee.name)] = employee;

   Employee newEmployee = book.waiting_list.extract_max();
   newEmployee.waiting_time = newEmployee.waiting_time + employee.retaining_time;
   book.current_employee = newEmployee;

   int size = books.size();
   for(int i = 0; i < size; i++) {
      books[i].waiting_list.invalidate(employee);
      books[i].waiting_list.invalidate(newEmployee);
   }
}

int Library::find_book(const string& book_name, std::vector<Book> book_list) {
   int i;
   int size = book_list.size();
   for(i = 0; i < size; i++) {
      if(book_list[i].name == book_name)
         return i;
   }
   return -1;
}

int Library::find_employee(const string& employee_name) {
   int i = 0;
   for(auto itr = employees.begin(); itr != employees.end(); itr++) {
      if((*itr).name == employee_name)
         return i;
      i++;
   }
   return -1;
}
