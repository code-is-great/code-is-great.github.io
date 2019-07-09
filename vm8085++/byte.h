#include "vm_include.h"
#ifdef DISPLAY
#include "label.h"
#endif

#ifndef __BYTE__
#define __BYTE__

namespace mpu
{
  class Byte
  {
  public:
    Byte ();
    Byte (int _value);
    virtual ~Byte ();

    void reset ();
    void put (int _value);
    int get () const;

#ifdef DISPLAY
     void set_label(display::Label * _label);
#else
     void print_bin();
#endif

    friend std::ostream & operator << (std::ostream & out, const Byte & byte);
  protected:
    int value;
#ifdef DISPLAY
     display::Label * label;
    virtual void update_label();
#endif
    std::string ito_binstr(int num);
  };

  std::ostream & operator << (std::ostream & out, const Byte & byte);

}

#endif
