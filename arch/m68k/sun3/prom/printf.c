<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * म_लिखो.c:  Internal prom library म_लिखो facility.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

/* This routine is पूर्णांकernal to the prom library, no one अन्यथा should know
 * about or use it!  It's simple and smelly anyway....
 */

#समावेश <linux/kernel.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

#अगर_घोषित CONFIG_KGDB
बाह्य पूर्णांक kgdb_initialized;
#पूर्ण_अगर

अटल अक्षर ppbuf[1024];

व्योम
prom_म_लिखो(अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर ch, *bptr;
	पूर्णांक i;

	बहु_शुरू(args, fmt);

#अगर_घोषित CONFIG_KGDB
	ppbuf[0] = 'O';
	i = भम_लिखो(ppbuf + 1, fmt, args) + 1;
#अन्यथा
	i = भम_लिखो(ppbuf, fmt, args);
#पूर्ण_अगर

	bptr = ppbuf;

#अगर_घोषित CONFIG_KGDB
	अगर (kgdb_initialized) अणु
		pr_info("kgdb_initialized = %d\n", kgdb_initialized);
		putpacket(bptr, 1);
	पूर्ण अन्यथा
#अन्यथा
	जबतक((ch = *(bptr++)) != 0) अणु
		अगर(ch == '\n')
			prom_अक्षर_दो('\r');

		prom_अक्षर_दो(ch);
	पूर्ण
#पूर्ण_अगर
	बहु_पूर्ण(args);
	वापस;
पूर्ण
