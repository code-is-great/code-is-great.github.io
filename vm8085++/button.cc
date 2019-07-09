#include "button.h"

using namespace display;

#ifdef __BUTTON__

Button::Button ()
{
  count++;

  label = new_label = "OK";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Button::Button (std::string lbl)
{
  count++;

  label = new_label = lbl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Button::Button (int x, int y)
{
  count++;

  label = new_label = "OK";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Button::Button (std::string lbl, int x, int y)
{
  count++;

  label = new_label = lbl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Button::Button (WINDOW * wn)
{
  count++;

  label = new_label = "OK";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Button::Button (WINDOW * wn, std::string lbl)
{
  count++;

  label = new_label = lbl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Button::Button (WINDOW * wn, int x, int y)
{
  count++;

  label = new_label = "OK";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Button::Button (WINDOW * wn, std::string lbl, int x, int y)
{
  count++;

  label = new_label = lbl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Button::~Button ()
{
  hide ();
  count--;
  if (!isendwin ())
    endwin ();
}

void
Button::press ()
{
#ifdef DISPLAY
  ctl->do_this (label);
#endif
}

void
Button::set_label (std::string lbl)
{
  new_label = lbl;
}

void
Button::set_focus ()
{
  wmove (win, y_pos, x_pos);
  wrefresh (win);
  if (has_colors ())
    wcolor_set (win, 8, 0);
  draw ();
  wmove (win, y_pos, x_pos + 2);
  wrefresh (win);
}

void
Button::remove_focus ()
{
  wmove (win, y_pos, x_pos);
  wrefresh (win);
  if (has_colors ())
    wcolor_set (win, 7, 0);
  draw ();
  wmove (win, y_pos, x_pos + 2);
  wrefresh (win);
}

void
Button::set_controller (mpu::ControlUnit * _ctl)
{
  ctl = _ctl;
}

int
Button::get_width () const
{
  return (label.size () + 4);
}

int
Button::get_height () const
{
  return 1;
}

void
Button::draw ()
{
  wmove (win, y_pos, x_pos);
  wprintw (win, "[ %s ]", label.c_str ());
  move (0, 0);
  hidden = false;
  wrefresh (win);
}

void
Button::hide ()
{
  int spc_cnt = label.size ();
  char *spc = new char[spc_cnt + 1];
  int i = 0;

  for (i = 0; i < spc_cnt; i++)
    {
      spc[i] = ' ';
    }
  spc[i] = '\0';

  move (y_pos, x_pos);
  printw ("  %s  ", spc);
  delete[]spc;
  hidden = true;
  refresh ();
}

void
Button::update ()
{
  label = new_label;
  x_pos = new_x_pos;
  y_pos = new_y_pos;
  win = new_win;
}

#endif
