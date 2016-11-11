#include"Library.h"
#include<iostream>

void Library::add_book(const string& book_name) {

   Book book;
   book.name = book_name;
   archived_books.push_back(book);
   std::cout << "Added " << book.name << " to archived books." << std::endl;
}

void Library::add_employee(const string& employee_name) {

   Employee new_employee = Employee(employee_name);
   employees.push_back(new_employee);

   int size = books.size();
   #pragma omp parallel for
   for(int i = 0; i < size; i++)
      books[i].waiting_list.insert(new_employee);

   std::cout << "Added " << new_employee.name << " to employees." << std::endl;
}

void Library::circulate_book(const string& book_name, Date date) {

   int index = find_book(book_name,archived_books);

   if(index == -1)
      throw runtime_error("No book found in archives: " + book_name);

   Book book = archived_books[index];
   book.circulate(date, employees);

   Employee* employee = book.get_current_employee();

   employees[find_employee(employee->name)] = *employee;

   update_employee(*employee);

   books.push_back(book);
   if(archived_books.size() == 1)
      archived_books.pop_back();
   else
      archived_books.erase(archived_books.begin() + index);

}

void Library::pass_on(const string& book_name, Date date) {

   int index = find_book(book_name, books);

   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   Book *book = &(books[index]);
   Employee employee = *(book->get_current_employee());

   employee.retaining_time += date - (book->circulation_last_date);
   employee.books_possessed -= 1;
   employees[find_employee(employee.name)] = employee;

   if(book->waiting_list_empty()) {

      book->end_circulation(date);

      archived_books.push_back(*book);

      if(books.size() == 1)
         books.pop_back();
      else
         books.erase(books.begin() + index);
   }
   else {
      book->pass_book(date);
      Employee* newEmployee = book.get_current_employee();
      newEmployee->waiting_time += date - (book->circulation_start_date);

      update_employee(*newEmployee);
   }
   update_employee(employee);
}

int Library::find_book(const string& book_name, std::vector<Book> book_list) {

   int size = book_list.size();
   int index = -1;

   #pragma omp parallel sections
   {
      #pragma omp section
         for(int i = 0; i < size/2; i++)
            if(index != -1)
               break;
            else if(book_list[i].get_name() == book_name)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(book_list[j].get_name() == book_name)
               index = j;
   }

   return index;
}

int Library::find_employee(const string& employee_name) {

   int size = employees.size();
   int index = -1;

   #pragma omp parallel sections
   {
      #pragma omp section
         for(int i = 0; i < size/2; i++)
            if(index != -1)
               break;
            else if(employees[i].name == employee_name)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(employees[j].name == employee_name)
               index = j;
   }

   return index;
}

void Library::update_employee(const Employee& employee) {
   int size = books.size();
   #pragma omp parallel for
   for(int i = 0; i < size; i++)
      books[i].update(employee);
}
