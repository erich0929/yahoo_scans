#include "treeapi.h"

typedef struct _STOCKINFO {
	char* symbol;
	char* code;
} STOCKINFO;

STOCKINFO table_stockinfo [] =	{
	{"World", NULL},
	{"NYSE", NULL},
	{"APPL", "45685.ns"},
	{"MS", "74584.NS"},
	{"LINUX", "75412.NS"}
};	

TreeElement table [] = 	{
	{100, true,	(gpointer) &table_stockinfo [0]},
	{110, false, (gpointer) &table_stockinfo [1]},
	{120, false, (gpointer) &table_stockinfo [2]},
	{130, false, (gpointer) &table_stockinfo [3]},
	{140, false, (gpointer) &table_stockinfo [4]},
	{0, NULL, NULL}
};

int main(void)
{
	GPtrArray* stocklist = array_to_GPtrArray (table, sizeof (table) / sizeof (TreeElement), stocklist);
	
	int i = 0;
	TreeElement* record;
	for (i=0; i<stocklist -> len; i++) {
		record = g_ptr_array_index (stocklist, i);
		printf ("%s\n", ((STOCKINFO*) (record -> data)) -> symbol);
	}
		
	g_ptr_array_free (stocklist, true);

	open_close_branch (table, &table [0], true);
	stocklist = array_to_GPtrArray (table, sizeof (table) / sizeof (TreeElement), stocklist);

	for (i=0; i<stocklist -> len; i++) {
		record = g_ptr_array_index (stocklist, i);
		printf ("%s\n", ((STOCKINFO*) (record -> data)) -> symbol);
	}
	
	g_ptr_array_free (stocklist, true);
	return 0;
}
