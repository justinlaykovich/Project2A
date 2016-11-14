#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
   Book(const string&);

   Employee* circulate(const Date&,const std::vector<Employee>&);
   Employee* get_next_employee(Date);
   Employee* get_current_employee();
   void update(const Employee&);
   void add(const Employee&);

   const Date& get_last_date() const;
   const Date& get_start_date() const;
   const string& get_name() const;

   /* Allows for compare between books by name */
   bool operator==(const Book& rhs) const {
      return name == rhs.name;
   }
private:
   string name;
   Date circulation_start_date;
   Date circulation_end_date;

   /* Last date simplifies math */
   Date circulation_last_date;

   /* Keeps track of employee currently holding book */
   Employee current_employee;
   bool archived;
   PriorityQueue<Employee,CompareEmployee> waiting_list;
};

#endif
