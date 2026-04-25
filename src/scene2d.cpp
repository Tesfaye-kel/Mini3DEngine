#include "scene2d.h"
#include <GL/glut.h>
#include <cmath>
#include <Windows.h>
#include <mmsystem.h>

static float angle1 = 30.0f; // train
static float angle3 = 0.5f;  // wheel
static float birdAngle = 0.2f;
static float cloud_X = 0;
static int dayMode = 1;
static int winW = 800, winH = 600;

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void Scene2D_init() {
    // nothing for now
}

void Scene2D_setViewport(int w, int h) { winW = w; winH = h; }

void Scene2D_update(float dt) {
    angle1 += 20.0f * dt;
    angle3 += 60.0f * dt;
    birdAngle += 40.0f * dt;
    cloud_X += 10.0f * dt;
}

void drawSun() {
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(winW - 150, winH - 150, 40, 100);
}

void drawCloud() {
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(100 + cloud_X, winH - 120, 30, 100);
    drawCircle(140 + cloud_X, winH - 120, 25, 100);
    drawCircle(70 + cloud_X, winH - 120, 25, 100);
}

void drawTree2D() {
    glColor3f(0.4, 0.2, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-10, 0);
        glVertex2f(10, 0);
        glVertex2f(10, 60);
        glVertex2f(-10, 60);
    glEnd();
    glColor3f(0.0, 0.5, 0.0);
    drawCircle(0, 80, 40, 100);
}

void drawWheel() {
    glColor3f(0.2, 0.2, 0.2);
    drawCircle(0, 0, 15, 100);
}

void drawTrain2D() {
    glPushMatrix();
    glTranslatef(200 + fmod(angle1, 800.0f), 100, 0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-50, 0);
        glVertex2f(50, 0);
        glVertex2f(50, 60);
        glVertex2f(-50, 60);
    glEnd();

    glPushMatrix();
        glTranslatef(-30, -10, 0);
        glRotatef(angle3, 0, 0, 1);
        drawWheel();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(30, -10, 0);
        glRotatef(angle3, 0, 0, 1);
        drawWheel();
    glPopMatrix();
    glPopMatrix();
}

void Scene2D_render() {
    // Save matrices
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winW, 0, winH);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (dayMode) {
        drawSun();
    }
    drawCloud();
    drawTrain2D();

    // restore
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void Scene2D_handleKey(unsigned char key) {
    switch (key) {
        case 'n': dayMode = 0; break;
        case 'd': dayMode = 1; break;
    }
}

void Scene2D_setDayMode(bool day) { dayMode = day ? 1 : 0; }
