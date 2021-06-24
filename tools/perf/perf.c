<शैली गुरु>
/*
 * perf.c
 *
 * Perक्रमmance analysis utility.
 *
 * This is the मुख्य hub from which the sub-commands (perf stat,
 * perf top, perf record, perf report, etc.) are started.
 */
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश "util/build-id.h"
#समावेश "util/cache.h"
#समावेश "util/env.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश <subcmd/exec-cmd.h>
#समावेश "util/config.h"
#समावेश <subcmd/run-command.h>
#समावेश "util/parse-events.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/bpf-loader.h"
#समावेश "util/debug.h"
#समावेश "util/event.h"
#समावेश "util/util.h" // usage()
#समावेश "ui/ui.h"
#समावेश "perf-sys.h"
#समावेश <api/fs/fs.h>
#समावेश <api/fs/tracing_path.h>
#समावेश <perf/core.h>
#समावेश <त्रुटिसं.स>
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

स्थिर अक्षर perf_usage_string[] =
	"perf [--version] [--help] [OPTIONS] COMMAND [ARGS]";

स्थिर अक्षर perf_more_info_string[] =
	"See 'perf help COMMAND' for more information on a specific command.";

अटल पूर्णांक use_pager = -1;
स्थिर अक्षर *input_name;

काष्ठा cmd_काष्ठा अणु
	स्थिर अक्षर *cmd;
	पूर्णांक (*fn)(पूर्णांक, स्थिर अक्षर **);
	पूर्णांक option;
पूर्ण;

अटल काष्ठा cmd_काष्ठा commands[] = अणु
	अणु "buildid-cache", cmd_buildid_cache, 0 पूर्ण,
	अणु "buildid-list", cmd_buildid_list, 0 पूर्ण,
	अणु "config",	cmd_config,	0 पूर्ण,
	अणु "c2c",	cmd_c2c,	0 पूर्ण,
	अणु "diff",	cmd_dअगरf,	0 पूर्ण,
	अणु "evlist",	cmd_evlist,	0 पूर्ण,
	अणु "help",	cmd_help,	0 पूर्ण,
	अणु "kallsyms",	cmd_kallsyms,	0 पूर्ण,
	अणु "list",	cmd_list,	0 पूर्ण,
	अणु "record",	cmd_record,	0 पूर्ण,
	अणु "report",	cmd_report,	0 पूर्ण,
	अणु "bench",	cmd_bench,	0 पूर्ण,
	अणु "stat",	cmd_stat,	0 पूर्ण,
	अणु "timechart",	cmd_समयअक्षरt,	0 पूर्ण,
	अणु "top",	cmd_top,	0 पूर्ण,
	अणु "annotate",	cmd_annotate,	0 पूर्ण,
	अणु "version",	cmd_version,	0 पूर्ण,
	अणु "script",	cmd_script,	0 पूर्ण,
	अणु "sched",	cmd_sched,	0 पूर्ण,
#अगर_घोषित HAVE_LIBELF_SUPPORT
	अणु "probe",	cmd_probe,	0 पूर्ण,
#पूर्ण_अगर
	अणु "kmem",	cmd_kmem,	0 पूर्ण,
	अणु "lock",	cmd_lock,	0 पूर्ण,
	अणु "kvm",	cmd_kvm,	0 पूर्ण,
	अणु "test",	cmd_test,	0 पूर्ण,
#अगर defined(HAVE_LIBAUDIT_SUPPORT) || defined(HAVE_SYSCALL_TABLE_SUPPORT)
	अणु "trace",	cmd_trace,	0 पूर्ण,
#पूर्ण_अगर
	अणु "inject",	cmd_inject,	0 पूर्ण,
	अणु "mem",	cmd_mem,	0 पूर्ण,
	अणु "data",	cmd_data,	0 पूर्ण,
	अणु "ftrace",	cmd_ftrace,	0 पूर्ण,
	अणु "daemon",	cmd_daemon,	0 पूर्ण,
पूर्ण;

काष्ठा pager_config अणु
	स्थिर अक्षर *cmd;
	पूर्णांक val;
पूर्ण;

अटल पूर्णांक pager_command_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	काष्ठा pager_config *c = data;
	अगर (strstarts(var, "pager.") && !म_भेद(var + 6, c->cmd))
		c->val = perf_config_bool(var, value);
	वापस 0;
पूर्ण

/* वापसs 0 क्रम "no pager", 1 क्रम "use pager", and -1 क्रम "not specified" */
अटल पूर्णांक check_pager_config(स्थिर अक्षर *cmd)
अणु
	पूर्णांक err;
	काष्ठा pager_config c;
	c.cmd = cmd;
	c.val = -1;
	err = perf_config(pager_command_config, &c);
	वापस err ?: c.val;
पूर्ण

अटल पूर्णांक browser_command_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	काष्ठा pager_config *c = data;
	अगर (strstarts(var, "tui.") && !म_भेद(var + 4, c->cmd))
		c->val = perf_config_bool(var, value);
	अगर (strstarts(var, "gtk.") && !म_भेद(var + 4, c->cmd))
		c->val = perf_config_bool(var, value) ? 2 : 0;
	वापस 0;
पूर्ण

/*
 * वापसs 0 क्रम "no tui", 1 क्रम "use tui", 2 क्रम "use gtk",
 * and -1 क्रम "not specified"
 */
अटल पूर्णांक check_browser_config(स्थिर अक्षर *cmd)
अणु
	पूर्णांक err;
	काष्ठा pager_config c;
	c.cmd = cmd;
	c.val = -1;
	err = perf_config(browser_command_config, &c);
	वापस err ?: c.val;
पूर्ण

अटल व्योम commit_pager_choice(व्योम)
अणु
	चयन (use_pager) अणु
	हाल 0:
		setenv(PERF_PAGER_ENVIRONMENT, "cat", 1);
		अवरोध;
	हाल 1:
		/* setup_pager(); */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा option options[] = अणु
	OPT_ARGUMENT("help", "help"),
	OPT_ARGUMENT("version", "version"),
	OPT_ARGUMENT("exec-path", "exec-path"),
	OPT_ARGUMENT("html-path", "html-path"),
	OPT_ARGUMENT("paginate", "paginate"),
	OPT_ARGUMENT("no-pager", "no-pager"),
	OPT_ARGUMENT("debugfs-dir", "debugfs-dir"),
	OPT_ARGUMENT("buildid-dir", "buildid-dir"),
	OPT_ARGUMENT("list-cmds", "list-cmds"),
	OPT_ARGUMENT("list-opts", "list-opts"),
	OPT_ARGUMENT("debug", "debug"),
	OPT_END()
पूर्ण;

अटल पूर्णांक handle_options(स्थिर अक्षर ***argv, पूर्णांक *argc, पूर्णांक *envchanged)
अणु
	पूर्णांक handled = 0;

	जबतक (*argc > 0) अणु
		स्थिर अक्षर *cmd = (*argv)[0];
		अगर (cmd[0] != '-')
			अवरोध;

		/*
		 * For legacy reasons, the "version" and "help"
		 * commands can be written with "--" prepended
		 * to make them look like flags.
		 */
		अगर (!म_भेद(cmd, "--help") || !म_भेद(cmd, "--version"))
			अवरोध;

		/*
		 * Shortcut क्रम '-h' and '-v' options to invoke help
		 * and version command.
		 */
		अगर (!म_भेद(cmd, "-h")) अणु
			(*argv)[0] = "--help";
			अवरोध;
		पूर्ण

		अगर (!म_भेद(cmd, "-v")) अणु
			(*argv)[0] = "--version";
			अवरोध;
		पूर्ण

		अगर (!म_भेद(cmd, "-vv")) अणु
			(*argv)[0] = "version";
			version_verbose = 1;
			अवरोध;
		पूर्ण

		/*
		 * Check reमुख्यing flags.
		 */
		अगर (strstarts(cmd, CMD_EXEC_PATH)) अणु
			cmd += म_माप(CMD_EXEC_PATH);
			अगर (*cmd == '=')
				set_argv_exec_path(cmd + 1);
			अन्यथा अणु
				माला_दो(get_argv_exec_path());
				निकास(0);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--html-path")) अणु
			माला_दो(प्रणाली_path(PERF_HTML_PATH));
			निकास(0);
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "-p") || !म_भेद(cmd, "--paginate")) अणु
			use_pager = 1;
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--no-pager")) अणु
			use_pager = 0;
			अगर (envchanged)
				*envchanged = 1;
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--debugfs-dir")) अणु
			अगर (*argc < 2) अणु
				ख_लिखो(मानक_त्रुटि, "No directory given for --debugfs-dir.\n");
				usage(perf_usage_string);
			पूर्ण
			tracing_path_set((*argv)[1]);
			अगर (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--buildid-dir")) अणु
			अगर (*argc < 2) अणु
				ख_लिखो(मानक_त्रुटि, "No directory given for --buildid-dir.\n");
				usage(perf_usage_string);
			पूर्ण
			set_buildid_dir((*argv)[1]);
			अगर (envchanged)
				*envchanged = 1;
			(*argv)++;
			(*argc)--;
		पूर्ण अन्यथा अगर (strstarts(cmd, CMD_DEBUGFS_सूची)) अणु
			tracing_path_set(cmd + म_माप(CMD_DEBUGFS_सूची));
			ख_लिखो(मानक_त्रुटि, "dir: %s\n", tracing_path_mount());
			अगर (envchanged)
				*envchanged = 1;
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--list-cmds")) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(commands); i++) अणु
				काष्ठा cmd_काष्ठा *p = commands+i;
				म_लिखो("%s ", p->cmd);
			पूर्ण
			अक्षर_दो('\n');
			निकास(0);
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--list-opts")) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(options)-1; i++) अणु
				काष्ठा option *p = options+i;
				म_लिखो("--%s ", p->दीर्घ_name);
			पूर्ण
			अक्षर_दो('\n');
			निकास(0);
		पूर्ण अन्यथा अगर (!म_भेद(cmd, "--debug")) अणु
			अगर (*argc < 2) अणु
				ख_लिखो(मानक_त्रुटि, "No variable specified for --debug.\n");
				usage(perf_usage_string);
			पूर्ण
			अगर (perf_debug_option((*argv)[1]))
				usage(perf_usage_string);

			(*argv)++;
			(*argc)--;
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Unknown option: %s\n", cmd);
			usage(perf_usage_string);
		पूर्ण

		(*argv)++;
		(*argc)--;
		handled++;
	पूर्ण
	वापस handled;
पूर्ण

#घोषणा RUN_SETUP	(1<<0)
#घोषणा USE_PAGER	(1<<1)

अटल पूर्णांक run_builtin(काष्ठा cmd_काष्ठा *p, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक status;
	काष्ठा stat st;
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (use_browser == -1)
		use_browser = check_browser_config(p->cmd);

	अगर (use_pager == -1 && p->option & RUN_SETUP)
		use_pager = check_pager_config(p->cmd);
	अगर (use_pager == -1 && p->option & USE_PAGER)
		use_pager = 1;
	commit_pager_choice();

	perf_env__init(&perf_env);
	perf_env__set_cmdline(&perf_env, argc, argv);
	status = p->fn(argc, argv);
	perf_config__निकास();
	निकास_browser(status);
	perf_env__निकास(&perf_env);
	bpf__clear();

	अगर (status)
		वापस status & 0xff;

	/* Somebody बंदd मानक_निकास? */
	अगर (ख_स्थिति(fileno(मानक_निकास), &st))
		वापस 0;
	/* Ignore ग_लिखो errors क्रम pipes and sockets.. */
	अगर (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		वापस 0;

	status = 1;
	/* Check क्रम ENOSPC and EIO errors.. */
	अगर (ख_साफ(मानक_निकास)) अणु
		ख_लिखो(मानक_त्रुटि, "write failure on standard output: %s",
			str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out;
	पूर्ण
	अगर (ख_त्रुटि(मानक_निकास)) अणु
		ख_लिखो(मानक_त्रुटि, "unknown write failure on standard output");
		जाओ out;
	पूर्ण
	अगर (ख_बंद(मानक_निकास)) अणु
		ख_लिखो(मानक_त्रुटि, "close failed on standard output: %s",
			str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out;
	पूर्ण
	status = 0;
out:
	वापस status;
पूर्ण

अटल व्योम handle_पूर्णांकernal_command(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *cmd = argv[0];
	अचिन्हित पूर्णांक i;

	/* Turn "perf cmd --help" पूर्णांकo "perf help cmd" */
	अगर (argc > 1 && !म_भेद(argv[1], "--help")) अणु
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(commands); i++) अणु
		काष्ठा cmd_काष्ठा *p = commands+i;
		अगर (म_भेद(p->cmd, cmd))
			जारी;
		निकास(run_builtin(p, argc, argv));
	पूर्ण
पूर्ण

अटल व्योम execv_dashed_बाह्यal(स्थिर अक्षर **argv)
अणु
	अक्षर *cmd;
	स्थिर अक्षर *पंचांगp;
	पूर्णांक status;

	अगर (aप्र_लिखो(&cmd, "perf-%s", argv[0]) < 0)
		जाओ करो_die;

	/*
	 * argv[0] must be the perf command, but the argv array
	 * beदीर्घs to the caller, and may be reused in
	 * subsequent loop iterations. Save argv[0] and
	 * restore it on error.
	 */
	पंचांगp = argv[0];
	argv[0] = cmd;

	/*
	 * अगर we fail because the command is not found, it is
	 * OK to वापस. Otherwise, we just pass aदीर्घ the status code.
	 */
	status = run_command_v_opt(argv, 0);
	अगर (status != -ERR_RUN_COMMAND_EXEC) अणु
		अगर (IS_RUN_COMMAND_ERR(status)) अणु
करो_die:
			pr_err("FATAL: unable to run '%s'", argv[0]);
			status = -128;
		पूर्ण
		निकास(-status);
	पूर्ण
	त्रुटि_सं = ENOENT; /* as अगर we called execvp */

	argv[0] = पंचांगp;
	zमुक्त(&cmd);
पूर्ण

अटल पूर्णांक run_argv(पूर्णांक *argcp, स्थिर अक्षर ***argv)
अणु
	/* See अगर it's an पूर्णांकernal command */
	handle_पूर्णांकernal_command(*argcp, *argv);

	/* .. then try the बाह्यal ones */
	execv_dashed_बाह्यal(*argv);
	वापस 0;
पूर्ण

अटल व्योम pthपढ़ो__block_sigwinch(व्योम)
अणु
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGWINCH);
	pthपढ़ो_sigmask(SIG_BLOCK, &set, शून्य);
पूर्ण

व्योम pthपढ़ो__unblock_sigwinch(व्योम)
अणु
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGWINCH);
	pthपढ़ो_sigmask(SIG_UNBLOCK, &set, शून्य);
पूर्ण

अटल पूर्णांक libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level,
			 स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस eम_लिखो(level, verbose, fmt, ap);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक err;
	स्थिर अक्षर *cmd;
	अक्षर sbuf[STRERR_बफ_मानE];

	perf_debug_setup();

	/* libsubcmd init */
	exec_cmd_init("perf", PREFIX, PERF_EXEC_PATH, EXEC_PATH_ENVIRONMENT);
	pager_init(PERF_PAGER_ENVIRONMENT);

	libperf_init(libperf_prपूर्णांक);

	cmd = extract_argv0_path(argv[0]);
	अगर (!cmd)
		cmd = "perf-help";

	बेक्रमom(समय(शून्य));

	/* Setting $PERF_CONFIG makes perf पढ़ो _only_ the given config file. */
	config_exclusive_filename = दो_पर्या("PERF_CONFIG");

	err = perf_config(perf_शेष_config, शून्य);
	अगर (err)
		वापस err;
	set_buildid_dir(शून्य);

	/*
	 * "perf-xxxx" is the same as "perf xxxx", but we obviously:
	 *
	 *  - cannot take flags in between the "perf" and the "xxxx".
	 *  - cannot execute it बाह्यally (since it would just करो
	 *    the same thing over again)
	 *
	 * So we just directly call the पूर्णांकernal command handler. If that one
	 * fails to handle this, then maybe we just run a नामd perf binary
	 * that contains a dash in its name. To handle this scenario, we just
	 * fall through and ignore the "xxxx" part of the command string.
	 */
	अगर (strstarts(cmd, "perf-")) अणु
		cmd += 5;
		argv[0] = cmd;
		handle_पूर्णांकernal_command(argc, argv);
		/*
		 * If the command is handled, the above function करोes not
		 * वापस unकरो changes and fall through in such a हाल.
		 */
		cmd -= 5;
		argv[0] = cmd;
	पूर्ण
	अगर (strstarts(cmd, "trace")) अणु
#अगर defined(HAVE_LIBAUDIT_SUPPORT) || defined(HAVE_SYSCALL_TABLE_SUPPORT)
		setup_path();
		argv[0] = "trace";
		वापस cmd_trace(argc, argv);
#अन्यथा
		ख_लिखो(मानक_त्रुटि,
			"trace command not available: missing audit-libs devel package at build time.\n");
		जाओ out;
#पूर्ण_अगर
	पूर्ण
	/* Look क्रम flags.. */
	argv++;
	argc--;
	handle_options(&argv, &argc, शून्य);
	commit_pager_choice();

	अगर (argc > 0) अणु
		अगर (strstarts(argv[0], "--"))
			argv[0] += 2;
	पूर्ण अन्यथा अणु
		/* The user didn't specअगरy a command; give them help */
		म_लिखो("\n usage: %s\n\n", perf_usage_string);
		list_common_cmds_help();
		म_लिखो("\n %s\n\n", perf_more_info_string);
		जाओ out;
	पूर्ण
	cmd = argv[0];

	test_attr__init();

	/*
	 * We use PATH to find perf commands, but we prepend some higher
	 * precedence paths: the "--exec-path" option, the PERF_EXEC_PATH
	 * environment, and the $(perfexecdir) from the Makefile at build
	 * समय.
	 */
	setup_path();
	/*
	 * Block SIGWINCH notअगरications so that the thपढ़ो that wants it can
	 * unblock and get syscalls like select पूर्णांकerrupted instead of रुकोing
	 * क्रमever जबतक the संकेत goes to some other non पूर्णांकerested thपढ़ो.
	 */
	pthपढ़ो__block_sigwinch();

	जबतक (1) अणु
		अटल पूर्णांक करोne_help;

		run_argv(&argc, &argv);

		अगर (त्रुटि_सं != ENOENT)
			अवरोध;

		अगर (!करोne_help) अणु
			cmd = argv[0] = help_unknown_cmd(cmd);
			करोne_help = 1;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Failed to run command '%s': %s\n",
		cmd, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
out:
	वापस 1;
पूर्ण
