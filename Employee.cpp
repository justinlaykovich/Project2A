#include"Employee.h"

Employee::Employee(const string& name = "") {

   this->name = name;
   waiting_time = 0;
   retaining_time = 0;
   books_possessed = 0;
}

const string& Employee::get_name() const {

   return name;
}

const int& Employee::get_waiting_time() const {

   return waiting_time;
}

const int& Employee::get_retaining_time() const {

   return retaining_time;
}

void Employee::receive_book(const int& waiting_time) {

   this->books_possessed += 1;
   this->waiting_time += waiting_time;
}

void Employee::pass_on(const int& retaining_time) {

   this->books_possessed -= 1;
   this->retaining_time += retaining_time;
}

