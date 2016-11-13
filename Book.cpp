#include"Book.h"

Book::Book(const string& name) {
   this->name = name;
}

const string& Book::get_name() const {
   return name;
}

const Date& Book::get_last_date() const {
   return circulation_last_date;
}

const Date& Book::get_start_date() const {
   return circulation_start_date;
}

Employee* Book::circulate(Date date,std::vector<Employee> employees) {
   circulation_start_date = date;
   circulation_last_date = date;
   archived = false;
   waiting_list = PriorityQueue<Employee>(employees);
   current_employee = waiting_list.extract_max();
   return get_current_employee();
}

Employee* Book::pass_on(Date date) {
   if(!waiting_list.is_empty()) {
      circulation_last_date = date;
      current_employee = waiting_list.extract_max();
      return get_current_employee();
   }

   circulation_end_date = date;
   archived = true;

   return NULL;
}

Employee* Book::get_current_employee() {
   return &(current_employee);
}

void Book::update(const Employee& employee) {
   waiting_list.invalidate(employee);
}

void Book::add(const Employee& employee) {
   waiting_list.insert(employee);
}
