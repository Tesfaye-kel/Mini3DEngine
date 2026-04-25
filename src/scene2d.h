#pragma once

// 2D overlay scene (sun, moon, clouds, simple train and birds)
void Scene2D_init();
void Scene2D_setViewport(int w, int h);
void Scene2D_update(float dt);
void Scene2D_render();
void Scene2D_handleKey(unsigned char key);
void Scene2D_setDayMode(bool day);
