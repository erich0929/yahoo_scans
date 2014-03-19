#ifndef _TREEAPI_H_
#define _TREEAPI_H_

#include <stdio.h>
#include <glib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>


typedef struct _STOCKINFO {
	char* symbol;
	char* code;
	bool IsActivated;
} STOCKINFO;

typedef struct _regex_t_and_array {
	regex_t state;
	GPtrArray* array;
}regex_t_and_array;

typedef	struct _TreeElement {
	int id;
	bool IsActivated;
	gpointer data;	
} TreeElement; /* IMPORTANCE : TreeElement table (array) should be ended by {0, NULL, NULL} !! */

/*
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
*/
static void activate_node (GNode* node, gpointer data);
static gboolean store_into_g_ptr_array (GNode* node, gpointer g_ptr_array);
static gboolean check_and_store (GNode* node, gpointer g_ptr_array);
void open_close_branch (GNode* node, bool flag);
GPtrArray* node_to_array (GNode* node, GPtrArray* empty_GPtrArray);
void dump_to_parent (GNode* parent, STOCKINFO table [], int length);
GPtrArray*  search_by_regex (GNode* node, char* pattern, GPtrArray* empty_GPtrArray);

/* --------- < Used by open_close_branch > ------------- */
static void activate_node (GNode* node, gpointer data) {
	STOCKINFO* temp = (STOCKINFO*) node -> data;
	bool flag = *((bool*) data);
	if (flag == true) {
		temp -> IsActivated = true;
	}
	else temp -> IsActivated = false;
}

/* --------- < Used by node_to_array > ----------- */
static gboolean store_into_g_ptr_array (GNode* node, gpointer g_ptr_array) {
	STOCKINFO* data = (STOCKINFO*) node -> data;
	if (data -> IsActivated == true) {
		GPtrArray* array = (GPtrArray*) g_ptr_array;
		g_ptr_array_add (g_ptr_array, data);
	}
	return false;
}

static gboolean check_and_store (GNode* node, gpointer data) {
	STOCKINFO* temp = (STOCKINFO*) node -> data;
	regex_t_and_array* temp1 = (regex_t_and_array*) data;
	int status = regexec (&(temp1 -> state), temp -> symbol, 0, NULL, 0);
	if (status == 0 || g_node_depth (node) <= 2) {
		g_ptr_array_add (temp1 -> array, temp);
	}	
	return false;
}
void open_close_branch (GNode* parent, bool flag) {
	g_node_children_foreach (parent, G_TRAVERSE_ALL, activate_node, &flag);
}

GPtrArray* node_to_array (GNode* node, GPtrArray* empty_GPtrArray) {
	empty_GPtrArray = g_ptr_array_new ();
	GPtrArray* fulled_GPtrArray = empty_GPtrArray;
	g_node_traverse (node, G_PRE_ORDER, G_TRAVERSE_ALL, -1, store_into_g_ptr_array, (gpointer) fulled_GPtrArray);
	return fulled_GPtrArray;
}
/*
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
*/

void dump_to_parent (GNode* parent, STOCKINFO table [], int length) {
	int i = 0;
	for (i = 0; i < length ; i++) {
		GNode* temp = g_node_new (&table [i]);
		g_node_insert (parent, -1, temp);
	}
}

GPtrArray*  search_by_regex (GNode* node, char* pattern, GPtrArray* empty_GPtrArray) {
	empty_GPtrArray = g_ptr_array_new ();
	GPtrArray* fulled_GPtrArray = empty_GPtrArray;
	regex_t_and_array data;
	regcomp (&(data.state), pattern, REG_EXTENDED);
	data.array = fulled_GPtrArray;
	g_node_traverse (node, G_PRE_ORDER, G_TRAVERSE_ALL, -1, check_and_store, (gpointer) &data);
	return fulled_GPtrArray;
}

#endif
