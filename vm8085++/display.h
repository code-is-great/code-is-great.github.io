#include "window.h"
#include "grid.h"
#include "mp_sheet.h"
#include "label.h"
#include "button.h"
#include "controlunit.h"

#ifndef __DISPLAY__
#define __DISPLAY__

namespace display
{
  class Display
  {
  public:
    Display ();
    ~Display ();

    void show ();
    void hide ();
    void draw_grid ();
    void update_labels();

    void set_focus (std::string element);
    void next_focus ();
    std::string focus_on ();
    void remove_focus (std::string element);
    void set_controller (mpu::ControlUnit * _ctl);
    void scroll_down();
    void scroll_up();

    WINDOW *get_ctl_win ();
    Mp_Sheet * get_mp_sheet();
    Element *get_element (std::string element);
    Label *get_label (std::string element);

  private:
      Window w_main;
    Grid g_reg;
    Grid g_ctl;
    Mp_Sheet g_hex;
    Label a;
    Label flag;
    Label b;
    Label c;
    Label d;
    Label e;
    Label h;
    Label l;
    Label pc;
    Label sp;
    Button load;
    Button start;
    Button stop;
    Button next;
    Button exit;
    Label file;
    Label prog_loc;

    int space;
    enum
    { NOTFOUND, LOAD, START, STOP, NEXT, EXIT, FILE, PROG_LOC,
    REGA, REGB, REGC, REGD, REGE, REGH, REGL, SP, PC, FLAG };
    int focus;

      mpu::ControlUnit * ctl;
  };

}

#endif
