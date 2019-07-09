#include "stack85.h"

using namespace mpu;

#ifdef __STACK__

Stack::Stack ()
{
	addr = 0xffff;
}

Stack::~Stack ()
{
}

void Stack::push(const Byte& _value)
{
	addr--;
	sp->put(addr);
	ram->write_at(addr, _value);
}

Byte& Stack::pop()
{
	Byte& ret = (*ram)[addr];

	/*
	AS THE CONTENTS OF THE RAM ARE NOT CHANGED BY
	POP INSTRUCTION THE ERASE PART IS NOW COMMENTED
	*/
	//ram->erase(ram->begin() + addr);

	(*sp)++;
	addr++;
	return ret;
}

void Stack::set_stack(int _addr)
{
	addr = _addr;
	sp->put(_addr);
}

void Stack::set_ram(Ram * _ram)
{
	ram = _ram;
}

void Stack::set_sp(Reg16Bit * _sp)
{
	sp = _sp;
}

#endif /* __STACK__ */
