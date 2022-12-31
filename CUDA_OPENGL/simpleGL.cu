#include <gl/glut.h>
#include <helper_math.h>
#include <cuda_runtime.h>
#include <stdlib.h>
#define PI 3.14159265
struct Vertex {
    float x, y, z;
};
__global__ void polygonKernel(Vertex* vertices, int sides, float radius) {
    for (int i = 0; i < sides; i++) {
        float angle = 2 * PI * i / sides;
        vertices[i].x = radius * cos(angle);
        vertices[i].y = radius * sin(angle);
        vertices[i].z = 0;
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Vertex* opengl_buffer;
    Vertex* cuda_device_buffer;
    int sides = 10; 
    float radius = 0.5; 
    size_t size = sides * sizeof(Vertex);
    opengl_buffer = (Vertex*)malloc(size);
    cudaMalloc((void**)&cuda_device_buffer, size);
    polygonKernel << <1, 1 >> > (cuda_device_buffer, sides, radius);
    cudaMemcpy(opengl_buffer, cuda_device_buffer, sides * sizeof(Vertex), cudaMemcpyDeviceToHost);
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        glVertex3f(opengl_buffer[i].x, opengl_buffer[i].y, opengl_buffer[i].z);
    }
    glEnd();
    glFlush();
    cudaFree(cuda_device_buffer);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A Simple Polygon");
    glutDisplayFunc(display);
    cudaSetDevice(0);
    glutMainLoop();
 
}
