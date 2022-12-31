#include <stdio.h>
#include <cuda_runtime.h>

__global__ void add(int a, int b, int* c) {
	*c = a + b;
}
int main() {
	int a, b, c;
	int* dev_c;
	printf("Nhap he so a: ");
	scanf("%d", &a);
	printf("Nhap he so b: ");
	scanf("%d", &b);
	cudaMalloc((void**)&dev_c, sizeof(int));
	add << <1, 128 >> > (a, b, dev_c);
	cudaMemcpy(&c, dev_c, sizeof(int), cudaMemcpyDeviceToHost);
	printf("The sum of %d and %d is %d\n", a, b, c);
	cudaFree(dev_c);
	return 0;
}
