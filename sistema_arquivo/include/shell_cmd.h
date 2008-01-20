struct cmd_list {
	char *name;
	void *func;
	struct cmd_list *next;
};

struct cmd_list *build_command(char *name, void *func);

void append_command_list(struct cmd_list **list, struct cmd_list *new_cmd); 

void call_command(char *name, int argc, char *argv[]);
