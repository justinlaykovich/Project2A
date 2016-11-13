#ifndef _BOOK_H_
#define _BOOK_H_

class Book {
public:
   Book(const string&);
   Employee* circulate(Date,std::vector<Employee>);
   Employee* pass_on(Date);
   Employee* get_current_employee();
   const Date& get_last_date() const;
   const string& get_name() const;
   void update(const Employee&);
   void add(const Employee&);

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
   bool archived = true;
   PriorityQueue<Employee> waiting_list;

};

#endif
