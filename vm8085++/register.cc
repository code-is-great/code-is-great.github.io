#include "register.h"

using namespace mpu;

#ifdef __REGISTER__

Register::Register ()
{
  value = 0x00;
}

Register::Register (int _value)
{
  value = _value;
}

Register::Register (const Register & other)
{
  this->value = other.get ();
}

Register::~Register ()
{
}

void
Register::incr ()
{
  (*this)++;
}

Register & Register::operator++ ()
{
  this->value++;
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

const Register&
Register::operator++ (int)
{
  this->value++;
#ifdef DISPLAY
  update_label();
#endif
  return (*this);
}

#endif /* __REGISTER__ */
