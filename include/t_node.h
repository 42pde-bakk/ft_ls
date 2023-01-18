//
// Created by peer on 12-11-22.
//

#ifndef FT_LS_T_NODE_H
#define FT_LS_T_NODE_H

#include <time.h>
#include <sys/stat.h>
#include <vector.h>
#include <dirent.h>

typedef struct s_node {
	char* name;
	char* fullpath;
	struct stat statbuf;
	t_ptrvector* vector;
} t_node;

t_node* create_new_rootnode(const char* arg);

t_node* create_new_object(const char* prefix, const char* pdirent_name);

void print_object(const t_node* dataObj);

void destroy_object(t_node* dataObj);

#endif //FT_LS_T_NODE_H
