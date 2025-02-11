//===--- test_masked.c ----------------------------------------------------===//
//
// OpenMP API Version 5.1 Nov 2020
// 
// This test utilizes the masked construct to ensure that a section of code
// only runs on a certain thread. When the filter clause is not present, the
// primary thread runs the structured block.
//
//===----------------------------------------------------------------------===//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "ompvv.h"

#define N 1024

int test_masked() {
  int errors = 0;
  int ct = 0;
  int total = 10;
  int threads = OMPVV_NUM_THREADS_HOST;

#pragma omp parallel num_threads(threads)
while(total > 0){
  #pragma omp masked
  {
    OMPVV_TEST_AND_SET_VERBOSE(errors, omp_get_thread_num() != 0); // primary thread
    ct++;
    total = total-1;
  }
}
  OMPVV_TEST_AND_SET_VERBOSE(errors, ct != 10);
  return errors;
}

int main() {
  OMPVV_TEST_OFFLOADING;
  int errors = 0;
  OMPVV_TEST_AND_SET_VERBOSE(errors, test_masked() != 0);
  OMPVV_REPORT_AND_RETURN(errors);
}
