//      flag.h

#include "byte.h"

#ifndef __FLAG__
#define __FLAG__

namespace mpu
{
  class Flag:public Byte
  {
  public:
    Flag ();
    Flag (int _value);
     ~Flag ();

    void set_zero ();
    void reset_zero ();
    void set_carry ();
    void reset_carry ();
    void set_sign ();
    void reset_sign ();
    void set_parity ();
    void reset_parity ();
    void set_aux_carry ();
    void reset_aux_carry ();

    bool zero () const;
    bool carry () const;
    bool sign () const;
    bool parity () const;
    bool aux_carry () const;
private:
#ifdef DISPLAY
    void update_label();
#endif
  };

}

#endif
