<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009, 2010 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */

#समावेश <प्रकार.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <dlfcn.h>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश "event-parse.h"
#समावेश "event-parse-local.h"
#समावेश "event-utils.h"
#समावेश "trace-seq.h"

#घोषणा LOCAL_PLUGIN_सूची ".local/lib/traceevent/plugins/"

अटल काष्ठा रेजिस्टरed_plugin_options अणु
	काष्ठा रेजिस्टरed_plugin_options	*next;
	काष्ठा tep_plugin_option		*options;
पूर्ण *रेजिस्टरed_options;

अटल काष्ठा trace_plugin_options अणु
	काष्ठा trace_plugin_options	*next;
	अक्षर				*plugin;
	अक्षर				*option;
	अक्षर				*value;
पूर्ण *trace_plugin_options;

काष्ठा tep_plugin_list अणु
	काष्ठा tep_plugin_list	*next;
	अक्षर			*name;
	व्योम			*handle;
पूर्ण;

काष्ठा tep_plugins_dir अणु
	काष्ठा tep_plugins_dir		*next;
	अक्षर				*path;
	क्रमागत tep_plugin_load_priority	prio;
पूर्ण;

अटल व्योम lower_हाल(अक्षर *str)
अणु
	अगर (!str)
		वापस;
	क्रम (; *str; str++)
		*str = छोटे(*str);
पूर्ण

अटल पूर्णांक update_option_value(काष्ठा tep_plugin_option *op, स्थिर अक्षर *val)
अणु
	अक्षर *op_val;

	अगर (!val) अणु
		/* toggle, only अगर option is boolean */
		अगर (op->value)
			/* Warn? */
			वापस 0;
		op->set ^= 1;
		वापस 0;
	पूर्ण

	/*
	 * If the option has a value then it takes a string
	 * otherwise the option is a boolean.
	 */
	अगर (op->value) अणु
		op->value = val;
		वापस 0;
	पूर्ण

	/* Option is boolean, must be either "1", "0", "true" or "false" */

	op_val = strdup(val);
	अगर (!op_val)
		वापस -1;
	lower_हाल(op_val);

	अगर (म_भेद(val, "1") == 0 || म_भेद(val, "true") == 0)
		op->set = 1;
	अन्यथा अगर (म_भेद(val, "0") == 0 || म_भेद(val, "false") == 0)
		op->set = 0;
	मुक्त(op_val);

	वापस 0;
पूर्ण

/**
 * tep_plugin_list_options - get list of plugin options
 *
 * Returns an array of अक्षर strings that list the currently रेजिस्टरed
 * plugin options in the क्रमmat of <plugin>:<option>. This list can be
 * used by toggling the option.
 *
 * Returns शून्य अगर there's no options रेजिस्टरed. On error it वापसs
 * INVALID_PLUGIN_LIST_OPTION
 *
 * Must be मुक्तd with tep_plugin_मुक्त_options_list().
 */
अक्षर **tep_plugin_list_options(व्योम)
अणु
	काष्ठा रेजिस्टरed_plugin_options *reg;
	काष्ठा tep_plugin_option *op;
	अक्षर **list = शून्य;
	अक्षर *name;
	पूर्णांक count = 0;

	क्रम (reg = रेजिस्टरed_options; reg; reg = reg->next) अणु
		क्रम (op = reg->options; op->name; op++) अणु
			अक्षर *alias = op->plugin_alias ? op->plugin_alias : op->file;
			अक्षर **temp = list;
			पूर्णांक ret;

			ret = aप्र_लिखो(&name, "%s:%s", alias, op->name);
			अगर (ret < 0)
				जाओ err;

			list = पुनः_स्मृति(list, count + 2);
			अगर (!list) अणु
				list = temp;
				मुक्त(name);
				जाओ err;
			पूर्ण
			list[count++] = name;
			list[count] = शून्य;
		पूर्ण
	पूर्ण
	वापस list;

 err:
	जबतक (--count >= 0)
		मुक्त(list[count]);
	मुक्त(list);

	वापस INVALID_PLUGIN_LIST_OPTION;
पूर्ण

व्योम tep_plugin_मुक्त_options_list(अक्षर **list)
अणु
	पूर्णांक i;

	अगर (!list)
		वापस;

	अगर (list == INVALID_PLUGIN_LIST_OPTION)
		वापस;

	क्रम (i = 0; list[i]; i++)
		मुक्त(list[i]);

	मुक्त(list);
पूर्ण

अटल पूर्णांक
update_option(स्थिर अक्षर *file, काष्ठा tep_plugin_option *option)
अणु
	काष्ठा trace_plugin_options *op;
	अक्षर *plugin;
	पूर्णांक ret = 0;

	अगर (option->plugin_alias) अणु
		plugin = strdup(option->plugin_alias);
		अगर (!plugin)
			वापस -1;
	पूर्ण अन्यथा अणु
		अक्षर *p;
		plugin = strdup(file);
		अगर (!plugin)
			वापस -1;
		p = म_माला(plugin, ".");
		अगर (p)
			*p = '\0';
	पूर्ण

	/* first look क्रम named options */
	क्रम (op = trace_plugin_options; op; op = op->next) अणु
		अगर (!op->plugin)
			जारी;
		अगर (म_भेद(op->plugin, plugin) != 0)
			जारी;
		अगर (म_भेद(op->option, option->name) != 0)
			जारी;

		ret = update_option_value(option, op->value);
		अगर (ret)
			जाओ out;
		अवरोध;
	पूर्ण

	/* first look क्रम unnamed options */
	क्रम (op = trace_plugin_options; op; op = op->next) अणु
		अगर (op->plugin)
			जारी;
		अगर (म_भेद(op->option, option->name) != 0)
			जारी;

		ret = update_option_value(option, op->value);
		अवरोध;
	पूर्ण

 out:
	मुक्त(plugin);
	वापस ret;
पूर्ण

/**
 * tep_plugin_add_options - Add a set of options by a plugin
 * @name: The name of the plugin adding the options
 * @options: The set of options being loaded
 *
 * Sets the options with the values that have been added by user.
 */
पूर्णांक tep_plugin_add_options(स्थिर अक्षर *name,
			   काष्ठा tep_plugin_option *options)
अणु
	काष्ठा रेजिस्टरed_plugin_options *reg;

	reg = दो_स्मृति(माप(*reg));
	अगर (!reg)
		वापस -1;
	reg->next = रेजिस्टरed_options;
	reg->options = options;
	रेजिस्टरed_options = reg;

	जबतक (options->name) अणु
		update_option(name, options);
		options++;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * tep_plugin_हटाओ_options - हटाओ plugin options that were रेजिस्टरed
 * @options: Options to हटाओd that were रेजिस्टरed with tep_plugin_add_options
 */
व्योम tep_plugin_हटाओ_options(काष्ठा tep_plugin_option *options)
अणु
	काष्ठा रेजिस्टरed_plugin_options **last;
	काष्ठा रेजिस्टरed_plugin_options *reg;

	क्रम (last = &रेजिस्टरed_options; *last; last = &(*last)->next) अणु
		अगर ((*last)->options == options) अणु
			reg = *last;
			*last = reg->next;
			मुक्त(reg);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक parse_option_name(अक्षर **option, अक्षर **plugin)
अणु
	अक्षर *p;

	*plugin = शून्य;

	अगर ((p = म_माला(*option, ":"))) अणु
		*plugin = *option;
		*p = '\0';
		*option = strdup(p + 1);
		अगर (!*option)
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा tep_plugin_option *
find_रेजिस्टरed_option(स्थिर अक्षर *plugin, स्थिर अक्षर *option)
अणु
	काष्ठा रेजिस्टरed_plugin_options *reg;
	काष्ठा tep_plugin_option *op;
	स्थिर अक्षर *op_plugin;

	क्रम (reg = रेजिस्टरed_options; reg; reg = reg->next) अणु
		क्रम (op = reg->options; op->name; op++) अणु
			अगर (op->plugin_alias)
				op_plugin = op->plugin_alias;
			अन्यथा
				op_plugin = op->file;

			अगर (plugin && म_भेद(plugin, op_plugin) != 0)
				जारी;
			अगर (म_भेद(option, op->name) != 0)
				जारी;

			वापस op;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक process_option(स्थिर अक्षर *plugin, स्थिर अक्षर *option, स्थिर अक्षर *val)
अणु
	काष्ठा tep_plugin_option *op;

	op = find_रेजिस्टरed_option(plugin, option);
	अगर (!op)
		वापस 0;

	वापस update_option_value(op, val);
पूर्ण

/**
 * tep_plugin_add_option - add an option/val pair to set plugin options
 * @name: The name of the option (क्रमmat: <plugin>:<option> or just <option>)
 * @val: (optional) the value क्रम the option
 *
 * Modअगरy a plugin option. If @val is given than the value of the option
 * is set (note, some options just take a boolean, so @val must be either
 * "1" or "0" or "true" or "false").
 */
पूर्णांक tep_plugin_add_option(स्थिर अक्षर *name, स्थिर अक्षर *val)
अणु
	काष्ठा trace_plugin_options *op;
	अक्षर *option_str;
	अक्षर *plugin;

	option_str = strdup(name);
	अगर (!option_str)
		वापस -ENOMEM;

	अगर (parse_option_name(&option_str, &plugin) < 0)
		वापस -ENOMEM;

	/* If the option exists, update the val */
	क्रम (op = trace_plugin_options; op; op = op->next) अणु
		/* Both must be शून्य or not शून्य */
		अगर ((!plugin || !op->plugin) && plugin != op->plugin)
			जारी;
		अगर (plugin && म_भेद(plugin, op->plugin) != 0)
			जारी;
		अगर (म_भेद(op->option, option_str) != 0)
			जारी;

		/* update option */
		मुक्त(op->value);
		अगर (val) अणु
			op->value = strdup(val);
			अगर (!op->value)
				जाओ out_मुक्त;
		पूर्ण अन्यथा
			op->value = शून्य;

		/* plugin and option_str करोn't get मुक्तd at the end */
		मुक्त(plugin);
		मुक्त(option_str);

		plugin = op->plugin;
		option_str = op->option;
		अवरोध;
	पूर्ण

	/* If not found, create */
	अगर (!op) अणु
		op = दो_स्मृति(माप(*op));
		अगर (!op)
			जाओ out_मुक्त;
		स_रखो(op, 0, माप(*op));
		op->plugin = plugin;
		op->option = option_str;
		अगर (val) अणु
			op->value = strdup(val);
			अगर (!op->value) अणु
				मुक्त(op);
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		op->next = trace_plugin_options;
		trace_plugin_options = op;
	पूर्ण

	वापस process_option(plugin, option_str, val);

out_मुक्त:
	मुक्त(plugin);
	मुक्त(option_str);
	वापस -ENOMEM;
पूर्ण

अटल व्योम prपूर्णांक_op_data(काष्ठा trace_seq *s, स्थिर अक्षर *name,
			  स्थिर अक्षर *op)
अणु
	अगर (op)
		trace_seq_म_लिखो(s, "%8s:\t%s\n", name, op);
पूर्ण

/**
 * tep_plugin_prपूर्णांक_options - prपूर्णांक out the रेजिस्टरed plugin options
 * @s: The trace_seq descriptor to ग_लिखो the plugin options पूर्णांकo
 *
 * Writes a list of options पूर्णांकo trace_seq @s.
 */
व्योम tep_plugin_prपूर्णांक_options(काष्ठा trace_seq *s)
अणु
	काष्ठा रेजिस्टरed_plugin_options *reg;
	काष्ठा tep_plugin_option *op;

	क्रम (reg = रेजिस्टरed_options; reg; reg = reg->next) अणु
		अगर (reg != रेजिस्टरed_options)
			trace_seq_म_लिखो(s, "============\n");
		क्रम (op = reg->options; op->name; op++) अणु
			अगर (op != reg->options)
				trace_seq_म_लिखो(s, "------------\n");
			prपूर्णांक_op_data(s, "file", op->file);
			prपूर्णांक_op_data(s, "plugin", op->plugin_alias);
			prपूर्णांक_op_data(s, "option", op->name);
			prपूर्णांक_op_data(s, "desc", op->description);
			prपूर्णांक_op_data(s, "value", op->value);
			trace_seq_म_लिखो(s, "%8s:\t%d\n", "set", op->set);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * tep_prपूर्णांक_plugins - prपूर्णांक out the list of plugins loaded
 * @s: the trace_seq descripter to ग_लिखो to
 * @prefix: The prefix string to add beक्रमe listing the option name
 * @suffix: The suffix string ot append after the option name
 * @list: The list of plugins (usually वापसed by tep_load_plugins()
 *
 * Writes to the trace_seq @s the list of plugins (files) that is
 * वापसed by tep_load_plugins(). Use @prefix and @suffix क्रम क्रमmating:
 * @prefix = "  ", @suffix = "\n".
 */
व्योम tep_prपूर्णांक_plugins(काष्ठा trace_seq *s,
		       स्थिर अक्षर *prefix, स्थिर अक्षर *suffix,
		       स्थिर काष्ठा tep_plugin_list *list)
अणु
	जबतक (list) अणु
		trace_seq_म_लिखो(s, "%s%s%s", prefix, list->name, suffix);
		list = list->next;
	पूर्ण
पूर्ण

अटल व्योम
load_plugin(काष्ठा tep_handle *tep, स्थिर अक्षर *path,
	    स्थिर अक्षर *file, व्योम *data)
अणु
	काष्ठा tep_plugin_list **plugin_list = data;
	काष्ठा tep_plugin_option *options;
	tep_plugin_load_func func;
	काष्ठा tep_plugin_list *list;
	स्थिर अक्षर *alias;
	अक्षर *plugin;
	व्योम *handle;
	पूर्णांक ret;

	ret = aप्र_लिखो(&plugin, "%s/%s", path, file);
	अगर (ret < 0) अणु
		warning("could not allocate plugin memory\n");
		वापस;
	पूर्ण

	handle = dlखोलो(plugin, RTLD_NOW | RTLD_GLOBAL);
	अगर (!handle) अणु
		warning("could not load plugin '%s'\n%s\n",
			plugin, dlerror());
		जाओ out_मुक्त;
	पूर्ण

	alias = dlsym(handle, TEP_PLUGIN_ALIAS_NAME);
	अगर (!alias)
		alias = file;

	options = dlsym(handle, TEP_PLUGIN_OPTIONS_NAME);
	अगर (options) अणु
		जबतक (options->name) अणु
			ret = update_option(alias, options);
			अगर (ret < 0)
				जाओ out_मुक्त;
			options++;
		पूर्ण
	पूर्ण

	func = dlsym(handle, TEP_PLUGIN_LOADER_NAME);
	अगर (!func) अणु
		warning("could not find func '%s' in plugin '%s'\n%s\n",
			TEP_PLUGIN_LOADER_NAME, plugin, dlerror());
		जाओ out_मुक्त;
	पूर्ण

	list = दो_स्मृति(माप(*list));
	अगर (!list) अणु
		warning("could not allocate plugin memory\n");
		जाओ out_मुक्त;
	पूर्ण

	list->next = *plugin_list;
	list->handle = handle;
	list->name = plugin;
	*plugin_list = list;

	pr_stat("registering plugin: %s", plugin);
	func(tep);
	वापस;

 out_मुक्त:
	मुक्त(plugin);
पूर्ण

अटल व्योम
load_plugins_dir(काष्ठा tep_handle *tep, स्थिर अक्षर *suffix,
		 स्थिर अक्षर *path,
		 व्योम (*load_plugin)(काष्ठा tep_handle *tep,
				     स्थिर अक्षर *path,
				     स्थिर अक्षर *name,
				     व्योम *data),
		 व्योम *data)
अणु
	काष्ठा dirent *dent;
	काष्ठा stat st;
	सूची *dir;
	पूर्णांक ret;

	ret = stat(path, &st);
	अगर (ret < 0)
		वापस;

	अगर (!S_ISसूची(st.st_mode))
		वापस;

	dir = सूची_खोलो(path);
	अगर (!dir)
		वापस;

	जबतक ((dent = सूची_पढ़ो(dir))) अणु
		स्थिर अक्षर *name = dent->d_name;

		अगर (म_भेद(name, ".") == 0 ||
		    म_भेद(name, "..") == 0)
			जारी;

		/* Only load plugins that end in suffix */
		अगर (म_भेद(name + (म_माप(name) - म_माप(suffix)), suffix) != 0)
			जारी;

		load_plugin(tep, path, name, data);
	पूर्ण

	बंद_सूची(dir);
पूर्ण

/**
 * tep_load_plugins_hook - call a user specअगरied callback to load a plugin
 * @tep: handler to traceevent context
 * @suffix: filter only plugin files with given suffix
 * @load_plugin: user specअगरied callback, called क्रम each plugin file
 * @data: custom context, passed to @load_plugin
 *
 * Searches क्रम traceevent plugin files and calls @load_plugin क्रम each
 * The order of plugins search is:
 *  - Directories, specअगरied in @tep->plugins_dir and priority TEP_PLUGIN_FIRST
 *  - Directory, specअगरied at compile समय with PLUGIN_TRACEEVENT_सूची
 *  - Directory, specअगरied by environment variable TRACEEVENT_PLUGIN_सूची
 *  - In user's home: ~/.local/lib/traceevent/plugins/
 *  - Directories, specअगरied in @tep->plugins_dir and priority TEP_PLUGIN_LAST
 *
 */
व्योम tep_load_plugins_hook(काष्ठा tep_handle *tep, स्थिर अक्षर *suffix,
			   व्योम (*load_plugin)(काष्ठा tep_handle *tep,
					       स्थिर अक्षर *path,
					       स्थिर अक्षर *name,
					       व्योम *data),
			   व्योम *data)
अणु
	काष्ठा tep_plugins_dir *dir = शून्य;
	अक्षर *home;
	अक्षर *path;
	अक्षर *envdir;
	पूर्णांक ret;

	अगर (tep && tep->flags & TEP_DISABLE_PLUGINS)
		वापस;

	अगर (tep)
		dir = tep->plugins_dir;
	जबतक (dir) अणु
		अगर (dir->prio == TEP_PLUGIN_FIRST)
			load_plugins_dir(tep, suffix, dir->path,
					 load_plugin, data);
		dir = dir->next;
	पूर्ण

	/*
	 * If a प्रणाली plugin directory was defined,
	 * check that first.
	 */
#अगर_घोषित PLUGIN_सूची
	अगर (!tep || !(tep->flags & TEP_DISABLE_SYS_PLUGINS))
		load_plugins_dir(tep, suffix, PLUGIN_सूची,
				 load_plugin, data);
#पूर्ण_अगर

	/*
	 * Next let the environment-set plugin directory
	 * override the प्रणाली शेषs.
	 */
	envdir = दो_पर्या("TRACEEVENT_PLUGIN_DIR");
	अगर (envdir)
		load_plugins_dir(tep, suffix, envdir, load_plugin, data);

	/*
	 * Now let the home directory override the environment
	 * or प्रणाली शेषs.
	 */
	home = दो_पर्या("HOME");
	अगर (!home)
		वापस;

	ret = aप्र_लिखो(&path, "%s/%s", home, LOCAL_PLUGIN_सूची);
	अगर (ret < 0) अणु
		warning("could not allocate plugin memory\n");
		वापस;
	पूर्ण

	load_plugins_dir(tep, suffix, path, load_plugin, data);

	अगर (tep)
		dir = tep->plugins_dir;
	जबतक (dir) अणु
		अगर (dir->prio == TEP_PLUGIN_LAST)
			load_plugins_dir(tep, suffix, dir->path,
					 load_plugin, data);
		dir = dir->next;
	पूर्ण

	मुक्त(path);
पूर्ण

काष्ठा tep_plugin_list*
tep_load_plugins(काष्ठा tep_handle *tep)
अणु
	काष्ठा tep_plugin_list *list = शून्य;

	tep_load_plugins_hook(tep, ".so", load_plugin, &list);
	वापस list;
पूर्ण

/**
 * tep_add_plugin_path - Add a new plugin directory.
 * @tep: Trace event handler.
 * @path: Path to a directory. All plugin files in that
 *	  directory will be loaded.
 *@prio: Load priority of the plugins in that directory.
 *
 * Returns -1 in हाल of an error, 0 otherwise.
 */
पूर्णांक tep_add_plugin_path(काष्ठा tep_handle *tep, अक्षर *path,
			क्रमागत tep_plugin_load_priority prio)
अणु
	काष्ठा tep_plugins_dir *dir;

	अगर (!tep || !path)
		वापस -1;

	dir = सुस्मृति(1, माप(*dir));
	अगर (!dir)
		वापस -1;

	dir->path = strdup(path);
	अगर (!dir->path) अणु
		मुक्त(dir);
		वापस -1;
	पूर्ण
	dir->prio = prio;
	dir->next = tep->plugins_dir;
	tep->plugins_dir = dir;

	वापस 0;
पूर्ण

__hidden व्योम मुक्त_tep_plugin_paths(काष्ठा tep_handle *tep)
अणु
	काष्ठा tep_plugins_dir *dir;

	अगर (!tep)
		वापस;

	dir = tep->plugins_dir;
	जबतक (dir) अणु
		tep->plugins_dir = tep->plugins_dir->next;
		मुक्त(dir->path);
		मुक्त(dir);
		dir = tep->plugins_dir;
	पूर्ण
पूर्ण

व्योम
tep_unload_plugins(काष्ठा tep_plugin_list *plugin_list, काष्ठा tep_handle *tep)
अणु
	tep_plugin_unload_func func;
	काष्ठा tep_plugin_list *list;

	जबतक (plugin_list) अणु
		list = plugin_list;
		plugin_list = list->next;
		func = dlsym(list->handle, TEP_PLUGIN_UNLOADER_NAME);
		अगर (func)
			func(tep);
		dlबंद(list->handle);
		मुक्त(list->name);
		मुक्त(list);
	पूर्ण
पूर्ण
