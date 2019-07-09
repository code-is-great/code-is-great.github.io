#include "vm_include.h"
#include "element.h"
#include "controlunit.h"

#ifdef __ELEMENT__

#ifndef __BUTTON__
#define __BUTTON__

namespace display
{

  class Button:public Element
  {
  public:
    Button ();
    Button (std::string lbl);
    Button (int x, int y);
      Button (std::string lbl, int x, int y);
      Button (WINDOW * wn);
      Button (WINDOW * wn, std::string lbl);
      Button (WINDOW * wn, int x, int y);
      Button (WINDOW * wn, std::string lbl, int x, int y);
     ~Button ();

    void press ();
    void set_label (const std::string lbl);
    void set_focus ();
    void remove_focus ();
    void set_controller (mpu::ControlUnit * _ctl);

    int get_width () const;
    int get_height () const;
    static int get_count ();

    void draw ();
    void hide ();
    void update ();

  protected:
      std::string label;
      std::string new_label;

    static int count;		// to count total no of buttons
  private:
      mpu::ControlUnit * ctl;
  };

}

#endif				/* __BUTTON__ */

#endif				/* __ELEMENT__ */
