#include"Library.h"
#include<iostream>
using std::cout;
using std::endl;

void Library::add_book(const string& bookname) {
   Book book;
   book.name = bookname;
   archived_books.push_back(book);
}

void Library::add_employee(const string& employeename) {
   employees.push_back(Employee(employeename,0,0));
}

void Library::circulate_book(const string& bookname, Date date) {
}

void Library::pass_on(const string& bookname, Date) {

}
