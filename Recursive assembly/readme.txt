This is using the LC-3 version of assembly.
The function is as follows:
#include <stdio.h>
#include <string.h>
int eval(const char *str, int len) {
	int i = 0;
	int left;
	int right;
	while(i < len) {
		if(*(str + i) == '+') {
			left = eval(str, i);
			right = eval(str + i + 1, len - i - 1);
			return left + right;
		}
		i++;
	}
	i = 0;
	while(i < len) {
		if(*(str + i) == '*') {
			left = eval(str, i);
			right = eval(str + i + 1, len - i - 1);
			return left * right;
		}
		i++;
	}
	return *str - '0';
}
int main(int argc, char **argv) {
	int x = eval(argv[1], strlen(argv[1]));
	printf("%d\n", x);
	return 0;
}