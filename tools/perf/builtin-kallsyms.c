<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * builtin-kallsyms.c
 *
 * Builtin command: Look क्रम a symbol in the running kernel and its modules
 *
 * Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश <पूर्णांकtypes.h>
#समावेश "builtin.h"
#समावेश <linux/compiler.h>
#समावेश <subcmd/parse-options.h>
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "symbol.h"

अटल पूर्णांक __cmd_kallsyms(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक i;
	काष्ठा machine *machine = machine__new_kallsyms();

	अगर (machine == शून्य) अणु
		pr_err("Couldn't read /proc/kallsyms\n");
		वापस -1;
	पूर्ण

	क्रम (i = 0; i < argc; ++i) अणु
		काष्ठा map *map;
		काष्ठा symbol *symbol = machine__find_kernel_symbol_by_name(machine, argv[i], &map);

		अगर (symbol == शून्य) अणु
			म_लिखो("%s: not found\n", argv[i]);
			जारी;
		पूर्ण

		म_लिखो("%s: %s %s %#" PRIx64 "-%#" PRIx64 " (%#" PRIx64 "-%#" PRIx64")\n",
			symbol->name, map->dso->लघु_name, map->dso->दीर्घ_name,
			map->unmap_ip(map, symbol->start), map->unmap_ip(map, symbol->end),
			symbol->start, symbol->end);
	पूर्ण

	machine__delete(machine);
	वापस 0;
पूर्ण

पूर्णांक cmd_kallsyms(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर काष्ठा option options[] = अणु
	OPT_INCR('v', "verbose", &verbose, "be more verbose (show counter open errors, etc)"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर kallsyms_usage[] = अणु
		"perf kallsyms [<options>] symbol_name",
		शून्य
	पूर्ण;

	argc = parse_options(argc, argv, options, kallsyms_usage, 0);
	अगर (argc < 1)
		usage_with_options(kallsyms_usage, options);

	symbol_conf.sort_by_name = true;
	symbol_conf.try_vmlinux_path = (symbol_conf.vmlinux_name == शून्य);
	अगर (symbol__init(शून्य) < 0)
		वापस -1;

	वापस __cmd_kallsyms(argc, argv);
पूर्ण
