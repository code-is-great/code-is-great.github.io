#include "vm_include.h"
#include "window.h"

#ifdef __WINDOW__

#ifndef __GRID__
#define __GRID__

namespace display
{

  class Grid:public Window
  {
  public:
    Grid ();
    Grid (std::string tl);
    Grid (int r, int c);
      Grid (std::string tl, int x, int y, int w, int h);
      Grid (std::string tl, int x, int y, int w, int h, int r, int c);
     ~Grid ();

    void set_rows (int r);
    void set_cols (int r);
    void set_cols_width (int c, int w);
    void set_rows_height (int r, int h);
    void write (std::string s, int r, int c);

    int get_rows ();
    int get_cols ();
    int get_cols_width (int c);
    int get_rows_height (int r);
    std::string read (int r, int c);

    void hide_grid ();
    void show_grid ();
    void draw ();
    void update ();

  protected:
    int rows;
    int cols;
    int new_rows;
    int new_cols;
    int *cols_width;
    int *rows_height;
    int *new_cols_width;
    int *new_rows_height;

    int free_row_space;
    int free_col_space;

    static int count;		// to count total no of grids

  };

}

#endif				/* __GRID__ */

#endif				/* __WINDOW__ */
