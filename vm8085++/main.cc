#include "8085microprocessor.h"


//ofstream debug("debug_file");

using namespace mpu;

int
main (int argc, char * argv[])
{
  int screen_rows;

  if(argc > 1)
  	screen_rows = atoi(argv[1]);
  else 
  	screen_rows = 25;
  Processor mp(screen_rows);
  mp.start ();
//  debug.close();
  return 0;
}
