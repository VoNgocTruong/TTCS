#include <gl/glut.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.14159265
struct Vertex {
    float x, y, z;
};
void generatePolygon(Vertex* vertices, int sides, float radius) {
    for (int i = 0; i < sides; i++) {
        float angle = 2 * PI * i / sides;
        vertices[i].x = radius * cos(angle);
        vertices[i].y = radius * sin(angle);
        vertices[i].z = 0;
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int sides = 10; 
    float radius = 0.5; 
    Vertex* vertices; 
    size_t size = sides * sizeof(Vertex); 
    vertices = (Vertex*)malloc(size);
    generatePolygon(vertices, sides, radius);
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
    glFlush();
    free(vertices);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A Simple Polygon");
    glutDisplayFunc(display);
    glutMainLoop();

}
