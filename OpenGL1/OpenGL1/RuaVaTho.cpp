#include <windows.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
double r = 0.2;
float rb = 70, counter = 0, text1 = 5, text2 = 5;
float ts = 0;
int text = 0;
void display1();
void display2();
void reshape(int w, int h);
void keySelect(unsigned char key, int x, int y);
void init(void);
void circle(double x, double y, double s);
void halfCircle(double x, double y, double s);
void drawString(float x, float y, float z,const char *string) // dùng để viết văn bản
{
    const char *ct;
    glRasterPos3f(x, y, z);

    for (ct = string; *ct != '\0'; ct++)
    {
        glColor3f(0.0, 0.0, 0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *ct);
    }
}
void TextStart()
{
    char text[120];
    sprintf(text, "CO TICH RUA VA THO");
    glRasterPos2f(-20, 12);
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] == ' ')
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
            glRasterPos2f(-32, 02);
        }
        else glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    sprintf(text, "  CREATE BY TRUONG, BAM NUT C DE TIEP TUC");
    glRasterPos2f(-100, 0);
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] == ' ')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
            glRasterPos2f(-35, 0);
        }
        else glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void TextEnd()
{
    char text[120];
    sprintf(text, "RUA DA THANG !!");
    glRasterPos2f(-20, 12);
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] == ' ')
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
            glRasterPos2f(-32, 02);
        }
        else glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    sprintf(text, "  VI THO DA CHU QUAN, NEN RUA DA THANG");
    glRasterPos2f(-100, 0);
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ' && text[i + 1] == ' ')
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
            glRasterPos2f(-35, 0);
        }
        else glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}
void circle(double x, double y, double s) // dùng để vẽ hình tròn
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++)
    {
        x = x + cos((i * 3.14) / 180) * s;
        y = y + sin((i * 3.14) / 180) * s;

        glVertex2d(x, y);
    }
    glEnd();
}
void halfCircle(double x, double y, double s)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 180; i++)
    {
        x = x + cos((i * 3.14) / 180) * s;
        y = y + sin((i * 3.14) / 180) * s;

        glVertex2d(x, y);
    }
    glEnd();
}
void display1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -20);
    // sky
    glBegin(GL_QUADS);
    glColor3f(0.61, 0.78, 0.98);
    glVertex2f(-120, 70);
    glVertex2f(120, 70);
    glColor3f(1, 1, 1);
    glVertex2f(120, 10);
    glVertex2f(-120, 10);
    glEnd();
    // dirt
    
    glColor3f(0.54, 1.00, 0.51);
    glRecti(-120, 30, 120, 10);
    glutPostRedisplay();
    // mountain
    glBegin(GL_TRIANGLES);
    glColor3f(0.43, 0.73, 0.16); glVertex2f(-110, 25);
    glColor3f(0.54, 1.00, 0.52); glVertex2f(-70, 50);
    glColor3f(0.43, 0.73, 0.16); glVertex2f(-40, 25);

    glColor3f(0.43, 0.73, 0.16); glVertex2f(-60, 20);
    glColor3f(0.39, 0.89, 0.34); glVertex2f(-40, 40);
    glColor3f(0.43, 0.73, 0.16); glVertex2f(-20, 20);

    glColor3f(0.43, 0.73, 0.16); glVertex2f(110, 20);
    glColor3f(0.39, 0.89, 0.34); glVertex2f(85, 40);
    glColor3f(0.43, 0.73, 0.16); glVertex2f(70, 20);  
    glEnd();
    // tree 1
    glColor3f(0.44, 0.22, 0.00);
    glRecti(-15, 32, -13, 12);
    glBegin(GL_TRIANGLES);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(-22, 29);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(-13.5, 45);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(-5.8, 29);

    glVertex2f(-22, 34);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(-13.5, 50);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(-5.8, 34);
    glEnd();

    // tree 2
    glColor3f(0.44, 0.22, 0.00);
    glRecti(8, 35, 10, 15);
    glBegin(GL_TRIANGLES);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(0, 31);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(9.5, 47);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(17.8, 31);

    glVertex2f(0, 36);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(9.5, 52);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(17.8, 36);
    glEnd();

    // tree 3
    glColor3f(0.44, 0.22, 0.00);
    glRecti(40, 37, 42, 17);
    glBegin(GL_TRIANGLES);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(32, 31);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(41.5, 47);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(49.8, 31);

    glVertex2f(32, 36);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(41.5, 52);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(49.8, 36);

    glVertex2f(32, 41);
    glColor3f(0.39, 0.89, 0.34);
    glVertex2f(41.5, 57);
    glColor3f(0.00, 0.51, 0.00);
    glVertex2f(49.8, 41);
    glEnd();

    // sun
    glColor3f(0.99, 1.00, 0.01);
    circle(90, 48, 0.1);
    // race
    glColor3f(0.70, 0.70, 0.70);
    glRecti(-120, 0, 120, -55);
    int x1 = -120, x2 = -110;
    for (int i = 0; i <= 25; i++)
    {
        if (i % 2 == 0)
        {
            glColor3f(1, 1, 1);
            glRecti(x1, 10, x2, 0);
            glRecti(x1, -65, x2, -55);
            glRecti(x1, -20, x2, -23);
        }
        x1 += 10;
        x2 += 10;
    }
    if (counter <= 244)
    {
        glRecti(20, 0, 24, -55);
    }
    else
    {
        glRecti(20, 0, 24, 0);
    }
    if (counter >= 244)
    {
        glColor3f(0.53, 0.24, 0.18);
        glRecti(-80, 0, -85, -55);
    }
    // turtle
    glPushMatrix();
    if (counter >= 75 && counter <= 244)
    {
        glTranslatef(ts, 0, 0);
        ts -= 0.01;
    }
    if (counter >= 244)
    {
        if (counter >= 244 && counter <= 245)
        {
            ts = 40;
        }
        glTranslatef(ts, 0, 0);
        ts -= 0.01;
    }
    glColor3f(0.39, 0.89, 0.34);
    glRotatef(90, 0, 0,1);
    halfCircle(-35, -45, 0.1);
    // leg
    glRotatef(-90, 0, 0, 1);
    glColor3f(0.50, 0.50, 0.50);
    glRecti(35, -35, 37, -38);
    glRecti(41, -35, 43, -38);
    // head
    circle(33, -35, 0.04);
    //eye
    glColor3f(0, 0, 0);
    circle(32, -33, 0.01);
    glPopMatrix();
    //rabbit
    //
    glPushMatrix();
    if (counter >= 0 && counter <= 70)
    {
        glTranslatef(rb, 0, 0);
        rb -= 0.03;
        if (rb <= 0)
        {
            rb = 0;
        }
    }
    if (counter >= 150)
    {
        glTranslatef(rb, 0, 0);
        rb -= 0.02;
    }
    if (counter >= 244)
    {
        rb = 0;
        glTranslatef(rb, 20, 0);
        drawString(28, 0.8, 0, "Z Z");
        drawString(25, 3, 0, "Z Z");
    }
    glTranslatef(rb, 0, 0);
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(33,-5);
    glVertex2f(38, -5);
    glVertex2f(40, -8);
    glVertex2f(40, -10);
    glVertex2f(35, -10);
    glEnd();
    // head
    circle(34, -7, 0.04);
    //eye
    glColor3f(0, 0, 0);
    circle(33, -5, 0.01);
    // leg
    glColor3f(1, 1, 1);
    glRecti(35, -10, 37, -11);
    glRecti(38, -10, 39, -11);
    // tall
    glColor3f(1, 1, 1);
    glRecti(35, -1, 36, -5);
    glPopMatrix();

    counter += 0.01;
    glColor3f(0, 0, 0);
    if (rb <= 0)
    {
        glPushMatrix();
        glTranslatef(text1,0,0);
        drawString(text1, 0, 0, "Cham nhu cau ma cung doi tap chay a?");
        drawString(text1, -30, 0, "Anh dung treu toi. Anh voi toi chay dua xem?");
        glPopMatrix();
        if (counter >= 50)
        {
            text1 = 120;  
            drawString(text2, 0, 0, "Haha cau dam? Toi chap cau nua duong do.");
            if (counter >= 70)
            {
                text2 = 120;
            }
        }
    }

    if (counter >= 400)
    {
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("RUA VA THO");
        init();
        glutReshapeFunc(reshape);
        glutDisplayFunc(display2);
        glutKeyboardFunc(keySelect);
        PlaySound(TEXT("victory.wav"), NULL, SND_LOOP | SND_ASYNC);
        glutMainLoop();
    }
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
void display2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -20);
    TextEnd();
    glFlush();
    glutSwapBuffers();

}
void keySelect(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        glutDestroyWindow(1);
        glutInitWindowSize(1240, 750);
        glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
        glutCreateWindow("RUA VA THO");
        init();
        glutReshapeFunc(reshape);
        glutDisplayFunc(display1);
        glutKeyboardFunc(keySelect);
        glutMainLoop();
        break;
    case 'e':
        exit(-1);
        break;
    }
}
void reshape(int w, int h)
{
    float aspectRatio = (float)w / (float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(145, aspectRatio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}
void init(void)
{
    glClearColor(0.92, 0.30, 0.22, 0.0f);
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -20);
    TextStart();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1240, 750);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1240) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 750) / 2);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("RUA VA THO");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keySelect);
    PlaySound(TEXT("sound.wav"), NULL, SND_LOOP | SND_ASYNC);
    glutMainLoop();
    return 0;
}