//      ram.h

#include "byte.h"
#ifdef DISPLAY
#include "mp_sheet.h"
#endif

#ifndef __RAM__
#define __RAM__

namespace mpu
{
  class Ram:public std::vector < Byte >
  {
  public:
    Ram ();
    ~Ram ();
    void load (std::vector < int >_value, int _prog_loc);
    int inst_at (int loc);
    void write_at (int loc, Byte data);
#ifdef DISPLAY
    void set_mp_sheet(display::Mp_Sheet * _g_hex);
#endif
  private:
    int prog_loc;
#ifdef DISPLAY
    display::Mp_Sheet * g_hex;
#else 
    void display();
#endif
  };
}
#endif				/* __RAM__ */
