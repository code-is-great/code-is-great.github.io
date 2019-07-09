#include "label.h"

using namespace display;

#ifdef __LABEL__

Label::Label ()
{
  count++;

  name = new_name = "LABEL";
  value = new_value = "";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (std::string nm)
{
  count++;

  name = new_name = nm;
  value = new_value = "";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (std::string nm, std::string vl)
{
  count++;

  name = new_name = nm;
  value = new_value = vl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (int x, int y)
{
  count++;

  name = new_name = "LABEL";
  value = new_value = "";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (std::string nm, int x, int y)
{
  count++;

  name = new_name = nm;
  value = new_value = "";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (std::string nm, std::string vl, int x, int y)
{
  count++;

  name = new_name = nm;
  value = new_value = vl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = stdscr;
}

Label::Label (WINDOW * wn)
{
  count++;

  name = new_name = "LABEL";
  value = new_value = "";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::Label (WINDOW * wn, std::string nm)
{
  count++;

  name = new_name = nm;
  value = new_value = "";
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::Label (WINDOW * wn, std::string nm, std::string vl)
{
  count++;

  name = new_name = nm;
  value = new_value = vl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::Label (WINDOW * wn, int x, int y)
{
  count++;

  name = new_name = "LABEL";
  value = new_value = "";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::Label (WINDOW * wn, std::string nm, int x, int y)
{
  count++;

  name = new_name = nm;
  value = new_value = "";
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::Label (WINDOW * wn, std::string nm, std::string vl, int x, int y)
{
  count++;

  name = new_name = nm;
  value = new_value = vl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = wn;
}

Label::~Label ()
{
  hide ();
  count--;
  if (!isendwin ())
    endwin ();
}

void
Label::set_name (std::string nm)
{
  new_name = nm;
}

void
Label::set_value (std::string vl)
{
  new_value = vl;
}

void
Label::set_focus ()
{
  wmove (win, y_pos, x_pos + name.size () + 3);
}

void
Label::remove_focus ()
{
  wmove (win, 1, 1);
}

int
Label::get_width () const
{
  return (name.size () + value.size () + 5);
}

int
Label::get_height () const
{
  return 1;
}

std::string Label::get_value () const
{
  return value;
}

std::string Label::get_name () const
{
  return name;
}

int
Label::get_count () const
{
  return count;
}

void
Label::draw ()
{
  wmove (win, y_pos, x_pos);
  if (has_colors ())
    {
      wcolor_set (win, 2, 0);
      wprintw (win, "%s [ ", name.c_str ());
      wcolor_set (win, 7, 0);
      wprintw (win, "%s", value.c_str ());
      wcolor_set (win, 2, 0);
      wprintw (win, " ]");
      wcolor_set (win, 7, 0);
    }
  else
    wprintw (win, "%s [ %s ]", name.c_str (), value.c_str ());
  move (0, 0);
  hidden = false;
  wrefresh (win);
}

void
Label::hide ()
{
  int spc_cnt = name.size () + value.size ();
  char *spc = new char[spc_cnt + 1];
  int i = 0;

  for (i = 0; i < spc_cnt; i++)
    {
      spc[i] = ' ';
    }
  spc[i] = '\0';

  move (y_pos, x_pos);
  printw ("  %s   ", spc);
  delete[]spc;
  hidden = true;
  refresh ();
}

void
Label::update ()
{
  name = new_name;
  value = new_value;
  x_pos = new_x_pos;
  y_pos = new_y_pos;
  win = new_win;
}

#endif
