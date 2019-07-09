#include "reg8bit.h"

using namespace mpu;

#ifdef __REGISTER8BIT__

Reg8Bit::Reg8Bit ()
{
  value = 0x00;
}

Reg8Bit::Reg8Bit (int _value)
{
  value = _value;
  value &= 0xff;
  accum = false;
#ifdef DISPLAY
  update_label();
#endif
}

Reg8Bit::Reg8Bit (const Byte & byte)
{
  value = byte.get ();
  value &= 0xff;
  accum = false;
#ifdef DISPLAY
  update_label();
#endif
}

Reg8Bit::Reg8Bit (const Reg8Bit & other)
{
  value = other.get ();
  value &= 0xff;
  accum = false;
#ifdef DISPLAY
  update_label();
#endif
}

Reg8Bit::~Reg8Bit ()
{
}

void
Reg8Bit::set_accum()
{
	accum = true;
}

bool
Reg8Bit::accumulator() const
{
	return accum;
}

void 
Reg8Bit::set_flag(Flag * _flag)
{
	flag = _flag;
}

void
Reg8Bit::add (const Reg8Bit & other)
{
  (*this) += other;
#ifdef DISPLAY
  update_label();
#endif
}

void
Reg8Bit::sub (const Reg8Bit & other)
{
  (*this) -= other;
#ifdef DISPLAY
  update_label();
#endif
}

void
Reg8Bit::dcr ()
{
  --(*this);
#ifdef DISPLAY
  update_label();
#endif
}

void
Reg8Bit::incr ()
{
  ++(*this);
#ifdef DISPLAY
  update_label();
#endif
}

/*
void
Reg8Bit::and (const Reg8Bit& other)
{
  (*this) &= other;
#ifdef DISPLAY
  update_label();
#endif
}

void
Reg8Bit::or (const Reg8Bit & other)
{
  (*this) |= other;
#ifdef DISPLAY
  update_label();
#endif
}
*/

void
Reg8Bit::ex_or (const Reg8Bit & other)
{
  (*this) ^= other;
#ifdef DISPLAY
  update_label();
#endif
}

Reg8Bit & Reg8Bit::operator =  (const Reg8Bit & other)
{
	this->value = other.get();
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator += (const Reg8Bit & other)
{
  int _lhs, _rhs;
  _lhs = this->value;
  _rhs = other.get();
  this->value += other.get ();
  check_and_set_flags(_lhs, _rhs);
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator -= (const Reg8Bit & other)
{
  int _lhs, _rhs;
  _lhs = this->value;
  _rhs = other.get();
  this->value -= other.get ();
  check_and_set_flags(_lhs, _rhs);
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator &= (const Reg8Bit & other)
{
  int _lhs, _rhs;
  _lhs = this->value;
  _rhs = other.get();
  this->value &= other.get ();
  check_and_set_flags(_lhs, _rhs);
  flag->reset_carry();
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator |= (const Reg8Bit & other)
{
  int _lhs, _rhs;
  _lhs = this->value;
  _rhs = other.get();
  this->value |= other.get ();
  check_and_set_flags(_lhs, _rhs);
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator ^= (const Reg8Bit & other)
{
  int _lhs, _rhs;
  _lhs = this->value;
  _rhs = other.get();
  this->value ^= other.get ();
  check_and_set_flags(_lhs, _rhs);
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator-- ()
{
  (*this) -= 1;
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

const
  Reg8Bit
Reg8Bit::operator-- (int)
{
  (*this) -= 1;
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

Reg8Bit & Reg8Bit::operator++ ()
{
  (*this) += 1;
#ifdef DISPLAY
  update_label();
#endif
  return *this;
}

const Reg8Bit&
Reg8Bit::operator++ (int)
{
  (*this) += 1;
#ifdef DISPLAY
  update_label();
#endif
  return (*this);
}

Reg8Bit & Reg8Bit::operator <<= (const int &shift)
{
  value <<= shift;
  value &= 0xff;
#ifdef DISPLAY
  update_label();
#endif
  return (*this);
}

Reg8Bit & Reg8Bit::operator >>= (const int &shift)
{
  value >>= shift;
#ifdef DISPLAY
  update_label();
#endif
  return (*this);
}

Reg8Bit
Reg8Bit::operator ! ()
     const
     {
       return ((this->value ^ 0xff) & 0xff);
     }

void
Reg8Bit::check_and_set_flags(int lhs, int rhs)
{
  int prev_carry;
  unsigned int ui = this->value;
  if(flag->carry())
  	prev_carry = 1;
  else
  	prev_carry = 0;
  if(ui > 0xff)
  {
	flag->set_carry();
  }
  else
  {
  	flag->reset_carry();
  }
  if(this->value < 0)
  {
  	flag->set_sign();
  }
  else
  {
  	flag->reset_sign();
  }
  this->value &= 0xff;
  if(this->value == 0)
  {
  	flag->set_zero();
  }
  else
  {
  	flag->reset_zero();
  }
  int parity_check;
  if(this->value & 1)
	parity_check++;
  if(this->value & 2)
	parity_check++;
  if(this->value & 4)
	parity_check++;
  if(this->value & 8)
	parity_check++;
  if(this->value & 16)
	parity_check++;
  if(this->value & 32)
	parity_check++;
  if(this->value & 64)
	parity_check++;
  if(this->value & 128)
	parity_check++;
  if(parity_check % 2)
  {
  	flag->set_parity();
  }
  else
  {
  	flag->reset_parity();
  }
  int _lhs = 0, _value = 0, isadd;
  if((lhs < value) && flag->carry())
  	isadd = 0;
  else if((lhs > value) && (!flag->carry()))
  	isadd = 0;
  else
  	isadd = 1;
  _lhs = (lhs & 0xf);
  _value = (value & 0xf);
  if((isadd) && ( _lhs > _value ))
  {
  	flag->set_aux_carry();
  }
  else
  {
  	flag->reset_aux_carry();
  }
}

bool
mpu::operator == (const Reg8Bit & one, const Reg8Bit & two)
{
  bool ret;
  if (one.value == two.value)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
mpu::operator > (const Reg8Bit & one, const Reg8Bit & two)
{
  bool
    ret;
  if (one.value > two.value)
    ret = true;
  else
    ret = false;
  return ret;
}

bool
mpu::operator < (const Reg8Bit & one, const Reg8Bit & two)
{
  bool
    ret;
  if (one.value < two.value)
    ret = true;
  else
    ret = false;
  return ret;
}

Reg8Bit
mpu::operator & (const Reg8Bit & one, const Reg8Bit & two)
{
  return (one.value & two.value);
}

Reg8Bit
mpu::operator | (const Reg8Bit & one, const Reg8Bit & two)
{
  return (one.value | two.value);
}

Reg8Bit
mpu::operator ^ (const Reg8Bit & one, const Reg8Bit & two)
{
  return (one.value ^ two.value);
}

Reg8Bit
mpu::operator + (const Reg8Bit & one, const Reg8Bit & two)
{
  return (one.get () + two.get ());
}

Reg8Bit
mpu::operator - (const Reg8Bit & one, const Reg8Bit & two)
{
  return (one.get () - two.get ());
}

Reg8Bit
mpu::operator << (const Reg8Bit & reg, const int &shift)
{
  return ((reg.value << shift) & 0xff);
}

Reg8Bit
mpu::operator >> (const Reg8Bit & reg, const int &shift)
{
  return (reg.value >> shift);
}

#endif /* __REGISTER8BIT__ */
