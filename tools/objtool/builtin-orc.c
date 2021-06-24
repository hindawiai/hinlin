<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */

/*
 * objtool orc:
 *
 * This command analyzes a .o file and adds .orc_unwind and .orc_unwind_ip
 * sections to it, which is used by the in-kernel ORC unwinder.
 *
 * This command is a superset of "objtool check".
 */

#समावेश <माला.स>
#समावेश <objtool/builtin.h>
#समावेश <objtool/objtool.h>

अटल स्थिर अक्षर *orc_usage[] = अणु
	"objtool orc generate [<options>] file.o",
	"objtool orc dump file.o",
	शून्य,
पूर्ण;

पूर्णांक cmd_orc(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *objname;

	argc--; argv++;
	अगर (argc <= 0)
		usage_with_options(orc_usage, check_options);

	अगर (!म_भेदन(argv[0], "gen", 3)) अणु
		काष्ठा objtool_file *file;
		पूर्णांक ret;

		argc = cmd_parse_options(argc, argv, orc_usage);
		objname = argv[0];

		file = objtool_खोलो_पढ़ो(objname);
		अगर (!file)
			वापस 1;

		ret = check(file);
		अगर (ret)
			वापस ret;

		अगर (list_empty(&file->insn_list))
			वापस 0;

		ret = orc_create(file);
		अगर (ret)
			वापस ret;

		अगर (!file->elf->changed)
			वापस 0;

		वापस elf_ग_लिखो(file->elf);
	पूर्ण

	अगर (!म_भेद(argv[0], "dump")) अणु
		अगर (argc != 2)
			usage_with_options(orc_usage, check_options);

		objname = argv[1];

		वापस orc_dump(objname);
	पूर्ण

	usage_with_options(orc_usage, check_options);

	वापस 0;
पूर्ण
