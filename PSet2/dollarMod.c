#include <stdlib.h>
#include <stdio.h>

void pay_amount(int dollar, int *twenties, int *tens, int *fives, int *ones) {
	*twenties = dollar/20;
	dollar -= 20*(*twenties);
	*tens = dollar/10;
	dollar -= 10*(*tens);
	*fives = dollar/5;
	dollar -= 5*(*fives);
	*ones = dollar/1;
}

int main() {
	int dollar, twenties, tens, fives, ones;
	printf("Please enter a whole dollar amount: ");
	scanf("%d", &dollar);
	pay_amount(dollar, &twenties, &tens, &fives, &ones);
	printf("$20 bills: %d\n", twenties);
	printf("$10 bills: %d\n", tens);
	printf("$20 bills: %d\n", fives);
	printf("$20 bills: %d\n", ones);
	return 0;
}
