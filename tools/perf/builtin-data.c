<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "debug.h"
#समावेश <subcmd/parse-options.h>
#समावेश "data-convert.h"

प्रकार पूर्णांक (*data_cmd_fn_t)(पूर्णांक argc, स्थिर अक्षर **argv);

काष्ठा data_cmd अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*summary;
	data_cmd_fn_t	fn;
पूर्ण;

अटल काष्ठा data_cmd data_cmds[];

#घोषणा क्रम_each_cmd(cmd) \
	क्रम (cmd = data_cmds; cmd && cmd->name; cmd++)

अटल स्थिर काष्ठा option data_options[] = अणु
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर data_subcommands[] = अणु "convert", शून्य पूर्ण;

अटल स्थिर अक्षर *data_usage[] = अणु
	"perf data [<common options>] <command> [<options>]",
	शून्य
पूर्ण;

अटल व्योम prपूर्णांक_usage(व्योम)
अणु
	काष्ठा data_cmd *cmd;

	म_लिखो("Usage:\n");
	म_लिखो("\t%s\n\n", data_usage[0]);
	म_लिखो("\tAvailable commands:\n");

	क्रम_each_cmd(cmd) अणु
		म_लिखो("\t %s\t- %s\n", cmd->name, cmd->summary);
	पूर्ण

	म_लिखो("\n");
पूर्ण

अटल स्थिर अक्षर * स्थिर data_convert_usage[] = अणु
	"perf data convert [<options>]",
	शून्य
पूर्ण;

अटल पूर्णांक cmd_data_convert(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *to_json = शून्य;
	स्थिर अक्षर *to_ctf = शून्य;
	काष्ठा perf_data_convert_opts opts = अणु
		.क्रमce = false,
		.all = false,
	पूर्ण;
	स्थिर काष्ठा option options[] = अणु
		OPT_INCR('v', "verbose", &verbose, "be more verbose"),
		OPT_STRING('i', "input", &input_name, "file", "input file name"),
		OPT_STRING(0, "to-json", &to_json, शून्य, "Convert to JSON format"),
#अगर_घोषित HAVE_LIBBABELTRACE_SUPPORT
		OPT_STRING(0, "to-ctf", &to_ctf, शून्य, "Convert to CTF format"),
		OPT_BOOLEAN(0, "tod", &opts.tod, "Convert time to wall clock time"),
#पूर्ण_अगर
		OPT_BOOLEAN('f', "force", &opts.force, "don't complain, करो it"),
		OPT_BOOLEAN(0, "all", &opts.all, "Convert all events"),
		OPT_END()
	पूर्ण;

	argc = parse_options(argc, argv, options,
			     data_convert_usage, 0);
	अगर (argc) अणु
		usage_with_options(data_convert_usage, options);
		वापस -1;
	पूर्ण

	अगर (to_json && to_ctf) अणु
		pr_err("You cannot specify both --to-ctf and --to-json.\n");
		वापस -1;
	पूर्ण
	अगर (!to_json && !to_ctf) अणु
		pr_err("You must specify one of --to-ctf or --to-json.\n");
		वापस -1;
	पूर्ण

	अगर (to_json)
		वापस bt_convert__perf2json(input_name, to_json, &opts);

	अगर (to_ctf) अणु
#अगर_घोषित HAVE_LIBBABELTRACE_SUPPORT
		वापस bt_convert__perf2ctf(input_name, to_ctf, &opts);
#अन्यथा
		pr_err("The libbabeltrace support is not compiled in. perf should be "
		       "compiled with environment variables LIBBABELTRACE=1 and "
		       "LIBBABELTRACE_DIR=/path/to/libbabeltrace/\n");
		वापस -1;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा data_cmd data_cmds[] = अणु
	अणु "convert", "converts data file between formats", cmd_data_convert पूर्ण,
	अणु .name = शून्य, पूर्ण,
पूर्ण;

पूर्णांक cmd_data(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा data_cmd *cmd;
	स्थिर अक्षर *cmdstr;

	/* No command specअगरied. */
	अगर (argc < 2)
		जाओ usage;

	argc = parse_options_subcommand(argc, argv, data_options, data_subcommands, data_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (argc < 1)
		जाओ usage;

	cmdstr = argv[0];

	क्रम_each_cmd(cmd) अणु
		अगर (म_भेद(cmd->name, cmdstr))
			जारी;

		वापस cmd->fn(argc, argv);
	पूर्ण

	pr_err("Unknown command: %s\n", cmdstr);
usage:
	prपूर्णांक_usage();
	वापस -1;
पूर्ण
