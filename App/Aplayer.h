// generated by Fast Light User Interface Designer (fluid) version 1.0400

#ifndef Aplayer_h
#define Aplayer_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
extern Fl_Double_Window *Window_Player;
#include <FL/Fl_Group.H>
extern Fl_Group *Group_Lyric;
#include <FL/Fl_Progress.H>
extern Fl_Group *Group_Control;
#include <FL/Fl_Box.H>
extern Fl_Box *Box_ControlBoard;
#include <FL/Fl_Button.H>
extern void Button_Play_Callback(Fl_Button*, void*);
extern Fl_Button *Button_Play;
extern void Button_NextLrc_Callback(Fl_Button*, void*);
extern Fl_Button *Button_NextLrc;
extern void Button_LastLrc_Callback(Fl_Button*, void*);
extern Fl_Button *Button_LastLrc;
extern Fl_Group *Group_Creation;
extern void Button_Create_Callback(Fl_Button*, void*);
extern Fl_Button *Button_Create;
#include <FL/Fl_Browser.H>
extern void Browser_List_Callback(Fl_Browser*, void*);
extern Fl_Browser *Browser_List;
Fl_Double_Window* make_window();
#endif
