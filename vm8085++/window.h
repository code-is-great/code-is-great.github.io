#include "vm_include.h"
#include "element.h"

#ifdef __ELEMENT__

#ifndef __WINDOW__
#define __WINDOW__

namespace display
{

  class Window:public Element
  {
  public:
    Window ();
    Window (std::string tl);
    Window (int x, int y);
      Window (std::string tl, int x, int y, int w, int h);
      Window (std::string tl, int x, int y);
     ~Window ();

    void set_title (const std::string tl);
    void set_width (int w);
    void set_height (int h);

    int get_width () const;
    int get_height () const;
    WINDOW *get_win () const;

    void show_title ();
    void hide_title ();
    void draw ();
    void hide ();
    void update ();

  protected:
      std::string title;
    int width;
    int height;
      std::string new_title;
    int new_width;
    int new_height;

    static int count;		// to count total no of windows

  };

}

#endif				/* __WINDOW__ */

#endif				/* __ELEMENT__ */
