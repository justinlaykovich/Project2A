#ifndef BOOK_H
#define BOOK_H

class Book {
public:
   string name;
   Date circulation_start_date;
   Date circulation_end_date;
   Date circulation_last_date;
   Employee current_employee;
   bool archived = true;
   PriorityQueue<Employee> waiting_list;
   bool operator==(const Book& rhs) {
      return name == rhs.name;
   }
};

#endif
