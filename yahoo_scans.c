#include <stdio.h>
#include <ncurses.h>
#include <form.h>

/*
#include "./stockapi/stockapi.h"
#include "./boardwidget/boardwidget.h"
*/

int main(void)
{
	/* initialize the display context */
	init_scr ();
	cbreak ();
	refresh ();

	/* initialize the fields */
	FIELD* field [3];
	field [0] = new_field (1, 4, 4, 14, 0, 0);
	field [1] = new_field (1, 4, 4, 32, 0, 0);
	field [2] = NULL;

	/* set field options */
	field_opts_off (field [0], O_AUTOSKIP);
	field_opts_off (field [1], O_AUTOSKIP);
	set_field_back (field [0], A_UNDERLINE);
	set_field_back (field [1], A_UNDERLINE);

	/* create the form and post it */
	FORM* form_dateinfo = new_form (field);
	post_form (form_dateinfo);
	refresh ();

	mvprintw (4, 1, "From Month :");
	mvprintw (4, 21, "From_day :");
	refresh ();

	/* main loop */
	int ch;
	while ((ch = getch ()) != KEY_F(1)) {
		switch (ch) {
			/* form window loop */
			case 'f' :
				set_current_field (form_dateinfo, field [0]);
				while ((ch = getch ()) != KEY_F(1)) {
					switch (ch) {
						case KEY_LEFT :
							/* go to previous field */
							form_driver (form_dateinfo, REQ_PREV_FIELD);
							form_driver (form_dateinfo, REQ_END_LINE);
							break;
						case KEY_RIGHT :
							/* go to next fied */
							form_driver (form_dateinfo, REQ_NEXT_FIELD);
							form_driver (form_dateinfo, REQ_END_LINE);
							break;
						default :
							form_driver (form_dateinfo, ch);
							break;
					}
					usleep (1000);
				}
				break;
		}
		usleep (1000);
	}

	/* un post form and free the memory */
	unpost_form (form_dateinfo);
	free_form (form_dateinfo);
	free_field (field [0]);
	free_field (field [1]);

	endwin ();
	return 0;
}
