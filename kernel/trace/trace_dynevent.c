<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic dynamic event control पूर्णांकerface
 *
 * Copyright (C) 2018 Masami Hiramatsu <mhiramat@kernel.org>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/tracefs.h>

#समावेश "trace.h"
#समावेश "trace_dynevent.h"

अटल DEFINE_MUTEX(dyn_event_ops_mutex);
अटल LIST_HEAD(dyn_event_ops_list);

पूर्णांक dyn_event_रेजिस्टर(काष्ठा dyn_event_operations *ops)
अणु
	अगर (!ops || !ops->create || !ops->show || !ops->is_busy ||
	    !ops->मुक्त || !ops->match)
		वापस -EINVAL;

	INIT_LIST_HEAD(&ops->list);
	mutex_lock(&dyn_event_ops_mutex);
	list_add_tail(&ops->list, &dyn_event_ops_list);
	mutex_unlock(&dyn_event_ops_mutex);
	वापस 0;
पूर्ण

पूर्णांक dyn_event_release(स्थिर अक्षर *raw_command, काष्ठा dyn_event_operations *type)
अणु
	काष्ठा dyn_event *pos, *n;
	अक्षर *प्रणाली = शून्य, *event, *p;
	पूर्णांक argc, ret = -ENOENT;
	अक्षर **argv;

	argv = argv_split(GFP_KERNEL, raw_command, &argc);
	अगर (!argv)
		वापस -ENOMEM;

	अगर (argv[0][0] == '-') अणु
		अगर (argv[0][1] != ':') अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		event = &argv[0][2];
	पूर्ण अन्यथा अणु
		event = म_अक्षर(argv[0], ':');
		अगर (!event) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		event++;
	पूर्ण

	p = म_अक्षर(event, '/');
	अगर (p) अणु
		प्रणाली = event;
		event = p + 1;
		*p = '\0';
	पूर्ण
	अगर (event[0] == '\0') अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	mutex_lock(&event_mutex);
	क्रम_each_dyn_event_safe(pos, n) अणु
		अगर (type && type != pos->ops)
			जारी;
		अगर (!pos->ops->match(प्रणाली, event,
				argc - 1, (स्थिर अक्षर **)argv + 1, pos))
			जारी;

		ret = pos->ops->मुक्त(pos);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&event_mutex);
out:
	argv_मुक्त(argv);
	वापस ret;
पूर्ण

अटल पूर्णांक create_dyn_event(स्थिर अक्षर *raw_command)
अणु
	काष्ठा dyn_event_operations *ops;
	पूर्णांक ret = -ENODEV;

	अगर (raw_command[0] == '-' || raw_command[0] == '!')
		वापस dyn_event_release(raw_command, शून्य);

	mutex_lock(&dyn_event_ops_mutex);
	list_क्रम_each_entry(ops, &dyn_event_ops_list, list) अणु
		ret = ops->create(raw_command);
		अगर (!ret || ret != -ECANCELED)
			अवरोध;
	पूर्ण
	mutex_unlock(&dyn_event_ops_mutex);
	अगर (ret == -ECANCELED)
		ret = -EINVAL;

	वापस ret;
पूर्ण

/* Protected by event_mutex */
LIST_HEAD(dyn_event_list);

व्योम *dyn_event_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&event_mutex);
	वापस seq_list_start(&dyn_event_list, *pos);
पूर्ण

व्योम *dyn_event_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &dyn_event_list, pos);
पूर्ण

व्योम dyn_event_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&event_mutex);
पूर्ण

अटल पूर्णांक dyn_event_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;

	अगर (ev && ev->ops)
		वापस ev->ops->show(m, ev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations dyn_event_seq_op = अणु
	.start	= dyn_event_seq_start,
	.next	= dyn_event_seq_next,
	.stop	= dyn_event_seq_stop,
	.show	= dyn_event_seq_show
पूर्ण;

/*
 * dyn_events_release_all - Release all specअगरic events
 * @type:	the dyn_event_operations * which filters releasing events
 *
 * This releases all events which ->ops matches @type. If @type is शून्य,
 * all events are released.
 * Return -EBUSY अगर any of them are in use, and वापस other errors when
 * it failed to मुक्त the given event. Except क्रम -EBUSY, event releasing
 * process will be पातed at that poपूर्णांक and there may be some other
 * releasable events on the list.
 */
पूर्णांक dyn_events_release_all(काष्ठा dyn_event_operations *type)
अणु
	काष्ठा dyn_event *ev, *पंचांगp;
	पूर्णांक ret = 0;

	mutex_lock(&event_mutex);
	क्रम_each_dyn_event(ev) अणु
		अगर (type && ev->ops != type)
			जारी;
		अगर (ev->ops->is_busy(ev)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण
	क्रम_each_dyn_event_safe(ev, पंचांगp) अणु
		अगर (type && ev->ops != type)
			जारी;
		ret = ev->ops->मुक्त(ev);
		अगर (ret)
			अवरोध;
	पूर्ण
out:
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक dyn_event_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = tracing_check_खोलो_get_tr(शून्य);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		ret = dyn_events_release_all(शून्य);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस seq_खोलो(file, &dyn_event_seq_op);
पूर्ण

अटल sमाप_प्रकार dyn_event_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	वापस trace_parse_run_command(file, buffer, count, ppos,
				       create_dyn_event);
पूर्ण

अटल स्थिर काष्ठा file_operations dynamic_events_ops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = dyn_event_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = seq_release,
	.ग_लिखो		= dyn_event_ग_लिखो,
पूर्ण;

/* Make a tracefs पूर्णांकerface क्रम controlling dynamic events */
अटल __init पूर्णांक init_dynamic_event(व्योम)
अणु
	काष्ठा dentry *entry;
	पूर्णांक ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	entry = tracefs_create_file("dynamic_events", 0644, शून्य,
				    शून्य, &dynamic_events_ops);

	/* Event list पूर्णांकerface */
	अगर (!entry)
		pr_warn("Could not create tracefs 'dynamic_events' entry\n");

	वापस 0;
पूर्ण
fs_initcall(init_dynamic_event);

/**
 * dynevent_arg_add - Add an arg to a dynevent_cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event cmd
 * @arg: The argument to append to the current cmd
 * @check_arg: An (optional) poपूर्णांकer to a function checking arg sanity
 *
 * Append an argument to a dynevent_cmd.  The argument string will be
 * appended to the current cmd string, followed by a separator, अगर
 * applicable.  Beक्रमe the argument is added, the @check_arg function,
 * अगर present, will be used to check the sanity of the current arg
 * string.
 *
 * The cmd string and separator should be set using the
 * dynevent_arg_init() beक्रमe any arguments are added using this
 * function.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक dynevent_arg_add(काष्ठा dynevent_cmd *cmd,
		     काष्ठा dynevent_arg *arg,
		     dynevent_check_arg_fn_t check_arg)
अणु
	पूर्णांक ret = 0;

	अगर (check_arg) अणु
		ret = check_arg(arg);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = seq_buf_म_लिखो(&cmd->seq, " %s%c", arg->str, arg->separator);
	अगर (ret) अणु
		pr_err("String is too long: %s%c\n", arg->str, arg->separator);
		वापस -E2BIG;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dynevent_arg_pair_add - Add an arg pair to a dynevent_cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event cmd
 * @arg_pair: The argument pair to append to the current cmd
 * @check_arg: An (optional) poपूर्णांकer to a function checking arg sanity
 *
 * Append an argument pair to a dynevent_cmd.  An argument pair
 * consists of a left-hand-side argument and a right-hand-side
 * argument separated by an चालक, which can be whitespace, all
 * followed by a separator, अगर applicable.  This can be used to add
 * arguments of the क्रमm 'type variable_name;' or 'x+y'.
 *
 * The lhs argument string will be appended to the current cmd string,
 * followed by an चालक, अगर applicable, followed by the rhs string,
 * followed finally by a separator, अगर applicable.  Beक्रमe the
 * argument is added, the @check_arg function, अगर present, will be
 * used to check the sanity of the current arg strings.
 *
 * The cmd strings, चालक, and separator should be set using the
 * dynevent_arg_pair_init() beक्रमe any arguments are added using this
 * function.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक dynevent_arg_pair_add(काष्ठा dynevent_cmd *cmd,
			  काष्ठा dynevent_arg_pair *arg_pair,
			  dynevent_check_arg_fn_t check_arg)
अणु
	पूर्णांक ret = 0;

	अगर (check_arg) अणु
		ret = check_arg(arg_pair);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = seq_buf_म_लिखो(&cmd->seq, " %s%c%s%c", arg_pair->lhs,
			     arg_pair->चालक, arg_pair->rhs,
			     arg_pair->separator);
	अगर (ret) अणु
		pr_err("field string is too long: %s%c%s%c\n", arg_pair->lhs,
		       arg_pair->चालक, arg_pair->rhs,
		       arg_pair->separator);
		वापस -E2BIG;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dynevent_str_add - Add a string to a dynevent_cmd
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the new event cmd
 * @str: The string to append to the current cmd
 *
 * Append a string to a dynevent_cmd.  The string will be appended to
 * the current cmd string as-is, with nothing prepended or appended.
 *
 * Return: 0 अगर successful, error otherwise.
 */
पूर्णांक dynevent_str_add(काष्ठा dynevent_cmd *cmd, स्थिर अक्षर *str)
अणु
	पूर्णांक ret = 0;

	ret = seq_buf_माला_दो(&cmd->seq, str);
	अगर (ret) अणु
		pr_err("String is too long: %s\n", str);
		वापस -E2BIG;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dynevent_cmd_init - Initialize a dynevent_cmd object
 * @cmd: A poपूर्णांकer to the dynevent_cmd काष्ठा representing the cmd
 * @buf: A poपूर्णांकer to the buffer to generate the command पूर्णांकo
 * @maxlen: The length of the buffer the command will be generated पूर्णांकo
 * @type: The type of the cmd, checked against further operations
 * @run_command: The type-specअगरic function that will actually run the command
 *
 * Initialize a dynevent_cmd.  A dynevent_cmd is used to build up and
 * run dynamic event creation commands, such as commands क्रम creating
 * synthetic and kprobe events.  Beक्रमe calling any of the functions
 * used to build the command, a dynevent_cmd object should be
 * instantiated and initialized using this function.
 *
 * The initialization sets things up by saving a poपूर्णांकer to the
 * user-supplied buffer and its length via the @buf and @maxlen
 * params, and by saving the cmd-specअगरic @type and @run_command
 * params which are used to check subsequent dynevent_cmd operations
 * and actually run the command when complete.
 */
व्योम dynevent_cmd_init(काष्ठा dynevent_cmd *cmd, अक्षर *buf, पूर्णांक maxlen,
		       क्रमागत dynevent_type type,
		       dynevent_create_fn_t run_command)
अणु
	स_रखो(cmd, '\0', माप(*cmd));

	seq_buf_init(&cmd->seq, buf, maxlen);
	cmd->type = type;
	cmd->run_command = run_command;
पूर्ण

/**
 * dynevent_arg_init - Initialize a dynevent_arg object
 * @arg: A poपूर्णांकer to the dynevent_arg काष्ठा representing the arg
 * @separator: An (optional) separator, appended after adding the arg
 *
 * Initialize a dynevent_arg object.  A dynevent_arg represents an
 * object used to append single arguments to the current command
 * string.  After the arg string is successfully appended to the
 * command string, the optional @separator is appended.  If no
 * separator was specअगरied when initializing the arg, a space will be
 * appended.
 */
व्योम dynevent_arg_init(काष्ठा dynevent_arg *arg,
		       अक्षर separator)
अणु
	स_रखो(arg, '\0', माप(*arg));

	अगर (!separator)
		separator = ' ';
	arg->separator = separator;
पूर्ण

/**
 * dynevent_arg_pair_init - Initialize a dynevent_arg_pair object
 * @arg_pair: A poपूर्णांकer to the dynevent_arg_pair काष्ठा representing the arg
 * @चालक: An (optional) चालक, appended after adding the first arg
 * @separator: An (optional) separator, appended after adding the second arg
 *
 * Initialize a dynevent_arg_pair object.  A dynevent_arg_pair
 * represents an object used to append argument pairs such as 'type
 * variable_name;' or 'x+y' to the current command string.  An
 * argument pair consists of a left-hand-side argument and a
 * right-hand-side argument separated by an चालक, which can be
 * whitespace, all followed by a separator, अगर applicable.  After the
 * first arg string is successfully appended to the command string,
 * the optional @चालक is appended, followed by the second arg and
 * optional @separator.  If no separator was specअगरied when
 * initializing the arg, a space will be appended.
 */
व्योम dynevent_arg_pair_init(काष्ठा dynevent_arg_pair *arg_pair,
			    अक्षर चालक, अक्षर separator)
अणु
	स_रखो(arg_pair, '\0', माप(*arg_pair));

	अगर (!चालक)
		चालक = ' ';
	arg_pair->चालक = चालक;

	अगर (!separator)
		separator = ' ';
	arg_pair->separator = separator;
पूर्ण

/**
 * dynevent_create - Create the dynamic event contained in dynevent_cmd
 * @cmd: The dynevent_cmd object containing the dynamic event creation command
 *
 * Once a dynevent_cmd object has been successfully built up via the
 * dynevent_cmd_init(), dynevent_arg_add() and dynevent_arg_pair_add()
 * functions, this function runs the final command to actually create
 * the event.
 *
 * Return: 0 अगर the event was successfully created, error otherwise.
 */
पूर्णांक dynevent_create(काष्ठा dynevent_cmd *cmd)
अणु
	वापस cmd->run_command(cmd);
पूर्ण
EXPORT_SYMBOL_GPL(dynevent_create);
