<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * builtin-probe.c
 *
 * Builtin probe command: Set up probe events by C expression
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */
#समावेश <sys/utsname.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "builtin.h"
#समावेश "namespaces.h"
#समावेश "util/build-id.h"
#समावेश "util/strlist.h"
#समावेश "util/strfilter.h"
#समावेश "util/symbol_conf.h"
#समावेश "util/debug.h"
#समावेश <subcmd/parse-options.h>
#समावेश "util/probe-finder.h"
#समावेश "util/probe-event.h"
#समावेश "util/probe-file.h"
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

#घोषणा DEFAULT_VAR_FILTER "!__k???tab_* & !__crc_*"
#घोषणा DEFAULT_FUNC_FILTER "!_*"
#घोषणा DEFAULT_LIST_FILTER "*"

/* Session management काष्ठाure */
अटल काष्ठा अणु
	पूर्णांक command;	/* Command लघु_name */
	bool list_events;
	bool uprobes;
	bool quiet;
	bool target_used;
	पूर्णांक nevents;
	काष्ठा perf_probe_event events[MAX_PROBES];
	काष्ठा line_range line_range;
	अक्षर *target;
	काष्ठा strfilter *filter;
	काष्ठा nsinfo *nsi;
पूर्ण params;

/* Parse an event definition. Note that any error must die. */
अटल पूर्णांक parse_probe_event(स्थिर अक्षर *str)
अणु
	काष्ठा perf_probe_event *pev = &params.events[params.nevents];
	पूर्णांक ret;

	pr_debug("probe-definition(%d): %s\n", params.nevents, str);
	अगर (++params.nevents == MAX_PROBES) अणु
		pr_err("Too many probes (> %d) were specified.", MAX_PROBES);
		वापस -1;
	पूर्ण

	pev->uprobes = params.uprobes;
	अगर (params.target) अणु
		pev->target = strdup(params.target);
		अगर (!pev->target)
			वापस -ENOMEM;
		params.target_used = true;
	पूर्ण

	pev->nsi = nsinfo__get(params.nsi);

	/* Parse a perf-probe command पूर्णांकo event */
	ret = parse_perf_probe_command(str, pev);
	pr_debug("%d arguments\n", pev->nargs);

	वापस ret;
पूर्ण

अटल पूर्णांक params_add_filter(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *err = शून्य;
	पूर्णांक ret = 0;

	pr_debug2("Add filter: %s\n", str);
	अगर (!params.filter) अणु
		params.filter = strfilter__new(str, &err);
		अगर (!params.filter)
			ret = err ? -EINVAL : -ENOMEM;
	पूर्ण अन्यथा
		ret = strfilter__or(params.filter, str, &err);

	अगर (ret == -EINVAL) अणु
		pr_err("Filter parse error at %td.\n", err - str + 1);
		pr_err("Source: \"%s\"\n", str);
		pr_err("         %*c\n", (पूर्णांक)(err - str + 1), '^');
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_target(स्थिर अक्षर *ptr)
अणु
	पूर्णांक found = 0;
	स्थिर अक्षर *buf;

	/*
	 * The first argument after options can be an असलolute path
	 * to an executable / library or kernel module.
	 *
	 * TODO: Support relative path, and $PATH, $LD_LIBRARY_PATH,
	 * लघु module name.
	 */
	अगर (!params.target && ptr && *ptr == '/') अणु
		params.target = strdup(ptr);
		अगर (!params.target)
			वापस -ENOMEM;
		params.target_used = false;

		found = 1;
		buf = ptr + (म_माप(ptr) - 3);

		अगर (म_भेद(buf, ".ko"))
			params.uprobes = true;

	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक parse_probe_event_argv(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i, len, ret, found_target;
	अक्षर *buf;

	found_target = set_target(argv[0]);
	अगर (found_target < 0)
		वापस found_target;

	अगर (found_target && argc == 1)
		वापस 0;

	/* Bind up rest arguments */
	len = 0;
	क्रम (i = 0; i < argc; i++) अणु
		अगर (i == 0 && found_target)
			जारी;

		len += म_माप(argv[i]) + 1;
	पूर्ण
	buf = zalloc(len + 1);
	अगर (buf == शून्य)
		वापस -ENOMEM;
	len = 0;
	क्रम (i = 0; i < argc; i++) अणु
		अगर (i == 0 && found_target)
			जारी;

		len += प्र_लिखो(&buf[len], "%s ", argv[i]);
	पूर्ण
	ret = parse_probe_event(buf);
	मुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक opt_set_target(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक ret = -ENOENT;
	अक्षर *पंचांगp;

	अगर  (str) अणु
		अगर (!म_भेद(opt->दीर्घ_name, "exec"))
			params.uprobes = true;
		अन्यथा अगर (!म_भेद(opt->दीर्घ_name, "module"))
			params.uprobes = false;
		अन्यथा
			वापस ret;

		/* Expand given path to असलolute path, except क्रम modulename */
		अगर (params.uprobes || म_अक्षर(str, '/')) अणु
			पंचांगp = nsinfo__realpath(str, params.nsi);
			अगर (!पंचांगp) अणु
				pr_warning("Failed to get the absolute path of %s: %m\n", str);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			पंचांगp = strdup(str);
			अगर (!पंचांगp)
				वापस -ENOMEM;
		पूर्ण
		मुक्त(params.target);
		params.target = पंचांगp;
		params.target_used = false;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक opt_set_target_ns(स्थिर काष्ठा option *opt __maybe_unused,
			     स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक ret = -ENOENT;
	pid_t ns_pid;
	काष्ठा nsinfo *nsip;

	अगर (str) अणु
		त्रुटि_सं = 0;
		ns_pid = (pid_t)म_से_दीर्घ(str, शून्य, 10);
		अगर (त्रुटि_सं != 0) अणु
			ret = -त्रुटि_सं;
			pr_warning("Failed to parse %s as a pid: %s\n", str,
				   म_त्रुटि(त्रुटि_सं));
			वापस ret;
		पूर्ण
		nsip = nsinfo__new(ns_pid);
		अगर (nsip && nsip->need_setns)
			params.nsi = nsinfo__get(nsip);
		nsinfo__put(nsip);

		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण


/* Command option callbacks */

#अगर_घोषित HAVE_DWARF_SUPPORT
अटल पूर्णांक opt_show_lines(स्थिर काष्ठा option *opt,
			  स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	पूर्णांक ret = 0;

	अगर (!str)
		वापस 0;

	अगर (params.command == 'L') अणु
		pr_warning("Warning: more than one --line options are"
			   " detected. Only the first one is valid.\n");
		वापस 0;
	पूर्ण

	params.command = opt->लघु_name;
	ret = parse_line_range_desc(str, &params.line_range);

	वापस ret;
पूर्ण

अटल पूर्णांक opt_show_vars(स्थिर काष्ठा option *opt,
			 स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	काष्ठा perf_probe_event *pev = &params.events[params.nevents];
	पूर्णांक ret;

	अगर (!str)
		वापस 0;

	ret = parse_probe_event(str);
	अगर (!ret && pev->nargs != 0) अणु
		pr_err("  Error: '--vars' doesn't accept arguments.\n");
		वापस -EINVAL;
	पूर्ण
	params.command = opt->लघु_name;

	वापस ret;
पूर्ण
#अन्यथा
# define opt_show_lines शून्य
# define opt_show_vars शून्य
#पूर्ण_अगर
अटल पूर्णांक opt_add_probe_event(स्थिर काष्ठा option *opt,
			      स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	अगर (str) अणु
		params.command = opt->लघु_name;
		वापस parse_probe_event(str);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opt_set_filter_with_command(स्थिर काष्ठा option *opt,
				       स्थिर अक्षर *str, पूर्णांक unset)
अणु
	अगर (!unset)
		params.command = opt->लघु_name;

	अगर (str)
		वापस params_add_filter(str);

	वापस 0;
पूर्ण

अटल पूर्णांक opt_set_filter(स्थिर काष्ठा option *opt __maybe_unused,
			  स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	अगर (str)
		वापस params_add_filter(str);

	वापस 0;
पूर्ण

अटल पूर्णांक init_params(व्योम)
अणु
	वापस line_range__init(&params.line_range);
पूर्ण

अटल व्योम cleanup_params(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < params.nevents; i++)
		clear_perf_probe_event(params.events + i);
	line_range__clear(&params.line_range);
	मुक्त(params.target);
	strfilter__delete(params.filter);
	nsinfo__put(params.nsi);
	स_रखो(&params, 0, माप(params));
पूर्ण

अटल व्योम pr_err_with_code(स्थिर अक्षर *msg, पूर्णांक err)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];

	pr_err("%s", msg);
	pr_debug(" Reason: %s (Code: %d)",
		 str_error_r(-err, sbuf, माप(sbuf)), err);
	pr_err("\n");
पूर्ण

अटल पूर्णांक perf_add_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	पूर्णांक ret;
	पूर्णांक i, k;
	स्थिर अक्षर *event = शून्य, *group = शून्य;

	ret = init_probe_symbol_maps(pevs->uprobes);
	अगर (ret < 0)
		वापस ret;

	ret = convert_perf_probe_events(pevs, npevs);
	अगर (ret < 0)
		जाओ out_cleanup;

	अगर (params.command == 'D') अणु	/* it shows definition */
		ret = show_probe_trace_events(pevs, npevs);
		जाओ out_cleanup;
	पूर्ण

	ret = apply_perf_probe_events(pevs, npevs);
	अगर (ret < 0)
		जाओ out_cleanup;

	क्रम (i = k = 0; i < npevs; i++)
		k += pevs[i].ntevs;

	pr_info("Added new event%s\n", (k > 1) ? "s:" : ":");
	क्रम (i = 0; i < npevs; i++) अणु
		काष्ठा perf_probe_event *pev = &pevs[i];

		क्रम (k = 0; k < pev->ntevs; k++) अणु
			काष्ठा probe_trace_event *tev = &pev->tevs[k];
			/* Skipped events have no event name */
			अगर (!tev->event)
				जारी;

			/* We use tev's name क्रम showing new events */
			show_perf_probe_event(tev->group, tev->event, pev,
					      tev->poपूर्णांक.module, false);

			/* Save the last valid name */
			event = tev->event;
			group = tev->group;
		पूर्ण
	पूर्ण

	/* Note that it is possible to skip all events because of blacklist */
	अगर (event) अणु
		/* Show how to use the event. */
		pr_info("\nYou can now use it in all perf tools, such as:\n\n");
		pr_info("\tperf record -e %s:%s -aR sleep 1\n\n", group, event);
	पूर्ण

out_cleanup:
	cleanup_perf_probe_events(pevs, npevs);
	निकास_probe_symbol_maps();
	वापस ret;
पूर्ण

अटल पूर्णांक del_perf_probe_caches(काष्ठा strfilter *filter)
अणु
	काष्ठा probe_cache *cache;
	काष्ठा strlist *bidlist;
	काष्ठा str_node *nd;
	पूर्णांक ret;

	bidlist = build_id_cache__list_all(false);
	अगर (!bidlist) अणु
		ret = -त्रुटि_सं;
		pr_debug("Failed to get buildids: %d\n", ret);
		वापस ret ?: -ENOMEM;
	पूर्ण

	strlist__क्रम_each_entry(nd, bidlist) अणु
		cache = probe_cache__new(nd->s, शून्य);
		अगर (!cache)
			जारी;
		अगर (probe_cache__filter_purge(cache, filter) < 0 ||
		    probe_cache__commit(cache) < 0)
			pr_warning("Failed to remove entries for %s\n", nd->s);
		probe_cache__delete(cache);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक perf_del_probe_events(काष्ठा strfilter *filter)
अणु
	पूर्णांक ret, ret2, ufd = -1, kfd = -1;
	अक्षर *str = strfilter__string(filter);
	काष्ठा strlist *klist = शून्य, *ulist = शून्य;
	काष्ठा str_node *ent;

	अगर (!str)
		वापस -EINVAL;

	pr_debug("Delete filter: \'%s\'\n", str);

	अगर (probe_conf.cache)
		वापस del_perf_probe_caches(filter);

	/* Get current event names */
	ret = probe_file__खोलो_both(&kfd, &ufd, PF_FL_RW);
	अगर (ret < 0)
		जाओ out;

	klist = strlist__new(शून्य, शून्य);
	ulist = strlist__new(शून्य, शून्य);
	अगर (!klist || !ulist) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = probe_file__get_events(kfd, filter, klist);
	अगर (ret == 0) अणु
		strlist__क्रम_each_entry(ent, klist)
			pr_info("Removed event: %s\n", ent->s);

		ret = probe_file__del_strlist(kfd, klist);
		अगर (ret < 0)
			जाओ error;
	पूर्ण अन्यथा अगर (ret == -ENOMEM)
		जाओ error;

	ret2 = probe_file__get_events(ufd, filter, ulist);
	अगर (ret2 == 0) अणु
		strlist__क्रम_each_entry(ent, ulist)
			pr_info("Removed event: %s\n", ent->s);

		ret2 = probe_file__del_strlist(ufd, ulist);
		अगर (ret2 < 0)
			जाओ error;
	पूर्ण अन्यथा अगर (ret2 == -ENOMEM)
		जाओ error;

	अगर (ret == -ENOENT && ret2 == -ENOENT)
		pr_warning("\"%s\" does not hit any event.\n", str);
	अन्यथा
		ret = 0;

error:
	अगर (kfd >= 0)
		बंद(kfd);
	अगर (ufd >= 0)
		बंद(ufd);
out:
	strlist__delete(klist);
	strlist__delete(ulist);
	मुक्त(str);

	वापस ret;
पूर्ण

#अगर_घोषित HAVE_DWARF_SUPPORT
#घोषणा PROBEDEF_STR	\
	"[EVENT=]FUNC[@SRC][+OFF|%return|:RL|;PT]|SRC:AL|SRC;PT [[NAME=]ARG ...]"
#अन्यथा
#घोषणा PROBEDEF_STR	"[EVENT=]FUNC[+OFF|%return] [[NAME=]ARG ...]"
#पूर्ण_अगर


अटल पूर्णांक
__cmd_probe(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर * स्थिर probe_usage[] = अणु
		"perf probe [<options>] 'PROBEDEF' ['PROBEDEF' ...]",
		"perf probe [<options>] --add 'PROBEDEF' [--add 'PROBEDEF' ...]",
		"perf probe [<options>] --del '[GROUP:]EVENT' ...",
		"perf probe --list [GROUP:]EVENT ...",
#अगर_घोषित HAVE_DWARF_SUPPORT
		"perf probe [<options>] --line 'LINEDESC'",
		"perf probe [<options>] --vars 'PROBEPOINT'",
#पूर्ण_अगर
		"perf probe [<options>] --funcs",
		शून्य
	पूर्ण;
	काष्ठा option options[] = अणु
	OPT_INCR('v', "verbose", &verbose,
		    "be more verbose (show parsed arguments, etc)"),
	OPT_BOOLEAN('q', "quiet", &params.quiet,
		    "be quiet (do not show any messages)"),
	OPT_CALLBACK_DEFAULT('l', "list", शून्य, "[GROUP:]EVENT",
			     "list up probe events",
			     opt_set_filter_with_command, DEFAULT_LIST_FILTER),
	OPT_CALLBACK('d', "del", शून्य, "[GROUP:]EVENT", "delete a probe event.",
		     opt_set_filter_with_command),
	OPT_CALLBACK('a', "add", शून्य, PROBEDEF_STR,
		"probe point definition, where\n"
		"\t\tGROUP:\tGroup name (optional)\n"
		"\t\tEVENT:\tEvent name\n"
		"\t\tFUNC:\tFunction name\n"
		"\t\tOFF:\tOffset from function entry (in byte)\n"
		"\t\t%return:\tPut the probe at function return\n"
#अगर_घोषित HAVE_DWARF_SUPPORT
		"\t\tSRC:\tSource code path\n"
		"\t\tRL:\tRelative line number from function entry.\n"
		"\t\tAL:\tAbsolute line number in file.\n"
		"\t\tPT:\tLazy expression of line code.\n"
		"\t\tARG:\tProbe argument (local variable name or\n"
		"\t\t\tkprobe-tracer argument format.)\n",
#अन्यथा
		"\t\tARG:\tProbe argument (kprobe-tracer argument format.)\n",
#पूर्ण_अगर
		opt_add_probe_event),
	OPT_CALLBACK('D', "definition", शून्य, PROBEDEF_STR,
		"Show trace event definition of given traceevent for k/uprobe_events.",
		opt_add_probe_event),
	OPT_BOOLEAN('f', "force", &probe_conf.क्रमce_add, "forcibly add events"
		    " with existing name"),
	OPT_CALLBACK('L', "line", शून्य,
		     "FUNC[:RLN[+NUM|-RLN2]]|SRC:ALN[+NUM|-ALN2]",
		     "Show source code lines.", opt_show_lines),
	OPT_CALLBACK('V', "vars", शून्य,
		     "FUNC[@SRC][+OFF|%return|:RL|;PT]|SRC:AL|SRC;PT",
		     "Show accessible variables on PROBEDEF", opt_show_vars),
	OPT_BOOLEAN('\0', "externs", &probe_conf.show_ext_vars,
		    "Show external variables too (with --vars only)"),
	OPT_BOOLEAN('\0', "range", &probe_conf.show_location_range,
		"Show variables location range in scope (with --vars only)"),
	OPT_STRING('k', "vmlinux", &symbol_conf.vmlinux_name,
		   "file", "vmlinux pathname"),
	OPT_STRING('s', "source", &symbol_conf.source_prefix,
		   "directory", "path to kernel source"),
	OPT_BOOLEAN('\0', "no-inlines", &probe_conf.no_अंतरभूतs,
		"Don't search inlined functions"),
	OPT__DRY_RUN(&probe_event_dry_run),
	OPT_INTEGER('\0', "max-probes", &probe_conf.max_probes,
		 "Set how many probe points can be found for a probe."),
	OPT_CALLBACK_DEFAULT('F', "funcs", शून्य, "[FILTER]",
			     "Show potential probe-able functions.",
			     opt_set_filter_with_command, DEFAULT_FUNC_FILTER),
	OPT_CALLBACK('\0', "filter", शून्य,
		     "[!]FILTER", "Set a filter (with --vars/funcs only)\n"
		     "\t\t\t(default: \"" DEFAULT_VAR_FILTER "\" for --vars,\n"
		     "\t\t\t \"" DEFAULT_FUNC_FILTER "\" for --funcs)",
		     opt_set_filter),
	OPT_CALLBACK('x', "exec", शून्य, "executable|path",
			"target executable name or path", opt_set_target),
	OPT_CALLBACK('m', "module", शून्य, "modname|path",
		"target module name (for online) or path (for offline)",
		opt_set_target),
	OPT_BOOLEAN(0, "demangle", &symbol_conf.demangle,
		    "Enable symbol demangling"),
	OPT_BOOLEAN(0, "demangle-kernel", &symbol_conf.demangle_kernel,
		    "Enable kernel symbol demangling"),
	OPT_BOOLEAN(0, "cache", &probe_conf.cache, "Manipulate probe cache"),
	OPT_STRING(0, "symfs", &symbol_conf.symfs, "directory",
		   "Look for files with symbols relative to this directory"),
	OPT_CALLBACK(0, "target-ns", शून्य, "pid",
		     "target pid for namespace contexts", opt_set_target_ns),
	OPT_END()
	पूर्ण;
	पूर्णांक ret;

	set_option_flag(options, 'a', "add", PARSE_OPT_EXCLUSIVE);
	set_option_flag(options, 'd', "del", PARSE_OPT_EXCLUSIVE);
	set_option_flag(options, 'D', "definition", PARSE_OPT_EXCLUSIVE);
	set_option_flag(options, 'l', "list", PARSE_OPT_EXCLUSIVE);
#अगर_घोषित HAVE_DWARF_SUPPORT
	set_option_flag(options, 'L', "line", PARSE_OPT_EXCLUSIVE);
	set_option_flag(options, 'V', "vars", PARSE_OPT_EXCLUSIVE);
#अन्यथा
# define set_nobuild(s, l, c) set_option_nobuild(options, s, l, "NO_DWARF=1", c)
	set_nobuild('L', "line", false);
	set_nobuild('V', "vars", false);
	set_nobuild('\0', "externs", false);
	set_nobuild('\0', "range", false);
	set_nobuild('k', "vmlinux", true);
	set_nobuild('s', "source", true);
	set_nobuild('\0', "no-inlines", true);
# undef set_nobuild
#पूर्ण_अगर
	set_option_flag(options, 'F', "funcs", PARSE_OPT_EXCLUSIVE);

	argc = parse_options(argc, argv, options, probe_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (argc > 0) अणु
		अगर (म_भेद(argv[0], "-") == 0) अणु
			usage_with_options_msg(probe_usage, options,
				"'-' is not supported.\n");
		पूर्ण
		अगर (params.command && params.command != 'a') अणु
			usage_with_options_msg(probe_usage, options,
				"another command except --add is set.\n");
		पूर्ण
		ret = parse_probe_event_argv(argc, argv);
		अगर (ret < 0) अणु
			pr_err_with_code("  Error: Command Parse Error.", ret);
			वापस ret;
		पूर्ण
		params.command = 'a';
	पूर्ण

	अगर (params.quiet) अणु
		अगर (verbose != 0) अणु
			pr_err("  Error: -v and -q are exclusive.\n");
			वापस -EINVAL;
		पूर्ण
		verbose = -1;
	पूर्ण

	अगर (probe_conf.max_probes == 0)
		probe_conf.max_probes = MAX_PROBES;

	/*
	 * Only consider the user's kernel image path अगर given.
	 */
	symbol_conf.try_vmlinux_path = (symbol_conf.vmlinux_name == शून्य);

	/*
	 * Except क्रम --list, --del and --add, other command करोesn't depend
	 * nor change running kernel. So अगर user gives offline vmlinux,
	 * ignore its buildid.
	 */
	अगर (!म_अक्षर("lda", params.command) && symbol_conf.vmlinux_name)
		symbol_conf.ignore_vmlinux_buildid = true;

	चयन (params.command) अणु
	हाल 'l':
		अगर (params.uprobes) अणु
			pr_err("  Error: Don't use --list with --exec.\n");
			parse_options_usage(probe_usage, options, "l", true);
			parse_options_usage(शून्य, options, "x", true);
			वापस -EINVAL;
		पूर्ण
		ret = show_perf_probe_events(params.filter);
		अगर (ret < 0)
			pr_err_with_code("  Error: Failed to show event list.", ret);
		वापस ret;
	हाल 'F':
		ret = show_available_funcs(params.target, params.nsi,
					   params.filter, params.uprobes);
		अगर (ret < 0)
			pr_err_with_code("  Error: Failed to show functions.", ret);
		वापस ret;
#अगर_घोषित HAVE_DWARF_SUPPORT
	हाल 'L':
		ret = show_line_range(&params.line_range, params.target,
				      params.nsi, params.uprobes);
		अगर (ret < 0)
			pr_err_with_code("  Error: Failed to show lines.", ret);
		वापस ret;
	हाल 'V':
		अगर (!params.filter)
			params.filter = strfilter__new(DEFAULT_VAR_FILTER,
						       शून्य);

		ret = show_available_vars(params.events, params.nevents,
					  params.filter);
		अगर (ret < 0)
			pr_err_with_code("  Error: Failed to show vars.", ret);
		वापस ret;
#पूर्ण_अगर
	हाल 'd':
		ret = perf_del_probe_events(params.filter);
		अगर (ret < 0) अणु
			pr_err_with_code("  Error: Failed to delete events.", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	हाल 'D':
	हाल 'a':

		/* Ensure the last given target is used */
		अगर (params.target && !params.target_used) अणु
			pr_err("  Error: -x/-m must follow the probe definitions.\n");
			parse_options_usage(probe_usage, options, "m", true);
			parse_options_usage(शून्य, options, "x", true);
			वापस -EINVAL;
		पूर्ण

		ret = perf_add_probe_events(params.events, params.nevents);
		अगर (ret < 0) अणु

			/*
			 * When perf_add_probe_events() fails it calls
			 * cleanup_perf_probe_events(pevs, npevs), i.e.
			 * cleanup_perf_probe_events(params.events, params.nevents), which
			 * will call clear_perf_probe_event(), so set nevents to zero
			 * to aव्योम cleanup_params() to call clear_perf_probe_event() again
			 * on the same pevs.
			 */
			params.nevents = 0;
			pr_err_with_code("  Error: Failed to add events.", ret);
			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		usage_with_options(probe_usage, options);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cmd_probe(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक ret;

	ret = init_params();
	अगर (!ret) अणु
		ret = __cmd_probe(argc, argv);
		cleanup_params();
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण
