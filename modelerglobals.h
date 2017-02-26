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
	XPOS, YPOS, ZPOS, HEIGHT, ROTATE, LIGHT_POS_X, LIGHT_POS_Y, LIGHT_POS_Z, LIGHT_INTENSITY, ROTATE_HEAD_X, ROTATE_HEAD_Y, ROTATE_HEAD_Z, ROTATE_HEAD_DEC, NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f
#define COLOR_WHITE		1.0f, 1.0f, 1.0f
#define COLOR_YELLOW	1.0f, 1.0f, 0.0f
#define COLOR_PURPLE	1.0f, 0.0f, 1.0f
#define COLOR_CYAN		0.0f, 1.0f, 1.0f
#define COLOR_GRAY		0.5f, 0.5f, 0.5f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))

#endif