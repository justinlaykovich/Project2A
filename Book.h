#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
   Book(const std::string&);
   void circulate(Date,std::vector<Employee>);
   void end_circulation(Date);
   void pass_book(Date);
   std::string get_name();
   bool waiting_list_empty();
   void update(const Employee&);
   Employee* get_current_employee();
   bool operator==(const Book& rhs) {
      return name == rhs.name;
   }
private:
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   Date circulation_last_date;
   Employee current_employee;
   bool archived;
   PriorityQueue<Employee> waiting_list;
};

Book::Book(const string& name) {
   this->name = name;
   archived = true;
}

Employee* Book::get_current_employee() {
   return &current_employee;
}

void Book::update(const Employee& employee) {
   waiting_list.invalidate(employee);
}

void Book::circulate(Date date, std::vector<Employee> employees) {
   circulation_start_date = date;
   circulation_last_date = date;
   waiting_list = PriorityQueue<Employee>(employees);
   current_employee = waiting_list.extract_max();
   archive = false;
   std::cout << "Moved " << book.name << " from archives to circulation." << std::endl;
}

void Book::end_circulation(Date date) {
   circulation_end_date = date;
   archived = true;
   std::cout << "Moved " << book->name << " to archive." << std::endl;
}

bool Book::waiting_list_empty() {
   return waiting_list.is_empty();
}

void Book::pass_book(Date date) {
   if(is_empty())
      throw runtime_error("No employee on waiting list.");

   Employee employee = *current_employee;

   current_employee = waiting_list.extract_max();
   current_employee.books_possessed += 1;
   circulation_last_date = date;

   std::cout << "Moved " << book->name << " from " << employee.name << " to " << current_employee.name << std::endl;
   std::cout << current_employee.name << " wait time: " << current_employee.waiting_time << std::endl;
   std::cout << employee.name << " retaining time: " << employee.retaining_time << std::endl;
}

std::string Book::get_name() {
   return name;
}

#endif
