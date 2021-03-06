#include"Library.h"
#include<iostream>

void Library::add_book(const string& book_name) {

   /* Adds book to archives */
   Book book(book_name);
   archived_books.push_back(book);
   std::cout << "Added " << book.get_name() << " to archived books." << std::endl;
}

void Library::add_employee(const string& employee_name) {

   /* Adds new employee to employee list */
   Employee new_employee(employee_name);
   employees.push_back(new_employee);

   /*
      Since I can parallelize this (no interdependence between books):
      this adds to the waiting list of all current, in-circulation books.
   */

   size_t size = books.size();

   #pragma omp parallel for num_threads(4)
   for(unsigned int i = 0; i < size; i++)
      books[i].add(new_employee);

   std::cout << "Added " << new_employee.get_name() << " to employees." << std::endl;
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

   /* Sends to the first employee. */
   Employee* employee = book.circulate(date,employees);
   employee->receive_book(0);

   /* Updates with new values - adding book count changes priority. */
   employees[find(employee->get_name(),employees)] = *employee;
   update_employee(*employee);

   /* Move the book from the archives to circulation. */
   books.push_back(book);
   archived_books.erase(archived_books.begin() + index);
   std::cout << "Moved " << book.get_name() << " from archives to circulation." << std::endl;
}

void Library::pass_on(const string& book_name, const Date& date) {

   int index = find(book_name, books);

   if(index == -1)
      throw runtime_error("No book found in circulation: " + book_name);

   /* Grab book */
   Book *book = &(books[index]);

   /* Grab the current employee */
   Employee employee = *(book->get_current_employee());
   employee.pass_on(date - book->get_last_date());

   /* Modifies employee in Employee list */
   employees[find(employee.get_name(),employees)] = employee;

   /* Gets next employee or NULL if non exist */
   Employee* newEmployee = book->get_next_employee(date);

   if(newEmployee == NULL) {

      /* And book added to archive */
      archived_books.push_back(*book);
      std::cout << "Moved " << book->get_name() << " to archive." << std::endl;

      /* Unnecessary to adjust values if no more books */
      if(books.size() == 1)
         books.pop_back();
      else {
         books.erase(books.begin() + index);
         update_employee(employee);
      }
   }
   else {

      /*
         And the priorities are updated in books
         Updates are mlog(n) on m, book_list and n, waiting_list.
      */

      newEmployee->receive_book(date - book->get_start_date());

      update_employee(*newEmployee);
      update_employee(employee);

      std::cout << "Moved " << book->get_name() << " from " << employee.get_name() << " to " << newEmployee->get_name() << std::endl;
      std::cout << newEmployee->get_name() << " wait time: " << newEmployee->get_waiting_time() << std::endl;
   }

   std::cout << employee.get_name() << " retaining time: " << employee.get_retaining_time() << std::endl;
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
            else if(list[i].get_name() == name)
               index = i;
      #pragma omp section
         for(int j = size/2; j < size; j++)
            if(index != -1)
               break;
            else if(list[j].get_name() == name)
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
      books[i].update(employee);
}
