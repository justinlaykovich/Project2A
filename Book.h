#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
   Book(const string&);
   string get_name();
   Employee circulate(Date,std::vector<Employee>);
   Employee pass_on(Date);
   Employee get_current_employee();
   void end_circulation(Date);
   bool waiting_list_empty();
   int time_since_last(Date);
   Employee current_employee;
   bool operator==(const Book& rhs) {
      return name == rhs.name;
   }
private:
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   Date circulation_last_date;
   PriorityQueue<Employee> waiting_list;
};

Book::Book(const string& name)
{
   this->name = name;
   archived = true;
}

string Book::get_name() {
   return name;
}

Employee Book::circulate(Date date, std::vector<Employee> employees) {
   waiting_list = PriorityQueue<Employee>(employees);
   circulation_start_date = date;
   circulation_last_date = date;
   archived = false;
   return pass_on(date);
}

void Book::end_circulation(Date date) {
   circulation_last_date = date;
   circulation_end_date = date;
   archived = true;
}

Employee pass_on(Date date) {
   current_employee = waiting_list.extract_max();
   circulation_last_date = date;
   current_employee.books_possessed += 1;
   return current_employee;
}

bool Book::waiting_list_empty() {
   return waiting_list.is_empty();
}

int Book::time_since_last(Date date) {
   return date - circulation_last_date;
}

Employee Book::get_current_employee() {
   return current_employee;
}


#endif
