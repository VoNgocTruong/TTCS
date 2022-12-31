#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

void my_display();

// #init()
// Prepare openGL for our art
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);

    // Smooth shading creates gradiants
    glShadeModel(GL_SMOOTH);

    glLoadIdentity();

    // Set the 2D plot limits
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("The Dark Side of the Nyan");
    glutDisplayFunc(my_display);
    init();
    glutMainLoop();
    return 0;
}


//# Painting function
// This is where all the drawing happens.
void my_display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // #The space sky
    // Draw two rectangles that cover the frame. Both rectangles have use Smooth shading to make a gradient. y is horizontal line where the two meet so that we have an illusion to two gradients

    float y = -0.3;
    //Draw the top dark deep space
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0, 0.07843, 0.16078);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(-1, .5);
    glColor3f(0, 0.2, 0.4);
    glVertex2f(1, y);
    glVertex2f(-1, y);
    glEnd();

    //Draw the bottom red glow  
    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.4);
    glVertex2f(-1, y);
    glVertex2f(1, y);
    glColor3f(1, 0.1607, 0.32156);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

    // #Draw the stars
    //  Randomly draw white points on the previously painted sky.
    glColor3f(1, 1, 1);
    float i;
    float sx, sy;
    int numStars = 400;

    glBegin(GL_POINTS);
    for (i = 0; i <= numStars; i++) {
        sx = (2 * (float)rand() / (float)RAND_MAX) - 1;
        sy = (2 * (float)rand() / (float)RAND_MAX) - 1;
        glVertex2f(sx, sy);
    }
    glEnd();

    //#Draw triangle prism
    // Draw a triangle with first corner at (px,py). We want an equilateral triangle but our coordinate system is skewed 5:8, this is why we use `r` scaling factor for the rest of the program.
    float px = -0.2;
    float py = -0.5;
    float side_length = -0.7;
    float r = 1.625; // sculling constant for a 500:800 
    float sectx = px + side_length;
    float secty = py;
    float topx = px + (side_length / 2.0);
    float topy = (py + side_length * -0.866 * r);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(px, py);
    glVertex2f(px + side_length, py); // Base line
    glVertex2f(px + (side_length / 2.0), py + side_length * -0.866 * r);
    glEnd();

    // #Draw light ray hitting the prism
    float rx = -1;
    float ry = 0.0;
    float hit = 0.7; // Where to hit [0,1]
    int width = 10;

    // `cept` is computing where the light ray will hit the prism
    float ceptx = sectx - (hit * (side_length / 2.0));
    float cepty = -1.73205 * r * hit * (side_length / 2.0) + py;

    // These are the parameters for the spread of the inside refraction
    hit = 0.4; // Where to on the right side, [0,1]
    float exitxU = (px + side_length / 2.0) - hit * side_length / 2.0;
    float exityU = (-1.73205 * r * (1 - hit) * (side_length / 2.0)) + py;
    hit = 0.1;  // Try changing this number
    float exitxL = (px + side_length / 2.0) - hit * side_length / 2.0;
    float exityL = (-1.73205 * r * (1 - hit) * (side_length / 2.0)) + py;

    // Draw the line with larger thickness then reset line thickness back to 1.
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(rx, ry);
    glVertex2f(ceptx, cepty);
    glLineWidth(1);
    glEnd();

    // Draw the inside prism ray
    glBegin(GL_TRIANGLES);
    glVertex2f(ceptx, cepty);
    glVertex2f(exitxU, exityU);
    glVertex2f(exitxL, exityL);
    glEnd();


    // #Draw the rainbow tail
    // The rainbow is made of 50 small rectangles that have rainbow shading. They are painted one after the other but the y coordinate is mapped to a sine wave. The height of the rainbow slices are based on the refraction triangle boundaries in the prism.
    float dx = exitxL;
    float dy = exityL;
    float w = 0.014;
    float step = (exityL - exityU) / 5.0;
    for (i = 0; i < 50; i++)
    {
        glBegin(GL_QUAD_STRIP);

        glColor3f(1, 0, 0);
        glVertex2f(dx, dy);
        glVertex2f(dx + w, dy);

        glColor3f(1, 0.6, 0);
        glVertex2f(dx, dy - step);
        glVertex2f(dx + w, dy - step);

        glColor3f(1, 1, 0);
        glVertex2f(dx, dy - step * 2);
        glVertex2f(dx + w, dy - step * 2);

        glColor3f(0.2, 1, 0);
        glVertex2f(dx, dy - step * 3);
        glVertex2f(dx + w, dy - step * 3);

        glColor3f(0, 0.6, 1);
        glVertex2f(dx, dy - step * 4);
        glVertex2f(dx + w, dy - step * 4);

        glColor3f(0.4, 0.2, 1);
        glVertex2f(dx, dy - step * 5);
        glVertex2f(dx + w, dy - step * 5);
        glEnd();

        dx += w;
        dy += 0.01 * sin(i * 3.14 / 5.0);

    }

    //# Paws and Tail

    // These parameters are for body but we need to compute them first
    float bx = dx;
    float by = dy;
    float bh = step * 5.0;//17:21
    float bw = bh * 0.80952;
    float round = 0.024;


    //Draw tail
    float th = .05;
    float ts = .01;
    float ty = by - bh * 0.8;

    glColor3f(.6, .6, .6);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(bx, ty);
    glVertex2f(bx, ty + th);
    ty += ts * 2;
    glVertex2f(bx - ts, ty);
    glVertex2f(bx - ts, ty + th);
    ty += ts * 1;
    glVertex2f(bx - ts * 2, ty);
    glVertex2f(bx - ts * 2, ty + th);
    ty += ts * 2;
    glVertex2f(bx - ts * 3, ty);
    glVertex2f(bx - ts * 3, ty + th);
    ty += ts * 3;
    glVertex2f(bx - ts * 4, ty);
    glVertex2f(bx - ts * 4, ty + th);

    glEnd();

    //#Draw the 4 paws
    // The feet are drawn with triangle fans that acts like ovals, we compute them with the circle formula (r*cos(i),r*sin(i))
    float fr = .02;
    float fx = bx + bw;
    float fy = by - bh - fr;

    /*
    glBegin(GL_TRIANGLE_FAN);
    for(i=0;i<=180;i=i+6*3.14)
      glVertex2f(fx+fr*cos(i),fy+fr*sin(i));
    glEnd();
    */

    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx -= bw;
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx + bw * .8;
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx * 0.6;
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();


    // # Poptart body
    // ##Black border
    // This is black and will act as a border when overlapped with the crust layer. It is mostly a rectangle with the corners clipped.
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();

    //##Crust
    // This is the same shape but smaller then the previously layed black shape and centered.
    float scale = 0.95;
    round *= scale;
    bx += (bw - bw * scale) / 2.0;
    by -= (bh - bh * scale) / 2.0;
    bh *= scale;
    bw *= scale;

    glBegin(GL_POLYGON);
    glColor3f(1, 0.8, 0.6);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();


    // ##Frosting
    // A smaller, centered pink rectangle
    scale = 0.86;
    round *= scale;
    bx += (bw - bw * scale) / 2.0;
    by -= (bh - bh * scale) / 2.0;
    bh *= scale;
    bw *= scale;

    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 1);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();

    //Draw sprinkles as random points  
    glBegin(GL_POINTS);
    for (i = 0; i < 1000; i++)
    {
        glColor3f(1, 0.2, 0.6);
        sx = (bw * (float)rand() / (float)RAND_MAX) + bx;
        sy = (-bh * (float)rand() / (float)RAND_MAX) + by;
        glVertex2f(sx, sy);
    }
    glEnd();


    //#Draw face
    // Every thing will be drawn with respect to the center of the head at (fx,fy)
    fx = bx + bw;
    fy = by - bh * 0.8;
    fr = 0.07;

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    //Draw the ears which are triangles
    float ew = fr * 0.9;
    glBegin(GL_TRIANGLES);
    //Right ear
    glVertex2f(fx, fy);
    glVertex2f(fx + ew, fy);
    glVertex2f(fx + ew, fy + ew * 2);
    //Left ear
    glVertex2f(fx, fy);
    glVertex2f(fx - ew, fy);
    glVertex2f(fx - ew, fy + ew * 2);
    glEnd();

    //Draw eyes
    // Eyes are black circles with 1/4th size white circles in the upper left corner as gleam
    fr = 0.01;
    fx -= fr * 2.5;

    // Left eye
    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i) * r);
    }
    glEnd();

    fr = .0025;

    // Gleam
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);

    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + fr * 2 + fr * sin(i) * r);
    }
    glEnd();

    // Right eye
    fr = .01;
    fx += fr * 4.5;

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
    {
        glVertex2f(fx - fr * cos(i), fy + fr * sin(i) * r);
    }
    glEnd();

    //Gleam
    fr = .0025;
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + fr * 2 + fr * sin(i) * r);
    glEnd();

    //Draw nose
    fr = 0.005; // radius of nose
    fx = bx + bw;
    fy *= 0.9;

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
        glVertex2f(fx - fr * cos(i), fy + fr * sin(i) * r);
    glEnd();

    // #Draw mouth
    fy *= 0.8;
    float mw = 5; // Mouth width measured in nose widths
    float mh = 2; // Mouth height measured in nose widths

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(fx - fr * mw, fy + fr * mh);
    glVertex2f(fx - fr * mw, fy);
    glVertex2f(fx, fy);
    glVertex2f(fx, fy + fr * mh);
    glVertex2f(fx, fy);
    glVertex2f(fx + fr * mw, fy);
    glVertex2f(fx + fr * mw, fy + fr * mh);
    glEnd();

    //Draw cheeks
    // Pink circles
    fr *= 1.4;
    glColor3f(1, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
        glVertex2f(fx + mw * 1.2 * fr - fr * cos(i), fy + fr * sin(i) * r + fr * mh);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 200; i += 6)
        glVertex2f(fx - mw * 1.2 * fr - fr * cos(i), fy + fr * sin(i) * r + fr * mh);
    glEnd();

    glFlush();

}
