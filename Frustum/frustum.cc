#include<stdio.h>
#include<GL/glut.h>
#include <cmath>

//roatation variable
GLfloat T = 0;
int s = 0;
int c=0;

void Spin() {
  // in case you want to see it rotate about z axis uncomment line
  T= T-.75;
  if(T>360)
    T=0;
  glutPostRedisplay();
}

//frustum coordinates as 8X3 matrix
GLfloat V[8][3]=
    {
    {-0.5,-0.5,-0.5},
    {-0.5,0.5,-0.5},
    {0.5,-0.5,-0.5},
    {0.5,0.5,-0.5},
    {-0.25,-0.25,0.5},
    {-0.25,0.25,0.5},
    {0.25,-0.25,0.5},
    {0.25,0.25,0.5}
    };
//triangle coordinates as 3X3 mtrix
GLfloat E[3][3]=
{
    {-.1,-.1,0},
    {-.1,.1,0},
    {.1,.1,0}
};

//roatation variable
const double Pi =3.141592;
double Thetax =0;
double Thetay =0;
double Thetaz =0;


void MyInit(void) {
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3f(1.0,0.0,0.0);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,100);// for orthogonal projection

  glMatrixMode(GL_MODELVIEW);
}

void sizeUp(GLfloat V[][3], GLfloat E[][3]){
  for(int i=0; i<8; i++) {
    for(int j=0; j<3; j++) {
      V[i][j]=  V[i][j] * 1.10;
    }
  }
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      E[i][j]=  E[i][j] * 1.10;
    }
  }
  glutPostRedisplay();
}
void sizeDown(GLfloat V[][3], GLfloat E[][3]){
  for(int i=0; i<8; i++) {
    for(int j=0; j<3; j++) {
      V[i][j]=  V[i][j]/1.10;
    }
  }
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      E[i][j]=  E[i][j]/1.10;
    }
  }
  glutPostRedisplay();
}

void translateX(GLfloat V[][3], int key){
//translates along x axis
  if(key ==1) //right key
  {
   for(int i=0; i<8; i++) {
      V[i][0]=  V[i][0] +0.1;
   }
  }
  else {//left key
    for(int i=0; i<8; i++) {
       V[i][0]=  V[i][0] - 0.1;
    }
  }
  glutPostRedisplay();
}

void translateZ(GLfloat V[][3], int key){
//translates along y axis
  if(key ==1) //right key
  {
   for(int i=0; i<8; i++) {
      V[i][2]=  V[i][2] +0.1;
   }
  }
  else {//left key
    for(int i=0; i<8; i++) {
       V[i][2]=  V[i][2] - 0.1;
    }
  }
  glutPostRedisplay();
}

void rotate(GLfloat E[][3], int key, double Thetax, double Thetay, double Thetaz ) {
  int i=0;
  double tx = Thetax*Pi/180.0;
  double ty = Thetay*Pi/180.0;
  double tz = Thetaz*Pi/180.0;
  if(key ==1) {//rotate along x axis
    for(i=0; i<3 ; i++) {
      E[i][1]=  (E[i][1]*cos(tx)) - (E[i][2]*sin(tx));
      E[i][2]= (E[i][1]*sin(tx)) + (E[i][2]*cos(tx));
    }
  }
  else if (key == 2)
  {
    for(i=0; i<3 ; i++) {
      E[i][0]=  (E[i][0]*cos(ty)) + (E[i][2]*sin(ty));
      E[i][2]= -(E[i][0]*sin(ty)) + (E[i][2]*cos(ty));
    }
  }
  else {
    for(i=0; i<3 ; i++) {
      E[i][0]=  (E[i][0]*cos(tz)) - (E[i][1]*sin(tz));
      E[i][1]= (E[i][0]*sin(tz)) + (E[i][1]*cos(tz));

    }
  }
  glutPostRedisplay();
}

void updateProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

  if(c%2==0)
    glOrtho(-1,1,-1,1,-1,100);// for orthogonal projection
  else
    glFrustum(-1,1,-1,1,-1,100);// for perspective view

  glMatrixMode(GL_MODELVIEW);
  glutPostRedisplay();
}

void NKey(unsigned char ch, int x, int y) {
  switch(ch) {
    case 'C':
    case 'c':
      c++;
      updateProjection();
      break;
    case 'R':
    case 'r':
      s=1;
      glutPostRedisplay();
      break;
    case 'S':
    case 's':
      s=0;
      glutPostRedisplay();
      break;
  }
}

void Key(int ch, int x, int y) {
  //defines keys for necessary operations
  switch (ch){
    case GLUT_KEY_UP:
      translateZ(V,1);
      break;
    case GLUT_KEY_PAGE_UP:
      sizeUp(V,E);
      break;
    case GLUT_KEY_DOWN:
      translateZ(V,2);
      break;
    case GLUT_KEY_PAGE_DOWN:
      sizeDown(V,E);
      break;
    case GLUT_KEY_HOME:
      rotate(E,1,Thetax++,Thetay, Thetaz);
      break;
    case GLUT_KEY_END:
      rotate(E,2,Thetax, Thetay++, Thetaz);
      break;
    case GLUT_KEY_INSERT:
      rotate(E,3,Thetax, Thetay, Thetaz++);
      break;
    case GLUT_KEY_RIGHT:
      translateX(V,1);
      break;
    case GLUT_KEY_LEFT:
      translateX(V,2);
      break;
  }
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
//creates a quadrilateral face with given points
  glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
  glEnd();
}

void Triangle (GLfloat A[], GLfloat B[], GLfloat C[]) {
  // creates the triangle with the given points
  glColor3f(0,0,0);
  glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
  glEnd();
}

void Frustum (GLfloat V0[],GLfloat V1[],GLfloat V2[],GLfloat V3[],GLfloat V4[],GLfloat V5[],GLfloat V6[],GLfloat V7[]){
  //creates the faces of the frustum with different colors
  glColor3f(0,0,1.5);
  Face(V0, V1,V3,V2);
  glColor3f(0,1.5,0);
  Face(V4, V5,V7,V6);
  glColor3f(1.5,0,.5);
  Face(V4, V0,V2,V6);
  glColor3f(1.5,0,1.5);
  Face(V5, V1,V3,V7);
  glColor3f(0,1.5,1.5);
  Face(V4, V5,V1,V0);
  glColor3f(1.5,1.5,0);
  Face(V6, V7,V3,V2);
}

void Draw() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0,-1,0,0,0,0,0,0,1);//sets camera location as given
  //calls frustrum and triangle to draw in the terminal

    glRotatef(T,0,0,1);

  Frustum(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
  Triangle(E[0],E[1], E[2]);
  glutSwapBuffers();

  if (s == 1)
    glutIdleFunc(Spin);
  else
    glutIdleFunc(NULL);
}

int main(int argC, char** argV)
{
  glutInit(&argC, argV);
  glutInitWindowPosition(100,100);//sets window position
  glutInitWindowSize(1200,1200);// sets window dimensions
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Frustrum Program");
  glutSpecialFunc(Key);
  glutKeyboardFunc(NKey);
  MyInit();
  glutDisplayFunc(Draw);
  glutMainLoop();
  return 0;
}
