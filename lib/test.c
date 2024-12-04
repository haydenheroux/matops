#include <stdio.h>

#include "test.h"

void test(const char *pass_message, const char *fail_message, bool passes) {
  if (passes) {
    printf("PASS %s\n", pass_message);
  } else {
    printf("FAIL %s\n", fail_message);
  }
}
