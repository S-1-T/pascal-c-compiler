#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0




int x, y, z;


int gcd(int a, int b) {





if (a % b == 0) {
return b;
}
else {
return gcd(b, a % b);
}

}

int main(int argc, char* argv[]) {

scanf("%d%d", &( x ), &( y ));
printf("%d", gcd(x, y));

	return 0;
}

