<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cmdline.c: पढ़ो the command line passed to us by the PROM.
 *
 * Copyright (C) 1998 Harald Koerfgen
 * Copyright (C) 2002, 2004  Maciej W. Rozycki
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/dec/prom.h>

#अघोषित PROM_DEBUG

व्योम __init prom_init_cmdline(s32 argc, s32 *argv, u32 magic)
अणु
	अक्षर *arg;
	पूर्णांक start_arg, i;

	/*
	 * collect args and prepare cmd_line
	 */
	अगर (!prom_is_rex(magic))
		start_arg = 1;
	अन्यथा
		start_arg = 2;
	क्रम (i = start_arg; i < argc; i++) अणु
		arg = (व्योम *)(दीर्घ)(argv[i]);
		म_जोड़ो(arcs_cmdline, arg);
		अगर (i < (argc - 1))
			म_जोड़ो(arcs_cmdline, " ");
	पूर्ण

#अगर_घोषित PROM_DEBUG
	prपूर्णांकk("arcs_cmdline: %s\n", &(arcs_cmdline[0]));
#पूर्ण_अगर
पूर्ण
