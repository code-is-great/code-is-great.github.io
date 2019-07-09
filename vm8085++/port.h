//      port.h

#include "byte.h"

#ifndef __PORT__
#define __PORT__

namespace mpu
{
  class Port:public Byte
  {
  public:
    Port ();
    ~Port ();

    void set_addr(int _addr);
    int get_addr() const;
  private:
    int addr;
  };

}

#endif
