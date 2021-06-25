<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-help.c
 *
 * Builtin help command
 */
#समावेश "util/cache.h"
#समावेश "util/config.h"
#समावेश "util/strbuf.h"
#समावेश "builtin.h"
#समावेश <subcmd/exec-cmd.h>
#समावेश "common-cmds.h"
#समावेश <subcmd/parse-options.h>
#समावेश <subcmd/run-command.h>
#समावेश <subcmd/help.h>
#समावेश "util/debug.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

अटल काष्ठा man_viewer_list अणु
	काष्ठा man_viewer_list *next;
	अक्षर name[0];
पूर्ण *man_viewer_list;

अटल काष्ठा man_viewer_info_list अणु
	काष्ठा man_viewer_info_list *next;
	स्थिर अक्षर *info;
	अक्षर name[0];
पूर्ण *man_viewer_info_list;

क्रमागत help_क्रमmat अणु
	HELP_FORMAT_NONE,
	HELP_FORMAT_MAN,
	HELP_FORMAT_INFO,
	HELP_FORMAT_WEB,
पूर्ण;

अटल क्रमागत help_क्रमmat parse_help_क्रमmat(स्थिर अक्षर *क्रमmat)
अणु
	अगर (!म_भेद(क्रमmat, "man"))
		वापस HELP_FORMAT_MAN;
	अगर (!म_भेद(क्रमmat, "info"))
		वापस HELP_FORMAT_INFO;
	अगर (!म_भेद(क्रमmat, "web") || !म_भेद(क्रमmat, "html"))
		वापस HELP_FORMAT_WEB;

	pr_err("unrecognized help format '%s'", क्रमmat);
	वापस HELP_FORMAT_NONE;
पूर्ण

अटल स्थिर अक्षर *get_man_viewer_info(स्थिर अक्षर *name)
अणु
	काष्ठा man_viewer_info_list *viewer;

	क्रम (viewer = man_viewer_info_list; viewer; viewer = viewer->next) अणु
		अगर (!strहालcmp(name, viewer->name))
			वापस viewer->info;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक check_emacsclient_version(व्योम)
अणु
	काष्ठा strbuf buffer = STRBUF_INIT;
	काष्ठा child_process ec_process;
	स्थिर अक्षर *argv_ec[] = अणु "emacsclient", "--version", शून्य पूर्ण;
	पूर्णांक version;
	पूर्णांक ret = -1;

	/* emacsclient prपूर्णांकs its version number on मानक_त्रुटि */
	स_रखो(&ec_process, 0, माप(ec_process));
	ec_process.argv = argv_ec;
	ec_process.err = -1;
	ec_process.मानक_निकास_to_मानक_त्रुटि = 1;
	अगर (start_command(&ec_process)) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to start emacsclient.\n");
		वापस -1;
	पूर्ण
	अगर (strbuf_पढ़ो(&buffer, ec_process.err, 20) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to read emacsclient version\n");
		जाओ out;
	पूर्ण
	बंद(ec_process.err);

	/*
	 * Don't bother checking वापस value, because "emacsclient --version"
	 * seems to always निकासs with code 1.
	 */
	finish_command(&ec_process);

	अगर (!strstarts(buffer.buf, "emacsclient")) अणु
		ख_लिखो(मानक_त्रुटि, "Failed to parse emacsclient version.\n");
		जाओ out;
	पूर्ण

	version = म_से_प(buffer.buf + म_माप("emacsclient"));

	अगर (version < 22) अणु
		ख_लिखो(मानक_त्रुटि,
			"emacsclient version '%d' too old (< 22).\n",
			version);
	पूर्ण अन्यथा
		ret = 0;
out:
	strbuf_release(&buffer);
	वापस ret;
पूर्ण

अटल व्योम exec_failed(स्थिर अक्षर *cmd)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];
	pr_warning("failed to exec '%s': %s", cmd, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
पूर्ण

अटल व्योम exec_woman_emacs(स्थिर अक्षर *path, स्थिर अक्षर *page)
अणु
	अगर (!check_emacsclient_version()) अणु
		/* This works only with emacsclient version >= 22. */
		अक्षर *man_page;

		अगर (!path)
			path = "emacsclient";
		अगर (aप्र_लिखो(&man_page, "(woman \"%s\")", page) > 0) अणु
			execlp(path, "emacsclient", "-e", man_page, शून्य);
			मुक्त(man_page);
		पूर्ण
		exec_failed(path);
	पूर्ण
पूर्ण

अटल व्योम exec_man_konqueror(स्थिर अक्षर *path, स्थिर अक्षर *page)
अणु
	स्थिर अक्षर *display = दो_पर्या("DISPLAY");

	अगर (display && *display) अणु
		अक्षर *man_page;
		स्थिर अक्षर *filename = "kfmclient";

		/* It's simpler to launch konqueror using kfmclient. */
		अगर (path) अणु
			स्थिर अक्षर *file = म_खोजप(path, '/');
			अगर (file && !म_भेद(file + 1, "konqueror")) अणु
				अक्षर *new = strdup(path);
				अक्षर *dest = म_खोजप(new, '/');

				/* म_माप("konqueror") == म_माप("kfmclient") */
				म_नकल(dest + 1, "kfmclient");
				path = new;
			पूर्ण
			अगर (file)
				filename = file;
		पूर्ण अन्यथा
			path = "kfmclient";
		अगर (aप्र_लिखो(&man_page, "man:%s(1)", page) > 0) अणु
			execlp(path, filename, "newTab", man_page, शून्य);
			मुक्त(man_page);
		पूर्ण
		exec_failed(path);
	पूर्ण
पूर्ण

अटल व्योम exec_man_man(स्थिर अक्षर *path, स्थिर अक्षर *page)
अणु
	अगर (!path)
		path = "man";
	execlp(path, "man", page, शून्य);
	exec_failed(path);
पूर्ण

अटल व्योम exec_man_cmd(स्थिर अक्षर *cmd, स्थिर अक्षर *page)
अणु
	अक्षर *shell_cmd;

	अगर (aप्र_लिखो(&shell_cmd, "%s %s", cmd, page) > 0) अणु
		execl("/bin/sh", "sh", "-c", shell_cmd, शून्य);
		मुक्त(shell_cmd);
	पूर्ण
	exec_failed(cmd);
पूर्ण

अटल व्योम add_man_viewer(स्थिर अक्षर *name)
अणु
	काष्ठा man_viewer_list **p = &man_viewer_list;
	माप_प्रकार len = म_माप(name);

	जबतक (*p)
		p = &((*p)->next);
	*p = zalloc(माप(**p) + len + 1);
	म_नकल((*p)->name, name);
पूर्ण

अटल पूर्णांक supported_man_viewer(स्थिर अक्षर *name, माप_प्रकार len)
अणु
	वापस (!strnहालcmp("man", name, len) ||
		!strnहालcmp("woman", name, len) ||
		!strnहालcmp("konqueror", name, len));
पूर्ण

अटल व्योम करो_add_man_viewer_info(स्थिर अक्षर *name,
				   माप_प्रकार len,
				   स्थिर अक्षर *value)
अणु
	काष्ठा man_viewer_info_list *new = zalloc(माप(*new) + len + 1);

	म_नकलन(new->name, name, len);
	new->info = strdup(value);
	new->next = man_viewer_info_list;
	man_viewer_info_list = new;
पूर्ण

अटल व्योम unsupported_man_viewer(स्थिर अक्षर *name, स्थिर अक्षर *var)
अणु
	pr_warning("'%s': path for unsupported man viewer.\n"
		   "Please consider using 'man.<tool>.%s' instead.", name, var);
पूर्ण

अटल पूर्णांक add_man_viewer_path(स्थिर अक्षर *name,
			       माप_प्रकार len,
			       स्थिर अक्षर *value)
अणु
	अगर (supported_man_viewer(name, len))
		करो_add_man_viewer_info(name, len, value);
	अन्यथा
		unsupported_man_viewer(name, "cmd");

	वापस 0;
पूर्ण

अटल पूर्णांक add_man_viewer_cmd(स्थिर अक्षर *name,
			      माप_प्रकार len,
			      स्थिर अक्षर *value)
अणु
	अगर (supported_man_viewer(name, len))
		unsupported_man_viewer(name, "path");
	अन्यथा
		करो_add_man_viewer_info(name, len, value);

	वापस 0;
पूर्ण

अटल पूर्णांक add_man_viewer_info(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	स्थिर अक्षर *name = var + 4;
	स्थिर अक्षर *subkey = म_खोजप(name, '.');

	अगर (!subkey) अणु
		pr_err("Config with no key for man viewer: %s", name);
		वापस -1;
	पूर्ण

	अगर (!म_भेद(subkey, ".path")) अणु
		अगर (!value)
			वापस config_error_nonbool(var);
		वापस add_man_viewer_path(name, subkey - name, value);
	पूर्ण
	अगर (!म_भेद(subkey, ".cmd")) अणु
		अगर (!value)
			वापस config_error_nonbool(var);
		वापस add_man_viewer_cmd(name, subkey - name, value);
	पूर्ण

	pr_warning("'%s': unsupported man viewer sub key.", subkey);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_help_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	क्रमागत help_क्रमmat *help_क्रमmatp = cb;

	अगर (!म_भेद(var, "help.format")) अणु
		अगर (!value)
			वापस config_error_nonbool(var);
		*help_क्रमmatp = parse_help_क्रमmat(value);
		अगर (*help_क्रमmatp == HELP_FORMAT_NONE)
			वापस -1;
		वापस 0;
	पूर्ण
	अगर (!म_भेद(var, "man.viewer")) अणु
		अगर (!value)
			वापस config_error_nonbool(var);
		add_man_viewer(value);
		वापस 0;
	पूर्ण
	अगर (strstarts(var, "man."))
		वापस add_man_viewer_info(var, value);

	वापस 0;
पूर्ण

अटल काष्ठा cmdnames मुख्य_cmds, other_cmds;

व्योम list_common_cmds_help(व्योम)
अणु
	अचिन्हित पूर्णांक i, दीर्घest = 0;

	क्रम (i = 0; i < ARRAY_SIZE(common_cmds); i++) अणु
		अगर (दीर्घest < म_माप(common_cmds[i].name))
			दीर्घest = म_माप(common_cmds[i].name);
	पूर्ण

	माला_दो(" The most commonly used perf commands are:");
	क्रम (i = 0; i < ARRAY_SIZE(common_cmds); i++) अणु
		म_लिखो("   %-*s   ", दीर्घest, common_cmds[i].name);
		माला_दो(common_cmds[i].help);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *cmd_to_page(स्थिर अक्षर *perf_cmd)
अणु
	अक्षर *s;

	अगर (!perf_cmd)
		वापस "perf";
	अन्यथा अगर (strstarts(perf_cmd, "perf"))
		वापस perf_cmd;

	वापस aप्र_लिखो(&s, "perf-%s", perf_cmd) < 0 ? शून्य : s;
पूर्ण

अटल व्योम setup_man_path(व्योम)
अणु
	अक्षर *new_path;
	स्थिर अक्षर *old_path = दो_पर्या("MANPATH");

	/* We should always put ':' after our path. If there is no
	 * old_path, the ':' at the end will let 'man' to try
	 * प्रणाली-wide paths after ours to find the manual page. If
	 * there is old_path, we need ':' as delimiter. */
	अगर (aप्र_लिखो(&new_path, "%s:%s", प्रणाली_path(PERF_MAN_PATH), old_path ?: "") > 0) अणु
		setenv("MANPATH", new_path, 1);
		मुक्त(new_path);
	पूर्ण अन्यथा अणु
		pr_err("Unable to setup man path");
	पूर्ण
पूर्ण

अटल व्योम exec_viewer(स्थिर अक्षर *name, स्थिर अक्षर *page)
अणु
	स्थिर अक्षर *info = get_man_viewer_info(name);

	अगर (!strहालcmp(name, "man"))
		exec_man_man(info, page);
	अन्यथा अगर (!strहालcmp(name, "woman"))
		exec_woman_emacs(info, page);
	अन्यथा अगर (!strहालcmp(name, "konqueror"))
		exec_man_konqueror(info, page);
	अन्यथा अगर (info)
		exec_man_cmd(info, page);
	अन्यथा
		pr_warning("'%s': unknown man viewer.", name);
पूर्ण

अटल पूर्णांक show_man_page(स्थिर अक्षर *perf_cmd)
अणु
	काष्ठा man_viewer_list *viewer;
	स्थिर अक्षर *page = cmd_to_page(perf_cmd);
	स्थिर अक्षर *fallback = दो_पर्या("PERF_MAN_VIEWER");

	setup_man_path();
	क्रम (viewer = man_viewer_list; viewer; viewer = viewer->next)
		exec_viewer(viewer->name, page); /* will वापस when unable */

	अगर (fallback)
		exec_viewer(fallback, page);
	exec_viewer("man", page);

	pr_err("no man viewer handled the request");
	वापस -1;
पूर्ण

अटल पूर्णांक show_info_page(स्थिर अक्षर *perf_cmd)
अणु
	स्थिर अक्षर *page = cmd_to_page(perf_cmd);
	setenv("INFOPATH", प्रणाली_path(PERF_INFO_PATH), 1);
	execlp("info", "info", "perfman", page, शून्य);
	वापस -1;
पूर्ण

अटल पूर्णांक get_hपंचांगl_page_path(अक्षर **page_path, स्थिर अक्षर *page)
अणु
	काष्ठा stat st;
	स्थिर अक्षर *hपंचांगl_path = प्रणाली_path(PERF_HTML_PATH);

	/* Check that we have a perf करोcumentation directory. */
	अगर (stat(mkpath("%s/perf.html", hपंचांगl_path), &st)
	    || !S_ISREG(st.st_mode)) अणु
		pr_err("'%s': not a documentation directory.", hपंचांगl_path);
		वापस -1;
	पूर्ण

	वापस aप्र_लिखो(page_path, "%s/%s.html", hपंचांगl_path, page);
पूर्ण

/*
 * If खोलो_hपंचांगl is not defined in a platक्रमm-specअगरic way (see क्रम
 * example compat/mingw.h), we use the script web--browse to display
 * HTML.
 */
#अगर_अघोषित खोलो_hपंचांगl
अटल व्योम खोलो_hपंचांगl(स्थिर अक्षर *path)
अणु
	execl_cmd("web--browse", "-c", "help.browser", path, शून्य);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक show_hपंचांगl_page(स्थिर अक्षर *perf_cmd)
अणु
	स्थिर अक्षर *page = cmd_to_page(perf_cmd);
	अक्षर *page_path; /* it leaks but we exec bellow */

	अगर (get_hपंचांगl_page_path(&page_path, page) < 0)
		वापस -1;

	खोलो_hपंचांगl(page_path);

	वापस 0;
पूर्ण

पूर्णांक cmd_help(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool show_all = false;
	क्रमागत help_क्रमmat help_क्रमmat = HELP_FORMAT_MAN;
	काष्ठा option builtin_help_options[] = अणु
	OPT_BOOLEAN('a', "all", &show_all, "print all available commands"),
	OPT_SET_UINT('m', "man", &help_क्रमmat, "show man page", HELP_FORMAT_MAN),
	OPT_SET_UINT('w', "web", &help_क्रमmat, "show manual in web browser",
			HELP_FORMAT_WEB),
	OPT_SET_UINT('i', "info", &help_क्रमmat, "show info page",
			HELP_FORMAT_INFO),
	OPT_END(),
	पूर्ण;
	स्थिर अक्षर * स्थिर builtin_help_subcommands[] = अणु
		"buildid-cache", "buildid-list", "diff", "evlist", "help", "list",
		"record", "report", "bench", "stat", "timechart", "top", "annotate",
		"script", "sched", "kallsyms", "kmem", "lock", "kvm", "test", "inject", "mem", "data",
#अगर_घोषित HAVE_LIBELF_SUPPORT
		"probe",
#पूर्ण_अगर
#अगर defined(HAVE_LIBAUDIT_SUPPORT) || defined(HAVE_SYSCALL_TABLE_SUPPORT)
		"trace",
#पूर्ण_अगर
	शून्य पूर्ण;
	स्थिर अक्षर *builtin_help_usage[] = अणु
		"perf help [--all] [--man|--web|--info] [command]",
		शून्य
	पूर्ण;
	पूर्णांक rc;

	load_command_list("perf-", &मुख्य_cmds, &other_cmds);

	rc = perf_config(perf_help_config, &help_क्रमmat);
	अगर (rc)
		वापस rc;

	argc = parse_options_subcommand(argc, argv, builtin_help_options,
			builtin_help_subcommands, builtin_help_usage, 0);

	अगर (show_all) अणु
		म_लिखो("\n Usage: %s\n\n", perf_usage_string);
		list_commands("perf commands", &मुख्य_cmds, &other_cmds);
		म_लिखो(" %s\n\n", perf_more_info_string);
		वापस 0;
	पूर्ण

	अगर (!argv[0]) अणु
		म_लिखो("\n usage: %s\n\n", perf_usage_string);
		list_common_cmds_help();
		म_लिखो("\n %s\n\n", perf_more_info_string);
		वापस 0;
	पूर्ण

	चयन (help_क्रमmat) अणु
	हाल HELP_FORMAT_MAN:
		rc = show_man_page(argv[0]);
		अवरोध;
	हाल HELP_FORMAT_INFO:
		rc = show_info_page(argv[0]);
		अवरोध;
	हाल HELP_FORMAT_WEB:
		rc = show_hपंचांगl_page(argv[0]);
		अवरोध;
	हाल HELP_FORMAT_NONE:
		/* fall-through */
	शेष:
		rc = -1;
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
