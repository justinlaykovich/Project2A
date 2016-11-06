###Using Queues, design a system that allows the circulation fo books to employees.

CS303, Fall 2016
Justin Laykovich

ToDo
1. Keep track of two lists:
   1. Books to be circulated
   2. Archived books
2. Keep track of Employees
3. Circulate a book to employees in the system, prioritized by:
   1. Total waiting time
   2. Total retaining time
4. Make priority queue (implemented with heap: see https://www.youtube.com/watch?v=s-L7wHMOBoU)
   1. Prioritized by _waiting\_time - retaining\_time_
5. Allow passing of book from one employee to next on queue at given date.
   1. Use parallelism to speed up performance.
   2. Following outcomes of passing book:
      1. If last in queue, archive book
      2. Total retaining time for prev employee is adjusted
      3. Total waiting time for next employee is adjusted
      4. If:
         1. More queues for other books and
         2. These queues contain next and prev employee

        Adjust queues to reflect new priorities.
