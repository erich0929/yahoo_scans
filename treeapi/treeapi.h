#ifndef _TREEAPI_H_
#define _TREEAPI_H_

#include <stdio.h>
#include <glib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef	struct _TreeElement {
	int id;
	bool IsActivated;
	gpointer data;	
} TreeElement; /* IMPORTANCE : TreeElement table (array) should be ended by {0, NULL, NULL} !! */

GPtrArray* array_to_GPtrArray (TreeElement table [], int length,
	   							GPtrArray* empty_GPtrArray) {
	empty_GPtrArray = g_ptr_array_new ();
	GPtrArray* fulled_GPtrArray = empty_GPtrArray;
	
	int i = 0;
	for (i=0; i<length - 1; i++) {
		if (table [i].IsActivated == true) {
			g_ptr_array_add (fulled_GPtrArray, &table [i]);
		}
	}

	return fulled_GPtrArray;
}

void open_close_branch (TreeElement table [], TreeElement* point, bool flag) {
	int from_id = point -> id;
	int to_id = next_branch_point (from_id);

	while (point -> id) {
		if (point -> id > from_id && point -> id < to_id) 
			if (flag == true) {
				point -> IsActivated = true;
			}
			else point -> IsActivated = false;
		if (point -> id > to_id) break;
		point ++;
	}	
}

int next_branch_point (int id) {
	char stringID [20];
	sprintf (stringID, "%d", id);

	int length = strlen (stringID);
	int zero_position = length;
	char* temp = stringID;
	for (zero_position; *temp; temp ++, zero_position --) {
		if (*temp == '0') break;
	}
	
	char* plus = (char*) malloc (zero_position + 2);
	plus [0] = '1';
	temp = plus;
	temp ++;
	for (; *temp; temp ++) {
		*temp = '0';
	}
	plus [zero_position + 1] = '\0';
	id += atoi (plus);

	return id;
}	
#endif
