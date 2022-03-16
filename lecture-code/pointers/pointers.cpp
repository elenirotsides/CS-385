#include <iostream>
using namespace std;

void pass_by_value(int k) {
	k = 10;
}

void pass_by_pointer(int *k) {
	*k = 10;
}

// & is not the "address of" operator here, it is just a notation
// to indicate that k is passed by reference.
void pass_by_reference(int &k) {
	k = 10;
}

// The array parameter is in fact a pointer but we can use it
// as if it were the name of the array itself.
void display_array(int array[], int length) {
	for(int i = 0; i < length; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

// The array parameter is a pointer and we use pointer arithmetic.
void display_array_ptr(int *array, int length) {
	for(int *p = array; p < array + length; p++) {
		cout << *p << " ";
	}
	cout << endl;
}

int main() {
	int x;  // Type: integer
	x = 5;  // Store the integer 5 into x.
	int *z; // Type: pointer to integer
	z = &x; // Store the address of integer x into z.
	// int x = 5, *z = &x; // Shorter version of the above.
	cout << x << " " << &x << " " << z << " " << &z << endl;
	// Pointer dereference: if z == &x then *z is the same as x itself.
	// Do not confuse the * dereference operator and the * pointer type.
	cout << "*z is: " << *z << endl;
	*z = 7; // Same as: x = 7
	cout << x << " " << &x << " " << z << " " << &z << endl;
	cout << "*z is: " << *z << endl;
	// Do not do this:
	//z += 30000;
	//cout << "*z is: " << *z << endl;
	// Note: when you get a segmentation fault, you can use gdb from
	// the command line to find the source of the problem.

	x = 5;
	// k (see the function definition) is a copy of x; changing k
	// does not change x; this function call is useless.
	pass_by_value(x);
	cout << "x is: " << x << endl;

	// k (see the function definition) is a copy of &x, so k points
	// at x; *k is then the same as x, so changing *k changes x.
	pass_by_pointer(&x);
	cout << "x is: " << x << endl;

	x = 5;
	// k (see the function definition) is an alias (another name) for x,
	// so changing k changes x.  Internally the compiler implements pass
	// by reference by rewriting your code to use a pointer (the way pass
	// by pointer works) so pass by reference is just for the convenience
	// of the C++ programmer because it makes the code easier to write.
	pass_by_reference(x);
	cout << "x is: " << x << endl;

	// Pointer to an anonymous variable-length array which is dynamically
	// allocated on the heap (as variable-length arrays must be):
	int *values = new int[x];
	for(int i = 0; i < x; i++) {
		// Using the pointer as if it were the name of the array:
		values[i] = i;
		// or using pointer arithmetic (which is what the CPU really does):
		*(values + i) = i;
	}
	// Using the pointer as if it were the name of the array:
	display_array(values, x);
	display_array_ptr(values, x);
	// Deleting the array (the pointer is not modified):
	delete [] values;
	return 0;
}
