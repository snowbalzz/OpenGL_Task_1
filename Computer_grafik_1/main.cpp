//////////////////////////////////////////////// /////////////////////
// //
// Code framework for lecture computer graphics WS 2022/23 Exercise 1 //
// //
//////////////////////////////////////////////// /////////////////////
#define GL_SILENCE_DEPRECATION
#include <iostream>
using namespace std;
#include "glut.h"
#include "Point.cpp"
#include "Color.cpp"


#define TEX_RES_X 60
#define TEX_RES_Y 60
// Anzahl der Pixel der Textur
#define TEX_RES TEX_RES_X*TEX_RES_Y
// Achsenl�nge der Textur (Achsen sind asymmetrisch von -TexRes#/2 bis TesRes#/2-1)
#define TEX_HALF_X TEX_RES_X/2
#define TEX_HALF_Y TEX_RES_Y/2
// Konvertiert Indices von (x,y) Koordinaten in ein lineares Array
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

// globaler Speicher f�r Texturdaten
char g_Buffer[3*TEX_RES];
// Textur ID Name
GLuint g_TexID = 0;

// Aufl�sung des Hauptfensters (kann sich durch User �ndern)
int g_WinWidth = 800;
int g_WinHeight = 800;


void manageTexture ()
{
    glEnable        (GL_TEXTURE_2D);
    if (g_TexID==0) glGenTextures (1, &g_TexID);
    glBindTexture   (GL_TEXTURE_2D, g_TexID);
    glTexEnvf       (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D    (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);
    glBindTexture   (GL_TEXTURE_2D, 0);
    glDisable       (GL_TEXTURE_2D);
}

// Callback Funktion um die Fenstergr��en anzupassen.
// Auch diese Funktion ist ein notwendiges �bel! K�mmern
// Sie sich im Moment nicht weiter darum.
void reshape(int w, int h)
{

    g_WinWidth = w;
    g_WinHeight = h;
    glViewport(0, 0, w, h);                    // Establish viewing area to cover entire window.

    glMatrixMode(GL_PROJECTION);            // Start modifying the projection matrix.
    glLoadIdentity();                        // Reset project matrix.
    glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);    // Map abstract coords directly to window coords.

    glutPostRedisplay ();
}

// Funktion l�scht den Bildschirm mit der angegebenen Farbe
// Usage z.B.: clearImage (Color (1,1,1))
// l�scht den Bildschirm in Wei�.
// Ohne Farbangabe ist der Standard Wei�
void clearImage (Color c=Color()) {
    for (int i=0; i<TEX_RES; i++) {
        g_Buffer[3*i  ] = 255.0*c.r;
        g_Buffer[3*i+1] = 255.0*c.g;
        g_Buffer[3*i+2] = 255.0*c.b;
    }
}

// Funktion malt einen Punkt an die angegebenen Koordinaten
// Usage z.B.: setPoint (Point(10, 5), Color (1,0,0))
// malt einen Punkt an die Koordinate (10, 5)
// Ohne Farbangabe ist die Standard-Malfarbe Schwarz
//
// Nutzen Sie diese Funktion ...

void setPoint (Point p, Color c=Color(0,0,0)) {
    int x = p.x + TEX_HALF_X;
    int y = p.y + TEX_HALF_Y;
    if (x < 0 || y < 0 || x >= TEX_RES_X || y >= TEX_RES_Y) {
        cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
        return;
    }

    g_Buffer[3*TO_LINEAR (x, y)  ] = 255.0*c.r;
    g_Buffer[3*TO_LINEAR (x, y)+1] = 255.0*c.g;
    g_Buffer[3*TO_LINEAR (x, y)+2] = 255.0*c.b;
}

//
// �BUNG 1 AUFGABE 1:
//
// Diese Funktion soll eine Gerade zwischen den Punkten
// p1 und p2 in der Farbe c malen. Benutzen Sie die Funktion
// setPoint um die individuellen Punkte zu zeichnen.
//My code

void bhamLine3 (int x0, int y0, int x1, int y1, Color c) {
    
    

    int d, dne, de, f, m1, m2, m3, m4, px, py;
    
    
    px = 0;
    py = 0;
    
    //Simple translation of the line position
    if( x0 == 0 && x0 == 0){
        px = 0;
        py = 0;
    } else{
        px = x0;
        py = y0;
        x0 =0;
        y0 =0;
        x1 = x1 - px;
        y1 = y1 - py;
    }

    int dy = y1 - y0;
    int dx = x1 - x0;
    
    //Checking the first flags
    bool flag1 = (dx>=0);
    bool flag2 = (dy>=0);
    bool flag3 = (abs(dy)>=abs(dx));

    
    ///////
    ///
    ///This part of code dose 2 things:
    /// - Uses the results of flags to determine wher is the line located;
    /// - Selects the correct Constans for multiplication;
    ///
    ///////
    if(flag1){
        if(flag2) {

            // x/y
            m1 = 1;
            m2 = 1;
            m3 = 1;
            m4 = 1;

        } else {
            // x/-y
            dx = abs(dx);
            dy = abs(dy);

            if(flag3){
                m1 = 1;
                m2 = 1;
                m3 = 1;
                m4 = -1;

            } else {
                m1 = 1;
                m2 = -1;
                m3 = 1;
                m4 = 1;
            }
        }
    } else{
        if(flag2) {
            //-x/y
            dx = abs(dx);
            dy = abs(dy);

            if(flag3){
                m1 = 1;
                m2 = 1;
                m3 = -1;
                m4 = 1;
            } else {
                m1 = -1;
                m2 = 1;
                m3 = 1;
                m4 = 1;
            }
        } else {
            //-x/-y
            m1 = -1;
            m2 = -1;
            m3 = -1;
            m4 = -1;
        }
    }
    
    //Bellow is the code that only thinks in the first 2 Octants
    //Its also adjusted to use the selected Constans

    x1 = abs(x1);
    y1 = abs(y1);

    dy = y1 - y0;
    dx = x1 - x0;

    flag1 = (dx>=0);
    flag2 = (dy>=0);
    flag3 = (abs(dy)>=abs(dx));
    

    if (flag3) {
        f = y1;
        y1 = x1;
        x1 = f;
    }

    dy = y1 - y0;
    dx = x1 - x0;
    
    dne = 2 * (dy-dx);
    de = 2 * dy;
    d = 2 * dy-dx;

    if (flag1) {
        if(flag2){
            if (!flag3) {

                Point xy2(x0 + px, y0 + py);
                setPoint (xy2, c);

            } else {

                Point xy2(y0 + px, x0 + py);
                setPoint(xy2,c);

            }
            while (x0 < x1) {

                if (d >= 0) {
                    d += dne;
                    x0++;
                    y0++;

                } else {
                    d += de;
                    x0++;
                }
                if (!flag3) {

                    Point xy2(x0 * m1 + px, y0 * m2+ py);
                    setPoint (xy2, c);

                } else {

                    Point xy2(y0 * m3 + px, x0 * m4 + py);
                    setPoint(xy2,c);

                }
            }
        }
    }
}

void plotCircle(int x, int y, int px, int py, Color c){
    Point xy0(x+px,y+py);
    setPoint(xy0,c);

    Point xy1(y+px,x+py);
    setPoint(xy1,c);

    Point xy2(-x+px,y+py);
    setPoint(xy2,c);

    Point xy3(-y+px,x+py);
    setPoint(xy3,c);

    Point xy4(x+px,-y+py);
    setPoint(xy4,c);

    Point xy5(y+px,-x+py);
    setPoint(xy5,c);

    Point xy6(-x+px,-y+py);
    setPoint(xy6,c);

    Point xy7(-y+px,-x+py);
    setPoint(xy7,c);
}

void BresenhamCircle(int px, int py, int r, Color c){
    
    int x, y, p, d, DSE, DE;

    p = 0;
    
    x = p;
    y = r;
    d = 5 - 4*r;
    
    plotCircle(x, y, px, py, c);
    
    while (y>x) {

        if (d>=0)
        {
            DSE = 4*(2*(x-y)+5);
            d += DSE;
            x++;
            y--;
        } // SE
        else {
            DE = 4*(2*x+3);
            d +=DE ;
            x++;
        } // E
        
        plotCircle(x, y, px, py, c);
    }
}

void display (void) {
    Color background(1,1,1);    // White background
    clearImage(background);                // Clearing the canvas or the screen

    //Calling the function to draw the line
    Color cRed(0.5, 0.1, 0.1);
    Color cGreen(0.1, 0.5, 0.1);
    Color cBlue(0.1, 0.1, 0.5);
    Color cBlack(0, 0, 0);
    
//    bhamLine3(10, 5, -10, -20, cGreen);
//
//    bhamLine3(-10, -20, 5, 10, cRed);
//
//    bhamLine3(10, 20, 5, -10, cRed);
//
//    bhamLine3(10, 0, -10, 10, cRed);

    BresenhamCircle(0, 0,10,cRed);
//
    
    
    //////////////////////////////////////////////////////////////////
    ///
    /// DONT TOUCH THIS!
    ///
    //////////////////////////////////////////////////////////////////
    manageTexture ();

    glClear      (GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, g_TexID);
    glEnable     (GL_TEXTURE_2D);

    glBegin     (GL_QUADS);
    glColor3f   (1, 0, 0);
    glTexCoord2f(0, 0);
    glVertex2f  (-g_WinWidth/2, -g_WinHeight/2);
    glTexCoord2f(1, 0);
    glVertex2f  (g_WinWidth/2, -g_WinHeight/2);
    glTexCoord2f(1, 1);
    glVertex2f  (g_WinWidth/2, g_WinHeight/2);
    glTexCoord2f(0, 1);
    glVertex2f  (-g_WinWidth/2, g_WinHeight/2);
    glEnd       ();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable    (GL_TEXTURE_2D);

    glFlush ();
}

// Main function of the file!
int main (int argc, char **argv) {

    glutInit (&argc, argv);
    glutInitWindowSize (g_WinWidth, g_WinHeight);
    glutCreateWindow ("Main Window");

    glutReshapeFunc (reshape);      // Responsible for resizing the window
    glutDisplayFunc (display);      // Responsible for repeatedly redrawing the screen

    glutMainLoop ();

    glDeleteTextures (1, &g_TexID);     // Deletes the texture created above

    return 0;
}

