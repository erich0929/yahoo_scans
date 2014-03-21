#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

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
	int pipe = (temp -> format_info & BASIS_PIPE) >> 12;
	int count_tab = (temp -> format_info & BASIS_TAB) >> 8;
	int arm = (temp -> format_info & BASIS_ARM) >> 4;
	int sign = (temp -> format_info & BASIS_SIGN);
	char format [30];
	memset (format, 0x0, sizeof (format));
	char* temp_ch = format;
	int i = 0;
	int t = 0;
	for (i = 0, t = 1; i < count_tab; i++) {
		int length = strlen (format);
		char tab_ch = '\t';
		strncpy (temp_ch + length, &tab_ch, 1);
		if (pipe == 1 && t == 1) {
			length = strlen (format);
			char pipe_ch = '|';
			strncpy (temp_ch + length, &pipe_ch, 1);
			t--;
		}
	}
	int length;
	char* arm_ch;
	if (arm == 1) {
		arm_ch = "|-- ";
		length = strlen (format);
		strncpy (temp_ch + length, arm_ch, 4);
	}
	else if (arm == 2) {
		arm_ch = "*-- ";
		length = strlen (format);
		strncpy (temp_ch + length, arm_ch, 4);
	}


	char* sign_ch;
	if (sign == 1) {
		sign_ch = "+ ";
		length = strlen (format);
		strncpy (temp_ch + length, sign_ch, 2);
	}
	else if (sign == 2) {
		sign_ch = "- ";
		length = strlen (format);
		strncpy ( temp_ch + length, sign_ch, 2);
	}
	
	length = strlen (format);
	strcpy (temp_ch + length, temp -> symbol);
	length = strlen (format);
	temp_ch [length] = '\0';

	wprintw (wnd, "%s", format);
}

STOCKINFO WORLD = {"World", NULL, true, 1, 0x0000};
STOCKINFO NYSE = {"NYSE", NULL, true, 2, 0x0000};
STOCKINFO KOSPI = {"KOSPI", NULL, true, 2, 0x0000};

STOCKINFO NYSE_LIST [] = 	{
								{"APPLE", "14255.NS", false, 3, 0x0000},
								{"MicroSoft", "14547.NS", false, 3, 0x0000},
								{"Boeing", "17554.NS", false, 3, 0x0000},
							};

STOCKINFO KOSPI_LIST [] = 	{
								{"SAMSUNG", "15478.KS", false, 3},
								{"LG", "15467.KS", false, 3},
								{"Hyundai", "78231.KS", false, 3},
								{"KIA", "25236.KS", false, 3}
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
	BOARD_WIDGET* main_board = new_board (main_board, 6, 1, 1, 33,
										&main_board_point_info, main_data_table,
										print_main_board_header, 
								   		print_main_board_data);

	set_rowIndex (main_board, 0);
	update_board (main_board);
	inactivate_board (main_board);

	/* main loop */
	int ch;
	while ((ch = getch ()) != KEY_F(1)) {
		switch (ch) {
			/* form window loop */
			case 'b' :
				board_eventhandler (main_board, world);
				break;
			default :
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

