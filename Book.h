#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
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

#endif
