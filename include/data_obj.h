//
// Created by peer on 12-11-22.
//

#ifndef FT_LS_DATA_OBJ_H
#define FT_LS_DATA_OBJ_H
#include <time.h>
#include <sys/stat.h>
#include <vector.h>
#include <dirent.h>

typedef struct s_data {
	char*	name;
	char*	fullpath;
	struct stat	statbuf;
	t_ptrvector	*vector; // for Recursive mode
	bool	is_root_node;
}	t_data;

t_data* create_new_rootnode(const char* arg);
t_data *create_new_object(const char *prefix, const char* pdirent_name);
//t_data *create_new_object_blank(char *fullpath, bool go_down_layer);
//t_data *create_new_object_of_type(const char *const name, unsigned char type, bool go_down_layer);

bool print_object(const t_data* dataObj);
void*	destroy_object(t_data* dataObj);

/*
 * utilities.c
 */
char	*ft_str3join(const char *a, const char *b, const char *c);

/*
 * get_directory_information.c
 */
void collect_children_nodes(t_data *ls_obj);

/*
 * get_filetype.c
 */
unsigned char get_filetype(const char *name);

/*
 * sort.c
 */
void	sort_dataObjects(t_data **dataObjects, size_t dataObject_amount);
#endif //FT_LS_DATA_OBJ_H
