#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell_cmd.h"


struct cmd_list *build_command(char *name, void *func) {
	 struct cmd_list *new_cmd;
	 new_cmd = malloc( sizeof(struct cmd_list) );
	 new_cmd->name = strdup(name);
	 new_cmd->func = func;
	 return new_cmd;
}

void append_command_list(struct cmd_list **list, struct cmd_list *new_cmd) {
	struct cmd_list *iterator = (*list);
	if (iterator == NULL) {
		(*list) = new_cmd;
		(*list)->next = NULL;
	} else {
		while ( iterator->next ) 
			iterator = iterator->next; 
		iterator->next = new_cmd;
		(iterator->next)->next = NULL;
	}
}

void dump_commands(struct cmd_list **list) {
	struct cmd_list *iterator = (*list);
	while ( iterator ) { 
		printf("Comando: %s\t\n", iterator->name);
		iterator = iterator->next;
	}
}

// retorna true se encontra comando
int call_command(char *name, int argc, char *argv[]) {
	struct cmd_list *iterator = command_list;
	while ( iterator ) { 
		if ( !strcmp(iterator->name, name) ) {
			(iterator->func)(argc, argv);
			return 1;
		}
		iterator = iterator->next;
	}
	return 0;
}

