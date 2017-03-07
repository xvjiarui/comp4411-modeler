// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <FL/glut.h>
#include <string>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
    int arm_angle = 0;
	int arm_angle_step = 1;
	int leg_angle = 0;
	int leg_angle_step = 1;
	std::string m_texturePath = "";
	GLuint m_texture;
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
	// if (m_texturePath != "") {
		// glEnable(GL_TEXTURE_2D);
		// glBindTexture(GL_TEXTURE_2D, m_texture);
		// drawTexture(std::string("Image/RedTexture.jpg"), m_texture);
	// }

    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	if(ModelerApplication::Instance()->m_animating == true)
	{
		arm_angle += arm_angle_step;
		if (arm_angle > 45 || arm_angle < -45)
		{
			arm_angle_step = -arm_angle_step;
		}
		leg_angle += leg_angle_step;
		if (leg_angle > 45 || leg_angle < -45)
		{
			leg_angle_step = -leg_angle_step;
		}
	}
	
    ModelerView::draw();
	GLfloat lightPosition0[] = { VAL(LIGHT0_POS_X), VAL(LIGHT0_POS_Y), VAL(LIGHT0_POS_Z), 0 };
	GLfloat lightDiffuse0[]  = { VAL(LIGHT0_INTENSITY), VAL(LIGHT0_INTENSITY), VAL(LIGHT0_INTENSITY), VAL(LIGHT0_INTENSITY) };
	GLfloat lightPosition1[] = { VAL(LIGHT1_POS_X), VAL(LIGHT1_POS_Y), VAL(LIGHT1_POS_Z), 0  };
	GLfloat lightDiffuse1[]  = { VAL(LIGHT1_INTENSITY), VAL(LIGHT1_INTENSITY), VAL(LIGHT1_INTENSITY), VAL(LIGHT1_INTENSITY) };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition0 );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse0 );
    glLightfv( GL_LIGHT1, GL_POSITION, lightPosition1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse1 );

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_RED);
	glPushMatrix();
	glTranslated(-5,-5,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();

	// draw the sample model
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_GRAY);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		// draw head
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_GREY);
		glPushMatrix();
		glTranslated(-1, 15, -1);
		glTranslated(1, -0.6, 1);
		glRotated(VAL(ROTATE_HEAD_X), 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_HEAD_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_HEAD_Z), 0.0, 0.0, 1.0);
		glTranslated(-1, 0.6, -1);

		drawHead(VAL(ROTATE_HEAD_DEC), VAL(LEVEL_OF_DETAILS));

		glPopMatrix();

		// draw Torso
		glPushMatrix();
		setDiffuseColor(COLOR_GRAY);
		glTranslated(-2, 6.4, -1);
		drawBox(4, 8, 2);

		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_WHITE);
		glPushMatrix();
		glTranslated(1, -1, 0.5);
		glScaled(2, 1, 1);
		drawRectangularPrism(2, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslated(1, -1, 1);
		glRotated(90, 0.0, 1.0, 0.0);
		drawCylinder(2, 0.5, 0.5);
		glPopMatrix();

		glPopMatrix();


		// draw right arm
		glPushMatrix();
		glTranslated(2.5, 12.5, -1);

		glTranslated(0, 1, 1);
		glRotated(-VAL(ROTATE_RIGHT_ARM_X) + VAL(LIFT_RIGHT_ARM) + arm_angle, 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_ARM_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_ARM_Z), 0.0, 0.0, 1.0);
		glTranslated(0, -1, -1);
		// draw right shoulder
		
		setDiffuseColor(COLOR_BLUE);
		drawShoulder(2, 0.5, VAL(LEVEL_OF_DETAILS));
		glTranslated(0, 0, 0.25);
		glTranslated(0, -3, 0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawBox(1.5, 3, 1.5);
		}
		glTranslated(0, -0.5, 0.5);
		glTranslated(0, 0, 0.25);
		glRotated(90, 0.0, 1.0, 0.0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawCylinder(1.5, 0.5, 0.5);
		}
		glRotated(-90, 0.0, 1.0, 0.0);
		glTranslated(0, 0, -0.25);
		glTranslated(0.5, 0, 0.25);
		glRotated(-VAL(ROTATE_RIGHT_ARM_L_X) - 3 * VAL(LIFT_RIGHT_ARM) - 3 * arm_angle, 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_ARM_L_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_ARM_L_Z), 0.0, 0.0, 1.0);
		glTranslated(-0.5, 0, -0.25);
		glTranslated(0, -3.5, -0.5);
		if (VAL(LEVEL_OF_DETAILS) > 2)
		{
			drawBox(1.5, 3, 1.5);
		}
		glPopMatrix();

		// draw left arm
		glPushMatrix();
		glRotated(180, 0.0, 1.0, 0.0);
		glTranslated(2.5, 12.5, -1);

		glTranslated(0, 1, 1);
		glRotated(VAL(ROTATE_LEFT_ARM_X) - VAL(LIFT_LEFT_ARM) + arm_angle, 1.0, 0.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_ARM_Y), 0.0, 1.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_ARM_Z), 0.0, 0.0, 1.0);
		glTranslated(0, -1, -1);
		// draw left shoulder
		
		setDiffuseColor(COLOR_BLUE);
		drawShoulder(2, 0.5, VAL(LEVEL_OF_DETAILS));
		glTranslated(0, 0, 0.25);
		glTranslated(0, -3, 0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawBox(1.5, 3, 1.5);
		}
		glTranslated(0, -0.5, 0.5);
		glTranslated(0, 0, 0.25);
		glRotated(90, 0.0, 1.0, 0.0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawCylinder(1.5, 0.5, 0.5);
		}
		glRotated(-90, 0.0, 1.0, 0.0);
		glTranslated(0, 0, -0.25);
		glTranslated(0.5, 0, 0.25);
		glRotated(VAL(ROTATE_LEFT_ARM_L_X) + 3 * VAL(LIFT_LEFT_ARM) - 3 * arm_angle, 1.0, 0.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_ARM_L_Y), 0.0, 1.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_ARM_L_Z), 0.0, 0.0, 1.0);
		glTranslated(-0.5, 0, -0.25);
		glTranslated(0, -3.5, -0.5);
		if (VAL(LEVEL_OF_DETAILS) > 2)
		{
			drawBox(1.5, 3, 1.5);
		}
		glPopMatrix();

		// draw right leg 
		glPushMatrix();
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_GREEN);

		glTranslated(0, 5, 0);
		glRotated(-VAL(ROTATE_RIGHT_LEG_X) - VAL(LIFT_RIGHT_LEG) + leg_angle, 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_LEG_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_LEG_Z), 0.0, 0.0, 1.0);
		glTranslated(0, -5, 0);

		glTranslated(0.5, 1.5, -1);
		glScaled(0.75, 1, 1);
		if (VAL(LEVEL_OF_DETAILS) > 0)
		{
			drawBox(2, 4.5, 2);
		}
		// draw right lower leg
		glTranslated(0, -0.5, 1);
		glRotated(90, 0.0, 1.0, 0.0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawCylinder(2, 0.5, 0.5);
		}
		glRotated(-90, 0.0, 1.0, 0.0);

		glTranslated(1, 0, 0);
		glRotated(-VAL(ROTATE_RIGHT_LEG_L_X) + 2 * VAL(LIFT_RIGHT_LEG) - 2 * leg_angle, 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_LEG_L_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_LEG_L_Z), 0.0, 0.0, 1.0);
		glTranslated(-1, 0, 0);

		glTranslated(0, -4, -1);
		glTranslated(0.25, 0, 0.25);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawRectangularPrism(2, 1.5, 3.5);
		}

		// draw right foot
		glTranslated(0.5, -1, 1);
		glRotated(-VAL(ROTATE_RIGHT_FOOT_X) - VAL(LIFT_RIGHT_LEG) + leg_angle, 1.0, 0.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_FOOT_Y), 0.0, 1.0, 0.0);
		glRotated(VAL(ROTATE_RIGHT_FOOT_Z), 0.0, 0.0, 1.0);
		glTranslated(-0.5, 1, -1);

		glTranslated(-0.25, 0, -0.25);
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_RED);
		glTranslated(0, -2, 0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawRectangularPrism(1.5, 2, 1.5);
		}
		glTranslated(1.75, 0, 1.5);
		glRotated(90, 0.0, 0.0, 1.0);
		if (VAL(LEVEL_OF_DETAILS) > 2)
		{
			drawTriangularPrism(1.5, 1.5, 1.5, 90);
		}
		glRotated(-90, 0.0, 0.0, 1.0);
		glPopMatrix();

		// draw left leg 
		glPushMatrix();
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_GREEN);
		glRotated(180, 0.0, 1.0, 0.0);

		glTranslated(0, 5, 0);
		glRotated(VAL(ROTATE_LEFT_LEG_X) + VAL(LIFT_LEFT_LEG) + leg_angle, 1.0, 0.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_LEG_Y), 0.0, 1.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_LEG_Z), 0.0, 0.0, 1.0);
		glTranslated(0, -5, 0);

		glTranslated(0.5, 1.5, -1);
		glScaled(0.75, 1, 1);
		if (VAL(LEVEL_OF_DETAILS) > 0)
		{
			drawBox(2, 4.5, 2);
		}
		// draw left lower leg
		glTranslated(0, -0.5, 1);
		glRotated(90, 0.0, 1.0, 0.0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawCylinder(2, 0.5, 0.5);
		}
		glRotated(-90, 0.0, 1.0, 0.0);

		glTranslated(1, 0, 0);
		glRotated(VAL(ROTATE_LEFT_LEG_L_X) - 2 * VAL(LIFT_LEFT_LEG) - 2 * leg_angle, 1.0, 0.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_LEG_L_Y), 0.0, 1.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_LEG_L_Z), 0.0, 0.0, 1.0);
		glTranslated(-1, 0, 0);

		glTranslated(0, -4, -1);
		glTranslated(0.25, 0, 0.25);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawRectangularPrism(2, 1.5, 3.5);
		}

		// draw left foot
		glTranslated(0.5, -1, 1);
		glRotated(VAL(ROTATE_LEFT_FOOT_X) + VAL(LIFT_LEFT_LEG) + leg_angle, 1.0, 0.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_FOOT_Y), 0.0, 1.0, 0.0);
		glRotated(-VAL(ROTATE_LEFT_FOOT_Z), 0.0, 0.0, 1.0);
		glTranslated(-0.5, 1, -1);

		glTranslated(-0.25, 0, -0.25);
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_RED);
		glTranslated(0, -2, 0);
		if (VAL(LEVEL_OF_DETAILS) > 1)
		{
			drawRectangularPrism(1.5, 2, 1.5);
		}
		glTranslated(1.75, 0, 0.5);
		glRotated(-90, 1.0, 0.0, 0.0);
		glRotated(90, 0.0, 0.0, 1.0);
		if (VAL(LEVEL_OF_DETAILS) > 2)
		{
			drawTriangularPrism(1.5, 1.5, 1.5, 90);
		}
		glRotated(-90, 0.0, 0.0, 1.0);
		glRotated(90, 1.0, 0.0, 0.0);
		glPopMatrix();

	glPopMatrix();
	// if (m_texturePath != "")
	// 	glDisable(GL_TEXTURE_2D);
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
	controls[LIGHT0_POS_X] = ModelerControl("Light0 pos X", -30, 30, 1, 4);
	controls[LIGHT0_POS_Y] = ModelerControl("Light0 pos Y", -30, 30, 1, 2);
	controls[LIGHT0_POS_Z] = ModelerControl("Light0 pos Z", -30, 30, 1, -4);
	controls[LIGHT0_INTENSITY] = ModelerControl("Light0 intensity", 0, 5, 0.01, 1.3);
	controls[LIGHT1_POS_X] = ModelerControl("Light1 pos X", -30, 30, 1, -2);
	controls[LIGHT1_POS_Y] = ModelerControl("Light1 pos Y", -30, 30, 1, 1);
	controls[LIGHT1_POS_Z] = ModelerControl("Light1 pos Z", -30, 30, 1, 5);
	controls[LIGHT1_INTENSITY] = ModelerControl("Light1 intensity", 0, 5, 0.01, 1.3);
	controls[ROTATE_HEAD_X] = ModelerControl("Rotate Head_X", -30, 30, 1, 0);
	controls[ROTATE_HEAD_Y] = ModelerControl("Rotate Head_Y", -90, 90, 1, 0);
	controls[ROTATE_HEAD_Z] = ModelerControl("Rotate Head_Z", -30, 30, 1, 0);
	controls[ROTATE_HEAD_DEC] = ModelerControl("Rotate Haed_Dec", -20, 20, 1, 0);
	controls[ROTATE_RIGHT_ARM_X] = ModelerControl("Rotate right arm X", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_Y] = ModelerControl("Rotate right arm Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_Z] = ModelerControl("Rotate right arm Z", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_X] = ModelerControl("Rotate right arm lower X", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_Y] = ModelerControl("Rotate right arm lower Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_Z] = ModelerControl("Rotate right arm lower Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_X] = ModelerControl("Rotate left arm X", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_Y] = ModelerControl("Rotate left arm Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_Z] = ModelerControl("Rotate left arm Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_L_X] = ModelerControl("Rotate left arm lower X", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_L_Y] = ModelerControl("Rotate left arm lower Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_L_Z] = ModelerControl("Rotate left arm lower Z", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_X] = ModelerControl("Rotate rihgt leg X", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_Y] = ModelerControl("Rotate rihgt leg Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_Z] = ModelerControl("Rotate rihgt leg Z", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_L_X] = ModelerControl("Rotate rihgt leg lower X", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_L_Y] = ModelerControl("Rotate rihgt leg lower Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_LEG_L_Z] = ModelerControl("Rotate rihgt leg lower Z", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_FOOT_X] = ModelerControl("Rotate rihgt foot X", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_FOOT_Y] = ModelerControl("Rotate rihgt foot Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_FOOT_Z] = ModelerControl("Rotate rihgt foot Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_X] = ModelerControl("Rotate left leg X", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_Y] = ModelerControl("Rotate left leg Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_Z] = ModelerControl("Rotate left leg Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_L_X] = ModelerControl("Rotate left leg lower X", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_L_Y] = ModelerControl("Rotate left leg lower Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_LEG_L_Z] = ModelerControl("Rotate left leg lower Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_FOOT_X] = ModelerControl("Rotate left foot X", -45, 45, 1, 0);
	controls[ROTATE_LEFT_FOOT_Y] = ModelerControl("Rotate left foot Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_FOOT_Z] = ModelerControl("Rotate left foot Z", -45, 45, 1, 0);
	controls[LIFT_RIGHT_ARM] = ModelerControl("Lift right arm", -45, 45, 1, 0);
	controls[LIFT_LEFT_ARM] = ModelerControl("Lift left arm", -45, 45, 1, 0);
	controls[LIFT_RIGHT_LEG] = ModelerControl("Lift right leg", -45, 45, 1, 0);
	controls[LIFT_LEFT_LEG] = ModelerControl("Lift left leg", -45, 45, 1, 0);
	controls[LEVEL_OF_DETAILS] = ModelerControl("Level Of Details", 0, 3, 1, 3);
    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
