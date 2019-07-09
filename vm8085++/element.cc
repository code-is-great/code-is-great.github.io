#include "element.h"

using namespace display;

#ifdef __ELEMENT__

Element::Element ()
{
  x_pos = 0;
  y_pos = 0;
  new_x_pos = 0;
  new_y_pos = 0;
  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = stdscr;
}

Element::Element (int x, int y)
{
  x_pos = x;
  y_pos = y;
  new_x_pos = x;
  new_y_pos = y;
  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = stdscr;
}

Element::~Element ()
{
  if (!isendwin ())
    endwin ();
}

void
Element::set_xy (int x, int y)
{
  new_x_pos = x;
  new_y_pos = y;
}

void
Element::set_win (WINDOW * wn)
{
  new_win = wn;
}

void
Element::disable()
{
	dis = true;
}

void
Element::enable()
{
	dis = false;
}

int
Element::get_x () const
{
  return x_pos;
}

int
Element::get_y () const
{
  return x_pos;
}

bool
Element::disabled() const
{
	return dis;
}

WINDOW *
Element::get_win (WINDOW * wn)
{
  return win;
}

void
Element::redraw ()
{
  hide ();
  update ();
  draw ();
}

#endif
