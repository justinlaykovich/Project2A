#include"Library.h"
#include<iostream>
using std::cout;
using std::endl;

void Library::add_book(const string& book_name) {
   Book book;
   book.name = book_name;
   archived_books.push_back(book);
   cout << "Added " << book.name << " to archived books." << endl;
}

void Library::add_employee(const string& employee_name) {
   Employee new_employee = Employee(employee_name,0,0);
   employees.push_back(Employee(employee_name,0,0));
   cout << "Added " << new_employee.name << " to employees." << endl;
}

void Library::circulate_book(const string& book_name, Date date) {
   int index = find_book(book_name,archived_books);
   if(index == -1)
      throw runtime_error("No book found in archives: " + book_name);

   Book book = std::move(archived_books[index]);
   book.circulation_start_date = date;
   book.circulation_last_date = date;
   book.waiting_list = PriorityQueue<Employee>(employees);

   Employee employee = book.waiting_list.extract_max();
   book.current_employee = employee;
   book.archived = false;

   int size = books.size();
   for(int i = 0; i < size; i++)
      books[i].waiting_list.invalidate(employee);

   books.push_back(book);
   archived_books.erase(archived_books.begin() + index);
   cout << "Moved " << book.name << " from archives to circulation." << endl;
}

void Library::pass_on(const string& book_name, Date date) {
   int index = find_book(book_name, books);
   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   Book *book = &(books[index]);
   Employee employee = book->current_employee;
   employee.retaining_time += date - book->circulation_last_date;

   cout << employee.name << " retaining time: " << employee.retaining_time << endl;
   employees[find_employee(employee.name)] = employee;

   if(book->waiting_list.is_empty()) {
      book->circulation_end_date = date;
      book->archived = true;
      archived_books.push_back(*book);

      int size= books.size();
      for(int i = 0; i < size; i++)
         books[i].waiting_list.invalidate(employee);

      cout << "Moved " << book->name << " to archive." << endl;
      if(books.size() == 1)
         books.pop_back();
      else
         books.erase(books.begin() + index);

   }
   else {
      Employee newEmployee = book->waiting_list.extract_max();
      newEmployee.waiting_time += date - book->circulation_start_date;
      cout << newEmployee.name << " wait time: " << newEmployee.waiting_time << endl;

      book->current_employee = newEmployee;
      int size = books.size();
      for(int i = 0; i < size; i++) {
         books[i].waiting_list.invalidate(employee);
         books[i].waiting_list.invalidate(newEmployee);
      }
      cout << "Moved " << book->name << " from " << employee.name << " to " << newEmployee.name << endl;
   }

   book->circulation_last_date = date;
}

int Library::find_book(const string& book_name, std::vector<Book> book_list) {
   int size = book_list.size();
   for(int i = 0; i < size; i++) {
      if(book_list[i].name == book_name)
         return i;
   }
   return -1;
}

int Library::find_employee(const string& employee_name) {
   int size = employees.size();
   for(int i = 0; i < size; i++) {
      if(employees[i].name == employee_name)
         return i;
   }
   return -1;
}
