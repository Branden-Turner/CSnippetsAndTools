#include <cstdio>
#include "handler.h"

CrashHandler handler;
int main(int argc, char *argv[]) {

  int zero = 0;
	int divideByZero = 1 / zero;

	return 0;
}
