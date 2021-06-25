<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */

/*
 * objtool:
 *
 * The 'check' subcmd analyzes every .o file and ensures the validity of its
 * stack trace metadata.  It enक्रमces a set of rules on यंत्र code and C अंतरभूत
 * assembly code so that stack traces can be reliable.
 *
 * For more inक्रमmation, see tools/objtool/Documentation/stack-validation.txt.
 */

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <subcmd/exec-cmd.h>
#समावेश <subcmd/pager.h>
#समावेश <linux/kernel.h>

#समावेश <objtool/builtin.h>
#समावेश <objtool/objtool.h>
#समावेश <objtool/warn.h>

काष्ठा cmd_काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक (*fn)(पूर्णांक, स्थिर अक्षर **);
	स्थिर अक्षर *help;
पूर्ण;

अटल स्थिर अक्षर objtool_usage_string[] =
	"objtool COMMAND [ARGS]";

अटल काष्ठा cmd_काष्ठा objtool_cmds[] = अणु
	अणु"check",	cmd_check,	"Perform stack metadata validation on an object file" पूर्ण,
	अणु"orc",		cmd_orc,	"Generate in-place ORC unwind tables for an object file" पूर्ण,
पूर्ण;

bool help;

स्थिर अक्षर *objname;
अटल काष्ठा objtool_file file;

अटल bool objtool_create_backup(स्थिर अक्षर *_objname)
अणु
	पूर्णांक len = म_माप(_objname);
	अक्षर *buf, *base, *name = दो_स्मृति(len+6);
	पूर्णांक s, d, l, t;

	अगर (!name) अणु
		लिखो_त्रुटि("failed backup name malloc");
		वापस false;
	पूर्ण

	म_नकल(name, _objname);
	म_नकल(name + len, ".orig");

	d = खोलो(name, O_CREAT|O_WRONLY|O_TRUNC, 0644);
	अगर (d < 0) अणु
		लिखो_त्रुटि("failed to create backup file");
		वापस false;
	पूर्ण

	s = खोलो(_objname, O_RDONLY);
	अगर (s < 0) अणु
		लिखो_त्रुटि("failed to open orig file");
		वापस false;
	पूर्ण

	buf = दो_स्मृति(4096);
	अगर (!buf) अणु
		लिखो_त्रुटि("failed backup data malloc");
		वापस false;
	पूर्ण

	जबतक ((l = पढ़ो(s, buf, 4096)) > 0) अणु
		base = buf;
		करो अणु
			t = ग_लिखो(d, base, l);
			अगर (t < 0) अणु
				लिखो_त्रुटि("failed backup write");
				वापस false;
			पूर्ण
			base += t;
			l -= t;
		पूर्ण जबतक (l);
	पूर्ण

	अगर (l < 0) अणु
		लिखो_त्रुटि("failed backup read");
		वापस false;
	पूर्ण

	मुक्त(name);
	मुक्त(buf);
	बंद(d);
	बंद(s);

	वापस true;
पूर्ण

काष्ठा objtool_file *objtool_खोलो_पढ़ो(स्थिर अक्षर *_objname)
अणु
	अगर (objname) अणु
		अगर (म_भेद(objname, _objname)) अणु
			WARN("won't handle more than one file at a time");
			वापस शून्य;
		पूर्ण
		वापस &file;
	पूर्ण
	objname = _objname;

	file.elf = elf_खोलो_पढ़ो(objname, O_RDWR);
	अगर (!file.elf)
		वापस शून्य;

	अगर (backup && !objtool_create_backup(objname)) अणु
		WARN("can't create backup file");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&file.insn_list);
	hash_init(file.insn_hash);
	INIT_LIST_HEAD(&file.retpoline_call_list);
	INIT_LIST_HEAD(&file.अटल_call_list);
	INIT_LIST_HEAD(&file.mcount_loc_list);
	file.c_file = !vmlinux && find_section_by_name(file.elf, ".comment");
	file.ignore_unreachables = no_unreachable;
	file.hपूर्णांकs = false;

	वापस &file;
पूर्ण

अटल व्योम cmd_usage(व्योम)
अणु
	अचिन्हित पूर्णांक i, दीर्घest = 0;

	म_लिखो("\n usage: %s\n\n", objtool_usage_string);

	क्रम (i = 0; i < ARRAY_SIZE(objtool_cmds); i++) अणु
		अगर (दीर्घest < म_माप(objtool_cmds[i].name))
			दीर्घest = म_माप(objtool_cmds[i].name);
	पूर्ण

	माला_दो(" Commands:");
	क्रम (i = 0; i < ARRAY_SIZE(objtool_cmds); i++) अणु
		म_लिखो("   %-*s   ", दीर्घest, objtool_cmds[i].name);
		माला_दो(objtool_cmds[i].help);
	पूर्ण

	म_लिखो("\n");

	अगर (!help)
		निकास(129);
	निकास(0);
पूर्ण

अटल व्योम handle_options(पूर्णांक *argc, स्थिर अक्षर ***argv)
अणु
	जबतक (*argc > 0) अणु
		स्थिर अक्षर *cmd = (*argv)[0];

		अगर (cmd[0] != '-')
			अवरोध;

		अगर (!म_भेद(cmd, "--help") || !म_भेद(cmd, "-h")) अणु
			help = true;
			अवरोध;
		पूर्ण अन्यथा अणु
			ख_लिखो(मानक_त्रुटि, "Unknown option: %s\n", cmd);
			cmd_usage();
		पूर्ण

		(*argv)++;
		(*argc)--;
	पूर्ण
पूर्ण

अटल व्योम handle_पूर्णांकernal_command(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *cmd = argv[0];
	अचिन्हित पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(objtool_cmds); i++) अणु
		काष्ठा cmd_काष्ठा *p = objtool_cmds+i;

		अगर (म_भेद(p->name, cmd))
			जारी;

		ret = p->fn(argc, argv);

		निकास(ret);
	पूर्ण

	cmd_usage();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अटल स्थिर अक्षर *UNUSED = "OBJTOOL_NOT_IMPLEMENTED";

	/* libsubcmd init */
	exec_cmd_init("objtool", UNUSED, UNUSED, UNUSED);
	pager_init(UNUSED);

	argv++;
	argc--;
	handle_options(&argc, &argv);

	अगर (!argc || help)
		cmd_usage();

	handle_पूर्णांकernal_command(argc, argv);

	वापस 0;
पूर्ण
