#include "byte.h"

using namespace mpu;

#ifdef __BYTE__

Byte::Byte ()
{
  value = 0x0;
}

Byte::Byte (int _value)
{
  value = _value;
}

Byte::~Byte ()
{
}

void
Byte::reset ()
{
  value = 0x00;
}

void
Byte::put (int _value)
{
  value = _value;
#ifdef DISPLAY
  update_label();
#endif
}

#ifdef DISPLAY
void
Byte::update_label()
{
	char s[3];
	sprintf(s, "%02x", this->get());
	label->set_value((std::string)s);
	label->update();
}
#endif

#ifndef DISPLAY

void
Byte::print_bin()
{
	std::cout << ito_binstr(value);
}

#endif

int
Byte::get () const
{
  return value;
}

#ifdef DISPLAY
void
Byte::set_label(display::Label * _label)
{
	label = _label;
}
#endif

	std::string
Byte::ito_binstr(int num)
{
	char binary[9];
	int rem;
	int i;
	
	for(i = 0;i < 7;i++)
	{
		binary[i] = '0';
	}
	binary[8] = '\0';
	i = 7;
	do
	{
		rem = num%2;	
		num = num/2;
		if(rem == 0)
			binary[i--] = '0';
		else
			binary[i--] = '1';
	}while(num != 0);
	return (std::string)binary;
}

std::ostream & mpu::operator << (std::ostream & out, const Byte & byte)
{
  out.setf (std::ios::showbase);
  out.setf (std::ios::hex, std::ios::basefield);
  out << byte.get ();
  out.unsetf (std::ios::hex);
  out.unsetf (std::ios::showbase);

  return out;
}

#endif /* __BYTE__ */
