#include <stdlib.h>
#include <stdio.h>

int main() {
	int dollar;
	printf("Please enter a whole dollar amount: ");
	scanf("%d", &dollar);
	printf("$20 bills: %d\n", (dollar/20));
	dollar -= 20*(dollar/20);
	printf("$10 bills: %d\n", (dollar/10));
	dollar -= 10*(dollar/10);
	printf("$20 bills: %d\n", (dollar/5));
	dollar -= 5*(dollar/5);
	printf("$20 bills: %d\n", (dollar/1));
}
