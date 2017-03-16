// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "MetaBall.h"
#include <FL/gl.h>
#include <FL/glut.h>
#include <string>
#include "vec.h"
#include "mat.h"
#include "modelerglobals.h"
#include <math.h>
// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }
    void IK_calculation(){
    	Vec3d joint1_first = effector - joints[1];
    	if (!joint1_first.iszero())
    	{
    		joint1_first.normalize();
    	}
    	Vec3d joint1_second = (Vec3d(VAL(CSTRN_X), VAL(CSTRN_Y), VAL(CSTRN_Z)) - joints[1]);
    	if (!joint1_second.iszero())
    	{
    		joint1_second.normalize();
    	}
    	rotate_angle[1] = get_angle(joint1_first, joint1_second);
    	if (abs(rotate_angle[1]) < 0.00000001)
    	{
    		return;
    	}
    	rotate_axis[1] = cross_product(joint1_first, joint1_second);
    	rotate_axis[1].normalize();
    	effector = rotate_vec(effector, rotate_angle[1], rotate_axis[1][0], rotate_axis[1][1], rotate_axis[1][2]);

    	Vec3d joint0_first = effector - joints[0];
    	if (!joint0_first.iszero())
    	{
    		joint0_first.normalize();
    	}
    	Vec3d joint0_second = (Vec3d(VAL(CSTRN_X), VAL(CSTRN_Y), VAL(CSTRN_Z)) - joints[0]);
    	if (!joint0_second.iszero())
    	{
    		joint0_second.normalize();
    	}
    	rotate_angle[0] = get_angle(joint0_first, joint0_second);
    	if (abs(rotate_angle[0]) < 0.00000001)
    	{
    		return;
    	}
    	rotate_axis[0] = cross_product(joint0_first, joint0_second);
    	rotate_axis[0].normalize();
    	effector = rotate_vec(effector, rotate_angle[0], rotate_axis[0][0], rotate_axis[0][1], rotate_axis[0][2]);
    	joints[1] = rotate_vec(joints[1], rotate_angle[0], rotate_axis[0][0], rotate_axis[0][1], rotate_axis[0][2]);
    	// printf("pre %f %f %f\n", joints[1][0], joints[1][1], joints[1][2]);
    	// double cof = -effector[2]/effector[1];
    	// if (abs(effector[1]) < 0.00000001)
    	// {
    	// 	return;
    	// }
    	// joints[1] = reflect_vec(joints[1], 0, cof, 1);
    	// printf("post %f %f %f\n", joints[1][0], joints[1][1], joints[1][2]);
    	Vec3d test_vec = Vec3d(0, 1, 0);
    	test_vec = reflect_vec(test_vec, 0, 1, 0);
    	printf("%f %f %f\n", test_vec[0], test_vec[1], test_vec[2]);

    }
    Vec3d cross_product(Vec3d v1, Vec3d v2)
    {
    	return Vec3d(v1[1] * v2[2] - v1[2] * v2[1], - (v1[0] * v2[2] - v1[2] * v2[0]), v1[0] * v2[1] - v1[1] * v2[0]);
    }
    double get_angle(Vec3d v1, Vec3d v2)
    {
    	double costheta = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    	return acos (costheta);
    }
    Vec3d rotate_vec(Vec3d v, double angle, double x, double y, double z)
    {
    	double s = sin(angle);
    	double c = cos(angle);
    	Vec4d h_v = Vec4d(v[0], v[1], v[2], 1);
    	Mat4d rotate_mat = Mat4d(x*x*(1-c)+c, x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0, y*x*(1-c)+z*s, y*y*(1-c)+c, y*z*(1-c)-x*s, 0, x*z*(1-c)-y*s, y*z*(1-c)+x*s, z*z*(1-c)+c, 0, 0, 0, 0, 1);
    	Vec4d result = rotate_mat*h_v;
    	return Vec3d(result[0], result[1], result[2]);
    }
    Vec3d translate_vec(Vec3d v, double x, double y, double z)
    {
    	Vec4d h_v = Vec4d(v[0], v[1], v[2], 1);
    	Mat4d translate_mat = Mat4d(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
    	Vec4d result = translate_mat * h_v;
    	return Vec3d(result[0], result[1], result[2]);
    }
    Vec3d reflect_vec(Vec3d v, double a, double b, double c)
    {
    	Mat3d reflect_mat = Mat3d(1 - 2*a*a, -2*a*b, -2*a*c, -2*a*b, 1-2*b*b, -2*b*c, -2*a*c, -2*b*c, 1-2*c*c);
    	Vec3d result = reflect_mat * v;
    	return result;
    }
    virtual void draw();
    int arm_angle = 0;
	int arm_angle_step = 1;
	int leg_angle = 0;
	int leg_angle_step = 1;
	std::string m_texturePath = "Image/RedTexture.jpg";
	GLuint m_texture;
	bool IKLastState = false;
	double metaball_pos = 0;
	double metaball_step = 0.1;
	double joint_raduis = 1;
	double joint_length = 4;
	Vec3d joints[2] = {Vec3d(0, 0, 0), Vec3d(0.0f, 0.0f, joint_raduis * 2.0f + joint_length * 1.0f)};
	// joints[1] = Vec3d(0.0f, 0.0f, joint_raduis * 2.0f + joint_length * 1.0f);
	// joints[0] = Vec3d(0.0f, 0.0f, 0.0f);
	Vec3d effector = Vec3d(0.0f, 0.0f, joint_raduis * 4.0f + joint_length * 2.0f);
	Vec3d rotate_axis[2] = {Vec3d(0, 0, 0), Vec3d(0, 0, 0)};
	double rotate_angle[2] = {0, 0};

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
	if (VAL(L_SYSTEM))
	{
		setAmbientColor(.1f,.1f,.1f);
		setDiffuseColor(COLOR_YELLOW);

		drawLSystem(VAL(L_SYSTEM_SIZE), VAL(L_SYSTEM_NUM));
		// glBegin(GL_LINES);
		//   glVertex3f(0, 0, 0);
		//   glVertex3f(0, 4, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(0, 1, 0);
		//   glVertex3f(1, 2, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(0, 1, 0);
		//   glVertex3f(-1, 2, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(0.5, 1.5, 0);
		//   glVertex3f(0.5, 2, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(-0.5, 1.5, 0);
		//   glVertex3f(-0.5, 2, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(0, 2, 0);
		//   glVertex3f(2, 4, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(0, 2, 0);
		//   glVertex3f(-2, 4, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(1, 3, 0);
		//   glVertex3f(1, 4, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(-1, 3, 0);
		//   glVertex3f(-1, 4, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(1, 3, 0);
		//   glVertex3f(2, 3, 0);
		// glEnd();
		// glBegin(GL_LINES);
		//   glVertex3f(-1, 3, 0);
		//   glVertex3f(-2, 3, 0);
		// glEnd();

	}
	else
	{
	if (VAL(MOOD_CYCLE))
	{
		SET(ROTATE_HEAD_X, 30);
		SET(ROTATE_RIGHT_ARM_X, 90);
		SET(ROTATE_LEFT_ARM_X, 90);
		SET(ROTATE_RIGHT_ARM_Y, -40);
		SET(ROTATE_LEFT_ARM_Y, -40);
		SET(ROTATE_RIGHT_ARM_L_X, 120);
		SET(ROTATE_LEFT_ARM_L_X, 120);
	}
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
		// MetaBall m_metaBall;
		// m_metaBall.cal();
		// m_metaBall.draw(1);
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
		if (VAL(INDIVIDUAL_LOOK))
		{	
			glTranslated(1, 1, 1);
			glutSolidDodecahedron();
			glTranslated(-1, -1, -1);
		}
		else drawShoulder(2, 0.5, VAL(LEVEL_OF_DETAILS));
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
			setDiffuseColor(COLOR_WHITE);
			drawCylinderWithTexture(1.5, 0.5, 0.5, "Image/YellowTexture.bmp");
			// drawCylinder(1.5, 0.5, 0.5);
			setDiffuseColor(COLOR_BLUE);
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
		if (VAL(INDIVIDUAL_LOOK))
		{	
			glTranslated(1, 1, 1);
			glutSolidDodecahedron();
			glTranslated(-1, -1, -1);
		}
		else drawShoulder(2, 0.5, VAL(LEVEL_OF_DETAILS));
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
			setDiffuseColor(COLOR_WHITE);
			drawCylinderWithTexture(1.5, 0.5, 0.5, "Image/YellowTexture.bmp");
			// drawCylinder(1.5, 0.5, 0.5);
			setDiffuseColor(COLOR_BLUE);
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

		// if (ModelerApplication::Instance()->m_animating == true)
		// {
		// 	MetaBall* m_metaBall = new MetaBall(1.0f);
		// 	m_metaBall->addBallRel(3, metaball_pos, 3, 4);
		// 	m_metaBall->addBallRel(3, 3 - metaball_pos, 3, 4);
		// 	m_metaBall->draw(30);
		// 	delete m_metaBall;
		// 	metaball_pos += metaball_step;
		// }

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

	if (VAL(INVERSE_KINEMATICS))
	{
		IK_calculation();
		IK_calculation();
		glPushMatrix();
			
			glPushMatrix();
			// glRotated(90, 1, 0, 0);
			glTranslated(1.2, 4.5, 0);
			glPushMatrix();
				setDiffuseColor(COLOR_YELLOW);
				glTranslated(VAL(CSTRN_X), VAL(CSTRN_Y), VAL(CSTRN_Z));
				drawSphere(joint_raduis);
			glPopMatrix();
			setDiffuseColor(COLOR_GREEN);
			glPushMatrix();
				glTranslated(joints[0][0], joints[0][1], joints[0][2]);
				drawSphere(joint_raduis);
			glPopMatrix();
			glPushMatrix();
				// glTranslated(joints[0][0], joints[0][1], joints[0][2] );
				// glRotated(rotate_angle[0], rotate_axis[0][0], rotate_axis[0][1], rotate_axis[0][2]);
				// glTranslated(0, 0, joint_raduis);
				// drawCylinder(joint_length, joint_raduis, joint_raduis);
				glLineWidth(20);
				glBegin(GL_LINES);
				  glVertex3f(joints[0][0], joints[0][1], joints[0][2]);
				  glVertex3f(joints[1][0], joints[1][1], joints[1][2]);
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslated(joints[1][0], joints[1][1], joints[1][2]);
				drawSphere(joint_raduis);
			glPopMatrix();
			glPushMatrix();
				// glTranslated(joints[1][0], joints[1][1], joints[1][2]);
				// glRotated(rotate_angle[1], rotate_axis[1][0], rotate_axis[1][1], rotate_axis[1][2]);
				// glTranslated(0, 0, joint_raduis);
				// drawCylinder(joint_length, joint_raduis, joint_raduis);
				glLineWidth(20);
				glBegin(GL_LINES);
				  glVertex3f(joints[1][0], joints[1][1], joints[1][2]);
				  glVertex3f(effector[0], effector[1], effector[2]);
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslated(effector[0], effector[1], effector[2]);
				drawSphere(joint_raduis);
			glPopMatrix();

			glPopMatrix();
		glPopMatrix();	


	glPopMatrix();
	}
	
	}
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
	controls[ROTATE_RIGHT_ARM_X] = ModelerControl("Rotate right arm X", -90, 90, 1, 0);
	controls[ROTATE_RIGHT_ARM_Y] = ModelerControl("Rotate right arm Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_Z] = ModelerControl("Rotate right arm Z", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_X] = ModelerControl("Rotate right arm lower X", -180, 180, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_Y] = ModelerControl("Rotate right arm lower Y", -45, 45, 1, 0);
	controls[ROTATE_RIGHT_ARM_L_Z] = ModelerControl("Rotate right arm lower Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_X] = ModelerControl("Rotate left arm X", -90, 90, 1, 0);
	controls[ROTATE_LEFT_ARM_Y] = ModelerControl("Rotate left arm Y", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_Z] = ModelerControl("Rotate left arm Z", -45, 45, 1, 0);
	controls[ROTATE_LEFT_ARM_L_X] = ModelerControl("Rotate left arm lower X", -180, 180, 1, 0);
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
	controls[INDIVIDUAL_LOOK] = ModelerControl("Individual look", 0, 1, 1, 0);
	controls[L_SYSTEM] = ModelerControl("L-system", 0, 1, 1, 0);
	controls[L_SYSTEM_SIZE] = ModelerControl("L-system size", 1, 5, 1, 1);
	controls[L_SYSTEM_NUM] = ModelerControl("L-system num", 0, 45, 1, 0);
	controls[MOOD_CYCLE] = ModelerControl("Mood cycle", 0, 1, 1, 0);
	controls[ANGLE_LIMIT] = ModelerControl("Angle Limit", 0, 1, 1, 0);

	controls[INVERSE_KINEMATICS] = ModelerControl("Inverse Kinematics?", 0, 1, 1, 0);
	
	controls[CSTRN_X] = ModelerControl("Constraint point X", -20, 20, 1, 0);
	controls[CSTRN_Y] = ModelerControl("Constraint point Y", -20, 20, 1, 0);
	controls[CSTRN_Z] = ModelerControl("Constraint point Z", 10, 30, 1, 15);
    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
