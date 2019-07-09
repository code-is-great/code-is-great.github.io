#include "vm_include.h"
#include "element.h"

#ifdef __ELEMENT__

#ifndef __LABEL__
#define __LABEL__

namespace display
{
  class Label:public Element
  {
  public:
    Label ();
    Label (std::string nm);
    Label (std::string nm, std::string vl);
    Label (int x, int y);
      Label (std::string nm, int x, int y);
      Label (std::string nm, std::string vl, int x, int y);
      Label (WINDOW * wn);
      Label (WINDOW * wn, std::string nm);
      Label (WINDOW * wn, std::string nm, std::string vl);
      Label (WINDOW * wn, int x, int y);
      Label (WINDOW * wn, std::string nm, int x, int y);
      Label (WINDOW * wn, std::string nm, std::string vl, int x, int y);
     ~Label ();

    void set_name (const std::string nm);
    void set_value (const std::string vl);
    void set_focus ();
    void remove_focus ();

    int get_width () const;
    int get_height () const;
    std::string get_value () const;
    std::string get_name () const;
    int get_count () const;

    void draw ();
    void hide ();
    void update ();

  protected:
      std::string name;
      std::string value;
      std::string new_name;
      std::string new_value;

    static int count;		// to count total no of labels

  };

}

#endif				/* __LABEL__ */

#endif				/* __ELEMENT__ */
