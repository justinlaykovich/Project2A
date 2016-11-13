#include"Book.h"

Employee* Book::start_circulation(Date date,std::vector<Employee> employees) {
   if(waiting_list.is_empty())
      return NULL;

   circulation_start_date = date;
   circulation_last_date = date;
   archived = false;
   waiting_list = PriorityQueue<Employee>(employees);

   current_employee = waiting_list.extract_max();
   return &(current_employee);
}

Employee* Book::pass_on(Date date) {
   circulation_last_date = date;
   if(waiting_list.is_empty()) {
      circulation_end_date = date;
      archived = true;
      return NULL;
   }

   current_employee = waiting_list.extract_max();
   return &(current_employee);
}
