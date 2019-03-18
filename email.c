#include <stdio.h>

int main(char **argv, int argc) {
	int emailAsInt = 0xFACEB00C>>2;
    
	printf("email: %d@facebook.com", emailAsInt);

    return 0;
}
