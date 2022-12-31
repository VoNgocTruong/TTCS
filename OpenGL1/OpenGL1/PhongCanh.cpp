#include <windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
int i; double r = 0.2, s = 0.3;
float tx = 10, bx = 10; // tốc độ translate đối tượng
// Bầu trời
void cloud(double x, double y) // vẽ mây
{
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 360; i++)
    {
        x = x + cos((i * 3.14) / 180) * r;
        y = y + sin((i * 3.14) / 180) * r;

        glVertex2d(x, y);
    }
    glEnd();
}
void sun(double x, double y) // vẽ mặt trời
{
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i < 360; i++)
    {
        x = x + cos((i * 3.14) / 180) * s;
        y = y + sin((i * 3.14) / 180) * s;

        glVertex2d(x, y);
    }
    glEnd();
}

void fence(int x) // hàng rào 
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2i(190 - x, 130);
    glVertex2i(190 - x, 70);
    glVertex2i(187 - x, 70);
    glVertex2i(187 - x, 130);
    glVertex2i(190 - x, 130);
    glEnd();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); /*tô màu nền*/
    glOrtho(-210, 210, -220, 310, -210, 310);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Khung hình chữ nhật cho bầu trời
    glColor3ub(135, 206, 250);//màu bầu trời
    glRecti(-200, 300, 200, 100);
    // Đất
    glBegin(GL_POLYGON);
    glColor3ub(0, 100, 0); // màu đất 

    glVertex2i(-200, 100);
    glVertex2i(-100, 180); // đỉnh núi thứ nhất
    glVertex2i(0, 100);
    glVertex2i(50, 70);
    glVertex2i(100, 180); // đỉnh núi thứ hai
    glVertex2i(200, 100);
    glVertex2i(200, -200);
    glVertex2i(-200, -200);
    glVertex2i(-200, 100);
    glEnd();
    // Vẽ mặt trời 
    glColor3ub(242, 216, 121);
    sun(170, 250);
    // Vẽ mây
    glPushMatrix();
    glColor3ub(220, 220, 220);
    glTranslatef(tx, 0, 0); // cho mây di chuyển
    cloud(0, 250);
    cloud(15, 245);
    cloud(10, 240);
    cloud(-2, 243);
    cloud(-80, 250);
    cloud(-95, 245);
    cloud(-90, 240);
    cloud(-90, 243);
    cloud(-75, 243);
    glPopMatrix();
    tx += 0.01;
    if (tx > 200)
        tx = -200;
    // Vẽ hàng rào
    int x = 0;
    for (int i = 0; i < 40; i++)
    {
        fence(x);
        x += 10;
    }
    glColor3ub(255, 255, 255);
    glRecti(-200, 120, 200, 115); // vẽ 3 hình chữ nhật dài làm đường hàng rào ngang
    glRecti(-200, 100, 200, 95);
    glRecti(-200, 85, 200, 80);
    // Vẽ cây
    glColor3ub(139, 69, 19); // màu thân cây
    glRecti(-20, 200, -13, 140);
    glColor3ub(0, 100, 0); // màu lá cây
    sun(-30, 190); // tận dùng vẽ hình của sun ghi đè vẽ cây
    sun(0, 190);
    sun(-10, 210);
    sun(-30, 175);
    sun(-0, 170);


    // Vẽ nhà
    glBegin(GL_POLYGON);  // mái nhà nhà đầu tiên
    glColor3ub(63, 107, 226);
    glVertex2i(-58, 115);
    glVertex2i(-75, 145);
    glVertex2i(-115, 150);
    glVertex2i(-90, 100);
    glVertex2i(-62, 100);
    glVertex2i(-58, 115);

    glVertex2i(-115, 150);
    glVertex2i(-130, 100);
    glVertex2i(-120, 100);
    glVertex2i(-108, 137);
    glVertex2i(-115, 150);
    glEnd();

    glBegin(GL_POLYGON); // vách nhà phía trái
    glColor3ub(130, 130, 115);
    glVertex2i(-108, 137);
    glVertex2i(-120, 100);
    glVertex2i(-120, 45);
    glVertex2i(-90, 40);
    glVertex2i(-90, 100);
    glVertex2i(-108, 137);
    glEnd();

    glBegin(GL_POLYGON);  // vách nhà phía phải
    glColor3ub(232, 231, 214);
    glVertex2i(-90, 40);
    glVertex2i(-60, 45);
    glVertex2i(-60, 100);
    glVertex2i(-90, 100);
    glEnd();

    glColor3ub(63, 107, 226); // cửa
    glRecti(-75, 80, -65, 40);
    glColor3ub(63, 107, 226);// cửa sổ
    glRecti(-110, 90, -100, 70);

    // Nhà thứ 2
    glBegin(GL_POLYGON);  
    glColor3ub(153, 79, 56);
    glVertex2i(0, 140);
    glVertex2i(50, 149);
    glVertex2i(62, 88);
    glVertex2i(-15, 89);
    glVertex2i(0, 140);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3ub(70, 130, 180);
    glVertex2i(-10, 90);
    glVertex2i(-10, 30);
    glVertex2i(40, 25);
    glVertex2i(40, 95);
    glEnd();

    glColor3ub(153, 79, 56);   // Cửa
    glRecti(5, 70, 20, 27);
    // vách
    glBegin(GL_POLYGON);
    glColor3ub(95, 158, 160);
    glVertex2i(40, 25);
    glVertex2i(68, 35);
    glVertex2i(68, 100);
    glVertex2i(50, 148);
    glVertex2i(40, 100);
    glVertex2i(40, 25);
    glEnd();

    glBegin(GL_POLYGON); // mái phải
    glColor3ub(153, 79, 56);
    glVertex2i(49, 150);
    glVertex2i(70, 100);
    glVertex2i(67, 90);
    glVertex2i(46, 140);
    glVertex2i(49, 150);
    glEnd();

    glBegin(GL_POLYGON);  // cửa
    glColor3ub(153, 79, 56);
    glVertex2i(50, 70);
    glVertex2i(60, 73);
    glVertex2i(60, 32);
    glVertex2i(50, 29);
    glVertex2i(50, 70);
    glEnd();

    // Sông 
    glBegin(GL_POLYGON);
    glColor3ub(30, 144, 255);
    glVertex2i(-200, -50);
    glVertex2i(200, -30);
    glColor3ub(0, 0, 128);
    glVertex2i(200, -200);
    glVertex2i(-200, -200);
    glVertex2i(-200, -50);
    glEnd();
    glBegin(GL_POLYGON); // ngăn cách đất và sông
    glColor3ub(128, 128, 0);
    glVertex2i(-200, -45);
    glVertex2i(200, -25);
    glVertex2i(200, -30);
    glVertex2i(-200, -50);
    glVertex2i(-200, -45);
    glEnd();

    // Vẽ thuyền
    glPushMatrix();
    glColor3ub(102, 0, 1);
    glTranslatef(bx, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(-180, -70);
    glVertex2i(-165, -100);
    glVertex2i(-150, -120);
    glVertex2i(-150, -100);
    glVertex2i(-180, -70);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-150, -100);
    glVertex2i(-150, -120);
    glVertex2i(-120, -125);
    glVertex2i(-90, -120);
    glVertex2i(-85, -100);
    glVertex2i(-150, -100);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2i(-85, -100);
    glVertex2i(-90, -120);
    glVertex2i(-75, -105);
    glVertex2i(-60, -70);
    glVertex2i(-85, -100);
    glEnd();
    glPopMatrix();
    bx += 0.03;
    if (bx > 270)
        bx = -200;

    glutPostRedisplay();
    glFlush();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Phong Canh");
    init();
    glutDisplayFunc(display);
    PlaySound(TEXT("sound.wav"), NULL, SND_LOOP | SND_ASYNC);
    glutMainLoop(); 
    return 0;
}