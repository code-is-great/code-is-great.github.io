#include "vm_include.h"
#include "grid.h"

#ifdef __GRID__

#ifndef __MP_SHEET__
#define __MP_SHEET__

namespace display
{

  class Mp_Sheet:public Grid
  {
  public:
    Mp_Sheet ();
    ~Mp_Sheet ();

    void draw ();
    void update ();
    void load(int _hex, int loc, ...);
    void reset();
    void draw_arrow();

  protected:
    static int count;		// to count total no of Mp_Sheets
  private:
    int ptr_loc;

  };

}

#endif				/* __MP_SHEET__ */

#endif				/* __GRID__ */
