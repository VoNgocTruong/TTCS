#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gl/glut.h>


struct GLintPoint
{
	GLint x, y;
};
struct ColorRec
{
	GLfloat r, g, b;
};
ColorRec ListColor[5];
GLintPoint ListStart[4];
int randomColor(int min, int max)
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL));
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}
void Rectangle(GLintPoint list[4]) {
	ListColor[0].r = 0; ListColor[0].g = 1; ListColor[0].b = 0;
	ListColor[1].r = 0; ListColor[1].g = 0; ListColor[1].b = 1;
	ListColor[2].r = 0; ListColor[2].g = 0.5; ListColor[2].b = 0.5;
	ListColor[3].r = 2; ListColor[3].g = 0.5; ListColor[3].b = 1;
	ListColor[4].r = 0.5; ListColor[4].g = 0.5; ListColor[4].b = 0.5;
	int num = randomColor(0, 4);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glColor3f(ListColor[num].r, ListColor[num].g, ListColor[num].b);
		glVertex2i(list[i].x, list[i].y);
	}
	glEnd();
	glFlush();
}
void resetRetangle() { 
	Rectangle(ListStart);
}
void Mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		/*hcn kich thuooc la 100x50*/
		ListStart[0].x = x; ListStart[0].y = y;
		ListStart[1].x = ListStart[0].x + 100; ListStart[1].y = ListStart[0].y;
		ListStart[2].x = ListStart[1].x; ListStart[2].y = ListStart[1].y + 50;
		ListStart[3].x = ListStart[0].x; ListStart[3].y = ListStart[0].y + 50;
		Rectangle(ListStart);
	}
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void Init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); /*tô màu nền*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 700, 700, 0.0);
	
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Draw Rec");
	
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	Init();
	glutMainLoop();
	return 0;
}