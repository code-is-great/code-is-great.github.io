#include "grid.h"

using namespace display;

#ifdef __GRID__

Grid::Grid ()
{
	std::string init_title ("GRID");
  init_title += ((count++) + 48);

  title = new_title = init_title;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;
  width = new_width = COLS;
  height = new_height = LINES;
  rows = new_rows = 2;
  cols = new_cols = 2;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      rows_height[i] = new_rows_height[i] = (height - 1) / rows;
    }
  free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
  new_rows_height[0] += free_row_space;
  rows_height[0] = new_rows_height[0];
  for (i = 0; i < cols; i++)
    {
      cols_width[i] = new_cols_width[i] = width / cols;
    }
  free_col_space = width - cols * (int) (width / cols);
  new_cols_width[cols - 1] += free_col_space;
  cols_width[cols - 1] = new_cols_width[cols - 1];

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Grid::Grid (std::string tl)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;
  width = new_width = COLS;
  height = new_height = LINES;
  rows = new_rows = 2;
  cols = new_cols = 2;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      rows_height[i] = new_rows_height[i] = (height - 1) / rows;
    }
  free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
  new_rows_height[0] += free_row_space;
  rows_height[0] = new_rows_height[0];
  for (i = 0; i < cols; i++)
    {
      cols_width[i] = new_cols_width[i] = width / cols;
    }
  free_col_space = width - cols * (int) (width / cols);
  new_cols_width[cols - 1] += free_col_space;
  cols_width[cols - 1] = new_cols_width[cols - 1];

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Grid::Grid (int r, int c)
{
	std::string init_title ("GRID");
  init_title += ((count++) + 48);

  title = new_title = init_title;
  x_pos = new_x_pos = 0;
  y_pos = new_y_pos = 0;
  width = new_width = COLS;
  height = new_height = LINES;
  rows = new_rows = r;
  cols = new_cols = c;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      rows_height[i] = new_rows_height[i] = (height - 1) / rows;
    }
  free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
  new_rows_height[0] += free_row_space;
  rows_height[0] = new_rows_height[0];
  for (i = 0; i < cols; i++)
    {
      cols_width[i] = new_cols_width[i] = width / cols;
    }
  free_col_space = width - cols * (int) (width / cols);
  new_cols_width[cols - 1] += free_col_space;
  cols_width[cols - 1] = new_cols_width[cols - 1];

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Grid::Grid (std::string tl, int x, int y, int w, int h)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;
  width = new_width = w;
  height = new_height = h;
  rows = new_rows = 2;
  cols = new_cols = 2;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      rows_height[i] = new_rows_height[i] = (height - 1) / rows;
    }
  free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
  new_rows_height[0] += free_row_space;
  rows_height[0] = new_rows_height[0];
  for (i = 0; i < cols; i++)
    {
      cols_width[i] = new_cols_width[i] = width / cols;
    }
  free_col_space = width - cols * (int) (width / cols);
  new_cols_width[cols - 1] += free_col_space;
  cols_width[cols - 1] = new_cols_width[cols - 1];

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Grid::Grid (std::string tl, int x, int y, int w, int h, int r, int c)
{
  count++;

  title = new_title = tl;
  x_pos = new_x_pos = x;
  y_pos = new_y_pos = y;
  width = new_width = w;
  height = new_height = h;
  rows = new_rows = r;
  cols = new_cols = c;
  cols_width = new int[cols];
  rows_height = new int[rows];
  new_cols_width = new int[cols];
  new_rows_height = new int[rows];
  int i = 0;
  for (i = 0; i < rows; i++)
    {
      rows_height[i] = new_rows_height[i] = (height - 1) / rows;
    }
  free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
  new_rows_height[0] += free_row_space;
  rows_height[0] = new_rows_height[0];
  for (i = 0; i < cols; i++)
    {
      cols_width[i] = new_cols_width[i] = width / cols;
    }
  free_col_space = width - cols * (int) (width / cols);
  new_cols_width[cols - 1] += free_col_space;
  cols_width[cols - 1] = new_cols_width[cols - 1];

  hidden = true;

	/***********NON CURSES VARIABLES ABOVE THIS**********/
  init ();
  win = new_win = newwin (height, width, y_pos, x_pos);
}

Grid::~Grid ()
{
  count--;
  delete[]new_cols_width;
  delete[]new_rows_height;
  delete[]rows_height;
  delete[]cols_width;
  hide ();
  if (!isendwin ())
    endwin ();
}

void
Grid::set_rows (int r)
{
  new_rows = r;
}

void
Grid::set_cols (int c)
{
  new_cols = c;
}

void
Grid::set_cols_width (int c, int w)
{
  new_cols_width[c] = w;
}

void
Grid::set_rows_height (int r, int h)
{
  new_rows_height[r] = h;
}

void
Grid::write (std::string s, int r, int c)
{
  wmove (win, r + 2, c + 1);
  wprintw (win, "%s", s.c_str ());
  move (0, 0);
  wrefresh (win);
}

int
Grid::get_rows ()
{
  return rows;
}

int
Grid::get_cols ()
{
  return cols;
}

int
Grid::get_cols_width (int c)
{
  return cols_width[c];
}

int
Grid::get_rows_height (int r)
{
  return rows_height[r];
}

	std::string
Grid::read (int r, int c)
{
  return "0";
}

void
Grid::hide_grid ()
{
  int i = 0, h_pos = 0, v_pos = 0;

  for (i = 0; i < (cols - 1); i++)
    {
      h_pos += cols_width[i];
      if (h_pos < width)
	{
	  wmove (win, 1, h_pos);
	  waddch (win, ACS_VLINE);
	  wmove (win, 2, h_pos);
	  wvline (win, ' ', (height - 3));
	  wmove (win, height - 1, h_pos);
	  waddch (win, ACS_VLINE);
	}
    }
  for (i = 0; i < (rows - 1); i++)
    {
      v_pos += rows_height[i];
      if (v_pos < (height - rows_height[i]))
	{
	  wmove (win, v_pos, 0);
	  waddch (win, ACS_HLINE);
	  wmove (win, v_pos, 1);
	  whline (win, ' ', (width - 2));
	  wmove (win, v_pos, width - 1);
	  waddch (win, ACS_HLINE);
	}
    }
  int j = 0;
  h_pos = v_pos = 0;
  for (i = 0; i < (cols - 1); i++)
    {
      h_pos += cols_width[i];
      if (h_pos < width)
	{
	  for (j = 0; j < (rows - 1); j++)
	    {
	      v_pos += rows_height[j];
	      if (v_pos < (height - rows_height[i]))
		{
		  wmove (win, v_pos, h_pos);
		  waddch (win, ' ');
		}
	    }
	}
      v_pos = 0;
    }

  wrefresh (win);
}

void
Grid::show_grid ()
{
  int i = 0;
  int lowest = cols_width[0];

  for (i = 0; i < cols; i++)
    {
      if (cols_width[i] < lowest)
	lowest = cols_width[i];
    }
  assert (lowest >= 2);

  lowest = rows_height[0];
  for (i = 0; i < rows; i++)
    {
      if (rows_height[i] < lowest)
	lowest = rows_height[i];
    }
  assert (lowest >= 2);

  wmove (win, 1, 0);
  waddch (win, ACS_LTEE);
  wmove (win, 1, 1);
  whline (win, ACS_HLINE, width - 2);
  wmove (win, 1, width - 1);
  waddch (win, ACS_RTEE);

  int h_pos = 0, v_pos = 0;
  for (i = 0; i < (cols - 1); i++)
    {
      h_pos += cols_width[i];
      if (h_pos < width)
	{
	  wmove (win, 1, h_pos);
	  waddch (win, ACS_TTEE);
	  wmove (win, 2, h_pos);
	  wvline (win, ACS_VLINE, (height - 3));
	  wmove (win, height - 1, h_pos);
	  waddch (win, ACS_BTEE);
	}
    }
  for (i = 0; i < (rows - 1); i++)
    {
      v_pos += rows_height[i];
      if (v_pos < (height - rows_height[i]))
	{
	  wmove (win, v_pos, 0);
	  waddch (win, ACS_LTEE);
	  wmove (win, v_pos, 1);
	  whline (win, ACS_HLINE, (width - 2));
	  wmove (win, v_pos, width - 1);
	  waddch (win, ACS_RTEE);
	}
    }
  int j = 0;
  h_pos = v_pos = 0;
  for (i = 0; i < (cols - 1); i++)
    {
      h_pos += cols_width[i];
      if (h_pos < width)
	{
	  for (j = 0; j < (rows - 1); j++)
	    {
	      v_pos += rows_height[j];
	      if (v_pos < (height - rows_height[j]))
		{
		  wmove (win, v_pos, h_pos);
		  waddch (win, ACS_PLUS);
		}
	    }
	}
      v_pos = 0;
    }

  wrefresh (win);
}

void
Grid::draw ()
{
  wborder (win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER,
	   ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  show_title ();
  show_grid ();

  move (0, 0);
  hidden = false;
  wrefresh (win);
}

void
Grid::update ()
{
  int i = 0;
  int old_cols = cols, old_rows = rows;
  int temp_rows_height[old_rows];
  int temp_cols_width[old_cols];
  if ((old_rows != new_rows) || (old_cols != new_cols))
    {
      for (i = 0; i < rows; i++)
	{
	  temp_rows_height[i] = rows_height[i];
	}
      for (i = 0; i < cols; i++)
	{
	  temp_cols_width[i] = cols_width[i];
	}
    }

  title = new_title;
  x_pos = new_x_pos;
  y_pos = new_y_pos;
  width = new_width;
  height = new_height;
  win = new_win = newwin (height, width, y_pos, x_pos);
  rows = new_rows;
  cols = new_cols;
  if ((old_rows != new_rows) || (old_cols != new_cols))
    {
      delete[]rows_height;
      delete[]new_rows_height;
      delete[]cols_width;
      delete[]new_cols_width;
      rows_height = new int[rows];
      new_rows_height = new int[rows];
      cols_width = new int[cols];
      new_cols_width = new int[cols];
      for (i = 0; i < rows; i++)
	{
	  rows_height[i] = new_rows_height[i] = (height - 1) / rows;
	}
      free_row_space = (height - 1) - rows * (int) ((height - 1) / rows);
      rows_height[0] = new_rows_height[0] += free_row_space;

      for (i = 0; i < cols; i++)
	{
	  cols_width[i] = new_cols_width[i] = width / cols;
	}
      free_col_space = width - cols * (int) (width / cols);
      cols_width[cols - 1] = new_cols_width[cols - 1] += free_col_space;
    }
  else
    {
      for (i = 0; i < rows; i++)
	rows_height[i] = new_rows_height[i];
      for (i = 0; i < cols; i++)
	cols_width[i] = new_cols_width[i];
    }

  wresize (win, height, width);
}

#endif
