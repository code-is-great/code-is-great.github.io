#include "vm_include.h"

#ifndef __ELEMENT__
#define __ELEMENT__

namespace display
{

  class Element
  {
  public:
    Element ();
    Element (int x, int y);
    virtual ~ Element ();

    void set_xy (int x, int y);
    void set_win (WINDOW * wn);
    void disable();
    void enable();

    int get_x () const;
    int get_y () const;
    WINDOW *get_win (WINDOW * wn);
    virtual int get_width () const = 0;
    virtual int get_height () const = 0;
    bool disabled() const;

    virtual void draw () = 0;
    virtual void hide () = 0;
    virtual void update () = 0;
    void redraw ();

    static void backspace (WINDOW * _win);

  protected:
      WINDOW * win;
    WINDOW *new_win;
    int x_pos, y_pos;
    int new_x_pos, new_y_pos;

    bool hidden;
    bool dis;
    static void init ();
  };

}

#endif
