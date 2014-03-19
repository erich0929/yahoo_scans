#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#include "./stockapi/stockapi.h"
#include "./boardwidget/boardwidget.h"
#include "./treeapi/treeapi.h"

static void print_main_board_header (WINDOW* wnd, int rows);
static void print_main_board_data (WINDOW* wnd, gpointer data, int rows);

static void print_main_board_header (WINDOW* wnd, int colindex) {
	wprintw (wnd, "%s", "Select a stock you want to scan.");
	wrefresh (wnd);
}

static void print_main_board_data (WINDOW* wnd, gpointer data, int colindex){
	STOCKINFO* temp = (STOCKINFO*) data;
	wprintw (wnd, "%s", temp -> symbol);
}

STOCKINFO WORLD = {"World", NULL, true};
STOCKINFO NYSE = {"NYSE", NULL, true};
STOCKINFO KOSPI = {"KOSPI", NULL, true};

STOCKINFO NYSE_LIST [] = 	{
								{"APPLE", "14255.NS", false},
								{"MicroSoft", "14547.NS", false},
								{"Boeing", "17554.NS", false},
							};

STOCKINFO KOSPI_LIST [] = 	{
								{"SAMSUNG", "15478.KS", false},
								{"LG", "15467.KS", false},
								{"Hyundai", "78231.KS", false},
								{"KIA", "25236.KS", false}
							};

int main(int argc, char* argv[])
{
	/* initialize the stock' informations */
	GNode* world = g_node_new (&WORLD);
	
	GNode* nyse = g_node_new (&NYSE);
	g_node_insert (world, -1, nyse);
	dump_to_parent (nyse, NYSE_LIST, sizeof (NYSE_LIST) / sizeof (STOCKINFO));

	GNode* kospi = g_node_new (&KOSPI);
	g_node_insert (world, -1, kospi);
	dump_to_parent (kospi, KOSPI_LIST, sizeof (KOSPI_LIST) / sizeof (STOCKINFO));

	GPtrArray* main_data_table;
	GPtrArray* result_data_table;

	main_data_table = node_to_array (world, main_data_table);

	/* initialize the display context */
	init_scr ();
		
	POINT_INFO main_board_point_info;
	main_board_point_info.origin_x = 3;
	main_board_point_info.origin_y = 3;
	main_board_point_info.base_color = COLOR_PAIR (0);
	main_board_point_info.selected_color = COLOR_PAIR (1);
	main_board_point_info.x_from_origin = 0;
	main_board_point_info.y_from_origin = 0;

	/* initialize the main_board widget */
	BOARD_WIDGET* main_board = new_board (main_board, 10, 1, 1, 20,
										&main_board_point_info, main_data_table,
										print_main_board_header, 
								   		print_main_board_data);

	set_rowIndex (main_board, 0);
	update_board (main_board);

	/* main loop */
	int ch;
	while ((ch = getch ()) != KEY_F(1)) {
		switch (ch) {
			/* form window loop */
			case 'f' :
				
				while ((ch = getch ()) != KEY_F(1)) {
					switch (ch) {
						case KEY_LEFT :
							/* go to previous field */
				
							break;
						case KEY_RIGHT :
							/* go to next fied */
			
							break;
						default :
				
							break;
					}
					usleep (1000);
				}
				break;
		}
		usleep (1000);
	}

	/* free the memory */
	g_ptr_array_free (main_data_table, false);
	g_node_destroy (world);
	del_board (main_board);
	endwin ();
	return 0;
}

