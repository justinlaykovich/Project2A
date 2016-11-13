#include"Library.h"
#include<iostream>

void Library::add_book(const string& book_name) {
   /* Adds book to archives */
   Book book;
   book.name = book_name;
   archived_books.push_back(book);
   std::cout << "Added " << book.name << " to archived books." << std::endl;
}

void Library::add_employee(const string& employee_name) {
   /* Adds new employee to employee list */
   Employee new_employee = Employee(employee_name);
   employees.push_back(new_employee);

   /*
      Since I can parallelize this (no interdependence between books):
      this adds to the waiting list of all current, in-circulation books.
   */

   int size = books.size();

   #pragma omp parallel for num_threads(4)
   for(int i = 0; i < size; i++)
      books[i].waiting_list.insert(new_employee);

   std::cout << "Added " << new_employee.name << " to employees." << std::endl;
}

void Library::circulate_book(const string& book_name, const Date& date) {

   int index = find(book_name,archived_books);

   if(index == -1)
      throw runtime_error("No book found in archives: " + book_name);

   /*
      Attains a book from the archives
      Sets properties relevant to circulated books
   */

   Book book = archived_books[index];
   book.circulation_start_date = date;
   book.circulation_last_date = date;
   book.archived = false;
   book.waiting_list = PriorityQueue<Employee>(employees);

   /* Sends to the first employee. extract_max() is log(n) on employees list */

   Employee employee = book.waiting_list.extract_max();
   employee.books_possessed += 1;
   employees[find(employee.name,employees)] = employee;

   book.current_employee = employee;

   /*
      Updates with new values - adding book count changes priority.
      this allows one to circulate multiple books adjusted for whether
      an employee already has a book or not
   */

   update_employee(employee);

   books.push_back(book);

   /* Remove the book from the archives */
   archived_books.erase(archived_books.begin() + index);

   std::cout << "Moved " << book.name << " from archives to circulation." << std::endl;
}

void Library::pass_on(const string& book_name, const Date& date) {

   int index = find(book_name, books);

   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   /* Grab book */
   Book *book = &(books[index]);
   /* Grab the current employee */
   Employee employee = book->current_employee;

   /* Adjust employee properties */
   employee.retaining_time += date - (book->circulation_last_date);
   employee.books_possessed -= 1;

   /* Modifies employee in Employee list */
   employees[find(employee.name,employees)] = employee;

   if(book->waiting_list.is_empty()) {
      std::cout << "Moved " << book->name << " to archive." << std::endl;

      /* No more in waiting list... End_date is set */
      book->circulation_end_date = date;
      book->circulation_last_date = date;

      /* And book added to archive */
      book->archived = true;
      archived_books.push_back(*book);

      if(books.size() == 1)
         books.pop_back();
      else {
         /* Unnecessary to adjust values if no more books */
         books.erase(books.begin() + index);
         update_employee(employee);
      }
   }
   else {
      /*
         Since waiting list isn't empty, a new employee is grabbed and set
         extract_max() is log(n) on employees in waiting_list
      */

      Employee newEmployee = book->waiting_list.extract_max();
      newEmployee.waiting_time += date - (book->circulation_start_date);
      newEmployee.books_possessed += 1;

      /* And the book iteself is adjusted to reflect this */
      book->current_employee = newEmployee;
      book->circulation_last_date = date;

      /*
         And the priorities are updated in books
         Updates are mlog(n) on m, book_list and n, waiting_list.
      */

      update_employee(newEmployee);
      update_employee(employee);

      std::cout << "Moved " << book->name << " from " << employee.name << " to " << newEmployee.name << std::endl;
      std::cout << newEmployee.name << " wait time: " << newEmployee.waiting_time << std::endl;
   }
   std::cout << employee.name << " retaining time: " << employee.retaining_time << std::endl;
}

template<typename T>
int Library::find(const string& name, const std::vector<T>& list) const {

   int size = list.size();
   int index = -1;

   /*
      Find can be parallelized without disrupting anything.
      Splits into two threads.
   */

   #pragma omp parallel sections num_threads(2)
   {
      #pragma omp section
         for(int i = 0; i < size/2; i++)
            if(index != -1)
               break;
            else if(list[i].name == name)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(list[j].name == name)
               index = j;
   }

   /*
      Will return index or -1 if not found.
      Not found is valid.
   */

   return index;
}

void Library::update_employee(const Employee& employee) {
   int size = books.size();

   /* Since books are not interdependent, paralellization can speed this up. */
   #pragma omp parallel for num_threads(4)
   for(int i = 0; i < size; i++)
      books[i].waiting_list.invalidate(employee);
}
