#include "register.h"
#include "flag.h"

#ifndef __REGISTER8BIT__
#define __REGISTER8BIT__

namespace mpu
{
  class Reg8Bit:public Register
  {
  public:
    Reg8Bit ();
    Reg8Bit (int _value);
    Reg8Bit (const Byte & byte);
    Reg8Bit (const Reg8Bit & other);
    ~Reg8Bit ();

    void set_accum();
    bool accumulator() const;
    void set_flag(Flag * _flag);

    void add (const Reg8Bit & other);
    void sub (const Reg8Bit & other);
    void dcr ();
    void incr ();

    //void and (const Reg8Bit& other);
    //void or (const Reg8Bit& other);
    void ex_or (const Reg8Bit& other);

    Reg8Bit& operator = (const Reg8Bit & other);
    Reg8Bit& operator += (const Reg8Bit & other);
    Reg8Bit& operator -= (const Reg8Bit & other);
    Reg8Bit& operator &= (const Reg8Bit & other);
    Reg8Bit& operator |= (const Reg8Bit & other);
    Reg8Bit& operator ^= (const Reg8Bit & other);
    Reg8Bit& operator-- ();	// prefix operator
    const Reg8Bit operator-- (int);	// postfix operator
    Reg8Bit& operator++ ();	// prefix operator
    const Reg8Bit& operator++ (int);	// postfix operator
    Reg8Bit& operator <<= (const int &shift);
    Reg8Bit& operator >>= (const int &shift);
    Reg8Bit operator ! () const;

    friend bool operator == (const Reg8Bit & one, const Reg8Bit & two);
    friend bool operator > (const Reg8Bit & one, const Reg8Bit & two);
    friend bool operator < (const Reg8Bit & one, const Reg8Bit & two);

    friend Reg8Bit operator ^ (const Reg8Bit & one, const Reg8Bit & two);
    friend Reg8Bit operator & (const Reg8Bit & one, const Reg8Bit & two);
    friend Reg8Bit operator | (const Reg8Bit & one, const Reg8Bit & two);
    friend Reg8Bit operator + (const Reg8Bit & one, const Reg8Bit & two);
    friend Reg8Bit operator - (const Reg8Bit & one, const Reg8Bit & two);
    friend Reg8Bit operator << (const Reg8Bit & reg, const int &shift);
    friend Reg8Bit operator >> (const Reg8Bit & reg, const int &shift);

  private:
    bool accum;
    Flag * flag;

    void check_and_set_flags(int lhs, int rhs);
  };

  bool operator == (const Reg8Bit & one, const Reg8Bit & two);
  bool operator > (const Reg8Bit & one, const Reg8Bit & two);
  bool operator < (const Reg8Bit & one, const Reg8Bit & two);

  Reg8Bit operator ^ (const Reg8Bit & one, const Reg8Bit & two);
  Reg8Bit operator & (const Reg8Bit & one, const Reg8Bit & two);
  Reg8Bit operator | (const Reg8Bit & one, const Reg8Bit & two);
  Reg8Bit operator + (const Reg8Bit & one, const Reg8Bit & two);
  Reg8Bit operator - (const Reg8Bit & one, const Reg8Bit & two);
  Reg8Bit operator << (const Reg8Bit & reg, const int &shift);
  Reg8Bit operator >> (const Reg8Bit & reg, const int &shift);
}

#endif				/* __REGISTER__ */
