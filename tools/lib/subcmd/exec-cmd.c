<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश "subcmd-util.h"
#समावेश "exec-cmd.h"
#समावेश "subcmd-config.h"

#घोषणा MAX_ARGS	32
#घोषणा PATH_MAX	4096

अटल स्थिर अक्षर *argv_exec_path;
अटल स्थिर अक्षर *argv0_path;

व्योम exec_cmd_init(स्थिर अक्षर *exec_name, स्थिर अक्षर *prefix,
		   स्थिर अक्षर *exec_path, स्थिर अक्षर *exec_path_env)
अणु
	subcmd_config.exec_name		= exec_name;
	subcmd_config.prefix		= prefix;
	subcmd_config.exec_path		= exec_path;
	subcmd_config.exec_path_env	= exec_path_env;
पूर्ण

#घोषणा is_dir_sep(c) ((c) == '/')

अटल पूर्णांक is_असलolute_path(स्थिर अक्षर *path)
अणु
	वापस path[0] == '/';
पूर्ण

अटल स्थिर अक्षर *get_pwd_cwd(व्योम)
अणु
	अटल अक्षर cwd[PATH_MAX + 1];
	अक्षर *pwd;
	काष्ठा stat cwd_stat, pwd_stat;
	अगर (अ_लोwd(cwd, PATH_MAX) == शून्य)
		वापस शून्य;
	pwd = दो_पर्या("PWD");
	अगर (pwd && म_भेद(pwd, cwd)) अणु
		stat(cwd, &cwd_stat);
		अगर (!stat(pwd, &pwd_stat) &&
		    pwd_stat.st_dev == cwd_stat.st_dev &&
		    pwd_stat.st_ino == cwd_stat.st_ino) अणु
			strlcpy(cwd, pwd, PATH_MAX);
		पूर्ण
	पूर्ण
	वापस cwd;
पूर्ण

अटल स्थिर अक्षर *make_nonrelative_path(स्थिर अक्षर *path)
अणु
	अटल अक्षर buf[PATH_MAX + 1];

	अगर (is_असलolute_path(path)) अणु
		अगर (strlcpy(buf, path, PATH_MAX) >= PATH_MAX)
			die("Too long path: %.*s", 60, path);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *cwd = get_pwd_cwd();
		अगर (!cwd)
			die("Cannot determine the current working directory");
		अगर (snम_लिखो(buf, PATH_MAX, "%s/%s", cwd, path) >= PATH_MAX)
			die("Too long path: %.*s", 60, path);
	पूर्ण
	वापस buf;
पूर्ण

अक्षर *प्रणाली_path(स्थिर अक्षर *path)
अणु
	अक्षर *buf = शून्य;

	अगर (is_असलolute_path(path))
		वापस strdup(path);

	aम_जोड़ोf(&buf, "%s/%s", subcmd_config.prefix, path);

	वापस buf;
पूर्ण

स्थिर अक्षर *extract_argv0_path(स्थिर अक्षर *argv0)
अणु
	स्थिर अक्षर *slash;

	अगर (!argv0 || !*argv0)
		वापस शून्य;
	slash = argv0 + म_माप(argv0);

	जबतक (argv0 <= slash && !is_dir_sep(*slash))
		slash--;

	अगर (slash >= argv0) अणु
		argv0_path = strndup(argv0, slash - argv0);
		वापस argv0_path ? slash + 1 : शून्य;
	पूर्ण

	वापस argv0;
पूर्ण

व्योम set_argv_exec_path(स्थिर अक्षर *exec_path)
अणु
	argv_exec_path = exec_path;
	/*
	 * Propagate this setting to बाह्यal programs.
	 */
	setenv(subcmd_config.exec_path_env, exec_path, 1);
पूर्ण


/* Returns the highest-priority location to look क्रम subprograms. */
अक्षर *get_argv_exec_path(व्योम)
अणु
	अक्षर *env;

	अगर (argv_exec_path)
		वापस strdup(argv_exec_path);

	env = दो_पर्या(subcmd_config.exec_path_env);
	अगर (env && *env)
		वापस strdup(env);

	वापस प्रणाली_path(subcmd_config.exec_path);
पूर्ण

अटल व्योम add_path(अक्षर **out, स्थिर अक्षर *path)
अणु
	अगर (path && *path) अणु
		अगर (is_असलolute_path(path))
			aम_जोड़ो(out, path);
		अन्यथा
			aम_जोड़ो(out, make_nonrelative_path(path));

		aम_जोड़ो(out, ":");
	पूर्ण
पूर्ण

व्योम setup_path(व्योम)
अणु
	स्थिर अक्षर *old_path = दो_पर्या("PATH");
	अक्षर *new_path = शून्य;
	अक्षर *पंचांगp = get_argv_exec_path();

	add_path(&new_path, पंचांगp);
	add_path(&new_path, argv0_path);
	मुक्त(पंचांगp);

	अगर (old_path)
		aम_जोड़ो(&new_path, old_path);
	अन्यथा
		aम_जोड़ो(&new_path, "/usr/local/bin:/usr/bin:/bin");

	setenv("PATH", new_path, 1);

	मुक्त(new_path);
पूर्ण

अटल स्थिर अक्षर **prepare_exec_cmd(स्थिर अक्षर **argv)
अणु
	पूर्णांक argc;
	स्थिर अक्षर **nargv;

	क्रम (argc = 0; argv[argc]; argc++)
		; /* just counting */
	nargv = दो_स्मृति(माप(*nargv) * (argc + 2));

	nargv[0] = subcmd_config.exec_name;
	क्रम (argc = 0; argv[argc]; argc++)
		nargv[argc + 1] = argv[argc];
	nargv[argc + 1] = शून्य;
	वापस nargv;
पूर्ण

पूर्णांक execv_cmd(स्थिर अक्षर **argv) अणु
	स्थिर अक्षर **nargv = prepare_exec_cmd(argv);

	/* execvp() can only ever वापस अगर it fails */
	execvp(subcmd_config.exec_name, (अक्षर **)nargv);

	मुक्त(nargv);
	वापस -1;
पूर्ण


पूर्णांक execl_cmd(स्थिर अक्षर *cmd,...)
अणु
	पूर्णांक argc;
	स्थिर अक्षर *argv[MAX_ARGS + 1];
	स्थिर अक्षर *arg;
	बहु_सूची param;

	बहु_शुरू(param, cmd);
	argv[0] = cmd;
	argc = 1;
	जबतक (argc < MAX_ARGS) अणु
		arg = argv[argc++] = बहु_तर्क(param, अक्षर *);
		अगर (!arg)
			अवरोध;
	पूर्ण
	बहु_पूर्ण(param);
	अगर (MAX_ARGS <= argc) अणु
		ख_लिखो(मानक_त्रुटि, " Error: too many args to run %s\n", cmd);
		वापस -1;
	पूर्ण

	argv[argc] = शून्य;
	वापस execv_cmd(argv);
पूर्ण
