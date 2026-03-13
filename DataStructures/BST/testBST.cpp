#include <iostream>
#include "BST.cpp"
using namespace std;

int main() {
	BST<int> object1;
	object1.insert(42);
	object1.insert(34);
	object1.insert(77);
	object1.insert(9);
	object1.insert(66);

	BST<int> object2(object1);
	object1.~BST();
	object2.print();

	
	cout << "find_target(84) = " << object2.find_target(84) << endl;
	cout << "find_target(43) = " << object2.find_target(43) << endl;
	cout << "find_target(76) = " << object2.find_target(76) << endl;
	cout << "find_target(143) = " << object2.find_target(143) << endl;
	cout << "find_target(45) = " << object2.find_target(45) << endl;
	
	cout << "Tree's height is " <<  object2.get_height() << endl;
	
	object2.~BST();
	return 0;
};
