#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
   Book(const string&);
   Employee* circulate(Date,std::vector<Employee>);
   Employee* pass_on(Date);
   Employee* get_current_employee();
   void add_employee(const Employee&);
   const string& get_name() const;
   bool has_waiting() const;
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   /* circulation_last_date was added to make computation of
      retaining time easier. */
   Date circulation_last_date;

   /* Keeps track of employee currently holding book */
   Employee current_employee;
   bool archived = true;
   PriorityQueue<Employee> waiting_list;

   /* Allows for compare betwen Book and String */
   bool operator==(const Book& rhs) const {
      return name == rhs.name;
   }
};

Book::Book(const string& name) {
   this->name = name;
}

const string& Book::get_name() const {
   return name;
}

void Book::add_employee(const Employee& employee) {
   waiting_list.insert(employee);
}

Employee* Book::circulate(Date date,std::vector<Employee> employees) {
   circulation_start_date = date;
   circulation_last_date = date;
   archived = false;
   waiting_list = PriorityQueue<Employee>(employees);
   current_employee = waiting_list.extract_max();
   current_employee.books_possessed += 1;
   return &current_employee;
}

bool Book::has_waiting() const {
   return waiting_list.is_empty();
}

Employee* Book::pass_on(Date date) {
   Employee last_employee = current_employee;
   last_employee.retaining_time += date - (circulation_last_date);
   last_employee.books_possessed -= 1;

   if(!waiting_list.is_empty()) {
      circulation_last_date = date;
      current_employee = waiting_list.extract_max();
      current_employee.waiting_time += date - circulation_start_date;
      current_employee.books_possessed += 1;
      return &current_employee;
   }
   else {
      circulation_end_date = date;
      archived = true;
   }

   return NULL;
}

Employee* Book::get_current_employee() {
   return &(current_employee);
}

#endif
