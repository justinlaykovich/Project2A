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
   std::cout << "Added " << new_employee.name << " to employees." << std::endl;

   int size = books.size();

   #pragma omp parallel for
   for(int i = 0; i < size; i++)
      books[i].waiting_list.insert(new_employee);

}

void Library::circulate_book(const string& book_name, Date date) {

   int index = find_book(book_name,archived_books);

   if(index == -1)
      throw runtime_error("No book found in archives: " + book_name);

   Book book = archived_books[index];
   book.circulation_start_date = date;
   book.circulation_last_date = date;
   book.archived = false;
   book.waiting_list = PriorityQueue<Employee>(employees);

   Employee employee = book.waiting_list.extract_max();
   employee.books_possessed += 1;
   employees[find_employee(employee.name)] = employee;

   book.current_employee = employee;

   int size = books.size();

   update_employee(employee);

   books.push_back(book);
   archived_books.erase(archived_books.begin() + index);

   std::cout << "Moved " << book.name << " from archives to circulation." << std::endl;
}

void Library::pass_on(const string& book_name, Date date) {

   int index = find_book(book_name, books);

   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   Book *book = &(books[index]);
   Employee employee = book->current_employee;
   employee.retaining_time += date - (book->circulation_last_date);
   employee.books_possessed -= 1;
   employees[find_employee(employee.name)] = employee;

   if(book->waiting_list.is_empty()) {
      std::cout << "Moved " << book->name << " to archive." << std::endl;

      book->circulation_end_date = date;
      book->circulation_last_date = date;
      book->archived = true;

      archived_books.push_back(*book);

      if(books.size() == 1)
         books.pop_back();
      else
         books.erase(books.begin() + index);

      update_employee(employee);
   }
   else {

      Employee newEmployee = book->waiting_list.extract_max();
      newEmployee.waiting_time += date - (book->circulation_start_date);
      newEmployee.books_possessed += 1;

      book->current_employee = newEmployee;
      book->circulation_last_date = date;

      int size = books.size();

      update_employee(newEmployee);

      std::cout << "Moved " << book->name << " from " << employee.name << " to " << newEmployee.name << std::endl;
      std::cout << newEmployee.name << " wait time: " << newEmployee.waiting_time << std::endl;
      std::cout << employee.name << " retaining time: " << employee.retaining_time << std::endl;
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
            else if(book_list[i].name == book_name)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(book_list[j].name == book_name)
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
      books[i].waiting_list.invalidate(employee);
}
