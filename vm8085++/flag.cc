#include "flag.h"

using namespace mpu;

#ifdef __FLAG__

Flag::Flag ()
{
  value = 0x00;
}

Flag::Flag (int _value)
{
  value = (_value & 0xff);
}

Flag::~Flag ()
{
}

void
Flag::set_zero ()
{
  value = (value & 0xff);
  value |= 0x40;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::reset_zero ()
{
  value = (value & 0xff);
  value &= 0xbf;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::set_carry ()
{
  value = (value & 0xff);
  value |= 0x01;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::reset_carry ()
{
  value = (value & 0xff);
  value &= 0xfe;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::set_sign ()
{
  value = (value & 0xff);
  value |= 0x80;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::reset_sign ()
{
  value = (value & 0xff);
  value &= 0x7f;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::set_parity ()
{
  value = (value & 0xff);
  value |= 0x04;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::reset_parity ()
{
  value = (value & 0xff);
  value &= 0xfb;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::set_aux_carry ()
{
  value = (value & 0xff);
  value |= 0x10;
#ifdef DISPLAY
  update_label();
#endif
}

void
Flag::reset_aux_carry ()
{
  value = (value & 0xff);
  value &= 0xef;
#ifdef DISPLAY
  update_label();
#endif
}

bool
Flag::zero () const
{
  bool ret;
  if (value & 0x40)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
Flag::carry () const
{
  bool ret;
  if (value & 0x01)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
Flag::sign () const
{
  bool ret;
  if (value & 0x80)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
Flag::parity () const
{
  bool ret;
  if (value & 0x04)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
Flag::aux_carry () const
{
  bool ret;
  if (value & 0x10)
    ret = true;
  else
    ret = false;
  return ret;
}

#ifdef DISPLAY
void
Flag::update_label()
{
	char s[9];
	sprintf(s, "%s", ito_binstr(this->get()).c_str());
	label->set_value((std::string)s);
	label->update();
}
#endif /* DISPLAY */

#endif /* __FLAG__ */
