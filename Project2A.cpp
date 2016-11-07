#include<iostream>
#include"Library.cpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
   Employee sam("Sam",10,1);
   Employee tom("Tom",1,10);

   if(sam < tom)
      cout << "Sam is less than tom." << endl;
   else
      cout << "Sam is not less than tom." << endl;

   Library library;
   library.add_book("Software Engineering");
   library.add_book("Chemistry");

   library.add_employee("Adam");
   library.add_employee("Sam");
   library.add_employee("Ann");

   library.circulate_book("Chemistry", Date(2015, 3, 1, DateFormat::US));
   library.circulate_book("Software Engineering", Date(2015, 4 , 1, DateFormat::US));

   library.pass_on("Chemistry", Date(2015, 3, 15, DateFormat::US));
   library.pass_on("Chemistry", Date(2015, 3, 17, DateFormat::US));
   library.pass_on("Chemistry", Date(2015, 3, 19, DateFormat::US));

   library.pass_on("Software Engineering", Date(2015, 4, 5, DateFormat::US));
   library.pass_on("Software Engineering", Date(2015, 4, 10, DateFormat::US));
   library.pass_on("Software Engineering", Date(2015, 4, 15, DateFormat::US));
}
