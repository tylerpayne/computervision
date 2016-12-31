#include <stdlib.h>
#include <cuda_runtime.h>
#include "cublas_v2.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

int VERBOSITY = 0;

typedef struct Matrix Matrix;

typedef void (*voidFunc)();
typedef float (*getMatrixElementFunc)(Matrix*, int,int);
typedef float* (*getMatrixRegionFunc)(Matrix*, int,int,int,int);
typedef void (*setMatrixElementFunc)(Matrix*, int, int, float);
typedef void (*setMatrixRegionFunc)(Matrix*, int,int,int,int, float*);


struct Matrix
{
  int* shape;
  void* nativePtr;
  void* devicePtr;
  int isHostSide;
  cublasOperation_t T;
  voidFunc transpose;
  getMatrixElementFunc getElement;
  getMatrixRegionFunc getRegion;
  setMatrixElementFunc setElement;
  setMatrixRegionFunc setRegion;
};

static int IDX2C(int i, int j, int td)
{
  return (i*td)+j;
}