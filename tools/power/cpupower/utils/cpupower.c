<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  (C) 2010,2011       Thomas Renninger <trenn@suse.de>, Novell Inc.
 *
 *  Ideas taken over from the perf userspace tool (included in the Linus
 *  kernel git repo): subcommand builtins and param parsing.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/utsname.h>

#समावेश "builtin.h"
#समावेश "helpers/helpers.h"
#समावेश "helpers/bitmask.h"

#घोषणा ARRAY_SIZE(x) (माप(x)/माप(x[0]))

अटल पूर्णांक cmd_help(पूर्णांक argc, स्थिर अक्षर **argv);

/* Global cpu_info object available क्रम all binaries
 * Info only retrieved from CPU 0
 *
 * Values will be zero/unknown on non X86 archs
 */
काष्ठा cpuघातer_cpu_info cpuघातer_cpu_info;
पूर्णांक run_as_root;
पूर्णांक base_cpu;
/* Affected cpus chosen by -c/--cpu param */
काष्ठा biपंचांगask *cpus_chosen;
काष्ठा biपंचांगask *online_cpus;
काष्ठा biपंचांगask *offline_cpus;

#अगर_घोषित DEBUG
पूर्णांक be_verbose;
#पूर्ण_अगर

अटल व्योम prपूर्णांक_help(व्योम);

काष्ठा cmd_काष्ठा अणु
	स्थिर अक्षर *cmd;
	पूर्णांक (*मुख्य)(पूर्णांक, स्थिर अक्षर **);
	पूर्णांक needs_root;
पूर्ण;

अटल काष्ठा cmd_काष्ठा commands[] = अणु
	अणु "frequency-info",	cmd_freq_info,	0	पूर्ण,
	अणु "frequency-set",	cmd_freq_set,	1	पूर्ण,
	अणु "idle-info",		cmd_idle_info,	0	पूर्ण,
	अणु "idle-set",		cmd_idle_set,	1	पूर्ण,
	अणु "set",		cmd_set,	1	पूर्ण,
	अणु "info",		cmd_info,	0	पूर्ण,
	अणु "monitor",		cmd_monitor,	0	पूर्ण,
	अणु "help",		cmd_help,	0	पूर्ण,
	/*	अणु "bench",	cmd_bench,	1	पूर्ण, */
पूर्ण;

अटल व्योम prपूर्णांक_help(व्योम)
अणु
	अचिन्हित पूर्णांक i;

#अगर_घोषित DEBUG
	म_लिखो(_("Usage:\tcpupower [-d|--debug] [-c|--cpu cpulist ] <command> [<args>]\n"));
#अन्यथा
	म_लिखो(_("Usage:\tcpupower [-c|--cpu cpulist ] <command> [<args>]\n"));
#पूर्ण_अगर
	म_लिखो(_("Supported commands are:\n"));
	क्रम (i = 0; i < ARRAY_SIZE(commands); i++)
		म_लिखो("\t%s\n", commands[i].cmd);
	म_लिखो(_("\nNot all commands can make use of the -c cpulist option.\n"));
	म_लिखो(_("\nUse 'cpupower help <command>' for getting help for above commands.\n"));
पूर्ण

अटल पूर्णांक prपूर्णांक_man_page(स्थिर अक्षर *subpage)
अणु
	पूर्णांक len;
	अक्षर *page;

	len = 10; /* enough क्रम "cpupower-" */
	अगर (subpage != शून्य)
		len += म_माप(subpage);

	page = दो_स्मृति(len);
	अगर (!page)
		वापस -ENOMEM;

	प्र_लिखो(page, "cpupower");
	अगर ((subpage != शून्य) && म_भेद(subpage, "help")) अणु
		म_जोड़ो(page, "-");
		म_जोड़ो(page, subpage);
	पूर्ण

	execlp("man", "man", page, शून्य);

	/* should not be reached */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cmd_help(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अगर (argc > 1) अणु
		prपूर्णांक_man_page(argv[1]); /* निकासs within execlp() */
		वापस निकास_त्रुटि;
	पूर्ण

	prपूर्णांक_help();
	वापस निकास_सफल;
पूर्ण

अटल व्योम prपूर्णांक_version(व्योम)
अणु
	म_लिखो(PACKAGE " " VERSION "\n");
	म_लिखो(_("Report errors and bugs to %s, please.\n"), PACKAGE_BUGREPORT);
पूर्ण

अटल व्योम handle_options(पूर्णांक *argc, स्थिर अक्षर ***argv)
अणु
	पूर्णांक ret, x, new_argc = 0;

	अगर (*argc < 1)
		वापस;

	क्रम (x = 0;  x < *argc && ((*argv)[x])[0] == '-'; x++) अणु
		स्थिर अक्षर *param = (*argv)[x];
		अगर (!म_भेद(param, "-h") || !म_भेद(param, "--help")) अणु
			prपूर्णांक_help();
			निकास(निकास_सफल);
		पूर्ण अन्यथा अगर (!म_भेद(param, "-c") || !म_भेद(param, "--cpu")) अणु
			अगर (*argc < 2) अणु
				prपूर्णांक_help();
				निकास(निकास_त्रुटि);
			पूर्ण
			अगर (!म_भेद((*argv)[x+1], "all"))
				biपंचांगask_setall(cpus_chosen);
			अन्यथा अणु
				ret = biपंचांगask_parselist(
						(*argv)[x+1], cpus_chosen);
				अगर (ret < 0) अणु
					ख_लिखो(मानक_त्रुटि, _("Error parsing cpu "
							  "list\n"));
					निकास(निकास_त्रुटि);
				पूर्ण
			पूर्ण
			x += 1;
			/* Cut out param: cpuघातer -c 1 info -> cpuघातer info */
			new_argc += 2;
			जारी;
		पूर्ण अन्यथा अगर (!म_भेद(param, "-v") ||
			!म_भेद(param, "--version")) अणु
			prपूर्णांक_version();
			निकास(निकास_सफल);
#अगर_घोषित DEBUG
		पूर्ण अन्यथा अगर (!म_भेद(param, "-d") || !म_भेद(param, "--debug")) अणु
			be_verbose = 1;
			new_argc++;
			जारी;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Unknown option: %s\n", param);
			prपूर्णांक_help();
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण
	*argc -= new_argc;
	*argv += new_argc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर *argv[])
अणु
	स्थिर अक्षर *cmd;
	अचिन्हित पूर्णांक i, ret;
	काष्ठा stat statbuf;
	काष्ठा utsname uts;
	अक्षर pathname[32];

	cpus_chosen = biपंचांगask_alloc(sysconf(_SC_NPROCESSORS_CONF));
	online_cpus = biपंचांगask_alloc(sysconf(_SC_NPROCESSORS_CONF));
	offline_cpus = biपंचांगask_alloc(sysconf(_SC_NPROCESSORS_CONF));

	argc--;
	argv += 1;

	handle_options(&argc, &argv);

	cmd = argv[0];

	अगर (argc < 1) अणु
		prपूर्णांक_help();
		वापस निकास_त्रुटि;
	पूर्ण

	रखो_क्षेत्र(LC_ALL, "");
	textकरोमुख्य(PACKAGE);

	/* Turn "perf cmd --help" पूर्णांकo "perf help cmd" */
	अगर (argc > 1 && !म_भेद(argv[1], "--help")) अणु
		argv[1] = argv[0];
		argv[0] = cmd = "help";
	पूर्ण

	base_cpu = sched_अ_लोpu();
	अगर (base_cpu < 0) अणु
		ख_लिखो(मानक_त्रुटि, _("No valid cpus found.\n"));
		वापस निकास_त्रुटि;
	पूर्ण

	get_cpu_info(&cpuघातer_cpu_info);
	run_as_root = !geteuid();
	अगर (run_as_root) अणु
		ret = uname(&uts);
		प्र_लिखो(pathname, "/dev/cpu/%d/msr", base_cpu);
		अगर (!ret && !म_भेद(uts.machine, "x86_64") &&
		    stat(pathname, &statbuf) != 0) अणु
			अगर (प्रणाली("modprobe msr") == -1)
	ख_लिखो(मानक_त्रुटि, _("MSR access not available.\n"));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(commands); i++) अणु
		काष्ठा cmd_काष्ठा *p = commands + i;
		अगर (म_भेद(p->cmd, cmd))
			जारी;
		अगर (!run_as_root && p->needs_root) अणु
			ख_लिखो(मानक_त्रुटि, _("Subcommand %s needs root "
					  "privileges\n"), cmd);
			वापस निकास_त्रुटि;
		पूर्ण
		ret = p->मुख्य(argc, argv);
		अगर (cpus_chosen)
			biपंचांगask_मुक्त(cpus_chosen);
		अगर (online_cpus)
			biपंचांगask_मुक्त(online_cpus);
		अगर (offline_cpus)
			biपंचांगask_मुक्त(offline_cpus);
		वापस ret;
	पूर्ण
	prपूर्णांक_help();
	वापस निकास_त्रुटि;
पूर्ण
