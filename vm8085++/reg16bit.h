#include "register.h"

#ifndef __REGISTER16BIT__
#define __REGISTER16BIT__

namespace mpu
{
  class Reg16Bit:public Register
  {
  public:
    Reg16Bit ();
    Reg16Bit (int _value);
      Reg16Bit (const Reg16Bit & other);
     ~Reg16Bit ();

  protected:
#ifdef DISPLAY
    void update_label();
#endif
  };

}

#endif				/* __REGISTER16BIT__ */
