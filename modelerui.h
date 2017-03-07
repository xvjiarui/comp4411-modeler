// generated by Fast Light User Interface Designer (fluid) version 1.00

#ifndef modelerui_h
#define modelerui_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include "modelerview.h"
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Message.H>
#include "bitmap.h"
#include "modelerdraw.h"
#include <FL/Fl_Browser.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Pack.H>
#include "modelerapp.h"

class ModelerUserInterface {
public:
  ModelerUserInterface();
  Fl_Window *m_controlsWindow;
private:
  inline void cb_m_controlsWindow_i(Fl_Window*, void*);
  static void cb_m_controlsWindow(Fl_Window*, void*);
public:
  Fl_Menu_Bar *m_controlsMenuBar;
  static Fl_Menu_Item menu_m_controlsMenuBar[];
private:
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_Save1_i(Fl_Menu_*, void*);
  static void cb_Save1(Fl_Menu_*, void*);
// IANLI - 10/9/2001
// callback functions for saving the position of the model.
  inline void cb_SavePos_i(Fl_Menu_*, void*);
  static void cb_SavePos(Fl_Menu_*, void*);
  inline void cb_OpenPos_i(Fl_Menu_*, void*);
  static void cb_OpenPos(Fl_Menu_*, void*);

  inline void cb_Exit_i(Fl_Menu_*, void*);
  static void cb_Exit(Fl_Menu_*, void*);
  inline void cb_Normal_i(Fl_Menu_*, void*);
  static void cb_Normal(Fl_Menu_*, void*);
  inline void cb_Flat_i(Fl_Menu_*, void*);
  static void cb_Flat(Fl_Menu_*, void*);
  inline void cb_Wireframe_i(Fl_Menu_*, void*);
  static void cb_Wireframe(Fl_Menu_*, void*);
  inline void cb_High_i(Fl_Menu_*, void*);
  static void cb_High(Fl_Menu_*, void*);
  inline void cb_Medium_i(Fl_Menu_*, void*);
  static void cb_Medium(Fl_Menu_*, void*);
  inline void cb_Low_i(Fl_Menu_*, void*);
  static void cb_Low(Fl_Menu_*, void*);
  inline void cb_Poor_i(Fl_Menu_*, void*);
  static void cb_Poor(Fl_Menu_*, void*);
  inline void cb_FrameAll_i(Fl_Menu_*, void*);
  static void cb_FrameAll(Fl_Menu_*, void*);
private:
  inline void cb_Focus_i(Fl_Menu_*, void*);
  static void cb_Focus(Fl_Menu_*, void*);
public:
  static Fl_Menu_Item *m_controlsAnimOnMenu;
private:
  inline void cb_m_controlsAnimOnMenu_i(Fl_Menu_*, void*);
  static void cb_m_controlsAnimOnMenu(Fl_Menu_*, void*);
public:
  Fl_Browser *m_controlsBrowser;
private:
  inline void cb_m_controlsBrowser_i(Fl_Browser*, void*);
  static void cb_m_controlsBrowser(Fl_Browser*, void*);
public:
  Fl_Scroll *m_controlsScroll;
  Fl_Pack *m_controlsPack;
  Fl_Window *m_modelerWindow;
private:
  inline void cb_m_modelerWindow_i(Fl_Window*, void*);
  static void cb_m_modelerWindow(Fl_Window*, void*);
public:
  ModelerView *m_modelerView;
  void show();
};
#endif
