/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

const float CUBE_SIZE = 4.0f;

GLuint _textureId; //The id of the texture
float _angle = 0.0f; //start angle


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				 //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	Image* image = loadBMP("f.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 20.0);
}




void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	
	glTranslatef(0.0, 0.0, -10.0f);
	
	//enable textures
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	float fz = CUBE_SIZE/2;    // front z
	float bz = -CUBE_SIZE/2;    // back z
	
	float lx = -CUBE_SIZE/2;   // left x
	float rx = CUBE_SIZE/2;    // right x
	
	float ty = CUBE_SIZE/2;    // top y
	float by = -CUBE_SIZE/2;   // bottom y

	GLfloat lightColor[] = {0.1f, 0.1f, 0.9f, 1.0f};
    GLfloat lightPos[] = {-2 * CUBE_SIZE, CUBE_SIZE, 20, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	
	//lets rotate
	glRotatef(_angle, 1.0f, 1.0f,0.0f);
	
	glBegin(GL_QUADS);
	//light source

	//front face
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(lx,by,fz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(lx, ty, fz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(rx, ty, fz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(rx, by, fz);
	
	//back face
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(lx,by,bz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(lx, ty, bz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(rx, ty, bz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(rx, by, bz);
	
	
	//right face (mirror textures)
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(rx,by,fz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(rx,ty,fz);
	glTexCoord2f(0.0, 1.0);
	
	glVertex3f(rx,ty,bz);
	glTexCoord2f(0.0, 0.0);
	
	glVertex3f(rx,by,bz);
	
	//left face (180°)
	glNormal3f(-1.0, 0.0, 0.0);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(lx,by,fz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(lx,ty,fz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(lx,ty,bz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(lx,by,bz);
	
	//top face
	glNormal3f(0.0, 1.0, 0.0);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(lx,ty,fz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(rx,ty,fz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(rx,ty,bz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(lx,ty,bz);
	
	//bottom face
	glNormal3f(0.0, -1.0, 0.0);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(lx,by,fz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(rx,by,fz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(rx,by,bz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(lx,by,bz);


	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("Textures - videotutorialsrock.com");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0); //Add a timer
	glutMainLoop();
	return 0;
}