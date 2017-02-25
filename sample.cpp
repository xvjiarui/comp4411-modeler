// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5,0,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GRAY);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// draw head
		glPushMatrix();
		// glTranslated(0, 4, 0);
		glTranslated(-1, 4, -1);
		glTranslated(1, 1, 1);
		glRotated(VAL(ROTATE_HEAD_X), 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_HEAD_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_HEAD_Z), 0.0, 0.0, 1.0);
		glTranslated(-1, -1, -1);
		// glTranslated(0, -4, 0);
		// glTranslated(-1, 4, -1);
		glScaled(2, 2, 2);
		drawBox(1,1,1);

			setAmbientColor(.1f,.1f,.1f);
			setDiffuseColor(COLOR_YELLOW);
			// draw head right dec
			glPushMatrix();
			glTranslated(0.5,1,1);
			glRotated(20, 0.0, 0.0, 1.0);
			glScaled(3, 1, 1);
			glRotated(90, 1.0 ,0.0, 0.0);
			drawTriangularPyramid(0.5);
			glPopMatrix();
			// draw head left dec
			glPushMatrix();
			glTranslated(0.5,1,1);
			glRotated(-20, 0.0, 0.0, 1.0);
			glScaled(3, 1, 1);
			glRotated(-120, 0.0, 0.0, 1.0);
			glRotated(90, 1.0 ,0.0, 0.0);
			drawTriangularPyramid(0.5);
			glPopMatrix();

		glPopMatrix();

		// // draw cannon
		// glPushMatrix();
		// glRotated(VAL(ROTATE), 0.0, 1.0, 0.0);
		// glRotated(-90, 1.0, 0.0, 0.0);
		// drawCylinder(VAL(HEIGHT), 0.1, 0.1);

		// glTranslated(0.0, 0.0, VAL(HEIGHT));
		// drawCylinder(1, 1.0, 0.9);

		// glTranslated(0.0, 0.0, 0.5);
		// glRotated(90, 1.0, 0.0, 0.0);
		// drawCylinder(4, 0.1, 0.2);
		// glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 2.5, 0.1f, 1);
	controls[ROTATE] = ModelerControl("Rotate", -135, 135, 1, 0);
	controls[ROTATE_HEAD_X] = ModelerControl("Rotate Head_X", -30, 30, 1, 0);
	controls[ROTATE_HEAD_Y] = ModelerControl("Rotate Head_Y", -90, 90, 1, 0);
	controls[ROTATE_HEAD_Z] = ModelerControl("Rotate Head_Z", -30, 30, 1, 0);
    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
