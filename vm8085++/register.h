#include "byte.h"

#ifndef __REGISTER__
#define __REGISTER__

namespace mpu
{
  class Register:public Byte
  {
  public:
    Register ();
    Register (int _value);
      Register (const Register & other);
     virtual ~Register ();

    virtual void incr ();

    virtual  Register & operator++ ();	// prefix operator
    virtual const Register& operator++ (int);	// postfix operator

  protected:
  };
}

#endif				/* __REGISTER__ */
