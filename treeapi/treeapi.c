#include "treeapi.h"


STOCKINFO WORLD = {"World", NULL, true};
STOCKINFO NYSE = {"NYSE", "55451.ns", true};
STOCKINFO KOSPI = {"KOSPI", "87221.ks", true};

STOCKINFO table_NYSE [] =	{
	{"APPL", "45685.ns", false},
	{"MS", "74584.NS", false},
	{"LINUX", "75412.NS", false}
};

STOCKINFO table_KOSPI [] =	{
	{"SAMSUNG", "54544.ks", false},
	{"LG", "478851.ks", false}
};

/*
TreeElement table [] = 	{
	{100, true,	(gpointer) &table_stockinfo [0]},
	{110, false, (gpointer) &table_stockinfo [1]},
	{120, false, (gpointer) &table_stockinfo [2]},
	{130, false, (gpointer) &table_stockinfo [3]},
	{140, false, (gpointer) &table_stockinfo [4]},
	{0, NULL, NULL}
};
*/
void foreach_func (GNode*, gpointer);

void foreach_func (GNode* node, gpointer data) {
	STOCKINFO* temp = (STOCKINFO*) node -> data;
	printf ("%s\n", temp -> symbol);
}

gboolean traverse_func (GNode* node, gpointer data);

gboolean traverse_func (GNode *node, gpointer data) {
	STOCKINFO* temp = (STOCKINFO*) node -> data;
	printf ("%s\n", temp -> symbol);
	return false;
}

int main(void)
{
/*
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
*/
	GNode* world = g_node_new (&WORLD);
	GNode* nyse = g_node_new (&NYSE);
	g_node_insert (world, -1, nyse);
	int i = 0;
	for (i = 0; i < sizeof (table_NYSE) / sizeof (STOCKINFO); i ++) {
		GNode* temp = g_node_new (&table_NYSE [i]);
		g_node_insert (nyse, -1, temp);
	}
	
	GNode* kospi = g_node_new (&KOSPI);
	g_node_insert (world, -1, kospi);
	dump_to_parent (kospi, table_KOSPI, sizeof (table_KOSPI) / sizeof (STOCKINFO));

	open_close_branch (kospi, true);
	/* g_node_children_foreach (world, G_TRAVERSE_ALL, foreach_func, NULL); */
	GPtrArray* datatable = search_by_regex (world, "LINUX", datatable);
	for (i = 0; i < datatable -> len; i++) {
		STOCKINFO* temp = (STOCKINFO*) g_ptr_array_index (datatable, i);
		printf ("%s\n", temp -> symbol);
	}

	return 0;
}
