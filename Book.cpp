#include"Book.h"

Book::Book(const string& name) {
   this->name = name;
   archived = true;
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

Employee* Book::get_current_employee() {
   return &(current_employee);
}

Employee* Book::get_next_employee(Date date) {
   circulation_last_date = date;

   if(!waiting_list.is_empty()) {
      current_employee = waiting_list.extract_max();
      return &current_employee;
   }

   circulation_end_date = date;
   archived = true;

   return NULL;
}

Employee* Book::circulate(Date date,std::vector<Employee> employees) {
   if(employees.size() == 0)
      throw runtime_error("No employees to circulate to.");

   /* Sets all the circulation parameters */

   circulation_start_date = date;
   circulation_last_date = date;
   archived = false;

   /* Fills the waiting list */
   waiting_list = PriorityQueue<Employee,CompareEmployee>(employees);

   /* Grab first employee */
   current_employee = waiting_list.extract_max();
   return get_current_employee();
}

void Book::update(const Employee& employee) {
   waiting_list.update(employee);
}

void Book::add(const Employee& employee) {
   waiting_list.insert(employee);
}
