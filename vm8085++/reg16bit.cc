#include "reg16bit.h"

using namespace mpu;

#ifdef __REGISTER16BIT__

Reg16Bit::Reg16Bit ()
{
  value = 0x00;
}

Reg16Bit::Reg16Bit (int _value)
{
  value = _value;
}

Reg16Bit::Reg16Bit (const Reg16Bit & other)
{
  value = other.get ();
}

Reg16Bit::~Reg16Bit ()
{
}

#ifdef DISPLAY
void
Reg16Bit::update_label()
{
	char s[5];
	sprintf(s, "%04x", this->get());
	label->set_value((std::string)s);
	label->update();
}
#endif

#endif /* __REGISTER16BIT__ */
