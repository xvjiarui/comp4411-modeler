#ifndef _MODELER_GLOBALS_H
#define _MODELER_GLOBALS_H

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif

// This is a list of the controls for the SampleModel
// We'll use these constants to access the values 
// of the controls from the user interface.
enum SampleModelControls
{ 
	XPOS, YPOS, ZPOS, HEIGHT, ROTATE, 
	LIGHT0_POS_X, LIGHT0_POS_Y, LIGHT0_POS_Z, LIGHT0_INTENSITY, 
	LIGHT1_POS_X, LIGHT1_POS_Y, LIGHT1_POS_Z, LIGHT1_INTENSITY, 
	ROTATE_HEAD_X, ROTATE_HEAD_Y, ROTATE_HEAD_Z, 
	ROTATE_HEAD_DEC, 
	ROTATE_RIGHT_ARM_X, ROTATE_RIGHT_ARM_Y, ROTATE_RIGHT_ARM_Z, 
	ROTATE_RIGHT_ARM_L_X, ROTATE_RIGHT_ARM_L_Y, ROTATE_RIGHT_ARM_L_Z, 
	ROTATE_LEFT_ARM_X, ROTATE_LEFT_ARM_Y, ROTATE_LEFT_ARM_Z,
	ROTATE_LEFT_ARM_L_X, ROTATE_LEFT_ARM_L_Y, ROTATE_LEFT_ARM_L_Z, 
	ROTATE_RIGHT_LEG_X, ROTATE_RIGHT_LEG_Y, ROTATE_RIGHT_LEG_Z, 
	ROTATE_RIGHT_LEG_L_X, ROTATE_RIGHT_LEG_L_Y, ROTATE_RIGHT_LEG_L_Z, 
	ROTATE_RIGHT_FOOT_X, ROTATE_RIGHT_FOOT_Y, ROTATE_RIGHT_FOOT_Z,  
	ROTATE_LEFT_LEG_X, ROTATE_LEFT_LEG_Y, ROTATE_LEFT_LEG_Z, 
	ROTATE_LEFT_LEG_L_X, ROTATE_LEFT_LEG_L_Y, ROTATE_LEFT_LEG_L_Z, 
	ROTATE_LEFT_FOOT_X, ROTATE_LEFT_FOOT_Y, ROTATE_LEFT_FOOT_Z,  
	NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 0.7f
#define COLOR_WHITE		1.0f, 1.0f, 1.0f
#define COLOR_YELLOW	1.0f, 1.0f, 0.0f
#define COLOR_PURPLE	1.0f, 0.0f, 1.0f
#define COLOR_CYAN		0.0f, 1.0f, 1.0f
#define COLOR_GRAY		0.5f, 0.5f, 0.5f
#define COLOR_GREY		0.7f, 0.7f, 0.7f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif