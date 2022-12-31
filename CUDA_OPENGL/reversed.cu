#include <stdio.h>
#include <cuda_runtime.h>

__global__ void reverseNumber(int n, int* reversed) {
	*reversed = 0;
	while (n != 0)
	{
		*reversed = *reversed * 10 + n % 10;
		n /= 10;
	}
}
int main() {
	int n, reversed;
	int* dev_reversed;
	printf("Nhap he so a: ");
	scanf("%d", &n);
	cudaMalloc((void**)&dev_reversed, sizeof(int));
	reverseNumber << <1, 1 >> > (n, dev_reversed);
	cudaMemcpy(&n, dev_reversed, sizeof(int), cudaMemcpyDeviceToHost);
	printf("So dao nguoc la: %d\n", reversed);
	cudaFree(dev_reversed);
	return 0;
}
