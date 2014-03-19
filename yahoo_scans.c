#include <stdio.h>
#include <ncurses.h>
#include <form.h>

#include "./stockapi/stockapi.h"
#include "./boardwidget/boardwidget.h"
#include "./treeapi/treeapi.h"

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

int main(void)
{
	/* initialize the display context */
	init_scr ();
	cbreak ();
	refresh ();
	
	/* initialize the stock' informations */
	GNode* world = g_node_new (&WORLD);
	
	GNode* nyse = g_node_new (&NYSE);
	g_node_insert (world, -1, nyse);
	dump_to_parent (nyse, NYSE_LIST, sizeof (NYSE_LIST) / sizeof (STOCKINFO));

	GNode* kospi = g_node_new (&KOSPI);
	g_node_insert (world, -1, kospi);
	dump_to_parent (kospi, KOSPI_LIST, sizeof (KOSPI_LIST) / sizeof (STOCKINFO));


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

	/* un post form and free the memory */
	endwin ();
	return 0;
}
