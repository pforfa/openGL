#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

// g++ project4.cpp -lglut -lGL -lGLEW -lGLU -o project4

GLfloat
  light_pos[] = {2, 4, 4, 1},
  spe[] = {0.25, 0.25, 0.25, 1.0},
  amb[] = {0.3, 0.3, 0.3, 1.0},
  difLight0[4] = {0.9, 0.9, 0.9, 1.0};


GLfloat
  airPlaneColor[] = {0.6, 0.6, 0.6},
  airTowerColor[]   = {.678431373, .678431373, .474509804, 1},
  orange[]   = {1, 0.5, 0, 1},
  green[] = {.25, 1, .30, 1},
  blue[]  = {0, 0.2, 0.8, 1};

GLfloat
  angle = 0,
  dt  = 0,
  dtStorePause,
  rutterSpeed = 0,
  rdt = 0,
  flank = 90;

int zoom = 120,
    resolution = 40,
    counter = 0;

double flightHeight = -2.5;

const int WIDTH_OF_WINDOW = 800, HEIGHT_OF_WINDOW = 600;

bool antialiasing = false,
     pause = false,
     bounce  = true,
     forward = true,
     moving  = true,
     takingOff = true,
     landing = false,
     inAir = false;

void wings(GLUquadricObj *quadObj) {
  //front left wing
  glPushMatrix();
  glRotated(90, 1, 0, 0);
  glTranslated(0.2, 1.5, 0);
  glRotated(45,0,0,1);
  gluCylinder(quadObj, 0.25, 0.1, 1.25, 4, 4);
  glPopMatrix();

  //front right wing
  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  glTranslated(0.2, -1.5, 0);
  glRotated(45,0,0,1);
  gluCylinder(quadObj, 0.25, 0.1, 1.25, 4, 4);
  glPopMatrix();

  //back left wing
  glPushMatrix();
  glRotated(90, 1, 0, 0);
  glTranslated(0.0, .5, 0);
  glRotated(45,0,0,1);
  gluCylinder(quadObj, 0.25, 0.1, .85, 4, 4);
  glPopMatrix();

  //back right wing
  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  glTranslated(0.0, -.5, 0);
  glRotated(45,0,0,1);
  gluCylinder(quadObj, 0.25, 0.1, .85, 4, 4);
  glPopMatrix();
}

void rutters(GLUquadricObj *quadObj) {
  //middle Rutter 1
  glPushMatrix();
  glTranslated(0, 0, 2.38);
  glRotated(0+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .4, 2, 2, 55, 60);
  glPopMatrix();

  //middle Rutter 2
  glPushMatrix();
  glTranslated(0, 0, 2.38);
  glRotated(90+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .4, 2, 2, 55, 60);
  glPopMatrix();

  //middle Rutter 3
  glPushMatrix();
  glTranslated(0, 0, 2.38);
  glRotated(180+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .4, 2, 2, 55, 60);
  glPopMatrix();

  //middle Rutter 4
  glPushMatrix();
  glTranslated(0, 0, 2.38);
  glRotated(270+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .4, 2, 2, 55, 60);
  glPopMatrix();

  //right Rutter 1
  glPushMatrix();
  glTranslated(-.025, .75, 1.85);
  glRotated(0+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //right Rutter 2
  glPushMatrix();
  glTranslated(-.025, .75, 1.85);
  glRotated(90+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //right Rutter 3
  glPushMatrix();
  glTranslated(-.025, .75, 1.85);
  glRotated(180+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //right Rutter 4
  glPushMatrix();
  glTranslated(-.025, .75, 1.85);
  glRotated(270+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //left Rutter 1
  glPushMatrix();
  glTranslated(-.025, -.75, 1.85);
  glRotated(0+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //left Rutter 2
  glPushMatrix();
  glTranslated(-.025, -.75, 1.85);
  glRotated(90+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //left Rutter 3
  glPushMatrix();
  glTranslated(-.025, -.75, 1.85);
  glRotated(180+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();

  //left Rutter 4
  glPushMatrix();
  glTranslated(-.025, -.75, 1.85);
  glRotated(270+angle+rutterSpeed, 0, 0, 1);
  gluPartialDisk(quadObj, 0, .3, 2, 2, 55, 60);
  glPopMatrix();
}

void engines(GLUquadricObj *quadObj) {
  //right Engine
  glPushMatrix();
  glRotated(90, 0, 0, 1);
  glTranslated(0.75, .075, 1.2);
  gluCylinder(quadObj, 0.15, 0.15, .55, resolution, resolution);
  glPopMatrix();

  //right Engine Spinner
  glPushMatrix();
  glRotated(90, 0, 0, 1);
  glTranslated(0.75, .075, 1.2);
  gluCylinder(quadObj, 0.15, 0.05, .80, resolution, resolution);
  glPopMatrix();

  //left Engine
  glPushMatrix();
  glRotated(90, 0, 0, 1);
  glTranslated(-0.75, .075, 1.2);
  gluCylinder(quadObj, 0.15, 0.15, .55, resolution, resolution);
  glPopMatrix();

  //left Engine Spinner
  glPushMatrix();
  glRotated(90, 0, 0, 1);
  glTranslated(-0.75, .075, 1.2);
  gluCylinder(quadObj, 0.15, 0.05, .80, resolution, resolution);
  glPopMatrix();
}

void airPlane(GLUquadricObj *quadObj) {
  glTranslated(0, flightHeight, 0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, airPlaneColor);

  //body
  glPushMatrix();
  glRotated(flank, 0, 0, 1);
  gluCylinder(quadObj, 0.45, 0.45, 2, resolution, resolution);

  wings(quadObj);
  rutters(quadObj);
  engines(quadObj);

  //back Piece
  glPushMatrix();
  glRotated(90, 1, 0, 0);
  glTranslated(0.25, -.25, 0);
  gluPartialDisk(quadObj, 0, .8, 8, 8, 0, 105);
  glPopMatrix();

  //front cockpit cover
  glTranslated(0, 0, 2);
  gluCylinder(quadObj, 0.45, 0.1, 0.4, resolution, resolution);
  glPopMatrix();

  //back exhaust cover
  glTranslated(0, 0, .0);
  glRotated(180, 0, 1, 0);
  gluCylinder(quadObj, 0.45, 0.1, 0.4, resolution, resolution);
  glPopMatrix();
}

void drawTerrain(GLUquadricObj *quadObj) {
  //sun
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
  glPushMatrix();
  glTranslated(0, 60, -40);
  gluSphere(quadObj, 12, resolution, resolution);
  glPopMatrix();

  //control Tower
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, airTowerColor);
  glPushMatrix();
  glTranslated(0, 2.5, -6);
  glRotated(90, 1, 0, 0);
  gluCylinder(quadObj, .75, .75, 7, resolution, resolution);
  glPopMatrix();

  //control tower top
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, airTowerColor);
  glPushMatrix();
  glTranslated(0, 2, -6);
  glRotated(90, 1, 0, 0);
  gluDisk(quadObj, 0, 1.3, 70, 70);
  glPopMatrix();

  //control tower bottom
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, airTowerColor);
  glPushMatrix();
  glTranslated(0, 1, -6);
  glRotated(90, 1, 0, 0);
  gluDisk(quadObj, 0, 1.3, 70, 70);
  glPopMatrix();

  //island
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
  gluQuadricOrientation(quadObj, GLU_INSIDE);
  glPushMatrix();
  glTranslated(0, -4, -14.5);
  glRotated(85, 1, 0, 0);
  gluDisk(quadObj, 0, 12, 70, 70);
  glPopMatrix();

  //water
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
  gluQuadricOrientation(quadObj, GLU_INSIDE);
  glPushMatrix();
  glTranslated(0, -6, -11);
  glRotated(95, 1, 0, 0);
  gluDisk(quadObj, 0, 25, resolution, resolution);
  glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, airPlaneColor);
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1, .5, 50);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    drawTerrain(quadObj);

    //move the airplane and change direction of flight
    if (forward) {
        glTranslated(0, 0, -10);
        glRotated(angle, 0, 1, 0);
        glTranslated(-6, 0, 0);
    }
    else {
        glTranslated(0, 0, -10);
        glRotated(angle-180, 0, 1, 0);
        glTranslated(6, 0, 0);

    }
    airPlane(quadObj);

    glutSwapBuffers();
}

void idle(void) {

    if (!pause) {
        if(counter == -1) {
          landing = true;
          if(flank != 90) {
            if(flank > 90)
              flank -= 1;
            else{
              flank += 1;
            }
          }
          angle += dt;
          if(forward && flightHeight > -2.49 && flank == 90) {
            rutterSpeed -= rdt;
            if(dt >= .02 && flightHeight <= -1) {
              dt -= .002;
              rdt -= .01;
            }
          }
          if(flightHeight >= -2.49 && flank == 90) {
            flightHeight -= .01;
          }else{
            inAir = false;
            landing = false;
            if(dt >= .02 && flank == 90) {
              dt -= .002;
            }
            if(rdt > 0 && flank == 90) {
              rdt -= .02;
            }
            if(rutterSpeed > 0) {
              rutterSpeed -= rdt;
            }
          }
        }
        if(counter < 500 && counter != -1) {
          landing = false;
          takingOff = true;
          if(counter==150)
            std::cout << "Control Tower: Delta One, cleared for takeoff runway 01." << std::endl;
          if(counter==400)
            std::cout << "Pilot: Cleared for takeoff runway 01, Delta One." << std::endl;
          counter += 1;
          rdt += .04;
          rutterSpeed += rdt;
        }
        if (moving) {
            //Reset angle to zero after 5 rotations in either direction
            //to avoid big angle calculations
            if(counter >= 500) {
              if(angle == 360 * 5 || angle == -(360 * 5) )
                angle=0;
              if(inAir==false) {
                if(flightHeight < -1 && dt >= 1) {
                    flightHeight += .01;
                }
              }
              if(flightHeight >= -2) {
                inAir=true;
                takingOff = false;
              }
              if(dt <= 1) {
                dt += .004;
              }

              if (forward) {
                angle += dt;
                rutterSpeed += rdt;
              }
              else{
                angle -= dt;
                rutterSpeed += rdt;
              }
          }
        }
    }
    glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y) {

      switch (key) {

        case 'l':
          if(landing == true || takingOff == true || flightHeight <= -2.49)break;
          counter = -1;
          std::cout << "Pilot: Control, requesting permission for landing, Delta One.\n";
          std::cout << "Control Tower: Delta One, cleared for landing.\n";
          break;

        case 't':
          if(landing || takingOff || inAir)break;
          counter = 0;
          break;

        //Ascend the aircraft
        case 'w':
          if(!pause) {
            if(takingOff || landing) break;
            if(flightHeight < 5.5) flightHeight += 0.05;
          }
          break;

        //Descend the aircraft
        case 's':
          if(!pause) {
            if(takingOff || landing) break;
            if(flightHeight > -1) flightHeight -= 0.05;
          }
          break;

        case 'x':
          zoom -= (zoom >= 90) ? 5: 0;
          break;

        case 'z':
          zoom += (zoom <= 130) ? 5: 0;
          break;

        case 'p':
          if(!pause) {
            dtStorePause = dt;
            dt=0;
            pause=true;
          }
          else{
            dt=dtStorePause;
            pause=false;
          }
          break;

        case 'f':
          if(takingOff || landing) break;
          if(dt < 1.75)
            dt += .25;
          break;

        case 'r':
          if(takingOff || landing) break;
          if(dt > .5)
            dt -= .25;
          break;

        case 'e':
          if(takingOff || flightHeight <= -1.5 || landing)break;
          if(flank==270) {
            flank=90;
          }
          flank += 2;
          break;

        case 'q':
          if(takingOff || flightHeight <= -1.5 || landing)break;
          if(flank==-270) {
            flank=90;
          }
          flank -= 2;
          break;
      }
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    std::cout << "Controls: \n\n";
    std::cout << "'w' key ->\t ascend \n";
    std::cout << "'s' key ->\t descend \n";
    std::cout << "'q' key ->\t Rotate Left\n";
    std::cout << "'e' key ->\t Rotate Right\n";
    std::cout << "'x' key ->\t zoom in \n";
    std::cout << "'z' key ->\t zoom out \n";
    std::cout << "'p' key ->\t Play/Pause \n";
    std::cout << "'f' key ->\t Speed Up \n";
    std::cout << "'r' key ->\t Slow Down \n";
    std::cout << "'t' key ->\t Take Off Into the Air \n";
    std::cout << "'l' key ->\t Land the Aircraft \n";


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Project 4");

    glClearColor(0.52734375, 0.8046875, 0.91796875, 1);
    glEnable(GL_DEPTH_TEST);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difLight0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
}
