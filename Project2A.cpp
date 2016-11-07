#include"heap.cpp"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
   MaxHeap<int> heap({10,3,4,20,9,2,1});

   heap.insert(30);
   int size = heap.get_size();
   for(int i = 0; i < size; i++)
      cout << heap.extract_max() << endl;

}
