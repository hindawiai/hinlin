<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

/*
 * objtool check:
 *
 * This command analyzes every .o file and ensures the validity of its stack
 * trace metadata.  It enक्रमces a set of rules on यंत्र code and C अंतरभूत
 * assembly code so that stack traces can be reliable.
 *
 * For more inक्रमmation, see tools/objtool/Documentation/stack-validation.txt.
 */

#समावेश <subcmd/parse-options.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <objtool/builtin.h>
#समावेश <objtool/objtool.h>

bool no_fp, no_unreachable, retpoline, module, backtrace, uaccess, stats,
     validate_dup, vmlinux, mcount, noinstr, backup;

अटल स्थिर अक्षर * स्थिर check_usage[] = अणु
	"objtool check [<options>] file.o",
	शून्य,
पूर्ण;

अटल स्थिर अक्षर * स्थिर env_usage[] = अणु
	"OBJTOOL_ARGS=\"<options>\"",
	शून्य,
पूर्ण;

स्थिर काष्ठा option check_options[] = अणु
	OPT_BOOLEAN('f', "no-fp", &no_fp, "Skip frame pointer validation"),
	OPT_BOOLEAN('u', "no-unreachable", &no_unreachable, "Skip 'unreachable instruction' warnings"),
	OPT_BOOLEAN('r', "retpoline", &retpoline, "Validate retpoline assumptions"),
	OPT_BOOLEAN('m', "module", &module, "Indicates the object will be part of a kernel module"),
	OPT_BOOLEAN('b', "backtrace", &backtrace, "unwind on error"),
	OPT_BOOLEAN('a', "uaccess", &uaccess, "enable uaccess checking"),
	OPT_BOOLEAN('s', "stats", &stats, "print statistics"),
	OPT_BOOLEAN('d', "duplicate", &validate_dup, "duplicate validation for vmlinux.o"),
	OPT_BOOLEAN('n', "noinstr", &noinstr, "noinstr validation for vmlinux.o"),
	OPT_BOOLEAN('l', "vmlinux", &vmlinux, "vmlinux.o validation"),
	OPT_BOOLEAN('M', "mcount", &mcount, "generate __mcount_loc"),
	OPT_BOOLEAN('B', "backup", &backup, "create .orig files before modification"),
	OPT_END(),
पूर्ण;

पूर्णांक cmd_parse_options(पूर्णांक argc, स्थिर अक्षर **argv, स्थिर अक्षर * स्थिर usage[])
अणु
	स्थिर अक्षर *envv[16] = अणु पूर्ण;
	अक्षर *env;
	पूर्णांक envc;

	env = दो_पर्या("OBJTOOL_ARGS");
	अगर (env) अणु
		envv[0] = "OBJTOOL_ARGS";
		क्रम (envc = 1; envc < ARRAY_SIZE(envv); ) अणु
			envv[envc++] = env;
			env = म_अक्षर(env, ' ');
			अगर (!env)
				अवरोध;
			*env = '\0';
			env++;
		पूर्ण

		parse_options(envc, envv, check_options, env_usage, 0);
	पूर्ण

	argc = parse_options(argc, argv, check_options, usage, 0);
	अगर (argc != 1)
		usage_with_options(usage, check_options);
	वापस argc;
पूर्ण

पूर्णांक cmd_check(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *objname;
	काष्ठा objtool_file *file;
	पूर्णांक ret;

	argc = cmd_parse_options(argc, argv, check_usage);
	objname = argv[0];

	file = objtool_खोलो_पढ़ो(objname);
	अगर (!file)
		वापस 1;

	ret = check(file);
	अगर (ret)
		वापस ret;

	अगर (file->elf->changed)
		वापस elf_ग_लिखो(file->elf);

	वापस 0;
पूर्ण
