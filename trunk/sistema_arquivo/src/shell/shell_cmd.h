struct cmd_list {
	char *name;
	void (*func)(int argc, char *argv[]);
	struct cmd_list *next;
};

struct cmd_list *build_command(char *name, void *func);

void append_command_list(struct cmd_list **list, struct cmd_list *new_cmd); 

int call_command(char *name, int argc, char *argv[]);

void dump_commands(struct cmd_list **list);

// declara uma lista de comandos globais
struct cmd_list *command_list;
