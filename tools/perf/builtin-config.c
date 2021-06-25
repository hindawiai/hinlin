<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-config.c
 *
 * Copyright (C) 2015, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#समावेश "builtin.h"

#समावेश "util/cache.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/debug.h"
#समावेश "util/config.h"
#समावेश <linux/माला.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

अटल bool use_प्रणाली_config, use_user_config;

अटल स्थिर अक्षर * स्थिर config_usage[] = अणु
	"perf config [<file-option>] [options] [section.name[=value] ...]",
	शून्य
पूर्ण;

क्रमागत actions अणु
	ACTION_LIST = 1
पूर्ण actions;

अटल काष्ठा option config_options[] = अणु
	OPT_SET_UINT('l', "list", &actions,
		     "show current config variables", ACTION_LIST),
	OPT_BOOLEAN(0, "system", &use_प्रणाली_config, "use system config file"),
	OPT_BOOLEAN(0, "user", &use_user_config, "use user config file"),
	OPT_END()
पूर्ण;

अटल पूर्णांक set_config(काष्ठा perf_config_set *set, स्थिर अक्षर *file_name)
अणु
	काष्ठा perf_config_section *section = शून्य;
	काष्ठा perf_config_item *item = शून्य;
	स्थिर अक्षर *first_line = "# this file is auto-generated.";
	खाता *fp;

	अगर (set == शून्य)
		वापस -1;

	fp = ख_खोलो(file_name, "w");
	अगर (!fp)
		वापस -1;

	ख_लिखो(fp, "%s\n", first_line);

	/* overग_लिखो configvariables */
	perf_config_items__क्रम_each_entry(&set->sections, section) अणु
		अगर (!use_प्रणाली_config && section->from_प्रणाली_config)
			जारी;
		ख_लिखो(fp, "[%s]\n", section->name);

		perf_config_items__क्रम_each_entry(&section->items, item) अणु
			अगर (!use_प्रणाली_config && item->from_प्रणाली_config)
				जारी;
			अगर (item->value)
				ख_लिखो(fp, "\t%s = %s\n",
					item->name, item->value);
		पूर्ण
	पूर्ण
	ख_बंद(fp);

	वापस 0;
पूर्ण

अटल पूर्णांक show_spec_config(काष्ठा perf_config_set *set, स्थिर अक्षर *var)
अणु
	काष्ठा perf_config_section *section;
	काष्ठा perf_config_item *item;

	अगर (set == शून्य)
		वापस -1;

	perf_config_items__क्रम_each_entry(&set->sections, section) अणु
		अगर (!strstarts(var, section->name))
			जारी;

		perf_config_items__क्रम_each_entry(&section->items, item) अणु
			स्थिर अक्षर *name = var + म_माप(section->name) + 1;

			अगर (म_भेद(name, item->name) == 0) अणु
				अक्षर *value = item->value;

				अगर (value) अणु
					म_लिखो("%s=%s\n", var, value);
					वापस 0;
				पूर्ण
			पूर्ण

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक show_config(काष्ठा perf_config_set *set)
अणु
	काष्ठा perf_config_section *section;
	काष्ठा perf_config_item *item;

	अगर (set == शून्य)
		वापस -1;

	perf_config_set__क्रम_each_entry(set, section, item) अणु
		अक्षर *value = item->value;

		अगर (value)
			म_लिखो("%s.%s=%s\n", section->name,
			       item->name, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_config_arg(अक्षर *arg, अक्षर **var, अक्षर **value)
अणु
	स्थिर अक्षर *last_करोt = म_अक्षर(arg, '.');

	/*
	 * Since "var" actually contains the section name and the real
	 * config variable name separated by a करोt, we have to know where the करोt is.
	 */
	अगर (last_करोt == शून्य || last_करोt == arg) अणु
		pr_err("The config variable does not contain a section name: %s\n", arg);
		वापस -1;
	पूर्ण
	अगर (!last_करोt[1]) अणु
		pr_err("The config variable does not contain a variable name: %s\n", arg);
		वापस -1;
	पूर्ण

	*value = म_अक्षर(arg, '=');
	अगर (*value == शून्य)
		*var = arg;
	अन्यथा अगर (!म_भेद(*value, "=")) अणु
		pr_err("The config variable does not contain a value: %s\n", arg);
		वापस -1;
	पूर्ण अन्यथा अणु
		*value = *value + 1; /* excluding a first अक्षरacter '=' */
		*var = strsep(&arg, "=");
		अगर (*var[0] == '\0') अणु
			pr_err("invalid config variable: %s\n", arg);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cmd_config(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i, ret = -1;
	काष्ठा perf_config_set *set;
	अक्षर *user_config = mkpath("%s/.perfconfig", दो_पर्या("HOME"));
	स्थिर अक्षर *config_filename;
	bool changed = false;

	argc = parse_options(argc, argv, config_options, config_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (use_प्रणाली_config && use_user_config) अणु
		pr_err("Error: only one config file at a time\n");
		parse_options_usage(config_usage, config_options, "user", 0);
		parse_options_usage(शून्य, config_options, "system", 0);
		वापस -1;
	पूर्ण

	अगर (use_प्रणाली_config)
		config_exclusive_filename = perf_etc_perfconfig();
	अन्यथा अगर (use_user_config)
		config_exclusive_filename = user_config;

	अगर (!config_exclusive_filename)
		config_filename = user_config;
	अन्यथा
		config_filename = config_exclusive_filename;

	/*
	 * At only 'config' sub-command, inभागidually use the config set
	 * because of reinitializing with options config file location.
	 */
	set = perf_config_set__new();
	अगर (!set)
		जाओ out_err;

	चयन (actions) अणु
	हाल ACTION_LIST:
		अगर (argc) अणु
			pr_err("Error: takes no arguments\n");
			parse_options_usage(config_usage, config_options, "l", 1);
		पूर्ण अन्यथा अणु
करो_action_list:
			अगर (show_config(set) < 0) अणु
				pr_err("Nothing configured, "
				       "please check your %s \n", config_filename);
				जाओ out_err;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अगर (!argc)
			जाओ करो_action_list;

		क्रम (i = 0; argv[i]; i++) अणु
			अक्षर *var, *value;
			अक्षर *arg = strdup(argv[i]);

			अगर (!arg) अणु
				pr_err("%s: strdup failed\n", __func__);
				जाओ out_err;
			पूर्ण

			अगर (parse_config_arg(arg, &var, &value) < 0) अणु
				मुक्त(arg);
				जाओ out_err;
			पूर्ण

			अगर (value == शून्य) अणु
				अगर (show_spec_config(set, var) < 0) अणु
					pr_err("%s is not configured: %s\n",
					       var, config_filename);
					मुक्त(arg);
					जाओ out_err;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (perf_config_set__collect(set, config_filename,
							     var, value) < 0) अणु
					pr_err("Failed to add '%s=%s'\n",
					       var, value);
					मुक्त(arg);
					जाओ out_err;
				पूर्ण
				changed = true;
			पूर्ण
			मुक्त(arg);
		पूर्ण

		अगर (!changed)
			अवरोध;

		अगर (set_config(set, config_filename) < 0) अणु
			pr_err("Failed to set the configs on %s\n",
			       config_filename);
			जाओ out_err;
		पूर्ण
	पूर्ण

	ret = 0;
out_err:
	perf_config_set__delete(set);
	वापस ret;
पूर्ण
