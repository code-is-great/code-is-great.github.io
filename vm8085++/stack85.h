#include "vm_include.h"
#include "ram.h"
#include "byte.h"
#include "reg16bit.h"

#ifndef __STACK__
#define __STACK__

namespace mpu
{
  class Stack
  {
  public:
    Stack ();
    ~Stack ();

    void push(const Byte& _value);
    Byte& pop();
    void set_stack(int _addr);

    void set_ram(Ram * _ram);
    void set_sp(Reg16Bit * _sp);
  protected:

    Ram * ram;
    Reg16Bit * sp;
    int addr;
  };

}

#endif
