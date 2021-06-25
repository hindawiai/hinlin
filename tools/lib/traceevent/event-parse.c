<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 *
 *  The parts क्रम function graph prपूर्णांकing was taken and modअगरied from the
 *  Linux Kernel that were written by
 *    - Copyright (C) 2009  Frederic Weisbecker,
 *  Frederic Weisbecker gave his permission to relicense the code to
 *  the Lesser General Public License.
 */
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानक_निवेशt.h>
#समावेश <सीमा.स>
#समावेश <linux/समय64.h>

#समावेश <netinet/in.h>
#समावेश "event-parse.h"

#समावेश "event-parse-local.h"
#समावेश "event-utils.h"
#समावेश "trace-seq.h"

अटल स्थिर अक्षर *input_buf;
अटल अचिन्हित दीर्घ दीर्घ input_buf_ptr;
अटल अचिन्हित दीर्घ दीर्घ input_buf_siz;

अटल पूर्णांक is_flag_field;
अटल पूर्णांक is_symbolic_field;

अटल पूर्णांक show_warning = 1;

#घोषणा करो_warning(fmt, ...)				\
	करो अणु						\
		अगर (show_warning)			\
			warning(fmt, ##__VA_ARGS__);	\
	पूर्ण जबतक (0)

#घोषणा करो_warning_event(event, fmt, ...)			\
	करो अणु							\
		अगर (!show_warning)				\
			जारी;				\
								\
		अगर (event)					\
			warning("[%s:%s] " fmt, event->प्रणाली,	\
				event->name, ##__VA_ARGS__);	\
		अन्यथा						\
			warning(fmt, ##__VA_ARGS__);		\
	पूर्ण जबतक (0)

/**
 * init_input_buf - init buffer क्रम parsing
 * @buf: buffer to parse
 * @size: the size of the buffer
 *
 * Initializes the पूर्णांकernal buffer that tep_पढ़ो_token() will parse.
 */
__hidden व्योम init_input_buf(स्थिर अक्षर *buf, अचिन्हित दीर्घ दीर्घ size)
अणु
	input_buf = buf;
	input_buf_siz = size;
	input_buf_ptr = 0;
पूर्ण

__hidden स्थिर अक्षर *get_input_buf(व्योम)
अणु
	वापस input_buf;
पूर्ण

__hidden अचिन्हित दीर्घ दीर्घ get_input_buf_ptr(व्योम)
अणु
	वापस input_buf_ptr;
पूर्ण

काष्ठा event_handler अणु
	काष्ठा event_handler		*next;
	पूर्णांक				id;
	स्थिर अक्षर			*sys_name;
	स्थिर अक्षर			*event_name;
	tep_event_handler_func		func;
	व्योम				*context;
पूर्ण;

काष्ठा func_params अणु
	काष्ठा func_params	*next;
	क्रमागत tep_func_arg_type	type;
पूर्ण;

काष्ठा tep_function_handler अणु
	काष्ठा tep_function_handler	*next;
	क्रमागत tep_func_arg_type		ret_type;
	अक्षर				*name;
	tep_func_handler		func;
	काष्ठा func_params		*params;
	पूर्णांक				nr_args;
पूर्ण;

अटल अचिन्हित दीर्घ दीर्घ
process_defined_func(काष्ठा trace_seq *s, व्योम *data, पूर्णांक size,
		     काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg);

अटल व्योम मुक्त_func_handle(काष्ठा tep_function_handler *func);

व्योम अवरोधpoपूर्णांक(व्योम)
अणु
	अटल पूर्णांक x;
	x++;
पूर्ण

अटल काष्ठा tep_prपूर्णांक_arg *alloc_arg(व्योम)
अणु
	वापस सुस्मृति(1, माप(काष्ठा tep_prपूर्णांक_arg));
पूर्ण

काष्ठा tep_cmdline अणु
	अक्षर *comm;
	पूर्णांक pid;
पूर्ण;

अटल पूर्णांक cmdline_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा tep_cmdline *ca = a;
	स्थिर काष्ठा tep_cmdline *cb = b;

	अगर (ca->pid < cb->pid)
		वापस -1;
	अगर (ca->pid > cb->pid)
		वापस 1;

	वापस 0;
पूर्ण

/* Looking क्रम where to place the key */
अटल पूर्णांक cmdline_slot_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा tep_cmdline *ca = a;
	स्थिर काष्ठा tep_cmdline *cb = b;
	स्थिर काष्ठा tep_cmdline *cb1 = cb + 1;

	अगर (ca->pid < cb->pid)
		वापस -1;

	अगर (ca->pid > cb->pid) अणु
		अगर (ca->pid <= cb1->pid)
			वापस 0;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cmdline_list अणु
	काष्ठा cmdline_list	*next;
	अक्षर			*comm;
	पूर्णांक			pid;
पूर्ण;

अटल पूर्णांक cmdline_init(काष्ठा tep_handle *tep)
अणु
	काष्ठा cmdline_list *cmdlist = tep->cmdlist;
	काष्ठा cmdline_list *item;
	काष्ठा tep_cmdline *cmdlines;
	पूर्णांक i;

	cmdlines = दो_स्मृति(माप(*cmdlines) * tep->cmdline_count);
	अगर (!cmdlines)
		वापस -1;

	i = 0;
	जबतक (cmdlist) अणु
		cmdlines[i].pid = cmdlist->pid;
		cmdlines[i].comm = cmdlist->comm;
		i++;
		item = cmdlist;
		cmdlist = cmdlist->next;
		मुक्त(item);
	पूर्ण

	क्विक(cmdlines, tep->cmdline_count, माप(*cmdlines), cmdline_cmp);

	tep->cmdlines = cmdlines;
	tep->cmdlist = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *find_cmdline(काष्ठा tep_handle *tep, पूर्णांक pid)
अणु
	स्थिर काष्ठा tep_cmdline *comm;
	काष्ठा tep_cmdline key;

	अगर (!pid)
		वापस "<idle>";

	अगर (!tep->cmdlines && cmdline_init(tep))
		वापस "<not enough memory for cmdlines!>";

	key.pid = pid;

	comm = द्वा_खोज(&key, tep->cmdlines, tep->cmdline_count,
		       माप(*tep->cmdlines), cmdline_cmp);

	अगर (comm)
		वापस comm->comm;
	वापस "<...>";
पूर्ण

/**
 * tep_is_pid_रेजिस्टरed - वापस अगर a pid has a cmdline रेजिस्टरed
 * @tep: a handle to the trace event parser context
 * @pid: The pid to check अगर it has a cmdline रेजिस्टरed with.
 *
 * Returns true अगर the pid has a cmdline mapped to it
 * false otherwise.
 */
bool tep_is_pid_रेजिस्टरed(काष्ठा tep_handle *tep, पूर्णांक pid)
अणु
	स्थिर काष्ठा tep_cmdline *comm;
	काष्ठा tep_cmdline key;

	अगर (!pid)
		वापस true;

	अगर (!tep->cmdlines && cmdline_init(tep))
		वापस false;

	key.pid = pid;

	comm = द्वा_खोज(&key, tep->cmdlines, tep->cmdline_count,
		       माप(*tep->cmdlines), cmdline_cmp);

	अगर (comm)
		वापस true;
	वापस false;
पूर्ण

/*
 * If the command lines have been converted to an array, then
 * we must add this pid. This is much slower than when cmdlines
 * are added beक्रमe the array is initialized.
 */
अटल पूर्णांक add_new_comm(काष्ठा tep_handle *tep,
			स्थिर अक्षर *comm, पूर्णांक pid, bool override)
अणु
	काष्ठा tep_cmdline *cmdlines = tep->cmdlines;
	काष्ठा tep_cmdline *cmdline;
	काष्ठा tep_cmdline key;
	अक्षर *new_comm;
	पूर्णांक cnt;

	अगर (!pid)
		वापस 0;

	/* aव्योम duplicates */
	key.pid = pid;

	cmdline = द्वा_खोज(&key, tep->cmdlines, tep->cmdline_count,
			  माप(*tep->cmdlines), cmdline_cmp);
	अगर (cmdline) अणु
		अगर (!override) अणु
			त्रुटि_सं = EEXIST;
			वापस -1;
		पूर्ण
		new_comm = strdup(comm);
		अगर (!new_comm) अणु
			त्रुटि_सं = ENOMEM;
			वापस -1;
		पूर्ण
		मुक्त(cmdline->comm);
		cmdline->comm = new_comm;

		वापस 0;
	पूर्ण

	cmdlines = पुनः_स्मृति(cmdlines, माप(*cmdlines) * (tep->cmdline_count + 1));
	अगर (!cmdlines) अणु
		त्रुटि_सं = ENOMEM;
		वापस -1;
	पूर्ण
	tep->cmdlines = cmdlines;

	key.comm = strdup(comm);
	अगर (!key.comm) अणु
		त्रुटि_सं = ENOMEM;
		वापस -1;
	पूर्ण

	अगर (!tep->cmdline_count) अणु
		/* no entries yet */
		tep->cmdlines[0] = key;
		tep->cmdline_count++;
		वापस 0;
	पूर्ण

	/* Now find where we want to store the new cmdline */
	cmdline = द्वा_खोज(&key, tep->cmdlines, tep->cmdline_count - 1,
			  माप(*tep->cmdlines), cmdline_slot_cmp);

	cnt = tep->cmdline_count;
	अगर (cmdline) अणु
		/* cmdline poपूर्णांकs to the one beक्रमe the spot we want */
		cmdline++;
		cnt -= cmdline - tep->cmdlines;

	पूर्ण अन्यथा अणु
		/* The new entry is either beक्रमe or after the list */
		अगर (key.pid > tep->cmdlines[tep->cmdline_count - 1].pid) अणु
			tep->cmdlines[tep->cmdline_count++] = key;
			वापस 0;
		पूर्ण
		cmdline = &tep->cmdlines[0];
	पूर्ण
	स_हटाओ(cmdline + 1, cmdline, (cnt * माप(*cmdline)));
	*cmdline = key;

	tep->cmdline_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक _tep_रेजिस्टर_comm(काष्ठा tep_handle *tep,
			      स्थिर अक्षर *comm, पूर्णांक pid, bool override)
अणु
	काष्ठा cmdline_list *item;

	अगर (tep->cmdlines)
		वापस add_new_comm(tep, comm, pid, override);

	item = दो_स्मृति(माप(*item));
	अगर (!item)
		वापस -1;

	अगर (comm)
		item->comm = strdup(comm);
	अन्यथा
		item->comm = strdup("<...>");
	अगर (!item->comm) अणु
		मुक्त(item);
		वापस -1;
	पूर्ण
	item->pid = pid;
	item->next = tep->cmdlist;

	tep->cmdlist = item;
	tep->cmdline_count++;

	वापस 0;
पूर्ण

/**
 * tep_रेजिस्टर_comm - रेजिस्टर a pid / comm mapping
 * @tep: a handle to the trace event parser context
 * @comm: the command line to रेजिस्टर
 * @pid: the pid to map the command line to
 *
 * This adds a mapping to search क्रम command line names with
 * a given pid. The comm is duplicated. If a command with the same pid
 * alपढ़ोy exist, -1 is वापसed and त्रुटि_सं is set to EEXIST
 */
पूर्णांक tep_रेजिस्टर_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm, पूर्णांक pid)
अणु
	वापस _tep_रेजिस्टर_comm(tep, comm, pid, false);
पूर्ण

/**
 * tep_override_comm - रेजिस्टर a pid / comm mapping
 * @tep: a handle to the trace event parser context
 * @comm: the command line to रेजिस्टर
 * @pid: the pid to map the command line to
 *
 * This adds a mapping to search क्रम command line names with
 * a given pid. The comm is duplicated. If a command with the same pid
 * alपढ़ोy exist, the command string is udapted with the new one
 */
पूर्णांक tep_override_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm, पूर्णांक pid)
अणु
	अगर (!tep->cmdlines && cmdline_init(tep)) अणु
		त्रुटि_सं = ENOMEM;
		वापस -1;
	पूर्ण
	वापस _tep_रेजिस्टर_comm(tep, comm, pid, true);
पूर्ण

काष्ठा func_map अणु
	अचिन्हित दीर्घ दीर्घ		addr;
	अक्षर				*func;
	अक्षर				*mod;
पूर्ण;

काष्ठा func_list अणु
	काष्ठा func_list	*next;
	अचिन्हित दीर्घ दीर्घ	addr;
	अक्षर			*func;
	अक्षर			*mod;
पूर्ण;

अटल पूर्णांक func_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा func_map *fa = a;
	स्थिर काष्ठा func_map *fb = b;

	अगर (fa->addr < fb->addr)
		वापस -1;
	अगर (fa->addr > fb->addr)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * We are searching क्रम a record in between, not an exact
 * match.
 */
अटल पूर्णांक func_bcmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा func_map *fa = a;
	स्थिर काष्ठा func_map *fb = b;

	अगर ((fa->addr == fb->addr) ||

	    (fa->addr > fb->addr &&
	     fa->addr < (fb+1)->addr))
		वापस 0;

	अगर (fa->addr < fb->addr)
		वापस -1;

	वापस 1;
पूर्ण

अटल पूर्णांक func_map_init(काष्ठा tep_handle *tep)
अणु
	काष्ठा func_list *funclist;
	काष्ठा func_list *item;
	काष्ठा func_map *func_map;
	पूर्णांक i;

	func_map = दो_स्मृति(माप(*func_map) * (tep->func_count + 1));
	अगर (!func_map)
		वापस -1;

	funclist = tep->funclist;

	i = 0;
	जबतक (funclist) अणु
		func_map[i].func = funclist->func;
		func_map[i].addr = funclist->addr;
		func_map[i].mod = funclist->mod;
		i++;
		item = funclist;
		funclist = funclist->next;
		मुक्त(item);
	पूर्ण

	क्विक(func_map, tep->func_count, माप(*func_map), func_cmp);

	/*
	 * Add a special record at the end.
	 */
	func_map[tep->func_count].func = शून्य;
	func_map[tep->func_count].addr = 0;
	func_map[tep->func_count].mod = शून्य;

	tep->func_map = func_map;
	tep->funclist = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा func_map *
__find_func(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा func_map *func;
	काष्ठा func_map key;

	अगर (!tep->func_map)
		func_map_init(tep);

	key.addr = addr;

	func = द्वा_खोज(&key, tep->func_map, tep->func_count,
		       माप(*tep->func_map), func_bcmp);

	वापस func;
पूर्ण

काष्ठा func_resolver अणु
	tep_func_resolver_t	*func;
	व्योम			*priv;
	काष्ठा func_map		map;
पूर्ण;

/**
 * tep_set_function_resolver - set an alternative function resolver
 * @tep: a handle to the trace event parser context
 * @resolver: function to be used
 * @priv: resolver function निजी state.
 *
 * Some tools may have alपढ़ोy a way to resolve kernel functions, allow them to
 * keep using it instead of duplicating all the entries inside tep->funclist.
 */
पूर्णांक tep_set_function_resolver(काष्ठा tep_handle *tep,
			      tep_func_resolver_t *func, व्योम *priv)
अणु
	काष्ठा func_resolver *resolver = दो_स्मृति(माप(*resolver));

	अगर (resolver == शून्य)
		वापस -1;

	resolver->func = func;
	resolver->priv = priv;

	मुक्त(tep->func_resolver);
	tep->func_resolver = resolver;

	वापस 0;
पूर्ण

/**
 * tep_reset_function_resolver - reset alternative function resolver
 * @tep: a handle to the trace event parser context
 *
 * Stop using whatever alternative resolver was set, use the शेष
 * one instead.
 */
व्योम tep_reset_function_resolver(काष्ठा tep_handle *tep)
अणु
	मुक्त(tep->func_resolver);
	tep->func_resolver = शून्य;
पूर्ण

अटल काष्ठा func_map *
find_func(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा func_map *map;

	अगर (!tep->func_resolver)
		वापस __find_func(tep, addr);

	map = &tep->func_resolver->map;
	map->mod  = शून्य;
	map->addr = addr;
	map->func = tep->func_resolver->func(tep->func_resolver->priv,
					     &map->addr, &map->mod);
	अगर (map->func == शून्य)
		वापस शून्य;

	वापस map;
पूर्ण

/**
 * tep_find_function - find a function by a given address
 * @tep: a handle to the trace event parser context
 * @addr: the address to find the function with
 *
 * Returns a poपूर्णांकer to the function stored that has the given
 * address. Note, the address करोes not have to be exact, it
 * will select the function that would contain the address.
 */
स्थिर अक्षर *tep_find_function(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा func_map *map;

	map = find_func(tep, addr);
	अगर (!map)
		वापस शून्य;

	वापस map->func;
पूर्ण

/**
 * tep_find_function_address - find a function address by a given address
 * @tep: a handle to the trace event parser context
 * @addr: the address to find the function with
 *
 * Returns the address the function starts at. This can be used in
 * conjunction with tep_find_function to prपूर्णांक both the function
 * name and the function offset.
 */
अचिन्हित दीर्घ दीर्घ
tep_find_function_address(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा func_map *map;

	map = find_func(tep, addr);
	अगर (!map)
		वापस 0;

	वापस map->addr;
पूर्ण

/**
 * tep_रेजिस्टर_function - रेजिस्टर a function with a given address
 * @tep: a handle to the trace event parser context
 * @function: the function name to रेजिस्टर
 * @addr: the address the function starts at
 * @mod: the kernel module the function may be in (शून्य क्रम none)
 *
 * This रेजिस्टरs a function name with an address and module.
 * The @func passed in is duplicated.
 */
पूर्णांक tep_रेजिस्टर_function(काष्ठा tep_handle *tep, अक्षर *func,
			  अचिन्हित दीर्घ दीर्घ addr, अक्षर *mod)
अणु
	काष्ठा func_list *item = दो_स्मृति(माप(*item));

	अगर (!item)
		वापस -1;

	item->next = tep->funclist;
	item->func = strdup(func);
	अगर (!item->func)
		जाओ out_मुक्त;

	अगर (mod) अणु
		item->mod = strdup(mod);
		अगर (!item->mod)
			जाओ out_मुक्त_func;
	पूर्ण अन्यथा
		item->mod = शून्य;
	item->addr = addr;

	tep->funclist = item;
	tep->func_count++;

	वापस 0;

out_मुक्त_func:
	मुक्त(item->func);
	item->func = शून्य;
out_मुक्त:
	मुक्त(item);
	त्रुटि_सं = ENOMEM;
	वापस -1;
पूर्ण

/**
 * tep_prपूर्णांक_funcs - prपूर्णांक out the stored functions
 * @tep: a handle to the trace event parser context
 *
 * This prपूर्णांकs out the stored functions.
 */
व्योम tep_prपूर्णांक_funcs(काष्ठा tep_handle *tep)
अणु
	पूर्णांक i;

	अगर (!tep->func_map)
		func_map_init(tep);

	क्रम (i = 0; i < (पूर्णांक)tep->func_count; i++) अणु
		म_लिखो("%016llx %s",
		       tep->func_map[i].addr,
		       tep->func_map[i].func);
		अगर (tep->func_map[i].mod)
			म_लिखो(" [%s]\n", tep->func_map[i].mod);
		अन्यथा
			म_लिखो("\n");
	पूर्ण
पूर्ण

काष्ठा prपूर्णांकk_map अणु
	अचिन्हित दीर्घ दीर्घ		addr;
	अक्षर				*prपूर्णांकk;
पूर्ण;

काष्ठा prपूर्णांकk_list अणु
	काष्ठा prपूर्णांकk_list	*next;
	अचिन्हित दीर्घ दीर्घ	addr;
	अक्षर			*prपूर्णांकk;
पूर्ण;

अटल पूर्णांक prपूर्णांकk_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा prपूर्णांकk_map *pa = a;
	स्थिर काष्ठा prपूर्णांकk_map *pb = b;

	अगर (pa->addr < pb->addr)
		वापस -1;
	अगर (pa->addr > pb->addr)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांकk_map_init(काष्ठा tep_handle *tep)
अणु
	काष्ठा prपूर्णांकk_list *prपूर्णांकklist;
	काष्ठा prपूर्णांकk_list *item;
	काष्ठा prपूर्णांकk_map *prपूर्णांकk_map;
	पूर्णांक i;

	prपूर्णांकk_map = दो_स्मृति(माप(*prपूर्णांकk_map) * (tep->prपूर्णांकk_count + 1));
	अगर (!prपूर्णांकk_map)
		वापस -1;

	prपूर्णांकklist = tep->prपूर्णांकklist;

	i = 0;
	जबतक (prपूर्णांकklist) अणु
		prपूर्णांकk_map[i].prपूर्णांकk = prपूर्णांकklist->prपूर्णांकk;
		prपूर्णांकk_map[i].addr = prपूर्णांकklist->addr;
		i++;
		item = prपूर्णांकklist;
		prपूर्णांकklist = prपूर्णांकklist->next;
		मुक्त(item);
	पूर्ण

	क्विक(prपूर्णांकk_map, tep->prपूर्णांकk_count, माप(*prपूर्णांकk_map), prपूर्णांकk_cmp);

	tep->prपूर्णांकk_map = prपूर्णांकk_map;
	tep->prपूर्णांकklist = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा prपूर्णांकk_map *
find_prपूर्णांकk(काष्ठा tep_handle *tep, अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा prपूर्णांकk_map *prपूर्णांकk;
	काष्ठा prपूर्णांकk_map key;

	अगर (!tep->prपूर्णांकk_map && prपूर्णांकk_map_init(tep))
		वापस शून्य;

	key.addr = addr;

	prपूर्णांकk = द्वा_खोज(&key, tep->prपूर्णांकk_map, tep->prपूर्णांकk_count,
			 माप(*tep->prपूर्णांकk_map), prपूर्णांकk_cmp);

	वापस prपूर्णांकk;
पूर्ण

/**
 * tep_रेजिस्टर_prपूर्णांक_string - रेजिस्टर a string by its address
 * @tep: a handle to the trace event parser context
 * @fmt: the string क्रमmat to रेजिस्टर
 * @addr: the address the string was located at
 *
 * This रेजिस्टरs a string by the address it was stored in the kernel.
 * The @fmt passed in is duplicated.
 */
पूर्णांक tep_रेजिस्टर_prपूर्णांक_string(काष्ठा tep_handle *tep, स्थिर अक्षर *fmt,
			      अचिन्हित दीर्घ दीर्घ addr)
अणु
	काष्ठा prपूर्णांकk_list *item = दो_स्मृति(माप(*item));
	अक्षर *p;

	अगर (!item)
		वापस -1;

	item->next = tep->prपूर्णांकklist;
	item->addr = addr;

	/* Strip off quotes and '\n' from the end */
	अगर (fmt[0] == '"')
		fmt++;
	item->prपूर्णांकk = strdup(fmt);
	अगर (!item->prपूर्णांकk)
		जाओ out_मुक्त;

	p = item->prपूर्णांकk + म_माप(item->prपूर्णांकk) - 1;
	अगर (*p == '"')
		*p = 0;

	p -= 2;
	अगर (म_भेद(p, "\\n") == 0)
		*p = 0;

	tep->prपूर्णांकklist = item;
	tep->prपूर्णांकk_count++;

	वापस 0;

out_मुक्त:
	मुक्त(item);
	त्रुटि_सं = ENOMEM;
	वापस -1;
पूर्ण

/**
 * tep_prपूर्णांक_prपूर्णांकk - prपूर्णांक out the stored strings
 * @tep: a handle to the trace event parser context
 *
 * This prपूर्णांकs the string क्रमmats that were stored.
 */
व्योम tep_prपूर्णांक_prपूर्णांकk(काष्ठा tep_handle *tep)
अणु
	पूर्णांक i;

	अगर (!tep->prपूर्णांकk_map)
		prपूर्णांकk_map_init(tep);

	क्रम (i = 0; i < (पूर्णांक)tep->prपूर्णांकk_count; i++) अणु
		म_लिखो("%016llx %s\n",
		       tep->prपूर्णांकk_map[i].addr,
		       tep->prपूर्णांकk_map[i].prपूर्णांकk);
	पूर्ण
पूर्ण

अटल काष्ठा tep_event *alloc_event(व्योम)
अणु
	वापस सुस्मृति(1, माप(काष्ठा tep_event));
पूर्ण

अटल पूर्णांक add_event(काष्ठा tep_handle *tep, काष्ठा tep_event *event)
अणु
	पूर्णांक i;
	काष्ठा tep_event **events = पुनः_स्मृति(tep->events, माप(event) *
					    (tep->nr_events + 1));
	अगर (!events)
		वापस -1;

	tep->events = events;

	क्रम (i = 0; i < tep->nr_events; i++) अणु
		अगर (tep->events[i]->id > event->id)
			अवरोध;
	पूर्ण
	अगर (i < tep->nr_events)
		स_हटाओ(&tep->events[i + 1],
			&tep->events[i],
			माप(event) * (tep->nr_events - i));

	tep->events[i] = event;
	tep->nr_events++;

	event->tep = tep;

	वापस 0;
पूर्ण

अटल पूर्णांक event_item_type(क्रमागत tep_event_type type)
अणु
	चयन (type) अणु
	हाल TEP_EVENT_ITEM ... TEP_EVENT_SQUOTE:
		वापस 1;
	हाल TEP_EVENT_ERROR ... TEP_EVENT_DELIM:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_flag_sym(काष्ठा tep_prपूर्णांक_flag_sym *fsym)
अणु
	काष्ठा tep_prपूर्णांक_flag_sym *next;

	जबतक (fsym) अणु
		next = fsym->next;
		मुक्त(fsym->value);
		मुक्त(fsym->str);
		मुक्त(fsym);
		fsym = next;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_arg(काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा tep_prपूर्णांक_arg *farg;

	अगर (!arg)
		वापस;

	चयन (arg->type) अणु
	हाल TEP_PRINT_ATOM:
		मुक्त(arg->atom.atom);
		अवरोध;
	हाल TEP_PRINT_FIELD:
		मुक्त(arg->field.name);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
		मुक्त_arg(arg->flags.field);
		मुक्त(arg->flags.delim);
		मुक्त_flag_sym(arg->flags.flags);
		अवरोध;
	हाल TEP_PRINT_SYMBOL:
		मुक्त_arg(arg->symbol.field);
		मुक्त_flag_sym(arg->symbol.symbols);
		अवरोध;
	हाल TEP_PRINT_HEX:
	हाल TEP_PRINT_HEX_STR:
		मुक्त_arg(arg->hex.field);
		मुक्त_arg(arg->hex.size);
		अवरोध;
	हाल TEP_PRINT_INT_ARRAY:
		मुक्त_arg(arg->पूर्णांक_array.field);
		मुक्त_arg(arg->पूर्णांक_array.count);
		मुक्त_arg(arg->पूर्णांक_array.el_size);
		अवरोध;
	हाल TEP_PRINT_TYPE:
		मुक्त(arg->typecast.type);
		मुक्त_arg(arg->typecast.item);
		अवरोध;
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BSTRING:
		मुक्त(arg->string.string);
		अवरोध;
	हाल TEP_PRINT_BITMASK:
		मुक्त(arg->biपंचांगask.biपंचांगask);
		अवरोध;
	हाल TEP_PRINT_DYNAMIC_ARRAY:
	हाल TEP_PRINT_DYNAMIC_ARRAY_LEN:
		मुक्त(arg->dynarray.index);
		अवरोध;
	हाल TEP_PRINT_OP:
		मुक्त(arg->op.op);
		मुक्त_arg(arg->op.left);
		मुक्त_arg(arg->op.right);
		अवरोध;
	हाल TEP_PRINT_FUNC:
		जबतक (arg->func.args) अणु
			farg = arg->func.args;
			arg->func.args = farg->next;
			मुक्त_arg(farg);
		पूर्ण
		अवरोध;

	हाल TEP_PRINT_शून्य:
	शेष:
		अवरोध;
	पूर्ण

	मुक्त(arg);
पूर्ण

अटल क्रमागत tep_event_type get_type(पूर्णांक ch)
अणु
	अगर (ch == '\n')
		वापस TEP_EVENT_NEWLINE;
	अगर (है_खाली(ch))
		वापस TEP_EVENT_SPACE;
	अगर (है_अक्षर_अंक(ch) || ch == '_')
		वापस TEP_EVENT_ITEM;
	अगर (ch == '\'')
		वापस TEP_EVENT_SQUOTE;
	अगर (ch == '"')
		वापस TEP_EVENT_DQUOTE;
	अगर (!है_छाप(ch))
		वापस TEP_EVENT_NONE;
	अगर (ch == '(' || ch == ')' || ch == ',')
		वापस TEP_EVENT_DELIM;

	वापस TEP_EVENT_OP;
पूर्ण

अटल पूर्णांक __पढ़ो_अक्षर(व्योम)
अणु
	अगर (input_buf_ptr >= input_buf_siz)
		वापस -1;

	वापस input_buf[input_buf_ptr++];
पूर्ण

/**
 * peek_अक्षर - peek at the next अक्षरacter that will be पढ़ो
 *
 * Returns the next अक्षरacter पढ़ो, or -1 अगर end of buffer.
 */
__hidden पूर्णांक peek_अक्षर(व्योम)
अणु
	अगर (input_buf_ptr >= input_buf_siz)
		वापस -1;

	वापस input_buf[input_buf_ptr];
पूर्ण

अटल पूर्णांक extend_token(अक्षर **tok, अक्षर *buf, पूर्णांक size)
अणु
	अक्षर *newtok = पुनः_स्मृति(*tok, size);

	अगर (!newtok) अणु
		मुक्त(*tok);
		*tok = शून्य;
		वापस -1;
	पूर्ण

	अगर (!*tok)
		म_नकल(newtok, buf);
	अन्यथा
		म_जोड़ो(newtok, buf);
	*tok = newtok;

	वापस 0;
पूर्ण

अटल क्रमागत tep_event_type क्रमce_token(स्थिर अक्षर *str, अक्षर **tok);

अटल क्रमागत tep_event_type __पढ़ो_token(अक्षर **tok)
अणु
	अक्षर buf[बफ_मान];
	पूर्णांक ch, last_ch, quote_ch, next_ch;
	पूर्णांक i = 0;
	पूर्णांक tok_size = 0;
	क्रमागत tep_event_type type;

	*tok = शून्य;


	ch = __पढ़ो_अक्षर();
	अगर (ch < 0)
		वापस TEP_EVENT_NONE;

	type = get_type(ch);
	अगर (type == TEP_EVENT_NONE)
		वापस type;

	buf[i++] = ch;

	चयन (type) अणु
	हाल TEP_EVENT_NEWLINE:
	हाल TEP_EVENT_DELIM:
		अगर (aप्र_लिखो(tok, "%c", ch) < 0)
			वापस TEP_EVENT_ERROR;

		वापस type;

	हाल TEP_EVENT_OP:
		चयन (ch) अणु
		हाल '-':
			next_ch = peek_अक्षर();
			अगर (next_ch == '>') अणु
				buf[i++] = __पढ़ो_अक्षर();
				अवरोध;
			पूर्ण
			/* fall through */
		हाल '+':
		हाल '|':
		हाल '&':
		हाल '>':
		हाल '<':
			last_ch = ch;
			ch = peek_अक्षर();
			अगर (ch != last_ch)
				जाओ test_equal;
			buf[i++] = __पढ़ो_अक्षर();
			चयन (last_ch) अणु
			हाल '>':
			हाल '<':
				जाओ test_equal;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		हाल '!':
		हाल '=':
			जाओ test_equal;
		शेष: /* what should we करो instead? */
			अवरोध;
		पूर्ण
		buf[i] = 0;
		*tok = strdup(buf);
		वापस type;

 test_equal:
		ch = peek_अक्षर();
		अगर (ch == '=')
			buf[i++] = __पढ़ो_अक्षर();
		जाओ out;

	हाल TEP_EVENT_DQUOTE:
	हाल TEP_EVENT_SQUOTE:
		/* करोn't keep quotes */
		i--;
		quote_ch = ch;
		last_ch = 0;
 concat:
		करो अणु
			अगर (i == (बफ_मान - 1)) अणु
				buf[i] = 0;
				tok_size += बफ_मान;

				अगर (extend_token(tok, buf, tok_size) < 0)
					वापस TEP_EVENT_NONE;
				i = 0;
			पूर्ण
			last_ch = ch;
			ch = __पढ़ो_अक्षर();
			buf[i++] = ch;
			/* the '\' '\' will cancel itself */
			अगर (ch == '\\' && last_ch == '\\')
				last_ch = 0;
		पूर्ण जबतक (ch != quote_ch || last_ch == '\\');
		/* हटाओ the last quote */
		i--;

		/*
		 * For strings (द्विगुन quotes) check the next token.
		 * If it is another string, concatinate the two.
		 */
		अगर (type == TEP_EVENT_DQUOTE) अणु
			अचिन्हित दीर्घ दीर्घ save_input_buf_ptr = input_buf_ptr;

			करो अणु
				ch = __पढ़ो_अक्षर();
			पूर्ण जबतक (है_खाली(ch));
			अगर (ch == '"')
				जाओ concat;
			input_buf_ptr = save_input_buf_ptr;
		पूर्ण

		जाओ out;

	हाल TEP_EVENT_ERROR ... TEP_EVENT_SPACE:
	हाल TEP_EVENT_ITEM:
	शेष:
		अवरोध;
	पूर्ण

	जबतक (get_type(peek_अक्षर()) == type) अणु
		अगर (i == (बफ_मान - 1)) अणु
			buf[i] = 0;
			tok_size += बफ_मान;

			अगर (extend_token(tok, buf, tok_size) < 0)
				वापस TEP_EVENT_NONE;
			i = 0;
		पूर्ण
		ch = __पढ़ो_अक्षर();
		buf[i++] = ch;
	पूर्ण

 out:
	buf[i] = 0;
	अगर (extend_token(tok, buf, tok_size + i + 1) < 0)
		वापस TEP_EVENT_NONE;

	अगर (type == TEP_EVENT_ITEM) अणु
		/*
		 * Older versions of the kernel has a bug that
		 * creates invalid symbols and will अवरोध the mac80211
		 * parsing. This is a work around to that bug.
		 *
		 * See Linux kernel commit:
		 *  811cb50baf63461ce0bdb234927046131fc7fa8b
		 */
		अगर (म_भेद(*tok, "LOCAL_PR_FMT") == 0) अणु
			मुक्त(*tok);
			*tok = शून्य;
			वापस क्रमce_token("\"%s\" ", tok);
		पूर्ण अन्यथा अगर (म_भेद(*tok, "STA_PR_FMT") == 0) अणु
			मुक्त(*tok);
			*tok = शून्य;
			वापस क्रमce_token("\" sta:%pM\" ", tok);
		पूर्ण अन्यथा अगर (म_भेद(*tok, "VIF_PR_FMT") == 0) अणु
			मुक्त(*tok);
			*tok = शून्य;
			वापस क्रमce_token("\" vif:%p(%d)\" ", tok);
		पूर्ण
	पूर्ण

	वापस type;
पूर्ण

अटल क्रमागत tep_event_type क्रमce_token(स्थिर अक्षर *str, अक्षर **tok)
अणु
	स्थिर अक्षर *save_input_buf;
	अचिन्हित दीर्घ दीर्घ save_input_buf_ptr;
	अचिन्हित दीर्घ दीर्घ save_input_buf_siz;
	क्रमागत tep_event_type type;
	
	/* save off the current input poपूर्णांकers */
	save_input_buf = input_buf;
	save_input_buf_ptr = input_buf_ptr;
	save_input_buf_siz = input_buf_siz;

	init_input_buf(str, म_माप(str));

	type = __पढ़ो_token(tok);

	/* reset back to original token */
	input_buf = save_input_buf;
	input_buf_ptr = save_input_buf_ptr;
	input_buf_siz = save_input_buf_siz;

	वापस type;
पूर्ण

/**
 * मुक्त_token - मुक्त a token वापसed by tep_पढ़ो_token
 * @token: the token to मुक्त
 */
__hidden व्योम मुक्त_token(अक्षर *tok)
अणु
	अगर (tok)
		मुक्त(tok);
पूर्ण

/**
 * पढ़ो_token - access to utilities to use the tep parser
 * @tok: The token to वापस
 *
 * This will parse tokens from the string given by
 * tep_init_data().
 *
 * Returns the token type.
 */
__hidden क्रमागत tep_event_type पढ़ो_token(अक्षर **tok)
अणु
	क्रमागत tep_event_type type;

	क्रम (;;) अणु
		type = __पढ़ो_token(tok);
		अगर (type != TEP_EVENT_SPACE)
			वापस type;

		मुक्त_token(*tok);
	पूर्ण

	/* not reached */
	*tok = शून्य;
	वापस TEP_EVENT_NONE;
पूर्ण

/* no newline */
अटल क्रमागत tep_event_type पढ़ो_token_item(अक्षर **tok)
अणु
	क्रमागत tep_event_type type;

	क्रम (;;) अणु
		type = __पढ़ो_token(tok);
		अगर (type != TEP_EVENT_SPACE && type != TEP_EVENT_NEWLINE)
			वापस type;
		मुक्त_token(*tok);
		*tok = शून्य;
	पूर्ण

	/* not reached */
	*tok = शून्य;
	वापस TEP_EVENT_NONE;
पूर्ण

अटल पूर्णांक test_type(क्रमागत tep_event_type type, क्रमागत tep_event_type expect)
अणु
	अगर (type != expect) अणु
		करो_warning("Error: expected type %d but read %d",
		    expect, type);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक test_type_token(क्रमागत tep_event_type type, स्थिर अक्षर *token,
		    क्रमागत tep_event_type expect, स्थिर अक्षर *expect_tok)
अणु
	अगर (type != expect) अणु
		करो_warning("Error: expected type %d but read %d",
		    expect, type);
		वापस -1;
	पूर्ण

	अगर (म_भेद(token, expect_tok) != 0) अणु
		करो_warning("Error: expected '%s' but read '%s'",
		    expect_tok, token);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __पढ़ो_expect_type(क्रमागत tep_event_type expect, अक्षर **tok, पूर्णांक newline_ok)
अणु
	क्रमागत tep_event_type type;

	अगर (newline_ok)
		type = पढ़ो_token(tok);
	अन्यथा
		type = पढ़ो_token_item(tok);
	वापस test_type(type, expect);
पूर्ण

अटल पूर्णांक पढ़ो_expect_type(क्रमागत tep_event_type expect, अक्षर **tok)
अणु
	वापस __पढ़ो_expect_type(expect, tok, 1);
पूर्ण

अटल पूर्णांक __पढ़ो_expected(क्रमागत tep_event_type expect, स्थिर अक्षर *str,
			   पूर्णांक newline_ok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token;
	पूर्णांक ret;

	अगर (newline_ok)
		type = पढ़ो_token(&token);
	अन्यथा
		type = पढ़ो_token_item(&token);

	ret = test_type_token(type, token, expect, str);

	मुक्त_token(token);

	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_expected(क्रमागत tep_event_type expect, स्थिर अक्षर *str)
अणु
	वापस __पढ़ो_expected(expect, str, 1);
पूर्ण

अटल पूर्णांक पढ़ो_expected_item(क्रमागत tep_event_type expect, स्थिर अक्षर *str)
अणु
	वापस __पढ़ो_expected(expect, str, 0);
पूर्ण

अटल अक्षर *event_पढ़ो_name(व्योम)
अणु
	अक्षर *token;

	अगर (पढ़ो_expected(TEP_EVENT_ITEM, "name") < 0)
		वापस शून्य;

	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस शून्य;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ fail;

	वापस token;

 fail:
	मुक्त_token(token);
	वापस शून्य;
पूर्ण

अटल पूर्णांक event_पढ़ो_id(व्योम)
अणु
	अक्षर *token;
	पूर्णांक id;

	अगर (पढ़ो_expected_item(TEP_EVENT_ITEM, "ID") < 0)
		वापस -1;

	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस -1;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ fail;

	id = म_से_अदीर्घ(token, शून्य, 0);
	मुक्त_token(token);
	वापस id;

 fail:
	मुक्त_token(token);
	वापस -1;
पूर्ण

अटल पूर्णांक field_is_string(काष्ठा tep_क्रमmat_field *field)
अणु
	अगर ((field->flags & TEP_FIELD_IS_ARRAY) &&
	    (म_माला(field->type, "char") || म_माला(field->type, "u8") ||
	     म_माला(field->type, "s8")))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक field_is_dynamic(काष्ठा tep_क्रमmat_field *field)
अणु
	अगर (म_भेदन(field->type, "__data_loc", 10) == 0)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक field_is_दीर्घ(काष्ठा tep_क्रमmat_field *field)
अणु
	/* includes दीर्घ दीर्घ */
	अगर (म_माला(field->type, "long"))
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक type_size(स्थिर अक्षर *name)
अणु
	/* This covers all TEP_FIELD_IS_STRING types. */
	अटल काष्ठा अणु
		स्थिर अक्षर *type;
		अचिन्हित पूर्णांक size;
	पूर्ण table[] = अणु
		अणु "u8",   1 पूर्ण,
		अणु "u16",  2 पूर्ण,
		अणु "u32",  4 पूर्ण,
		अणु "u64",  8 पूर्ण,
		अणु "s8",   1 पूर्ण,
		अणु "s16",  2 पूर्ण,
		अणु "s32",  4 पूर्ण,
		अणु "s64",  8 पूर्ण,
		अणु "char", 1 पूर्ण,
		अणु पूर्ण,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; table[i].type; i++) अणु
		अगर (!म_भेद(table[i].type, name))
			वापस table[i].size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक append(अक्षर **buf, स्थिर अक्षर *delim, स्थिर अक्षर *str)
अणु
	अक्षर *new_buf;

	new_buf = पुनः_स्मृति(*buf, म_माप(*buf) + म_माप(delim) + म_माप(str) + 1);
	अगर (!new_buf)
		वापस -1;
	म_जोड़ो(new_buf, delim);
	म_जोड़ो(new_buf, str);
	*buf = new_buf;
	वापस 0;
पूर्ण

अटल पूर्णांक event_पढ़ो_fields(काष्ठा tep_event *event, काष्ठा tep_क्रमmat_field **fields)
अणु
	काष्ठा tep_क्रमmat_field *field = शून्य;
	क्रमागत tep_event_type type;
	अक्षर *token;
	अक्षर *last_token;
	अक्षर *delim = " ";
	पूर्णांक count = 0;
	पूर्णांक ret;

	करो अणु
		अचिन्हित पूर्णांक size_dynamic = 0;

		type = पढ़ो_token(&token);
		अगर (type == TEP_EVENT_NEWLINE) अणु
			मुक्त_token(token);
			वापस count;
		पूर्ण

		count++;

		अगर (test_type_token(type, token, TEP_EVENT_ITEM, "field"))
			जाओ fail;
		मुक्त_token(token);

		type = पढ़ो_token(&token);
		/*
		 * The ftrace fields may still use the "special" name.
		 * Just ignore it.
		 */
		अगर (event->flags & TEP_EVENT_FL_ISFTRACE &&
		    type == TEP_EVENT_ITEM && म_भेद(token, "special") == 0) अणु
			मुक्त_token(token);
			type = पढ़ो_token(&token);
		पूर्ण

		अगर (test_type_token(type, token, TEP_EVENT_OP, ":") < 0)
			जाओ fail;

		मुक्त_token(token);
		अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
			जाओ fail;

		last_token = token;

		field = सुस्मृति(1, माप(*field));
		अगर (!field)
			जाओ fail;

		field->event = event;

		/* पढ़ो the rest of the type */
		क्रम (;;) अणु
			type = पढ़ो_token(&token);
			अगर (type == TEP_EVENT_ITEM ||
			    (type == TEP_EVENT_OP && म_भेद(token, "*") == 0) ||
			    /*
			     * Some of the ftrace fields are broken and have
			     * an illegal "." in them.
			     */
			    (event->flags & TEP_EVENT_FL_ISFTRACE &&
			     type == TEP_EVENT_OP && म_भेद(token, ".") == 0)) अणु

				अगर (म_भेद(token, "*") == 0)
					field->flags |= TEP_FIELD_IS_POINTER;

				अगर (field->type) अणु
					ret = append(&field->type, delim, last_token);
					मुक्त(last_token);
					अगर (ret < 0)
						जाओ fail;
				पूर्ण अन्यथा
					field->type = last_token;
				last_token = token;
				delim = " ";
				जारी;
			पूर्ण

			/* Handle __attribute__((user)) */
			अगर ((type == TEP_EVENT_DELIM) &&
			    म_भेद("__attribute__", last_token) == 0 &&
			    token[0] == '(') अणु
				पूर्णांक depth = 1;
				पूर्णांक ret;

				ret = append(&field->type, " ", last_token);
				ret |= append(&field->type, "", "(");
				अगर (ret < 0)
					जाओ fail;

				delim = " ";
				जबतक ((type = पढ़ो_token(&token)) != TEP_EVENT_NONE) अणु
					अगर (type == TEP_EVENT_DELIM) अणु
						अगर (token[0] == '(')
							depth++;
						अन्यथा अगर (token[0] == ')')
							depth--;
						अगर (!depth)
							अवरोध;
						ret = append(&field->type, "", token);
						delim = "";
					पूर्ण अन्यथा अणु
						ret = append(&field->type, delim, token);
						delim = " ";
					पूर्ण
					अगर (ret < 0)
						जाओ fail;
					मुक्त(last_token);
					last_token = token;
				पूर्ण
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (!field->type) अणु
			करो_warning_event(event, "%s: no type found", __func__);
			जाओ fail;
		पूर्ण
		field->name = field->alias = last_token;

		अगर (test_type(type, TEP_EVENT_OP))
			जाओ fail;

		अगर (म_भेद(token, "[") == 0) अणु
			क्रमागत tep_event_type last_type = type;
			अक्षर *brackets = token;

			field->flags |= TEP_FIELD_IS_ARRAY;

			type = पढ़ो_token(&token);

			अगर (type == TEP_EVENT_ITEM)
				field->arraylen = म_से_अदीर्घ(token, शून्य, 0);
			अन्यथा
				field->arraylen = 0;

		        जबतक (म_भेद(token, "]") != 0) अणु
				स्थिर अक्षर *delim;

				अगर (last_type == TEP_EVENT_ITEM &&
				    type == TEP_EVENT_ITEM)
					delim = " ";
				अन्यथा
					delim = "";

				last_type = type;

				ret = append(&brackets, delim, token);
				अगर (ret < 0) अणु
					मुक्त(brackets);
					जाओ fail;
				पूर्ण
				/* We only care about the last token */
				field->arraylen = म_से_अदीर्घ(token, शून्य, 0);
				मुक्त_token(token);
				type = पढ़ो_token(&token);
				अगर (type == TEP_EVENT_NONE) अणु
					मुक्त(brackets);
					करो_warning_event(event, "failed to find token");
					जाओ fail;
				पूर्ण
			पूर्ण

			मुक्त_token(token);

			ret = append(&brackets, "", "]");
			अगर (ret < 0) अणु
				मुक्त(brackets);
				जाओ fail;
			पूर्ण

			/* add brackets to type */

			type = पढ़ो_token(&token);
			/*
			 * If the next token is not an OP, then it is of
			 * the क्रमmat: type [] item;
			 */
			अगर (type == TEP_EVENT_ITEM) अणु
				ret = append(&field->type, " ", field->name);
				अगर (ret < 0) अणु
					मुक्त(brackets);
					जाओ fail;
				पूर्ण
				ret = append(&field->type, "", brackets);

				size_dynamic = type_size(field->name);
				मुक्त_token(field->name);
				field->name = field->alias = token;
				type = पढ़ो_token(&token);
			पूर्ण अन्यथा अणु
				ret = append(&field->type, "", brackets);
				अगर (ret < 0) अणु
					मुक्त(brackets);
					जाओ fail;
				पूर्ण
			पूर्ण
			मुक्त(brackets);
		पूर्ण

		अगर (field_is_string(field))
			field->flags |= TEP_FIELD_IS_STRING;
		अगर (field_is_dynamic(field))
			field->flags |= TEP_FIELD_IS_DYNAMIC;
		अगर (field_is_दीर्घ(field))
			field->flags |= TEP_FIELD_IS_LONG;

		अगर (test_type_token(type, token,  TEP_EVENT_OP, ";"))
			जाओ fail;
		मुक्त_token(token);

		अगर (पढ़ो_expected(TEP_EVENT_ITEM, "offset") < 0)
			जाओ fail_expect;

		अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
			जाओ fail_expect;

		अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token))
			जाओ fail;
		field->offset = म_से_अदीर्घ(token, शून्य, 0);
		मुक्त_token(token);

		अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
			जाओ fail_expect;

		अगर (पढ़ो_expected(TEP_EVENT_ITEM, "size") < 0)
			जाओ fail_expect;

		अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
			जाओ fail_expect;

		अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token))
			जाओ fail;
		field->size = म_से_अदीर्घ(token, शून्य, 0);
		मुक्त_token(token);

		अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
			जाओ fail_expect;

		type = पढ़ो_token(&token);
		अगर (type != TEP_EVENT_NEWLINE) अणु
			/* newer versions of the kernel have a "signed" type */
			अगर (test_type_token(type, token, TEP_EVENT_ITEM, "signed"))
				जाओ fail;

			मुक्त_token(token);

			अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
				जाओ fail_expect;

			अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token))
				जाओ fail;

			अगर (म_से_अदीर्घ(token, शून्य, 0))
				field->flags |= TEP_FIELD_IS_SIGNED;

			मुक्त_token(token);
			अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
				जाओ fail_expect;

			अगर (पढ़ो_expect_type(TEP_EVENT_NEWLINE, &token))
				जाओ fail;
		पूर्ण

		मुक्त_token(token);

		अगर (field->flags & TEP_FIELD_IS_ARRAY) अणु
			अगर (field->arraylen)
				field->elementsize = field->size / field->arraylen;
			अन्यथा अगर (field->flags & TEP_FIELD_IS_DYNAMIC)
				field->elementsize = size_dynamic;
			अन्यथा अगर (field->flags & TEP_FIELD_IS_STRING)
				field->elementsize = 1;
			अन्यथा अगर (field->flags & TEP_FIELD_IS_LONG)
				field->elementsize = event->tep ?
						     event->tep->दीर्घ_size :
						     माप(दीर्घ);
		पूर्ण अन्यथा
			field->elementsize = field->size;

		*fields = field;
		fields = &field->next;

	पूर्ण जबतक (1);

	वापस 0;

fail:
	मुक्त_token(token);
fail_expect:
	अगर (field) अणु
		मुक्त(field->type);
		मुक्त(field->name);
		मुक्त(field);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक event_पढ़ो_क्रमmat(काष्ठा tep_event *event)
अणु
	अक्षर *token;
	पूर्णांक ret;

	अगर (पढ़ो_expected_item(TEP_EVENT_ITEM, "format") < 0)
		वापस -1;

	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस -1;

	अगर (पढ़ो_expect_type(TEP_EVENT_NEWLINE, &token))
		जाओ fail;
	मुक्त_token(token);

	ret = event_पढ़ो_fields(event, &event->क्रमmat.common_fields);
	अगर (ret < 0)
		वापस ret;
	event->क्रमmat.nr_common = ret;

	ret = event_पढ़ो_fields(event, &event->क्रमmat.fields);
	अगर (ret < 0)
		वापस ret;
	event->क्रमmat.nr_fields = ret;

	वापस 0;

 fail:
	मुक्त_token(token);
	वापस -1;
पूर्ण

अटल क्रमागत tep_event_type
process_arg_token(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
		  अक्षर **tok, क्रमागत tep_event_type type);

अटल क्रमागत tep_event_type
process_arg(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token;

	type = पढ़ो_token(&token);
	*tok = token;

	वापस process_arg_token(event, arg, tok, type);
पूर्ण

अटल क्रमागत tep_event_type
process_op(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok);

/*
 * For __prपूर्णांक_symbolic() and __prपूर्णांक_flags, we need to completely
 * evaluate the first argument, which defines what to prपूर्णांक next.
 */
अटल क्रमागत tep_event_type
process_field_arg(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	क्रमागत tep_event_type type;

	type = process_arg(event, arg, tok);

	जबतक (type == TEP_EVENT_OP) अणु
		type = process_op(event, arg, tok);
	पूर्ण

	वापस type;
पूर्ण

अटल क्रमागत tep_event_type
process_cond(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *top, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *arg, *left, *right;
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	arg = alloc_arg();
	left = alloc_arg();
	right = alloc_arg();

	अगर (!arg || !left || !right) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		/* arg will be मुक्तd at out_मुक्त */
		मुक्त_arg(left);
		मुक्त_arg(right);
		जाओ out_मुक्त;
	पूर्ण

	arg->type = TEP_PRINT_OP;
	arg->op.left = left;
	arg->op.right = right;

	*tok = शून्य;
	type = process_arg(event, left, &token);

 again:
	अगर (type == TEP_EVENT_ERROR)
		जाओ out_मुक्त;

	/* Handle other operations in the arguments */
	अगर (type == TEP_EVENT_OP && म_भेद(token, ":") != 0) अणु
		type = process_op(event, left, &token);
		जाओ again;
	पूर्ण

	अगर (test_type_token(type, token, TEP_EVENT_OP, ":"))
		जाओ out_मुक्त;

	arg->op.op = token;

	type = process_arg(event, right, &token);

	top->op.right = arg;

	*tok = token;
	वापस type;

out_मुक्त:
	/* Top may poपूर्णांक to itself */
	top->op.right = शून्य;
	मुक्त_token(token);
	मुक्त_arg(arg);
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_array(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *top, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *arg;
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	arg = alloc_arg();
	अगर (!arg) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		/* '*tok' is set to top->op.op.  No need to मुक्त. */
		*tok = शून्य;
		वापस TEP_EVENT_ERROR;
	पूर्ण

	*tok = शून्य;
	type = process_arg(event, arg, &token);
	अगर (test_type_token(type, token, TEP_EVENT_OP, "]"))
		जाओ out_मुक्त;

	top->op.right = arg;

	मुक्त_token(token);
	type = पढ़ो_token_item(&token);
	*tok = token;

	वापस type;

out_मुक्त:
	मुक्त_token(token);
	मुक्त_arg(arg);
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल पूर्णांक get_op_prio(अक्षर *op)
अणु
	अगर (!op[1]) अणु
		चयन (op[0]) अणु
		हाल '~':
		हाल '!':
			वापस 4;
		हाल '*':
		हाल '/':
		हाल '%':
			वापस 6;
		हाल '+':
		हाल '-':
			वापस 7;
			/* '>>' and '<<' are 8 */
		हाल '<':
		हाल '>':
			वापस 9;
			/* '==' and '!=' are 10 */
		हाल '&':
			वापस 11;
		हाल '^':
			वापस 12;
		हाल '|':
			वापस 13;
		हाल '?':
			वापस 16;
		शेष:
			करो_warning("unknown op '%c'", op[0]);
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (म_भेद(op, "++") == 0 ||
		    म_भेद(op, "--") == 0) अणु
			वापस 3;
		पूर्ण अन्यथा अगर (म_भेद(op, ">>") == 0 ||
			   म_भेद(op, "<<") == 0) अणु
			वापस 8;
		पूर्ण अन्यथा अगर (म_भेद(op, ">=") == 0 ||
			   म_भेद(op, "<=") == 0) अणु
			वापस 9;
		पूर्ण अन्यथा अगर (म_भेद(op, "==") == 0 ||
			   म_भेद(op, "!=") == 0) अणु
			वापस 10;
		पूर्ण अन्यथा अगर (म_भेद(op, "&&") == 0) अणु
			वापस 14;
		पूर्ण अन्यथा अगर (म_भेद(op, "||") == 0) अणु
			वापस 15;
		पूर्ण अन्यथा अणु
			करो_warning("unknown op '%s'", op);
			वापस -1;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक set_op_prio(काष्ठा tep_prपूर्णांक_arg *arg)
अणु

	/* single ops are the greatest */
	अगर (!arg->op.left || arg->op.left->type == TEP_PRINT_शून्य)
		arg->op.prio = 0;
	अन्यथा
		arg->op.prio = get_op_prio(arg->op.op);

	वापस arg->op.prio;
पूर्ण

/* Note, *tok करोes not get मुक्तd, but will most likely be saved */
अटल क्रमागत tep_event_type
process_op(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *left, *right = शून्य;
	क्रमागत tep_event_type type;
	अक्षर *token;

	/* the op is passed in via tok */
	token = *tok;

	अगर (arg->type == TEP_PRINT_OP && !arg->op.left) अणु
		/* handle single op */
		अगर (token[1]) अणु
			करो_warning_event(event, "bad op token %s", token);
			जाओ out_मुक्त;
		पूर्ण
		चयन (token[0]) अणु
		हाल '~':
		हाल '!':
		हाल '+':
		हाल '-':
			अवरोध;
		शेष:
			करो_warning_event(event, "bad op token %s", token);
			जाओ out_मुक्त;

		पूर्ण

		/* make an empty left */
		left = alloc_arg();
		अगर (!left)
			जाओ out_warn_मुक्त;

		left->type = TEP_PRINT_शून्य;
		arg->op.left = left;

		right = alloc_arg();
		अगर (!right)
			जाओ out_warn_मुक्त;

		arg->op.right = right;

		/* करो not मुक्त the token, it beदीर्घs to an op */
		*tok = शून्य;
		type = process_arg(event, right, tok);

	पूर्ण अन्यथा अगर (म_भेद(token, "?") == 0) अणु

		left = alloc_arg();
		अगर (!left)
			जाओ out_warn_मुक्त;

		/* copy the top arg to the left */
		*left = *arg;

		arg->type = TEP_PRINT_OP;
		arg->op.op = token;
		arg->op.left = left;
		arg->op.prio = 0;

		/* it will set arg->op.right */
		type = process_cond(event, arg, tok);

	पूर्ण अन्यथा अगर (म_भेद(token, ">>") == 0 ||
		   म_भेद(token, "<<") == 0 ||
		   म_भेद(token, "&") == 0 ||
		   म_भेद(token, "|") == 0 ||
		   म_भेद(token, "&&") == 0 ||
		   म_भेद(token, "||") == 0 ||
		   म_भेद(token, "-") == 0 ||
		   म_भेद(token, "+") == 0 ||
		   म_भेद(token, "*") == 0 ||
		   म_भेद(token, "^") == 0 ||
		   म_भेद(token, "/") == 0 ||
		   म_भेद(token, "%") == 0 ||
		   म_भेद(token, "<") == 0 ||
		   म_भेद(token, ">") == 0 ||
		   म_भेद(token, "<=") == 0 ||
		   म_भेद(token, ">=") == 0 ||
		   म_भेद(token, "==") == 0 ||
		   म_भेद(token, "!=") == 0) अणु

		left = alloc_arg();
		अगर (!left)
			जाओ out_warn_मुक्त;

		/* copy the top arg to the left */
		*left = *arg;

		arg->type = TEP_PRINT_OP;
		arg->op.op = token;
		arg->op.left = left;
		arg->op.right = शून्य;

		अगर (set_op_prio(arg) == -1) अणु
			event->flags |= TEP_EVENT_FL_FAILED;
			/* arg->op.op (= token) will be मुक्तd at out_मुक्त */
			arg->op.op = शून्य;
			जाओ out_मुक्त;
		पूर्ण

		type = पढ़ो_token_item(&token);
		*tok = token;

		/* could just be a type poपूर्णांकer */
		अगर ((म_भेद(arg->op.op, "*") == 0) &&
		    type == TEP_EVENT_DELIM && (म_भेद(token, ")") == 0)) अणु
			पूर्णांक ret;

			अगर (left->type != TEP_PRINT_ATOM) अणु
				करो_warning_event(event, "bad pointer type");
				जाओ out_मुक्त;
			पूर्ण
			ret = append(&left->atom.atom, " ", "*");
			अगर (ret < 0)
				जाओ out_warn_मुक्त;

			मुक्त(arg->op.op);
			*arg = *left;
			मुक्त(left);

			वापस type;
		पूर्ण

		right = alloc_arg();
		अगर (!right)
			जाओ out_warn_मुक्त;

		type = process_arg_token(event, right, tok, type);
		अगर (type == TEP_EVENT_ERROR) अणु
			मुक्त_arg(right);
			/* token was मुक्तd in process_arg_token() via *tok */
			token = शून्य;
			जाओ out_मुक्त;
		पूर्ण

		अगर (right->type == TEP_PRINT_OP &&
		    get_op_prio(arg->op.op) < get_op_prio(right->op.op)) अणु
			काष्ठा tep_prपूर्णांक_arg पंचांगp;

			/* rotate ops according to the priority */
			arg->op.right = right->op.left;

			पंचांगp = *arg;
			*arg = *right;
			*right = पंचांगp;

			arg->op.left = right;
		पूर्ण अन्यथा अणु
			arg->op.right = right;
		पूर्ण

	पूर्ण अन्यथा अगर (म_भेद(token, "[") == 0) अणु

		left = alloc_arg();
		अगर (!left)
			जाओ out_warn_मुक्त;

		*left = *arg;

		arg->type = TEP_PRINT_OP;
		arg->op.op = token;
		arg->op.left = left;

		arg->op.prio = 0;

		/* it will set arg->op.right */
		type = process_array(event, arg, tok);

	पूर्ण अन्यथा अणु
		करो_warning_event(event, "unknown op '%s'", token);
		event->flags |= TEP_EVENT_FL_FAILED;
		/* the arg is now the left side */
		जाओ out_मुक्त;
	पूर्ण

	अगर (type == TEP_EVENT_OP && म_भेद(*tok, ":") != 0) अणु
		पूर्णांक prio;

		/* higher prios need to be बंदr to the root */
		prio = get_op_prio(*tok);

		अगर (prio > arg->op.prio)
			वापस process_op(event, arg, tok);

		वापस process_op(event, right, tok);
	पूर्ण

	वापस type;

out_warn_मुक्त:
	करो_warning_event(event, "%s: not enough memory!", __func__);
out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_entry(काष्ठा tep_event *event __maybe_unused, काष्ठा tep_prपूर्णांक_arg *arg,
	      अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *field;
	अक्षर *token;

	अगर (पढ़ो_expected(TEP_EVENT_OP, "->") < 0)
		जाओ out_err;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ out_मुक्त;
	field = token;

	arg->type = TEP_PRINT_FIELD;
	arg->field.name = field;

	अगर (is_flag_field) अणु
		arg->field.field = tep_find_any_field(event, arg->field.name);
		arg->field.field->flags |= TEP_FIELD_IS_FLAG;
		is_flag_field = 0;
	पूर्ण अन्यथा अगर (is_symbolic_field) अणु
		arg->field.field = tep_find_any_field(event, arg->field.name);
		arg->field.field->flags |= TEP_FIELD_IS_SYMBOLIC;
		is_symbolic_field = 0;
	पूर्ण

	type = पढ़ो_token(&token);
	*tok = token;

	वापस type;

 out_मुक्त:
	मुक्त_token(token);
 out_err:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल पूर्णांक alloc_and_process_delim(काष्ठा tep_event *event, अक्षर *next_token,
				   काष्ठा tep_prपूर्णांक_arg **prपूर्णांक_arg)
अणु
	काष्ठा tep_prपूर्णांक_arg *field;
	क्रमागत tep_event_type type;
	अक्षर *token;
	पूर्णांक ret = 0;

	field = alloc_arg();
	अगर (!field) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		त्रुटि_सं = ENOMEM;
		वापस -1;
	पूर्ण

	type = process_arg(event, field, &token);

	अगर (test_type_token(type, token, TEP_EVENT_DELIM, next_token)) अणु
		त्रुटि_सं = EINVAL;
		ret = -1;
		मुक्त_arg(field);
		जाओ out_मुक्त_token;
	पूर्ण

	*prपूर्णांक_arg = field;

out_मुक्त_token:
	मुक्त_token(token);

	वापस ret;
पूर्ण

अटल अक्षर *arg_eval (काष्ठा tep_prपूर्णांक_arg *arg);

अटल अचिन्हित दीर्घ दीर्घ
eval_type_str(अचिन्हित दीर्घ दीर्घ val, स्थिर अक्षर *type, पूर्णांक poपूर्णांकer)
अणु
	पूर्णांक sign = 0;
	अक्षर *ref;
	पूर्णांक len;

	len = म_माप(type);

	अगर (poपूर्णांकer) अणु

		अगर (type[len-1] != '*') अणु
			करो_warning("pointer expected with non pointer type");
			वापस val;
		पूर्ण

		ref = दो_स्मृति(len);
		अगर (!ref) अणु
			करो_warning("%s: not enough memory!", __func__);
			वापस val;
		पूर्ण
		स_नकल(ref, type, len);

		/* chop off the " *" */
		ref[len - 2] = 0;

		val = eval_type_str(val, ref, 0);
		मुक्त(ref);
		वापस val;
	पूर्ण

	/* check अगर this is a poपूर्णांकer */
	अगर (type[len - 1] == '*')
		वापस val;

	/* Try to figure out the arg size*/
	अगर (म_भेदन(type, "struct", 6) == 0)
		/* all bets off */
		वापस val;

	अगर (म_भेद(type, "u8") == 0)
		वापस val & 0xff;

	अगर (म_भेद(type, "u16") == 0)
		वापस val & 0xffff;

	अगर (म_भेद(type, "u32") == 0)
		वापस val & 0xffffffff;

	अगर (म_भेद(type, "u64") == 0 ||
	    म_भेद(type, "s64") == 0)
		वापस val;

	अगर (म_भेद(type, "s8") == 0)
		वापस (अचिन्हित दीर्घ दीर्घ)(अक्षर)val & 0xff;

	अगर (म_भेद(type, "s16") == 0)
		वापस (अचिन्हित दीर्घ दीर्घ)(लघु)val & 0xffff;

	अगर (म_भेद(type, "s32") == 0)
		वापस (अचिन्हित दीर्घ दीर्घ)(पूर्णांक)val & 0xffffffff;

	अगर (म_भेदन(type, "unsigned ", 9) == 0) अणु
		sign = 0;
		type += 9;
	पूर्ण

	अगर (म_भेद(type, "char") == 0) अणु
		अगर (sign)
			वापस (अचिन्हित दीर्घ दीर्घ)(अक्षर)val & 0xff;
		अन्यथा
			वापस val & 0xff;
	पूर्ण

	अगर (म_भेद(type, "short") == 0) अणु
		अगर (sign)
			वापस (अचिन्हित दीर्घ दीर्घ)(लघु)val & 0xffff;
		अन्यथा
			वापस val & 0xffff;
	पूर्ण

	अगर (म_भेद(type, "int") == 0) अणु
		अगर (sign)
			वापस (अचिन्हित दीर्घ दीर्घ)(पूर्णांक)val & 0xffffffff;
		अन्यथा
			वापस val & 0xffffffff;
	पूर्ण

	वापस val;
पूर्ण

/*
 * Try to figure out the type.
 */
अटल अचिन्हित दीर्घ दीर्घ
eval_type(अचिन्हित दीर्घ दीर्घ val, काष्ठा tep_prपूर्णांक_arg *arg, पूर्णांक poपूर्णांकer)
अणु
	अगर (arg->type != TEP_PRINT_TYPE) अणु
		करो_warning("expected type argument");
		वापस 0;
	पूर्ण

	वापस eval_type_str(val, arg->typecast.type, poपूर्णांकer);
पूर्ण

अटल पूर्णांक arg_num_eval(काष्ठा tep_prपूर्णांक_arg *arg, दीर्घ दीर्घ *val)
अणु
	दीर्घ दीर्घ left, right;
	पूर्णांक ret = 1;

	चयन (arg->type) अणु
	हाल TEP_PRINT_ATOM:
		*val = म_से_दीर्घl(arg->atom.atom, शून्य, 0);
		अवरोध;
	हाल TEP_PRINT_TYPE:
		ret = arg_num_eval(arg->typecast.item, val);
		अगर (!ret)
			अवरोध;
		*val = eval_type(*val, arg, 0);
		अवरोध;
	हाल TEP_PRINT_OP:
		चयन (arg->op.op[0]) अणु
		हाल '|':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			अगर (arg->op.op[1])
				*val = left || right;
			अन्यथा
				*val = left | right;
			अवरोध;
		हाल '&':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			अगर (arg->op.op[1])
				*val = left && right;
			अन्यथा
				*val = left & right;
			अवरोध;
		हाल '<':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			चयन (arg->op.op[1]) अणु
			हाल 0:
				*val = left < right;
				अवरोध;
			हाल '<':
				*val = left << right;
				अवरोध;
			हाल '=':
				*val = left <= right;
				अवरोध;
			शेष:
				करो_warning("unknown op '%s'", arg->op.op);
				ret = 0;
			पूर्ण
			अवरोध;
		हाल '>':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			चयन (arg->op.op[1]) अणु
			हाल 0:
				*val = left > right;
				अवरोध;
			हाल '>':
				*val = left >> right;
				अवरोध;
			हाल '=':
				*val = left >= right;
				अवरोध;
			शेष:
				करो_warning("unknown op '%s'", arg->op.op);
				ret = 0;
			पूर्ण
			अवरोध;
		हाल '=':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;

			अगर (arg->op.op[1] != '=') अणु
				करो_warning("unknown op '%s'", arg->op.op);
				ret = 0;
			पूर्ण अन्यथा
				*val = left == right;
			अवरोध;
		हाल '!':
			ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;

			चयन (arg->op.op[1]) अणु
			हाल '=':
				*val = left != right;
				अवरोध;
			शेष:
				करो_warning("unknown op '%s'", arg->op.op);
				ret = 0;
			पूर्ण
			अवरोध;
		हाल '-':
			/* check क्रम negative */
			अगर (arg->op.left->type == TEP_PRINT_शून्य)
				left = 0;
			अन्यथा
				ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			*val = left - right;
			अवरोध;
		हाल '+':
			अगर (arg->op.left->type == TEP_PRINT_शून्य)
				left = 0;
			अन्यथा
				ret = arg_num_eval(arg->op.left, &left);
			अगर (!ret)
				अवरोध;
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			*val = left + right;
			अवरोध;
		हाल '~':
			ret = arg_num_eval(arg->op.right, &right);
			अगर (!ret)
				अवरोध;
			*val = ~right;
			अवरोध;
		शेष:
			करो_warning("unknown op '%s'", arg->op.op);
			ret = 0;
		पूर्ण
		अवरोध;

	हाल TEP_PRINT_शून्य:
	हाल TEP_PRINT_FIELD ... TEP_PRINT_SYMBOL:
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BSTRING:
	हाल TEP_PRINT_BITMASK:
	शेष:
		करो_warning("invalid eval type %d", arg->type);
		ret = 0;

	पूर्ण
	वापस ret;
पूर्ण

अटल अक्षर *arg_eval (काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	दीर्घ दीर्घ val;
	अटल अक्षर buf[24];

	चयन (arg->type) अणु
	हाल TEP_PRINT_ATOM:
		वापस arg->atom.atom;
	हाल TEP_PRINT_TYPE:
		वापस arg_eval(arg->typecast.item);
	हाल TEP_PRINT_OP:
		अगर (!arg_num_eval(arg, &val))
			अवरोध;
		प्र_लिखो(buf, "%lld", val);
		वापस buf;

	हाल TEP_PRINT_शून्य:
	हाल TEP_PRINT_FIELD ... TEP_PRINT_SYMBOL:
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BSTRING:
	हाल TEP_PRINT_BITMASK:
	शेष:
		करो_warning("invalid eval type %d", arg->type);
		अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत tep_event_type
process_fields(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_flag_sym **list, अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	काष्ठा tep_prपूर्णांक_arg *arg = शून्य;
	काष्ठा tep_prपूर्णांक_flag_sym *field;
	अक्षर *token = *tok;
	अक्षर *value;

	करो अणु
		मुक्त_token(token);
		type = पढ़ो_token_item(&token);
		अगर (test_type_token(type, token, TEP_EVENT_OP, "{"))
			अवरोध;

		arg = alloc_arg();
		अगर (!arg)
			जाओ out_मुक्त;

		मुक्त_token(token);
		type = process_arg(event, arg, &token);

		अगर (type == TEP_EVENT_OP)
			type = process_op(event, arg, &token);

		अगर (type == TEP_EVENT_ERROR)
			जाओ out_मुक्त;

		अगर (test_type_token(type, token, TEP_EVENT_DELIM, ","))
			जाओ out_मुक्त;

		field = सुस्मृति(1, माप(*field));
		अगर (!field)
			जाओ out_मुक्त;

		value = arg_eval(arg);
		अगर (value == शून्य)
			जाओ out_मुक्त_field;
		field->value = strdup(value);
		अगर (field->value == शून्य)
			जाओ out_मुक्त_field;

		मुक्त_arg(arg);
		arg = alloc_arg();
		अगर (!arg)
			जाओ out_मुक्त;

		मुक्त_token(token);
		type = process_arg(event, arg, &token);
		अगर (test_type_token(type, token, TEP_EVENT_OP, "}"))
			जाओ out_मुक्त_field;

		value = arg_eval(arg);
		अगर (value == शून्य)
			जाओ out_मुक्त_field;
		field->str = strdup(value);
		अगर (field->str == शून्य)
			जाओ out_मुक्त_field;
		मुक्त_arg(arg);
		arg = शून्य;

		*list = field;
		list = &field->next;

		मुक्त_token(token);
		type = पढ़ो_token_item(&token);
	पूर्ण जबतक (type == TEP_EVENT_DELIM && म_भेद(token, ",") == 0);

	*tok = token;
	वापस type;

out_मुक्त_field:
	मुक्त_flag_sym(field);
out_मुक्त:
	मुक्त_arg(arg);
	मुक्त_token(token);
	*tok = शून्य;

	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_flags(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *field;
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	स_रखो(arg, 0, माप(*arg));
	arg->type = TEP_PRINT_FLAGS;

	field = alloc_arg();
	अगर (!field) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		जाओ out_मुक्त;
	पूर्ण

	type = process_field_arg(event, field, &token);

	/* Handle operations in the first argument */
	जबतक (type == TEP_EVENT_OP)
		type = process_op(event, field, &token);

	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ","))
		जाओ out_मुक्त_field;
	मुक्त_token(token);

	arg->flags.field = field;

	type = पढ़ो_token_item(&token);
	अगर (event_item_type(type)) अणु
		arg->flags.delim = token;
		type = पढ़ो_token_item(&token);
	पूर्ण

	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ","))
		जाओ out_मुक्त;

	type = process_fields(event, &arg->flags.flags, &token);
	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ")"))
		जाओ out_मुक्त;

	मुक्त_token(token);
	type = पढ़ो_token_item(tok);
	वापस type;

out_मुक्त_field:
	मुक्त_arg(field);
out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_symbols(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *field;
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	स_रखो(arg, 0, माप(*arg));
	arg->type = TEP_PRINT_SYMBOL;

	field = alloc_arg();
	अगर (!field) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		जाओ out_मुक्त;
	पूर्ण

	type = process_field_arg(event, field, &token);

	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ","))
		जाओ out_मुक्त_field;

	arg->symbol.field = field;

	type = process_fields(event, &arg->symbol.symbols, &token);
	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ")"))
		जाओ out_मुक्त;

	मुक्त_token(token);
	type = पढ़ो_token_item(tok);
	वापस type;

out_मुक्त_field:
	मुक्त_arg(field);
out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_hex_common(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
		   अक्षर **tok, क्रमागत tep_prपूर्णांक_arg_type type)
अणु
	स_रखो(arg, 0, माप(*arg));
	arg->type = type;

	अगर (alloc_and_process_delim(event, ",", &arg->hex.field))
		जाओ out;

	अगर (alloc_and_process_delim(event, ")", &arg->hex.size))
		जाओ मुक्त_field;

	वापस पढ़ो_token_item(tok);

मुक्त_field:
	मुक्त_arg(arg->hex.field);
	arg->hex.field = शून्य;
out:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_hex(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	वापस process_hex_common(event, arg, tok, TEP_PRINT_HEX);
पूर्ण

अटल क्रमागत tep_event_type
process_hex_str(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
		अक्षर **tok)
अणु
	वापस process_hex_common(event, arg, tok, TEP_PRINT_HEX_STR);
पूर्ण

अटल क्रमागत tep_event_type
process_पूर्णांक_array(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	स_रखो(arg, 0, माप(*arg));
	arg->type = TEP_PRINT_INT_ARRAY;

	अगर (alloc_and_process_delim(event, ",", &arg->पूर्णांक_array.field))
		जाओ out;

	अगर (alloc_and_process_delim(event, ",", &arg->पूर्णांक_array.count))
		जाओ मुक्त_field;

	अगर (alloc_and_process_delim(event, ")", &arg->पूर्णांक_array.el_size))
		जाओ मुक्त_size;

	वापस पढ़ो_token_item(tok);

मुक्त_size:
	मुक्त_arg(arg->पूर्णांक_array.count);
	arg->पूर्णांक_array.count = शून्य;
मुक्त_field:
	मुक्त_arg(arg->पूर्णांक_array.field);
	arg->पूर्णांक_array.field = शून्य;
out:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_dynamic_array(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_क्रमmat_field *field;
	क्रमागत tep_event_type type;
	अक्षर *token;

	स_रखो(arg, 0, माप(*arg));
	arg->type = TEP_PRINT_DYNAMIC_ARRAY;

	/*
	 * The item within the parenthesis is another field that holds
	 * the index पूर्णांकo where the array starts.
	 */
	type = पढ़ो_token(&token);
	*tok = token;
	अगर (type != TEP_EVENT_ITEM)
		जाओ out_मुक्त;

	/* Find the field */

	field = tep_find_field(event, token);
	अगर (!field)
		जाओ out_मुक्त;

	arg->dynarray.field = field;
	arg->dynarray.index = 0;

	अगर (पढ़ो_expected(TEP_EVENT_DELIM, ")") < 0)
		जाओ out_मुक्त;

	मुक्त_token(token);
	type = पढ़ो_token_item(&token);
	*tok = token;
	अगर (type != TEP_EVENT_OP || म_भेद(token, "[") != 0)
		वापस type;

	मुक्त_token(token);
	arg = alloc_arg();
	अगर (!arg) अणु
		करो_warning_event(event, "%s: not enough memory!", __func__);
		*tok = शून्य;
		वापस TEP_EVENT_ERROR;
	पूर्ण

	type = process_arg(event, arg, &token);
	अगर (type == TEP_EVENT_ERROR)
		जाओ out_मुक्त_arg;

	अगर (!test_type_token(type, token, TEP_EVENT_OP, "]"))
		जाओ out_मुक्त_arg;

	मुक्त_token(token);
	type = पढ़ो_token_item(tok);
	वापस type;

 out_मुक्त_arg:
	मुक्त_arg(arg);
 out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_dynamic_array_len(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
			  अक्षर **tok)
अणु
	काष्ठा tep_क्रमmat_field *field;
	क्रमागत tep_event_type type;
	अक्षर *token;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ out_मुक्त;

	arg->type = TEP_PRINT_DYNAMIC_ARRAY_LEN;

	/* Find the field */
	field = tep_find_field(event, token);
	अगर (!field)
		जाओ out_मुक्त;

	arg->dynarray.field = field;
	arg->dynarray.index = 0;

	अगर (पढ़ो_expected(TEP_EVENT_DELIM, ")") < 0)
		जाओ out_err;

	मुक्त_token(token);
	type = पढ़ो_token(&token);
	*tok = token;

	वापस type;

 out_मुक्त:
	मुक्त_token(token);
 out_err:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_paren(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg *item_arg;
	क्रमागत tep_event_type type;
	अक्षर *token;

	type = process_arg(event, arg, &token);

	अगर (type == TEP_EVENT_ERROR)
		जाओ out_मुक्त;

	अगर (type == TEP_EVENT_OP)
		type = process_op(event, arg, &token);

	अगर (type == TEP_EVENT_ERROR)
		जाओ out_मुक्त;

	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ")"))
		जाओ out_मुक्त;

	मुक्त_token(token);
	type = पढ़ो_token_item(&token);

	/*
	 * If the next token is an item or another खोलो paren, then
	 * this was a typecast.
	 */
	अगर (event_item_type(type) ||
	    (type == TEP_EVENT_DELIM && म_भेद(token, "(") == 0)) अणु

		/* make this a typecast and contine */

		/* prevous must be an atom */
		अगर (arg->type != TEP_PRINT_ATOM) अणु
			करो_warning_event(event, "previous needed to be TEP_PRINT_ATOM");
			जाओ out_मुक्त;
		पूर्ण

		item_arg = alloc_arg();
		अगर (!item_arg) अणु
			करो_warning_event(event, "%s: not enough memory!",
					 __func__);
			जाओ out_मुक्त;
		पूर्ण

		arg->type = TEP_PRINT_TYPE;
		arg->typecast.type = arg->atom.atom;
		arg->typecast.item = item_arg;
		type = process_arg_token(event, item_arg, &token, type);

	पूर्ण

	*tok = token;
	वापस type;

 out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण


अटल क्रमागत tep_event_type
process_str(काष्ठा tep_event *event __maybe_unused, काष्ठा tep_prपूर्णांक_arg *arg,
	    अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ out_मुक्त;

	arg->type = TEP_PRINT_STRING;
	arg->string.string = token;
	arg->string.offset = -1;

	अगर (पढ़ो_expected(TEP_EVENT_DELIM, ")") < 0)
		जाओ out_err;

	type = पढ़ो_token(&token);
	*tok = token;

	वापस type;

 out_मुक्त:
	मुक्त_token(token);
 out_err:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_biपंचांगask(काष्ठा tep_event *event __maybe_unused, काष्ठा tep_prपूर्णांक_arg *arg,
		अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token;

	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ out_मुक्त;

	arg->type = TEP_PRINT_BITMASK;
	arg->biपंचांगask.biपंचांगask = token;
	arg->biपंचांगask.offset = -1;

	अगर (पढ़ो_expected(TEP_EVENT_DELIM, ")") < 0)
		जाओ out_err;

	type = पढ़ो_token(&token);
	*tok = token;

	वापस type;

 out_मुक्त:
	मुक्त_token(token);
 out_err:
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल काष्ठा tep_function_handler *
find_func_handler(काष्ठा tep_handle *tep, अक्षर *func_name)
अणु
	काष्ठा tep_function_handler *func;

	अगर (!tep)
		वापस शून्य;

	क्रम (func = tep->func_handlers; func; func = func->next) अणु
		अगर (म_भेद(func->name, func_name) == 0)
			अवरोध;
	पूर्ण

	वापस func;
पूर्ण

अटल व्योम हटाओ_func_handler(काष्ठा tep_handle *tep, अक्षर *func_name)
अणु
	काष्ठा tep_function_handler *func;
	काष्ठा tep_function_handler **next;

	next = &tep->func_handlers;
	जबतक ((func = *next)) अणु
		अगर (म_भेद(func->name, func_name) == 0) अणु
			*next = func->next;
			मुक्त_func_handle(func);
			अवरोध;
		पूर्ण
		next = &func->next;
	पूर्ण
पूर्ण

अटल क्रमागत tep_event_type
process_func_handler(काष्ठा tep_event *event, काष्ठा tep_function_handler *func,
		     काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	काष्ठा tep_prपूर्णांक_arg **next_arg;
	काष्ठा tep_prपूर्णांक_arg *farg;
	क्रमागत tep_event_type type;
	अक्षर *token;
	पूर्णांक i;

	arg->type = TEP_PRINT_FUNC;
	arg->func.func = func;

	*tok = शून्य;

	next_arg = &(arg->func.args);
	क्रम (i = 0; i < func->nr_args; i++) अणु
		farg = alloc_arg();
		अगर (!farg) अणु
			करो_warning_event(event, "%s: not enough memory!",
					 __func__);
			वापस TEP_EVENT_ERROR;
		पूर्ण

		type = process_arg(event, farg, &token);
		अगर (i < (func->nr_args - 1)) अणु
			अगर (type != TEP_EVENT_DELIM || म_भेद(token, ",") != 0) अणु
				करो_warning_event(event,
					"Error: function '%s()' expects %d arguments but event %s only uses %d",
					func->name, func->nr_args,
					event->name, i + 1);
				जाओ err;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (type != TEP_EVENT_DELIM || म_भेद(token, ")") != 0) अणु
				करो_warning_event(event,
					"Error: function '%s()' only expects %d arguments but event %s has more",
					func->name, func->nr_args, event->name);
				जाओ err;
			पूर्ण
		पूर्ण

		*next_arg = farg;
		next_arg = &(farg->next);
		मुक्त_token(token);
	पूर्ण

	type = पढ़ो_token(&token);
	*tok = token;

	वापस type;

err:
	मुक्त_arg(farg);
	मुक्त_token(token);
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_builtin_expect(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg, अक्षर **tok)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token = शून्य;

	/* Handle __builtin_expect( cond, #) */
	type = process_arg(event, arg, &token);

	अगर (type != TEP_EVENT_DELIM || token[0] != ',')
		जाओ out_मुक्त;

	मुक्त_token(token);

	/* We करोn't care what the second parameter is of the __builtin_expect() */
	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ out_मुक्त;

	अगर (पढ़ो_expected(TEP_EVENT_DELIM, ")") < 0)
		जाओ out_मुक्त;

	मुक्त_token(token);
	type = पढ़ो_token_item(tok);
	वापस type;

out_मुक्त:
	मुक्त_token(token);
	*tok = शून्य;
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_function(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
		 अक्षर *token, अक्षर **tok)
अणु
	काष्ठा tep_function_handler *func;

	अगर (म_भेद(token, "__print_flags") == 0) अणु
		मुक्त_token(token);
		is_flag_field = 1;
		वापस process_flags(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__print_symbolic") == 0) अणु
		मुक्त_token(token);
		is_symbolic_field = 1;
		वापस process_symbols(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__print_hex") == 0) अणु
		मुक्त_token(token);
		वापस process_hex(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__print_hex_str") == 0) अणु
		मुक्त_token(token);
		वापस process_hex_str(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__print_array") == 0) अणु
		मुक्त_token(token);
		वापस process_पूर्णांक_array(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__get_str") == 0) अणु
		मुक्त_token(token);
		वापस process_str(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__get_bitmask") == 0) अणु
		मुक्त_token(token);
		वापस process_biपंचांगask(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__get_dynamic_array") == 0) अणु
		मुक्त_token(token);
		वापस process_dynamic_array(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__get_dynamic_array_len") == 0) अणु
		मुक्त_token(token);
		वापस process_dynamic_array_len(event, arg, tok);
	पूर्ण
	अगर (म_भेद(token, "__builtin_expect") == 0) अणु
		मुक्त_token(token);
		वापस process_builtin_expect(event, arg, tok);
	पूर्ण

	func = find_func_handler(event->tep, token);
	अगर (func) अणु
		मुक्त_token(token);
		वापस process_func_handler(event, func, arg, tok);
	पूर्ण

	करो_warning_event(event, "function %s not defined", token);
	मुक्त_token(token);
	वापस TEP_EVENT_ERROR;
पूर्ण

अटल क्रमागत tep_event_type
process_arg_token(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg,
		  अक्षर **tok, क्रमागत tep_event_type type)
अणु
	अक्षर *token;
	अक्षर *atom;

	token = *tok;

	चयन (type) अणु
	हाल TEP_EVENT_ITEM:
		अगर (म_भेद(token, "REC") == 0) अणु
			मुक्त_token(token);
			type = process_entry(event, arg, &token);
			अवरोध;
		पूर्ण
		atom = token;
		/* test the next token */
		type = पढ़ो_token_item(&token);

		/*
		 * If the next token is a parenthesis, then this
		 * is a function.
		 */
		अगर (type == TEP_EVENT_DELIM && म_भेद(token, "(") == 0) अणु
			मुक्त_token(token);
			token = शून्य;
			/* this will मुक्त atom. */
			type = process_function(event, arg, atom, &token);
			अवरोध;
		पूर्ण
		/* atoms can be more than one token दीर्घ */
		जबतक (type == TEP_EVENT_ITEM) अणु
			पूर्णांक ret;

			ret = append(&atom, " ", token);
			अगर (ret < 0) अणु
				मुक्त(atom);
				*tok = शून्य;
				मुक्त_token(token);
				वापस TEP_EVENT_ERROR;
			पूर्ण
			मुक्त_token(token);
			type = पढ़ो_token_item(&token);
		पूर्ण

		arg->type = TEP_PRINT_ATOM;
		arg->atom.atom = atom;
		अवरोध;

	हाल TEP_EVENT_DQUOTE:
	हाल TEP_EVENT_SQUOTE:
		arg->type = TEP_PRINT_ATOM;
		arg->atom.atom = token;
		type = पढ़ो_token_item(&token);
		अवरोध;
	हाल TEP_EVENT_DELIM:
		अगर (म_भेद(token, "(") == 0) अणु
			मुक्त_token(token);
			type = process_paren(event, arg, &token);
			अवरोध;
		पूर्ण
	हाल TEP_EVENT_OP:
		/* handle single ops */
		arg->type = TEP_PRINT_OP;
		arg->op.op = token;
		arg->op.left = शून्य;
		type = process_op(event, arg, &token);

		/* On error, the op is मुक्तd */
		अगर (type == TEP_EVENT_ERROR)
			arg->op.op = शून्य;

		/* वापस error type अगर errored */
		अवरोध;

	हाल TEP_EVENT_ERROR ... TEP_EVENT_NEWLINE:
	शेष:
		करो_warning_event(event, "unexpected type %d", type);
		वापस TEP_EVENT_ERROR;
	पूर्ण
	*tok = token;

	वापस type;
पूर्ण

अटल पूर्णांक event_पढ़ो_prपूर्णांक_args(काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg **list)
अणु
	क्रमागत tep_event_type type = TEP_EVENT_ERROR;
	काष्ठा tep_prपूर्णांक_arg *arg;
	अक्षर *token;
	पूर्णांक args = 0;

	करो अणु
		अगर (type == TEP_EVENT_NEWLINE) अणु
			type = पढ़ो_token_item(&token);
			जारी;
		पूर्ण

		arg = alloc_arg();
		अगर (!arg) अणु
			करो_warning_event(event, "%s: not enough memory!",
					 __func__);
			वापस -1;
		पूर्ण

		type = process_arg(event, arg, &token);

		अगर (type == TEP_EVENT_ERROR) अणु
			मुक्त_token(token);
			मुक्त_arg(arg);
			वापस -1;
		पूर्ण

		*list = arg;
		args++;

		अगर (type == TEP_EVENT_OP) अणु
			type = process_op(event, arg, &token);
			मुक्त_token(token);
			अगर (type == TEP_EVENT_ERROR) अणु
				*list = शून्य;
				मुक्त_arg(arg);
				वापस -1;
			पूर्ण
			list = &arg->next;
			जारी;
		पूर्ण

		अगर (type == TEP_EVENT_DELIM && म_भेद(token, ",") == 0) अणु
			मुक्त_token(token);
			*list = arg;
			list = &arg->next;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (type != TEP_EVENT_NONE);

	अगर (type != TEP_EVENT_NONE && type != TEP_EVENT_ERROR)
		मुक्त_token(token);

	वापस args;
पूर्ण

अटल पूर्णांक event_पढ़ो_prपूर्णांक(काष्ठा tep_event *event)
अणु
	क्रमागत tep_event_type type;
	अक्षर *token;
	पूर्णांक ret;

	अगर (पढ़ो_expected_item(TEP_EVENT_ITEM, "print") < 0)
		वापस -1;

	अगर (पढ़ो_expected(TEP_EVENT_ITEM, "fmt") < 0)
		वापस -1;

	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस -1;

	अगर (पढ़ो_expect_type(TEP_EVENT_DQUOTE, &token) < 0)
		जाओ fail;

 concat:
	event->prपूर्णांक_fmt.क्रमmat = token;
	event->prपूर्णांक_fmt.args = शून्य;

	/* ok to have no arg */
	type = पढ़ो_token_item(&token);

	अगर (type == TEP_EVENT_NONE)
		वापस 0;

	/* Handle concatenation of prपूर्णांक lines */
	अगर (type == TEP_EVENT_DQUOTE) अणु
		अक्षर *cat;

		अगर (aप्र_लिखो(&cat, "%s%s", event->prपूर्णांक_fmt.क्रमmat, token) < 0)
			जाओ fail;
		मुक्त_token(token);
		मुक्त_token(event->prपूर्णांक_fmt.क्रमmat);
		event->prपूर्णांक_fmt.क्रमmat = शून्य;
		token = cat;
		जाओ concat;
	पूर्ण
			     
	अगर (test_type_token(type, token, TEP_EVENT_DELIM, ","))
		जाओ fail;

	मुक्त_token(token);

	ret = event_पढ़ो_prपूर्णांक_args(event, &event->prपूर्णांक_fmt.args);
	अगर (ret < 0)
		वापस -1;

	वापस ret;

 fail:
	मुक्त_token(token);
	वापस -1;
पूर्ण

/**
 * tep_find_common_field - वापस a common field by event
 * @event: handle क्रम the event
 * @name: the name of the common field to वापस
 *
 * Returns a common field from the event by the given @name.
 * This only searches the common fields and not all field.
 */
काष्ठा tep_क्रमmat_field *
tep_find_common_field(काष्ठा tep_event *event, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *क्रमmat;

	क्रम (क्रमmat = event->क्रमmat.common_fields;
	     क्रमmat; क्रमmat = क्रमmat->next) अणु
		अगर (म_भेद(क्रमmat->name, name) == 0)
			अवरोध;
	पूर्ण

	वापस क्रमmat;
पूर्ण

/**
 * tep_find_field - find a non-common field
 * @event: handle क्रम the event
 * @name: the name of the non-common field
 *
 * Returns a non-common field by the given @name.
 * This करोes not search common fields.
 */
काष्ठा tep_क्रमmat_field *
tep_find_field(काष्ठा tep_event *event, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *क्रमmat;

	क्रम (क्रमmat = event->क्रमmat.fields;
	     क्रमmat; क्रमmat = क्रमmat->next) अणु
		अगर (म_भेद(क्रमmat->name, name) == 0)
			अवरोध;
	पूर्ण

	वापस क्रमmat;
पूर्ण

/**
 * tep_find_any_field - find any field by name
 * @event: handle क्रम the event
 * @name: the name of the field
 *
 * Returns a field by the given @name.
 * This searches the common field names first, then
 * the non-common ones अगर a common one was not found.
 */
काष्ठा tep_क्रमmat_field *
tep_find_any_field(काष्ठा tep_event *event, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *क्रमmat;

	क्रमmat = tep_find_common_field(event, name);
	अगर (क्रमmat)
		वापस क्रमmat;
	वापस tep_find_field(event, name);
पूर्ण

/**
 * tep_पढ़ो_number - पढ़ो a number from data
 * @tep: a handle to the trace event parser context
 * @ptr: the raw data
 * @size: the size of the data that holds the number
 *
 * Returns the number (converted to host) from the
 * raw data.
 */
अचिन्हित दीर्घ दीर्घ tep_पढ़ो_number(काष्ठा tep_handle *tep,
				   स्थिर व्योम *ptr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	चयन (size) अणु
	हाल 1:
		वापस *(अचिन्हित अक्षर *)ptr;
	हाल 2:
		वापस data2host2(tep, *(अचिन्हित लघु *)ptr);
	हाल 4:
		वापस data2host4(tep, *(अचिन्हित पूर्णांक *)ptr);
	हाल 8:
		स_नकल(&val, (ptr), माप(अचिन्हित दीर्घ दीर्घ));
		वापस data2host8(tep, val);
	शेष:
		/* BUG! */
		वापस 0;
	पूर्ण
पूर्ण

/**
 * tep_पढ़ो_number_field - पढ़ो a number from data
 * @field: a handle to the field
 * @data: the raw data to पढ़ो
 * @value: the value to place the number in
 *
 * Reads raw data according to a field offset and size,
 * and translates it पूर्णांकo @value.
 *
 * Returns 0 on success, -1 otherwise.
 */
पूर्णांक tep_पढ़ो_number_field(काष्ठा tep_क्रमmat_field *field, स्थिर व्योम *data,
			  अचिन्हित दीर्घ दीर्घ *value)
अणु
	अगर (!field)
		वापस -1;
	चयन (field->size) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		*value = tep_पढ़ो_number(field->event->tep,
					 data + field->offset, field->size);
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक get_common_info(काष्ठा tep_handle *tep,
			   स्थिर अक्षर *type, पूर्णांक *offset, पूर्णांक *size)
अणु
	काष्ठा tep_event *event;
	काष्ठा tep_क्रमmat_field *field;

	/*
	 * All events should have the same common elements.
	 * Pick any event to find where the type is;
	 */
	अगर (!tep->events) अणु
		करो_warning("no event_list!");
		वापस -1;
	पूर्ण

	event = tep->events[0];
	field = tep_find_common_field(event, type);
	अगर (!field)
		वापस -1;

	*offset = field->offset;
	*size = field->size;

	वापस 0;
पूर्ण

अटल पूर्णांक __parse_common(काष्ठा tep_handle *tep, व्योम *data,
			  पूर्णांक *size, पूर्णांक *offset, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	अगर (!*size) अणु
		ret = get_common_info(tep, name, offset, size);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस tep_पढ़ो_number(tep, data + *offset, *size);
पूर्ण

अटल पूर्णांक trace_parse_common_type(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->type_size, &tep->type_offset,
			      "common_type");
पूर्ण

अटल पूर्णांक parse_common_pid(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->pid_size, &tep->pid_offset,
			      "common_pid");
पूर्ण

अटल पूर्णांक parse_common_pc(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->pc_size, &tep->pc_offset,
			      "common_preempt_count");
पूर्ण

अटल पूर्णांक parse_common_flags(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->flags_size, &tep->flags_offset,
			      "common_flags");
पूर्ण

अटल पूर्णांक parse_common_lock_depth(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->ld_size, &tep->ld_offset,
			      "common_lock_depth");
पूर्ण

अटल पूर्णांक parse_common_migrate_disable(काष्ठा tep_handle *tep, व्योम *data)
अणु
	वापस __parse_common(tep, data,
			      &tep->ld_size, &tep->ld_offset,
			      "common_migrate_disable");
पूर्ण

अटल पूर्णांक events_id_cmp(स्थिर व्योम *a, स्थिर व्योम *b);

/**
 * tep_find_event - find an event by given id
 * @tep: a handle to the trace event parser context
 * @id: the id of the event
 *
 * Returns an event that has a given @id.
 */
काष्ठा tep_event *tep_find_event(काष्ठा tep_handle *tep, पूर्णांक id)
अणु
	काष्ठा tep_event **eventptr;
	काष्ठा tep_event key;
	काष्ठा tep_event *pkey = &key;

	/* Check cache first */
	अगर (tep->last_event && tep->last_event->id == id)
		वापस tep->last_event;

	key.id = id;

	eventptr = द्वा_खोज(&pkey, tep->events, tep->nr_events,
			   माप(*tep->events), events_id_cmp);

	अगर (eventptr) अणु
		tep->last_event = *eventptr;
		वापस *eventptr;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * tep_find_event_by_name - find an event by given name
 * @tep: a handle to the trace event parser context
 * @sys: the प्रणाली name to search क्रम
 * @name: the name of the event to search क्रम
 *
 * This वापसs an event with a given @name and under the प्रणाली
 * @sys. If @sys is शून्य the first event with @name is वापसed.
 */
काष्ठा tep_event *
tep_find_event_by_name(काष्ठा tep_handle *tep,
		       स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	काष्ठा tep_event *event = शून्य;
	पूर्णांक i;

	अगर (tep->last_event &&
	    म_भेद(tep->last_event->name, name) == 0 &&
	    (!sys || म_भेद(tep->last_event->प्रणाली, sys) == 0))
		वापस tep->last_event;

	क्रम (i = 0; i < tep->nr_events; i++) अणु
		event = tep->events[i];
		अगर (म_भेद(event->name, name) == 0) अणु
			अगर (!sys)
				अवरोध;
			अगर (म_भेद(event->प्रणाली, sys) == 0)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == tep->nr_events)
		event = शून्य;

	tep->last_event = event;
	वापस event;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
eval_num_arg(व्योम *data, पूर्णांक size, काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा tep_handle *tep = event->tep;
	अचिन्हित दीर्घ दीर्घ val = 0;
	अचिन्हित दीर्घ दीर्घ left, right;
	काष्ठा tep_prपूर्णांक_arg *typearg = शून्य;
	काष्ठा tep_prपूर्णांक_arg *larg;
	अचिन्हित दीर्घ offset;
	अचिन्हित पूर्णांक field_size;

	चयन (arg->type) अणु
	हाल TEP_PRINT_शून्य:
		/* ?? */
		वापस 0;
	हाल TEP_PRINT_ATOM:
		वापस म_से_अदीर्घl(arg->atom.atom, शून्य, 0);
	हाल TEP_PRINT_FIELD:
		अगर (!arg->field.field) अणु
			arg->field.field = tep_find_any_field(event, arg->field.name);
			अगर (!arg->field.field)
				जाओ out_warning_field;
			
		पूर्ण
		/* must be a number */
		val = tep_पढ़ो_number(tep, data + arg->field.field->offset,
				      arg->field.field->size);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
	हाल TEP_PRINT_SYMBOL:
	हाल TEP_PRINT_INT_ARRAY:
	हाल TEP_PRINT_HEX:
	हाल TEP_PRINT_HEX_STR:
		अवरोध;
	हाल TEP_PRINT_TYPE:
		val = eval_num_arg(data, size, event, arg->typecast.item);
		वापस eval_type(val, arg, 0);
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BSTRING:
	हाल TEP_PRINT_BITMASK:
		वापस 0;
	हाल TEP_PRINT_FUNC: अणु
		काष्ठा trace_seq s;
		trace_seq_init(&s);
		val = process_defined_func(&s, data, size, event, arg);
		trace_seq_destroy(&s);
		वापस val;
	पूर्ण
	हाल TEP_PRINT_OP:
		अगर (म_भेद(arg->op.op, "[") == 0) अणु
			/*
			 * Arrays are special, since we करोn't want
			 * to पढ़ो the arg as is.
			 */
			right = eval_num_arg(data, size, event, arg->op.right);

			/* handle typecasts */
			larg = arg->op.left;
			जबतक (larg->type == TEP_PRINT_TYPE) अणु
				अगर (!typearg)
					typearg = larg;
				larg = larg->typecast.item;
			पूर्ण

			/* Default to दीर्घ size */
			field_size = tep->दीर्घ_size;

			चयन (larg->type) अणु
			हाल TEP_PRINT_DYNAMIC_ARRAY:
				offset = tep_पढ़ो_number(tep,
						   data + larg->dynarray.field->offset,
						   larg->dynarray.field->size);
				अगर (larg->dynarray.field->elementsize)
					field_size = larg->dynarray.field->elementsize;
				/*
				 * The actual length of the dynamic array is stored
				 * in the top half of the field, and the offset
				 * is in the bottom half of the 32 bit field.
				 */
				offset &= 0xffff;
				offset += right;
				अवरोध;
			हाल TEP_PRINT_FIELD:
				अगर (!larg->field.field) अणु
					larg->field.field =
						tep_find_any_field(event, larg->field.name);
					अगर (!larg->field.field) अणु
						arg = larg;
						जाओ out_warning_field;
					पूर्ण
				पूर्ण
				field_size = larg->field.field->elementsize;
				offset = larg->field.field->offset +
					right * larg->field.field->elementsize;
				अवरोध;
			शेष:
				जाओ शेष_op; /* oops, all bets off */
			पूर्ण
			val = tep_पढ़ो_number(tep,
					      data + offset, field_size);
			अगर (typearg)
				val = eval_type(val, typearg, 1);
			अवरोध;
		पूर्ण अन्यथा अगर (म_भेद(arg->op.op, "?") == 0) अणु
			left = eval_num_arg(data, size, event, arg->op.left);
			arg = arg->op.right;
			अगर (left)
				val = eval_num_arg(data, size, event, arg->op.left);
			अन्यथा
				val = eval_num_arg(data, size, event, arg->op.right);
			अवरोध;
		पूर्ण
 शेष_op:
		left = eval_num_arg(data, size, event, arg->op.left);
		right = eval_num_arg(data, size, event, arg->op.right);
		चयन (arg->op.op[0]) अणु
		हाल '!':
			चयन (arg->op.op[1]) अणु
			हाल 0:
				val = !right;
				अवरोध;
			हाल '=':
				val = left != right;
				अवरोध;
			शेष:
				जाओ out_warning_op;
			पूर्ण
			अवरोध;
		हाल '~':
			val = ~right;
			अवरोध;
		हाल '|':
			अगर (arg->op.op[1])
				val = left || right;
			अन्यथा
				val = left | right;
			अवरोध;
		हाल '&':
			अगर (arg->op.op[1])
				val = left && right;
			अन्यथा
				val = left & right;
			अवरोध;
		हाल '<':
			चयन (arg->op.op[1]) अणु
			हाल 0:
				val = left < right;
				अवरोध;
			हाल '<':
				val = left << right;
				अवरोध;
			हाल '=':
				val = left <= right;
				अवरोध;
			शेष:
				जाओ out_warning_op;
			पूर्ण
			अवरोध;
		हाल '>':
			चयन (arg->op.op[1]) अणु
			हाल 0:
				val = left > right;
				अवरोध;
			हाल '>':
				val = left >> right;
				अवरोध;
			हाल '=':
				val = left >= right;
				अवरोध;
			शेष:
				जाओ out_warning_op;
			पूर्ण
			अवरोध;
		हाल '=':
			अगर (arg->op.op[1] != '=')
				जाओ out_warning_op;

			val = left == right;
			अवरोध;
		हाल '-':
			val = left - right;
			अवरोध;
		हाल '+':
			val = left + right;
			अवरोध;
		हाल '/':
			val = left / right;
			अवरोध;
		हाल '%':
			val = left % right;
			अवरोध;
		हाल '*':
			val = left * right;
			अवरोध;
		शेष:
			जाओ out_warning_op;
		पूर्ण
		अवरोध;
	हाल TEP_PRINT_DYNAMIC_ARRAY_LEN:
		offset = tep_पढ़ो_number(tep,
					 data + arg->dynarray.field->offset,
					 arg->dynarray.field->size);
		/*
		 * The total allocated length of the dynamic array is
		 * stored in the top half of the field, and the offset
		 * is in the bottom half of the 32 bit field.
		 */
		val = (अचिन्हित दीर्घ दीर्घ)(offset >> 16);
		अवरोध;
	हाल TEP_PRINT_DYNAMIC_ARRAY:
		/* Without [], we pass the address to the dynamic data */
		offset = tep_पढ़ो_number(tep,
					 data + arg->dynarray.field->offset,
					 arg->dynarray.field->size);
		/*
		 * The total allocated length of the dynamic array is
		 * stored in the top half of the field, and the offset
		 * is in the bottom half of the 32 bit field.
		 */
		offset &= 0xffff;
		val = (अचिन्हित दीर्घ दीर्घ)((अचिन्हित दीर्घ)data + offset);
		अवरोध;
	शेष: /* not sure what to करो there */
		वापस 0;
	पूर्ण
	वापस val;

out_warning_op:
	करो_warning_event(event, "%s: unknown op '%s'", __func__, arg->op.op);
	वापस 0;

out_warning_field:
	करो_warning_event(event, "%s: field %s not found",
			 __func__, arg->field.name);
	वापस 0;
पूर्ण

काष्ठा flag अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ दीर्घ value;
पूर्ण;

अटल स्थिर काष्ठा flag flags[] = अणु
	अणु "HI_SOFTIRQ", 0 पूर्ण,
	अणु "TIMER_SOFTIRQ", 1 पूर्ण,
	अणु "NET_TX_SOFTIRQ", 2 पूर्ण,
	अणु "NET_RX_SOFTIRQ", 3 पूर्ण,
	अणु "BLOCK_SOFTIRQ", 4 पूर्ण,
	अणु "IRQ_POLL_SOFTIRQ", 5 पूर्ण,
	अणु "TASKLET_SOFTIRQ", 6 पूर्ण,
	अणु "SCHED_SOFTIRQ", 7 पूर्ण,
	अणु "HRTIMER_SOFTIRQ", 8 पूर्ण,
	अणु "RCU_SOFTIRQ", 9 पूर्ण,

	अणु "HRTIMER_NORESTART", 0 पूर्ण,
	अणु "HRTIMER_RESTART", 1 पूर्ण,
पूर्ण;

अटल दीर्घ दीर्घ eval_flag(स्थिर अक्षर *flag)
अणु
	पूर्णांक i;

	/*
	 * Some flags in the क्रमmat files करो not get converted.
	 * If the flag is not numeric, see अगर it is something that
	 * we alपढ़ोy know about.
	 */
	अगर (है_अंक(flag[0]))
		वापस म_से_अदीर्घl(flag, शून्य, 0);

	क्रम (i = 0; i < (पूर्णांक)(माप(flags)/माप(flags[0])); i++)
		अगर (म_भेद(flags[i].name, flag) == 0)
			वापस flags[i].value;

	वापस -1LL;
पूर्ण

अटल व्योम prपूर्णांक_str_to_seq(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat,
			     पूर्णांक len_arg, स्थिर अक्षर *str)
अणु
	अगर (len_arg >= 0)
		trace_seq_म_लिखो(s, क्रमmat, len_arg, str);
	अन्यथा
		trace_seq_म_लिखो(s, क्रमmat, str);
पूर्ण

अटल व्योम prपूर्णांक_biपंचांगask_to_seq(काष्ठा tep_handle *tep,
				 काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat,
				 पूर्णांक len_arg, स्थिर व्योम *data, पूर्णांक size)
अणु
	पूर्णांक nr_bits = size * 8;
	पूर्णांक str_size = (nr_bits + 3) / 4;
	पूर्णांक len = 0;
	अक्षर buf[3];
	अक्षर *str;
	पूर्णांक index;
	पूर्णांक i;

	/*
	 * The kernel likes to put in commas every 32 bits, we
	 * can करो the same.
	 */
	str_size += (nr_bits - 1) / 32;

	str = दो_स्मृति(str_size + 1);
	अगर (!str) अणु
		करो_warning("%s: not enough memory!", __func__);
		वापस;
	पूर्ण
	str[str_size] = 0;

	/* Start out with -2 क्रम the two अक्षरs per byte */
	क्रम (i = str_size - 2; i >= 0; i -= 2) अणु
		/*
		 * data poपूर्णांकs to a bit mask of size bytes.
		 * In the kernel, this is an array of दीर्घ words, thus
		 * endianness is very important.
		 */
		अगर (tep->file_bigendian)
			index = size - (len + 1);
		अन्यथा
			index = len;

		snम_लिखो(buf, 3, "%02x", *((अचिन्हित अक्षर *)data + index));
		स_नकल(str + i, buf, 2);
		len++;
		अगर (!(len & 3) && i > 0) अणु
			i--;
			str[i] = ',';
		पूर्ण
	पूर्ण

	अगर (len_arg >= 0)
		trace_seq_म_लिखो(s, क्रमmat, len_arg, str);
	अन्यथा
		trace_seq_म_लिखो(s, क्रमmat, str);

	मुक्त(str);
पूर्ण

अटल व्योम prपूर्णांक_str_arg(काष्ठा trace_seq *s, व्योम *data, पूर्णांक size,
			  काष्ठा tep_event *event, स्थिर अक्षर *क्रमmat,
			  पूर्णांक len_arg, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा tep_handle *tep = event->tep;
	काष्ठा tep_prपूर्णांक_flag_sym *flag;
	काष्ठा tep_क्रमmat_field *field;
	काष्ठा prपूर्णांकk_map *prपूर्णांकk;
	दीर्घ दीर्घ val, fval;
	अचिन्हित दीर्घ दीर्घ addr;
	अक्षर *str;
	अचिन्हित अक्षर *hex;
	पूर्णांक prपूर्णांक;
	पूर्णांक i, len;

	चयन (arg->type) अणु
	हाल TEP_PRINT_शून्य:
		/* ?? */
		वापस;
	हाल TEP_PRINT_ATOM:
		prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, arg->atom.atom);
		वापस;
	हाल TEP_PRINT_FIELD:
		field = arg->field.field;
		अगर (!field) अणु
			field = tep_find_any_field(event, arg->field.name);
			अगर (!field) अणु
				str = arg->field.name;
				जाओ out_warning_field;
			पूर्ण
			arg->field.field = field;
		पूर्ण
		/* Zero sized fields, mean the rest of the data */
		len = field->size ? : size - field->offset;

		/*
		 * Some events pass in poपूर्णांकers. If this is not an array
		 * and the size is the same as दीर्घ_size, assume that it
		 * is a poपूर्णांकer.
		 */
		अगर (!(field->flags & TEP_FIELD_IS_ARRAY) &&
		    field->size == tep->दीर्घ_size) अणु

			/* Handle heterogeneous recording and processing
			 * architectures
			 *
			 * CASE I:
			 * Traces recorded on 32-bit devices (32-bit
			 * addressing) and processed on 64-bit devices:
			 * In this हाल, only 32 bits should be पढ़ो.
			 *
			 * CASE II:
			 * Traces recorded on 64 bit devices and processed
			 * on 32-bit devices:
			 * In this हाल, 64 bits must be पढ़ो.
			 */
			addr = (tep->दीर्घ_size == 8) ?
				*(अचिन्हित दीर्घ दीर्घ *)(data + field->offset) :
				(अचिन्हित दीर्घ दीर्घ)*(अचिन्हित पूर्णांक *)(data + field->offset);

			/* Check अगर it matches a prपूर्णांक क्रमmat */
			prपूर्णांकk = find_prपूर्णांकk(tep, addr);
			अगर (prपूर्णांकk)
				trace_seq_माला_दो(s, prपूर्णांकk->prपूर्णांकk);
			अन्यथा
				trace_seq_म_लिखो(s, "%llx", addr);
			अवरोध;
		पूर्ण
		str = दो_स्मृति(len + 1);
		अगर (!str) अणु
			करो_warning_event(event, "%s: not enough memory!",
					 __func__);
			वापस;
		पूर्ण
		स_नकल(str, data + field->offset, len);
		str[len] = 0;
		prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, str);
		मुक्त(str);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
		val = eval_num_arg(data, size, event, arg->flags.field);
		prपूर्णांक = 0;
		क्रम (flag = arg->flags.flags; flag; flag = flag->next) अणु
			fval = eval_flag(flag->value);
			अगर (!val && fval < 0) अणु
				prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, flag->str);
				अवरोध;
			पूर्ण
			अगर (fval > 0 && (val & fval) == fval) अणु
				अगर (prपूर्णांक && arg->flags.delim)
					trace_seq_माला_दो(s, arg->flags.delim);
				prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, flag->str);
				prपूर्णांक = 1;
				val &= ~fval;
			पूर्ण
		पूर्ण
		अगर (val) अणु
			अगर (prपूर्णांक && arg->flags.delim)
				trace_seq_माला_दो(s, arg->flags.delim);
			trace_seq_म_लिखो(s, "0x%llx", val);
		पूर्ण
		अवरोध;
	हाल TEP_PRINT_SYMBOL:
		val = eval_num_arg(data, size, event, arg->symbol.field);
		क्रम (flag = arg->symbol.symbols; flag; flag = flag->next) अणु
			fval = eval_flag(flag->value);
			अगर (val == fval) अणु
				prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, flag->str);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!flag)
			trace_seq_म_लिखो(s, "0x%llx", val);
		अवरोध;
	हाल TEP_PRINT_HEX:
	हाल TEP_PRINT_HEX_STR:
		अगर (arg->hex.field->type == TEP_PRINT_DYNAMIC_ARRAY) अणु
			अचिन्हित दीर्घ offset;
			offset = tep_पढ़ो_number(tep,
				data + arg->hex.field->dynarray.field->offset,
				arg->hex.field->dynarray.field->size);
			hex = data + (offset & 0xffff);
		पूर्ण अन्यथा अणु
			field = arg->hex.field->field.field;
			अगर (!field) अणु
				str = arg->hex.field->field.name;
				field = tep_find_any_field(event, str);
				अगर (!field)
					जाओ out_warning_field;
				arg->hex.field->field.field = field;
			पूर्ण
			hex = data + field->offset;
		पूर्ण
		len = eval_num_arg(data, size, event, arg->hex.size);
		क्रम (i = 0; i < len; i++) अणु
			अगर (i && arg->type == TEP_PRINT_HEX)
				trace_seq_अ_दो(s, ' ');
			trace_seq_म_लिखो(s, "%02x", hex[i]);
		पूर्ण
		अवरोध;

	हाल TEP_PRINT_INT_ARRAY: अणु
		व्योम *num;
		पूर्णांक el_size;

		अगर (arg->पूर्णांक_array.field->type == TEP_PRINT_DYNAMIC_ARRAY) अणु
			अचिन्हित दीर्घ offset;
			काष्ठा tep_क्रमmat_field *field =
				arg->पूर्णांक_array.field->dynarray.field;
			offset = tep_पढ़ो_number(tep,
						 data + field->offset,
						 field->size);
			num = data + (offset & 0xffff);
		पूर्ण अन्यथा अणु
			field = arg->पूर्णांक_array.field->field.field;
			अगर (!field) अणु
				str = arg->पूर्णांक_array.field->field.name;
				field = tep_find_any_field(event, str);
				अगर (!field)
					जाओ out_warning_field;
				arg->पूर्णांक_array.field->field.field = field;
			पूर्ण
			num = data + field->offset;
		पूर्ण
		len = eval_num_arg(data, size, event, arg->पूर्णांक_array.count);
		el_size = eval_num_arg(data, size, event,
				       arg->पूर्णांक_array.el_size);
		क्रम (i = 0; i < len; i++) अणु
			अगर (i)
				trace_seq_अ_दो(s, ' ');

			अगर (el_size == 1) अणु
				trace_seq_म_लिखो(s, "%u", *(uपूर्णांक8_t *)num);
			पूर्ण अन्यथा अगर (el_size == 2) अणु
				trace_seq_म_लिखो(s, "%u", *(uपूर्णांक16_t *)num);
			पूर्ण अन्यथा अगर (el_size == 4) अणु
				trace_seq_म_लिखो(s, "%u", *(uपूर्णांक32_t *)num);
			पूर्ण अन्यथा अगर (el_size == 8) अणु
				trace_seq_म_लिखो(s, "%"PRIu64, *(uपूर्णांक64_t *)num);
			पूर्ण अन्यथा अणु
				trace_seq_म_लिखो(s, "BAD SIZE:%d 0x%x",
						 el_size, *(uपूर्णांक8_t *)num);
				el_size = 1;
			पूर्ण

			num += el_size;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल TEP_PRINT_TYPE:
		अवरोध;
	हाल TEP_PRINT_STRING: अणु
		पूर्णांक str_offset;

		अगर (arg->string.offset == -1) अणु
			काष्ठा tep_क्रमmat_field *f;

			f = tep_find_any_field(event, arg->string.string);
			arg->string.offset = f->offset;
		पूर्ण
		str_offset = data2host4(tep, *(अचिन्हित पूर्णांक *)(data + arg->string.offset));
		str_offset &= 0xffff;
		prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, ((अक्षर *)data) + str_offset);
		अवरोध;
	पूर्ण
	हाल TEP_PRINT_BSTRING:
		prपूर्णांक_str_to_seq(s, क्रमmat, len_arg, arg->string.string);
		अवरोध;
	हाल TEP_PRINT_BITMASK: अणु
		पूर्णांक biपंचांगask_offset;
		पूर्णांक biपंचांगask_size;

		अगर (arg->biपंचांगask.offset == -1) अणु
			काष्ठा tep_क्रमmat_field *f;

			f = tep_find_any_field(event, arg->biपंचांगask.biपंचांगask);
			arg->biपंचांगask.offset = f->offset;
		पूर्ण
		biपंचांगask_offset = data2host4(tep, *(अचिन्हित पूर्णांक *)(data + arg->biपंचांगask.offset));
		biपंचांगask_size = biपंचांगask_offset >> 16;
		biपंचांगask_offset &= 0xffff;
		prपूर्णांक_biपंचांगask_to_seq(tep, s, क्रमmat, len_arg,
				     data + biपंचांगask_offset, biपंचांगask_size);
		अवरोध;
	पूर्ण
	हाल TEP_PRINT_OP:
		/*
		 * The only op क्रम string should be ? :
		 */
		अगर (arg->op.op[0] != '?')
			वापस;
		val = eval_num_arg(data, size, event, arg->op.left);
		अगर (val)
			prपूर्णांक_str_arg(s, data, size, event,
				      क्रमmat, len_arg, arg->op.right->op.left);
		अन्यथा
			prपूर्णांक_str_arg(s, data, size, event,
				      क्रमmat, len_arg, arg->op.right->op.right);
		अवरोध;
	हाल TEP_PRINT_FUNC:
		process_defined_func(s, data, size, event, arg);
		अवरोध;
	शेष:
		/* well... */
		अवरोध;
	पूर्ण

	वापस;

out_warning_field:
	करो_warning_event(event, "%s: field %s not found",
			 __func__, arg->field.name);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ
process_defined_func(काष्ठा trace_seq *s, व्योम *data, पूर्णांक size,
		     काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा tep_function_handler *func_handle = arg->func.func;
	काष्ठा func_params *param;
	अचिन्हित दीर्घ दीर्घ *args;
	अचिन्हित दीर्घ दीर्घ ret;
	काष्ठा tep_prपूर्णांक_arg *farg;
	काष्ठा trace_seq str;
	काष्ठा save_str अणु
		काष्ठा save_str *next;
		अक्षर *str;
	पूर्ण *strings = शून्य, *string;
	पूर्णांक i;

	अगर (!func_handle->nr_args) अणु
		ret = (*func_handle->func)(s, शून्य);
		जाओ out;
	पूर्ण

	farg = arg->func.args;
	param = func_handle->params;

	ret = ULदीर्घ_उच्च;
	args = दो_स्मृति(माप(*args) * func_handle->nr_args);
	अगर (!args)
		जाओ out;

	क्रम (i = 0; i < func_handle->nr_args; i++) अणु
		चयन (param->type) अणु
		हाल TEP_FUNC_ARG_INT:
		हाल TEP_FUNC_ARG_LONG:
		हाल TEP_FUNC_ARG_PTR:
			args[i] = eval_num_arg(data, size, event, farg);
			अवरोध;
		हाल TEP_FUNC_ARG_STRING:
			trace_seq_init(&str);
			prपूर्णांक_str_arg(&str, data, size, event, "%s", -1, farg);
			trace_seq_terminate(&str);
			string = दो_स्मृति(माप(*string));
			अगर (!string) अणु
				करो_warning_event(event, "%s(%d): malloc str",
						 __func__, __LINE__);
				जाओ out_मुक्त;
			पूर्ण
			string->next = strings;
			string->str = strdup(str.buffer);
			अगर (!string->str) अणु
				मुक्त(string);
				करो_warning_event(event, "%s(%d): malloc str",
						 __func__, __LINE__);
				जाओ out_मुक्त;
			पूर्ण
			args[i] = (uपूर्णांकptr_t)string->str;
			strings = string;
			trace_seq_destroy(&str);
			अवरोध;
		शेष:
			/*
			 * Something went totally wrong, this is not
			 * an input error, something in this code broke.
			 */
			करो_warning_event(event, "Unexpected end of arguments\n");
			जाओ out_मुक्त;
		पूर्ण
		farg = farg->next;
		param = param->next;
	पूर्ण

	ret = (*func_handle->func)(s, args);
out_मुक्त:
	मुक्त(args);
	जबतक (strings) अणु
		string = strings;
		strings = string->next;
		मुक्त(string->str);
		मुक्त(string);
	पूर्ण

 out:
	/* TBD : handle वापस type here */
	वापस ret;
पूर्ण

अटल व्योम मुक्त_args(काष्ठा tep_prपूर्णांक_arg *args)
अणु
	काष्ठा tep_prपूर्णांक_arg *next;

	जबतक (args) अणु
		next = args->next;

		मुक्त_arg(args);
		args = next;
	पूर्ण
पूर्ण

अटल काष्ठा tep_prपूर्णांक_arg *make_bprपूर्णांक_args(अक्षर *fmt, व्योम *data, पूर्णांक size, काष्ठा tep_event *event)
अणु
	काष्ठा tep_handle *tep = event->tep;
	काष्ठा tep_क्रमmat_field *field, *ip_field;
	काष्ठा tep_prपूर्णांक_arg *args, *arg, **next;
	अचिन्हित दीर्घ दीर्घ ip, val;
	अक्षर *ptr;
	व्योम *bptr;
	पूर्णांक vsize = 0;

	field = tep->bprपूर्णांक_buf_field;
	ip_field = tep->bprपूर्णांक_ip_field;

	अगर (!field) अणु
		field = tep_find_field(event, "buf");
		अगर (!field) अणु
			करो_warning_event(event, "can't find buffer field for binary printk");
			वापस शून्य;
		पूर्ण
		ip_field = tep_find_field(event, "ip");
		अगर (!ip_field) अणु
			करो_warning_event(event, "can't find ip field for binary printk");
			वापस शून्य;
		पूर्ण
		tep->bprपूर्णांक_buf_field = field;
		tep->bprपूर्णांक_ip_field = ip_field;
	पूर्ण

	ip = tep_पढ़ो_number(tep, data + ip_field->offset, ip_field->size);

	/*
	 * The first arg is the IP poपूर्णांकer.
	 */
	args = alloc_arg();
	अगर (!args) अणु
		करो_warning_event(event, "%s(%d): not enough memory!",
				 __func__, __LINE__);
		वापस शून्य;
	पूर्ण
	arg = args;
	arg->next = शून्य;
	next = &arg->next;

	arg->type = TEP_PRINT_ATOM;
		
	अगर (aप्र_लिखो(&arg->atom.atom, "%lld", ip) < 0)
		जाओ out_मुक्त;

	/* skip the first "%ps: " */
	क्रम (ptr = fmt + 5, bptr = data + field->offset;
	     bptr < data + size && *ptr; ptr++) अणु
		पूर्णांक ls = 0;

		अगर (*ptr == '%') अणु
 process_again:
			ptr++;
			चयन (*ptr) अणु
			हाल '%':
				अवरोध;
			हाल 'l':
				ls++;
				जाओ process_again;
			हाल 'L':
				ls = 2;
				जाओ process_again;
			हाल '0' ... '9':
				जाओ process_again;
			हाल '.':
				जाओ process_again;
			हाल 'z':
			हाल 'Z':
				ls = 1;
				जाओ process_again;
			हाल 'p':
				ls = 1;
				अगर (है_अक्षर_अंक(ptr[1])) अणु
					ptr++;
					/* Check क्रम special poपूर्णांकers */
					चयन (*ptr) अणु
					हाल 's':
					हाल 'S':
					हाल 'x':
						अवरोध;
					हाल 'f':
					हाल 'F':
						/*
						 * Pre-5.5 kernels use %pf and
						 * %pF क्रम prपूर्णांकing symbols
						 * जबतक kernels since 5.5 use
						 * %pfw क्रम fwnodes. So check
						 * %p[fF] isn't followed by 'w'.
						 */
						अगर (ptr[1] != 'w')
							अवरोध;
						/* fall through */
					शेष:
						/*
						 * Older kernels करो not process
						 * dereferenced poपूर्णांकers.
						 * Only process अगर the poपूर्णांकer
						 * value is a prपूर्णांकable.
						 */
						अगर (है_छाप(*(अक्षर *)bptr))
							जाओ process_string;
					पूर्ण
				पूर्ण
				/* fall through */
			हाल 'd':
			हाल 'u':
			हाल 'i':
			हाल 'x':
			हाल 'X':
			हाल 'o':
				चयन (ls) अणु
				हाल 0:
					vsize = 4;
					अवरोध;
				हाल 1:
					vsize = tep->दीर्घ_size;
					अवरोध;
				हाल 2:
					vsize = 8;
					अवरोध;
				शेष:
					vsize = ls; /* ? */
					अवरोध;
				पूर्ण
			/* fall through */
			हाल '*':
				अगर (*ptr == '*')
					vsize = 4;

				/* the poपूर्णांकers are always 4 bytes aligned */
				bptr = (व्योम *)(((अचिन्हित दीर्घ)bptr + 3) &
						~3);
				val = tep_पढ़ो_number(tep, bptr, vsize);
				bptr += vsize;
				arg = alloc_arg();
				अगर (!arg) अणु
					करो_warning_event(event, "%s(%d): not enough memory!",
						   __func__, __LINE__);
					जाओ out_मुक्त;
				पूर्ण
				arg->next = शून्य;
				arg->type = TEP_PRINT_ATOM;
				अगर (aप्र_लिखो(&arg->atom.atom, "%lld", val) < 0) अणु
					मुक्त(arg);
					जाओ out_मुक्त;
				पूर्ण
				*next = arg;
				next = &arg->next;
				/*
				 * The '*' हाल means that an arg is used as the length.
				 * We need to जारी to figure out क्रम what.
				 */
				अगर (*ptr == '*')
					जाओ process_again;

				अवरोध;
			हाल 's':
 process_string:
				arg = alloc_arg();
				अगर (!arg) अणु
					करो_warning_event(event, "%s(%d): not enough memory!",
						   __func__, __LINE__);
					जाओ out_मुक्त;
				पूर्ण
				arg->next = शून्य;
				arg->type = TEP_PRINT_BSTRING;
				arg->string.string = strdup(bptr);
				अगर (!arg->string.string)
					जाओ out_मुक्त;
				bptr += म_माप(bptr) + 1;
				*next = arg;
				next = &arg->next;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस args;

out_मुक्त:
	मुक्त_args(args);
	वापस शून्य;
पूर्ण

अटल अक्षर *
get_bprपूर्णांक_क्रमmat(व्योम *data, पूर्णांक size __maybe_unused,
		  काष्ठा tep_event *event)
अणु
	काष्ठा tep_handle *tep = event->tep;
	अचिन्हित दीर्घ दीर्घ addr;
	काष्ठा tep_क्रमmat_field *field;
	काष्ठा prपूर्णांकk_map *prपूर्णांकk;
	अक्षर *क्रमmat;

	field = tep->bprपूर्णांक_fmt_field;

	अगर (!field) अणु
		field = tep_find_field(event, "fmt");
		अगर (!field) अणु
			करो_warning_event(event, "can't find format field for binary printk");
			वापस शून्य;
		पूर्ण
		tep->bprपूर्णांक_fmt_field = field;
	पूर्ण

	addr = tep_पढ़ो_number(tep, data + field->offset, field->size);

	prपूर्णांकk = find_prपूर्णांकk(tep, addr);
	अगर (!prपूर्णांकk) अणु
		अगर (aप्र_लिखो(&क्रमmat, "%%ps: (NO FORMAT FOUND at %llx)\n", addr) < 0)
			वापस शून्य;
		वापस क्रमmat;
	पूर्ण

	अगर (aप्र_लिखो(&क्रमmat, "%s: %s", "%ps", prपूर्णांकk->prपूर्णांकk) < 0)
		वापस शून्य;

	वापस क्रमmat;
पूर्ण

अटल पूर्णांक prपूर्णांक_mac_arg(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat,
			 व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			 काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	स्थिर अक्षर *fmt = "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x";
	bool reverse = false;
	अचिन्हित अक्षर *buf;
	पूर्णांक ret = 0;

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस 0;
	पूर्ण

	अगर (arg->type != TEP_PRINT_FIELD) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d",
				 arg->type);
		वापस 0;
	पूर्ण

	अगर (क्रमmat[0] == 'm') अणु
		fmt = "%.2x%.2x%.2x%.2x%.2x%.2x";
	पूर्ण अन्यथा अगर (क्रमmat[0] == 'M' && format[1] == 'F') अणु
		fmt = "%.2x-%.2x-%.2x-%.2x-%.2x-%.2x";
		ret++;
	पूर्ण
	अगर (क्रमmat[1] == 'R') अणु
		reverse = true;
		ret++;
	पूर्ण

	अगर (!arg->field.field) अणु
		arg->field.field =
			tep_find_any_field(event, arg->field.name);
		अगर (!arg->field.field) अणु
			करो_warning_event(event, "%s: field %s not found",
					 __func__, arg->field.name);
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (arg->field.field->size != 6) अणु
		trace_seq_म_लिखो(s, "INVALIDMAC");
		वापस ret;
	पूर्ण

	buf = data + arg->field.field->offset;
	अगर (reverse)
		trace_seq_म_लिखो(s, fmt, buf[5], buf[4], buf[3], buf[2], buf[1], buf[0]);
	अन्यथा
		trace_seq_म_लिखो(s, fmt, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

	वापस ret;
पूर्ण

अटल पूर्णांक parse_ip4_prपूर्णांक_args(काष्ठा tep_handle *tep,
				स्थिर अक्षर *ptr, bool *reverse)
अणु
	पूर्णांक ret = 0;

	*reverse = false;

	/* hnbl */
	चयन (*ptr) अणु
	हाल 'h':
		अगर (tep->file_bigendian)
			*reverse = false;
		अन्यथा
			*reverse = true;
		ret++;
		अवरोध;
	हाल 'l':
		*reverse = true;
		ret++;
		अवरोध;
	हाल 'n':
	हाल 'b':
		ret++;
		/* fall through */
	शेष:
		*reverse = false;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम prपूर्णांक_ip4_addr(काष्ठा trace_seq *s, अक्षर i, bool reverse, अचिन्हित अक्षर *buf)
अणु
	स्थिर अक्षर *fmt;

	अगर (i == 'i')
		fmt = "%03d.%03d.%03d.%03d";
	अन्यथा
		fmt = "%d.%d.%d.%d";

	अगर (reverse)
		trace_seq_म_लिखो(s, fmt, buf[3], buf[2], buf[1], buf[0]);
	अन्यथा
		trace_seq_म_लिखो(s, fmt, buf[0], buf[1], buf[2], buf[3]);

पूर्ण

अटल अंतरभूत bool ipv6_addr_v4mapped(स्थिर काष्ठा in6_addr *a)
अणु
	वापस ((अचिन्हित दीर्घ)(a->s6_addr32[0] | a->s6_addr32[1]) |
		(अचिन्हित दीर्घ)(a->s6_addr32[2] ^ htonl(0x0000ffff))) == 0UL;
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_isatap(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस (addr->s6_addr32[2] | htonl(0x02000000)) == htonl(0x02005EFE);
पूर्ण

अटल व्योम prपूर्णांक_ip6c_addr(काष्ठा trace_seq *s, अचिन्हित अक्षर *addr)
अणु
	पूर्णांक i, j, range;
	अचिन्हित अक्षर zerolength[8];
	पूर्णांक दीर्घest = 1;
	पूर्णांक colonpos = -1;
	uपूर्णांक16_t word;
	uपूर्णांक8_t hi, lo;
	bool needcolon = false;
	bool useIPv4;
	काष्ठा in6_addr in6;

	स_नकल(&in6, addr, माप(काष्ठा in6_addr));

	useIPv4 = ipv6_addr_v4mapped(&in6) || ipv6_addr_is_isatap(&in6);

	स_रखो(zerolength, 0, माप(zerolength));

	अगर (useIPv4)
		range = 6;
	अन्यथा
		range = 8;

	/* find position of दीर्घest 0 run */
	क्रम (i = 0; i < range; i++) अणु
		क्रम (j = i; j < range; j++) अणु
			अगर (in6.s6_addr16[j] != 0)
				अवरोध;
			zerolength[i]++;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < range; i++) अणु
		अगर (zerolength[i] > दीर्घest) अणु
			दीर्घest = zerolength[i];
			colonpos = i;
		पूर्ण
	पूर्ण
	अगर (दीर्घest == 1)		/* करोn't compress a single 0 */
		colonpos = -1;

	/* emit address */
	क्रम (i = 0; i < range; i++) अणु
		अगर (i == colonpos) अणु
			अगर (needcolon || i == 0)
				trace_seq_म_लिखो(s, ":");
			trace_seq_म_लिखो(s, ":");
			needcolon = false;
			i += दीर्घest - 1;
			जारी;
		पूर्ण
		अगर (needcolon) अणु
			trace_seq_म_लिखो(s, ":");
			needcolon = false;
		पूर्ण
		/* hex u16 without leading 0s */
		word = ntohs(in6.s6_addr16[i]);
		hi = word >> 8;
		lo = word & 0xff;
		अगर (hi)
			trace_seq_म_लिखो(s, "%x%02x", hi, lo);
		अन्यथा
			trace_seq_म_लिखो(s, "%x", lo);

		needcolon = true;
	पूर्ण

	अगर (useIPv4) अणु
		अगर (needcolon)
			trace_seq_म_लिखो(s, ":");
		prपूर्णांक_ip4_addr(s, 'I', false, &in6.s6_addr[12]);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम prपूर्णांक_ip6_addr(काष्ठा trace_seq *s, अक्षर i, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < 16; j += 2) अणु
		trace_seq_म_लिखो(s, "%02x%02x", buf[j], buf[j+1]);
		अगर (i == 'I' && j < 14)
			trace_seq_म_लिखो(s, ":");
	पूर्ण
पूर्ण

/*
 * %pi4   prपूर्णांक an IPv4 address with leading zeros
 * %pI4   prपूर्णांक an IPv4 address without leading zeros
 * %pi6   prपूर्णांक an IPv6 address without colons
 * %pI6   prपूर्णांक an IPv6 address with colons
 * %pI6c  prपूर्णांक an IPv6 address in compressed क्रमm with colons
 * %pISpc prपूर्णांक an IP address based on sockaddr; p adds port.
 */
अटल पूर्णांक prपूर्णांक_ipv4_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr, अक्षर i,
			  व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			  काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	bool reverse = false;
	अचिन्हित अक्षर *buf;
	पूर्णांक ret;

	ret = parse_ip4_prपूर्णांक_args(event->tep, ptr, &reverse);

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस ret;
	पूर्ण

	अगर (arg->type != TEP_PRINT_FIELD) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d", arg->type);
		वापस ret;
	पूर्ण

	अगर (!arg->field.field) अणु
		arg->field.field =
			tep_find_any_field(event, arg->field.name);
		अगर (!arg->field.field) अणु
			करो_warning("%s: field %s not found",
				   __func__, arg->field.name);
			वापस ret;
		पूर्ण
	पूर्ण

	buf = data + arg->field.field->offset;

	अगर (arg->field.field->size != 4) अणु
		trace_seq_म_लिखो(s, "INVALIDIPv4");
		वापस ret;
	पूर्ण

	prपूर्णांक_ip4_addr(s, i, reverse, buf);
	वापस ret;

पूर्ण

अटल पूर्णांक prपूर्णांक_ipv6_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr, अक्षर i,
			  व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			  काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	अक्षर have_c = 0;
	अचिन्हित अक्षर *buf;
	पूर्णांक rc = 0;

	/* pI6c */
	अगर (i == 'I' && *ptr == 'c') अणु
		have_c = 1;
		ptr++;
		rc++;
	पूर्ण

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस rc;
	पूर्ण

	अगर (arg->type != TEP_PRINT_FIELD) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d", arg->type);
		वापस rc;
	पूर्ण

	अगर (!arg->field.field) अणु
		arg->field.field =
			tep_find_any_field(event, arg->field.name);
		अगर (!arg->field.field) अणु
			करो_warning("%s: field %s not found",
				   __func__, arg->field.name);
			वापस rc;
		पूर्ण
	पूर्ण

	buf = data + arg->field.field->offset;

	अगर (arg->field.field->size != 16) अणु
		trace_seq_म_लिखो(s, "INVALIDIPv6");
		वापस rc;
	पूर्ण

	अगर (have_c)
		prपूर्णांक_ip6c_addr(s, buf);
	अन्यथा
		prपूर्णांक_ip6_addr(s, i, buf);

	वापस rc;
पूर्ण

अटल पूर्णांक prपूर्णांक_ipsa_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr, अक्षर i,
			  व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			  काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	अक्षर have_c = 0, have_p = 0;
	अचिन्हित अक्षर *buf;
	काष्ठा sockaddr_storage *sa;
	bool reverse = false;
	पूर्णांक rc = 0;
	पूर्णांक ret;

	/* pISpc */
	अगर (i == 'I') अणु
		अगर (*ptr == 'p') अणु
			have_p = 1;
			ptr++;
			rc++;
		पूर्ण
		अगर (*ptr == 'c') अणु
			have_c = 1;
			ptr++;
			rc++;
		पूर्ण
	पूर्ण
	ret = parse_ip4_prपूर्णांक_args(event->tep, ptr, &reverse);
	ptr += ret;
	rc += ret;

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस rc;
	पूर्ण

	अगर (arg->type != TEP_PRINT_FIELD) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d", arg->type);
		वापस rc;
	पूर्ण

	अगर (!arg->field.field) अणु
		arg->field.field =
			tep_find_any_field(event, arg->field.name);
		अगर (!arg->field.field) अणु
			करो_warning("%s: field %s not found",
				   __func__, arg->field.name);
			वापस rc;
		पूर्ण
	पूर्ण

	sa = (काष्ठा sockaddr_storage *) (data + arg->field.field->offset);

	अगर (sa->ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *sa4 = (काष्ठा sockaddr_in *) sa;

		अगर (arg->field.field->size < माप(काष्ठा sockaddr_in)) अणु
			trace_seq_म_लिखो(s, "INVALIDIPv4");
			वापस rc;
		पूर्ण

		prपूर्णांक_ip4_addr(s, i, reverse, (अचिन्हित अक्षर *) &sa4->sin_addr);
		अगर (have_p)
			trace_seq_म_लिखो(s, ":%d", ntohs(sa4->sin_port));


	पूर्ण अन्यथा अगर (sa->ss_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sa6 = (काष्ठा sockaddr_in6 *) sa;

		अगर (arg->field.field->size < माप(काष्ठा sockaddr_in6)) अणु
			trace_seq_म_लिखो(s, "INVALIDIPv6");
			वापस rc;
		पूर्ण

		अगर (have_p)
			trace_seq_म_लिखो(s, "[");

		buf = (अचिन्हित अक्षर *) &sa6->sin6_addr;
		अगर (have_c)
			prपूर्णांक_ip6c_addr(s, buf);
		अन्यथा
			prपूर्णांक_ip6_addr(s, i, buf);

		अगर (have_p)
			trace_seq_म_लिखो(s, "]:%d", ntohs(sa6->sin6_port));
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक prपूर्णांक_ip_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr,
			व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	अक्षर i = *ptr;  /* 'i' or 'I' */
	पूर्णांक rc = 1;

	/* IP version */
	ptr++;

	चयन (*ptr) अणु
	हाल '4':
		rc += prपूर्णांक_ipv4_arg(s, ptr + 1, i, data, size, event, arg);
		अवरोध;
	हाल '6':
		rc += prपूर्णांक_ipv6_arg(s, ptr + 1, i, data, size, event, arg);
		अवरोध;
	हाल 'S':
		rc += prपूर्णांक_ipsa_arg(s, ptr + 1, i, data, size, event, arg);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर पूर्णांक guid_index[16] = अणु3, 2, 1, 0, 5, 4, 7, 6, 8, 9, 10, 11, 12, 13, 14, 15पूर्ण;
अटल स्थिर पूर्णांक uuid_index[16] = अणु0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15पूर्ण;

अटल पूर्णांक prपूर्णांक_uuid_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr,
			व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	स्थिर पूर्णांक *index = uuid_index;
	अक्षर *क्रमmat = "%02x";
	पूर्णांक ret = 0;
	अक्षर *buf;
	पूर्णांक i;

	चयन (*(ptr + 1)) अणु
	हाल 'L':
		क्रमmat = "%02X";
		/* fall through */
	हाल 'l':
		index = guid_index;
		ret++;
		अवरोध;
	हाल 'B':
		क्रमmat = "%02X";
		/* fall through */
	हाल 'b':
		ret++;
		अवरोध;
	पूर्ण

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस ret;
	पूर्ण

	अगर (arg->type != TEP_PRINT_FIELD) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d", arg->type);
		वापस ret;
	पूर्ण

	अगर (!arg->field.field) अणु
		arg->field.field =
			tep_find_any_field(event, arg->field.name);
		अगर (!arg->field.field) अणु
			करो_warning("%s: field %s not found",
				   __func__, arg->field.name);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (arg->field.field->size != 16) अणु
		trace_seq_म_लिखो(s, "INVALIDUUID");
		वापस ret;
	पूर्ण

	buf = data + arg->field.field->offset;

	क्रम (i = 0; i < 16; i++) अणु
		trace_seq_म_लिखो(s, क्रमmat, buf[index[i]] & 0xff);
		चयन (i) अणु
		हाल 3:
		हाल 5:
		हाल 7:
		हाल 9:
			trace_seq_म_लिखो(s, "-");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक prपूर्णांक_raw_buff_arg(काष्ठा trace_seq *s, स्थिर अक्षर *ptr,
			      व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			      काष्ठा tep_prपूर्णांक_arg *arg, पूर्णांक prपूर्णांक_len)
अणु
	पूर्णांक plen = prपूर्णांक_len;
	अक्षर *delim = " ";
	पूर्णांक ret = 0;
	अक्षर *buf;
	पूर्णांक i;
	अचिन्हित दीर्घ offset;
	पूर्णांक arr_len;

	चयन (*(ptr + 1)) अणु
	हाल 'C':
		delim = ":";
		ret++;
		अवरोध;
	हाल 'D':
		delim = "-";
		ret++;
		अवरोध;
	हाल 'N':
		delim = "";
		ret++;
		अवरोध;
	पूर्ण

	अगर (arg->type == TEP_PRINT_FUNC) अणु
		process_defined_func(s, data, size, event, arg);
		वापस ret;
	पूर्ण

	अगर (arg->type != TEP_PRINT_DYNAMIC_ARRAY) अणु
		trace_seq_म_लिखो(s, "ARG TYPE NOT FIELD BUT %d", arg->type);
		वापस ret;
	पूर्ण

	offset = tep_पढ़ो_number(event->tep,
				 data + arg->dynarray.field->offset,
				 arg->dynarray.field->size);
	arr_len = (अचिन्हित दीर्घ दीर्घ)(offset >> 16);
	buf = data + (offset & 0xffff);

	अगर (arr_len < plen)
		plen = arr_len;

	अगर (plen < 1)
		वापस ret;

	trace_seq_म_लिखो(s, "%02x", buf[0] & 0xff);
	क्रम (i = 1; i < plen; i++)
		trace_seq_म_लिखो(s, "%s%02x", delim, buf[i] & 0xff);

	वापस ret;
पूर्ण

अटल पूर्णांक is_prपूर्णांकable_array(अक्षर *p, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len && p[i]; i++)
		अगर (!है_छाप(p[i]) && !है_खाली(p[i]))
		    वापस 0;
	वापस 1;
पूर्ण

व्योम tep_prपूर्णांक_field(काष्ठा trace_seq *s, व्योम *data,
		     काष्ठा tep_क्रमmat_field *field)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित पूर्णांक offset, len, i;
	काष्ठा tep_handle *tep = field->event->tep;

	अगर (field->flags & TEP_FIELD_IS_ARRAY) अणु
		offset = field->offset;
		len = field->size;
		अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
			val = tep_पढ़ो_number(tep, data + offset, len);
			offset = val;
			len = offset >> 16;
			offset &= 0xffff;
		पूर्ण
		अगर (field->flags & TEP_FIELD_IS_STRING &&
		    is_prपूर्णांकable_array(data + offset, len)) अणु
			trace_seq_म_लिखो(s, "%s", (अक्षर *)data + offset);
		पूर्ण अन्यथा अणु
			trace_seq_माला_दो(s, "ARRAY[");
			क्रम (i = 0; i < len; i++) अणु
				अगर (i)
					trace_seq_माला_दो(s, ", ");
				trace_seq_म_लिखो(s, "%02x",
						 *((अचिन्हित अक्षर *)data + offset + i));
			पूर्ण
			trace_seq_अ_दो(s, ']');
			field->flags &= ~TEP_FIELD_IS_STRING;
		पूर्ण
	पूर्ण अन्यथा अणु
		val = tep_पढ़ो_number(tep, data + field->offset,
				      field->size);
		अगर (field->flags & TEP_FIELD_IS_POINTER) अणु
			trace_seq_म_लिखो(s, "0x%llx", val);
		पूर्ण अन्यथा अगर (field->flags & TEP_FIELD_IS_SIGNED) अणु
			चयन (field->size) अणु
			हाल 4:
				/*
				 * If field is दीर्घ then prपूर्णांक it in hex.
				 * A दीर्घ usually stores poपूर्णांकers.
				 */
				अगर (field->flags & TEP_FIELD_IS_LONG)
					trace_seq_म_लिखो(s, "0x%x", (पूर्णांक)val);
				अन्यथा
					trace_seq_म_लिखो(s, "%d", (पूर्णांक)val);
				अवरोध;
			हाल 2:
				trace_seq_म_लिखो(s, "%2d", (लघु)val);
				अवरोध;
			हाल 1:
				trace_seq_म_लिखो(s, "%1d", (अक्षर)val);
				अवरोध;
			शेष:
				trace_seq_म_लिखो(s, "%lld", val);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (field->flags & TEP_FIELD_IS_LONG)
				trace_seq_म_लिखो(s, "0x%llx", val);
			अन्यथा
				trace_seq_म_लिखो(s, "%llu", val);
		पूर्ण
	पूर्ण
पूर्ण

व्योम tep_prपूर्णांक_fields(काष्ठा trace_seq *s, व्योम *data,
		      पूर्णांक size __maybe_unused, काष्ठा tep_event *event)
अणु
	काष्ठा tep_क्रमmat_field *field;

	field = event->क्रमmat.fields;
	जबतक (field) अणु
		trace_seq_म_लिखो(s, " %s=", field->name);
		tep_prपूर्णांक_field(s, data, field);
		field = field->next;
	पूर्ण
पूर्ण

अटल पूर्णांक prपूर्णांक_function(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat,
			  व्योम *data, पूर्णांक size, काष्ठा tep_event *event,
			  काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा func_map *func;
	अचिन्हित दीर्घ दीर्घ val;

	val = eval_num_arg(data, size, event, arg);
	func = find_func(event->tep, val);
	अगर (func) अणु
		trace_seq_माला_दो(s, func->func);
		अगर (*क्रमmat == 'F' || *format == 'S')
			trace_seq_म_लिखो(s, "+0x%llx", val - func->addr);
	पूर्ण अन्यथा अणु
		अगर (event->tep->दीर्घ_size == 4)
			trace_seq_म_लिखो(s, "0x%lx", (दीर्घ)val);
		अन्यथा
			trace_seq_म_लिखो(s, "0x%llx", (दीर्घ दीर्घ)val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prपूर्णांक_arg_poपूर्णांकer(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat, पूर्णांक plen,
			     व्योम *data, पूर्णांक size,
			     काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	अचिन्हित दीर्घ दीर्घ val;
	पूर्णांक ret = 1;

	अगर (arg->type == TEP_PRINT_BSTRING) अणु
		trace_seq_माला_दो(s, arg->string.string);
		वापस 0;
	पूर्ण
	जबतक (*क्रमmat) अणु
		अगर (*क्रमmat == 'p') अणु
			क्रमmat++;
			अवरोध;
		पूर्ण
		क्रमmat++;
	पूर्ण

	चयन (*क्रमmat) अणु
	हाल 'F':
	हाल 'f':
	हाल 'S':
	हाल 's':
		ret += prपूर्णांक_function(s, क्रमmat, data, size, event, arg);
		अवरोध;
	हाल 'M':
	हाल 'm':
		ret += prपूर्णांक_mac_arg(s, क्रमmat, data, size, event, arg);
		अवरोध;
	हाल 'I':
	हाल 'i':
		ret += prपूर्णांक_ip_arg(s, क्रमmat, data, size, event, arg);
		अवरोध;
	हाल 'U':
		ret += prपूर्णांक_uuid_arg(s, क्रमmat, data, size, event, arg);
		अवरोध;
	हाल 'h':
		ret += prपूर्णांक_raw_buff_arg(s, क्रमmat, data, size, event, arg, plen);
		अवरोध;
	शेष:
		ret = 0;
		val = eval_num_arg(data, size, event, arg);
		trace_seq_म_लिखो(s, "%p", (व्योम *)(पूर्णांकptr_t)val);
		अवरोध;
	पूर्ण

	वापस ret;

पूर्ण

अटल पूर्णांक prपूर्णांक_arg_number(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat, पूर्णांक plen,
			    व्योम *data, पूर्णांक size, पूर्णांक ls,
			    काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	val = eval_num_arg(data, size, event, arg);

	चयन (ls) अणु
	हाल -2:
		अगर (plen >= 0)
			trace_seq_म_लिखो(s, क्रमmat, plen, (अक्षर)val);
		अन्यथा
			trace_seq_म_लिखो(s, क्रमmat, (अक्षर)val);
		अवरोध;
	हाल -1:
		अगर (plen >= 0)
			trace_seq_म_लिखो(s, क्रमmat, plen, (लघु)val);
		अन्यथा
			trace_seq_म_लिखो(s, क्रमmat, (लघु)val);
		अवरोध;
	हाल 0:
		अगर (plen >= 0)
			trace_seq_म_लिखो(s, क्रमmat, plen, (पूर्णांक)val);
		अन्यथा
			trace_seq_म_लिखो(s, क्रमmat, (पूर्णांक)val);
		अवरोध;
	हाल 1:
		अगर (plen >= 0)
			trace_seq_म_लिखो(s, क्रमmat, plen, (दीर्घ)val);
		अन्यथा
			trace_seq_म_लिखो(s, क्रमmat, (दीर्घ)val);
		अवरोध;
	हाल 2:
		अगर (plen >= 0)
			trace_seq_म_लिखो(s, क्रमmat, plen, (दीर्घ दीर्घ)val);
		अन्यथा
			trace_seq_म_लिखो(s, क्रमmat, (दीर्घ दीर्घ)val);
		अवरोध;
	शेष:
		करो_warning_event(event, "bad count (%d)", ls);
		event->flags |= TEP_EVENT_FL_FAILED;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम prपूर्णांक_arg_string(काष्ठा trace_seq *s, स्थिर अक्षर *क्रमmat, पूर्णांक plen,
			     व्योम *data, पूर्णांक size,
			     काष्ठा tep_event *event, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा trace_seq p;

	/* Use helper trace_seq */
	trace_seq_init(&p);
	prपूर्णांक_str_arg(&p, data, size, event,
		      क्रमmat, plen, arg);
	trace_seq_terminate(&p);
	trace_seq_माला_दो(s, p.buffer);
	trace_seq_destroy(&p);
पूर्ण

अटल पूर्णांक parse_arg_क्रमmat_poपूर्णांकer(स्थिर अक्षर *क्रमmat)
अणु
	पूर्णांक ret = 0;
	पूर्णांक index;
	पूर्णांक loop;

	चयन (*क्रमmat) अणु
	हाल 'F':
	हाल 'S':
	हाल 'f':
	हाल 's':
		ret++;
		अवरोध;
	हाल 'M':
	हाल 'm':
		/* [mM]R , [mM]F */
		चयन (क्रमmat[1]) अणु
		हाल 'R':
		हाल 'F':
			ret++;
			अवरोध;
		पूर्ण
		ret++;
		अवरोध;
	हाल 'I':
	हाल 'i':
		index = 2;
		loop = 1;
		चयन (क्रमmat[1]) अणु
		हाल 'S':
			/*[S][pfs]*/
			जबतक (loop) अणु
				चयन (क्रमmat[index]) अणु
				हाल 'p':
				हाल 'f':
				हाल 's':
					ret++;
					index++;
					अवरोध;
				शेष:
					loop = 0;
					अवरोध;
				पूर्ण
			पूर्ण
			/* fall through */
		हाल '4':
			/* [4S][hnbl] */
			चयन (क्रमmat[index]) अणु
			हाल 'h':
			हाल 'n':
			हाल 'l':
			हाल 'b':
				ret++;
				index++;
				अवरोध;
			पूर्ण
			अगर (क्रमmat[1] == '4') अणु
				ret++;
				अवरोध;
			पूर्ण
			/* fall through */
		हाल '6':
			/* [6S]c */
			अगर (क्रमmat[index] == 'c')
				ret++;
			ret++;
			अवरोध;
		पूर्ण
		ret++;
		अवरोध;
	हाल 'U':
		चयन (क्रमmat[1]) अणु
		हाल 'L':
		हाल 'l':
		हाल 'B':
		हाल 'b':
			ret++;
			अवरोध;
		पूर्ण
		ret++;
		अवरोध;
	हाल 'h':
		चयन (क्रमmat[1]) अणु
		हाल 'C':
		हाल 'D':
		हाल 'N':
			ret++;
			अवरोध;
		पूर्ण
		ret++;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम मुक्त_parse_args(काष्ठा tep_prपूर्णांक_parse *arg)
अणु
	काष्ठा tep_prपूर्णांक_parse *del;

	जबतक (arg) अणु
		del = arg;
		arg = del->next;
		मुक्त(del->क्रमmat);
		मुक्त(del);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_arg_add(काष्ठा tep_prपूर्णांक_parse **parse, अक्षर *क्रमmat,
			 क्रमागत tep_prपूर्णांक_parse_type type,
			 काष्ठा tep_prपूर्णांक_arg *arg,
			 काष्ठा tep_prपूर्णांक_arg *len_as_arg,
			 पूर्णांक ls)
अणु
	काष्ठा tep_prपूर्णांक_parse *parg = शून्य;

	parg = सुस्मृति(1, माप(*parg));
	अगर (!parg)
		जाओ error;
	parg->क्रमmat = strdup(क्रमmat);
	अगर (!parg->क्रमmat)
		जाओ error;
	parg->type = type;
	parg->arg = arg;
	parg->len_as_arg = len_as_arg;
	parg->ls = ls;
	*parse = parg;
	वापस 0;
error:
	अगर (parg) अणु
		मुक्त(parg->क्रमmat);
		मुक्त(parg);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_arg_क्रमmat(काष्ठा tep_prपूर्णांक_parse **parse,
			    काष्ठा tep_event *event,
			    स्थिर अक्षर *क्रमmat, काष्ठा tep_prपूर्णांक_arg **arg)
अणु
	काष्ठा tep_prपूर्णांक_arg *len_arg = शून्य;
	अक्षर prपूर्णांक_क्रमmat[32];
	स्थिर अक्षर *start = क्रमmat;
	पूर्णांक ret = 0;
	पूर्णांक ls = 0;
	पूर्णांक res;
	पूर्णांक len;

	क्रमmat++;
	ret++;
	क्रम (; *क्रमmat; क्रमmat++) अणु
		चयन (*क्रमmat) अणु
		हाल '#':
			/* FIXME: need to handle properly */
			अवरोध;
		हाल 'h':
			ls--;
			अवरोध;
		हाल 'l':
			ls++;
			अवरोध;
		हाल 'L':
			ls = 2;
			अवरोध;
		हाल '.':
		हाल 'z':
		हाल 'Z':
		हाल '0' ... '9':
		हाल '-':
			अवरोध;
		हाल '*':
			/* The argument is the length. */
			अगर (!*arg) अणु
				करो_warning_event(event, "no argument match");
				event->flags |= TEP_EVENT_FL_FAILED;
				जाओ out_failed;
			पूर्ण
			अगर (len_arg) अणु
				करो_warning_event(event, "argument already matched");
				event->flags |= TEP_EVENT_FL_FAILED;
				जाओ out_failed;
			पूर्ण
			len_arg = *arg;
			*arg = (*arg)->next;
			अवरोध;
		हाल 'p':
			अगर (!*arg) अणु
				करो_warning_event(event, "no argument match");
				event->flags |= TEP_EVENT_FL_FAILED;
				जाओ out_failed;
			पूर्ण
			res = parse_arg_क्रमmat_poपूर्णांकer(क्रमmat + 1);
			अगर (res > 0) अणु
				क्रमmat += res;
				ret += res;
			पूर्ण
			len = ((अचिन्हित दीर्घ)क्रमmat + 1) -
				(अचिन्हित दीर्घ)start;
			/* should never happen */
			अगर (len > 31) अणु
				करो_warning_event(event, "bad format!");
				event->flags |= TEP_EVENT_FL_FAILED;
				len = 31;
			पूर्ण
			स_नकल(prपूर्णांक_क्रमmat, start, len);
			prपूर्णांक_क्रमmat[len] = 0;

			parse_arg_add(parse, prपूर्णांक_क्रमmat,
				      PRINT_FMT_ARG_POINTER, *arg, len_arg, ls);
			*arg = (*arg)->next;
			ret++;
			वापस ret;
		हाल 'd':
		हाल 'u':
		हाल 'i':
		हाल 'x':
		हाल 'X':
		हाल 'o':
			अगर (!*arg) अणु
				करो_warning_event(event, "no argument match");
				event->flags |= TEP_EVENT_FL_FAILED;
				जाओ out_failed;
			पूर्ण

			len = ((अचिन्हित दीर्घ)क्रमmat + 1) -
				(अचिन्हित दीर्घ)start;

			/* should never happen */
			अगर (len > 30) अणु
				करो_warning_event(event, "bad format!");
				event->flags |= TEP_EVENT_FL_FAILED;
				len = 31;
			पूर्ण
			स_नकल(prपूर्णांक_क्रमmat, start, len);
			prपूर्णांक_क्रमmat[len] = 0;

			अगर (event->tep->दीर्घ_size == 8 && ls == 1 &&
			    माप(दीर्घ) != 8) अणु
				अक्षर *p;

				/* make %l पूर्णांकo %ll */
				अगर (ls == 1 && (p = म_अक्षर(prपूर्णांक_क्रमmat, 'l')))
					स_हटाओ(p+1, p, म_माप(p)+1);
				ls = 2;
			पूर्ण
			अगर (ls < -2 || ls > 2) अणु
				करो_warning_event(event, "bad count (%d)", ls);
				event->flags |= TEP_EVENT_FL_FAILED;
			पूर्ण
			parse_arg_add(parse, prपूर्णांक_क्रमmat,
				      PRINT_FMT_ARG_DIGIT, *arg, len_arg, ls);
			*arg = (*arg)->next;
			ret++;
			वापस ret;
		हाल 's':
			अगर (!*arg) अणु
				करो_warning_event(event, "no matching argument");
				event->flags |= TEP_EVENT_FL_FAILED;
				जाओ out_failed;
			पूर्ण

			len = ((अचिन्हित दीर्घ)क्रमmat + 1) -
				(अचिन्हित दीर्घ)start;

			/* should never happen */
			अगर (len > 31) अणु
				करो_warning_event(event, "bad format!");
				event->flags |= TEP_EVENT_FL_FAILED;
				len = 31;
			पूर्ण

			स_नकल(prपूर्णांक_क्रमmat, start, len);
			prपूर्णांक_क्रमmat[len] = 0;

			parse_arg_add(parse, prपूर्णांक_क्रमmat,
					PRINT_FMT_ARG_STRING, *arg, len_arg, 0);
			*arg = (*arg)->next;
			ret++;
			वापस ret;
		शेष:
			snम_लिखो(prपूर्णांक_क्रमmat, 32, ">%c<", *क्रमmat);
			parse_arg_add(parse, prपूर्णांक_क्रमmat,
					PRINT_FMT_STRING, शून्य, शून्य, 0);
			ret++;
			वापस ret;
		पूर्ण
		ret++;
	पूर्ण

out_failed:
	वापस ret;

पूर्ण

अटल पूर्णांक parse_arg_string(काष्ठा tep_prपूर्णांक_parse **parse, स्थिर अक्षर *क्रमmat)
अणु
	काष्ठा trace_seq s;
	पूर्णांक ret = 0;

	trace_seq_init(&s);
	क्रम (; *क्रमmat; क्रमmat++) अणु
		अगर (*क्रमmat == '\\') अणु
			क्रमmat++;
			ret++;
			चयन (*क्रमmat) अणु
			हाल 'n':
				trace_seq_अ_दो(&s, '\n');
				अवरोध;
			हाल 't':
				trace_seq_अ_दो(&s, '\t');
				अवरोध;
			हाल 'r':
				trace_seq_अ_दो(&s, '\r');
				अवरोध;
			हाल '\\':
				trace_seq_अ_दो(&s, '\\');
				अवरोध;
			शेष:
				trace_seq_अ_दो(&s, *क्रमmat);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (*क्रमmat == '%') अणु
			अगर (*(क्रमmat + 1) == '%') अणु
				trace_seq_अ_दो(&s, '%');
				क्रमmat++;
				ret++;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण अन्यथा
			trace_seq_अ_दो(&s, *क्रमmat);

		ret++;
	पूर्ण
	trace_seq_terminate(&s);
	parse_arg_add(parse, s.buffer, PRINT_FMT_STRING, शून्य, शून्य, 0);
	trace_seq_destroy(&s);

	वापस ret;
पूर्ण

अटल काष्ठा tep_prपूर्णांक_parse *
parse_args(काष्ठा tep_event *event, स्थिर अक्षर *क्रमmat, काष्ठा tep_prपूर्णांक_arg *arg)
अणु
	काष्ठा tep_prपूर्णांक_parse *parse_ret = शून्य;
	काष्ठा tep_prपूर्णांक_parse **parse = शून्य;
	पूर्णांक ret;
	पूर्णांक len;

	len = म_माप(क्रमmat);
	जबतक (*क्रमmat) अणु
		अगर (!parse_ret)
			parse = &parse_ret;
		अगर (*क्रमmat == '%' && *(format + 1) != '%')
			ret = parse_arg_क्रमmat(parse, event, क्रमmat, &arg);
		अन्यथा
			ret = parse_arg_string(parse, क्रमmat);
		अगर (*parse)
			parse = &((*parse)->next);

		len -= ret;
		अगर (len > 0)
			क्रमmat += ret;
		अन्यथा
			अवरोध;
	पूर्ण
	वापस parse_ret;
पूर्ण

अटल व्योम prपूर्णांक_event_cache(काष्ठा tep_prपूर्णांक_parse *parse, काष्ठा trace_seq *s,
			      व्योम *data, पूर्णांक size, काष्ठा tep_event *event)
अणु
	पूर्णांक len_arg;

	जबतक (parse) अणु
		अगर (parse->len_as_arg)
			len_arg = eval_num_arg(data, size, event, parse->len_as_arg);
		चयन (parse->type) अणु
		हाल PRINT_FMT_ARG_DIGIT:
			prपूर्णांक_arg_number(s, parse->क्रमmat,
					parse->len_as_arg ? len_arg : -1, data,
					 size, parse->ls, event, parse->arg);
			अवरोध;
		हाल PRINT_FMT_ARG_POINTER:
			prपूर्णांक_arg_poपूर्णांकer(s, parse->क्रमmat,
					  parse->len_as_arg ? len_arg : 1,
					  data, size, event, parse->arg);
			अवरोध;
		हाल PRINT_FMT_ARG_STRING:
			prपूर्णांक_arg_string(s, parse->क्रमmat,
					 parse->len_as_arg ? len_arg : -1,
					 data, size, event, parse->arg);
			अवरोध;
		हाल PRINT_FMT_STRING:
		शेष:
			trace_seq_म_लिखो(s, "%s", parse->क्रमmat);
			अवरोध;
		पूर्ण
		parse = parse->next;
	पूर्ण
पूर्ण

अटल व्योम pretty_prपूर्णांक(काष्ठा trace_seq *s, व्योम *data, पूर्णांक size, काष्ठा tep_event *event)
अणु
	काष्ठा tep_prपूर्णांक_parse *parse = event->prपूर्णांक_fmt.prपूर्णांक_cache;
	काष्ठा tep_prपूर्णांक_arg *args = शून्य;
	अक्षर *bprपूर्णांक_fmt = शून्य;

	अगर (event->flags & TEP_EVENT_FL_FAILED) अणु
		trace_seq_म_लिखो(s, "[FAILED TO PARSE]");
		tep_prपूर्णांक_fields(s, data, size, event);
		वापस;
	पूर्ण

	अगर (event->flags & TEP_EVENT_FL_ISBPRINT) अणु
		bprपूर्णांक_fmt = get_bprपूर्णांक_क्रमmat(data, size, event);
		args = make_bprपूर्णांक_args(bprपूर्णांक_fmt, data, size, event);
		parse = parse_args(event, bprपूर्णांक_fmt, args);
	पूर्ण

	prपूर्णांक_event_cache(parse, s, data, size, event);

	अगर (event->flags & TEP_EVENT_FL_ISBPRINT) अणु
		मुक्त_parse_args(parse);
		मुक्त_args(args);
		मुक्त(bprपूर्णांक_fmt);
	पूर्ण
पूर्ण

/*
 * This parses out the Latency क्रमmat (पूर्णांकerrupts disabled,
 * need rescheduling, in hard/soft पूर्णांकerrupt, preempt count
 * and lock depth) and places it पूर्णांकo the trace_seq.
 */
अटल व्योम data_latency_क्रमmat(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
				अक्षर *क्रमmat, काष्ठा tep_record *record)
अणु
	अटल पूर्णांक check_lock_depth = 1;
	अटल पूर्णांक check_migrate_disable = 1;
	अटल पूर्णांक lock_depth_exists;
	अटल पूर्णांक migrate_disable_exists;
	अचिन्हित पूर्णांक lat_flags;
	काष्ठा trace_seq sq;
	अचिन्हित पूर्णांक pc;
	पूर्णांक lock_depth = 0;
	पूर्णांक migrate_disable = 0;
	पूर्णांक hardirq;
	पूर्णांक softirq;
	व्योम *data = record->data;

	trace_seq_init(&sq);
	lat_flags = parse_common_flags(tep, data);
	pc = parse_common_pc(tep, data);
	/* lock_depth may not always exist */
	अगर (lock_depth_exists)
		lock_depth = parse_common_lock_depth(tep, data);
	अन्यथा अगर (check_lock_depth) अणु
		lock_depth = parse_common_lock_depth(tep, data);
		अगर (lock_depth < 0)
			check_lock_depth = 0;
		अन्यथा
			lock_depth_exists = 1;
	पूर्ण

	/* migrate_disable may not always exist */
	अगर (migrate_disable_exists)
		migrate_disable = parse_common_migrate_disable(tep, data);
	अन्यथा अगर (check_migrate_disable) अणु
		migrate_disable = parse_common_migrate_disable(tep, data);
		अगर (migrate_disable < 0)
			check_migrate_disable = 0;
		अन्यथा
			migrate_disable_exists = 1;
	पूर्ण

	hardirq = lat_flags & TRACE_FLAG_HARसूचीQ;
	softirq = lat_flags & TRACE_FLAG_SOFTIRQ;

	trace_seq_म_लिखो(&sq, "%c%c%c",
	       (lat_flags & TRACE_FLAG_IRQS_OFF) ? 'd' :
	       (lat_flags & TRACE_FLAG_IRQS_NOSUPPORT) ?
	       'X' : '.',
	       (lat_flags & TRACE_FLAG_NEED_RESCHED) ?
	       'N' : '.',
	       (hardirq && softirq) ? 'H' :
	       hardirq ? 'h' : softirq ? 's' : '.');

	अगर (pc)
		trace_seq_म_लिखो(&sq, "%x", pc);
	अन्यथा
		trace_seq_म_लिखो(&sq, ".");

	अगर (migrate_disable_exists) अणु
		अगर (migrate_disable < 0)
			trace_seq_म_लिखो(&sq, ".");
		अन्यथा
			trace_seq_म_लिखो(&sq, "%d", migrate_disable);
	पूर्ण

	अगर (lock_depth_exists) अणु
		अगर (lock_depth < 0)
			trace_seq_म_लिखो(&sq, ".");
		अन्यथा
			trace_seq_म_लिखो(&sq, "%d", lock_depth);
	पूर्ण

	अगर (sq.state == TRACE_SEQ__MEM_ALLOC_FAILED) अणु
		s->state = TRACE_SEQ__MEM_ALLOC_FAILED;
		वापस;
	पूर्ण

	trace_seq_terminate(&sq);
	trace_seq_माला_दो(s, sq.buffer);
	trace_seq_destroy(&sq);
	trace_seq_terminate(s);
पूर्ण

/**
 * tep_data_type - parse out the given event type
 * @tep: a handle to the trace event parser context
 * @rec: the record to पढ़ो from
 *
 * This वापसs the event id from the @rec.
 */
पूर्णांक tep_data_type(काष्ठा tep_handle *tep, काष्ठा tep_record *rec)
अणु
	वापस trace_parse_common_type(tep, rec->data);
पूर्ण

/**
 * tep_data_pid - parse the PID from record
 * @tep: a handle to the trace event parser context
 * @rec: the record to parse
 *
 * This वापसs the PID from a record.
 */
पूर्णांक tep_data_pid(काष्ठा tep_handle *tep, काष्ठा tep_record *rec)
अणु
	वापस parse_common_pid(tep, rec->data);
पूर्ण

/**
 * tep_data_preempt_count - parse the preempt count from the record
 * @tep: a handle to the trace event parser context
 * @rec: the record to parse
 *
 * This वापसs the preempt count from a record.
 */
पूर्णांक tep_data_preempt_count(काष्ठा tep_handle *tep, काष्ठा tep_record *rec)
अणु
	वापस parse_common_pc(tep, rec->data);
पूर्ण

/**
 * tep_data_flags - parse the latency flags from the record
 * @tep: a handle to the trace event parser context
 * @rec: the record to parse
 *
 * This वापसs the latency flags from a record.
 *
 *  Use trace_flag_type क्रमागत क्रम the flags (see event-parse.h).
 */
पूर्णांक tep_data_flags(काष्ठा tep_handle *tep, काष्ठा tep_record *rec)
अणु
	वापस parse_common_flags(tep, rec->data);
पूर्ण

/**
 * tep_data_comm_from_pid - वापस the command line from PID
 * @tep: a handle to the trace event parser context
 * @pid: the PID of the task to search क्रम
 *
 * This वापसs a poपूर्णांकer to the command line that has the given
 * @pid.
 */
स्थिर अक्षर *tep_data_comm_from_pid(काष्ठा tep_handle *tep, पूर्णांक pid)
अणु
	स्थिर अक्षर *comm;

	comm = find_cmdline(tep, pid);
	वापस comm;
पूर्ण

अटल काष्ठा tep_cmdline *
pid_from_cmdlist(काष्ठा tep_handle *tep, स्थिर अक्षर *comm, काष्ठा tep_cmdline *next)
अणु
	काष्ठा cmdline_list *cmdlist = (काष्ठा cmdline_list *)next;

	अगर (cmdlist)
		cmdlist = cmdlist->next;
	अन्यथा
		cmdlist = tep->cmdlist;

	जबतक (cmdlist && म_भेद(cmdlist->comm, comm) != 0)
		cmdlist = cmdlist->next;

	वापस (काष्ठा tep_cmdline *)cmdlist;
पूर्ण

/**
 * tep_data_pid_from_comm - वापस the pid from a given comm
 * @tep: a handle to the trace event parser context
 * @comm: the cmdline to find the pid from
 * @next: the cmdline काष्ठाure to find the next comm
 *
 * This वापसs the cmdline काष्ठाure that holds a pid क्रम a given
 * comm, or शून्य अगर none found. As there may be more than one pid क्रम
 * a given comm, the result of this call can be passed back पूर्णांकo
 * a recurring call in the @next parameter, and then it will find the
 * next pid.
 * Also, it करोes a linear search, so it may be slow.
 */
काष्ठा tep_cmdline *tep_data_pid_from_comm(काष्ठा tep_handle *tep, स्थिर अक्षर *comm,
					   काष्ठा tep_cmdline *next)
अणु
	काष्ठा tep_cmdline *cmdline;

	/*
	 * If the cmdlines have not been converted yet, then use
	 * the list.
	 */
	अगर (!tep->cmdlines)
		वापस pid_from_cmdlist(tep, comm, next);

	अगर (next) अणु
		/*
		 * The next poपूर्णांकer could have been still from
		 * a previous call beक्रमe cmdlines were created
		 */
		अगर (next < tep->cmdlines ||
		    next >= tep->cmdlines + tep->cmdline_count)
			next = शून्य;
		अन्यथा
			cmdline  = next++;
	पूर्ण

	अगर (!next)
		cmdline = tep->cmdlines;

	जबतक (cmdline < tep->cmdlines + tep->cmdline_count) अणु
		अगर (म_भेद(cmdline->comm, comm) == 0)
			वापस cmdline;
		cmdline++;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * tep_cmdline_pid - वापस the pid associated to a given cmdline
 * @tep: a handle to the trace event parser context
 * @cmdline: The cmdline काष्ठाure to get the pid from
 *
 * Returns the pid क्रम a give cmdline. If @cmdline is शून्य, then
 * -1 is वापसed.
 */
पूर्णांक tep_cmdline_pid(काष्ठा tep_handle *tep, काष्ठा tep_cmdline *cmdline)
अणु
	काष्ठा cmdline_list *cmdlist = (काष्ठा cmdline_list *)cmdline;

	अगर (!cmdline)
		वापस -1;

	/*
	 * If cmdlines have not been created yet, or cmdline is
	 * not part of the array, then treat it as a cmdlist instead.
	 */
	अगर (!tep->cmdlines ||
	    cmdline < tep->cmdlines ||
	    cmdline >= tep->cmdlines + tep->cmdline_count)
		वापस cmdlist->pid;

	वापस cmdline->pid;
पूर्ण

/*
 * This parses the raw @data using the given @event inक्रमmation and
 * ग_लिखोs the prपूर्णांक क्रमmat पूर्णांकo the trace_seq.
 */
अटल व्योम prपूर्णांक_event_info(काष्ठा trace_seq *s, अक्षर *क्रमmat, bool raw,
			     काष्ठा tep_event *event, काष्ठा tep_record *record)
अणु
	पूर्णांक prपूर्णांक_pretty = 1;

	अगर (raw || (event->flags & TEP_EVENT_FL_PRINTRAW))
		tep_prपूर्णांक_fields(s, record->data, record->size, event);
	अन्यथा अणु

		अगर (event->handler && !(event->flags & TEP_EVENT_FL_NOHANDLE))
			prपूर्णांक_pretty = event->handler(s, record, event,
						      event->context);

		अगर (prपूर्णांक_pretty)
			pretty_prपूर्णांक(s, record->data, record->size, event);
	पूर्ण

	trace_seq_terminate(s);
पूर्ण

/**
 * tep_find_event_by_record - वापस the event from a given record
 * @tep: a handle to the trace event parser context
 * @record: The record to get the event from
 *
 * Returns the associated event क्रम a given record, or शून्य अगर non is
 * is found.
 */
काष्ठा tep_event *
tep_find_event_by_record(काष्ठा tep_handle *tep, काष्ठा tep_record *record)
अणु
	पूर्णांक type;

	अगर (record->size < 0) अणु
		करो_warning("ug! negative record size %d", record->size);
		वापस शून्य;
	पूर्ण

	type = trace_parse_common_type(tep, record->data);

	वापस tep_find_event(tep, type);
पूर्ण

/*
 * Writes the बारtamp of the record पूर्णांकo @s. Time भागisor and precision can be
 * specअगरied as part of म_लिखो @क्रमmat string. Example:
 *	"%3.1000d" - भागide the समय by 1000 and prपूर्णांक the first 3 digits
 *	beक्रमe the करोt. Thus, the बारtamp "123456000" will be prपूर्णांकed as
 *	"123.456"
 */
अटल व्योम prपूर्णांक_event_समय(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
				 अक्षर *क्रमmat, काष्ठा tep_event *event,
				 काष्ठा tep_record *record)
अणु
	अचिन्हित दीर्घ दीर्घ समय;
	अक्षर *भागstr;
	पूर्णांक prec = 0, pr;
	पूर्णांक भाग = 0;
	पूर्णांक p10 = 1;

	अगर (है_अंक(*(क्रमmat + 1)))
		prec = म_से_प(क्रमmat + 1);
	भागstr = म_अक्षर(क्रमmat, '.');
	अगर (भागstr && है_अंक(*(भागstr + 1)))
		भाग = म_से_प(भागstr + 1);
	समय = record->ts;
	अगर (भाग) अणु
		समय += भाग / 2;
		समय /= भाग;
	पूर्ण
	pr = prec;
	जबतक (pr--)
		p10 *= 10;

	अगर (p10 > 1 && p10 < समय)
		trace_seq_म_लिखो(s, "%5llu.%0*llu", समय / p10, prec, समय % p10);
	अन्यथा
		trace_seq_म_लिखो(s, "%12llu", समय);
पूर्ण

काष्ठा prपूर्णांक_event_type अणु
	क्रमागत अणु
		EVENT_TYPE_INT = 1,
		EVENT_TYPE_STRING,
		EVENT_TYPE_UNKNOWN,
	पूर्ण type;
	अक्षर क्रमmat[32];
पूर्ण;

अटल व्योम prपूर्णांक_string(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
			 काष्ठा tep_record *record, काष्ठा tep_event *event,
			 स्थिर अक्षर *arg, काष्ठा prपूर्णांक_event_type *type)
अणु
	स्थिर अक्षर *comm;
	पूर्णांक pid;

	अगर (म_भेदन(arg, TEP_PRINT_LATENCY, म_माप(TEP_PRINT_LATENCY)) == 0) अणु
		data_latency_क्रमmat(tep, s, type->क्रमmat, record);
	पूर्ण अन्यथा अगर (म_भेदन(arg, TEP_PRINT_COMM, म_माप(TEP_PRINT_COMM)) == 0) अणु
		pid = parse_common_pid(tep, record->data);
		comm = find_cmdline(tep, pid);
		trace_seq_म_लिखो(s, type->क्रमmat, comm);
	पूर्ण अन्यथा अगर (म_भेदन(arg, TEP_PRINT_INFO_RAW, म_माप(TEP_PRINT_INFO_RAW)) == 0) अणु
		prपूर्णांक_event_info(s, type->क्रमmat, true, event, record);
	पूर्ण अन्यथा अगर (म_भेदन(arg, TEP_PRINT_INFO, म_माप(TEP_PRINT_INFO)) == 0) अणु
		prपूर्णांक_event_info(s, type->क्रमmat, false, event, record);
	पूर्ण अन्यथा अगर  (म_भेदन(arg, TEP_PRINT_NAME, म_माप(TEP_PRINT_NAME)) == 0) अणु
		trace_seq_म_लिखो(s, type->क्रमmat, event->name);
	पूर्ण अन्यथा अणु
		trace_seq_म_लिखो(s, "[UNKNOWN TEP TYPE %s]", arg);
	पूर्ण

पूर्ण

अटल व्योम prपूर्णांक_पूर्णांक(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
		      काष्ठा tep_record *record, काष्ठा tep_event *event,
		      पूर्णांक arg, काष्ठा prपूर्णांक_event_type *type)
अणु
	पूर्णांक param;

	चयन (arg) अणु
	हाल TEP_PRINT_CPU:
		param = record->cpu;
		अवरोध;
	हाल TEP_PRINT_PID:
		param = parse_common_pid(tep, record->data);
		अवरोध;
	हाल TEP_PRINT_TIME:
		वापस prपूर्णांक_event_समय(tep, s, type->क्रमmat, event, record);
	शेष:
		वापस;
	पूर्ण
	trace_seq_म_लिखो(s, type->क्रमmat, param);
पूर्ण

अटल पूर्णांक tep_prपूर्णांक_event_param_type(अक्षर *क्रमmat,
				      काष्ठा prपूर्णांक_event_type *type)
अणु
	अक्षर *str = क्रमmat + 1;
	पूर्णांक i = 1;

	type->type = EVENT_TYPE_UNKNOWN;
	जबतक (*str) अणु
		चयन (*str) अणु
		हाल 'd':
		हाल 'u':
		हाल 'i':
		हाल 'x':
		हाल 'X':
		हाल 'o':
			type->type = EVENT_TYPE_INT;
			अवरोध;
		हाल 's':
			type->type = EVENT_TYPE_STRING;
			अवरोध;
		पूर्ण
		str++;
		i++;
		अगर (type->type != EVENT_TYPE_UNKNOWN)
			अवरोध;
	पूर्ण
	स_रखो(type->क्रमmat, 0, 32);
	स_नकल(type->क्रमmat, क्रमmat, i < 32 ? i : 31);
	वापस i;
पूर्ण

/**
 * tep_prपूर्णांक_event - Write various event inक्रमmation
 * @tep: a handle to the trace event parser context
 * @s: the trace_seq to ग_लिखो to
 * @record: The record to get the event from
 * @क्रमmat: a म_लिखो क्रमmat string. Supported event fileds:
 *	TEP_PRINT_PID, "%d" - event PID
 *	TEP_PRINT_CPU, "%d" - event CPU
 *	TEP_PRINT_COMM, "%s" - event command string
 *	TEP_PRINT_NAME, "%s" - event name
 *	TEP_PRINT_LATENCY, "%s" - event latency
 *	TEP_PRINT_TIME, %d - event समय stamp. A भागisor and precision
 *			can be specअगरied as part of this क्रमmat string:
 *			"%precision.divisord". Example:
 *			"%3.1000d" - भागide the समय by 1000 and prपूर्णांक the first
 *			3 digits beक्रमe the करोt. Thus, the समय stamp
 *			"123456000" will be prपूर्णांकed as "123.456"
 *	TEP_PRINT_INFO, "%s" - event inक्रमmation. If any width is specअगरied in
 *			the क्रमmat string, the event inक्रमmation will be prपूर्णांकed
 *			in raw क्रमmat.
 * Writes the specअगरied event inक्रमmation पूर्णांकo @s.
 */
व्योम tep_prपूर्णांक_event(काष्ठा tep_handle *tep, काष्ठा trace_seq *s,
		     काष्ठा tep_record *record, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा prपूर्णांक_event_type type;
	अक्षर *क्रमmat = strdup(fmt);
	अक्षर *current = क्रमmat;
	अक्षर *str = क्रमmat;
	पूर्णांक offset;
	बहु_सूची args;
	काष्ठा tep_event *event;

	अगर (!क्रमmat)
		वापस;

	event = tep_find_event_by_record(tep, record);
	बहु_शुरू(args, fmt);
	जबतक (*current) अणु
		current = म_अक्षर(str, '%');
		अगर (!current) अणु
			trace_seq_माला_दो(s, str);
			अवरोध;
		पूर्ण
		स_रखो(&type, 0, माप(type));
		offset = tep_prपूर्णांक_event_param_type(current, &type);
		*current = '\0';
		trace_seq_माला_दो(s, str);
		current += offset;
		चयन (type.type) अणु
		हाल EVENT_TYPE_STRING:
			prपूर्णांक_string(tep, s, record, event,
				     बहु_तर्क(args, अक्षर*), &type);
			अवरोध;
		हाल EVENT_TYPE_INT:
			prपूर्णांक_पूर्णांक(tep, s, record, event,
				  बहु_तर्क(args, पूर्णांक), &type);
			अवरोध;
		हाल EVENT_TYPE_UNKNOWN:
		शेष:
			trace_seq_म_लिखो(s, "[UNKNOWN TYPE]");
			अवरोध;
		पूर्ण
		str = current;

	पूर्ण
	बहु_पूर्ण(args);
	मुक्त(क्रमmat);
पूर्ण

अटल पूर्णांक events_id_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा tep_event * स्थिर * ea = a;
	काष्ठा tep_event * स्थिर * eb = b;

	अगर ((*ea)->id < (*eb)->id)
		वापस -1;

	अगर ((*ea)->id > (*eb)->id)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक events_name_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा tep_event * स्थिर * ea = a;
	काष्ठा tep_event * स्थिर * eb = b;
	पूर्णांक res;

	res = म_भेद((*ea)->name, (*eb)->name);
	अगर (res)
		वापस res;

	res = म_भेद((*ea)->प्रणाली, (*eb)->प्रणाली);
	अगर (res)
		वापस res;

	वापस events_id_cmp(a, b);
पूर्ण

अटल पूर्णांक events_प्रणाली_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	काष्ठा tep_event * स्थिर * ea = a;
	काष्ठा tep_event * स्थिर * eb = b;
	पूर्णांक res;

	res = म_भेद((*ea)->प्रणाली, (*eb)->प्रणाली);
	अगर (res)
		वापस res;

	res = म_भेद((*ea)->name, (*eb)->name);
	अगर (res)
		वापस res;

	वापस events_id_cmp(a, b);
पूर्ण

अटल काष्ठा tep_event **list_events_copy(काष्ठा tep_handle *tep)
अणु
	काष्ठा tep_event **events;

	अगर (!tep)
		वापस शून्य;

	events = दो_स्मृति(माप(*events) * (tep->nr_events + 1));
	अगर (!events)
		वापस शून्य;

	स_नकल(events, tep->events, माप(*events) * tep->nr_events);
	events[tep->nr_events] = शून्य;
	वापस events;
पूर्ण

अटल व्योम list_events_sort(काष्ठा tep_event **events, पूर्णांक nr_events,
			     क्रमागत tep_event_sort_type sort_type)
अणु
	पूर्णांक (*sort)(स्थिर व्योम *a, स्थिर व्योम *b);

	चयन (sort_type) अणु
	हाल TEP_EVENT_SORT_ID:
		sort = events_id_cmp;
		अवरोध;
	हाल TEP_EVENT_SORT_NAME:
		sort = events_name_cmp;
		अवरोध;
	हाल TEP_EVENT_SORT_SYSTEM:
		sort = events_प्रणाली_cmp;
		अवरोध;
	शेष:
		sort = शून्य;
	पूर्ण

	अगर (sort)
		क्विक(events, nr_events, माप(*events), sort);
पूर्ण

/**
 * tep_list_events - Get events, sorted by given criteria.
 * @tep: a handle to the tep context
 * @sort_type: desired sort order of the events in the array
 *
 * Returns an array of poपूर्णांकers to all events, sorted by the given
 * @sort_type criteria. The last element of the array is शून्य. The वापसed
 * memory must not be मुक्तd, it is managed by the library.
 * The function is not thपढ़ो safe.
 */
काष्ठा tep_event **tep_list_events(काष्ठा tep_handle *tep,
				   क्रमागत tep_event_sort_type sort_type)
अणु
	काष्ठा tep_event **events;

	अगर (!tep)
		वापस शून्य;

	events = tep->sort_events;
	अगर (events && tep->last_type == sort_type)
		वापस events;

	अगर (!events) अणु
		events = list_events_copy(tep);
		अगर (!events)
			वापस शून्य;

		tep->sort_events = events;

		/* the पूर्णांकernal events are sorted by id */
		अगर (sort_type == TEP_EVENT_SORT_ID) अणु
			tep->last_type = sort_type;
			वापस events;
		पूर्ण
	पूर्ण

	list_events_sort(events, tep->nr_events, sort_type);
	tep->last_type = sort_type;

	वापस events;
पूर्ण


/**
 * tep_list_events_copy - Thपढ़ो safe version of tep_list_events()
 * @tep: a handle to the tep context
 * @sort_type: desired sort order of the events in the array
 *
 * Returns an array of poपूर्णांकers to all events, sorted by the given
 * @sort_type criteria. The last element of the array is शून्य. The वापसed
 * array is newly allocated inside the function and must be मुक्तd by the caller
 */
काष्ठा tep_event **tep_list_events_copy(काष्ठा tep_handle *tep,
					क्रमागत tep_event_sort_type sort_type)
अणु
	काष्ठा tep_event **events;

	अगर (!tep)
		वापस शून्य;

	events = list_events_copy(tep);
	अगर (!events)
		वापस शून्य;

	/* the पूर्णांकernal events are sorted by id */
	अगर (sort_type == TEP_EVENT_SORT_ID)
		वापस events;

	list_events_sort(events, tep->nr_events, sort_type);

	वापस events;
पूर्ण

अटल काष्ठा tep_क्रमmat_field **
get_event_fields(स्थिर अक्षर *type, स्थिर अक्षर *name,
		 पूर्णांक count, काष्ठा tep_क्रमmat_field *list)
अणु
	काष्ठा tep_क्रमmat_field **fields;
	काष्ठा tep_क्रमmat_field *field;
	पूर्णांक i = 0;

	fields = दो_स्मृति(माप(*fields) * (count + 1));
	अगर (!fields)
		वापस शून्य;

	क्रम (field = list; field; field = field->next) अणु
		fields[i++] = field;
		अगर (i == count + 1) अणु
			करो_warning("event %s has more %s fields than specified",
				name, type);
			i--;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i != count)
		करो_warning("event %s has less %s fields than specified",
			name, type);

	fields[i] = शून्य;

	वापस fields;
पूर्ण

/**
 * tep_event_common_fields - वापस a list of common fields क्रम an event
 * @event: the event to वापस the common fields of.
 *
 * Returns an allocated array of fields. The last item in the array is शून्य.
 * The array must be मुक्तd with मुक्त().
 */
काष्ठा tep_क्रमmat_field **tep_event_common_fields(काष्ठा tep_event *event)
अणु
	वापस get_event_fields("common", event->name,
				event->क्रमmat.nr_common,
				event->क्रमmat.common_fields);
पूर्ण

/**
 * tep_event_fields - वापस a list of event specअगरic fields क्रम an event
 * @event: the event to वापस the fields of.
 *
 * Returns an allocated array of fields. The last item in the array is शून्य.
 * The array must be मुक्तd with मुक्त().
 */
काष्ठा tep_क्रमmat_field **tep_event_fields(काष्ठा tep_event *event)
अणु
	वापस get_event_fields("event", event->name,
				event->क्रमmat.nr_fields,
				event->क्रमmat.fields);
पूर्ण

अटल व्योम prपूर्णांक_fields(काष्ठा trace_seq *s, काष्ठा tep_prपूर्णांक_flag_sym *field)
अणु
	trace_seq_म_लिखो(s, "{ %s, %s }", field->value, field->str);
	अगर (field->next) अणु
		trace_seq_माला_दो(s, ", ");
		prपूर्णांक_fields(s, field->next);
	पूर्ण
पूर्ण

/* क्रम debugging */
अटल व्योम prपूर्णांक_args(काष्ठा tep_prपूर्णांक_arg *args)
अणु
	पूर्णांक prपूर्णांक_paren = 1;
	काष्ठा trace_seq s;

	चयन (args->type) अणु
	हाल TEP_PRINT_शून्य:
		म_लिखो("null");
		अवरोध;
	हाल TEP_PRINT_ATOM:
		म_लिखो("%s", args->atom.atom);
		अवरोध;
	हाल TEP_PRINT_FIELD:
		म_लिखो("REC->%s", args->field.name);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
		म_लिखो("__print_flags(");
		prपूर्णांक_args(args->flags.field);
		म_लिखो(", %s, ", args->flags.delim);
		trace_seq_init(&s);
		prपूर्णांक_fields(&s, args->flags.flags);
		trace_seq_करो_म_लिखो(&s);
		trace_seq_destroy(&s);
		म_लिखो(")");
		अवरोध;
	हाल TEP_PRINT_SYMBOL:
		म_लिखो("__print_symbolic(");
		prपूर्णांक_args(args->symbol.field);
		म_लिखो(", ");
		trace_seq_init(&s);
		prपूर्णांक_fields(&s, args->symbol.symbols);
		trace_seq_करो_म_लिखो(&s);
		trace_seq_destroy(&s);
		म_लिखो(")");
		अवरोध;
	हाल TEP_PRINT_HEX:
		म_लिखो("__print_hex(");
		prपूर्णांक_args(args->hex.field);
		म_लिखो(", ");
		prपूर्णांक_args(args->hex.size);
		म_लिखो(")");
		अवरोध;
	हाल TEP_PRINT_HEX_STR:
		म_लिखो("__print_hex_str(");
		prपूर्णांक_args(args->hex.field);
		म_लिखो(", ");
		prपूर्णांक_args(args->hex.size);
		म_लिखो(")");
		अवरोध;
	हाल TEP_PRINT_INT_ARRAY:
		म_लिखो("__print_array(");
		prपूर्णांक_args(args->पूर्णांक_array.field);
		म_लिखो(", ");
		prपूर्णांक_args(args->पूर्णांक_array.count);
		म_लिखो(", ");
		prपूर्णांक_args(args->पूर्णांक_array.el_size);
		म_लिखो(")");
		अवरोध;
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BSTRING:
		म_लिखो("__get_str(%s)", args->string.string);
		अवरोध;
	हाल TEP_PRINT_BITMASK:
		म_लिखो("__get_bitmask(%s)", args->biपंचांगask.biपंचांगask);
		अवरोध;
	हाल TEP_PRINT_TYPE:
		म_लिखो("(%s)", args->typecast.type);
		prपूर्णांक_args(args->typecast.item);
		अवरोध;
	हाल TEP_PRINT_OP:
		अगर (म_भेद(args->op.op, ":") == 0)
			prपूर्णांक_paren = 0;
		अगर (prपूर्णांक_paren)
			म_लिखो("(");
		prपूर्णांक_args(args->op.left);
		म_लिखो(" %s ", args->op.op);
		prपूर्णांक_args(args->op.right);
		अगर (prपूर्णांक_paren)
			म_लिखो(")");
		अवरोध;
	शेष:
		/* we should warn... */
		वापस;
	पूर्ण
	अगर (args->next) अणु
		म_लिखो("\n");
		prपूर्णांक_args(args->next);
	पूर्ण
पूर्ण

अटल व्योम parse_header_field(स्थिर अक्षर *field,
			       पूर्णांक *offset, पूर्णांक *size, पूर्णांक mandatory)
अणु
	अचिन्हित दीर्घ दीर्घ save_input_buf_ptr;
	अचिन्हित दीर्घ दीर्घ save_input_buf_siz;
	अक्षर *token;
	पूर्णांक type;

	save_input_buf_ptr = input_buf_ptr;
	save_input_buf_siz = input_buf_siz;

	अगर (पढ़ो_expected(TEP_EVENT_ITEM, "field") < 0)
		वापस;
	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस;

	/* type */
	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ fail;
	मुक्त_token(token);

	/*
	 * If this is not a mandatory field, then test it first.
	 */
	अगर (mandatory) अणु
		अगर (पढ़ो_expected(TEP_EVENT_ITEM, field) < 0)
			वापस;
	पूर्ण अन्यथा अणु
		अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
			जाओ fail;
		अगर (म_भेद(token, field) != 0)
			जाओ discard;
		मुक्त_token(token);
	पूर्ण

	अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
		वापस;
	अगर (पढ़ो_expected(TEP_EVENT_ITEM, "offset") < 0)
		वापस;
	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस;
	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ fail;
	*offset = म_से_प(token);
	मुक्त_token(token);
	अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
		वापस;
	अगर (पढ़ो_expected(TEP_EVENT_ITEM, "size") < 0)
		वापस;
	अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
		वापस;
	अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token) < 0)
		जाओ fail;
	*size = म_से_प(token);
	मुक्त_token(token);
	अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
		वापस;
	type = पढ़ो_token(&token);
	अगर (type != TEP_EVENT_NEWLINE) अणु
		/* newer versions of the kernel have a "signed" type */
		अगर (type != TEP_EVENT_ITEM)
			जाओ fail;

		अगर (म_भेद(token, "signed") != 0)
			जाओ fail;

		मुक्त_token(token);

		अगर (पढ़ो_expected(TEP_EVENT_OP, ":") < 0)
			वापस;

		अगर (पढ़ो_expect_type(TEP_EVENT_ITEM, &token))
			जाओ fail;

		मुक्त_token(token);
		अगर (पढ़ो_expected(TEP_EVENT_OP, ";") < 0)
			वापस;

		अगर (पढ़ो_expect_type(TEP_EVENT_NEWLINE, &token))
			जाओ fail;
	पूर्ण
 fail:
	मुक्त_token(token);
	वापस;

 discard:
	input_buf_ptr = save_input_buf_ptr;
	input_buf_siz = save_input_buf_siz;
	*offset = 0;
	*size = 0;
	मुक्त_token(token);
पूर्ण

/**
 * tep_parse_header_page - parse the data stored in the header page
 * @tep: a handle to the trace event parser context
 * @buf: the buffer storing the header page क्रमmat string
 * @size: the size of @buf
 * @दीर्घ_size: the दीर्घ size to use अगर there is no header
 *
 * This parses the header page क्रमmat क्रम inक्रमmation on the
 * ring buffer used. The @buf should be copied from
 *
 * /sys/kernel/debug/tracing/events/header_page
 */
पूर्णांक tep_parse_header_page(काष्ठा tep_handle *tep, अक्षर *buf, अचिन्हित दीर्घ size,
			  पूर्णांक दीर्घ_size)
अणु
	पूर्णांक ignore;

	अगर (!size) अणु
		/*
		 * Old kernels did not have header page info.
		 * Sorry but we just use what we find here in user space.
		 */
		tep->header_page_ts_size = माप(दीर्घ दीर्घ);
		tep->header_page_size_size = दीर्घ_size;
		tep->header_page_data_offset = माप(दीर्घ दीर्घ) + दीर्घ_size;
		tep->old_क्रमmat = 1;
		वापस -1;
	पूर्ण
	init_input_buf(buf, size);

	parse_header_field("timestamp", &tep->header_page_ts_offset,
			   &tep->header_page_ts_size, 1);
	parse_header_field("commit", &tep->header_page_size_offset,
			   &tep->header_page_size_size, 1);
	parse_header_field("overwrite", &tep->header_page_overग_लिखो,
			   &ignore, 0);
	parse_header_field("data", &tep->header_page_data_offset,
			   &tep->header_page_data_size, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक event_matches(काष्ठा tep_event *event,
			 पूर्णांक id, स्थिर अक्षर *sys_name,
			 स्थिर अक्षर *event_name)
अणु
	अगर (id >= 0 && id != event->id)
		वापस 0;

	अगर (event_name && (म_भेद(event_name, event->name) != 0))
		वापस 0;

	अगर (sys_name && (म_भेद(sys_name, event->प्रणाली) != 0))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम मुक्त_handler(काष्ठा event_handler *handle)
अणु
	मुक्त((व्योम *)handle->sys_name);
	मुक्त((व्योम *)handle->event_name);
	मुक्त(handle);
पूर्ण

अटल पूर्णांक find_event_handle(काष्ठा tep_handle *tep, काष्ठा tep_event *event)
अणु
	काष्ठा event_handler *handle, **next;

	क्रम (next = &tep->handlers; *next;
	     next = &(*next)->next) अणु
		handle = *next;
		अगर (event_matches(event, handle->id,
				  handle->sys_name,
				  handle->event_name))
			अवरोध;
	पूर्ण

	अगर (!(*next))
		वापस 0;

	pr_stat("overriding event (%d) %s:%s with new print handler",
		event->id, event->प्रणाली, event->name);

	event->handler = handle->func;
	event->context = handle->context;

	*next = handle->next;
	मुक्त_handler(handle);

	वापस 1;
पूर्ण

/**
 * parse_क्रमmat - parse the event क्रमmat
 * @buf: the buffer storing the event क्रमmat string
 * @size: the size of @buf
 * @sys: the प्रणाली the event beदीर्घs to
 *
 * This parses the event क्रमmat and creates an event काष्ठाure
 * to quickly parse raw data क्रम a given event.
 *
 * These files currently come from:
 *
 * /sys/kernel/debug/tracing/events/.../.../क्रमmat
 */
अटल क्रमागत tep_त्रुटि_सं parse_क्रमmat(काष्ठा tep_event **eventp,
				   काष्ठा tep_handle *tep, स्थिर अक्षर *buf,
				   अचिन्हित दीर्घ size, स्थिर अक्षर *sys)
अणु
	काष्ठा tep_event *event;
	पूर्णांक ret;

	init_input_buf(buf, size);

	*eventp = event = alloc_event();
	अगर (!event)
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;

	event->name = event_पढ़ो_name();
	अगर (!event->name) अणु
		/* Bad event? */
		ret = TEP_ERRNO__MEM_ALLOC_FAILED;
		जाओ event_alloc_failed;
	पूर्ण

	अगर (म_भेद(sys, "ftrace") == 0) अणु
		event->flags |= TEP_EVENT_FL_ISFTRACE;

		अगर (म_भेद(event->name, "bprint") == 0)
			event->flags |= TEP_EVENT_FL_ISBPRINT;
	पूर्ण
		
	event->id = event_पढ़ो_id();
	अगर (event->id < 0) अणु
		ret = TEP_ERRNO__READ_ID_FAILED;
		/*
		 * This isn't an allocation error actually.
		 * But as the ID is critical, just bail out.
		 */
		जाओ event_alloc_failed;
	पूर्ण

	event->प्रणाली = strdup(sys);
	अगर (!event->प्रणाली) अणु
		ret = TEP_ERRNO__MEM_ALLOC_FAILED;
		जाओ event_alloc_failed;
	पूर्ण

	/* Add tep to event so that it can be referenced */
	event->tep = tep;

	ret = event_पढ़ो_क्रमmat(event);
	अगर (ret < 0) अणु
		ret = TEP_ERRNO__READ_FORMAT_FAILED;
		जाओ event_parse_failed;
	पूर्ण

	/*
	 * If the event has an override, करोn't prपूर्णांक warnings अगर the event
	 * prपूर्णांक क्रमmat fails to parse.
	 */
	अगर (tep && find_event_handle(tep, event))
		show_warning = 0;

	ret = event_पढ़ो_prपूर्णांक(event);
	show_warning = 1;

	अगर (ret < 0) अणु
		ret = TEP_ERRNO__READ_PRINT_FAILED;
		जाओ event_parse_failed;
	पूर्ण

	अगर (!ret && (event->flags & TEP_EVENT_FL_ISFTRACE)) अणु
		काष्ठा tep_क्रमmat_field *field;
		काष्ठा tep_prपूर्णांक_arg *arg, **list;

		/* old ftrace had no args */
		list = &event->prपूर्णांक_fmt.args;
		क्रम (field = event->क्रमmat.fields; field; field = field->next) अणु
			arg = alloc_arg();
			अगर (!arg) अणु
				event->flags |= TEP_EVENT_FL_FAILED;
				वापस TEP_ERRNO__OLD_FTRACE_ARG_FAILED;
			पूर्ण
			arg->type = TEP_PRINT_FIELD;
			arg->field.name = strdup(field->name);
			अगर (!arg->field.name) अणु
				event->flags |= TEP_EVENT_FL_FAILED;
				मुक्त_arg(arg);
				वापस TEP_ERRNO__OLD_FTRACE_ARG_FAILED;
			पूर्ण
			arg->field.field = field;
			*list = arg;
			list = &arg->next;
		पूर्ण
	पूर्ण

	अगर (!(event->flags & TEP_EVENT_FL_ISBPRINT))
		event->prपूर्णांक_fmt.prपूर्णांक_cache = parse_args(event,
							  event->prपूर्णांक_fmt.क्रमmat,
							  event->prपूर्णांक_fmt.args);

	वापस 0;

 event_parse_failed:
	event->flags |= TEP_EVENT_FL_FAILED;
	वापस ret;

 event_alloc_failed:
	मुक्त(event->प्रणाली);
	मुक्त(event->name);
	मुक्त(event);
	*eventp = शून्य;
	वापस ret;
पूर्ण

अटल क्रमागत tep_त्रुटि_सं
__parse_event(काष्ठा tep_handle *tep,
	      काष्ठा tep_event **eventp,
	      स्थिर अक्षर *buf, अचिन्हित दीर्घ size,
	      स्थिर अक्षर *sys)
अणु
	पूर्णांक ret = parse_क्रमmat(eventp, tep, buf, size, sys);
	काष्ठा tep_event *event = *eventp;

	अगर (event == शून्य)
		वापस ret;

	अगर (tep && add_event(tep, event)) अणु
		ret = TEP_ERRNO__MEM_ALLOC_FAILED;
		जाओ event_add_failed;
	पूर्ण

#घोषणा PRINT_ARGS 0
	अगर (PRINT_ARGS && event->prपूर्णांक_fmt.args)
		prपूर्णांक_args(event->prपूर्णांक_fmt.args);

	वापस 0;

event_add_failed:
	मुक्त_tep_event(event);
	वापस ret;
पूर्ण

/**
 * tep_parse_क्रमmat - parse the event क्रमmat
 * @tep: a handle to the trace event parser context
 * @eventp: वापसed क्रमmat
 * @buf: the buffer storing the event क्रमmat string
 * @size: the size of @buf
 * @sys: the प्रणाली the event beदीर्घs to
 *
 * This parses the event क्रमmat and creates an event काष्ठाure
 * to quickly parse raw data क्रम a given event.
 *
 * These files currently come from:
 *
 * /sys/kernel/debug/tracing/events/.../.../क्रमmat
 */
क्रमागत tep_त्रुटि_सं tep_parse_क्रमmat(काष्ठा tep_handle *tep,
				काष्ठा tep_event **eventp,
				स्थिर अक्षर *buf,
				अचिन्हित दीर्घ size, स्थिर अक्षर *sys)
अणु
	वापस __parse_event(tep, eventp, buf, size, sys);
पूर्ण

/**
 * tep_parse_event - parse the event क्रमmat
 * @tep: a handle to the trace event parser context
 * @buf: the buffer storing the event क्रमmat string
 * @size: the size of @buf
 * @sys: the प्रणाली the event beदीर्घs to
 *
 * This parses the event क्रमmat and creates an event काष्ठाure
 * to quickly parse raw data क्रम a given event.
 *
 * These files currently come from:
 *
 * /sys/kernel/debug/tracing/events/.../.../क्रमmat
 */
क्रमागत tep_त्रुटि_सं tep_parse_event(काष्ठा tep_handle *tep, स्थिर अक्षर *buf,
			       अचिन्हित दीर्घ size, स्थिर अक्षर *sys)
अणु
	काष्ठा tep_event *event = शून्य;
	वापस __parse_event(tep, &event, buf, size, sys);
पूर्ण

पूर्णांक get_field_val(काष्ठा trace_seq *s, काष्ठा tep_क्रमmat_field *field,
		  स्थिर अक्षर *name, काष्ठा tep_record *record,
		  अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err)
अणु
	अगर (!field) अणु
		अगर (err)
			trace_seq_म_लिखो(s, "<CANT FIND FIELD %s>", name);
		वापस -1;
	पूर्ण

	अगर (tep_पढ़ो_number_field(field, record->data, val)) अणु
		अगर (err)
			trace_seq_म_लिखो(s, " %s=INVALID", name);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tep_get_field_raw - वापस the raw poपूर्णांकer पूर्णांकo the data field
 * @s: The seq to prपूर्णांक to on error
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @len: place to store the field length.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns a poपूर्णांकer पूर्णांकo record->data of the field and places
 * the length of the field in @len.
 *
 * On failure, it वापसs शून्य.
 */
व्योम *tep_get_field_raw(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			स्थिर अक्षर *name, काष्ठा tep_record *record,
			पूर्णांक *len, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field;
	व्योम *data = record->data;
	अचिन्हित offset;
	पूर्णांक dummy;

	अगर (!event)
		वापस शून्य;

	field = tep_find_field(event, name);

	अगर (!field) अणु
		अगर (err)
			trace_seq_म_लिखो(s, "<CANT FIND FIELD %s>", name);
		वापस शून्य;
	पूर्ण

	/* Allow @len to be शून्य */
	अगर (!len)
		len = &dummy;

	offset = field->offset;
	अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
		offset = tep_पढ़ो_number(event->tep,
					 data + offset, field->size);
		*len = offset >> 16;
		offset &= 0xffff;
	पूर्ण अन्यथा
		*len = field->size;

	वापस data + offset;
पूर्ण

/**
 * tep_get_field_val - find a field and वापस its value
 * @s: The seq to prपूर्णांक to on error
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @val: place to store the value of the field.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns 0 on success -1 on field not found.
 */
पूर्णांक tep_get_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
		      स्थिर अक्षर *name, काष्ठा tep_record *record,
		      अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field;

	अगर (!event)
		वापस -1;

	field = tep_find_field(event, name);

	वापस get_field_val(s, field, name, record, val, err);
पूर्ण

/**
 * tep_get_common_field_val - find a common field and वापस its value
 * @s: The seq to prपूर्णांक to on error
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @val: place to store the value of the field.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns 0 on success -1 on field not found.
 */
पूर्णांक tep_get_common_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			     स्थिर अक्षर *name, काष्ठा tep_record *record,
			     अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field;

	अगर (!event)
		वापस -1;

	field = tep_find_common_field(event, name);

	वापस get_field_val(s, field, name, record, val, err);
पूर्ण

/**
 * tep_get_any_field_val - find a any field and वापस its value
 * @s: The seq to prपूर्णांक to on error
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @val: place to store the value of the field.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns 0 on success -1 on field not found.
 */
पूर्णांक tep_get_any_field_val(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			  स्थिर अक्षर *name, काष्ठा tep_record *record,
			  अचिन्हित दीर्घ दीर्घ *val, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field;

	अगर (!event)
		वापस -1;

	field = tep_find_any_field(event, name);

	वापस get_field_val(s, field, name, record, val, err);
पूर्ण

/**
 * tep_prपूर्णांक_num_field - prपूर्णांक a field and a क्रमmat
 * @s: The seq to prपूर्णांक to
 * @fmt: The म_लिखो क्रमmat to prपूर्णांक the field with.
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns positive value on success, negative in हाल of an error,
 * or 0 अगर buffer is full.
 */
पूर्णांक tep_prपूर्णांक_num_field(काष्ठा trace_seq *s, स्थिर अक्षर *fmt,
			काष्ठा tep_event *event, स्थिर अक्षर *name,
			काष्ठा tep_record *record, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field = tep_find_field(event, name);
	अचिन्हित दीर्घ दीर्घ val;

	अगर (!field)
		जाओ failed;

	अगर (tep_पढ़ो_number_field(field, record->data, &val))
		जाओ failed;

	वापस trace_seq_म_लिखो(s, fmt, val);

 failed:
	अगर (err)
		trace_seq_म_लिखो(s, "CAN'T FIND FIELD \"%s\"", name);
	वापस -1;
पूर्ण

/**
 * tep_prपूर्णांक_func_field - prपूर्णांक a field and a क्रमmat क्रम function poपूर्णांकers
 * @s: The seq to prपूर्णांक to
 * @fmt: The म_लिखो क्रमmat to prपूर्णांक the field with.
 * @event: the event that the field is क्रम
 * @name: The name of the field
 * @record: The record with the field name.
 * @err: prपूर्णांक शेष error अगर failed.
 *
 * Returns positive value on success, negative in हाल of an error,
 * or 0 अगर buffer is full.
 */
पूर्णांक tep_prपूर्णांक_func_field(काष्ठा trace_seq *s, स्थिर अक्षर *fmt,
			 काष्ठा tep_event *event, स्थिर अक्षर *name,
			 काष्ठा tep_record *record, पूर्णांक err)
अणु
	काष्ठा tep_क्रमmat_field *field = tep_find_field(event, name);
	काष्ठा tep_handle *tep = event->tep;
	अचिन्हित दीर्घ दीर्घ val;
	काष्ठा func_map *func;
	अक्षर पंचांगp[128];

	अगर (!field)
		जाओ failed;

	अगर (tep_पढ़ो_number_field(field, record->data, &val))
		जाओ failed;

	func = find_func(tep, val);

	अगर (func)
		snम_लिखो(पंचांगp, 128, "%s/0x%llx", func->func, func->addr - val);
	अन्यथा
		प्र_लिखो(पंचांगp, "0x%08llx", val);

	वापस trace_seq_म_लिखो(s, fmt, पंचांगp);

 failed:
	अगर (err)
		trace_seq_म_लिखो(s, "CAN'T FIND FIELD \"%s\"", name);
	वापस -1;
पूर्ण

अटल व्योम मुक्त_func_handle(काष्ठा tep_function_handler *func)
अणु
	काष्ठा func_params *params;

	मुक्त(func->name);

	जबतक (func->params) अणु
		params = func->params;
		func->params = params->next;
		मुक्त(params);
	पूर्ण

	मुक्त(func);
पूर्ण

/**
 * tep_रेजिस्टर_prपूर्णांक_function - रेजिस्टर a helper function
 * @tep: a handle to the trace event parser context
 * @func: the function to process the helper function
 * @ret_type: the वापस type of the helper function
 * @name: the name of the helper function
 * @parameters: A list of क्रमागत tep_func_arg_type
 *
 * Some events may have helper functions in the prपूर्णांक क्रमmat arguments.
 * This allows a plugin to dynamically create a way to process one
 * of these functions.
 *
 * The @parameters is a variable list of tep_func_arg_type क्रमागतs that
 * must end with TEP_FUNC_ARG_VOID.
 */
पूर्णांक tep_रेजिस्टर_prपूर्णांक_function(काष्ठा tep_handle *tep,
				tep_func_handler func,
				क्रमागत tep_func_arg_type ret_type,
				अक्षर *name, ...)
अणु
	काष्ठा tep_function_handler *func_handle;
	काष्ठा func_params **next_param;
	काष्ठा func_params *param;
	क्रमागत tep_func_arg_type type;
	बहु_सूची ap;
	पूर्णांक ret;

	func_handle = find_func_handler(tep, name);
	अगर (func_handle) अणु
		/*
		 * This is most like caused by the users own
		 * plugins updating the function. This overrides the
		 * प्रणाली शेषs.
		 */
		pr_stat("override of function helper '%s'", name);
		हटाओ_func_handler(tep, name);
	पूर्ण

	func_handle = सुस्मृति(1, माप(*func_handle));
	अगर (!func_handle) अणु
		करो_warning("Failed to allocate function handler");
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	func_handle->ret_type = ret_type;
	func_handle->name = strdup(name);
	func_handle->func = func;
	अगर (!func_handle->name) अणु
		करो_warning("Failed to allocate function name");
		मुक्त(func_handle);
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	next_param = &(func_handle->params);
	बहु_शुरू(ap, name);
	क्रम (;;) अणु
		type = बहु_तर्क(ap, क्रमागत tep_func_arg_type);
		अगर (type == TEP_FUNC_ARG_VOID)
			अवरोध;

		अगर (type >= TEP_FUNC_ARG_MAX_TYPES) अणु
			करो_warning("Invalid argument type %d", type);
			ret = TEP_ERRNO__INVALID_ARG_TYPE;
			जाओ out_मुक्त;
		पूर्ण

		param = दो_स्मृति(माप(*param));
		अगर (!param) अणु
			करो_warning("Failed to allocate function param");
			ret = TEP_ERRNO__MEM_ALLOC_FAILED;
			जाओ out_मुक्त;
		पूर्ण
		param->type = type;
		param->next = शून्य;

		*next_param = param;
		next_param = &(param->next);

		func_handle->nr_args++;
	पूर्ण
	बहु_पूर्ण(ap);

	func_handle->next = tep->func_handlers;
	tep->func_handlers = func_handle;

	वापस 0;
 out_मुक्त:
	बहु_पूर्ण(ap);
	मुक्त_func_handle(func_handle);
	वापस ret;
पूर्ण

/**
 * tep_unरेजिस्टर_prपूर्णांक_function - unरेजिस्टर a helper function
 * @tep: a handle to the trace event parser context
 * @func: the function to process the helper function
 * @name: the name of the helper function
 *
 * This function हटाओs existing prपूर्णांक handler क्रम function @name.
 *
 * Returns 0 अगर the handler was हटाओd successully, -1 otherwise.
 */
पूर्णांक tep_unरेजिस्टर_prपूर्णांक_function(काष्ठा tep_handle *tep,
				  tep_func_handler func, अक्षर *name)
अणु
	काष्ठा tep_function_handler *func_handle;

	func_handle = find_func_handler(tep, name);
	अगर (func_handle && func_handle->func == func) अणु
		हटाओ_func_handler(tep, name);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल काष्ठा tep_event *search_event(काष्ठा tep_handle *tep, पूर्णांक id,
				      स्थिर अक्षर *sys_name,
				      स्थिर अक्षर *event_name)
अणु
	काष्ठा tep_event *event;

	अगर (id >= 0) अणु
		/* search by id */
		event = tep_find_event(tep, id);
		अगर (!event)
			वापस शून्य;
		अगर (event_name && (म_भेद(event_name, event->name) != 0))
			वापस शून्य;
		अगर (sys_name && (म_भेद(sys_name, event->प्रणाली) != 0))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		event = tep_find_event_by_name(tep, sys_name, event_name);
		अगर (!event)
			वापस शून्य;
	पूर्ण
	वापस event;
पूर्ण

/**
 * tep_रेजिस्टर_event_handler - रेजिस्टर a way to parse an event
 * @tep: a handle to the trace event parser context
 * @id: the id of the event to रेजिस्टर
 * @sys_name: the प्रणाली name the event beदीर्घs to
 * @event_name: the name of the event
 * @func: the function to call to parse the event inक्रमmation
 * @context: the data to be passed to @func
 *
 * This function allows a developer to override the parsing of
 * a given event. If क्रम some reason the शेष prपूर्णांक क्रमmat
 * is not sufficient, this function will रेजिस्टर a function
 * क्रम an event to be used to parse the data instead.
 *
 * If @id is >= 0, then it is used to find the event.
 * अन्यथा @sys_name and @event_name are used.
 *
 * Returns:
 *  TEP_REGISTER_SUCCESS_OVERWRITE अगर an existing handler is overwritten
 *  TEP_REGISTER_SUCCESS अगर a new handler is रेजिस्टरed successfully
 *  negative TEP_ERRNO_... in हाल of an error
 *
 */
पूर्णांक tep_रेजिस्टर_event_handler(काष्ठा tep_handle *tep, पूर्णांक id,
			       स्थिर अक्षर *sys_name, स्थिर अक्षर *event_name,
			       tep_event_handler_func func, व्योम *context)
अणु
	काष्ठा tep_event *event;
	काष्ठा event_handler *handle;

	event = search_event(tep, id, sys_name, event_name);
	अगर (event == शून्य)
		जाओ not_found;

	pr_stat("overriding event (%d) %s:%s with new print handler",
		event->id, event->प्रणाली, event->name);

	event->handler = func;
	event->context = context;
	वापस TEP_REGISTER_SUCCESS_OVERWRITE;

 not_found:
	/* Save क्रम later use. */
	handle = सुस्मृति(1, माप(*handle));
	अगर (!handle) अणु
		करो_warning("Failed to allocate event handler");
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	handle->id = id;
	अगर (event_name)
		handle->event_name = strdup(event_name);
	अगर (sys_name)
		handle->sys_name = strdup(sys_name);

	अगर ((event_name && !handle->event_name) ||
	    (sys_name && !handle->sys_name)) अणु
		करो_warning("Failed to allocate event/sys name");
		मुक्त((व्योम *)handle->event_name);
		मुक्त((व्योम *)handle->sys_name);
		मुक्त(handle);
		वापस TEP_ERRNO__MEM_ALLOC_FAILED;
	पूर्ण

	handle->func = func;
	handle->next = tep->handlers;
	tep->handlers = handle;
	handle->context = context;

	वापस TEP_REGISTER_SUCCESS;
पूर्ण

अटल पूर्णांक handle_matches(काष्ठा event_handler *handler, पूर्णांक id,
			  स्थिर अक्षर *sys_name, स्थिर अक्षर *event_name,
			  tep_event_handler_func func, व्योम *context)
अणु
	अगर (id >= 0 && id != handler->id)
		वापस 0;

	अगर (event_name && (म_भेद(event_name, handler->event_name) != 0))
		वापस 0;

	अगर (sys_name && (म_भेद(sys_name, handler->sys_name) != 0))
		वापस 0;

	अगर (func != handler->func || context != handler->context)
		वापस 0;

	वापस 1;
पूर्ण

/**
 * tep_unरेजिस्टर_event_handler - unरेजिस्टर an existing event handler
 * @tep: a handle to the trace event parser context
 * @id: the id of the event to unरेजिस्टर
 * @sys_name: the प्रणाली name the handler beदीर्घs to
 * @event_name: the name of the event handler
 * @func: the function to call to parse the event inक्रमmation
 * @context: the data to be passed to @func
 *
 * This function हटाओs existing event handler (parser).
 *
 * If @id is >= 0, then it is used to find the event.
 * अन्यथा @sys_name and @event_name are used.
 *
 * Returns 0 अगर handler was हटाओd successfully, -1 अगर event was not found.
 */
पूर्णांक tep_unरेजिस्टर_event_handler(काष्ठा tep_handle *tep, पूर्णांक id,
				 स्थिर अक्षर *sys_name, स्थिर अक्षर *event_name,
				 tep_event_handler_func func, व्योम *context)
अणु
	काष्ठा tep_event *event;
	काष्ठा event_handler *handle;
	काष्ठा event_handler **next;

	event = search_event(tep, id, sys_name, event_name);
	अगर (event == शून्य)
		जाओ not_found;

	अगर (event->handler == func && event->context == context) अणु
		pr_stat("removing override handler for event (%d) %s:%s. Going back to default handler.",
			event->id, event->प्रणाली, event->name);

		event->handler = शून्य;
		event->context = शून्य;
		वापस 0;
	पूर्ण

not_found:
	क्रम (next = &tep->handlers; *next; next = &(*next)->next) अणु
		handle = *next;
		अगर (handle_matches(handle, id, sys_name, event_name,
				   func, context))
			अवरोध;
	पूर्ण

	अगर (!(*next))
		वापस -1;

	*next = handle->next;
	मुक्त_handler(handle);

	वापस 0;
पूर्ण

/**
 * tep_alloc - create a tep handle
 */
काष्ठा tep_handle *tep_alloc(व्योम)
अणु
	काष्ठा tep_handle *tep = सुस्मृति(1, माप(*tep));

	अगर (tep) अणु
		tep->ref_count = 1;
		tep->host_bigendian = tep_is_bigendian();
	पूर्ण

	वापस tep;
पूर्ण

व्योम tep_ref(काष्ठा tep_handle *tep)
अणु
	tep->ref_count++;
पूर्ण

पूर्णांक tep_get_ref(काष्ठा tep_handle *tep)
अणु
	अगर (tep)
		वापस tep->ref_count;
	वापस 0;
पूर्ण

__hidden व्योम मुक्त_tep_क्रमmat_field(काष्ठा tep_क्रमmat_field *field)
अणु
	मुक्त(field->type);
	अगर (field->alias != field->name)
		मुक्त(field->alias);
	मुक्त(field->name);
	मुक्त(field);
पूर्ण

अटल व्योम मुक्त_क्रमmat_fields(काष्ठा tep_क्रमmat_field *field)
अणु
	काष्ठा tep_क्रमmat_field *next;

	जबतक (field) अणु
		next = field->next;
		मुक्त_tep_क्रमmat_field(field);
		field = next;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_क्रमmats(काष्ठा tep_क्रमmat *क्रमmat)
अणु
	मुक्त_क्रमmat_fields(क्रमmat->common_fields);
	मुक्त_क्रमmat_fields(क्रमmat->fields);
पूर्ण

__hidden व्योम मुक्त_tep_event(काष्ठा tep_event *event)
अणु
	मुक्त(event->name);
	मुक्त(event->प्रणाली);

	मुक्त_क्रमmats(&event->क्रमmat);

	मुक्त(event->prपूर्णांक_fmt.क्रमmat);
	मुक्त_args(event->prपूर्णांक_fmt.args);
	मुक्त_parse_args(event->prपूर्णांक_fmt.prपूर्णांक_cache);
	मुक्त(event);
पूर्ण

/**
 * tep_मुक्त - मुक्त a tep handle
 * @tep: the tep handle to मुक्त
 */
व्योम tep_मुक्त(काष्ठा tep_handle *tep)
अणु
	काष्ठा cmdline_list *cmdlist, *cmdnext;
	काष्ठा func_list *funclist, *funcnext;
	काष्ठा prपूर्णांकk_list *prपूर्णांकklist, *prपूर्णांकknext;
	काष्ठा tep_function_handler *func_handler;
	काष्ठा event_handler *handle;
	पूर्णांक i;

	अगर (!tep)
		वापस;

	cmdlist = tep->cmdlist;
	funclist = tep->funclist;
	prपूर्णांकklist = tep->prपूर्णांकklist;

	tep->ref_count--;
	अगर (tep->ref_count)
		वापस;

	अगर (tep->cmdlines) अणु
		क्रम (i = 0; i < tep->cmdline_count; i++)
			मुक्त(tep->cmdlines[i].comm);
		मुक्त(tep->cmdlines);
	पूर्ण

	जबतक (cmdlist) अणु
		cmdnext = cmdlist->next;
		मुक्त(cmdlist->comm);
		मुक्त(cmdlist);
		cmdlist = cmdnext;
	पूर्ण

	अगर (tep->func_map) अणु
		क्रम (i = 0; i < (पूर्णांक)tep->func_count; i++) अणु
			मुक्त(tep->func_map[i].func);
			मुक्त(tep->func_map[i].mod);
		पूर्ण
		मुक्त(tep->func_map);
	पूर्ण

	जबतक (funclist) अणु
		funcnext = funclist->next;
		मुक्त(funclist->func);
		मुक्त(funclist->mod);
		मुक्त(funclist);
		funclist = funcnext;
	पूर्ण

	जबतक (tep->func_handlers) अणु
		func_handler = tep->func_handlers;
		tep->func_handlers = func_handler->next;
		मुक्त_func_handle(func_handler);
	पूर्ण

	अगर (tep->prपूर्णांकk_map) अणु
		क्रम (i = 0; i < (पूर्णांक)tep->prपूर्णांकk_count; i++)
			मुक्त(tep->prपूर्णांकk_map[i].prपूर्णांकk);
		मुक्त(tep->prपूर्णांकk_map);
	पूर्ण

	जबतक (prपूर्णांकklist) अणु
		prपूर्णांकknext = prपूर्णांकklist->next;
		मुक्त(prपूर्णांकklist->prपूर्णांकk);
		मुक्त(prपूर्णांकklist);
		prपूर्णांकklist = prपूर्णांकknext;
	पूर्ण

	क्रम (i = 0; i < tep->nr_events; i++)
		मुक्त_tep_event(tep->events[i]);

	जबतक (tep->handlers) अणु
		handle = tep->handlers;
		tep->handlers = handle->next;
		मुक्त_handler(handle);
	पूर्ण

	मुक्त(tep->events);
	मुक्त(tep->sort_events);
	मुक्त(tep->func_resolver);
	मुक्त_tep_plugin_paths(tep);

	मुक्त(tep);
पूर्ण

व्योम tep_unref(काष्ठा tep_handle *tep)
अणु
	tep_मुक्त(tep);
पूर्ण
