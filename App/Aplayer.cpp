// generated by Fast Light User Interface Designer (fluid) version 1.0400

#include "Aplayer.h"

Fl_Double_Window *Window_Player=(Fl_Double_Window *)0;

Fl_Group *Group_Lyric=(Fl_Group *)0;

Fl_Group *Group_Control=(Fl_Group *)0;

Fl_Box *Box_ControlBoard=(Fl_Box *)0;

Fl_Button *Button_Play=(Fl_Button *)0;

Fl_Button *Button_NextLrc=(Fl_Button *)0;

Fl_Button *Button_LastLrc=(Fl_Button *)0;

Fl_Group *Group_Creation=(Fl_Group *)0;

Fl_Button *Button_Create=(Fl_Button *)0;

Fl_Browser *Browser_List=(Fl_Browser *)0;

Fl_Double_Window* make_window() {
  { Window_Player = new Fl_Double_Window(1080, 574, "VOA player");
    Window_Player->box(FL_GLEAM_UP_BOX);
    Window_Player->color((Fl_Color)246);
    { Group_Lyric = new Fl_Group(10, 20, 710, 480);
      Group_Lyric->end();
    } // Fl_Group* Group_Lyric
    { Fl_Progress* o = new Fl_Progress(15, 505, 700, 10);
      o->box(FL_PLASTIC_ROUND_UP_BOX);
    } // Fl_Progress* o
    { Group_Control = new Fl_Group(15, 515, 700, 50);
      Group_Control->align(Fl_Align(FL_ALIGN_CENTER));
      { Box_ControlBoard = new Fl_Box(15, 520, 700, 40);
        Box_ControlBoard->box(FL_GLEAM_THIN_UP_BOX);
        Box_ControlBoard->color((Fl_Color)246);
        Box_ControlBoard->labelcolor((Fl_Color)197);
        Box_ControlBoard->align(Fl_Align(FL_ALIGN_TEXT_OVER_IMAGE));
      } // Fl_Box* Box_ControlBoard
      { Button_Play = new Fl_Button(345, 525, 40, 30, "@+2>");
        Button_Play->box(FL_PLASTIC_UP_BOX);
        Button_Play->color((Fl_Color)97);
        Button_Play->labelcolor((Fl_Color)109);
        Button_Play->callback((Fl_Callback*)Button_Play_Callback);
      } // Fl_Button* Button_Play
      { Fl_Button* o = new Fl_Button(310, 525, 35, 30, "@<<");
        o->box(FL_PLASTIC_UP_BOX);
        o->color((Fl_Color)239);
        o->labelcolor((Fl_Color)191);
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(385, 525, 35, 30, "@>>");
        o->box(FL_PLASTIC_UP_BOX);
        o->color((Fl_Color)239);
        o->labelcolor((Fl_Color)191);
      } // Fl_Button* o
      { Button_NextLrc = new Fl_Button(420, 525, 60, 30, "@+2->");
        Button_NextLrc->box(FL_PLASTIC_UP_BOX);
        Button_NextLrc->color(FL_DARK_CYAN);
        Button_NextLrc->labelcolor((Fl_Color)132);
        Button_NextLrc->callback((Fl_Callback*)Button_NextLrc_Callback);
      } // Fl_Button* Button_NextLrc
      { Button_LastLrc = new Fl_Button(250, 525, 60, 30, "@+2<-");
        Button_LastLrc->box(FL_PLASTIC_UP_BOX);
        Button_LastLrc->color(FL_DARK_CYAN);
        Button_LastLrc->labelcolor((Fl_Color)132);
        Button_LastLrc->callback((Fl_Callback*)Button_LastLrc_Callback);
      } // Fl_Button* Button_LastLrc
      Group_Control->end();
    } // Fl_Group* Group_Control
    { Fl_Group* o = new Fl_Group(730, 15, 340, 555);
      { Group_Creation = new Fl_Group(730, 15, 330, 40);
        { Fl_Box* o = new Fl_Box(730, 20, 330, 30, "Create a list");
          o->box(FL_GTK_DOWN_BOX);
          o->color(FL_LIGHT3);
        } // Fl_Box* o
        { Button_Create = new Fl_Button(1025, 20, 35, 30, "@fileopen");
          Button_Create->box(FL_GTK_UP_BOX);
          Button_Create->down_box(FL_GTK_UP_BOX);
          Button_Create->color(FL_LIGHT3);
          Button_Create->labelcolor((Fl_Color)174);
          Button_Create->callback((Fl_Callback*)Button_Create_Callback);
        } // Fl_Button* Button_Create
        Group_Creation->end();
      } // Fl_Group* Group_Creation
      { Browser_List = new Fl_Browser(730, 55, 330, 505);
        Browser_List->type(2);
        Browser_List->box(FL_GTK_DOWN_BOX);
        Browser_List->selection_color((Fl_Color)6);
        Browser_List->callback((Fl_Callback*)Browser_List_Callback);
      } // Fl_Browser* Browser_List
      o->end();
    } // Fl_Group* o
    Window_Player->end();
  } // Fl_Double_Window* Window_Player
  return Window_Player;
}
