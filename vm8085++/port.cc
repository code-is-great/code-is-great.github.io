#include "port.h"

using namespace mpu;

#ifdef __PORT__

Port::Port ()
{
  value = 0x0;
}

Port::~Port ()
{
}

void 
Port::set_addr(int _addr)
{
	addr = _addr;
}

int
Port::get_addr() const
{
	return addr;
}

#endif /* __PORT__ */
