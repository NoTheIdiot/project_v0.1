// include files
#include <dogemath.h>
#include <stdint.h>
#include <stddef.h>

// power of some number
int math_power(int input, int power) {
	for (int i = 0; i < power; i++) {
		input = input * input;
	}
	return input;
}

int math_sqaure(int input) {
	input = math_power(input, 2);
	return input;
}

int math_root(int input, int root) {
	input = math_power(input, 1/root);
	return input;
}

int math_sqaureroot(int input) {
	input = math_power(input, 1/2);
	return input;
}
